/** This the ansers for assignment simple C++
 */

#include <console.h>
#include <ctime>
#include <iostream>
#include <random.h>
#include <set.h>
#include <simpio.h>

using namespace std;

/// ------------------------------------------------------------------------ Question 2 ---------------------------
struct electionConfigT
{
    int voters;
    double voteSpread;
    double errorPerc;
};

void generateVotes(int *c1, int *c2, int numVotes, double errorRate);
electionConfigT getConfigFromUser();

void question_02()
{
    int *c1 = new int;
    int *c2 = new int;
    int winsC1 = 0;
    int winsC2 = 0;
    const double TRIALS = 500.0;
    srand(time(0));

    electionConfigT eConfig = getConfigFromUser();
    const int C1_VOTES = (eConfig.voters * eConfig.voteSpread) + eConfig.voters / 2;
    const int C2_VOTES = eConfig.voters - C1_VOTES;

    for (int i = 0; i < TRIALS; i++) {
        *c1 = 0;
        *c2 = 0;
        generateVotes(c1, c2, C1_VOTES, eConfig.errorPerc);
        generateVotes(c2, c1, C2_VOTES, eConfig.errorPerc);

        if (*c1 > *c2)
            winsC1++;
        else
            winsC2++;
    }

    cout << "Canditate 1 won " << winsC1 << " times and candidate 2 won " << winsC2 << " times."
         << endl;
    cout << "The election was in valid " << (winsC2 / TRIALS) * 100 << "% of the time." << endl;
}

/**
 * @brief generateVotes Generates all the votes for the candidates given the number of votes and error rate
 * @param c1[out] candidate 1 votes
 * @param c2[out] candidate 2 votes
 * @param numVotes
 * @param errorRate the percentage at which the second candidates will get the votes instead
 */
void generateVotes(int *c1, int *c2, int numVotes, double errorRate)
{
    int random_num = rand() % 100;

    for (int i = 0; i < numVotes; i++) {
        if (random_num >= errorRate * 100.0)
            *c1 = *c1 + 1;
        else
            *c2 = *c2 + 1;
    }
}

/**
 * @brief getConfigFromUser gets value for election config from user. Checks if valid and reprompts if not.
 * @return election config
 */
electionConfigT getConfigFromUser()
{
    electionConfigT config;
    config.voters = -1;
    config.voteSpread = 2;
    config.errorPerc = 2;

    while (config.voters < 0) {
        config.voters = getInteger("Please enter the number of voters: ");
        if (config.voters < 0)
            cout << "You must enter a positive interge value." << endl;
    }
    while (config.voteSpread < 0 || config.voteSpread > 1) {
        config.voteSpread = getReal("Please enter the spread between candidates: ");
        if (config.voteSpread < 0 || config.voteSpread > 1)
            cout << "You must enter a value between 0 and 1." << endl;
    }
    while (config.errorPerc < 0 || config.errorPerc > 1) {
        config.errorPerc = getReal("Please enter the error percentage: ");
        if (config.errorPerc < 0 || config.errorPerc > 1)
            cout << "You must enter a value between 0 and 1." << endl;
    }

    return config;
};

/// ------------------------------------------------------------------------ Question 4 ---------------------------

string getSoundexValues(string *str);
string parseSoundexCode(string str);

void question_04()
{
    string *surname = new string;
    while (true) {
        *surname = getLine("Enter a surname (return to quit): ");

        if (!surname->length())
            return;

        string soundexVal = getSoundexValues(surname);
        soundexVal = char(toupper(surname->at(0))) + parseSoundexCode(soundexVal);
        cout << "The value is " << soundexVal << endl;
    }
}

string parseSoundexCode(string str)
{
    string soundexStr = "";

    for (char c : str) {
        // Ignore zeros
        if (c == '0')
            continue;
        if (!soundexStr.length()) {
            soundexStr += c;
            continue;
        }
        // Don't add consecutive duplicates
        if (soundexStr[soundexStr.length() - 1] != c)
            soundexStr += c;
    }

    while (soundexStr.length() < 3)
        soundexStr += '0';

    return soundexStr.substr(0, 3);
}

string getSoundexValues(string *str)
{
    string integerVal = "";
    Set<char> zero = {'a', 'e', 'i', 'o', 'u', 'h', 'w', 'y'};
    Set<char> one = {'b', 'f', 'p', 'v'};
    Set<char> two = {'c', 'g', 'j', 'k', 'q', 's', 'x', 'z'};
    Set<char> three = {'d', 't'};
    Set<char> four = {'m', 'n'};

    for (int i = 1; i < str->length(); i++) {
        if (zero.contains(str->at(i))) {
            integerVal += '0';
            continue;
        }
        if (one.contains(str->at(i))) {
            integerVal += '1';
            continue;
        }
        if (two.contains(str->at(i))) {
            integerVal += '2';
            continue;
        }
        if (three.contains(str->at(i))) {
            integerVal += '3';
            continue;
        }
        if (four.contains(str->at(i))) {
            integerVal += '4';
            continue;
        }
        if (str->at(i) == 'l') {
            integerVal += '5';
            continue;
        }
        if (str->at(i) == 'r') {
            integerVal += '6';
        }
    }
    return integerVal;
}

int main()
{
    question_02();
    return 0;
}
