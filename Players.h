#ifndef PROJETQUARTDESINGE_PLAYERS_H
#define PROJETQUARTDESINGE_PLAYERS_H


/**
 * @file Players.h
 * SAÉ S1.02 : The Quarter Monkey
 * @authors PROUX Clothilde
 * @version finale - 18/01/2023
 * @brief All player functions.
 * Comparison of algorithmic approaches -- BUT Paris - Rives de Seine
*/


/**
 * @brief Players data structure
 */
struct Players {
    int noPlayers;
    char *players;
    unsigned int currentPlayer;
    unsigned int previousPlayer;
    unsigned int losingPlayer;
    float *scoresPlayers;
};


/**
 * @brief The player abandons the round.
 * @param[in,out] playerRound -> the structure containing the players, their number and their score
 */
void quitRound(Players &playerRound);


/**
 * @brief The player asks the previous player what word they were thinking of.
 * @param[in,out] playerRound -> the structure containing the players, their number and their score
 * @param[in] lettersPlayed -> the list of letters already played by previous players
 */
void previousPlayerResponse(Players &playerRound, const char *lettersPlayed);


/**
 * @brief Checks if the letter played by the player belongs to the dictionary.
 * @param[in,out] playerRound -> the structure containing the players, their number and their score
 * @param[in] lettersPlayed -> the list of letters already played by previous players
 * @param[in] movePlayed -> the move made by the current player
 */
bool lettersPlayedHuman(Players &playerRound, char *lettersPlayed, const char movePlayed);


/**
 * @brief Enter the nature of the current player.
 * @param[in,out] playerRound -> the structure containing the players, their number and their score
 * @param[in] lettersPlayed -> the list of letters already played by previous players
 * @return movePlayed -> the move made by the current player
 */
char currentPlayerGame(Players &playerRound, const char *lettersPlayed);


/**
 * @brief The player who was asked for the word they were thinking of either wins the round or not.
 * @param[in,out] playerRound -> the structure containing the players, their number and their score
 * @param[in] lettersPlayed -> the list of letters already played by previous players
 */
void previousHumanResponse(Players &playerRound, const char *lettersPlayed);


/**
 * @brief Displays the word the robot was "thinking" about
 * @param[in,out] playerRound -> the structure containing the players, their number and their score
 * @param[in] lettersPlayed -> the list of letters already played by previous players
 */
void previousRobotResponse(Players &playerRound, const char *lettersPlayed);


/**
 * @brief Checks whether the letter entered is correct.
 * @param[in,out] playerRound -> the structure containing the players, their number and their score
 * @param[in] lettersPlayed -> the list of letters already played by previous players
 * @param[in] movePlayed -> the move made by the current player
 * @return goodLetter -> the boolean that checks if the letter is correct
 */
bool lettersPlayedCurrentPlayer(Players &playerRound, char *lettersPlayed, const char movePlayed);


/**
 * @brief Play a round.
 * @param[in,out] playerRound -> the structure containing the players, their number and their score
 */
void round(Players &playerRound);


/**
 * @brief Play a full game.
 * @param[in,out] playerRound -> the structure containing the players, their number and their score
 */
void game(Players &playerRound);


#endif //PROJETQUARTDESINGE_PLAYERS_H
