#include "console.h"
#include "random.h"
#include "simpio.h"
#include <card.h>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stringutils.h>
#include <unistr.h>
#include <vector>

using namespace std;

const int UPPER_DIFFERENCE = 32;

/// ------------------------------------------------------------------------ Question 01 ---------------------------
/// Write a program that repeatedly generates a random real number between 0 and 1
/// and then displays the average after a certain number of runs, as illustrated by the
/// following sample run:
/// AverageRand
/// This program averages a series of random numbers
/// between 0 and 1.
/// How many trials: 10000
/// The average value after 10000 trials is 0.501493
/// If the random number generator is working well, the average should get closer to 0.5
/// as the number of trials increases.
void question_01()
{
    int howMany = getInteger("Please enter an integer value for amount of numbers to generate : ");
    int howTimesMany = getInteger(
        "Please enter an integer value for how many times to regenerate : ");
    double totalNum = 0.0;

    for (int h = 0; h < howTimesMany; h++) {
        for (int i = 0; i < howMany; i++) {
            totalNum += randomReal(0.0, 1.0);
        }

        cout << "The average number is " << totalNum / howMany << endl;
        totalNum = 0;
    }
}

/// ------------------------------------------------------------------------ Question 02 ---------------------------
///
/// Write a program that simulates flipping a coin repeatedly and continues until three
/// consecutive heads are tossed. At that point, your program should display the total
/// number of coin flips that were made. The following is one possible sample run of
/// the program:
void howManyFlips(int consecutiveHeads);

void question_02()
{
    howManyFlips(3);
    howManyFlips(5);
    howManyFlips(10);
}

void howManyFlips(int consecutiveHeads)
{
    int coinFlips = 0;
    int headsCount = 0;

    while (true) {
        bool coinFlip = randomBool();
        coinFlips++;

        // Heads is true
        if (coinFlip) {
            cout << "heads" << endl;
            headsCount++;
            if (headsCount >= consecutiveHeads)
                break;
        } else {
            cout << "tails" << endl;
            headsCount = 0;
        }
    }
    cout << "It took " << coinFlips << " coinflips to get " << consecutiveHeads
         << " consecutive heads." << endl;
}

/// ------------------------------------------------------------------------ Question 03 ---------------------------
/// Create a slot machine program

enum slotSymbolT { CHERRY, LEMON, ORANGE, PLUM, BELL, BAR };
const int SYMBOL_COUNT = 6;

slotSymbolT cherry = CHERRY;
slotSymbolT lemon = LEMON;
slotSymbolT orange = ORANGE;
slotSymbolT plum = PLUM;
slotSymbolT bell = BELL;
slotSymbolT bar = BAR;

struct gameOutcomeT
{
    slotSymbolT gameOutcome[3];
    int symbolCount[SYMBOL_COUNT] = {0, 0, 0, 0, 0, 0};
    int winnings = 0;
};

bool yesPlay(int bank);
void getSlots(gameOutcomeT *outcome);
int getWinnings(gameOutcomeT outcome);
void outputOutcome(gameOutcomeT *outcome);

void question_03()
{
    int bank = 50;

    while (true) {
        if (!yesPlay(bank))
            break;

        bank -= 1;

        gameOutcomeT *outcome = new gameOutcomeT;

        getSlots(outcome);
        outcome->winnings = getWinnings(*outcome);
        bank += outcome->winnings;
        outputOutcome(outcome);
    }
}

/// Wrote this with the enums only to discover they don't work in a switch statement
/// Next time the better solution would be to just use const int values for each type
void outputOutcome(gameOutcomeT *outcome)
{
    cout << right;
    for (int i = 0; i < 3; i++) {
        switch (outcome->gameOutcome[i]) {
        case 0:
            cout << "CHERRY" << setw(10);
            break;
        case 1:
            cout << "LEMON" << setw(10);

            break;
        case 2:
            cout << "ORANGE" << setw(10);

            break;
        case 3:
            cout << "PLUM" << setw(10);

            break;
        case 4:
            cout << "BELL" << setw(10);

            break;
        case 5:
            cout << "BAR" << setw(10);
            break;
        }
    }
    cout << " -- ";
    if (outcome->winnings) {
        cout << "You win $" << outcome->winnings << endl;
        return;
    }
    cout << "You lose" << endl;
}

int getWinnings(gameOutcomeT outcome)
{
    if (outcome.symbolCount[bar] == 3) {
        return 250;
    }
    if (outcome.symbolCount[bell] == 3
        || (outcome.symbolCount[bell] == 2 && outcome.symbolCount[bar] == 1)) {
        return 20;
    }
    if (outcome.symbolCount[plum] == 3
        || (outcome.symbolCount[plum] == 2 && outcome.symbolCount[bar] == 1)) {
        return 14;
    }
    if (outcome.symbolCount[orange] == 3
        || (outcome.symbolCount[orange] == 2 && outcome.symbolCount[bar] == 1)) {
        return 10;
    }

    switch (outcome.symbolCount[cherry]) {
    case 1:
        return 2;
    case 2:
        return 5;
    case 3:
        return 7;
    }
    return 0;
}

/**
 * @brief getSlots populates the outcome variable with the 3 slot symbols for the game
 * @param outcome[out] value to store the games outcome in
 */
void getSlots(gameOutcomeT *outcome)
{
    for (int i = 0; i < 3; i++) {
        int symbolNum = randomInteger(0, SYMBOL_COUNT - 1);
        outcome->symbolCount[symbolNum]++;
        outcome->gameOutcome[i] = slotSymbolT(symbolNum);
    }
}

bool yesPlay(int bank)
{
    ostringstream oss;
    oss << "You have $" << bank << ". Would you like to play? ";
    while (true) {
        string yesNo = getLine(oss.str());

        switch (tolower(yesNo[0])) {
        case 'y':
            return true;
        case 'n':
            return false;
        }

        cout << "Invalid input. You must enter either Yes,No,y,n." << endl;
    }
}

/// ------------------------------------------------------------------------ Question 04 ---------------------------
/// Implement a function EqualIgnoringCase(str1, str2) that returns true if the
/// two string parameters contain the same sequence of characters ignoring case
/// distinctions. Implement this once using the convenience functions from strutils.h
/// and again without

bool equalIgnoreCase(string str1, string str2);

void question_04()
{
    string userEntryA = "";
    string userEntryB = "";

    while (true) {
        userEntryA = getLine("Enter string a : ");
        userEntryB = getLine("Enter string b : ");
        if (!userEntryA.length())
            break;
        if (equalIgnoreCase(userEntryA, userEntryB))
            cout << "Those strings are equal!" << endl;
        else
            cout << "Those strings are not equal" << endl;
    }
}

/**
 * @brief equalIgnoreCase Checks to see if two strings are equal, ignoring case, doesn't use standard library
 * @param str1 
 * @param str2
 * @return True if strings are equal
 */
bool equalIgnoreCase(string str1, string str2)
{
    if (!(str1.length() == str2.length()))
        return false;

    for (int i = 0; i < str1.length(); i++) {
        char a = str1[i];
        char b = str2[i];

        if (a >= 'A' && a <= 'Z')
            a += UPPER_DIFFERENCE;
        if (b >= 'A' && b <= 'Z')
            b += UPPER_DIFFERENCE;

        if (a != b)
            return false;
    }
    return true;
}
/// ------------------------------------------------------------------------ Question 05 ---------------------------
/// Implement a function Capitalize(str) that returns a string in which the initial
/// character is capitalized (if it is a letter) and all other letters are converted so that they
/// appear in lowercase form. Characters other than letters are not affected. For
/// example, Capitalize("BOOLEAN") and Capitalize("boolean") should each
/// return the string "Boolean"

string capitalize(string str);
bool isCapital(char c);

void question_05()
{
    string one = "unEVNeCaps";
    string two = "lowercase";

    string oneAfter = capitalize(one);
    string twoAfter = capitalize(two);

    cout << one << " -> " << oneAfter << endl;
    cout << two << " -> " << twoAfter << endl;
}

/**
 * @brief capitalize capitalizes first char, makes everything else lower
 * @param str string to update
 * @return string after its been updated
 */
string capitalize(string str)
{
    if (!isCapital(str[0]))
        str[0] -= UPPER_DIFFERENCE;

    for (int i = 1; i < str.length(); i++) {
        if (isCapital(str[i]))
            str[i] += UPPER_DIFFERENCE;
    }
    return str;
}

/**
 * @brief isCapital checks if a letter is a capital
 * @param c chracter to check
 * @return true if capital
 */
bool isCapital(char c)
{
    return (c >= 'A' && c <= 'Z');
}

/// ------------------------------------------------------------------------ Question 06 ---------------------------
/// A palindrome is a word that reads identically backward and forward, such as level
/// or noon. Write a predicate function IsPalindrome(str) that returns true if the
/// string str is a palindrome. In addition, design and write a test program that calls
/// IsPalindrome to demonstrate that it works.

bool isPalindrome(string str);

string isTrue(bool b)
{
    if (b)
        return "True";
    return "False";
}

void question_06()
{
    string aPalindrome = "LeVEl";
    string notPalidrome = "notapalindrome";

    cout << aPalindrome << " is a palindrome : " << isTrue(isPalindrome(aPalindrome)) << endl;
    cout << notPalidrome << " is a palindrome : " << isTrue(isPalindrome(notPalidrome)) << endl;
}

/**
 * @brief isPalindrome checks to see if the string is a palindrom
 * @param str string ot check
 * @return true if its a palindrome
 */
bool isPalindrome(string str)
{
    int strLen = str.length();

    for (int i = 0; i < strLen; i++) {
        str[i] = tolower(str[i]);
    }

    for (int i = 0; i < strLen; i++) {
        if (str[i] != str[strLen - 1 - i])
            return false;
    }

    return true;
}

/// ------------------------------------------------------------------------ Question 07 ---------------------------

/// One of the simplest types of codes used to make it harder for someone to read a
/// message is a letter-substitution cipher, in which each letter in the original message
/// is replaced by some different letter in the coded version of that message. A
/// particularly simple type of letter-substitution cipher is a cyclic cipher, in which each
/// letter is replaced by its counterpart a fixed distance ahead in the alphabet.

string encodeString(string str, int key);
char shiftLetter(char l, int nShift);

void question_07()
{
    int shiftKey = 4;
    string toEncode = "ABC";
    string encoded = encodeString(toEncode, shiftKey);

    cout << "The string " << toEncode << " encoded to " << encoded << " with a key of " << shiftKey
         << "." << endl;

    shiftKey = 3;
    toEncode = "XYZ";
    encoded = encodeString(toEncode, shiftKey);

    cout << "The string " << toEncode << " encoded to " << encoded << " with a key of " << shiftKey
         << "." << endl;

    shiftKey = -3;
    toEncode = "ABC";
    encoded = encodeString(toEncode, shiftKey);

    cout << "The string " << toEncode << " encoded to " << encoded << " with a key of " << shiftKey
         << "." << endl;

    shiftKey = -23;
    toEncode = "AbCdefGHi";
    encoded = encodeString(toEncode, shiftKey);

    cout << "The string " << toEncode << " encoded to " << encoded << " with a key of " << shiftKey
         << "." << endl;

    shiftKey = -100;
    toEncode = "ABC";
    encoded = encodeString(toEncode, shiftKey);

    cout << "The string " << toEncode << " encoded to " << encoded << " with a key of " << shiftKey
         << "." << endl;
}

/**
 * @brief encodeString encodes a letter using letter shifting
 * @param str string to encode
 * @param key places to shift by
 * @return the mewly shifted string
 */
string encodeString(string str, int key)
{
    string newString = "";

    for (int i = 0; i < str.length(); i++) {
        int newLet = shiftLetter(str[i], key);
        newString += char(newLet);
    }
    return newString;
}

/**
 * @brief shiftLetter Shifts a letter in the alphabit by nSHift places
 * @param l letter to shift
 * @param nShift places to shift
 * @return the shifted letter
 */
char shiftLetter(char l, int nShift)
{
    bool isCap = isCapital(l);
    const int ALPHA_LENGTH = 26;

    // Wrap the key if it loops alphabit multiple times
    nShift = nShift % ALPHA_LENGTH;

    l += nShift;

    if (isCap && l > 'Z')
        return l % 'Z' + 'A' - 1;
    if (isCap && l < 'A')
        return l + ALPHA_LENGTH;
    if (!isCap && l > 'z')
        return l % 'z' + 'a' - 1;
    if (!isCap && l < 'a')
        return l + ALPHA_LENGTH;
    return l;
}

/// ------------------------------------------------------------------------ Question 08 ---------------------------
///
// Without using the string method s u b s t r , implement your own function
// SubString(s, pos, len) , which returns the substring of s , beginning at position
// pos and including at most len characters. Make sure that your function correctly
// applies the following rules:
// a. If pos is negative, it is set to 0 so that it indicates the first character in the string.
// b. If len is greater than s.length()– pos , it is set to strlen(s) – pos so that it
// stops at last character.
// c. If pos is greater than s.length() - 1 , SubString returns the empty string.

string subString(string s, int pos, int len);

void question_08()
{
    int index = 5;
    int len = 5;
    string one = "jaberwalky";
    string subOne = subString(one, index, len);

    cout << "The substring of " << one << " starting at index " << index << " and going for " << len
         << " characters is " << subOne << "." << endl;

    index = -10;
    len = 5;
    one = "jaberwalky";
    subOne = subString(one, index, len);

    cout << "The substring of " << one << " starting at index " << index << " and going for " << len
         << " characters is " << subOne << "." << endl;
}

/**
 * @brief subString returns a substring of s from pos to len
 * @param s string to get substring from
 * @param pos index to start at
 * @param len amount of characters to get
 * @return the substring of s
 */
string subString(string s, int pos, int len)
{
    string sString = "";

    if (pos < 0)
        pos = 0;

    if (pos + len > s.length())
        len = s.length() - pos;

    for (int i = pos; i < pos + len; i++) {
        sString += s[i];
    }

    return sString;
}

/// ------------------------------------------------------------------------ Question 09 ---------------------------
/// Write a program wc.cpp that reads a file and reports how many lines, words, and
/// characters appear in it. For the purposes of this program, a word consists of a
/// consecutive sequence of any characters except whitespace characters. For example,
/// if the file twinkle.txt contains the following verse from Alice in Wonderland,
/// Twinkle, twinkle, little bat!
/// How I wonder what you're at!
/// Up above the world you fly,
/// Like a teatray in the sky.
/// your program should be able to generate the following sample run:
/// LineWordCharCount
/// File: twinkle.txt
/// Lines: 4
/// Words: 22
/// Chars: 114

string *getFileText(string filepath);
void letterWordLineCount(string *fileLines, int *letterCount, int *wordCount, int *lineCount);

void question_09()
{
    string filename = "question_09.txt";
    string fileDirectory = "/home/admin/development/CS106B/Practice Coding/Ch3/res/";
    string filepath = fileDirectory + filename;
    string *fileLines;
    fileLines = getFileText(filepath);
    const int INDENT = 10;

    int *lineCount = new int;
    int *wordCount = new int;
    int *charCount = new int;
    *wordCount = 0;
    *charCount = 0;

    letterWordLineCount(fileLines, charCount, wordCount, lineCount);
    cout << left << setw(INDENT) << "Lines:" << *lineCount << endl;
    cout << left << setw(INDENT) << "Words:" << *wordCount << endl;
    cout << left << setw(INDENT) << "Chars:" << *charCount << endl;
}

/**
 * @brief letterWordLineCount
 * @param fileLines[in] lines of text from the file
 * @param letterCount[out] tally of chars in the file
 * @param wordCount[out] tall of words in the file
 * @param lineCount[out] tall of lines in the file
 */
void letterWordLineCount(string *fileLines, int *letterCount, int *wordCount, int *lineCount)
{
    *lineCount = sizeof(*fileLines) / sizeof(string *);

    for (int i = 0; i < *lineCount; i++) {
        for (int j = 0; j < fileLines[i].length(); j++) {
            *letterCount = *letterCount + 1;

            if (fileLines[i][j] == ' ') {
                *wordCount = *wordCount + 1;
            }
        }
        *letterCount = *letterCount + 1;
        *wordCount = *wordCount + 1;
    }
}

/**
 * @brief getFileText Gets each line of text from a file and returns it as array of strings, with one line per index
 * @param filepath filepath of the file to read
 * @return the array of strings
 */
string *getFileText(string filepath)
{
    cout << "Reading file " << filepath << endl;
    int fileLinesCount = 0;
    ifstream infile(filepath);
    string *fileLines = new string[fileLinesCount];

    // Output error and return empty arr if file fails to open
    if (!infile.is_open()) {
        cerr << "Could not open the file " << filepath << endl;
        return fileLines;
    }

    // While lines remaining in file, increase array size, create a new array of that size, copy the old array to new array
    // then add the new line to the new array, repeat to end of file.
    string line;
    while (getline(infile, line)) {
        fileLinesCount++;
        string *newArr = new string[fileLinesCount];
        copy(fileLines, &fileLines[fileLinesCount - 1], newArr);
        delete[] fileLines;
        fileLines = newArr;
        fileLines[fileLinesCount - 1] = line;
    }
    infile.close();

    return fileLines;
}
/// ------------------------------------------------------------------------ Question 12 - 13 ---------------------------

cardT *generateDeck();
void outputDeck(cardT *deck);
void shuffleDeck(cardT *deck, int iter = 1);

void question_12_13()
{
    cardT *deck = generateDeck();
    outputDeck(deck);
    cout << endl << endl << endl;
    shuffleDeck(deck);
    outputDeck(deck);
}

void outputDeck(cardT *deck)
{
    for (int i = 0; i < 52; i++) {
        if (i % 13 == 0)
            cout << endl;

        cout << cardName(deck[i]) << "  ";
    }
}

void shuffleDeck(cardT *deck, int iter)
{
    for (int iteration = 0; iteration < iter; iteration++) {
        for (int i = 0; i < 52; i++) {
            int whereTo = randomInteger(0, 51);
            cardT temp = deck[whereTo];
            deck[whereTo] = deck[i];
            deck[i] = temp;
        }
    }
}

cardT *generateDeck()
{
    cardT *deck = new cardT[52];
    int cardNum = 0;
    for (suitT s = clubs; s <= spades; s = suitT(int(s) + 1)) {
        for (rankT r = ace; r <= king; r = rankT(int(r) + 1)) {
            deck[cardNum] = newCard(r, s);
            cardNum++;
        }
    }

    return deck;
}
/// /// ------------------------------------------------------------------------ Question 10 ---------------------------
/// /// ------------------------------------------------------------------------ Question 10 ---------------------------
/// /// ------------------------------------------------------------------------ Question 10 ---------------------------
/// /// ------------------------------------------------------------------------ Question 10 ---------------------------
/// /// ------------------------------------------------------------------------ Question 10 ---------------------------
int main()
{
    question_12_13();
    return 0;
}
