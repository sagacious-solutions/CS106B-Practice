#include "console.h"
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

int main()
{
    question_04();
    return 0;
}
