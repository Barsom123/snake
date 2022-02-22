#include <iostream>
#include <ctime>
#include <conio.h>
#include <Windows.h>
using namespace std;
void start();
void over();
// enum for direction of snake 
enum Direction { Top = 1, Down, Rigth, Left };

struct snake
{
	int headx, heady, tail, tail_x[50], tail_y[50]; Direction dir;
};
// struct for values of map
struct map
{
	int wigth, heigth, fruitx, fruity;
};
// struct for values of player
struct player
{
	int score, game_level, trying ; bool lose;
};
// create object from struct
map map1; snake snake1; player player1;
// Assign values to variables
void generate_frute() {
	srand(time(NULL));
	//  To make fruitx  a random number
	map1.fruitx = rand() % (map1.wigth - 2) + 1;
	// To make fruity  a random number
	map1.fruity = rand() % (map1.heigth - 2) + 1;
}
void generate_snake() {
	//  To make the head [x] number of the snake half the width of the screen
	snake1.headx = map1.wigth / 2;
	// To make the head of [x] a snake number half the heigth of the screen
	snake1.heady = map1.heigth / 2;
	snake1.tail = 0;
}
void generate_player() {
	player1.score = 0;
	player1.game_level = 1;
	player1.lose = false;
}
// setup the project values 
void setup() {
	// make screen width = 40
	map1.wigth = 40;
	// make screen heigth = 20
	map1.heigth = 20;
	// call generate_frute for set up the values
	generate_frute();
	// call generate_snake  for set up the values
	generate_snake();
	// call generate_player for set up the values
	generate_player();
}
// draw the map 
void draw() {
	system("cls");
	cout << "  the score of player   :  " << player1.score << '\n';
	cout << "  the level is          :  " << player1.game_level << '\n';
	cout << "  your attempts         :  " << player1.trying << '\n';
	cout << "  for exit press (X)    :  "  << '\n';
	cout << "  for exit the game press (g)    :  " << '\n';
	for (int i = 0; i < map1.heigth; i++) {
		for (int j = 0; j < map1.wigth; j++)
		{
			if (i == 0 || i == map1.heigth - 1)
				cout << "*";
			else if (j == 0 || j == map1.wigth - 1)
				cout << "*";
			else if (i == map1.fruity && j == map1.fruitx)
				cout << "$";
			else if (i == snake1.heady && j == snake1.headx)
				cout << "O";

			else {
				bool printed = false;
				for (int z = 1; z < snake1.tail; z++)
				{
					if (snake1.tail_x[z] == j && snake1.tail_y[z] == i) {
						cout << "O";
						printed = true;
						break;
					}
				}
				if (!printed) {
					cout << " ";
				}


			}

		}
		cout << endl;

	}
	
}
void input() {
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			if (snake1.dir != Down)
				snake1.dir = Top;
			break;
		case 'a':
			if (snake1.dir != Rigth)
				snake1.dir = Left;
			break;
		case 's':
			if (snake1.dir != Top)
				snake1.dir = Down;
			break;
		case 'd':
			if (snake1.dir != Left)
				snake1.dir = Rigth;
			break;
		case 'x': 
			system("cls");
			start();
			break;
		case'g':
			cout << "\n \t\t good bay\n";
			exit(0);
		}
	}
}

void shift(int arr[], int size) {
	for (int i = size - 2; i >= 0; i--) {
		arr[i + 1] = arr[i];
	}
}
// move the snake 
void move() {

	shift(snake1.tail_x, 50);
	shift(snake1.tail_y, 50);
	snake1.tail_x[0] = snake1.headx;
	snake1.tail_y[0] = snake1.heady;
	// To change the location of the snake according to the user
	switch (snake1.dir)
	{
	case Top: snake1.heady--; break;
	case Down: snake1.heady++; break;
	case Rigth: snake1.headx++; break;
	case Left: snake1.headx--; break;
	}
	// Increase the snake's body if it eats frute
	if (snake1.headx == map1.fruitx && snake1.heady == map1.fruity) {
		// Increase player score by 1
		player1.score++;
		snake1.tail += 1;
		// Audio playback
		cout << "\a";
		//  call generate_frute for set up the  new values
		generate_frute();
	}
}
void check3() {
	if (snake1.tail == 10) {
		cout << "\n you win";
		Sleep(50);
		int x;
		cout << "\n \t\t next game press 1 : ";
		cin >> x;
		if (x == 1)
		{
			setup();
			player1.game_level++;
		}
		else
		{
			exit(0);
		}

	}
	if (snake1.heady == map1.heigth || snake1.heady <= 0 || snake1.headx >= map1.wigth || snake1.headx <= 0) {
		over();
	
	}
	for (int i = 0; i < snake1.tail; i++) {
		if (snake1.headx == snake1.tail_x[i] && snake1.heady == snake1.tail_y[i]) {
			if (player1.trying == 0) {
				over();
			}
			else {
				player1.trying--;
			}
		}
	}

}
// Ask the user if he wants to continue playing or quit his game
void over() {
	// to clear the screen
	system("cls");
	cout << "\t\t game over \n";
	cout << "\t a.for return the game \n";
	cout << "\t b.for exit the game \n";
	bool boole = true;
	// get input from  the user
	while (boole)
	{
		// if _kbhit is true In this case, the user enters a value.
		if (_kbhit())
		{
			// _getch() check any key user enters  
			switch (_getch())
			{
			// If a restart the game
			case 'a':
				start();
				break;
             // if b Get out of the game
			case 'b':
				player1.lose = true;
				break;
	
			}
			// if _kbhit is true In this case, the user enters a value, so we want to stop the loop
			boole = false;
		}
	}
}
void check1(int x) {
	if (snake1.headx == 0) {
		snake1.headx = map1.wigth - 3;
		for (int i = 0; i < snake1.tail; i++) {
			if (snake1.tail_x[i] == 0) {
				snake1.tail_x[i] = map1.wigth - 3;
				break;
			}

		}
	}
	else if (snake1.headx == map1.wigth - 1)
	{
		snake1.headx = 0;
		for (int i = 0; i < snake1.tail; i++) {
			if (snake1.tail_x[i] == map1.wigth - 1) {
				snake1.tail_x[i] = 0;
				break;
			}

		}
	}
	else if (snake1.heady == 0) {
		snake1.heady = map1.heigth - 1;
		for (int i = 0; i < snake1.tail; i++) {
			if (snake1.tail_y[i] == 0) {
				snake1.tail_y[i] = map1.heigth - 1;
				break;
			}

		}
	}
	else if (snake1.heady == map1.heigth - 1) {
		snake1.heady = 1;
		for (int i = 0; i < snake1.tail; i++) {
			if (snake1.tail_y[i] == map1.heigth - 1) {
				snake1.tail_y[i] = 1;
				break;
			}

		}
	}
	if (x == 0) {
		if (snake1.tail == 49) {
			cout << "\n you win";
			exit(0);
		}
	}
	if (x == 1) {
		if (snake1.tail == 20) {
			cout << "\n you win";
			Sleep(50);
			int x;
			cout << "\n \t\t next level press 1 : ";
			cin >> x;
			if (x == 1)
			{
				setup();
				player1.game_level++;
			}
			else
			{
				// call the function over
				over();
			}
		}
		// Check if the player lost or won
		for (int i = 0; i < snake1.tail; i++) {
			if (snake1.headx == snake1.tail_x[i] && snake1.heady == snake1.tail_y[i]) {
				// If player attempts = 0 call the function over
				if (player1.trying == 0) {
					over();
				}
				// Player's attempts decreased by 1
				else {
					player1.trying--;
				}
			}
		}
	}
}
void start() {
	// clean the screen 
	system("cls");
	cout << "\t\t welcome to my game \n ";
	cout << "\t a.for easy  \n ";
	cout << "\t b.for avwrage \n";
	cout << "\t c.for difficult \n \n \n\n\n";
	cout << " \t\t\t\tdeveloped by barsoum \n ";
	int x = 0;
	bool boole = true;
	// To take the inputs from the user to determine if the level is easy, medium or difficult
	while (boole)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
            // if [a] This means that I, the user, wanted to play the easy level
			case 'a':
				x = 1;
				break;   
			// if [a] This means that I, the user, wanted to play the avwrage level
			case 'b':
				x = 2;
				// Make Player Attempts = 5
				player1.trying = 5;
				// clean the screen 
				system("cls");
				cout << "\n\n \t\t you have 5 attempts \n \t\t good luck ";
				// To make the game stop for 3000 milliseconds
				Sleep(3000);
				break;
			case 'c':
				x = 3;
				// Make Player Attempts = 3
				player1.trying = 3;
				// clean the screen 
				system("cls");
				cout << "\n\n \t\tyou have 3 attempts \n \t\t good luck ";
				// To make the game stop for 3000 milliseconds
				Sleep(3000);
				break;
			}
			boole = false;
		}
	}
	setup();
	while (!player1.lose)
	{
		draw();
		input();
		move();
		if (x == 1)
		   check1(0);
		else if(x==2)
			check1(1);
		else if (x==3)
			check3();
		Sleep(20);
	}
	system("pause");
}
int main()
{ 
	start();
}


