#ifndef LIBGAME_H_INCLUDED
#define LIBGAME_H_INCLUDED

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

namespace TerrainSpace {

// Error codes.
const int ERR_ARGC = -1; // Invalid number of arguments.
const int ERR_CONV = -2; // Conversion error.
const int ERR_RANGE = -3; // Range error.

// Grid size constraints.
const int MAX_SIZE = 20; // Maximum grid size.
const int MIN_SIZE = 5;  // Minimum grid size.

// Feature types.
const int EMPTY = 0;
const int PLAYER = 1;
const int U_OBSTACLE = 2;
const int MINES = 3;
const int T_ENERGY = 4;
const int PLAYER_T_ENERGY = 5;
const int EXPLOSION = 6;

// Symbols for displaying features on the grid.
const char FEATURES[6] = {'.', 'P', 'O', '*', 'T', 'P'};

// Typedefs for dynamic arrays.
typedef int* oneDArray;
typedef int** twoDArray;

// Function declarations.
int ConvertToString(string strNum);
twoDArray initGame(int intRows, int intCols, int numU_OBSTACLES, int numMINES, int numT_ENERGY);
void placeFeature(twoDArray arrGame, int intRows, int intCols, int Feature, int intCount);
void printWorld(twoDArray arrGame, int intRows, int intCols);
void pause();
void movePlayer(twoDArray arrGame, int intRows, int intCols, char chInput);
void findPlayer(twoDArray arrGame, int intRows, int intCols, int& intRow, int& intCol);
bool isInGame(int intRows, int intCols, int intRow, int intCol);
bool isVictory(twoDArray arrGame, int intRows, int intCols);
bool isDefeat(twoDArray arrGame, int intRows, int intCols);
void dealloc(twoDArray& arrGame, int intRows); // Deallocates memory used by the grid.

}

#endif // LIBGAME_H_INCLUDED
