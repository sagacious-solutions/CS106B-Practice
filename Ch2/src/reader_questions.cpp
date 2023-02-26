#include "console.h"
#include "simpio.h"
#include <iostream>
using namespace std;

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
weekdayT incrementDay(weekdayT day, int delta_days)
{
    // The extra + 7 % 7 corrects for negative deltas
    return weekdayT((((day + delta_days) % 7) + 7) % 7);
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

int main()
{
    question_01();
    return 0;
}
