#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <SFML/Graphics.hpp>
#include "Run.h"
#include <string>

class GameView {
private:
    sf::RenderWindow window;
    Run* gameLogic;

    float tickRate;
    bool isPaused;

    int boardViewSize;
    int menuWidth;
    int currentGridSize;

    // GUI
    sf::Font font;
    sf::RectangleShape btnPause, btnReset;
    sf::Text txtPause, txtReset;

    sf::RectangleShape btnBounds;
    sf::Text txtBounds;

    sf::RectangleShape boxSpeed, boxInf, boxImm, boxSize;
    sf::Text txtSpeedDisplay, txtInfDisplay, txtImmDisplay, txtSizeDisplay;
    sf::Text lblSpeed, lblInf, lblImm, lblSize;

    std::string strSpeed, strInf, strImm, strSize;
    bool focusSpeed, focusInf, focusImm, focusSize;

    void findAndLoadSystemFont();
    void initMenu();
    void updateMenuText();
    void processEvents();
    void update(float dt);
    void render();
    void handleInput(sf::Uint32 unicode);
    void updateLogicFromInputs();
    void resetGame();

public:
    GameView(int width, int gridCount);
    ~GameView();
    void start();
};

#endif //GAMEVIEW_H