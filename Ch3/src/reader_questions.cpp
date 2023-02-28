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

int main()
{
    question_02();

    return 0;
}
