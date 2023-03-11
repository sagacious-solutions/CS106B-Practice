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

void outputResult(int height, int balls)
{
    cout << "Height of " << height << " results in " << balls << " balls total." << endl;
}

int cannonBall(int height)
{
    if (height == 1) {
        return 1;
    } else {
        return cannonBall(height - 1) + height * height;
    }
}

int main()
{
    srand(time(0));
    question_01();
    return 0;
}
