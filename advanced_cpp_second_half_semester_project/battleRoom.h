/*
 *Author: Carson Allbee
 *Date: 4/9/23
 *Email: callbee@dmacc.edu
 *This is a short room that utilizes the rand function to do battle with a slime enemy
*/

#ifndef BATTLEROOM_H
#define BATTLEROOM_H

#endif // BATTLEROOM_H

#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

int playerHealth = 15;
int slimeHealth = 8;
int MAX_ATTACK = 4;
int damageDealt;
string playerChoice;

//This function returns a random number between 1 and 4
int attack() {
    damageDealt = 1 + rand() % MAX_ATTACK;
    return damageDealt;
}

//This function takes in an int and returns that number halved and rounded to the nearest 1
int defend(int damage) {
    int damageDefended = round(damage / 2);
    return damageDefended;
}


int battleRoomMain() {

    cout << "You enter the room and notice that the ground has become slippery.\n"
            "You also notice sounds of something being dragged, these sounds are approaching you.\n"
            "After a few seconds a creature enters the light, it is a slime\n" << endl;
    cout << "What do you do?\n 1.Attack\n 2.Defend\n 3.Give Up" << endl;
    cin >> playerChoice;

    while (playerChoice != "3") {
        //if choice is 1 attack function is used
        if(playerChoice == "1") {
            cout << "You swing your fist at the slime" << endl;
            int playerDamage = attack();
            slimeHealth = slimeHealth - playerDamage;
            cout << "The slime pounces at you" << endl;
            int slimeDamage = attack();
            playerHealth = playerHealth - slimeDamage;
            // if the player's health fall to 0 or below end game is called
            if(playerHealth <= 0) {
                cout << "Oh No!" << endl;
                cout << "You fall to the slime and your journey ends here." << endl;
                break;
            }
            //player progresses if slime's health falls to 0 or below
            else if(slimeHealth <= 0) {
                cout << "Huzzah!" << endl;
                cout << "You fell the evil slime and can now pass on to the next room" << endl;
                break;
            }
    }
        //if choice is 2 defend function is called
        else if(playerChoice == "2") {
            cout << "You defend against the slime's attack" << endl;
            int slimeDamage = attack();
            damageDealt = defend(slimeDamage);
            playerHealth = playerHealth - damageDealt;
            if(playerHealth <= 0) {
                cout << "Oh No!" << endl;
                cout << "You fall to the slime and your journey ends here." << endl;
                break;
            }
            else if(slimeHealth <= 0) {
                cout << "Huzzah!" << endl;
                cout << "You fell the evil slime and can now pass on to the next room" << endl;
                break;
            }

        }

        //outputs player's and slime's health before asking for next loop iteration
        cout << "Player Health: " << playerHealth << endl;
        cout << "Slime Health: " << slimeHealth << endl;
        cout << "What do you do?\n 1.Attack\n 2.Defend\n 3.Give Up" << endl;
        cin >> playerChoice;
    }

    if (playerChoice == "3") {
        playerHealth = 0;
        cout << "You give up and become the slime's next meal" << endl;
    }

    if (playerHealth > 0) {
        cout << "You move on to the next room" << endl;
    }
    else {
        cout << "Your journey ends here and you cannot continue" << endl;
    }
    return 0;
}
