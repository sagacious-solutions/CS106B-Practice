#include <console.h>
#include <ctime>
#include <fstream>

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

void removeZeroElements(vector<int> &vec) {}

bool readVector(ifstrean &inFile, vector<double> &vec) {}

int main()
{
    srand(time(0));

    return 0;
}
