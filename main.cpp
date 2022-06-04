#include <iostream>
#include <cstring>
#include "Game.h"

Game * createGameFromLoadedData(int n, int m, int k, int activePlayer){
    int content;
    Game * game = new Game(n, m, k,activePlayer );
    for (int i = 0; i < game->getSizeY(); ++i) {
        for (int j = 0; j < game->getSizeX(); ++j) {
            scanf("%d", &content);
            game->changeContentOnTile(i, j, content);

        }

    }
    return game;
}

void inputCommand() {
    char *  command = new char[40];
    int n, m, k, activePlayer;
    scanf("%39s ", command);
    scanf("%d %d %d %d", &n, &m, &k, &activePlayer);
    if(strcmp(command, "GEN_ALL_POS_MOV") == 0){
        Game * game = createGameFromLoadedData(n, m, k, activePlayer);
        game->printAllPossibleMoves();
        delete game;

    }
    else if(strcmp(command, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0){
        Game * game = createGameFromLoadedData(n, m, k, activePlayer);
        if(!game->cutIfTheGameOver()){
            game->printAllPossibleMoves();

        }
        delete game;

    }
    else  if(strcmp(command, "SOLVE_GAME_STATE") == 0){
        Game * game = createGameFromLoadedData(n, m, k, activePlayer);
        game->solveGameState();
        delete game;


    }
    else{

    }
}


int main() {
    while(feof(stdin) == 0)
        inputCommand();
    return 0;
}