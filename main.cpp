//Completed between 19/04/2024 - 26/04/2024

#include "LibGame.h"
#include <iostream>
#include <ctime>

using namespace std;
using namespace TerrainSpace;

int main(int argc,char** argv)
{
    srand(time(nullptr)); // Seed the random number generator with the current time.

    if (argc != 6) { // Ensure exactly 6 command-line arguments are provided.
        cerr << "Please enter a valid number of arguments.";
        cerr << "Please run " << argv[0] << " <TotalRows> <TotalCols> <numU_OBSTACLES> <numMINES> <numT_ENERGY>" << endl;
        exit(ERR_ARGC); // Exit with an error code if arguments are invalid.
    }

    // Convert command-line arguments from strings to integers.
    int intRows = ConvertToString(argv[1]);
    int intCols = ConvertToString(argv[2]);
    int numU_OBSTACLES = ConvertToString(argv[3]);
    int numMINES = ConvertToString(argv[4]);
    int numT_ENERGY = ConvertToString(argv[5]);

    // Validate the grid size against minimum and maximum limits.
    if (intRows > MAX_SIZE || intCols > MAX_SIZE || intRows < MIN_SIZE || intCols < MIN_SIZE) {
        cerr << "Command Line arguments must be greater than " << MIN_SIZE << " and less than " << MAX_SIZE << endl;
        exit(ERR_RANGE); // Exit if grid size is out of range.
    }

    bool blnContinue = true; // Control variable for the game loop.
    char chInput = '\0'; // Variable to store user input.

    // Initialize the game board with the specified parameters.
    twoDArray arrGame = initGame(intRows, intCols, numU_OBSTACLES, numMINES, numT_ENERGY);

    do {
        printWorld(arrGame, intRows, intCols); // Display the current state of the game board.

        cin >> chInput; // Get user input.
        chInput = tolower(chInput); // Convert input to lowercase for uniformity.

        switch (chInput) {
            case 'w': // Move up.
            case 'a': // Move left.
            case 's': // Move down.
            case 'd': { // Move right.
                movePlayer(arrGame, intRows, intCols, chInput); // Perform the player movement.
                break;
            }
            case 'q': { // Quit the game.
                blnContinue = false;
                break;
            }
            default: { // Handle invalid inputs.
                cerr << "Incorrect option" << endl;
                pause(); // Pause to allow the user to see the error message.
            }
        }

    } while (blnContinue && !isDefeat(arrGame, intRows, intCols) && !isVictory(arrGame, intRows, intCols));

    printWorld(arrGame, intRows, intCols); // Display the final state of the game board.

    // Output the result based on the game's outcome.
    if (isDefeat(arrGame, intRows, intCols))
        cout << "YOU LOSE!";
    else if (isVictory(arrGame, intRows, intCols))
        cout << "YOU WIN!";

    // Free up dynamically allocated memory.
    dealloc(arrGame, intRows);

    return 0; // End the program successfully.
}
