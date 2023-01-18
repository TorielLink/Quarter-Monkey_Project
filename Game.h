#ifndef PROJETQUARTDESINGE_GAME_H
#define PROJETQUARTDESINGE_GAME_H


/**
 * @file game.h
 * SAÉ S1.02 : The Quarter Monkey
 * @authors PROUX Clothilde
 * @version finale - 18/01/2023
 * @brief All game's functions.
 * Comparison of algorithmic approaches -- BUT Paris - Rives de Seine
*/


#include <iostream>
#include <fstream> // for ifstream
#include <iomanip> // for setw
#include <cstdlib> // for rand

using namespace std;


/**
 * @brief Open the dictionary.
 * @return dico -> the said dictionary
 */
ifstream dicoOpening();


/**
 * @brief Checks if the word entered belongs to the dictionary.
 * @param[in] wordSearched -> word entered by the player
 * @return 0 -> the word does not belong ; 1 -> it belongs to ; 2 -> the dictionary did not open
 */
bool belongsDico(const char wordSearched[]);


/**
 * @brief Gives the next move of a robot player.
 * @param[in] lettersPlayed -> the structure containing the players, their number and their score
 * @return movePlayed -> the move made by the current player
 */
char robotGame(const char *lettersPlayed);


#endif //PROJETQUARTDESINGE_GAME_H
