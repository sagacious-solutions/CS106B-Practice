//#include "console.h"
#include "random.h"
#include "simpio.h"
#include <cmath>
#include <iostream>
using namespace std;

string trueOrFalse(bool isTrue)
{
    if (isTrue) {
        return "True";
    }
    return "False";
}

/// ------------------------------------------------------------------ QUESTION 01 -----------------------------------------

//  Define an enumeration type weekdayT whose elements are the days of the week.
//  Write functions NextDay and PreviousDay that take a value of type weekdayT and
//  return the day of the week that comes after or before the specified day, respectively.
//
//  Also write a function IncrementDay(startDay, delta) that returns the day of the
//  week that comes delta days after startDay . Thus, IncrementDay(Thursday, 4)
//  should return Monday . Your implementation of IncrementDay should work if the
//  value of delta is negative, in which case it should proceed backward in time

enum weekdayT {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday,
};
weekdayT nextDay(weekdayT day);
weekdayT previousDay(weekdayT day);
weekdayT incrementDay(weekdayT day, int delta_days);
string getDayString(weekdayT day);

void question_01()
{
    weekdayT tue = Tuesday;
    string dayAfterTues = getDayString(nextDay(tue));

    cout << "The day after Tuesday is " << dayAfterTues << endl;

    weekdayT mon = Monday;
    string dayBeforeMon = getDayString(previousDay(mon));

    cout << "The day before Monday is " << dayBeforeMon << endl;

    int DAYS_AFTER = 6;
    weekdayT fri = Friday;
    string newDayStr = getDayString(incrementDay(fri, DAYS_AFTER));

    cout << newDayStr << " is " << DAYS_AFTER << " days after " << getDayString(fri) << endl;

    int DAYS_BEFORE = -62;
    string newDayStr2 = getDayString(incrementDay(fri, DAYS_BEFORE));

    cout << newDayStr2 << " is " << DAYS_BEFORE << " days before " << getDayString(fri) << endl;
}

/*
 * This function takes in a day and returns the next day
 *
 * @param day A day of the week
 * @returns the immediate following day
 */
weekdayT nextDay(weekdayT day)
{
    return weekdayT((day + 1) % 7);
}

/*
 * This function takes in a day and returns and returns the previous day
 *
 * @param day A day of the week
 * @returns the immediate previous day
 */
weekdayT previousDay(weekdayT day)
{
    if (day == 0) {
        return weekdayT(6);
    }

    return weekdayT((day - 1) % 7);
}

/*
 * This function takes in a day and returns a new day of delta_days difference
 *
 * @param day A day of the week
 * @param delta_days The amount of days to shift by
 * @returns the updated day value
 */
weekdayT incrementDay(weekdayT day, int deltaDays)
{
    // The extra + 7 % 7 corrects for negative deltas
    return weekdayT((((day + deltaDays) % 7) + 7) % 7);
}

/*
 * This function takes in a weekdayT enum and returns the string reperesentation 
 *
 * @param day A day of the week
 * @param delta_days The amount of days to shift by
 * @returns the updated day value
 */
string getDayString(weekdayT day)
{
    switch (day) {
    case Monday:
        return "Monday";
    case Tuesday:
        return "Tuesday";
    case Wednesday:
        return "Wednesday";
    case Thursday:
        return "Thursday";
    case Friday:
        return "Friday";
    case Saturday:
        return "Saturday";
    case Sunday:
        return "Sunday";
    default:
        return 0;
    }
}

/// ------------------------------------------------------------------------ Question 02 ---------------------------
/// Write a program that computes the surface area and volume of a cylinder, given the
//height (h) and radius of the base (r) as shown in the following diagram:
//The formulas for calculating surface area and volume are
//A = 2 π h r
//V = π h r 2
//In this exercise, design your main program so that it consists of three function
//calls: one to read the input data, one to compute the results, and one to display the
//answers. When appropriate, use call by reference to communicate data between the
//functions and the main program.

void calculateVolume(int h, int r, double *volume);
void calculateSurfaceArea(int h, int r, double *surfaceArea);
const double PI = 3.14159265359;

void question_02()
{
    int height = 0;
    int radius = 0;
    double *volume = new double;
    double *surfaceArea = new double;

    cout << "Input the cylinder height : ";
    cin >> height;
    cout << "Input the radius of the cylnder : ";
    cin >> radius;

    calculateVolume(height, radius, volume);

    cout << "The calculated volume is " << *volume << endl;

    calculateSurfaceArea(height, radius, surfaceArea);

    cout << "The calculated surface area is " << *surfaceArea;

    delete volume;
    delete surfaceArea;
}

// While the question says to use pointers, i would argue this is bad coding. You shouldn't mutate a volue inside a funciton, instead you should create a new value and
// return that value back so you can see clearly at the function call that its returning assigning the value it calculated
/*
 * This function calculates the volume of a cylinder
 * V = π h r 2
 *
 * @param h[in] height of the cylinder
 * @param r[in] the radius of the cylinder
 * @param *volume[out] Pointer for volume result
 */
void calculateVolume(int h, int r, double *volume)
{
    *volume = PI * h * (r * r);
}
/*
 * This function calculates the area of a cylinder
 *
 * @param h[in] height of the cylinder
 * @param r[in] the radius of the cylinder
 * @param *surfaceArea[out] Pointer for surface area result
 */
void calculateSurfaceArea(int h, int r, double *surfaceArea)
{
    *surfaceArea = (2 * PI * pow(r, 2)) + (2 * PI * r * h);
}

/// ------------------------------------------------------------------------ Question 04 ---------------------------
///
///  Write a predicate function IsSorted(array, n) that takes an integer array and its
///  effective size as parameters and returns true if the array is sorted in nondecreasing
///  order.
bool isSorted(int arr[], int n);

void question_04()
{
    int sortedArr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sortedArrSize = sizeof(sortedArr) / sizeof(sortedArr[0]);
    int unSortedArr[] = {5, 2, 10, 4, 9, 1};
    int unSortedArrSize = sizeof(unSortedArr) / sizeof(unSortedArr[0]);

    cout << "The sorted array is sorted : " << trueOrFalse(isSorted(sortedArr, sortedArrSize))
         << endl;
    cout << "The unsorted array is sorted : " << trueOrFalse(isSorted(unSortedArr, unSortedArrSize))
         << endl;
}

/*
 * This function calculates the area of a cylinder
 *
 * @param arr[in] arr of numbers
 * @param n[in] length of the arr
 * @returns True if its sorted in ascending order
 */
bool isSorted(int arr[], int n)
{
    int currentNum = -1;

    for (int i = 0; i < n; i++) {
        if (arr[i] < currentNum) {
            return false;
        }
        currentNum = arr[i];
    }

    return true;
}

/// ------------------------------------------------------------------------ Question 05 ---------------------------
/// In the third century B .C ., the Greek astronomer Eratosthenes developed an algorithm
/// for finding all the prime numbers up to some upper limit N. To apply the algorithm,
/// you start by writing down a list of the integers between 2 and N. For example, if N
/// were 20, you would begin by writing down the following list:
/// 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
/// Next you circle the first number in the list, indicating that you have found a prime.
/// You then go through the rest of the list and cross off every multiple of the value you
/// have just circled, since none of those multiples can be prime. Thus, after executing
/// the first step of the algorithm, you will have circled the number 2 and crossed off
/// every multiple of two, as follows:
/// 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
/// From this point, you simply repeat the process by circling the first number in the
/// list that is neither crossed off nor circled, and then crossing off its multiples. In this
/// Data Types in C++ – 79 –
/// example, you would circle 3 as a prime and cross off all multiples of 3 in the rest of
/// the list, which would result in the following state:
/// 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
/// Eventually, every number in the list will either be circled or crossed out, as shown in
/// this diagram:
/// 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
/// The circled numbers are the primes; the crossed-out numbers are composites. This
/// algorithm for generating a list of primes is called the sieve of Eratosthenes.
/// Write a program that uses the sieve of Eratosthenes to generate a list of the primes
/// between 2 and 1000

void generateArr(int array[], int start, int stop);
void removeMultiples(int multiple, int array[], int start, int stop);
void question_05()
{
    const int START = 2;
    const int STOP = 1001;
    int numberArr[STOP - START];

    generateArr(numberArr, START, STOP);

    for (int i = 0; i < STOP - START; i++) {
        if (numberArr[i] > 0) {
            removeMultiples(numberArr[i], numberArr, START, STOP);
        }
    }

    for (int i = 0; i < STOP - START; i++) {
        if (numberArr[i] > 0) {
            cout << numberArr[i] << endl;
        }
    }
}

/*
 * This function calculates the area of a cylinder
 * @param multiple[in] remove all multiples of this number
 * @param array[out] array to generate numbers in
 * @param start[in] first number in the array
 * @param start[in] last number in the array
 */
void removeMultiples(int multiple, int array[], int start, int stop)
{
    for (int i = 0; i < stop - start; i++) {
        if (array[i] == -1) {
            continue;
        }
        int remainderOfDivision = array[i] % multiple;

        if (!remainderOfDivision && array[i] != multiple) {
            array[i] = -1;
        }
    }
}

/*
 * This function calculates the area of a cylinder
 *
 * @param array[out] array to generate numbers in
 * @param start[in] first number in the array
 * @param start[in] last number in the array
 */
void generateArr(int array[], int start, int stop)
{
    for (int i = 0; i < stop - start; i++) {
        array[i] = i + start;
    }
}

/// ------------------------------------------------------------------------ Question 06 ---------------------------
/// A histogram is a graphical way of displaying data by dividing the data into separate
/// ranges and then indicating how many data values fall into each range. For example,
/// given the set of exam scores
/// 100, 95, 47, 88, 86, 92, 75, 89, 81, 70, 55, 80
/// a traditional histogram would have the following form:
/// *
/// *
/// *
/// * * *
/// * * * * * *
/// 0–9 10–19 20–29 30–39 40–49 50–59 60–69 70–79 80–89 90–99 100
/// The asterisks in the histogram indicate one score in the 40s, one score in the 50s, five
/// scores in the 80s, and so forth.
/// When you generate histograms using a computer, however, it is usually much
/// easier to display them sideways on the page, as in this sample run:
/// HistogramSideways
/// 0:
/// 10:
/// 20:
/// 30:
/// 40: *
/// 50: *
/// 60:
/// 70: **
/// 80: *****
/// 90: **
/// 100: *
/// Write a program that reads in an array of integers and then displays a histogram of
/// those numbers, divided into the ranges 0–9, 10–19, 20–29, and so forth, up to the
/// range containing only the value 100. Your program should generate output that
/// looks as much like the sample run as possible.

/// ------------------------------------------------------------------------ Question 07 ---------------------------
//Rewrite the histogram program from the preceding exercise so that it displays the
//histogram in a more traditional vertical orientation, like this:
//Histogram

void generateRandomArr(int array[], int length = 50, int min = 0, int max = 100);
void createHistogramArray(int histArr[], int histLength, int numberArr[], int numLength);
void outputHistogramHorizontal(int array[], int length);
void outputHistogramVertical(int array[], int length);

void question_06_07()
{
    const int TOTAL_NUMBERS = 50;
    const int HISTOGRAM_GROUPS = 11;
    int numberArr[TOTAL_NUMBERS];
    int histArr[HISTOGRAM_GROUPS];

    generateRandomArr(numberArr, TOTAL_NUMBERS);

    createHistogramArray(histArr, HISTOGRAM_GROUPS, numberArr, TOTAL_NUMBERS);
    outputHistogramHorizontal(histArr, HISTOGRAM_GROUPS);
    cout << endl << endl << endl;
    outputHistogramVertical(histArr, HISTOGRAM_GROUPS);
}

void createHistogramArray(int histArr[], int histLength, int numberArr[], int numLength)
{
    // Init array
    for (int i = 0; i < histLength; i++) {
        histArr[i] = 0;
    }
    // Add up all the numbers in each range
    for (int i = 0; i < numLength; i++) {
        int value_range = numberArr[i] / 10;
        histArr[value_range]++;
    }
}

void outputHistogramHorizontal(int array[], int length)
{
    for (int i = 0; i < length; i++) {
        cout << i * 10 << ": ";
        for (int j = 0; j < array[i]; j++) {
            cout << '*';
        }
        cout << endl;
    }
}

/// ------------------------------------------------------------------------ Question 07 ---------------------------
void outputHistogramVertical(int array[], int length)
{
    for (int i = length; i >= 0; i--) {
        for (int j = 0; j < length; j++) {
            if (array[j] > i) {
                cout << "  *";
                continue;
            }
            cout << "   ";
        }
        cout << endl;
    }
    cout << "  ";

    for (int i = 0; i < length; i++) {
        cout << i * 10 << ' ';
    }
    cout << endl;
}

void generateRandomArr(int array[], int length, int min, int max)
{
    for (int i = 0; i < length; i++) {
        int newRandomNumber = randomInteger(min, max);
        array[i] = newRandomNumber;
    }
}

/// ------------------------------------------------------------------------ Question 08 ---------------------------
/// Write a function RemoveZeroElements(array, n) that goes through an array of
/// integers and eliminates any elements whose value is 0. Because this operation
/// changes the effective size of the array, RemoveZeroElements should take the
/// effective size as a reference parameter and adjust it accordingly. For example,
/// suppose that scores contains an array of scores on an optional exam and that
/// nScores indicates the effective size of the array, as shown:

void generateRandomArrWithExtraZeros(int array[], int length, int min = 0, int max = 100);
void RemoveZeroElements(int scores[], int *nScores);

void question_08()
{
    int *totalScores = new int;
    *totalScores = 50;
    int scoreArray[*totalScores];

    generateRandomArrWithExtraZeros(scoreArray, *totalScores);
    RemoveZeroElements(scoreArray, totalScores);

    cout << "The new element count is " << *totalScores << endl;

    for (int i = 0; i < *totalScores; i++) {
        cout << scoreArray[i] << endl;
    }

    cout << endl;
}

void generateRandomArrWithExtraZeros(int array[], int length, int min, int max)
{
    for (int i = 0; i < length; i++) {
        if (randomChance(0.8)) {
            array[i] = 0;
            continue;
        }
        array[i] = randomInteger(min, max);
    }
}

void RemoveZeroElements(int scores[], int *nScores)
{
    int elementCount = *nScores;

    for (int i = 0; i < *nScores; i++) {
        if (i >= elementCount) {
            scores[i] = -1;
            continue;
        }
        // If the element is a zero, loop over array shifting everything left,
        // Then de-increment loop so it repeats the index with the shifted element
        if (scores[i] == 0) {
            elementCount--;
            for (int j = i + 1; j < *nScores; j++) {
                scores[j - 1] = scores[j];
            }
            i--;
        }
    }
    *nScores = elementCount;
}

/// ------------------------------------------------------------------------ Question 09 ---------------------------

int main()
{
    question_08();
    return 0;
}
