#include "GameView.h"
#include "Board.h"
#include "Cell.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

GameView::GameView(int width, int gridCount)
    : tickRate(0.1f),
      isPaused(false),
      boardViewSize(width), // 900 px
      menuWidth(250),
      currentGridSize(gridCount),
      focusSpeed(false), focusInf(false), focusImm(false), focusSize(false)
{
    // 1. TWORZENIE OKNA
    int totalWidth = boardViewSize + menuWidth;
    int totalHeight = boardViewSize;

    if (totalHeight < 600) totalHeight = 600;

    window.create(sf::VideoMode(totalWidth, totalHeight), "Symulacja - Fixed 900px", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    // 2. LOGIKA STARTOWA
    gameLogic = new Run(gridCount, gridCount);
    gameLogic->setBoardBounds(true); // Domyślnie ściany włączone

    findAndLoadSystemFont();

    // Wartości startowe
    strSpeed = "100";
    strInf = std::to_string(gameLogic->getInfectionTime());
    strImm = std::to_string(gameLogic->getImmunityTime());
    strSize = std::to_string(gridCount);

    initMenu();
    updateMenuText(); // <--- WAŻNE: Ustawia napis na przycisku po raz pierwszy
}

GameView::~GameView() {
    delete gameLogic;
}

void GameView::resetGame() {
    // 1. Zczytaj nową gęstość siatki
    try {
        int newSize = std::stoi(strSize);
        if (newSize < 5) newSize = 5;
        if (newSize > 300) newSize = 300;
        currentGridSize = newSize;
    } catch (...) {
        currentGridSize = 50;
    }

    // 2. Zachowaj stare ustawienia
    int oldInf = gameLogic->getInfectionTime();
    int oldImm = gameLogic->getImmunityTime();
    bool oldBounds = gameLogic->isBoundsEnabled(); // <--- ZACHOWAJ STAN ŚCIAN

    // 3. Restart
    delete gameLogic;
    gameLogic = new Run(currentGridSize, currentGridSize);

    gameLogic->setInfectionTime(oldInf);
    gameLogic->setImmunityTime(oldImm);
    gameLogic->setBoardBounds(oldBounds); // <--- PRZYWRÓĆ STAN ŚCIAN
}

void GameView::initMenu() {
    int x = boardViewSize + 20;
    int y = 20;

    // Przycisk PAUZA
    btnPause.setSize(sf::Vector2f(210, 40));
    btnPause.setPosition(x, y);
    btnPause.setFillColor(sf::Color(200, 50, 50));

    txtPause.setFont(font);
    txtPause.setString("PAUZA");
    txtPause.setCharacterSize(18);
    txtPause.setPosition(x + 75, y + 8);

    auto setupInput = [&](sf::RectangleShape& box, sf::Text& txt, sf::Text& lbl, std::string label, int yPos) {
        lbl.setFont(font);
        lbl.setString(label);
        lbl.setCharacterSize(14);
        lbl.setPosition(x, yPos);

        box.setSize(sf::Vector2f(210, 30));
        box.setPosition(x, yPos + 20);
        box.setFillColor(sf::Color::White);
        box.setOutlineThickness(2);
        box.setOutlineColor(sf::Color(100, 100, 100));

        txt.setFont(font);
        txt.setCharacterSize(18);
        txt.setFillColor(sf::Color::Black);
        txt.setPosition(x + 5, yPos + 23);
    };

    y += 60; setupInput(boxSpeed, txtSpeedDisplay, lblSpeed, "Predkosc (ms):", y);
    y += 60; setupInput(boxInf, txtInfDisplay, lblInf, "Czas Infekcji (tury):", y);
    y += 60; setupInput(boxImm, txtImmDisplay, lblImm, "Czas Odpornosci (tury):", y);
    y += 60; setupInput(boxSize, txtSizeDisplay, lblSize, "Gestosc Siatki (Ilosc):", y);

    // --- PRZYCISK OBRAMOWANIE (TEGO BRAKOWAŁO) ---
    y += 70;
    btnBounds.setSize(sf::Vector2f(210, 40));
    btnBounds.setPosition(x, y);
    btnBounds.setFillColor(sf::Color(100, 100, 100)); // Startowy kolor

    txtBounds.setFont(font);
    txtBounds.setCharacterSize(14); // Mniejsza czcionka żeby weszło
    txtBounds.setPosition(x + 20, y + 10);

    // --- PRZYCISK RESET ---
    y += 60;
    btnReset.setSize(sf::Vector2f(210, 40));
    btnReset.setPosition(x, y);
    btnReset.setFillColor(sf::Color(50, 100, 200));

    txtReset.setFont(font);
    txtReset.setString("APLIKUJ / RESET");
    txtReset.setCharacterSize(16);
    txtReset.setPosition(x + 40, y + 10);
}

// --- NOWA METODA (TEGO BRAKOWAŁO) ---
void GameView::updateMenuText() {
    if (gameLogic->isBoundsEnabled()) {
        txtBounds.setString("MAPA: SCIANY");
        btnBounds.setFillColor(sf::Color(180, 100, 100)); // Czerwony
    } else {
        txtBounds.setString("MAPA: PRZEJSCIE");
        btnBounds.setFillColor(sf::Color(100, 180, 100)); // Zielony
    }
}

void GameView::findAndLoadSystemFont() {
    std::string searchPaths[] = { "/usr/share/fonts", "/usr/local/share/fonts", "~/.fonts" };
    bool found = false;
    if (font.loadFromFile("font.ttf")) return;

    for (const auto& path : searchPaths) {
        if (!fs::exists(path)) continue;
        try {
            for (const auto& entry : fs::recursive_directory_iterator(path)) {
                if (entry.is_regular_file() && entry.path().extension() == ".ttf") {
                    if (font.loadFromFile(entry.path().string())) {
                        found = true; break;
                    }
                }
            }
        } catch (...) {}
        if (found) break;
    }
}

void GameView::start() {
    sf::Clock clock;
    float timeAccumulator = 0.0f;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        if (!isPaused) timeAccumulator += dt;
        processEvents();
        if (timeAccumulator >= tickRate) {
            update(tickRate);
            timeAccumulator = 0.0f;
        }
        render();
    }
}

void GameView::handleInput(sf::Uint32 unicode) {
    std::string* activeStr = nullptr;
    if (focusSpeed) activeStr = &strSpeed;
    if (focusInf) activeStr = &strInf;
    if (focusImm) activeStr = &strImm;
    if (focusSize) activeStr = &strSize;

    if (!activeStr) return;
    if (unicode == 8) { if (!activeStr->empty()) activeStr->pop_back(); }
    else if (unicode >= 48 && unicode <= 57) { if (activeStr->length() < 5) *activeStr += static_cast<char>(unicode); }

    updateLogicFromInputs();
}

void GameView::updateLogicFromInputs() {
    try {
        if (!strSpeed.empty()) {
            int ms = std::stoi(strSpeed);
            if (ms < 1) ms = 1;
            tickRate = ms / 1000.0f;
        }
        if (!strInf.empty()) gameLogic->setInfectionTime(std::stoi(strInf));
        if (!strImm.empty()) gameLogic->setImmunityTime(std::stoi(strImm));
    } catch (...) {}
}

void GameView::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
        if (event.type == sf::Event::TextEntered) handleInput(event.text.unicode);

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            focusSpeed = false; focusInf = false; focusImm = false; focusSize = false;
            boxSpeed.setOutlineColor(sf::Color(100, 100, 100));
            boxInf.setOutlineColor(sf::Color(100, 100, 100));
            boxImm.setOutlineColor(sf::Color(100, 100, 100));
            boxSize.setOutlineColor(sf::Color(100, 100, 100));

            if (boxSpeed.getGlobalBounds().contains(mousePos.x, mousePos.y)) { focusSpeed = true; boxSpeed.setOutlineColor(sf::Color::Blue); }
            else if (boxInf.getGlobalBounds().contains(mousePos.x, mousePos.y)) { focusInf = true; boxInf.setOutlineColor(sf::Color::Blue); }
            else if (boxImm.getGlobalBounds().contains(mousePos.x, mousePos.y)) { focusImm = true; boxImm.setOutlineColor(sf::Color::Blue); }
            else if (boxSize.getGlobalBounds().contains(mousePos.x, mousePos.y)) { focusSize = true; boxSize.setOutlineColor(sf::Color::Blue); }

            if (btnPause.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                isPaused = !isPaused;
                if (isPaused) { btnPause.setFillColor(sf::Color(50, 200, 50)); txtPause.setString("START"); }
                else { btnPause.setFillColor(sf::Color(200, 50, 50)); txtPause.setString("PAUZA"); }
            }

            // --- KLIKNIĘCIE W PRZYCISK BOUNDS (TEGO BRAKOWAŁO) ---
            if (btnBounds.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                bool current = gameLogic->isBoundsEnabled();
                gameLogic->setBoardBounds(!current);
                updateMenuText();
            }

            if (btnReset.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                resetGame();
            }

            // Kliknięcie w planszę
            if (mousePos.x < boardViewSize && mousePos.y < boardViewSize && mousePos.x >= 0 && mousePos.y >= 0) {
                float dynamicCellSize = static_cast<float>(boardViewSize) / currentGridSize;
                int col = static_cast<int>(mousePos.x / dynamicCellSize);
                int row = static_cast<int>(mousePos.y / dynamicCellSize);
                gameLogic->spawnInfection(row, col);
            }
        }
    }
}

void GameView::update(float dt) {
    gameLogic->updateGame();
}

void GameView::render() {
    window.clear(sf::Color(30, 30, 30));

    Board& board = gameLogic->getBoard();
    float dynamicCellSize = static_cast<float>(boardViewSize) / currentGridSize;

    sf::RectangleShape rect(sf::Vector2f(dynamicCellSize + 0.5f, dynamicCellSize + 0.5f));

    for (int r = 0; r < board.getRows(); ++r) {
        for (int c = 0; c < board.getCols(); ++c) {
            Cell* cell = board.getCell(r, c);
            rect.setPosition(c * dynamicCellSize, r * dynamicCellSize);

            switch (cell->getCurrentState()) {
                case HEALTHY: rect.setFillColor(sf::Color(240, 220, 200)); break;
                case INFECTED: rect.setFillColor(sf::Color(200, 40, 40)); break;
                case IMMUNE: rect.setFillColor(sf::Color(60, 100, 180)); break;
                default: rect.setFillColor(sf::Color::Black);
            }
            window.draw(rect);
        }
    }

    sf::RectangleShape menuBg(sf::Vector2f(menuWidth, window.getSize().y));
    menuBg.setPosition(boardViewSize, 0);
    menuBg.setFillColor(sf::Color(50, 50, 50));
    window.draw(menuBg);

    window.draw(btnPause); window.draw(txtPause);
    window.draw(btnReset); window.draw(txtReset);

    window.draw(btnBounds); window.draw(txtBounds);

    txtSpeedDisplay.setString(strSpeed);
    txtInfDisplay.setString(strInf);
    txtImmDisplay.setString(strImm);
    txtSizeDisplay.setString(strSize);

    window.draw(lblSpeed); window.draw(boxSpeed); window.draw(txtSpeedDisplay);
    window.draw(lblInf);   window.draw(boxInf);   window.draw(txtInfDisplay);
    window.draw(lblImm);   window.draw(boxImm);   window.draw(txtImmDisplay);
    window.draw(lblSize);  window.draw(boxSize);  window.draw(txtSizeDisplay);

    window.display();
}