/** This source file contains the answers to Lecture 3's section assignment #1 * 
 * 
 */

#include <console.h>
#include <iostream>
#include <set.h>
#include <string>

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

int main()
{
    question_01();
    return 0;
}
