/*
	Jayce Abens
	FA 2021
	Due : N/A
	Bonus Challenge
	Make a number guessing game which generates a random number between 1-10, 
	gives the player 3 guesses, and tells them if they guessed right or not.
*/

#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>

using namespace std;

void randomNumberGenerator();
void difficultySelect();
void playGame();
void endMessage();
void calculateHint();

int randomNumber;				// declares random number variable
const int low = 1;				// sets the low end of the number range
int high;						// declares the variable for the high end of the number range
int range;						// declares range variable
int numberOfGuesses = 3;		// sets the number of guesses allowed in the game
int guess;						// declares the guess variable
int lastGuess;					// declares the variable to store the previous guess
string playerResponse;			// declares the player response variable
bool play = true;				// declares the boolean variable play, deterimes if the player wants to play again
bool hints;						// declares the hints boolean variable

int main()
{
	cout << "********** WELCOME TO THE NUMBER GUESSING GAME! ***********" << endl << endl;
	while (play == true)
	{
		difficultySelect();
		randomNumberGenerator();
		playGame();
		endMessage();
	}
	return 0;
}

void randomNumberGenerator()
{
	srand(time(0));													// sets the current time as the pseudo random number generator seed
	range = (high - low) + 1;										// calculates the total range of number posibilities
	randomNumber = low + int(range * rand() / (RAND_MAX + 1.0));	// randomNumber = the low end of the number range(1) + a random number(0-32767) scaled to the range (0-9)
}

void difficultySelect()
{
	cout << "--- Please select a difficulty from the list below ---" << endl << endl;
	cout << "1. EASY : Number 1-10 | 4 Guesses | Hints!" << endl;
	cout << "2. MEDIUM : Number 1-10 | 3 Guesses | No Hints!" << endl;
	cout << "3. HARD : Number 1-25 | 5 Guesses | Good Luck!" << endl << endl;
	cout << "Enter the number of your difficulty selection and press enter to continue." << endl << endl;
	difficultyRepeat:
	cin >> playerResponse;
	if (playerResponse == "1")
	{
		cout << endl << "***** EASY *****" << endl << endl;
		high = 10;
		numberOfGuesses = 4;
		hints = true;
	}
	else if (playerResponse == "2")
	{
		cout << endl << "***** MEDIUM *****" << endl << endl;
		high = 10;
		numberOfGuesses = 3;
		hints = false;
	}
	else if (playerResponse == "3")
	{
		cout << endl << "***** HARD *****" << endl << endl;
		high = 25;
		numberOfGuesses = 5;
		hints = false;
	}
	else
	{
		cout << endl << "You didn't enter a number 1-3. Try Again!" << endl << endl;
		goto difficultyRepeat;
	}
}

void playGame()
{
	cout << "I have generated a number between " << low << " and " << high << ". It is your job to guess what it is! You get "
		<< numberOfGuesses << " tries, whats your guess? " << endl << endl;

	for (int i = 1; i <= numberOfGuesses; i++)
	{
		cout << "Type your guess #" << i << " and press enter to confirm" << endl << endl;
		cin >> guess;
		if (guess == randomNumber)
		{
			cout << endl << "You got it on your " << i << " try!" << endl << endl;
			i = numberOfGuesses + 1;
		}
		else
		{
			if (i < numberOfGuesses - 1)
			{
				cout << endl << "Not Quite!";
				if (i != 1 ) { calculateHint(); }
				cout << "You have " << numberOfGuesses - i << " guesses left.Try Again!" << endl << endl;
			}
			else if (i < numberOfGuesses)
			{
				cout << endl << "That's not it!";
				if (i != 1) { calculateHint(); }
				cout << "You have 1 guess left. One last try!" << endl << endl;
			}
			else 
			{
				cout << endl << "Nope! You're out of guesses!" << endl << endl;
			}
		}
		cout << "------------------------------------------------------------------------------------------------" << endl << endl;
	}
}

void calculateHint()
{
	if (hints == true)
	{
		if (abs(randomNumber - lastGuess) > abs(randomNumber - guess))
		{
			cout << " You're getting warmer! ";
		}
		else if (abs(randomNumber - lastGuess) < abs(randomNumber - guess))
		{
			cout << " You're getting colder!";
		}
		else
		{
			cout << " You stayed the same temperature. Guess a different number! ";
		}
	}
}

void endMessage()
{
	endRepeat:
	cout << "Do you want to play again? (yes / no)" << endl << endl;
	cin >> playerResponse;
	if (playerResponse == "yes" || playerResponse == "Yes" || playerResponse == "y")
	{
		cout << endl << "Let's start again!" << endl << endl;
		play = true;
	}
	else if (playerResponse == "no" || playerResponse == "No" || playerResponse == "n")
	{
		cout << endl <<  "It's been good playing! See you next time!" << endl << endl;
		play = false;
	}
	else
	{
		cout << endl << "I don't understand. Make sure you answer yes or no!" << endl << endl;
		goto endRepeat;
	}
}

