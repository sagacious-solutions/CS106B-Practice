#include <console.h>

using namespace std;

bool randomChnc(double chance)
{
    int intChance = chance * 100;
    int randomInt = rand() % 100;

    return (intChance >= randomInt);
}

int randomInt(int min, int max)
{
    int randomNum = rand();
    int num = randomNum % (max - min);
    return num + min;
}

// ************************************************ Question 01 ************************************************

//Spherical objects, such as cannonballs, can be stacked to form a pyramid with one
//cannonball at the top, sitting on top of a square composed of four cannonballs, sitting
//on top of a square composed of nine cannonballs, and so forth. Write a recursive
//function Cannonball that takes as its argument the height of the pyramid and returns
//the number of cannonballs it contains. Your function must operate recursively and
//must not use any iterative constructs, such as while or for .

int cannonBall(int height);
void outputResult(int height, int balls);

void question_01()
{
    int heightOne = cannonBall(1);
    outputResult(1, heightOne);
    int heightTwo = cannonBall(2);
    outputResult(2, heightTwo);
    int heightThree = cannonBall(3);
    outputResult(3, heightThree);
    int heightFifty = cannonBall(50);
    outputResult(50, heightFifty);
}

/**
 * @brief outputResult Outputs an easily readable string with results for cannonBall fn
 * @param height
 * @param balls
 */
void outputResult(int height, int balls)
{
    cout << "Height of " << height << " results in " << balls << " balls total." << endl;
}

/**
 * @brief cannonBall given a pyramid of cannon balls where each level contains its heigh in balls squared
 * This function will tell you the total ammount of cannon balls.
 * @param height of pyramid
 * @return Total count of balls
 */
int cannonBall(int height)
{
    if (height == 1) {
        return 1;
    } else {
        return cannonBall(height - 1) + height * height;
    }
}

// ************************************************ Question 02 ************************************************
///Unlike many programming languages, C++ does not include a predefined operator
///that raises a number to a power. As a partial remedy for this deficiency, write a
///recursive implementation of a function
///int RaiseIntToPower(int n, int k)

int raisePower(int n, int k);

void question_02()
{
    cout << "3 Squared should be 9 : " << raisePower(3, 2) << endl;
    cout << "9 squared should be 81 : " << raisePower(9, 2) << endl;
    cout << "4^4 should be 256 : " << raisePower(4, 4) << endl;
}

/**
 * @brief raisePower Get the answer to n to the kth power
 * @param n Number
 * @param k Power
 * @return Calculated answer
 */
int raisePower(int n, int k)
{
    if (k == 0) {
        return 1;
    } else {
        return n * raisePower(n, k - 1);
    }
}

// ************************************************ Question 02 ************************************************
///The greatest common divisor (g.c.d.) of two nonnegative integers is the largest
///integer that divides evenly into both. In the third century B . C ., the Greek
///mathematician Euclid discovered that the greatest common divisor of x and y can
///always be computed as follows:
///• If x is evenly divisible by y, then y is the greatest common divisor.
///• Otherwise, the greatest common divisor of x and y is always equal to the greatest
///common divisor of y and the remainder of x divided by y.
///Use Euclid’s insight to write a recursive function GCD(x, y) that computes the
///greatest common divisor of x and y.

int GCD(int x, int y);
void gcdWrap(int x, int y);

void question_03()
{
    gcdWrap(10, 5);
    gcdWrap(100, 26);
    gcdWrap(234234, 2345);
}

/**
 * @brief gcdWrap Wraps GCD to output the values being calculated and answer
 * @param x
 * @param y
 */
void gcdWrap(int x, int y)
{
    cout << "GCD of " << x << ", " << y << " is " << GCD(x, y) << endl;
}

/**
 * @brief GCD Gets the greatest common devisor os x and y
 * @param x
 * @param y
 * @return The calculated greatest devisor
 */
int GCD(int x, int y)
{
    if (x % y == 0) {
        return y;
    } else {
        return GCD(y, x % y);
    }
}

int main()
{
    srand(time(0));
    question_03();
    return 0;
}
