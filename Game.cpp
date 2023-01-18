/**
 * @file game.cpp
 * SAÉ S1.02 : The Quarter Monkey
 * @authors PROUX Clothilde
 * @version finale - 18/01/2023
 * @brief Game's functions.
 * Comparison of algorithmic approaches -- BUT Paris - Rives de Seine
*/

#include <iostream>
#include <iomanip> // for setw
#include <cstdlib> // for rand
#include "Game.h" // Game's fonctions

using namespace std;
const int MAX_WORD = 26;



/**
 * @brief Open the dictionary.
 * @return dico -> the said dictionary
 */
ifstream dicoOpening() {
    ifstream dico("ods4.txt",ios::in | ios::binary);

    if (!dico) {
        cerr << "The dictionary could not be opened" << endl;
        exit(2);
    }
    return dico;
}


/**
 * @brief Checks if the word entered belongs to the dictionary.
 * @param[in] wordSearched -> word entered by the player
 * @return 0 -> the word does not belong ; 1 -> it belongs to ; 2 -> the dictionary did not open
 */
bool belongsDico(const char wordSearched[]) {
    ifstream dico = dicoOpening();
    bool found = false;
    char wordRead[MAX_WORD];

    dico >> setw(MAX_WORD) >> wordRead;
    while (dico) {
        if (strcmp(wordSearched, wordRead) == 0) { // The word searched belongs to the dictionary
            found = true;
        }
        else if (strcmp(wordSearched, wordRead) < 0) { // The word read is listed in alphabetical order after the word searched
            break; // The word does not belong in the dictionary. We leave the loop
        }
        dico >> setw(MAX_WORD) >> wordRead;
    }
    dico.close();
    return found;
}


/**
 * @brief Gives the next move of a robot player.
 * @param[in] lettersPlayed -> the structure containing the players, their number and their score
 * @return movePlayed -> the move made by the current player
 */
char robotGame(const char *lettersPlayed) {
    ifstream dico = dicoOpening();
    char movePlayed;
    char wordRead[MAX_WORD];
    char wordFound[MAX_WORD] = "";
    char startWordForbidden[MAX_WORD] = "";

    dico >> setw(MAX_WORD) >> wordRead;
    if (strlen(lettersPlayed) == 0) { // The robot plays first
        movePlayed = (char) (rand() % 26 + 65); // He pulls out a random letter
    }
    else {
        while (dico) {
            if (strncmp(lettersPlayed, wordRead, strlen(lettersPlayed)) == 0
                // If the first letters of the word read match the letters played
                && (strncmp(wordRead, startWordForbidden, strlen(startWordForbidden)) != 0
                || strlen(startWordForbidden) == 0)) {
                // And that it doesn't start with the forbidden letters or that there aren't any
                if (strlen(wordRead) == strlen(lettersPlayed) + 1) {
                    // Not to give a letter that would end a word
                    strcpy(startWordForbidden, wordRead);
                }
                else if (strlen(wordRead) > strlen(lettersPlayed) + 1
                         && (strlen(wordFound) == 0 || strlen(wordFound) > strlen(wordRead))) {
                    // To find the shortest word
                    strcpy(wordFound, wordRead);
                }
            }
            else if (strncmp(lettersPlayed, wordRead, strlen(lettersPlayed)) < 0) {
                // The word read is arranged in alphabetical order after the letters played
                break;
            }
            dico >> setw(MAX_WORD) >> wordRead;
        }

        if (strlen(wordFound) == 0) // No words were found
            movePlayed = '?';
        else
            movePlayed = wordFound[strlen(lettersPlayed)];
        dico.close();
    }
    return movePlayed;
}