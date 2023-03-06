#include <console.h>
#include <ctime>
#include <fstream>
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

//void removeZeroElements(vector<int> &vec) {}

/**
 * @brief readVector Reads values into the vector until it encounters a blank line
 * @param inFile filestream object to read from
 * @param vec vector to add information too
 * @return True if it sucesfully reads
 */
bool readVector(ifstream &inFile, vector<double> &vec)
{
    if (!inFile) {
        cerr << "Error: could not open file or end of file reached." << endl;
        return false;
    }

    string line;
    while (getline(inFile, line)) {
        if (!line.length())
            return true;
        vec.push_back(stod(line));
    }

    return true;
}

void sortTextFile(ifstream &inFile, Vector<string> &lines)
{
    if (!inFile) {
        cerr << "Error: could not open file or end of file reached." << endl;
    }

    string line;
    while (getline(inFile, line)) {
        // If line blank stop reading
        if (!line.length())
            return;

        // If lines empty, push to back
        if (!lines.size()) {
            lines.push_back(line);
            continue;
        }

        // If greater than start or end
        if (stod(line) > stod(lines[lines.size() - 1])) {
            lines.push_back(line);
            continue;
        }
        if (stod(line) < stod(lines[0])) {
            lines.insert(0, line);
            continue;
        }

        // Insert into middle
        for (int i = 0; i <= lines.size(); i++) {
            // Less than current, more than next, or same as current
            if (stod(line) > stod(lines[i]) && stod(line) < stod(lines[i + 1])
                || stod(line) == stod(lines[i])) {
                lines.insert(i + 1, line);
                break;
            }
        }
    }
}

void question_1_2_3()
{
    const string PATH_ROOTS
        = "/home/admin/development/CS106B/Practice Coding/Ch4/sourceText/squareAndCubeRoots.txt";
    vector<double> vec;
    Vector<string> lines;
    ifstream inFile(PATH_ROOTS);

    cout << readVector(inFile, vec) << endl;
    cout << readVector(inFile, vec) << endl;
    cout << readVector(inFile, vec) << endl;

    // Return stream to begining of file with an offset of zero
    inFile.clear();
    inFile.seekg(0, ios::beg);

    sortTextFile(inFile, lines);
    sortTextFile(inFile, lines);

    for (string line : lines)
        cout << line << endl;
}

int main()
{
    srand(time(0));
    question_1_2_3();
    return 0;
}
