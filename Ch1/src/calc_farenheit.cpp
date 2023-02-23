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

int main() {
    float cels = get_celsius();
    float temp_farenheit = convert_cel_to_far(cels);
    cout << "Temperature is " << temp_farenheit << "f." << endl;
    return 0;
}
