/*
 * Author: Carson Allbee
 * Date: 3/27/22
 * Email: callbee@dmacc.edu
*/
#ifndef ROOMA_H
#define ROOMA_H

#endif // ROOMA_H
#include <iostream>
using namespace std;

bool unlockedDoor = false; //boolean to determine if door is unlocked
bool keyGot = false; //boolean to simulate if key is found
string userChoice;

void lookAround() {
    cout << "You notice a door at the end of the room, the room is empty except for a single key on the left side of the room." << endl;
}

void pickupKey() {
    keyGot = true;
    cout << "You pick up the key" << endl;
}

void unlockDoor() {
    if (keyGot == true) {
        cout << "You unlock and open the door" << endl;
    }
}

//Acts as .h file's main function
int roomAMain() {
    cout << "You enter the room, what do you do? \n 1: Look around\n 3: Quit Loop" << endl;
    cin >> userChoice;

    //Loop that gives user a couple of choices to find the key
    while(userChoice != "3") {
        if(userChoice == "1") {
            lookAround();
        }
        else if (userChoice == "2") {
             pickupKey();
        }
        else if(userChoice == "3") {
            break;
        }
        else {
            cout << "Invalid choice" << endl;
        }
        cout << "What Now? \n 1: Look around \n 2: Pick up the key \n 3: Quit Loop" << endl;
        cin >> userChoice;
    }

    //User should exit above loop when the key is found, if so new option is availabe, if not program ends after a short message.
    if(keyGot == true){
        cout << "You can now open the door, what would you like to do? \n 1: Unlock door \n 2: Quit Game" << endl;
        cin >> userChoice;
        if(userChoice == "1") {
            unlockDoor();
            cout << "You step through the room into the next." << endl;
            return 0;
        }
        else if(userChoice == "2") {

            return 0;
        }
    }

    cout << "Thanks for Playing!" << endl;

    return 0;
}
