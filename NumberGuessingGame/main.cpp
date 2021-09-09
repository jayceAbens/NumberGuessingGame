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
		difficultySelect();			// prompts the player to select difficulty, adjusts settings
		randomNumberGenerator();	// generates a new random number between low and high each game cycle
		playGame();					// contains the main gamplay gussing loop, player input, reponses
		endMessage();				// propts the player to play again, loops to beginning if yes
	}
	return 0;
}

void difficultySelect()
{
	cout << "--- Please select a difficulty from the list below ---" << endl << endl;
	cout << "1. EASY : Number 1-10 | 4 Guesses | Hints!" << endl;
	cout << "2. MEDIUM : Number 1-10 | 3 Guesses | No Hints!" << endl;
	cout << "3. HARD : Number 1-25 | 5 Guesses | Good Luck!" << endl << endl;
	cout << "Enter the number of your difficulty selection and press enter to continue." << endl << endl;
	difficultyRepeat:				// goto here if difficulty selection number is not in range
	cin >> playerResponse;			// stores players selection
	if (playerResponse == "1")		// prints easy selection, adjusts game parameters accordingly
	{
		cout << endl << "***** EASY *****" << endl << endl;
		high = 10;
		numberOfGuesses = 4;
		hints = true;
	}
	else if (playerResponse == "2")	// prints easy selection, adjusts game parameters accordingly
	{
		cout << endl << "***** MEDIUM *****" << endl << endl;
		high = 10;
		numberOfGuesses = 3;
		hints = false;
	}
	else if (playerResponse == "3")	// prints easy selection, adjusts game parameters accordingly
	{
		cout << endl << "***** HARD *****" << endl << endl;
		high = 25;
		numberOfGuesses = 5;
		hints = false;
	}
	else							// asks the player for a correct selection, repeats logic
	{
		cout << endl << "You didn't enter a number 1-3. Try Again!" << endl << endl;
		goto difficultyRepeat;
	}
}

void randomNumberGenerator()
{
	srand(time(0));													// sets the current time as the pseudo random number generator seed
	range = (high - low) + 1;										// calculates the total range of number posibilities
	randomNumber = low + int(range * rand() / (RAND_MAX + 1.0));	// randomNumber = the low end of the number range(1) + a random number(0-32767) scaled to the range (0-9)
}

void playGame()
{
	cout << "I have generated a number between " << low << " and " << high << ". It is your job to guess what it is! You get "
		<< numberOfGuesses << " tries, whats your guess? " << endl << endl;
	// Tells the player the range of numbers possible, number of guesses

	for (int i = 1; i <= numberOfGuesses; i++)
	{
		cout << "Type your guess #" << i << " and press enter to confirm" << endl << endl;		// Prompts for guess
		guessRepeat:		// goto here if guess is out of range, gives another try
		cin >> guess;		// stores player guess
		if (guess >= low && guess <= high)		// validates that player guess is within range
		{
			if (guess == randomNumber)			// identifies correct guess, ends game loop
			{
				cout << endl << "You got it on your " << i << " try!" << endl << endl;
				i = numberOfGuesses + 1;
			}
			else			// Responses for incorrect guess			
			{
				if (i < numberOfGuesses - 1)
				{
					cout << endl << "Not Quite!";
					if (i != 1) { calculateHint(); }	// disables hints for first guess
					cout << "You have " << numberOfGuesses - i << " guesses left.Try Again!" << endl << endl; // Prints the number of guesses remaining
				}
				else if (i < numberOfGuesses)
				{
					cout << endl << "That's not it!";
					if (i != 1) { calculateHint(); }	// disables hints for first guess
					cout << "You have 1 guess left. One last try!" << endl << endl;	// prints that there is one guess remaining
				}
				else
				{
					cout << endl << "Nope! You're out of guesses!" << endl << endl; // losing message for running out of guesses
				}
			}
		}
		else	// Prompts player to enter a valid guess, jumps to begining of game loop without penalty
		{
			cout << "You didn't enter a number between " << low << " and " << high << "! I won't count that one, guess again!" << endl << endl;
			goto guessRepeat;
		}
		cout << "------------------------------------------------------------------------------------------------" << endl << endl;
	}
}

void calculateHint()
{
	if (hints == true)	// checks if hints are enabled
	{
		if (abs(randomNumber - lastGuess) > abs(randomNumber - guess)) // checks if new guess is closer to random number
		{
			cout << " You're getting warmer! ";
		}
		else if (abs(randomNumber - lastGuess) < abs(randomNumber - guess))	// checks if new guess is farther from random number
		{
			cout << " You're getting colder!";
		}
		else	// player entered same number, not warmer or colder
		{
			cout << " You stayed the same temperature. Guess a different number! ";
		}
	}
}

void endMessage()
{
	endRepeat:		// goto here if y/n response is invalid
	cout << "Do you want to play again? (yes / no)" << endl << endl;
	cin >> playerResponse;		// stores y/n answer
	if (playerResponse == "yes" || playerResponse == "Yes" || playerResponse == "y") // allows various possible yes answers
	{
		cout << endl << "Let's start again!" << endl << endl;
		play = true;	// keeps play true allowing repeat of game
	}
	else if (playerResponse == "no" || playerResponse == "No" || playerResponse == "n") // allows various possible no answers
	{
		cout << endl <<  "It's been good playing! See you next time!" << endl << endl;
		play = false;	// sets play to false ending game loop
	}
	else	// repeats question if answer is not valid
	{
		cout << endl << "I don't understand. Make sure you answer yes or no!" << endl << endl;
		goto endRepeat;	
	}
	cout << "------------------------------------------------------------------------------------------------" << endl << endl;                            
}

