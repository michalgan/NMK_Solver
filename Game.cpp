//
// Created by michal on 01.06.22.
//

#include "Game.h"


Game::Game(int y, int x, int tilesInRow) : sizeX(x), sizeY(y), tilesInRow(tilesInRow) {
    this->board = new int * [y];
    for (int i = 0; i < y; ++i) {
        board[i] = new int[x];
        for (int j = 0; j < x; ++j) {
            board[i][j] = 0;

        }

    }
    this->currentPlayer = 1;
}

Game::Game(int y, int x, int tilesInRow, int currentPlayer) : sizeX(x), sizeY(y), tilesInRow(tilesInRow) {
    this->currentPlayer = currentPlayer;
    this->board = new int * [y];
    for (int i = 0; i < y; ++i) {
        board[i] = new int[x];
        for (int j = 0; j < x; ++j) {
            board[i][j] = 0;

        }

    }
    this->currentPlayer = currentPlayer;
}
int Game::getSizeX() const{
    return sizeX;
}
int Game::getSizeY() const{
    return sizeY;
}

void Game::changeThePlayer(){
    if(currentPlayer == 1){
        currentPlayer = 2;

    }
    else if(currentPlayer == 2){
        currentPlayer = 1;

    }
}

void Game::printGameState(){
    for (int i = 0; i < sizeY; ++i) {
        for (int j = 0; j < sizeX; ++j) {
            printf("%d ", board[i][j]);

        }
        printf("\n");

    }
}

void Game::changeContentOnTile(int y, int x, int content){
    board[y][x] = content;
}
void Game::printGameWithChangedContent(int y, int x, int content){
    for (int i = 0; i < sizeY; ++i) {
        for (int j = 0; j < sizeX; ++j) {
            if(i == y && j == x){
                printf("%d ", content);

            }
            else{
                printf("%d ", board[i][j]);

            }

        }
        printf("\n");

    }

}

bool Game::checkInRow(int y, int x) const{
    int counter = 1;
    bool backward = true, forward = true;
    for (int i = 1; i < tilesInRow; ++i) {
        if(x+i >= sizeX){
            forward = false;

        }
        if(x-i < 0){
            backward = false;

        }
        if(forward){
            if(board[y][x+i] == currentPlayer){
                counter += 1;

            }
            else{
                forward = false;

            }

        }
        if(backward){
            if(board[y][x-i] == currentPlayer){
                counter += 1;

            }
            else{
                forward = false;

            }

        }

    }
    return counter >= tilesInRow;
}


bool Game::checkInColumn(int y, int x) const{
    int counter = 1;
    bool backward = true, forward = true;
    for (int i = 1; i < tilesInRow; ++i) {
        if(y+i >= sizeY){
            forward = false;

        }
        if(y-i < 0){
            backward = false;

        }
        if(forward){
            if(board[y+i][x] == currentPlayer){
                counter += 1;

            }
            else{
                forward = false;

            }

        }
        if(backward){
            if(board[y-i][x] == currentPlayer){
                counter += 1;

            }
            else{
                forward = false;

            }

        }

    }
    return counter >= tilesInRow;
}

bool Game::checkInBackslash(int y, int x) const{
    int counter = 1;
    bool backward = true, forward = true;
    for (int i = 1; i < tilesInRow; ++i) {
        if(y+i >= sizeY || x+i >= sizeX){
            forward = false;

        }
        if(y-i < 0 || x-i < 0){
            backward = false;

        }
        if(forward){
            if(board[y+i][x+i] == currentPlayer){
                counter += 1;

            }
            else{
                forward = false;

            }

        }
        if(backward){
            if(board[y-i][x-i] == currentPlayer){
                counter += 1;

            }
            else{
                forward = false;

            }

        }

    }
    return counter >= tilesInRow;
}

bool Game::checkInSlash(int y, int x) const{
    int counter = 1;
    bool backward = true, forward = true;
    for (int i = 1; i < tilesInRow; ++i) {
        if(y+i >= sizeY || x-i < 0){
            forward = false;

        }
        if(y-i < 0 || x+i >= sizeX){
            backward = false;

        }
        if(forward){
            if(board[y+i][x-i] == currentPlayer){
                counter += 1;

            }
            else{
                forward = false;

            }

        }
        if(backward){
            if(board[y-i][x+i] == currentPlayer){
                counter += 1;

            }
            else{
                forward = false;

            }

        }

    }
    return counter >= tilesInRow;

}

int Game::checkWinForGameWithChangedContent(int y, int x) const{
    if(tilesInRow <= 1){
        return currentPlayer;

    }
    if(checkInRow(y, x) || checkInColumn(y, x) || checkInSlash(y, x) || checkInBackslash(y, x)){
        return currentPlayer;

    }
    else{
        return 0;

    }
}



int Game::checkRows() const{
    bool found = false;
    int winner = 0;
    for (int i = 0; i < sizeY; ++i) {
        int counter = 1;
        int lastTileOwner = board[i][0];
        for (int j = 1; j < sizeX; ++j) {
            if(board[i][j] == lastTileOwner && board[i][j] != 0){
                counter++;
                if(counter >= tilesInRow){
                    found = true;
                    winner = lastTileOwner;
                    break;

                }

            }
            else{
                lastTileOwner = board[i][j];
                counter = 1;

            }

        }
        if(found){
            break;

        }

    }
    return winner;
}

int Game::checkColumns() const{
    bool found = false;
    int winner = 0;
    for (int i = 0; i < sizeX; ++i) {
        int counter = 1;
        int lastTileOwner = board[0][i];
        for (int j = 1; j < sizeY; ++j) {
            if(board[j][i] == lastTileOwner && board[j][i] != 0){
                counter++;
                if(counter >= tilesInRow){
                    found = true;
                    winner = lastTileOwner;
                    break;

                }

            }
            else{
                lastTileOwner = board[j][i];
                counter = 1;

            }

        }
        if(found){
            break;

        }

    }
    return winner;
}

int Game::checkBackslashes() const{
    int counter, lastTileOwner;
    bool found = false;
    int winner = 0;
    for (int i = 0; i < sizeY; ++i) {
        counter = 1;
        lastTileOwner = board[i][0];
        for (int j = 1; j < sizeX && i+j < sizeY; ++j) {
            if(board[i+j][j] == lastTileOwner && board[i+j][j] != 0){
                counter += 1;
                if(counter >= tilesInRow){
                    found = true;
                    winner = lastTileOwner;
                    break;

                }

            }
            else{
                lastTileOwner = board[i+j][j];
                counter = 1;

            }

        }
        if(found){
            break;

        }

    }

    for (int i = 0; i < sizeX; ++i) {
        counter = 1;
        lastTileOwner = board[0][i];
        for (int j = 1; j < sizeY && i+j < sizeX; ++j) {
            if(board[j][i+j] == lastTileOwner && board[j][i+j] != 0){
                counter += 1;
                if(counter >= tilesInRow){
                    found = true;
                    winner = lastTileOwner;
                    break;

                }

            }
            else{
                lastTileOwner = board[j][i+j];
                counter = 1;

            }

        }
        if(found){
            break;

        }

    }
    return winner;
}


int Game::checkSlashes() const{
    int counter, lastTileOwner;
    bool found = false;
    int winner = 0;
    for (int i = 0; i < sizeY; ++i) {
        counter = 1;
        lastTileOwner = board[i][0];
        for (int j = 1; j < sizeX && i-j >= 0; ++j) {
            if(board[i-j][j] == lastTileOwner && board[i-j][j] != 0){
                counter++;
                if(counter >= tilesInRow){
                    found = true;
                    winner = lastTileOwner;
                    break;

                }

            }
            else{
                counter = 1;
                lastTileOwner = board[i-j][j];

            }

        }
        if(found){
            break;

        }

    }

    for (int i = 0; i < sizeX; ++i) {
        counter = 1;
        lastTileOwner = board[sizeY-1][i];
        for (int j = sizeY-2; j >= 0 && i+(sizeY-1-j) < sizeX; --j) {
            if(board[j][i+(sizeY-1-j)] == lastTileOwner && board[j][i+(sizeY-1-j)] != 0){
                counter++;
                if(counter >= tilesInRow){
                    found = true;
                    winner = lastTileOwner;
                    break;

                }

            }
            else{
                counter = 1;
                lastTileOwner = board[j][i+(sizeY-1-j)];

            }

        }
        if(found){
            break;

        }

    }

    return winner;
}
int Game::countAllPossibleMoves() {
    if(checkIfTheGameIsOver()){
        return 0;

    }
    else{
        int counter = 0;
        for (int i = 0; i < sizeY; ++i) {
            for (int j = 0; j < sizeX; ++j) {
                if(board[i][j] == 0){
                    counter++;

                }

            }

        }
        return counter;

    }
}

int Game::findWinner() {
    if(checkRows() != 0){
        return checkRows();

    }
    if(checkColumns() != 0){
        return checkColumns();

    }
    if(checkBackslashes() != 0){
        return checkBackslashes();

    }
    if(checkSlashes() != 0){
        return checkSlashes();

    }
    if(countAllPossibleMoves() == 0){
        return 0;

    }
    else{
        return -1;

    }

}

bool Game::checkIfTheGameIsOver() const {
    return checkRows() != 0 || checkColumns() != 0 || checkBackslashes() != 0 || checkSlashes() != 0 || tilesInRow <= 1;
}




void Game::printAllPossibleMoves(){
    int n = countAllPossibleMoves();
    printf("%d\n", n);
    if(n != 0){
        for (int i = 0; i < sizeY; ++i) {
            for (int j = 0; j < sizeX; ++j) {
                if(board[i][j] == 0){
                    printGameWithChangedContent(i, j, currentPlayer);

                }

            }

        }

    }
}


bool Game::cutIfTheGameOver(){
    bool end = checkIfTheGameIsOver();
    if(!end){
        for (int i = 0; i < sizeY; ++i) {
            for (int j = 0; j < sizeX; ++j) {
                if(board[i][j] == 0){
                    if(checkWinForGameWithChangedContent(i, j) != 0){
                        printf("1\n");
                        printGameWithChangedContent(i, j, currentPlayer);
                        end = true;
                        break;

                    }

                }

            }
            if(end){
                break;

            }

        }

    }
    else{
        printf("0\n");

    }
    return end;
}


int Game::minimax(int depth, int player) {
    int result = findWinner();
    bool reachedFinalResult = false;
    if(result == 1){
        return 1;

    }
    else if(result == 0){
        return 0;

    }
    else if(result != -1){
        return -1;

    }
    else{
        int bestScore = 2;
        if(player == 1){
            bestScore = -2;

        }
        for (int i = 0; i < sizeY; ++i) {
            for (int j = 0; j < sizeX; ++j) {
                if(board[i][j] == 0){
                    board[i][j] = player;
                    if(player == 1){
                        int score = minimax( depth+1, 2);
                        if(score > bestScore){
                            bestScore = score;

                        }
                        if(bestScore == 1) reachedFinalResult = true;

                    }
                    else{
                        int score = minimax( depth+1, 1);
                        if(score < bestScore){
                            bestScore = score;

                        }
                        if(bestScore == -1) reachedFinalResult = true;

                    }
                    board[i][j] = 0;
                    if(reachedFinalResult) break;

                }
                if(reachedFinalResult) break;

            }

        }
        return bestScore;

    }

}

void Game::solveGameState(){
    /*int maxScore , maxScoreX, maxScoreY, winner = findWinner();
    maxScore = std::round_toward_infinity;
    if(currentPlayer == 1){
        maxScore = std::round_toward_neg_infinity;
    }
    maxScoreX = 0;
    maxScoreY = 0;
    while(winner == -1){
        for (int i = 0; i < sizeY; ++i) {
            for (int j = 0; j < sizeX; ++j) {
                if(board[i][j] == 0){
                    board[i][j] = currentPlayer;
                    if(currentPlayer == 1){
                        int score = minimax( 0, 1);
                        if(score > maxScore){
                            maxScore = score;
                            maxScoreY = i;
                            maxScoreX = j;
                        }
                    }
                    else{
                        int score = minimax( 0, 2);
                        if(score < maxScore){
                            maxScore = score;
                            maxScoreY = i;
                            maxScoreX = j;
                        }
                    }
                    board[i][j] = 0;
                }
            }
        }
        board[maxScoreY][maxScoreX] = currentPlayer;
        winner = findWinner();
        changeThePlayer();
    }*/

    int winner = minimax(0,currentPlayer);

    switch(winner){
        case 0:
            printf("BOTH_PLAYERS_TIE\n");
            break;
        case 1:
            printf("FIRST_PLAYER_WINS\n");
            break;
        case -1:
            printf("SECOND_PLAYER_WINS\n");
            break;
        default:
            printf("winner: %d, count: %d Check value for the variable \"winner\" in function \"solveGameState(int y, int x)\"\n", winner, countAllPossibleMoves());

    }


}



Game::~Game(){
    delete board;
}
