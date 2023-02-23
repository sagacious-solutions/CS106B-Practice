#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

float get_celsius(){
    cout << "Please input a temperature in Celsius : ";
    float temp_celsius = getReal();

    return temp_celsius;
}

float convert_cel_to_far(float temp_celsius){
    return (temp_celsius * (9.0 / 5.0)) + 32;
}

/*
 * Write a program that reads in a temperature in degrees Celsius and displays the
 * corresponding temperature in degrees Fahrenheit.
 */
void question_01(){
    float cels = get_celsius();
    float temp_farenheit = convert_cel_to_far(cels);
    cout << "Temperature is " << temp_farenheit << "f." << endl;
}

/*
 * Write a program that converts a distance in meters to the corresponding English
 * distance in feet and inches.
 */
void question_02(){
    const float INCH_IN_METERS = 0.0254;
    const int INCHES_IN_FOOT = 12;

    cout << "Input a distance in meters to convert to imperial : ";
    float distance_meters = getReal();
    float distance_inches = distance_meters / INCH_IN_METERS;
    int distance_feet = distance_inches / INCHES_IN_FOOT;
    float left_over_inches = distance_inches - (distance_feet * INCHES_IN_FOOT);

    /*Set precision point to decimal point and 2 decimal places*/
    cout << fixed;
    cout.precision(2);
    cout << "The imperial conversion is " << distance_feet << "ft " << left_over_inches << " inches." << endl;
}

/*
 * According to legend, the German mathematician Karl Friedrich Gauss (1777–1855)
 * began to show his mathematical talent at a very early age. When he was in
 * elementary school, Gauss was asked by his teacher to compute the sum of the
 * numbers between 1 and 100. Gauss is said to have given the answer instantly: 5050.
 * Write a program that computes the answer to the question Gauss’s teacher posed.
 */
void question_03(){
    const int BOTTOM_END = 1;
    const int TOP_END = 100;
    int sum_of_range = 0;

    for(int i = BOTTOM_END; i<= TOP_END; i++) {
        sum_of_range += i;
    };

    cout << "The answer to question 3 is " << sum_of_range << '.';
}

/*
 * Write a program that reads in a positive integer N and then calculates and displays
 * the sum of the first N odd integers. For example, if N is 4, your program should
 * display the value 16, which is 1 + 3 + 5 + 7.
 */
void question_04(){
    int sum_odd_nums = 0;

    cout << "Provide an interger to calculate odd sum from :";
    int n = getInteger() * 2;

    for(int i = 1; i <= n; i+=2){
        sum_odd_nums += i;
    }

    cout << "The sum of the first " << n / 2 << " odd integers is " << sum_odd_nums << '.';
}

/*
 * Write a program that reads in a list of integers from the user until the user enters the
 * value 0 as a sentinel. When the sentinel appears, your program should display the
 * largest value in the list, as illustrated in the following sample run
 */
void question_05(){
    int input = 0;
    int highest = -1;

    cout << "Input as many integers as you'd like hitting enter after each one. When you are done, enter 0, and the program will stop and output the highest numer.";

    do {
        input = getInteger();

        if (input > highest) highest = input;

    } while (input);

    cout << "The largest inputed integer was " << highest << '.';
}

int main() {
    question_05();

    return 0;
}
