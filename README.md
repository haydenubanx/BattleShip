# Battleship Game Simulation

## Overview

This project simulates a game of Battleship where the player attempts to hit ships placed randomly on a 25x25 grid. The player enters X and Y coordinates, and the game checks whether the shot hits or misses a ship. The game continues until all ships are sunk or the player chooses to quit.

## Features

- **Randomized Ship Placement**: Ships are placed randomly on a 25x25 grid.
- **User Interaction**: The user inputs X and Y coordinates to take shots on the grid.
- **Game Feedback**: The game informs the player if they hit or missed a ship. If a ship has already been hit in the same position, the game warns the player.
- **Map Display**: The player can view their guesses by entering `0 0` as coordinates.
- **Quit Option**: The player can quit the game by entering `-1` as a coordinate.
- **Endgame Condition**: The game continues until all ships are sunk.

## Getting Started

### Prerequisites

To run the project, you'll need:
- A C++ compiler (e.g., g++, clang++).
- A terminal or command line environment to compile and run the program.

### Running the Game

1. Clone or download the repository to your local machine.
2. Compile the source code using a C++ compiler. For example:
   ```bash
   g++ battleship.cpp -o battleship
3. Run the executable ./battleship
### Game Instructions

- Enter X and Y coordinates (between 1 and 25) to take a shot on the grid.
- The grid is 25x25, and ships are placed randomly at the start of the game.
- To display your current guesses, enter `0 0`.
- To quit the game at any time, enter `-1` for either the X or Y coordinate.

### Example Input:

```plaintext
Enter X and Y Coordinates (-1 to quit): 12 5
HIT!
```
## Folder Structure

```bash
BattleshipGame/
│
├── BattleshipMaps/           # Folder containing pre-generated maps for the game
│   ├── BattleMap1.txt
│   ├── BattleMap2.txt
│   └── ...
├── battleship.cpp            # Main game source code
└── README.md                 # This file
```

## Code Structure

- **`main()`**: Initializes the game, loads the ship map, and runs the main game loop. It prompts the player for input and manages game termination.
- **`fire()`**: Checks if the entered coordinates hit or miss a ship and updates the map accordingly.
- **`updateShipDetails()`**: Initializes ship details from the map and tracks ship positions.
- **`fleetSunk()`**: Checks if all ships have been sunk and prints the final game board if so.

## How to Add Custom Ship Maps

- You can create custom ship maps in the `BattleshipMaps/` directory. Ensure that the maps:
    - Are 25x25 grids.
    - Use `#` to represent ship positions and `~` to represent water.

## Future Improvements

- Add powerups for special abilities.
- Implement different levels of difficulty with varying grid sizes.
- Enhance the visual representation of the grid for better readability.

## License

This project is open source under the [MIT License](LICENSE).

