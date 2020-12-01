/*
Anthony Thompson
Due Nov 30 23:59
Lab 7: Battleship
Make a Simple Battleship game.
*/

#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

// Resets all boards
void board_reset();
// Menu
char menu_select(int scoreboard[2]);
// Prints boards to console
void print_board(int board_number);
// Place ships onto their appropriate boards
void ship_set(bool player);
// Verifies valid ship placement
bool ship_validate(int x_coor, int y_coor, int direction, int ship_length, bool player);
// Gameplay
bool gameplay();
// Fire a shot
bool fire(bool player);
// Validate firing coordinates
char fire_validate(int x_coor, int y_coor, bool player, int board, char hit_miss);
// Receiving inputs
void receive_input(int& x_coor, int& y_coor, int& direction, bool player, bool valid_input, bool set_fire, int ship_length);
// Select the appropriate board
void select_board(bool set_fire, int& board, bool player);
// Check if coordinates are inbounds
bool inbounds(int x_coor, int y_coor);
/*
Declaring array to hold boards
[4] board: 0 - player ship board. 1 - player fire board. 2 - computer ship board. 3 - computer fire board.
[10] x axis
[10] y axis
*/
char battleship_array[4][10][10];

int main()
{
	// variable to tell function which board to print
	int board_number;
	// Array for scorekeeping [0] = Player wins, [1] = Player losses
	int scoreboard[2];
	// Option selected in menu
	char menu_option;

	// Initializing scoreboard
	scoreboard[0] = 0;
	scoreboard[1] = 0;

	// Initiallizing randomization
	srand(time(NULL));

	// Clearing the array
	board_reset();

	cout << "Welcome to battleship.\n";
	do
	{
		// Select an option from the menu
		menu_option = menu_select(scoreboard);

		switch (menu_option)
		{
		case 'N':
			// Iterate through one game
			if (gameplay())
			{
				// If player wins
				scoreboard[0]++;
			}
			else
			{
				// If player loses
				scoreboard[1]++;
			}
			break;
		case 'S':
			// Clear screen
			system("CLS");

			// Show scoreboard
			cout << "wins: " << scoreboard[0] << "losses: " << scoreboard[1] << endl;
			break;
		case 'B':
			for (board_number = 0; board_number < 4; board_number++)
			{
				// verifying outputs
				print_board(board_number);
			}
			break;
		case 'E':
			// Close the program
			return 0;
			break;
		default: cout << "The option you have chosen is invalid. Please try again.";
			break;
		}
	} while (menu_option != 'E');
}

void board_reset()
{
	// Loop through each board
	for (int board = 0; board < 4; board++)
	{
		// Loop through each row
		for (int y_axis = 0; y_axis < 10; y_axis++)
		{
			// Loop through each column
			for (int x_axis = 0; x_axis < 10; x_axis++)
			{
				// Place a water indicator in the array location
				battleship_array[board][x_axis][y_axis] = '~';
			}
		}
	}
}

char menu_select(int scoreboard[2])
{
	char menu_option;
	cout << "Please select an option from the Menu Below : \n";
	cout << "(N): Play through one Game of Battleship.\n";
	cout << "(S): Show the scoreboard.\n";
	if (scoreboard[0] > scoreboard[1])
	{
		cout << "(B): Show all boards for previous game.\n";
		cout << "(E): Exit the game.\n";
	}
	else
	{
		cout << "(E): Exit the game.\n";
	}

	cin >> menu_option;

	return menu_option;
}

void print_board(int board_number)
{
	// Declaring variable for row header
	int row_name;

	// resetting variable for row header
	row_name = 1;

	// Naming each board
	switch (board_number)
	{
	case 0: cout << "player ship array: " << endl;
		break;
	case 1: cout << "player fire array: " << endl;
		break;
	case 2: cout << "computer ship array: " << endl;
		break;
	case 3: cout << "computer fire array: " << endl;
		break;
	default: cout << "printing error" << endl;
	}

	// Printing column header
	cout << "   1 2 3 4 5 6 7 8 9 10" << endl;

	// Loop through each row
	for (int y_axis = 0; y_axis < 10; y_axis++)
	{
		// Naming row
		if (row_name != 10)
		{
			cout << row_name << "  ";
		}
		else
		{
			cout << row_name << " ";
		}
		// Looping through each column
		for (int x_axis = 0; x_axis < 10; x_axis++)
		{
			// Printing current place in the array
			cout << battleship_array[board_number][x_axis][y_axis] << " ";
		}

		// Progressing to the next row
		row_name = row_name + 1;

		// Moving to the next row of the console
		cout << endl;
	}
}

bool gameplay()
{
	int player_remaining = 17;
	int computer_remaining = 17;
	bool player;

	// Clear the board
	board_reset();

	// Place Ships on the board
	player = false;
	ship_set(player);
	player = true;
	ship_set(player);

	// Select a random player to go first
	player = rand() % 2;

	// Loop until win
	do
	{
		// fire one shot
		if (fire(player))
		{
			// tracking number of hits left
			if (player)
			{
				computer_remaining--;
			}
			else
			{
				player_remaining--;
			}
		}

		// Checking for win
		if (player_remaining <= 0)
		{
			return false;
		}
		else if (computer_remaining <= 0)
		{
			return true;
		}

		// alternate player
		if (player)
		{
			player = false;
		}
		else
		{
			player = true;
		}
	} while (player_remaining > 0 || computer_remaining > 0);

}

void receive_input(int& x_coor, int& y_coor, int& direction, bool player, bool valid_input, bool set_fire, int ship_length)
{
	// Receiving inputs
	if (!player)
	{
		// From Computer
		x_coor = rand() % 10;
		y_coor = rand() % 10;
		if (set_fire)
		{
			direction = rand() % 4 + 1;
		}
	}
	else
	{
		// Only print board if input is valid
		if (valid_input)
		{
			// Clear screen
			system("CLS");
			if (set_fire)
			{
				print_board(0);
			}
			else
			{
				print_board(0);
				print_board(1);
			}
		}

		// From User
		if (set_fire)
		{
			/*
			// Code for automating player inputs.
			x_coor = rand() % 10 + 1;
			y_coor = rand() % 10 + 1;
			direction = rand() % 4 + 1;
			system("PAUSE");
			/*/
			cout << "Please choose the coordinates on which you would like to place your Ship (length: " << ship_length << ")\n(Vertical Horizontal [1=up,2=down,3=left,4=right]\n";
			cin >> y_coor >> x_coor >> direction;
			//*/
		}
		else
		{
			/*
			// Code for automating player inputs.
			x_coor = rand() % 10 + 1;
			y_coor = rand() % 10 + 1;
			system("PAUSE");
			/*/
			cout << "Please choose which coordinates you would like to fire upon.\n";
			cin >> y_coor >> x_coor;
			//*/
		}

		// Adjust user inputs to work with array
		x_coor = x_coor - 1;
		y_coor = y_coor - 1;
	}

}

void select_board(bool set_fire, int& board, bool player)
{
	if (player)
	{
		if (set_fire)
		{
			// Player ship board
			board = 0;
		}
		else
		{
			// Computer ship board
			board = 2;
		}
	}
	else
	{
		if (set_fire)
		{
			// Computer ship board
			board = 2;
		}
		else
		{
			// Player ship board
			board = 0;
		}
	}
}

void ship_set(bool player)
{
	// X coordinate
	int x_coor;
	// Y coordinate
	int y_coor;
	// Desired direction. 1 = up, 2 = down, 3 = left, 4 = right
	int direction;
	// Error checking flag
	bool valid_input = true;
	// Length of ship being placed
	int ship_length = 2;
	// flag for second 3 length ship
	bool repeat = false;

	bool set_fire = true;

	int board_number = 0;

	do
	{
		do
		{
			receive_input(x_coor, y_coor, direction, player, valid_input, set_fire, ship_length);
			// 
			valid_input = true;

			// Verify desired location and direction are valid			
			if (!ship_validate(x_coor, y_coor, direction, ship_length, player))
			{
				valid_input = false;
			}

		// Loop until valid inputs are given
		} while (valid_input == false);

		// Run loop an extra time to place the second 3 length ship
		if (ship_length == 3)
		{
			if (repeat == false)
			{
				repeat = true;
			}
			else
			{
				ship_length++;
				repeat = false;
			}
		}
		else
		{
			ship_length++;
		}
		// Loop until all ships have been placed
	} while (ship_length <= 5);

	// Print the finalized board for the player
	if (player)
	{
		system("CLS");
		print_board(0);
		system("PAUSE");
	}
}

bool ship_validate(int x_coor, int y_coor, int direction, int ship_length, bool player)
{
	int end_x;
	int end_y;
	int dir_x = 0;
	int dir_y = 0;
	int board;
	bool redundant = false;
	bool set_fire = true;

	// Adjusting ship length to workable length
	ship_length = ship_length - 1;

	select_board(set_fire, board, player);

	// Verifying Starting coordinates are within bounds
	if (!inbounds(x_coor, y_coor))
	{
		if (player)
		{
			cout << "Selected coordinates are out of bounds. Vertical axis must only be numbers 1-10. Horizontal axis must only be numbers 1-10";
		}
		return false;
	}

	// verifying proper directional input and setting x/y axis movement
	switch (direction)
	{
	case 1: dir_y = -1;
		break;
	case 2: dir_y = 1;
		break;
	case 3: dir_x = -1;
		break;
	case 4: dir_x = 1;
		break;
	default:
		// Error message for player
		if (player)
		{
			cout << "The direction you have chosen is invalid. Please choose a value between 1 and 4.\n";
		}
		return false;
		break;
	}

	// Calculating ending coordinates
	end_x = x_coor + (dir_x * ship_length);
	end_y = y_coor + (dir_y * ship_length);
	
	// Adjusting axial movement so that loops work as intended
	if (dir_x == 0)
	{
		dir_x = 1;
	}
	if (dir_y == 0)
	{
		dir_y = 1;
	}
	
	// Verify that ending coordinates are within bounds
	if (inbounds(end_x, end_y))
	{
		// Check for overlap
		// Loop axially based on dir_x
		for (int x = x_coor; x != end_x + dir_x; x = x + dir_x)
		{
			// Loop axially based on dir_y
			for (int y = y_coor; y != end_y + dir_y; y = y + dir_y)
			{
				// Check to see if the ship will be placed on water
				if (battleship_array[board][x][y] != '~')
				{
					if (player)
					{
						cout << "You are attempting to place a ship on top of another ship. Please try again.";
					}
					return false;
				}
			}
		}
	}
	else
	{
		return false;
		if (player)
		{
			cout << "You are attempting to place a ship off of the board. Please Reevaluate and try again.\n";
		}
	}
	// Place ship in the array

	// Loop axially based on dir_x
	for (int x = x_coor; x != end_x + dir_x; x = x + dir_x)
	{
		// Loop axially baed on dir_y
		for (int y = y_coor; y != end_y + dir_y; y = y + dir_y)
		{
			// Place ship in the array
			battleship_array[board][x][y] = '#';
		}
	}

	return true;
}

bool fire(bool player)
{
	char hit_miss = 'E';
	int board;
	bool valid_input = true;
	int x_coor;
	int y_coor;
	bool set_fire = false;
	int direction;
	int ship_length = 0;

	// Loop until valid inputs are received
	do
	{
		// recieve inputs
		receive_input(x_coor, y_coor, direction, player, valid_input, set_fire, ship_length);

		// Select appropriate board
		select_board(set_fire, board, player);

		// check for hit, miss, or invalidity
		hit_miss = fire_validate(x_coor, y_coor, player, board, hit_miss);

		// error flag
		if (hit_miss == 'E')
		{
			valid_input = false;
		}
	} while (!valid_input);

	// Place marker
	if (hit_miss != 'E')
	{
		// place marker onto ship board
		battleship_array[board][x_coor][y_coor] = hit_miss;

		// select opposing firing board
		board = board + 3;
		if (board > 3)
		{
			board = board - 4;
		}

		// place marker onto firing board
		battleship_array[board][x_coor][y_coor] = hit_miss;

		// return whether the shot hit or missed
		if (hit_miss == 'H')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

char fire_validate(int x_coor, int y_coor, bool player, int board, char hit_miss)
{
	bool set_fire = false;

	if (player)
	{
		// Verifying Firing coordinates are within bounds
		if (!inbounds(x_coor, y_coor))
		{
			// Error message for the player
			if (player)
			{
				cout << "Selected coordinates are out of bounds. Vertical axis must only be numbers 1-10. Horizontal axis must only be numbers 1-10";
			}
			return hit_miss;
		}
	}

	// check array
	switch (battleship_array[board][x_coor][y_coor])
	{
	case '~':
		hit_miss = 'M';
		break;
	case '#':
		hit_miss = 'H';
		break;
	case 'H':
		// Error message for player
		if (player)
		{
			cout << "You have already fired on this position. Please select another coordinate.\n";
		}
		return 'E';
		break;
	case 'M':
		// Error message for player
		if (player)
		{
			cout << "You have already fired on this position. Please select another coordinate.\n";
		}
		return 'E';
		break;
	default: cout << "Error on validate.";
		break;
	}

	return hit_miss;
}

bool inbounds(int x_coor, int y_coor)
{
	// Verify given coordinates are within bounds
	if (x_coor >= 0 && x_coor <= 9 && y_coor >= 0 && y_coor <= 9)
	{
		return true;
	}
	else
	{
		return false;
	}
}
