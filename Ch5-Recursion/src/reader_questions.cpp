#include <console.h>
#include <iomanip>
#include <iostream>
#include <vector.h>

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

// ************************************************ Question 03 ************************************************
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

// ************************************************ Question 04 ************************************************
//Write an iterative implementation of the function Fib(n)

/*
* Constants
* ---------
* MIN_INDEX -- Index of first term to generate
* MAX_INDEX -- Index of last term to generate
*/

const int MIN_INDEX = 0;
const int MAX_INDEX = 12;

/* Private function prototypes */

int FibIt(int n);
int FibRe(int n);

void question_04()
{
    cout << "This question lists the Fibonacci sequence." << endl;
    for (int i = MIN_INDEX; i <= MAX_INDEX; i++) {
        cout << "Fib(" << i << ")";
        if (i < 10)
            cout << " ";
        cout << " = " << FibRe(i) << endl;
    }

    cout << endl << endl;

    for (int i = MIN_INDEX; i <= MAX_INDEX; i++) {
        cout << "Fib(" << i << ")";
        if (i < 10)
            cout << " ";
        cout << " = " << FibIt(i) << endl;
    }
}

/**
 * @brief FibIt Fibonacci sequence calculated iteratively
 * @param n Factor to calculate to
 * @return The calculated number
 */
int FibIt(int n)
{
    int fib = 1;
    int prevFib = 1;
    int temp;

    if (n <= 1) {
        return n;
    }

    for (int i = 2; i < n; i++) {
        temp = fib;
        fib += prevFib;
        prevFib = temp;
    }
    return fib;
}

/**
 * @brief FibIt Fibonacci sequence calculated recursively
 * @param n Factor to calculate to
 * @return The calculated number
 */
int FibRe(int n)
{
    if (n < 2) {
        return n;
    } else {
        return FibRe(n - 1) + FibRe(n - 2);
    }
}

// ************************************************ Question 05 ************************************************
///For each of the two recursive implementations of the function Fib(n) presented in
///this chapter, write a recursive function (you can call these CountFib1 and
///CountFib2 for the two algorithms) that counts the number of function calls made
///during the evaluation of the corresponding Fibonacci calculation. Write a main
///program that uses these functions to display a table showing the number of calls
///made by each algorithm for various values of n , as shown in the following sample
///run:

int countFib1(int n, int &count);
void outputRow(int n, int fib1, int fib2);
int AdditiveSequence(int n, int t0, int t1, int &runCount);
int countFib2(int n, int &runCount);

void question_05()
{
    int *fib1Count = new int;
    *fib1Count = 0;
    int *fib2Count = new int;
    *fib2Count = 0;

    cout << "This program compares the performance of two algorithms to compute the Fibonacci "
            "sequence."
         << endl
         << "Number of calls:" << endl
         << right << setw(3) << "N" << setw(10) << "Fib1" << setw(7) << "Fib2" << endl
         << right << setw(3) << "--" << setw(10) << "----" << setw(7) << "----" << endl;

    // Runs the fibonachi function twice on each loop with 2 different algorithms.
    // Counts the recursive calls to the functions and displays it.
    for (int i = MIN_INDEX; i <= MAX_INDEX; i++) {
        countFib1(i, *fib1Count);
        countFib2(i, *fib2Count);
        outputRow(i, *fib1Count, *fib2Count);
        *fib1Count = 0;
        *fib2Count = 0;
    }
}

/**
 * @brief outputRow outputs the data with the correct formatting for each iteration of the question_05 loop
 * @param n Iterations to run function on
 * @param fib1 Times first recursive function ran
 * @param fib2 Times the second resursive function ran
 */
void outputRow(int n, int fib1, int fib2)
{
    cout << right << setw(3) << n << setw(10) << fib1 << setw(7) << fib2 << endl;
}

/**
 * @brief countFib1 Recursive fib function from the reader with counter pointer added
 * @param n
 * @param count
 * @return 
 */
int countFib1(int n, int &count)
{
    count++;
    if (n < 2) {
        return n;
    } else {
        return countFib1(n - 1, count) + countFib1(n - 2, count);
    }
}

/**
 * @brief countFib2 Another Recursive fib function from the reader with counter pointer added
 * @param n
 * @param count
 * @return 
 */
int countFib2(int n, int &runCount)
{
    return AdditiveSequence(n, 0, 1, runCount);
}

/**
 * @brief AdditiveSequence Another Recursive fib function from the reader with counter pointer added
 * @param n
 * @param count
 * @return 
 */
int AdditiveSequence(int n, int t0, int t1, int &runCount)
{
    runCount++;
    if (n == 0)
        return t0;
    if (n == 1)
        return t1;
    return AdditiveSequence(n - 1, t1, t0 + t1, runCount);
}

// ************************************************ Question 06 ************************************************
///Write a recursive function DigitSum(n) that takes a nonnegative integer and returns
///the sum of its digits. For example, calling DigitSum(1729) should return
///1 + 7 + 2 + 9, which is 19.
int DigitSumGPT(int n);
int digitSum(int n, int sum = 0);
void digitSumOutputWrapper(int n, int expected);

void question_06()
{
    digitSumOutputWrapper(2, 11);
    digitSumOutputWrapper(222, 6);
    digitSumOutputWrapper(12345, 15);
    digitSumOutputWrapper(99999, 45);
}

/**
 * @brief digitSumOutputWrapper Output wrapper, stop gap before switching to test suite
 * @param n Number being summed
 * @param expected Expected output
 */
void digitSumOutputWrapper(int n, int expected)
{
    cout << "My digitSum of " << n << " should be " << expected << " : " << digitSum(n) << endl;
    cout << "GPT digitSum of " << n << " should be " << expected << " : " << DigitSumGPT(n) << endl;
}

/**
 * @brief digitSum my implementation being worried the base case of less than 10 would be factored farther
 * @param n Number to sum
 * @param sum current sum tracked across function calls
 * @return sum of digits
 */
int digitSum(int n, int sum)
{
    if (n == 0) {
        return sum;
    } else {
        return digitSum(n / 10, (sum + (n % 10)));
    }
}

/**
 * @brief DigitSumGPT ChatGPTs implementation to check against mine
 * @param n Number to sum
 * @return sum of digits
 */
int DigitSumGPT(int n)
{
    // Base case: If n is less than 10, return n as it is the only digit.
    if (n < 10) {
        return n;
    }

    // Recursive case: Calculate the sum of the last digit and the sum of the remaining digits.
    int last_digit = n % 10;
    int remaining_digits = n / 10;

    return last_digit + DigitSumGPT(remaining_digits);
}

// ************************************************ Question 07 ************************************************
///The digital root of an integer n is defined as the result of summing the digits
///repeatedly until only a single digit remains. For example, the digital root of 1729
///can be calculated using the following steps:
///Step 1: 1 + 7 + 2 + 9 → 19
///Step 2: 1 + 9 → 10
///Step 3: 1 + 0 → 1

int digitalRoot(int n);
void digitRootOutputWrapper(int n, int expected);

void question_07()
{
    digitRootOutputWrapper(1729, 1);
    digitRootOutputWrapper(999, 9);
}

/**
 * @brief digitRootOutputWrapper Output wrapper for easy display
 * @param n
 * @param expected
 */
void digitRootOutputWrapper(int n, int expected)
{
    cout << "digitalRoot of " << n << " should be " << expected << " : " << digitalRoot(n) << endl;
}

/**
 * @brief digitalRoot Gets the digital root as described above
 * @param n Number to get digital root for
 * @return The digital root
 */
int digitalRoot(int n)
{
    n = digitSum(n);
    // Base case: If n is less than 10, return n as it is the only digit.
    if (n < 10) {
        return n;
    }
    return digitalRoot(n);
}

// ************************************************ Question 09 ************************************************

///Write a recursive function that takes a string as argument and returns the reverse of
///that string. The prototype for this function should be
///string Reverse(string str);
///and the statement
///cout << Reverse("program") << endl;
///should display
///ReverseString
///margorp
///Your solution should be entirely recursive and should not use any iterative constructs
///such as while or for

void reReverseOutputWrapper(string str);
string reReverse(string str);

void question_09()
{
    reReverseOutputWrapper("Hello World");
    reReverseOutputWrapper("Mississippi");
}

void reReverseOutputWrapper(string str)
{
    cout << "The string " << str << " reversed is " << reReverse(str) << endl;
}

/**
 * @brief reReverse Recursive string reverse
 * @param str String to reverse
 * @return the reversed string
 */
string reReverse(string str)
{
    // Base case, Return the only remaining character
    if (str.length() == 1) {
        return str;

        // Recursive Case : Return the last index of str, then add run the function again with a substring missing the last char
    } else {
        return str[str.length() - 1] + reReverse(str.substr(0, str.length() - 1));
    }
}

// ************************************************ Question 10 ************************************************

///The strutils.h library contains a function IntegerToString ,. You might have
///wondered how the computer actually goes about the process of converting an integer
///into its string representation. As it turns out, the easiest way to implement this
///function is to use the recursive decomposition of an integer outlined in exercise 6.
///Rewrite the IntegerToString implementation so that it operates recursively without
///using use any of the iterative constructs such as while and for

void reIntToStringOutputWrapper(int n);
string reIntToString(int n);

void question_10()
{
    reIntToStringOutputWrapper(12345);
    reIntToStringOutputWrapper(100000);
    reIntToStringOutputWrapper(99999);
}

void reIntToStringOutputWrapper(int n)
{
    cout << "The number " << n << " is " << reIntToString(n) << " as a string. " << endl;
}

/**
 * @brief reIntToString Recursive convert integer to string
 * @param n Number to convert to string
 * @return String representation of n
 */
string reIntToString(int n)
{
    // Modulo gets last digit, convert to char offset by ascii 0
    const string numChar(1, char('0' + (n % 10)));

    // Base case : If less than 10, return n offset by the ASCII code for zero
    if (n < 10) {
        return numChar;
    }
    // Recursive Case : Get the next recursive case with the current number added as a string onto the back of its return
    return reIntToString(n / 10) + numChar;
}

int main()
{
    srand(time(0));
    question_10();
    return 0;
}
