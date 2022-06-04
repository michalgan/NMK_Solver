//
// Created by michal on 01.06.22.
//

#ifndef NMK_SOLVER_GAME_H
#define NMK_SOLVER_GAME_H

#include <iostream>
class Game {
public:
    Game(int y, int x, int tilesInRow);
    Game(int y, int x, int tilesInRow, int currentPlayer);
    int getSizeX() const;
    int getSizeY() const;
    void changeThePlayer();
    void printGameState();
    void changeContentOnTile(int y, int x, int content);
    void printGameWithChangedContent(int y, int x, int content);
    bool checkInRow(int y, int x) const;
    bool checkInColumn(int y, int x) const;
    bool checkInSlash(int y, int x) const;
    bool checkInBackslash(int y, int x) const;
    int checkWinForGameWithChangedContent(int y, int x) const;
    int countAllPossibleMoves() ;
    void printAllPossibleMoves();
    bool cutIfTheGameOver();
    int checkRows() const;
    int checkColumns() const;
    int checkBackslashes() const;
    int checkSlashes() const;
    int findWinner() ;
    bool checkIfTheGameIsOver() const ;
    int minimax(int depth, int player);
    void solveGameState();
    ~Game();

private:
    int ** board;
    const int sizeX;
    const int sizeY;
    const int tilesInRow;
    int currentPlayer;
};

#endif //NMK_SOLVER_GAME_H
