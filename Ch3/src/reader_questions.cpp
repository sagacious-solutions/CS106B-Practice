#include "console.h"
#include "random.h"
#include "simpio.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

/// ------------------------------------------------------------------------ Question 01 ---------------------------
/// Write a program that repeatedly generates a random real number between 0 and 1
/// and then displays the average after a certain number of runs, as illustrated by the
/// following sample run:
/// AverageRand
/// This program averages a series of random numbers
/// between 0 and 1.
/// How many trials: 10000
/// The average value after 10000 trials is 0.501493
/// If the random number generator is working well, the average should get closer to 0.5
/// as the number of trials increases.
void question_01()
{
    int howMany = getInteger("Please enter an integer value for amount of numbers to generate : ");
    int howTimesMany = getInteger(
        "Please enter an integer value for how many times to regenerate : ");
    double totalNum = 0.0;

    for (int h = 0; h < howTimesMany; h++) {
        for (int i = 0; i < howMany; i++) {
            totalNum += randomReal(0.0, 1.0);
        }

        cout << "The average number is " << totalNum / howMany << endl;
        totalNum = 0;
    }
}

/// ------------------------------------------------------------------------ Question 02 ---------------------------
///
/// Write a program that simulates flipping a coin repeatedly and continues until three
/// consecutive heads are tossed. At that point, your program should display the total
/// number of coin flips that were made. The following is one possible sample run of
/// the program:
void howManyFlips(int consecutiveHeads);

void question_02()
{
    howManyFlips(3);
    howManyFlips(5);
    howManyFlips(10);
}

void howManyFlips(int consecutiveHeads)
{
    int coinFlips = 0;
    int headsCount = 0;

    while (true) {
        bool coinFlip = randomBool();
        coinFlips++;

        // Heads is true
        if (coinFlip) {
            cout << "heads" << endl;
            headsCount++;
            if (headsCount >= consecutiveHeads)
                break;
        } else {
            cout << "tails" << endl;
            headsCount = 0;
        }
    }
    cout << "It took " << coinFlips << " coinflips to get " << consecutiveHeads
         << " consecutive heads." << endl;
}

/// ------------------------------------------------------------------------ Question 03 ---------------------------
/// Create a slot machine program

enum slotSymbolT { CHERRY, LEMON, ORANGE, PLUM, BELL, BAR };
const int SYMBOL_COUNT = 6;

slotSymbolT cherry = CHERRY;
slotSymbolT lemon = LEMON;
slotSymbolT orange = ORANGE;
slotSymbolT plum = PLUM;
slotSymbolT bell = BELL;
slotSymbolT bar = BAR;

struct gameOutcomeT
{
    slotSymbolT gameOutcome[3];
    int symbolCount[SYMBOL_COUNT] = {0, 0, 0, 0, 0, 0};
    int winnings = 0;
};

bool yesPlay(int bank);
void getSlots(gameOutcomeT *outcome);
int getWinnings(gameOutcomeT outcome);
void outputOutcome(gameOutcomeT *outcome);

void question_03()
{
    int bank = 50;

    while (true) {
        if (!yesPlay(bank))
            break;

        bank -= 1;

        gameOutcomeT *outcome = new gameOutcomeT;

        getSlots(outcome);
        outcome->winnings = getWinnings(*outcome);
        bank += outcome->winnings;
        outputOutcome(outcome);
    }
}

/// Wrote this with the enums only to discover they don't work in a switch statement
/// Next time the better solution would be to just use const int values for each type
void outputOutcome(gameOutcomeT *outcome)
{
    cout << right;
    for (int i = 0; i < 3; i++) {
        switch (outcome->gameOutcome[i]) {
        case 0:
            cout << "CHERRY" << setw(10);
            break;
        case 1:
            cout << "LEMON" << setw(10);

            break;
        case 2:
            cout << "ORANGE" << setw(10);

            break;
        case 3:
            cout << "PLUM" << setw(10);

            break;
        case 4:
            cout << "BELL" << setw(10);

            break;
        case 5:
            cout << "BAR" << setw(10);
            break;
        }
    }
    cout << " -- ";
    if (outcome->winnings) {
        cout << "You win $" << outcome->winnings << endl;
        return;
    }
    cout << "You lose" << endl;
}

int getWinnings(gameOutcomeT outcome)
{
    if (outcome.symbolCount[bar] == 3) {
        return 250;
    }
    if (outcome.symbolCount[bell] == 3
        || (outcome.symbolCount[bell] == 2 && outcome.symbolCount[bar] == 1)) {
        return 20;
    }
    if (outcome.symbolCount[plum] == 3
        || (outcome.symbolCount[plum] == 2 && outcome.symbolCount[bar] == 1)) {
        return 14;
    }
    if (outcome.symbolCount[orange] == 3
        || (outcome.symbolCount[orange] == 2 && outcome.symbolCount[bar] == 1)) {
        return 10;
    }

    switch (outcome.symbolCount[cherry]) {
    case 1:
        return 2;
    case 2:
        return 5;
    case 3:
        return 7;
    }
    return 0;
}

/**
 * @brief getSlots populates the outcome variable with the 3 slot symbols for the game
 * @param outcome[out] value to store the games outcome in
 */
void getSlots(gameOutcomeT *outcome)
{
    for (int i = 0; i < 3; i++) {
        int symbolNum = randomInteger(0, SYMBOL_COUNT - 1);
        outcome->symbolCount[symbolNum]++;
        outcome->gameOutcome[i] = slotSymbolT(symbolNum);
    }
}

bool yesPlay(int bank)
{
    ostringstream oss;
    oss << "You have $" << bank << ". Would you like to play? ";
    while (true) {
        string yesNo = getLine(oss.str());

        switch (tolower(yesNo[0])) {
        case 'y':
            return true;
        case 'n':
            return false;
        }

        cout << "Invalid input. You must enter either Yes,No,y,n." << endl;
    }
}
int main()
{
    question_03();

    return 0;
}
