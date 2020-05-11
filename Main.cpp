//Assignment 5
//Ishan Chaurasia, 101011068
//Hangman Game to demonstrate understanding and usage of file stream.

#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
#include <vector>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

void gotoXY(int x, int y);
void Credits();
void mainMenu();
void printMan(int hangman);
void singleplayGame();
void twoplayGame();

vector <string> words;
int random;
string soloplayer;
string oneplayer;
string twoplayer;

int main()
{
	srand(time(NULL));

	ifstream myFile("dictionary.txt");

	//Open File Check
	if (!myFile.fail())
	{
		while (!myFile.eof())
		{
			string temp;
			getline(myFile, temp);
			words.push_back(temp);
		}
		myFile.close();
	}
	
	srand(time(NULL));
	random = rand() % words.size();

	mainMenu();

	system("pause");
	return 0;
}

void singleplayGame()
{
	cout << "You have chosen Single Player." << endl;
	cout << "Enter player name: ";
	cin >> soloplayer;

	char guess;
	string hangman_word = words[random];
	int mistakes = 0;

	//Display Chosen Letter for Testing
	cout << hangman_word << endl;

	//Display _ for each Letter
	cout << "Your word has " << hangman_word.size() << " letters." << endl;
	for (int i = 0; i < hangman_word.size(); i++)
	{
		cout << "_" << " ";
	}
	printMan(mistakes);

	string userWord;
	char temp = '_';
	string wrongGuess;
	bool gameOver = false;

	//Assign _ to guessed word.
	for (int i = 0; i < hangman_word.size(); i++)
	{
		userWord = userWord + temp;
	}

	//Main Game
	while (mistakes != 6 && !gameOver)
	{
		gameOver = true;

		//User Guess
		cout << endl << "Please enter a letter: ";
		cin >> guess;
		cout << endl;

		bool wrongLetter = true;

		//Letter Check
		for (int i = 0; i < hangman_word.size(); i++)
		{
			if (guess == hangman_word[i])
			{
				cout << "You Guessed Right!" << endl;
				//system("PAUSE");
				userWord[i] = guess;
				wrongLetter = false;
			}
		}
		if (wrongLetter == true)
		{
			wrongGuess += guess;
			cout << "You Guessed Wrong." << endl;
			//system("PAUSE");
			mistakes++;
		}

		system("CLS");
		cout << "Your word has " << hangman_word.size() << " letters." << endl;

		//Print Guessed Words
		for (int i = 0; i < userWord.size(); i++)
		{
			cout << userWord[i] << " ";
		}
		printMan(mistakes);

		for (int i = 0; i < userWord.size(); i++)
		{
			if (userWord[i] == '_')
			{
				gameOver = false;
			}
		}
	}

	cout << "The End." << endl << endl;

	ofstream scoreFile("Final_Score.txt");

	if (!scoreFile.fail())
	{
		scoreFile << soloplayer << " guessed '" << hangman_word << "' with " << mistakes << " wrong guesses." << endl;
		scoreFile.close();
	}

	system("PAUSE");
	system("CLS");
	mainMenu();

}

void twoplayGame()
{
	cout << "You have chosen Double Player." << endl;

	char guess;
	string hangman_word;
	int mistakes = 0;

	cout << "Player 1." << endl << "Enter your name: ";
	cin >> oneplayer;
	cout << endl << "Player 2." << endl << "Enter your name: ";
	cin >> twoplayer;
	cout << endl << oneplayer << ", Type your secret word : ";
	cin >> hangman_word;

	//Display _ for each Letter
	system("CLS");
	cout << oneplayer << " has written a " << hangman_word.size() << " letters long word." << endl << twoplayer << "'s turn." << endl;
	for (int i = 0; i < hangman_word.size(); i++)
	{
		cout << "_" << " ";
	}
	printMan(mistakes);

	string userWord;
	char temp = '_';
	string wrongGuess;
	bool gameOver = false;

	//Assign _ to guessed word.
	for (int i = 0; i < hangman_word.size(); i++)
	{
		userWord = userWord + temp;
	}

	//Main Game
	while (mistakes != 6 && !gameOver) //change true to how many turns until guy hangs
	{
		gameOver = true;

		//User Guess
		cout << endl << "Please enter a letter: ";
		cin >> guess;
		cout << endl;

		bool wrongLetter = true;

		//Letter Check
		for (int i = 0; i < hangman_word.size(); i++)
		{
			if (guess == hangman_word[i])
			{
				cout << "You Guessed Right!" << endl;
				//system("PAUSE");
				userWord[i] = guess;
				wrongLetter = false;
			}
		}
		if (wrongLetter == true)
		{
			wrongGuess += guess;
			cout << "You Guessed Wrong." << endl;
			//system("PAUSE");
			mistakes++;
		}

		system("CLS");
		cout << "Your word has " << hangman_word.size() << " letters." << endl;

		//Print Guessed Words
		for (int i = 0; i < userWord.size(); i++)
		{
			cout << userWord[i] << " ";
		}
		printMan(mistakes);

		for (int i = 0; i < userWord.size(); i++)
		{
			if (userWord[i] == '_')
			{
				gameOver = false;
			}
		}
	}

	cout << "The End." << endl << endl;

	ofstream scoreFile("Final_Score.txt");

	if (!scoreFile.fail())
	{
		scoreFile << oneplayer << " picked '" << hangman_word << "' and " << twoplayer << " guessed it with " << mistakes << " wrong guesses." << endl;
		//scoreFile << twoplayer << " guessed '" << hangman_word << "' with " << mistakes << " wrong guesses." << endl;
		scoreFile.close();
	}

	system("PAUSE");
	system("CLS");
	mainMenu();
}

void gotoXY(int x, int y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };
	SetConsoleCursorPosition(hStdout, position);
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = false;
	cursorInfo.dwSize = 10;
	SetConsoleCursorInfo(hStdout, &cursorInfo);
}

void Credits()
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "Written by: Ishan Chaurasia 101011068" << endl;
	cout << "You have 6 allowed mistakes before the guy hangs." << endl << "GoodLuck." << endl;
	system("pause");
	system("CLS");
	mainMenu();
}

void mainMenu()
{

	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	string hangingpost1 = " __________";
	string hangingpost2 = " |         |";
	string hangingpost3 = " |";
	string hangingpost4 = "_|_";

	gotoXY(46, 9);
	cout << hangingpost1;
	gotoXY(46, 10);
	cout << hangingpost2;
	gotoXY(46, 11);
	cout << hangingpost2;
	gotoXY(46, 12);
	cout << hangingpost3;
	gotoXY(46, 13);
	cout << hangingpost3;
	gotoXY(46, 14);
	cout << hangingpost3;
	gotoXY(46, 15);
	cout << hangingpost3;
	gotoXY(46, 16);
	cout << hangingpost3;
	gotoXY(46, 17);
	cout << hangingpost4;
	gotoXY(54, 12);
	cout << "HANGMAN";

	//Game Options
	gotoXY(53, 14);															// Menu Display to show options
	cout << "Game Info";
	gotoXY(53, 15);
	cout << "Player vs AI";
	gotoXY(53, 16);
	cout << "Player vs Player";
	gotoXY(53, 17);
	cout << "Quit Game" << endl;


	gotoXY(51, 14);
	cout << (char)175;

	// Cursor Movements in MainScreen
	int y = 14;
	int c = 0;
	c = _getch();

	while (c != 13)
	{
		switch (c = _getch())
		{
		case KEY_ENTER:
			switch (y)
			{
			case 14:
				system("CLS");
				Credits();
				break;

			case 15:
				system("CLS");
				singleplayGame();
				break;

			case 16:
				system("CLS");
				twoplayGame();
				break;

			case 17:
				break;
			}

		case KEY_DOWN:
			if (y < 17) {
				gotoXY(51, y);
				cout << " ";
				gotoXY(51, y + 1);
				cout << (char)175;
				y++;
			}
			break;

		case KEY_UP:
			if (y > 14)
			{
				gotoXY(51, y);
				cout << " ";
				gotoXY(51, y - 1);
				cout << (char)175;
				y--;
				break;
			}
		}
	}
	system("cls");
}

void printMan(int hangman)
{
	switch (hangman)
	{
	case 0:
		cout << "\n    _______\n";
		cout << "   |/      |\n";
		cout << "   |\n";
		cout << "   |\n";
		cout << "   |\n";
		cout << "   |\n";
		cout << "   |\n";
		cout << "___|___\n";
		break;
	case 1:
		cout << "\n    _______\n";
		cout << "   |/      |\n";
		cout << "   |      (_)\n";
		cout << "   |\n";
		cout << "   |\n";
		cout << "   |\n";
		cout << "   |\n";
		cout << "___|___\n";
		break;
	case 2:
		cout << "\n    _______\n";
		cout << "   |/      |\n";
		cout << "   |      (_)\n";
		cout << "   |       |\n";
		cout << "   |       |\n";
		cout << "   |\n";
		cout << "   |\n";
		cout << "___|___\n";
		break;
	case 3:
		cout << "\n    _______\n";
		cout << "   |/      |\n";
		cout << "   |      (_)\n";
		cout << "   |      \\|\n";
		cout << "   |       |\n";
		cout << "   |\n";
		cout << "   |\n";
		cout << "___|___\n";
		break;
	case 4:
		cout << "\n    _______\n";
		cout << "   |/      |\n";
		cout << "   |      (_)\n";
		cout << "   |      \\|/\n";
		cout << "   |       |\n";
		cout << "   |\n";
		cout << "   |\n";
		cout << "___|___\n";
		break;
	case 5:
		cout << "\n    _______\n";
		cout << "   |/      |\n";
		cout << "   |      (_)\n";
		cout << "   |      \\|/\n";
		cout << "   |       |\n";
		cout << "   |      /\n";
		cout << "   |\n";
		cout << "___|___\n";
		break;
	case 6:
		cout << "\n    _______\n";
		cout << "   |/      |\n";
		cout << "   |      (_)\n";
		cout << "   |      \\|/\n";
		cout << "   |       |\n";
		cout << "   |      / \\\n";
		cout << "   |\n";
		cout << "___|___\n";
		break;
	}
}