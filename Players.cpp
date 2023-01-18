/**
 * @file Players.cpp
 * SAÉ S1.02 : The Quarter Monkey
 * @authors PROUX Clothilde
 * @version finale - 18/01/2023
 * @brief Players' functions.
 * Comparison of algorithmic approaches -- BUT Paris - Rives de Seine
*/

#include <iostream>
#include <iomanip> // for setw
#include <cstdlib> // for rand
#include "Players.h" // Players structure
#include "Game.h" // Functions of the game


using namespace std;
const int MAX_WORD = 26;


/**
 * @brief The player abandons the round.
 * @param[in,out] playerRound -> the structure containing the players, their number and their score
 */
void quitRound(Players &playerRound) {
    playerRound.scoresPlayers[playerRound.currentPlayer - 1] += 0.25;
    playerRound.losingPlayer = playerRound.currentPlayer;
    cout << "the player " << playerRound.currentPlayer
         << (char) toupper(playerRound.players[playerRound.currentPlayer - 1])
         << " gives up the round and takes a quarter monkey" << endl;
}


/**
 * @brief The player asks the previous player what word they were thinking of.
 * @param[in,out] playerRound -> the structure containing the players, their number and their score
 * @param[in] lettersPlayed -> the list of letters already played by previous players
 */
void previousPlayerResponse(Players &playerRound, const char *lettersPlayed) {
    playerRound.previousPlayer = playerRound.currentPlayer - 1;
    if (playerRound.previousPlayer == 0) playerRound.previousPlayer = playerRound.noPlayers;
    // The first player asks the last
    cout << playerRound.previousPlayer
         << (char) toupper(playerRound.players[playerRound.previousPlayer - 1]) << ", enter the word > ";

    if (toupper(playerRound.players[playerRound.previousPlayer - 1]) == 'H') // Human player
        previousHumanResponse(playerRound, lettersPlayed);
    else // Robot player
        previousRobotResponse(playerRound, lettersPlayed);
    playerRound.scoresPlayers[playerRound.losingPlayer - 1] += 0.25;
}


/**
 * @brief Checks if the letter played by the player belongs to the dictionary.
 * @param[in,out] playerRound -> the structure containing the players, their number and their score
 * @param[in] lettersPlayed -> the list of letters already played by previous players
 * @param[in] movePlayed -> the move made by the current player
 */
bool lettersPlayedHuman(Players &playerRound, char *lettersPlayed, const char movePlayed) {
    bool goodLetter = true;

    if (toupper(movePlayed) >= 65 && toupper(movePlayed) <= 90) { // The letter is unaccented
        if (strlen(lettersPlayed) < MAX_WORD - 1)
            lettersPlayed[strlen(lettersPlayed)] = (char) toupper(movePlayed);
        if (strlen(lettersPlayed) > 2) { // Tested word from three letters
            if (belongsDico(lettersPlayed)) {
                cout << "the word " << lettersPlayed << " exists, the player " << playerRound.currentPlayer
                     << (char) toupper(playerRound.players[playerRound.currentPlayer - 1])
                     << " takes a quarter monkey" << endl;
                playerRound.scoresPlayers[playerRound.currentPlayer - 1] += 0.25;
                playerRound.losingPlayer = playerRound.currentPlayer;
                goodLetter = false;
            }
        }
    }
    else {
        cout << "please enter a non-emphasis letter" << endl;
        playerRound.currentPlayer--;
    }
    return goodLetter;
}


/**
 * @brief Enter the nature of the current player.
 * @param[in,out] playerRound -> the structure containing the players, their number and their score
 * @param[in] lettersPlayed -> the list of letters already played by previous players
 * @return movePlayed -> the move made by the current player
 */
char currentPlayerGame(Players &playerRound, const char *lettersPlayed) {
    char movePlayed;

    if (playerRound.currentPlayer > playerRound.noPlayers) playerRound.currentPlayer = 1;
    // the player after the last is first
    cout << playerRound.currentPlayer << (char) toupper(playerRound.players[playerRound.currentPlayer - 1])
         << ", (" << lettersPlayed << ") > ";
    if (toupper(playerRound.players[playerRound.currentPlayer - 1]) == 'H') { // Human player
        cin >> movePlayed;
        cin.ignore(INT_MAX, '\n');
    }
    else if (toupper(playerRound.players[playerRound.currentPlayer - 1]) == 'R') { // Robot player
        movePlayed = robotGame(lettersPlayed);
        cout << movePlayed << endl;
    }
    else { // Alien player
        cerr << "invalid player. please replay a game" << endl;
        exit(1);
    }
    return movePlayed;
}


/**
 * @brief The player who was asked for the word they were thinking of either wins the round or not.
 * @param[in,out] playerRound -> the structure containing the players, their number and their score
 * @param[in] lettersPlayed -> the list of letters already played by previous players
 */
void previousHumanResponse(Players &playerRound, const char *lettersPlayed) {
    char wordEntered[MAX_WORD];
    bool win;

    cin >> setw(MAX_WORD) >> wordEntered;
    cin.ignore(INT_MAX, '\n');
    for (int i = 0; i < strlen(wordEntered); i++) { // Capitalise the word entered
        wordEntered[i] = (char) toupper(wordEntered[i]);
    }
    if (strncmp(wordEntered, lettersPlayed, strlen(lettersPlayed)) != 0) {
        // If it doesn't start with the letters already played
        cout << "the word " << wordEntered << " does not start with the expected letters, the player "
             << playerRound.previousPlayer << (char) toupper(playerRound.players[playerRound.previousPlayer - 1])
             << " takes a quarter monkey" << endl;
        win = false;
    }
    else {
        // Check if the word is in the dictionary
        if (belongsDico(wordEntered)) { // The word belongs in the dictionary
            cout << "the word " << wordEntered << " exists, the player " << playerRound.currentPlayer
                 << (char) toupper(playerRound.players[playerRound.currentPlayer - 1]) << " takes a quarter monkey" << endl;
            win = true;
        }
        else { // The word does not belong to
            cout << "the word " << wordEntered << " does not exist, the player " << playerRound.previousPlayer
                 << (char) toupper(playerRound.players[playerRound.previousPlayer - 1])
                 << " takes a quarter monkey" << endl;
            win = false;
        }
    }
    if (win)
        playerRound.losingPlayer = playerRound.currentPlayer;
    else
        playerRound.losingPlayer = playerRound.previousPlayer;
}


/**
 * @brief Displays the word the robot was "thinking" about
 * @param[in,out] playerRound -> the structure containing the players, their number and their score
 * @param[in] lettersPlayed -> the list of letters already played by previous players
 */
void previousRobotResponse(Players &playerRound, const char *lettersPlayed) {
    ifstream dico = dicoOpening();

    char wordRead[MAX_WORD];
    char wordFound[MAX_WORD] = "";
    dico >> setw(MAX_WORD) >> wordRead;
    while (dico) {
        if (strncmp(lettersPlayed, wordRead, strlen(lettersPlayed)) == 0) {
            // Find a word that begins with the letters played
            strcpy(wordFound, wordRead);
            cout << wordFound << endl;
            cout << "the word " << wordFound << " exists, the player " << playerRound.currentPlayer
                 << (char) toupper(playerRound.players[playerRound.currentPlayer - 1])
                 << " takes a quarter monkey" << endl;
            break;
        }
        dico >> setw(MAX_WORD) >> wordRead;
    }
    dico.close();
    playerRound.losingPlayer = playerRound.currentPlayer;
}


/**
 * @brief Checks whether the letter entered is correct.
 * @param[in,out] playerRound -> the structure containing the players, their number and their score
 * @param[in] lettersPlayed -> the list of letters already played by previous players
 * @param[in] movePlayed -> the move made by the current player
 * @return goodLetter -> the boolean that checks if the letter is correct
 */
bool lettersPlayedCurrentPlayer(Players &playerRound, char *lettersPlayed, const char movePlayed) {
    bool goodLetter = true;

    if (toupper(playerRound.players[playerRound.currentPlayer - 1]) == 'H')  // By a human
        goodLetter = lettersPlayedHuman(playerRound, lettersPlayed, movePlayed);
    else { // By a robot
        lettersPlayed[strlen(lettersPlayed)] = movePlayed;
    }
    return goodLetter;
}


/**
 * @brief Play a round.
 * @param[in,out] playerRound -> the structure containing the players, their number and their score
 */
void round(Players &playerRound) {
    char movePlayed;
    char lettersPlayed[MAX_WORD] = "";
    bool finishedRound = false;

    while (!finishedRound) {
        movePlayed = currentPlayerGame(playerRound, lettersPlayed);

        // Possible moves
        if (movePlayed == '!') { // Abandonment of the round
            quitRound(playerRound);
            finishedRound = true;
        }
        else if (movePlayed == '?') { // Request word from previous player
            previousPlayerResponse(playerRound, lettersPlayed);
            finishedRound = true;
        }
        else { // Letter played → Add a letter to those already played
            if (!lettersPlayedCurrentPlayer(playerRound, lettersPlayed, movePlayed))
                finishedRound = true;
        }
        playerRound.currentPlayer++;
    }
}


/**
 * @brief Play a full game.
 * @param[in,out] playerRound -> the structure containing the players, their number and their score
 */
void game(Players &playerRound) {
    playerRound.scoresPlayers = new float[playerRound.noPlayers];
    playerRound.currentPlayer = 1;
    for (int j = 0; j < playerRound.noPlayers; ++j) playerRound.scoresPlayers[j] = 0.;
    // Sets scores to zero

    do {
        round(playerRound);
        playerRound.currentPlayer = playerRound.losingPlayer;
        for (int i = 1; i <= playerRound.noPlayers; ++i) {
            cout << i << (char) toupper(playerRound.players[i - 1]) << " : " << playerRound.scoresPlayers[i - 1];
            if (i != playerRound.noPlayers)
                cout << "; ";
            else
                cout << endl;
        }
    } while (playerRound.scoresPlayers[playerRound.losingPlayer - 1] != 1.);
    cout << "The game is over" << endl;
}