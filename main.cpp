/**
 * @file main.cpp
 * SAÉ S1.02 : The Quarter Monkey
 * @authors PROUX Clothilde
 * @version finale - 18/01/2023
 * @brief Playing a game of Monkey Quarter.
 * Comparison of algorithmic approaches -- BUT Paris - Rives de Seine
*/

#include <iostream>
#include "Players.h" // Players structure

using namespace std;

/**
 * @brief Main programme.
 * @param[in] argc -> number of parameters on the command line (+ 1)
 * @param[in] argv -> command line parameters (argv[0]: the command, argv[1]: the 1st parameter, etc.)
 * @return 0 -> the program ran smoothly.
 */
int main(int argc, const char* argv[]) {
    Players playerRound{};

    // Parameter on the command line
    if (argc >= 2) {
        if (strlen(argv[1]) > 1) {
            playerRound.noPlayers = (int) strlen(argv[1]);
            playerRound.players = new char[playerRound.noPlayers];
            strcpy(playerRound.players, argv[1]);
            game(playerRound);
        }
        else
            cout << "At least two players are required" << endl;
    }
    else
        cout << "There are no parameters" << endl;
    return 0;
}