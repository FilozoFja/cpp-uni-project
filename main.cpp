#include "GameView.h"
#include <stdlib.h>

int main() {
    setenv("LIBGL_ALWAYS_SOFTWARE", "1", 1);
    GameView app(900, 50);

    app.start();
    return 0;
}