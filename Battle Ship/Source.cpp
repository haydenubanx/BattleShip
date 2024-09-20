//battleShip -- This file simulates a game of battleship using X and Y coordinate inputs from the user 
//and checking them against a 25 x 25 grid of ships to determine hits.
//In the end the grid from the game will be printed for the user to see
//CSIS 111-B02 
//<Sources if necessary>

//Include statements
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
using namespace std;

//Global declarations: Constants and type definitions only -- no variables
const int NUM_ROWS = 25;
const int NUM_COLUMNS = 25;

//struct for ship info
struct shipType
{
	int length = 0;
	int hitCount = 0;
	bool hitBefore = false;
	bool sunk = false;
	string shipMember[NUM_ROWS][NUM_COLUMNS];
}ship1, ship2, ship3, ship4, ship5, ship6, ship7;


//Function prototypes
void updateShipDetails(char shMap[][NUM_COLUMNS], bool posChecked[][NUM_COLUMNS], bool shipTrack1[][NUM_COLUMNS], bool shipTrack2[][NUM_COLUMNS],
	bool shipTrack3[][NUM_COLUMNS], bool shipTrack4[][NUM_COLUMNS], bool shipTrack5[][NUM_COLUMNS], bool shipTrack6[][NUM_COLUMNS],
	bool shipTrack7[][NUM_COLUMNS]);

void fire(int xCoordinate, int yCoordinate, char sMap[][NUM_COLUMNS], char sMapBlank[][NUM_COLUMNS], bool shipTra1[][NUM_COLUMNS],
	bool shipTra2[][NUM_COLUMNS], bool shipTra3[][NUM_COLUMNS], bool shipTra4[][NUM_COLUMNS], bool shipTra5[][NUM_COLUMNS],
	bool shipTra6[][NUM_COLUMNS], bool shipTra7[][NUM_COLUMNS]);

void fleetSunk(char shipM[][NUM_COLUMNS], bool& allsunk);



int main()
{
	//In cout statement below SUBSTITUTE your name and lab number
	cout << "Hayden Eubanks -- Lab 8" << endl << endl;

	//Variable declarations

	//Array to store the ship map and hits
	char shipMap[NUM_ROWS][NUM_COLUMNS];

	//Blank ship map to show guesses
	char shipMapBlank[NUM_ROWS][NUM_COLUMNS];

	//Array to store when a position has been checked
	bool positionAlreadyChecked[NUM_ROWS][NUM_COLUMNS];

	//Arrays to track which position on the grid belongs to which ships
	bool shipTracker1[NUM_ROWS][NUM_COLUMNS];
	bool shipTracker2[NUM_ROWS][NUM_COLUMNS];
	bool shipTracker3[NUM_ROWS][NUM_COLUMNS];
	bool shipTracker4[NUM_ROWS][NUM_COLUMNS];
	bool shipTracker5[NUM_ROWS][NUM_COLUMNS];
	bool shipTracker6[NUM_ROWS][NUM_COLUMNS];
	bool shipTracker7[NUM_ROWS][NUM_COLUMNS];

	//Bool to check if all of the ships have been sunk
	bool allSunkCheck = false;
	//Variables for x and y coordinates
	int xCord = 0;
	int yCord = 0;

	string fileName;
	ifstream inFile;

	//Program logic

	//User Instructions for the program
	cout << "Welcome to Battle Ship!" << endl;
	cout << "To use this program, enter an X and Y coordinate for a 25x25 grid to see if you hit a ship." << endl;
	cout << "Example: 20 19" << endl;
	cout << "The program will let you know if you hit, missed, or hit again as well as when all of the ships are sunk." << endl;
	cout << "To see a current map of your guesses enter 0 0 for your x and y coordinates." << endl << endl;

	//Asks which file the user would like to use
	cout << "Enter file Name of battle map file to begin (example: file.txt)." << endl;
	cout << "Files uploaded should be txt files with no more than 7 ships of a max length of 5." << endl << endl;
	cout << "File Name: ";
	cin >> fileName;
	cout << endl << endl;

	//initialize all positions to unchecked and unassigned to ships
	for (int k = 0; k < 25; k++)
	{
		for (int l = 0; l < 25; l++)
		{
			positionAlreadyChecked[k][l] = false;
			shipTracker1[k][l] = false;
			shipTracker2[k][l] = false;
			shipTracker3[k][l] = false;
			shipTracker4[k][l] = false;
			shipTracker5[k][l] = false;
			shipTracker6[k][l] = false;
			shipTracker7[k][l] = false;
		}

	}
	
	//Open file and loop through each row and column to import grid
	inFile.open(fileName);
	for (int g = 0; g < 25; g++)
	{
		for (int h = 0; h < 25; h++)
		{
			inFile >> shipMap[g][h];
			shipMapBlank[g][h] = '~';
		}
	}

	//Function to update ship info for data in file
	updateShipDetails(shipMap, positionAlreadyChecked, shipTracker1, shipTracker2, shipTracker3, shipTracker4,shipTracker5,
		shipTracker6, shipTracker7);

	//While there are still ships to be sunk, continue looping through asking for coordinates
	while (allSunkCheck != true)
	{

		//Prompts User for X and Y coordinates
		cout << "X and Y Coordinates: ";
		cin >> xCord >> yCord;

		//Alligns user input with the zero indexed array so guess "1 1" is the first position and "25 25" is the last
		xCord = xCord - 1;
		yCord = yCord - 1;
		cout << endl << endl;

		//Function to see if the coordinates input are a hit, miss, hit again, or repeat
		fire(xCord, yCord, shipMap, shipMapBlank, shipTracker1, shipTracker2, shipTracker3, shipTracker4, shipTracker5,
			shipTracker6, shipTracker7);

		//Funciton to see if all of the ships are sunk and if so prints the final game board
		fleetSunk(shipMap, allSunkCheck);
	}

	//Closing program statements
	system("pause");
	return 0;
}

//Function definitions

//Function to update information for the ships
void updateShipDetails(char shMap[][NUM_COLUMNS], bool posChecked[][NUM_COLUMNS], bool shipTrack1[][NUM_COLUMNS], bool shipTrack2[][NUM_COLUMNS],
bool shipTrack3[][NUM_COLUMNS], bool shipTrack4[][NUM_COLUMNS], bool shipTrack5[][NUM_COLUMNS], bool shipTrack6[][NUM_COLUMNS],
bool shipTrack7[][NUM_COLUMNS])
{
	//Loops through the grid and for each position assigns corisponding ship, ship length, and position
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			//Updates ship struct to gather info of ship
			if (shMap[i][j] == '#' && posChecked[i][j] == false)
			{
				//If no info for ship 1, start gathering data for ship 1
				if (ship1.length == 0)
				{
					ship1.length++;
					shipTrack1[i][j] = true;
					posChecked[i][j] = true;

					//Check spaces around this one to continue assigning to the same ship
					for (int p = 1; p <= 5; p++)
					{
						//Check spaces directly below this location up to 5 spaces below
						if (shMap[i + p][j] == '#')
						{
							ship1.length++;
							shipTrack1[i + p][j] = true;
							posChecked[i + p][j] = true;
						}
						//Check spaces to right of this position up to 5 spaces away
						if (shMap[i][j + p] == '#')
						{
							ship1.length++;
							shipTrack1[i][j + p] = true;
							posChecked[i][j + p] = true;
						}
					}
				}
				//If no info for ship 2, start gathering data for ship 2
				else if (ship2.length == 0)
				{
					ship2.length++;
					shipTrack2[i][j] = true;
					posChecked[i][j] = true;

					//Check spaces around this one
					for (int p = 1; p <= 5; p++)
					{
						//Check spaces directly below this location up to 5 spaces below
						if (shMap[i + p][j] == '#')
						{
							ship2.length++;
							shipTrack2[i + p][j] = true;
							posChecked[i + p][j] = true;
						}
						//Check spaces to right of this position up to 5 spaces away
						if (shMap[i][j + p] == '#')
						{
							ship2.length++;
							shipTrack2[i][j + p] = true;
							posChecked[i][j + p] = true;
						}
					}
				}
				//If no info for ship 3, start gathering data for ship 3
				else if (ship3.length == 0)
				{
					ship3.length++;
					shipTrack3[i][j] = true;
					posChecked[i][j] = true;

					//Check spaces around this one
					for (int p = 1; p <= 5; p++)
					{
						//Check spaces directly below this location up to 5 spaces below
						if (shMap[i + p][j] == '#')
						{
							ship3.length++;
							shipTrack3[i + p][j] = true;
							posChecked[i + p][j] = true;
						}
						//Check spaces to right of this position up to 5 spaces away
						if (shMap[i][j + p] == '#')
						{
							ship3.length++;
							shipTrack3[i][j + p] = true;
							posChecked[i][j + p] = true;
						}
					}
				}

				//If no info for ship 4, start gathering data for ship 4
				else if (ship4.length == 0)
				{
					ship4.length++;
					shipTrack4[i][j] = true;
					posChecked[i][j] = true;

					//Check spaces around this one
					for (int p = 1; p <= 5; p++)
					{
						//Check spaces directly below this location up to 5 spaces below
						if (shMap[i + p][j] == '#')
						{
							ship4.length++;
							shipTrack4[i + p][j] = true;
							posChecked[i + p][j] = true;
						}
						//Check spaces to right of this position up to 5 spaces away
						if (shMap[i][j + p] == '#')
						{
							ship4.length++;
							shipTrack4[i][j + p] = true;
							posChecked[i][j + p] = true;
						}
					}
				}
				//If no info for ship 5, start gathering data for ship 5
				else if (ship5.length == 0)
				{
					ship5.length++;
					shipTrack5[i][j] = true;
					posChecked[i][j] = true;

					//Check spaces around this one
					for (int p = 1; p <= 5; p++)
					{
						//Check spaces directly below this location up to 5 spaces below
						if (shMap[i + p][j] == '#')
						{
							ship5.length++;
							shipTrack5[i + p][j] = true;
							posChecked[i + p][j] = true;
						}
						//Check spaces to right of this position up to 5 spaces away
						if (shMap[i][j + p] == '#')
						{
							ship5.length++;
							shipTrack5[i][j + p] = true;
							posChecked[i][j + p] = true;
						}
					}
				}

				//If no info for ship 6, start gathering data for ship 6
				else if (ship6.length == 0)
				{
					ship6.length++;
					shipTrack6[i][j] = true;
					posChecked[i][j] = true;

					//Check spaces around this one
					for (int p = 1; p <= 5; p++)
					{
						//Check spaces directly below this location up to 5 spaces below
						if (shMap[i + p][j] == '#')
						{
							ship6.length++;
							shipTrack6[i + p][j] = true;
							posChecked[i + p][j] = true;
						}

						//Check spaces to right of this position up to 5 spaces away
						if (shMap[i][j + p] == '#')
						{
							ship6.length++;
							shipTrack6[i][j + p] = true;
							posChecked[i][j + p] = true;
						}
					}
				}

				//If no info for ship 7, start gathering data for ship 7
				else if (ship7.length == 0)
				{
					ship7.length++;
					shipTrack7[i][j] = true;
					posChecked[i][j] = true;

					//Check spaces around this one
					for (int p = 1; p <= 5; p++)
					{
						//Check spaces directly below this location up to 5 spaces below
						if (shMap[i + p][j] == '#')
						{
							ship7.length++;
							shipTrack7[i + p][j] = true;
							posChecked[i + p][j] = true;
						}
						//Check spaces to right of this position up to 5 spaces away
						if (shMap[i][j + p] == '#')
						{
							ship7.length++;
							shipTrack7[i][j + p] = true;
							posChecked[i][j + p] = true;
						}
					}
				}
			}
		}
	}
}


//Function to take in x and y coordinates and see if they hit a ship
void fire(int xCoordinate, int yCoordinate, char sMap[][NUM_COLUMNS], char sMapBlank[][NUM_COLUMNS], bool shipTra1[][NUM_COLUMNS], 
	bool shipTra2[][NUM_COLUMNS], bool shipTra3[][NUM_COLUMNS],bool shipTra4[][NUM_COLUMNS],bool shipTra5[][NUM_COLUMNS],
	bool shipTra6[][NUM_COLUMNS], bool shipTra7[][NUM_COLUMNS])
{
	//If user input is "0 0" prints current map of guesses (-1 because of arrray's 0 indexing)
	if (xCoordinate == -1 && yCoordinate == -1)
	{
		for (int w = 0; w < 25; w++)
		{
			for (int z = 0; z < 25; z++)
			{
				cout << sMapBlank[w][z];
			}
			cout << endl;
		}
	}
 
	

	//Checks for hits
	if (sMap[xCoordinate][yCoordinate] == '#')
	{
		
		//Checks if ship has been hit before and if so prints hit again message
		if (ship1.hitBefore == true && shipTra1[xCoordinate][yCoordinate] == true)
		{
			//Updates both the final map and the current guesses map
			sMap[xCoordinate][yCoordinate] = 'H';
			sMapBlank[xCoordinate][yCoordinate] = 'H';
			cout << "HIT AGAIN ";

			//Updates the number of times this ship has been hit
			ship1.hitCount++;

			//If the ship has been hit as many times as it is long, the ship is sunk and the sunk message is printed
			if (ship1.hitCount == ship1.length)
			{						
				cout << "AND SUNK!";
				ship1.sunk = true;
			}

		}

		//Repeat hit check for ship 2
		else if (ship2.hitBefore == true && shipTra2[xCoordinate][yCoordinate] == true)
		{
			sMap[xCoordinate][yCoordinate] = 'H';
			sMapBlank[xCoordinate][yCoordinate] = 'H';
			cout << "HIT AGAIN ";

			//Updates the number of times this ship has been hit
			ship2.hitCount++;

			if (ship2.hitCount == ship2.length)
			{
				cout << "AND SUNK!";
				ship2.sunk = true;
			}
		
		}

		//Repeat hit check for ship 3
		else if (ship3.hitBefore == true && shipTra3[xCoordinate][yCoordinate] == true)
		{
			sMap[xCoordinate][yCoordinate] = 'H';
			sMapBlank[xCoordinate][yCoordinate] = 'H';
			cout << "HIT AGAIN ";

			//Updates the number of times this ship has been hit
			ship3.hitCount++;

			if (ship3.hitCount == ship3.length)
			{
				cout << "AND SUNK!";
				ship3.sunk = true;
			}
			
		}

		//Repeat hit check for ship 4
		else if (ship4.hitBefore == true && shipTra4[xCoordinate][yCoordinate] == true)
		{
			sMap[xCoordinate][yCoordinate] = 'H';
			sMapBlank[xCoordinate][yCoordinate] = 'H';
			cout << "HIT AGAIN ";

			//Updates the number of times this ship has been hit
			ship4.hitCount++;

			if (ship4.hitCount == ship4.length)
			{
				cout << "AND SUNK!";
				ship4.sunk = true;
			}
			
		}

		//Repeat hit check for ship 5
		else if (ship5.hitBefore == true && shipTra5[xCoordinate][yCoordinate] == true)
		{
			sMap[xCoordinate][yCoordinate] = 'H';
			sMapBlank[xCoordinate][yCoordinate] = 'H';
			cout << "HIT AGAIN ";

			//Updates the number of times this ship has been hit
			ship5.hitCount++;

			if (ship5.hitCount == ship5.length)
			{
				cout << "AND SUNK!";
				ship5.sunk = true;
			}
			
		}

		//Repeat hit check for ship 6
		else if (ship6.hitBefore == true && shipTra6[xCoordinate][yCoordinate] == true)
		{
			sMap[xCoordinate][yCoordinate] = 'H';
			sMapBlank[xCoordinate][yCoordinate] = 'H';
			cout << "HIT AGAIN ";

			//Updates the number of times this ship has been hit
			ship6.hitCount++;

			if (ship6.hitCount == ship6.length)
			{
				cout << "AND SUNK!";
				ship6.sunk = true;
			}
		}

		//Repeat hit check for ship 7
		else if (ship7.hitBefore == true && shipTra7[xCoordinate][yCoordinate] == true)
		{
			sMap[xCoordinate][yCoordinate] = 'H';
			sMapBlank[xCoordinate][yCoordinate] = 'H';
			cout << "HIT AGAIN ";

			//Updates the number of times this ship has been hit
			ship7.hitCount++;

			if (ship7.hitCount == ship7.length)
			{
				cout << "AND SUNK!";
				ship7.sunk = true;
			}
		}


		//Prints hit message if this is the first time this ship has been hit
		else
		{
			//Updates both the endgame grid and the current guesses grid
			sMap[xCoordinate][yCoordinate] = 'H';
			sMapBlank[xCoordinate][yCoordinate] = 'H';
			cout << "HIT";

			//If this is the first time this ship has been hit, mark it as having been hit and update hit count
			if (ship1.hitCount == 0 && shipTra1[xCoordinate][yCoordinate] == true)
			{
				ship1.hitBefore = true;
				ship1.hitCount++;
			}
			else if (ship2.hitCount == 0 && shipTra2[xCoordinate][yCoordinate] == true)
			{
				ship2.hitBefore = true;
				ship2.hitCount++;
			}
			else if (ship3.hitCount == 0 && shipTra3[xCoordinate][yCoordinate] == true)
			{
				ship3.hitBefore = true;
				ship3.hitCount++;
			}
			else if (ship4.hitCount == 0 && shipTra4[xCoordinate][yCoordinate] == true)
			{
				ship4.hitBefore = true;
				ship4.hitCount++;
			}
			else if (ship5.hitCount == 0 && shipTra5[xCoordinate][yCoordinate] == true)
			{
				ship5.hitBefore = true;
				ship5.hitCount++;
			}
			else if (ship6.hitCount == 0 && shipTra6[xCoordinate][yCoordinate] == true)
			{
				ship6.hitBefore = true;
				ship6.hitCount++;
			}
			else if (ship7.hitCount == 0 && shipTra7[xCoordinate][yCoordinate] == true)
			{
				ship7.hitBefore = true;
				ship7.hitCount++;
			}
		}
	}

	//Checks for miss but only prints if coordinate is inbounds
	else if (sMap[xCoordinate][yCoordinate] == '~' && xCoordinate >= 0 && xCoordinate < 25 && yCoordinate >= 0 
	&& yCoordinate < 25)
	{
		//Prints 'M' if coordinates entered miss on both maps and miss message
		sMap[xCoordinate][yCoordinate] = 'M';
		sMapBlank[xCoordinate][yCoordinate] = 'M';
		cout << "MISS";
	}

	//Print message if you guess a missed space again
	else if (sMap[xCoordinate][yCoordinate] == 'M')
	{
		cout << "Already Missed here";
	}

	//Print message if you guess a hit space again
	else if (sMap[xCoordinate][yCoordinate] == 'H')
	{
		cout << "Already Hit here";
	}

	cout << endl << endl;
}

//Function to check if all of the ships have been sunk and then print final game board
void fleetSunk(char shipM[][NUM_COLUMNS], bool& allsunk)
{
	//Checks to see if all of teh ships have been sunk
	if (ship1.sunk == true && ship2.sunk == true && ship3.sunk == true && ship4.sunk == true && ship5.sunk == true &&
		ship6.sunk == true && ship7.sunk == true)
	{
		//If so, sets the allSunk variable to true so the loop of the main body will no longer continue
		allsunk = true;

		//loops through the grid to print the final game board of all of your guesses
		for (int d = 0; d < 25; d++)
		{
			for (int b = 0; b < 25; b++)
			{
				cout << shipM[d][b];
			}
			cout << endl;
		}
		//Final Print Message
		cout << endl << "The fleet was destroyed!" << endl << endl;
	}
}