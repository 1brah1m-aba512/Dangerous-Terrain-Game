#include "LibGame.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

namespace TerrainSpace {

int energy = 7; // Global variable to track player energy.

int getRandom(int intLower, int intUpper) {
    // Generate a random number within the given range.
    int intRange = intUpper - intLower + 1;
    return rand() % intRange + intLower;
}

int ConvertToString(string strNum) {
    int intNum = 0;
    stringstream ss {strNum};
    ss >> intNum;
    if (ss.fail()) {
        cerr << "Could not convert " << strNum << " to integer." << endl;
        exit(ERR_CONV); // Exit if conversion fails.
    }
    return intNum;
}

twoDArray initGame(int intRows, int intCols, int numU_OBSTACLES, int numMINES, int numT_ENERGY) {
    twoDArray arrGame = new oneDArray[intRows];
    for (int i = 0; i < intRows; i++) {
        arrGame[i] = new int[intCols];
        for (int j = 0; j < intCols; j++) {
            arrGame[i][j] = EMPTY; // Initialize the grid with EMPTY cells.
        }
    }
    // Place features on the grid.
    placeFeature(arrGame, intRows, intCols, PLAYER, 1);
    placeFeature(arrGame, intRows, intCols, U_OBSTACLE, numU_OBSTACLES);
    placeFeature(arrGame, intRows, intCols, MINES, numMINES);
    placeFeature(arrGame, intRows, intCols, T_ENERGY, numT_ENERGY);

    return arrGame;
}

void placeFeature(twoDArray arrGame, int intRows, int intCols, int intFeature, int intCount) {

    //places a feature randomly within a given range
    for (int n = 0; n < intCount; n++) {
        int intRow = getRandom(0, intRows - 1);
        int intCol = getRandom(0, intCols - 1);

        while (arrGame[intRow][intCol] != EMPTY) { // Ensure no overlap of features.
            intRow = getRandom(0, intRows - 1);
            intCol = getRandom(0, intCols - 1);
        }
        arrGame[intRow][intCol] = intFeature;
    }
}

void printWorld(twoDArray arrGame,int intRows,int intCols){

system("cls");//clean the display after each update

//Iterate through the whoole world and find which feature is placed where and display it
for (int k = 0 ;k<intRows;k++){

for (int c = 0; c<intCols;c++){

int intFeature = arrGame[k][c];
cout<<FEATURES[intFeature]<<' ';

}
cout <<" "<<endl;
}
//Menu and Player Control System
cout <<" "<<endl;
cout<<"W:Move UP"<<endl;
cout<<"A:Move LEFT"<<endl;
cout<<"S:Move Down"<<endl;
cout<<"D:Move RIGHT"<<endl;
cout<<"Q:Quit"<<endl;
cout<<"Energy:"<<energy<<endl;
}

//incase of invalid inputs pause the game
void pause(){
cin.ignore(100,'\n');
cout<<"Press Enter to Continue"<<endl;
cin.get();
}
//find the player wherever he is in the world
void findPlayer(twoDArray arrGame, int intRows, int intCols, int& intRow, int& intCol)
    {
        for(int r = 0; r < intRows; r++)
        {
            for(int c = 0; c < intCols; c++)
            {
                if(arrGame[r][c] == PLAYER)
                {
                    // Update intRow and intCol based on the value of r and c since they were passed by reference to this function.
                    intRow = r;
                    intCol = c;
                    break;
                }
            }
        }
    }

    void movePlayer(twoDArray arrGame, int intRows, int intCols, char chInput)
    {

        //GIve the player row default values
        int intPRow = 0;
        int intPCol = 0;

        // Find the player row and column.
        findPlayer(arrGame, intRows, intCols, intPRow, intPCol);

        int intDRow = intPRow;
        int intDCol = intPCol;
        // Modify the destination row and columns accordingly.

        switch(chInput)
        {

        //Left Movement
        case 'a':
            {

                --intDCol;
              }
              if(arrGame[intDRow][intDCol] == T_ENERGY){
              energy+=5;
              }
              else {

              //decrease energy
              energy--;
              }
                break;

        //Right Movement
        case 'd':

        {

                ++intDCol;
              }
if(arrGame[intDRow][intDCol] == T_ENERGY){
              energy+=5;
              }
              else {

              //decrease energy
              energy--;
              }
                break;

        //Up Movement
        case 'w':
            {

                --intDRow;
              }
if(arrGame[intDRow][intDCol] == T_ENERGY){
              energy+=5;
              }
              else {

              //decrease energy
              energy--;
              }
                break;

        //Down Movement
        case 's':
            {
            ++intDRow;
              }
if(arrGame[intDRow][intDCol] == T_ENERGY){
              energy+=5;
              }
              else {

              //decrease energy
              energy--;
              }
                break;
            }




 if(isInGame(intRows, intCols, intDRow, intDCol))
        {
           // Only move the player if the destination location is not an obstacle
           if(arrGame[intDRow][intDCol] != U_OBSTACLE){

            if(arrGame[intDRow][intDCol] == MINES)
            {
                arrGame[intDRow][intDCol] = EXPLOSION;//Player Status if land on mine
            }
            else{
                arrGame[intDRow][intDCol] = PLAYER;//if nothing in the way move player
            }
            arrGame[intPRow][intPCol] = EMPTY;//make the previous player position empty
            }
            else{
            energy +=1;//increase energy if lands on an energy point
            }
            }
            }


    bool isInGame(int intRows, int intCols, int intRow, int intCol)
    {
    //check if player is within in the world
        if(intRow < 0 || intRow >= intRows)
            return false;
        if(intCol < 0 || intCol >= intCols)
            return false;
        return true;
    }
    //check if the player has lost
    bool isDefeat(twoDArray arrGame, int intRows, int intCols)
    {
        for(int r = 0; r < intRows; r++)
        {
            for(int c = 0; c < intCols; c++)
            {
            //defeat through explosion or energy depletion
                if(arrGame[r][c] == EXPLOSION || energy == 0)
                    return true;

            }
        }
        return false;
    }

    //Check if the player has won
    bool isVictory(twoDArray arrGame, int intRows, int intCols)
    {
        for(int r = 0; r < intRows; r++)
        {
            for(int c = 0; c < intCols; c++)
            {
            //win if player has recahed the last the coloumn
                if(arrGame[r][c] == PLAYER
                    && c == intCols - 1)
                    return true;
            }
        }
        return false;
    }

    //deallocate memory to ensure no memory leaks
void dealloc(twoDArray& arrGame, int intRows) {
    for (int r = 0; r < intRows; r++)
        delete [] arrGame[r];
    delete [] arrGame;
    arrGame = nullptr;


}
}
