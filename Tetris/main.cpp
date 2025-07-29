#include "Tetris.h"
#include <iostream>
#include <ctime>

using namespace std;

#undef main
int main(int argc, char* argv[]) {
    srand(time(0));
    Tetris* game = new Tetris();
    const char* name = "Tetris";
    game->init(name);
    while (game->TetrisWait()) {
        while (game->Tetrisrunning()) {
            game->setCurrentTime(SDL_GetTicks());
            game->handleEvennts();

            if (game->Tetrisback1()) {
                game->Loadingback1();
            }
            else if (game->isChoosingTheme()) {
                game->ChooseTheme();
            }
            else {
                game->Gameplay();
                game->UpdateRender();
            }
            game->GameOver();
        }

        bool goBackToMenu = false;
        bool playAgain = false;
        game->GameOverScreen(goBackToMenu, playAgain);

        if (goBackToMenu) {
            game->Setback1(true);
        }

        if (playAgain) {
            game->Setback1(false);
            if (game->isChoosingTheme()) {
                game->ChooseTheme();
            }
        }

        game->Reset();

        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            }
        }
    }
    game->Clean();
    return 0;
}
