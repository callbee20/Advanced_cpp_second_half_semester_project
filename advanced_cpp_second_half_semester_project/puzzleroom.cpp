#include "puzzleroom.h"
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <algorithm>
#include <iterator>

//default constructor
PuzzleRoom::PuzzleRoom()
{
    //initialize assets
    //reset door lock
    doorLocked = true;
    //reset area
    area = 0;
    //reset input
    userInput = 0;
    //leftPuzzleWon set to false
    leftPuzzleWon = false;
    //rightPuzzleWon set to false
    rightPuzzleWon = false;
    //game set to not over
    gameOver = false;

    //play room
    playRoom();
}

PuzzleRoom::~PuzzleRoom()
{
}

void PuzzleRoom::playRoom()
{
    //MAIN ROOM LOOP:
    while(gameOver != true)
    {
        //play room area
        playArea();
    }
}

void PuzzleRoom::playArea()
{
    if (area == 0) mainArea();
    else if (area == 1) endArea();
    else if (area == 2) leftArea();
    else if (area == 3) rightArea();
    else
    {
        std::cout << "Error, invalid room inputted" << std::endl;
        gameOver = true;
    }
}

void PuzzleRoom::mainArea()
{
    //clear screen
    clearScreen();
    //Display area message
    std::cout << "MAIN AREA:" << std::endl;
    coolPrint("You see a door ahead of you, and two peculiar puzzles are to your right and left");
    std::cout << std::endl;
    coolPrint("1. Go to door");
    std::cout << std::endl;
    coolPrint("2. Go to left");
    std::cout << std::endl;
    coolPrint("3. Go to right");
    std::cout << std::endl;
    coolPrint("What would you like to do?");
    std::cout << std::endl;

    //get userInput
    getInput(3);

    //process userInput
    if (userInput == 1) area = 1;
    else if (userInput == 2) area = 2;
    else if (userInput == 3) area = 3;
    //clear screen
    clearScreen();
}

void PuzzleRoom::endArea()
{
    //Display area message
    std::cout << "DOOR:" << std::endl <<
        "You walk up to a massive red door with the letters 'NO' on it. Hmmm..." << std::endl <<
        "1. Try the door" << std::endl <<
        "2. Examine the door" << std::endl <<
        "3. Go back to main area" << std::endl <<
        "What would you like to do?" << std::endl;

    //get userInput
    getInput(3);

    //process userInput
    //If door is unlocked, go thru and finish room, otherwise print message and do nothing
    if (userInput == 1)
    {
        if (doorLocked)
        {
            //print message and do nothing (currently ends game)
            std::cout << "The door won't open, you try so hard you get a heart attack and die" << std::endl;
            gameOver = true;
        }
        else
        {
            //Finish room
            //TODO
        }
    }
    else if (userInput == 2)
    {
        //Print a message depending on completion of puzzles and do nothing
        if ((leftPuzzleWon == true) && (rightPuzzleWon == true))
        {
            std::cout << "Upon closer examination you notice no locks remain. The door is unlocked." << std::endl;
        }
        else if ((leftPuzzleWon == true) && (rightPuzzleWon == false))
        {
            std::cout << "Upon closer examination you notice only the right lock remains." << std::endl;
        }
        else if ((leftPuzzleWon == false) && (rightPuzzleWon == true))
        {
            std::cout << "Upon closer examination you notice only the left lock remains." << std::endl;
        }
        else
        {
            std::cout << "Upon closer examination you notice two massive locks on the door, each with chains leading around the room to either side" << std::endl <<
                "Wow! How did you not notice them?" << std::endl;
        }
    }
    else if (userInput == 3)
    {
        //Go back to main area
        area = 0;
        //clear screen
        clearScreen();
    }
}

void PuzzleRoom::leftArea()
{
    //Display area message
    std::cout << "LEFT AREA:" << std::endl;
    //Modify message depending if left puzzle has been won or not
    if (leftPuzzleWon)
    {
        std::cout << "Where chains used to lead off of the left of the door, only a pile of ash remains with subtle burn marks" << std::endl <<
            "outlining the chains that used to remain" << std::endl << std::endl;
    }
    else
    {
        std::cout << "You walk up to where chains lead off of the left of the door over to a odd looking puzzle." << std::endl <<
            "1. Examine puzzle" << std::endl;
    }
    std::cout << "2. Go back to main area" << std::endl <<
        "What would you like to do?" << std::endl;

    //get userInput
    getInput(2);

    //process userInput
    if (userInput == 1)
    {
        //check if puzzle has been completed
        if (leftPuzzleWon)
        {
            std::cout << "The puzzle has been completed, and is now a pile of dust." << std::endl;
        }
        else
        {
            //play left puzzle
            leftPuzzle();
        }
    }
    //Go back to main area
    else if (userInput == 2)
    {
        area = 0;
        //clear screen
        clearScreen();
    }
}

void PuzzleRoom::rightArea()
{
    //Display area message
    std::cout << "RIGHT AREA:" << std::endl;
    //Modify message depending if left puzzle has been won or not
    if (rightPuzzleWon)
    {
        std::cout << "Where chains used lead off of the left of the door, only a pile of ash remains with subtle burn marks" << std::endl <<
            "outlining the chains that used to remain" << std::endl;
    }
    else
    {
        std::cout << "You walk up to where chains lead off of the left of the door over to a odd looking puzzle." << std::endl;
    }
    std::cout << "1. Examine puzzle" << std::endl <<
        "2. Go back to main area" << std::endl <<
        "What would you like to do?" << std::endl;

    //get userInput
    getInput(2);

    //process userInput
    if (userInput == 1)
    {
        //check if puzzle has been completed
        if (rightPuzzleWon)
        {
            std::cout << "The puzzle has been completed, and is now a pile of dust." << std::endl;
        }
        else
        {
            //play right puzzle
            rightPuzzle();
        }
    }
    //go back to main area
    else if (userInput == 2)
    {
        area = 0;
        //clear screen
        clearScreen();
    }
}

void PuzzleRoom::leftPuzzle()
{
    //initialize puzzle room assets:

    //create bool to determine puzzle fail/win and set
    bool puzzleFail = false;

    //create/set int for number of correct matches and incorrect matches
    int correctMatches = 0;
    int incorrectMatches = 0;

    //create user guesses
    int guess1 = 1;
    int guess2 = 1;

    //create puzzle board
    int const boardSize = 16;
    int board[boardSize]{};

    //load board with random ints
    for (int i = 0; i < boardSize; i++) board[i] = (rand() % 2) + 1; //random number between 1-2

    //create boolean array of user guesses and set to false
    bool userGuess[boardSize]{false};


    //ENTER PUZZLE LOOP
    while((!leftPuzzleWon) && (!puzzleFail))
    {
        //Refresh screen
        clearScreen();

        //Print start, correct, or incorrect message:
        //if game has just started, print a blank space
        if ((correctMatches == 0) && (incorrectMatches == 0))
        {
            std::cout << std::endl;
        }
        else if (board[guess1 - 1] == board[guess2 - 1]) //if correct match
        {
            std::cout << "Correct!" << std::endl;
        }
        else //else incorrect match
        {
            std::cout << "Incorrect!" << std::endl;
        }

        //Print board:
        for (int i = 0; i < boardSize; i++)
        {
            //if space has been guessed, show it, else dont
            (userGuess[i]) ? (std::cout << board[i] << " ") : (std::cout << "X ");
            //Every 4 board spaces, go to a new line:
            if ((i + 1) % 4 == 0) std::cout << std::endl;
        }

        //Print correct and incorrect guesses
        std::cout << "Correct matches: " << correctMatches << std::endl;
        std::cout << "Incorrect matches: " << incorrectMatches << std::endl;

        std::cout << "Guess a match" << std::endl <<
            "Guess 1: ";
        //get guess 1
        std::cin >> guess1;
        //input validation:
        while ((guess1 < 1) || (guess1 > boardSize) || (userGuess[guess1 - 1] == true))
        {
            if ((guess1 < 1) || (guess1 > boardSize))
            {
                std::cout << "Invalid selection, enter a number between 1-" << boardSize << ": ";
                std::cin >> guess1;
            }
            else if (userGuess[guess1 - 1] == true)
            {
                std::cout << "Invalid selection, you have already selected that one.";
                std::cin >> guess1;
            }
        }
        userGuess[guess1 - 1] = true;

        std::cout << "Guess 2: ";
        //get guess2
        std::cin >> guess2;
        //input validation
        while((guess2 < 1) || (guess2 > boardSize) || (userGuess[guess2 - 1] == true))
        {
            if ((guess2 < 1) || (guess2 > boardSize))
            {
                std::cout << "Invalid selection, enter a number between 1-" << boardSize << ": ";
                std::cin >> guess2;
            }
            else if (userGuess[guess2 - 1] == true)
            {
                std::cout << "Invalid selection, you have already selected that one. Select again";
                std::cin >> guess2;
            }
        }
        userGuess[guess2 - 1] = true;

        //check to see if guesses match
        if (board[guess1 - 1] == board[guess2 - 1]) //if correct match
        {
            correctMatches += 1;
        }
        else //else incorrect match
        {
            incorrectMatches += 1;
        }

        //Check for win and loss conditions:
        if (correctMatches == 3)
        {
            std::cout << "As you enter your guess, the puzzle starts to crack, and within seconds it crumbles into itself." << std::endl <<
                "In a chain-reaction, the links attached to the puzzle begin to break away in similar fashion." << std::endl <<
                "One by one, The chains break away until they break away from the door." << std::endl;
            leftPuzzleWon = true;
        }
        else if (incorrectMatches == 3)
        {
            std::cout << "Slashes break through all sides of the puzzle, scribbling it into a blank slate." << std::endl <<
                "As quickly as the puzzle disappeared, a fresh, blank puzzle rises from the surface in an effervescent fashion," << std::endl <<
                "as though the surface was liquid." << std::endl;
            puzzleFail = true;
        }
    }
}

void PuzzleRoom::rightPuzzle()
{
    //initialize puzzle room assets:

    //create bool to determine puzzle fail/win and set
    bool puzzleFail = false;

    //create bool for invalid inputs
    bool invalidInput = false;

    //create int for index of zero
    int indexOfZero = 0;

    //create puzzle board
    int const boardSize = 9;
    int board[boardSize]{};

    //create array of random ints for a randomized selection sort on the board
    int randomizer[boardSize]{};

    //load board with ints 0-15 and randomizer with random ints
    //generate initial rand() seed based off system time
    srand(time(0));
    for (int i = 0; i < boardSize; i++)
    {
        board[i] = i;
        //get new random seed from last random number
        srand(rand());
        randomizer[i] = time(NULL) / rand(); //random ints with system clock as random seed
    }

    //RANDOM SORT:
    //performed through a selection sort of the randomizer, and
    //perform the same sorting on the board array
    int min_index;
    for (int i = 0; i < boardSize - 1; i++)
    {
        min_index = i;
        for (int j = i + 1; j < boardSize; j++)
        {
            if (randomizer[j] < randomizer[min_index])
            {
                min_index = j;
            }
        }
        //swap randomizer variables
        int temp = randomizer[i];
        randomizer[i] = randomizer[min_index];
        randomizer[min_index] = temp;
        //swap board numbers
        temp = board[i];
        board[i] = board[min_index];
        board[min_index] = temp;
    }

    //BEGIN PUZZLE LOOP
    while ((!puzzleFail) && (!leftPuzzleWon))
    {
        //clear screen
        clearScreen();

        //print is sorted followed by new line
        std::cout << "is sorted: " << std::boolalpha <<
            std::is_sorted(std::begin(board), std::end(board)) << std::endl << std::endl;

        //print randomized board
        for (int i = 0; i < boardSize; i++)
        {
            if (board[i] == 0)
            {
                //record index
                indexOfZero = i;
                std::cout << "   ";
            }
            else std::cout << ((board[i] < 10) ? (" ") : ("")) << board[i] << " ";

            if ((i + 1) % 3 == 0) std::cout << std::endl;
        }

        //Print directions
        std::cout << "Align the pieces in order," << std::endl <<
            "Choose a number to the top, left, right, or bottom" << std::endl <<
            "of the blank space, to swap it's place" << std::endl << std::endl;

        //if last input was invalid, print message
        if (invalidInput)
        {
            std::cout << "Error, that move is not allowed!" << std::endl << std::endl;
            //reset invalidInput to false
            invalidInput = false;
        }
        //else print blank line
        else std::cout << std::endl << std::endl;

        //get input
        std::cout << "Which number do you want to swap?: " << std::endl <<
            "1. Left" << std::endl <<
            "2. Bottom" << std::endl <<
            "3. Right" << std::endl <<
            "4. Top" << std::endl <<
            "5. Exit" << std::endl;
        getInput(5);

        if (userInput == 5) //exit the puzzle
        {
            std::cout << "Are you sure you want to exit the puzzle?" << std::endl <<
                "1. Yes" << std::endl <<
                "2. No" << std::endl;
            getInput(2);
            if (userInput == 1)
            {
                puzzleFail = true;
            }
        }
        //check input and zero index to decide if swap is possible
        //make swap if possible
        //trigger invalid input message
        else if (userInput == 1) //left
        {
            //swapping to left is impossible if indexOfZero is on left,
            //This is indexes 0, 3, and 6
            //This can be accomplished by asking is indexOfZero % 3 == 0
            if (indexOfZero % 3 == 0) invalidInput = true; //invalid move
            else //valid move
            {
                //swap zero with value to the left of it
                board[indexOfZero] = board[indexOfZero - 1];
                board[indexOfZero - 1] = 0;
                //set new indexOfZero
                --indexOfZero;
            }
        }
        else if (userInput == 2) //bottom
        {
            //swapping bottom is impossible if indexOfZero is on bottom,
            //this is indexes 6, 7, and 8
            //this is checked simply by checking if indexOfZero is 12 or greater
            if (indexOfZero >= 6) invalidInput = true; //invalid move
            else //valid move
            {
                //swap zero with value to the bottom of it
                board[indexOfZero] = board[indexOfZero + 3];
                board[indexOfZero + 3] = 0;
                //set new indexOfZero
                indexOfZero += 3;
            }
        }
        else if (userInput == 3) //right
        {
            //swapping right is impossible if indexOfZero is on right
            //this is indexes 2, 5, and 8
            //this is checked by (indexOfZero + 1) % 3
            if ((indexOfZero + 1) % 3 == 0) invalidInput = true; // invalid move
            else //valid move
            {
                //swap zero with value to the right of it
                board[indexOfZero] = board[indexOfZero + 1];
                board[indexOfZero + 1] = 0;
                //set new indexOfZero
                ++indexOfZero;
            }
        }
        else if (userInput == 4) //top
        {
            //swapping top is impossible if indexOfZero is on top
            //this is indexes 0, 1, and 2
            //this is checked if indexOfZero is 2 or less
            if (indexOfZero <= 2) invalidInput = true; // invalid move
            else //valid move
            {
                //swap zero with value to the top of it
                board[indexOfZero] = board[indexOfZero - 3];
                board[indexOfZero - 3] = 0;
                //set new indexOfZero
                indexOfZero -= 3;
            }
        }

    }


}

void PuzzleRoom::getInput(int numOptions)
{
    //reset input
    userInput = 0;

    //loop input if input is not valid
    while(userInput < 1 || userInput > numOptions)
    {
        std::cin >> userInput;
        if (userInput < 1 || userInput > numOptions) std::cout << "Invalid selection" << std::endl;
    }
}

void PuzzleRoom::processInput()
{
    //TODO? all if/else if statements can be put here for better cleanup
}

void PuzzleRoom::clearScreen()
{
    std::cout << std::flush;
    system("CLS");
}

void PuzzleRoom::coolPrint(std::string s)
{
    for (size_t i = 0; i < s.length(); i++)
    {
        std::cout << s[i];

        //pulled from https://stackoverflow.com/questions/4184468/sleep-for-milliseconds:
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        //sleeps for 1 milisecond
    }
}
