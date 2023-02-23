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

int main() {
    question_02();

    return 0;
}
