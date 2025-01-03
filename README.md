# Dangerous-Terrain-Game
This turn-based game simulates navigating a minefield with obstacles, where the player aims to reach the top of a grid without stepping on mines or running out of energy. This project introduces dynamic 2D arrays and gameplay mechanics.

## Features
- Randomly generated game grid with mines, obstacles, and energy items.
- Movement controls to navigate the grid.
- Victory and defeat conditions based on energy level and mine collision.
- Encapsulated in the `TerrainSpace` namespace.

## How to Win 
- Reach the rigth most coloumn without depleteing your energy or hitting a mine

## How to lose 
- Deplete your energy without reaching the required coloumn
- Hit a mine 

## How to Run
1. Clone the repository: `git clone https://github.com/1brah1m-aba512/Dangerous-Terrain-Game.git`
2. Navigate to the directory: `cd Dangerous-Terrain-Game`
3. Compile the program: `g++ *.cpp -o <numRows> <numCols> <numObstacles> <numMines> <numEnergy> Dangerous-Terrain-Game `
4. Run the program: `./Dangerous-Terrain-Game`

## Future Improvements
- Add difficulty levels with adjustable mine density.
- Include a graphical interface for the game.
