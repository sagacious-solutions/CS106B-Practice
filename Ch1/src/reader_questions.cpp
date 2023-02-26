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
/*
 * int DigitSum(int n) {
 *      int sum;
 *
 *      sum = 0;
 *      while (n > 0) {
 *          sum += n % 10;
 *          n /= 10;
 *      }
 *
 *      return sum;
 * }
*/

/*
 * Using the DigitSum function from the section entitled “The while statement” as a
 * model, write a program that reads in an integer and then displays the number that has
 * the same digits in the reverse order, as illustrated by this sample run:
 */
void question_06(){
    long reversed_num = 0;

    cout << "Enter a number you'd like to reverse : ";
    long number = getInteger();

    while (number > 0){
        int new_num = number % 10;
        reversed_num = reversed_num * 10 + new_num;
        number /= 10;
    }

    cout << "The reversed number is " << reversed_num << '.';
}

/*
 * Greek mathematicians took a special interest in numbers that are equal to the sum of
 * their proper divisors (a proper divisor of N is any divisor less than N itself). They
 * called such numbers perfect numbers. For example, 6 is a perfect number because
 * it is the sum of 1, 2, and 3, which are the integers less than 6 that divide evenly into
 * 6. Similarly, 28 is a perfect number because it is the sum of 1, 2, 4, 7, and 14.
 *
 * Write a predicate function IsPerfect that takes an integer n and returns true if n
 * is perfect, and false otherwise. Test your implementation by writing a main
 * program that uses the IsPerfect function to check for perfect numbers in the range
 * 1 to 9999 by testing each number in turn. When a perfect number is found, your
 * program should display it on the screen. The first two lines of output should be 6
 * and 28. Your program should find two other perfect numbers in the range as well.
 */
bool isPerfect(int n);

void question_07(){
    const int BOTTOM_RANGE = 1;
    const int TOP_RANGE = 9999;

    for (int i = BOTTOM_RANGE; i <= TOP_RANGE; i++){
        if (isPerfect(i)) cout << i << endl;
    }
}

/*
 * This function checks to see if parameter n is a perfect number
 *
 * @param[in] n number to chec
 * @returns True if number is perfect
 */
bool isPerfect(int n){
    int sum_of_factors = 0;

    for(int i = 1; i < n; i++){
        if (!(n % i)){
            sum_of_factors += i;
        }
    }

    return sum_of_factors == n;
}
/*
 * Every positive integer greater than 1 can be expressed as a product of prime
 * numbers. This factorization is unique and is called the prime factorization. For
 * example, the number 60 can be decomposed into the factors 2 x 2 x 3 x 5, each of
 * which is prime. Note that the same prime can appear more than once in the
 * factorization.
 * Write a program to display the prime factorization of a number n, as illustrated by
 * the following sample run:
 */
bool isPrime(int n);

void question_08(){
   cout << "Enter a number to get the prime factorization : ";
   int num = getInteger();
   int remaining = num;

   while (remaining > 1){
       for (int i = remaining; i > 1; i--){
           if (isPrime(i) && !(remaining % i)) {
               remaining /= i;
               cout << i;
               if (remaining != 1) cout << " * ";
               break;
           }
       }
   }
}

/*
 * This function checks if a number is prime number
 *
 * @param n the number to check
 * @returns true if prime else false
 */
bool isPrime(int n){
    if (n == 0 || n == 1) return false;

    for (int i = 2; i <= n / 2; i++){
        if (!(n % i)) return false;
    }
    return true;
}

/*
 * When a floating-point number is converted to an integer in C++, the value is
 * truncated by throwing away any fraction. Thus, when 4.99999 is converted to an
 * integer, the result is 4. In many cases, it would be useful to have the option of
 * rounding a floating-point value to the nearest integer. For a positive floating-point
 * number x , the rounding operation can be achieved by adding 0.5 to x and then
 * truncating the result to an integer. If the decimal fraction of x is less than .5, the
 * truncated value will be the integer less than x ; if the fraction is .5 or more, the
 * truncated value will be the next larger integer. Because truncation always moves
 * toward zero, negative numbers must be rounded by subtracting 0.5 and truncating,
 * instead of adding 0.5.
 *
 * Write a function Round(x) that rounds a floating-point number x to the nearest
 * integer. Show that your function works by writing a suitable main program to test it.
 */
int round(float dec_num);

void question_09(){
    cout << "Enter a floating number to round : ";
    float a_dec_num = getReal();

    cout << "The rounded number is " << round(a_dec_num);
}

/*
 * This function rounds using only the first decimal place
 *
 * @param dec_num the number to round
 * @returns the rounded number
 */
int round(float dec_num){
    int decimal = int(dec_num * 10) % 10;

    if((dec_num > 0 && decimal >= 5) || (dec_num < 0 && decimal < 5)){
        return int(dec_num + 0.5);
    }
    return int(dec_num);
}

/*
 * the German mathematician Leibniz (1646–1716) discovered the rather remarkable
 * fact that the mathematical constant π can be computed using the following
 * mathematical relationship:

 * The formula to the right of the equal sign represents an infinite series; each fraction
 * represents a term in that series. If you start with 1, subtract one-third, add one-fifth,
 * and so on, for each of the odd integers, you get a number that gets closer and closer
 * to the value of π/4 as you go along.
 * Write a program that calculates an approximation of π consisting of the first
 * 10,000 terms in Leibniz’s series.
 */
void question_10(){
    int counter = 1;
    double pi = 1;
    int calculate_to = 10000;

    for (int i = 3; i <= calculate_to; i+=2){
        if (counter % 2){
            pi -= 1.0 / i;
            counter++;
            continue;
        }
        pi += 1.0 / i;
        counter++;
    }

    cout << "The number is " << pi * 4;
}

void question_10_alt(){
    double pi = 1;
    const int FACTORS = 10000;

    for (int i = 1; i <= FACTORS; i++){
        if (i % 2){
            pi -= 1.0 / ((i * 2) + 1);
            continue;
        }
        pi += 1.0 / ((i * 2) + 1);
    }

    cout << "The number is " << pi * 4;
}

int main() {
    question_10_alt();

    return 0;
}
