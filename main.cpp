/*
Anthony Thompson
Due Nov 30 23:59
Lab 7: Battleship
Make a Simple Battleship game.
*/

#include <iostream>
#include <time.h>

using namespace std;

// Resets all boards
void board_reset(char battleship_array[4][10][10]);
// Prints boards to console
void print_board(char battleship_array[4][10][10]);
// Place ships onto their appropriate boards
void ship_set(char battleship_array[4][10][10], bool player);
// Verifies valid ship placement
void ship_validate(char battleship_array[4][10][10], int x_coor, int y_coor, int direction, bool& valid_input, int ship_length, bool player);
// Places ship inside the array
void place_ship(char battleship_array[4][10][10], int x_coor, int y_coor, bool player, int ship_length, int direction);

int main()
{
	srand(time(NULL));
	// Declaring array to hold boards
	char battleship_array[4][10][10];
	// Clearing the array
	board_reset(battleship_array);


	bool player = false;
	ship_set(battleship_array, player);

	// verifying outputs
	print_board(battleship_array);

	return 0;
}

void board_reset(char battleship_array[4][10][10])
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

void print_board(char battleship_array[4][10][10])
{
	// Declaring variable for row header
	char row_name;
	// Loop through each board
	for (int board = 0; board < 4; board++)
	{
		// resetting variable for row header
		row_name = 'A';
		// Naming each board
		switch (board)
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
		cout << "  1 2 3 4 5 6 7 8 9 10" << endl;
		// Loop through each row
		for (int y_axis = 0; y_axis < 10; y_axis++)
		{
			// Naming row
			cout << row_name << " ";
			// Looping through each column
			for (int x_axis = 0; x_axis < 10; x_axis++)
			{
				// Printing current place in the array
				cout << battleship_array[board][x_axis][y_axis] << " ";
			}
			// Progressing to the next letter of the alphabet
			row_name = char(row_name + 1);
			// Moving to the next row of the console
			cout << endl;
		}
	}
}

void ship_set(char battleship_array[4][10][10], bool player)
{
	// X coordinate
	int x_coor;
	// Y coordinate
	int y_coor;
	// Desired direction
	int direction;
	// Error checking flag
	bool valid_input = false;
	// Length of ship being placed
	int ship_length = 2;
	// flag for second 3 length ship
	bool repeat = false;

	do
	{
		do
		{
			if (player == false)
			{
				x_coor = rand() % 10;
				y_coor = rand() % 10;
				direction = rand() % 4 + 1;
			}
			else
			{
				cout << "Please choose the coordinates on which you would like to place your Ship (length: " << ship_length << ")\n(Horizontal Vertical [1=up,2=down,3=left,4=right]\n";

				cin >> x_coor >> y_coor >> direction;

				x_coor = x_coor - 1;

				y_coor = y_coor - 1;
			}

			ship_validate(battleship_array, x_coor, y_coor, direction, valid_input, ship_length, player);
		} while (valid_input == false);

		place_ship(battleship_array, x_coor, y_coor, player, ship_length, direction);

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
	} while (ship_length != 6);
}

void ship_validate(char battleship_array[4][10][10], int x_coor, int y_coor, int direction, bool& valid_input, int ship_length, bool player)
{
	int end_x;
	int end_y;
	int dir_x = 0;
	int dir_y = 0;
	int board;

	ship_length = ship_length - 1;

	if (player)
	{
		board = 0;
	}
	else
	{
		board = 2;
	}

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
	default: valid_input = false;
		break;
	}

	end_x = x_coor + (dir_x * ship_length);
	end_y = y_coor + (dir_y * ship_length);
	
	if (dir_x == 0)
	{
		dir_x = 1;
	}
	if (dir_y == 0)
	{
		dir_y = 1;
	}
	
	if (0 <= end_x <= 9 && 0 <= end_y <= 9)
	{
		for (int x = x_coor; x != end_x + dir_x; x = x + dir_x)
		{
			for (int y = y_coor; y != end_y + dir_y; y = y + dir_y)
			{
				if (battleship_array[board][x][y] != '~')
					valid_input = false;
			}
		}
	}
	else
	{
		valid_input = true;
	}
}

void place_ship(char battleship_array[4][10][10], int x_coor, int y_coor, bool player, int ship_length, int direction)
{
	int board;
	int end_x;
	int end_y;
	int dir_x = 0;
	int dir_y = 0;

	if (player == true)
	{
		board = 0;
	}
	else
	{
		board = 2;
	}

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
	}

	end_x = x_coor + (dir_x * ship_length);
	end_y = y_coor + (dir_y * ship_length);
	
	if (dir_x == 0)
	{
		dir_x = 1;
	}
	if (dir_y == 0)
	{
		dir_y = 1;
	}
	
	if (0 <= end_x <= 9 && 0 <= end_y <= 9)
	{
		for (int x = x_coor; x != end_x + dir_x; x = x + dir_x)
		{
			for (int y = y_coor; y != end_y + dir_y; y = y + dir_y)
			{
				battleship_array[board][x][y] = '#';
			}
		}
	}
}