//Header file PuzzleRoom.h
#pragma once
#include <string>

class PuzzleRoom
{
private:
    //Message to be displayed to console
    std::string message;

    //Area of the room (0-3)
    //0 is main area
    //1 is door wall ahead
    //2 is left puzzle wall
    //and 3 is right puzzle wall
    int area;

    //boolean variable containing left and right puzzle status
    bool leftPuzzleWon;
    bool rightPuzzleWon;

    //boolean variable containing door status
    bool doorLocked;

    //User input
    int userInput;

    //boolean variable of game over status
    bool gameOver;

public:
    //defaut constructor
    //Initializes room and assets
    PuzzleRoom();

    //default destructor
    ~PuzzleRoom();

    //Enters room loop
    void playRoom();

    //read area information to user
    void playArea();


    //functions for each room
    void mainArea();

    void endArea();

    void leftArea();

    void rightArea();

    //functions for each puzzle
    void leftPuzzle();

    void rightPuzzle();

    //gets user input using a validation loop between 1-numOptions
    void getInput(int numOptions);

    //process input
    void processInput();

    //clear console screen
    void clearScreen();

    //cool print technique i thought of this morning
    void coolPrint(std::string s);
};

