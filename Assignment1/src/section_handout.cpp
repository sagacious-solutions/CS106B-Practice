/** This source file contains the answers to Lecture 3's section assignment #1 * 
 * 
 */

#include <cctype>
#include <console.h>
#include <fstream>
#include <iostream>
#include <map.h>
#include <random.h>
#include <set.h>
#include <string>
#include <strlib.h>
#include <unistd.h>
#include <vector.h>

using namespace std;

/// ------------------------------------------------------------------------ Question 1 ---------------------------

/// Problem 1: Removing all occurrences of characters
/// Write a function CensorString that takes two strings as input and returns the first string
/// with all of the characters that are present in the second removed.
/// "Stanford University" with “nt” removed becomes "Saford Uiversiy"
/// "Llamas like to laugh" with “la” removed becomes "Lms ike to ugh"
/// and so on . . .
/// Note that the function is case sensitive. This function could be written two ways. One
/// way is to return a completely new string, and the other is to modify the original string.
/// For practice write both of these functions. First write a function that returns a completely
/// new string with the following prototype:
/// string CensorString1(string text, string remove);
/// and then write a function that modifies the original string with the following prototype:

string censorString(string text, string remove);
void censorString(string *text, string remove);

void question_01()
{
    string str1 = "Stanford University";
    string str2 = "Llamas like to laugh";
    string rm1 = "nt";
    string rm2 = "la";
    string *ptrStr = new string;
    *ptrStr = str1;

    cout << "The string " << str1 << " with " << rm1 << " removed is " << censorString(str1, rm1)
         << endl;
    cout << "The string " << str2 << " with " << rm2 << " removed is " << censorString(str2, rm2)
         << endl;

    censorString(ptrStr, rm1);

    cout << "The string " << str1 << " with " << rm1 << " removed is " << *ptrStr << endl;
}

/**
 * @brief censorString1 removes all the letters that appear in remove from text
 * @param text
 * @param remove
 * @return a new string without removes chars
 */
string censorString(string text, string remove)
{
    string censoredString = "";
    Set<char> badChars;

    for (char c : remove)
        badChars.add(c);

    // Using a normal iterator to iterate over the characters in the string
    for (string::iterator it = text.begin(); it != text.end(); ++it) {
        if (!badChars.contains(*it))
            censoredString += *it;
    }

    return censoredString;
}

/**
 * @brief censorString Takes in a pointer to a string and removes from it
 * all letters that are in the string remove
 * @param text[out]
 * @param remove[in]
 */
void censorString(string *text, string remove)
{
    Set<char> badChars;

    for (char c : remove)
        badChars.add(c);

    for (int i = 0; i <= (text->length() - 1); i++) {
        if (badChars.contains((*text)[i])) {
            text->erase(i, 1);
            i--;
        }
    }
}

/// ------------------------------------------------------------------------ Question 2 ---------------------------

/// When we grade your exams, we’re going to keep track of some statistics like the min,
/// max and average scores. Define a struct containing these statistics. Then, write a
/// function that takes a filename, reads the scores from it (one per line where 0 <= score <=
/// 100), and returns the struct you defined. For efficiency’s sake, your function should
/// make only a single pass over the file.

struct scoreStatisticsT
{
    int min;
    int max;
    double avg;
};

scoreStatisticsT getStatsFromFile(string filename);
void generateFileOfRandomScores(string filename);

void question_02()
{
    string scoresFilename = "scores.txt";

    // Get cwd, then stepback one directory
    char buffer[250];
    getcwd(buffer, sizeof(buffer));
    string cwd = buffer;

    cwd.erase(stringLastIndexOf(cwd, "/"), cwd.length());
    string filepath = cwd + "/" + scoresFilename;

    generateFileOfRandomScores(filepath);
    scoreStatisticsT stats = getStatsFromFile(filepath);

    cout << "Min: " << stats.min << endl << "Max:" << stats.max << endl << "Avg: " << stats.avg;
}

/**
 * @brief generateFileOfRandomScores Generates a file of random length (25 - 80) with random scores (0-100)
 * with one score per line
 * @param filename name of file to create
 */
void generateFileOfRandomScores(string filepath)
{
    ofstream outFile(filepath);
    const int SCORES_TO_GENERATE = randomInteger(25, 80);

    if (!outFile) {
        cerr << "Failed to create the file " << filepath;
        return;
    }

    for (int i = 0; i < SCORES_TO_GENERATE; i++) {
        outFile << randomInteger(0, 100) << endl;
    }

    outFile.close();
}

scoreStatisticsT getStatsFromFile(string filename)
{
    ifstream inFile(filename);
    string line;
    int min = 100;
    int max = 0;
    double avgScore = 0;
    int totalScores = 0;

    while (getline(inFile, line)) {
        const int score = stringToInteger(line);
        avgScore += score;
        totalScores++;
        if (score < min) {
            min = score;
            continue;
        }
        if (score > max)
            max = score;
    }

    avgScore /= totalScores;

    return scoreStatisticsT{min, max, avgScore};
}

/// ------------------------------------------------------------------------ Question 2 ---------------------------

/// Write a function CountLetters that takes a filename and prints the number of times
/// each letter of the alphabet appears in that file. Because there are 26 numbers to be
/// printed, CountLetters needs to create a Vector. For example, if the file is:

typedef Map<char, int> letterMap;

letterMap countLetters(string filepath);
void outputLetterMap(letterMap &m);

void question_03()
{
    string lettersFile = "lettersFile.txt";

    // Get cwd, then stepback one directory
    char buffer[250];
    getcwd(buffer, sizeof(buffer));
    string cwd = buffer;

    cwd.erase(stringLastIndexOf(cwd, "/"), cwd.length());
    string filepath = cwd + "/" + lettersFile;
    letterMap letters = countLetters(filepath);
    outputLetterMap(letters);
}

/**
 * @brief outputLetterMap outputs the letter, then the number of times it showed up
 * @param m map of letter occurences
 */
void outputLetterMap(letterMap &m)
{
    for (char l : m) {
        cout << l << ": " << m[l] << endl;
    }
}

/**
 * @brief countLetters reads from the file at filepath and counts the occurences of each letter
 * @param filepath
 * @return a map with one key per letter and the occurence count in each file
 */
letterMap countLetters(string filepath)
{
    ifstream inFile(filepath);
    string line;
    letterMap letters;

    while (getline(inFile, line)) {
        for (char c : line) {
            c = tolower(c);

            if (c < 'a' || c > 'z')
                continue;

            if (letters.containsKey(c))
                letters[c]++;
            else
                letters[c] = 1;
        }
    }
    return letters;
}

int main()
{
    question_03();
    return 0;
}
