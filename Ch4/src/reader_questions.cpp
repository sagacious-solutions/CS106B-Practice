#include <console.h>
#include <ctime>
#include <fstream>
#include <grid.h>
#include <set.h>
#include <simpio.h>
#include <stack.h>
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

/**
 * @brief sortTextFile Reads in text file and adds it to the lines vector in sorted order
 * @param inFile
 * @param lines Vector to store the incoming text in
 */
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
            if ((stod(line) > stod(lines[i]) && stod(line) < stod(lines[i + 1]))
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

// ************************************************ Question 04 ************************************************

/// The code in Figure 4-2 shows how to check the rows, columns, and diagonals of a
/// tic-tac-toe board using a single helper function. That function, however, is coded in
/// such a way that it only works for 3 x 3 boards. As a first step toward creating a
/// program that can play tic-tac-toe on larger grids, reimplement the CheckForWin and
/// CheckLine functions so that they work for square grids of any size.

///*
//* Checks to see whether the specified player identified by mark
//* ('X' or 'O') has won the game. To reduce the number of special
//* cases, this implementation uses the helper function CheckLine.
//*/
//bool CheckForWin(Grid<char> & board, char mark) {
//    for (int i = 0; i < 3; i++) {
//        if (CheckLine(board, mark, i, 0, 0, 1)) return true;
//        if (CheckLine(board, mark, 0, i, 1, 0)) return true;
//    }
//    if (CheckLine(board, mark, 0, 0, 1, 1)) return true;
//    return CheckLine(board, mark, 2, 0, -1, 1);
//}
///*
//* Checks a line extending across the board in some direction. The
//* starting coordinates are given by the row and col parameters.
//* The direction of motion is specified by dRow and dCol, which
//* show how to adjust the row and col values on each cycle. For
//* rows, dRow is always 0; for columns, dCol is 0. For diagonals,
//* these values will be +1 or -1 depending on the direction.
//*/
//bool CheckLine(Grid<char> & board, char mark, int row, int col,
//               int dRow, int dCol) {
//    for (int i = 0; i < 3; i++) {
//        if (board[row][col] != mark) return false;
//        row += dRow;
//        col += dCol;
//    }
//    return true;
//}
/**
 * @brief CheckLine Checks a line in any given direction to see if they are all the same mark
 * @param board grid of game board
 * @param mark Current player to be checking for
 * @param row starting row
 * @param col starting column
 * @param dRow the offset to move in the row direction its checking
 * @param dCol the offset to move in the col direction its checking
 * @return 
 */
bool CheckLine(Grid<char> &board, char mark, int row, int col, int dRow, int dCol)
{
    for (int i = 0; i < board.numRows(); i++) {
        if (board[row][col] != mark)
            return false;
        row += dRow;
        col += dCol;
    }
    return true;
}

/**
 * @brief CheckForWin Runs the check lines function for vertical, horizontal or diagnol wins
 * @param board 
 * @param mark current player
 * @return True if win
 */
bool CheckForWin(Grid<char> &board, char mark)
{
    for (int i = 0; i < board.numRows(); i++) {
        if (CheckLine(board, mark, i, 0, 0, 1))
            return true;
        if (CheckLine(board, mark, 0, i, 1, 0))
            return true;
    }
    if (CheckLine(board, mark, 0, 0, 1, 1))
        return true;
    return CheckLine(board, mark, board.numCols() - 1, 0, -1, 1);
}

/**
 * @brief drawBoard Draws the gameboard
 * @param board grid containing current state of gameboard
 */
void drawBoard(Grid<char> &board)
{
    for (int i = 0; i < board.numRows(); i++) {
        // 2 Underlines for each grid spot to cover vert lines too;
        for (int j = 0; j < board.numRows() * 2 + 1; j++)
            cout << '_';
        cout << endl;
        cout << '|';
        for (int j = 0; j < board.numCols(); j++) {
            cout << board[i][j] << '|';
        }
        cout << endl;
    }
    // Draw last underline
    for (int j = 0; j < board.numRows() * 2 + 1; j++)
        cout << '_';
    cout << endl;
}

void question_04()
{
    Grid<char> board(4, 4);
    board.fill(' ');    
    char player = 'X';

    while (true) {
        bool validPlay = false;
        int playX, playY;

        while (!validPlay) {
            // Get input, offset to match grid index
            playX = getInteger("Input Row :") - 1;
            playY = getInteger("Input Col :") - 1;

            /// Check input with offset between 0 and grid length
            if (playX > board.numRows() - 1 || playY > board.numCols() - 1 || playX < 0
                || playY < 0) {
                cout << "Value out of range, try again." << endl;
                continue;
            }

            if (board.get(playX, playY) != ' ') {
                cout << "Space already taken, try again." << endl;
                continue;
            }

            validPlay = true;
        }
        board.set(playX, playY, player);
        drawBoard(board);
        if (CheckForWin(board, 'X')) {
            cout << "X Wins!";
            break;
        }
        if (CheckForWin(board, 'O')) {
            cout << "Y Wins!";
            break;
        };

        if (player == 'X')
            player = 'O';
        else
            player = 'X';
    }
}

// ************************************************ Question 05 ************************************************
bool IsMagicSquare(Grid<int> &square);

void question_05()
{
    Grid<int> square1 = {{8, 1, 6}, {3, 5, 7}, {4, 9, 2}};    // IS MAGIC
    Grid<int> square2 = {{10, 10, 60}, {3, 5, 7}, {4, 9, 2}}; // IS NOT MAGIC
    Grid<int> square3 = {{16, 3, 2, 13}, {5, 10, 11, 8}, {9, 6, 7, 12}, {4, 15, 14, 1}}; // IS MAGIC
    Grid<int> square4 = {{16, 3, 2, 13},
                         {5, 10, 11, 8},
                         {9, 6, 7, 12},
                         {4, 15, 14, 22}}; // IS NOT MAGIC

    cout << "This Should be True : " << boolToString(IsMagicSquare(square1)) << endl;
    cout << "This should be False : " << boolToString(IsMagicSquare(square2)) << endl;

    cout << "This should be True : " << boolToString(IsMagicSquare(square3)) << endl;
    cout << "This should be False : " << boolToString(IsMagicSquare(square4)) << endl;
}

/**
 * @brief checkLineSum checks to make sure the line sums up to expected sum 
 * @param square Grid with magic square
 * @param row starting row
 * @param col starting column
 * @param dRow the offset to move in the row direction its checking
 * @param dCol the offset to move in the col direction its checking
 * @param expectedSum what it should add up to
 * @return true if matches expected sum
 */
bool checkLineSum(Grid<int> &square, int row, int col, int dRow, int dCol, int expectedSum)
{
    for (int i = 0; i < square.numCols(); i++) {
        expectedSum -= square[row][col];
        row += dRow;
        col += dCol;
    }

    return expectedSum == 0;
}

/**
 * @brief sumFirstLine Gets the sum of the first line
 * @param square Grid holding magic square
 * @return the sum of the first line
 */
int sumFirstLine(Grid<int> &square)
{
    int sum = 0;
    for (int i = 0; i < square.numRows(); i++) {
        sum += square[0][i];
    }
    return sum;
}

/**
 * @brief IsMagicSquare Gets the sum of the first line, then checks to make sure all rows, columns, and diagnols have the same sum
 * @param square Grid with magic square
 * @return True if magic square
 */
bool IsMagicSquare(Grid<int> &square)
{
    int expectedSum = sumFirstLine(square);

    for (int i = 0; i < square.numRows(); i++) {
        if (!checkLineSum(square, i, 0, 0, 1, expectedSum))
            return false;
        if (!checkLineSum(square, 0, i, 1, 0, expectedSum))
            return false;
    }
    if (!checkLineSum(square, 0, 0, 1, 1, expectedSum))
        return false;

    return checkLineSum(square, square.numCols() - 1, 0, -1, 1, expectedSum);
};

// ************************************************ Question 06 ************************************************

bool checkSodukoLine(Grid<int> &board, int row, int col, int dRow, int dCol);
bool checkSodukoSolution(Grid<int> &board);
bool checkSodukoSquare(Grid<int> &board, int row, int col);

void question_06()
{
    Grid<int> sBoard1 = {{3, 9, 2, 4, 6, 5, 8, 1, 7}, // First line good, Solution Good
                         {7, 4, 1, 8, 9, 3, 6, 2, 5},
                         {6, 8, 5, 2, 7, 1, 4, 3, 9},
                         {2, 5, 4, 1, 3, 8, 7, 9, 6},
                         {8, 3, 9, 6, 2, 7, 1, 5, 4},
                         {1, 7, 6, 9, 5, 4, 2, 8, 3},
                         {9, 6, 7, 5, 8, 2, 3, 4, 1},
                         {4, 2, 3, 7, 1, 9, 5, 6, 8},
                         {5, 1, 8, 3, 4, 6, 9, 7, 2}};
    Grid<int> sBoard2 = {{3, 9, 2, 4, 1, 5, 8, 1, 7}, // First line Bad, Solution bad
                         {7, 4, 1, 8, 9, 3, 6, 2, 5},
                         {6, 8, 5, 2, 7, 1, 4, 3, 9},
                         {2, 5, 4, 1, 3, 8, 7, 9, 6},
                         {8, 3, 9, 6, 2, 7, 1, 5, 4},
                         {1, 7, 6, 9, 5, 4, 2, 8, 3},
                         {9, 6, 7, 5, 8, 2, 3, 4, 1},
                         {4, 2, 3, 7, 1, 9, 5, 6, 8},
                         {5, 1, 8, 3, 4, 6, 9, 7, 2}};

    bool firstLineOkay = checkSodukoLine(sBoard1, 0, 0, 0, 1);
    bool solutionGood = checkSodukoSolution(sBoard1);
    bool firstSquareOkay = checkSodukoSquare(sBoard1, 0, 0);

    bool solutionBad = checkSodukoSolution(sBoard2);
    bool firstLinebad = checkSodukoLine(sBoard2, 0, 0, 0, 1);
    bool secondSquareBad = checkSodukoSquare(sBoard2, 0, 3);

    cout << "The first line is okay - This should be True : " << boolToString(firstLineOkay)
         << endl;
    cout << "The solution is good - This should be True : " << boolToString(solutionGood) << endl;
    cout << "The first square is good - This should be True : " << boolToString(firstSquareOkay)
         << endl
         << endl;
    cout << "The first line is bad - This should be False : " << boolToString(firstLinebad) << endl;
    cout << "The solution is bad - This should be False : " << boolToString(solutionBad) << endl;
    cout << "The second square is bad - This should be False : " << boolToString(secondSquareBad)
         << endl;
}

/**
 * @brief checkSodukoSquare Checks an individual 3x3 to make sure theres no repeats
 * @param board whole board
 * @param row int to start at
 * @param col int to start at
 * @return true if part of a valid solution
 */
bool checkSodukoSquare(Grid<int> &board, int row, int col)
{
    const int SQUARE_SIZE = 3;
    Set<int> usedNums;

    for (int i = row; i < row + SQUARE_SIZE; i++) {
        for (int j = col; j < col + SQUARE_SIZE; j++) {
            int num = board[i][j];

            if (usedNums.contains(num))
                return false;
            usedNums.add(num);
        }
    }
    return true;
}

/**
 * @brief checkSodukoLine Checks a row or col to make sure all the numbers are unique and in the range 1-9
 * @param board Grid containing suduko board
 * @param row Int row to start at
 * @param col int Col to start at
 * @param dRow int direction for row
 * @param dCol int direction for col
 * @return 
 */
bool checkSodukoLine(Grid<int> &board, int row, int col, int dRow, int dCol)
{
    //    cout << "Checking soduko line row: " << row << " col: " << col << " dRow: " << dRow
    //         << " dCol: " << dCol << endl;
    const int BOARD_SIZE = 9;
    Set<int> usedNums;

    for (int i = 0; i < BOARD_SIZE; i++) {
        const int current_num = board[row][col];

        if (usedNums.contains(current_num))
            return false;

        usedNums.add(current_num);
        row += dRow;
        col += dCol;
    }
    return true;
}

/**
 * @brief checkSodukoLine Checks all rows vertically or horizontally depending on whats passed
 * @param board Grid containing suduko board
 * @param dRow Move down rows while checking
 * @param dCol Move through columns while checking
 * @return 
 */
bool checkLines(Grid<int> &board, int dRow, int dCol)
{
    const int BOARD_SIZE = 9;
    int row = 0;
    int col = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {
        // The values for column and row direction are reversed, because we want it to move through a column in
        // check soduko line when checkLines is running through rows and vice versa
        if (!checkSodukoLine(board, row, col, dCol, dRow))
            return false;

        // Multiplying the direciton by the iterator gives the correct index, or doesn't change it if
        // if its not suppose to be moving
        row = i * dRow;
        col = i * dCol;
    }

    return true;
}

bool checkSodukoSolution(Grid<int> &board)
{
    const int GRID_SIZE = 3;
    const int BOARD_SIZE = 9;

    if (board.numCols() != BOARD_SIZE || board.numRows() != BOARD_SIZE) {
        cerr << "The board isn't 9x9! THE BOARD HAS TO BE 9x9!!!!!" << endl;
        return false;
    }
    // Check rows
    if (!checkLines(board, 1, 0))
        return false;
    // Check columns
    if (!checkLines(board, 0, 1))
        return false;

    for (int i = 0; i < BOARD_SIZE; i += GRID_SIZE) {
        for (int j = 0; j < BOARD_SIZE; j += GRID_SIZE) {
            if (!checkSodukoSquare(board, i, j))
                return false;
        }
    }

    return true;
}

// ************************************************ Question 07 ************************************************
/// Write a program that uses a stack to reverse a sequence of integers read in one per
/// line from the console, as shown in the following sample run:
/// ReverseList
/// Enter a list of integers, ending with 0:
/// > 10
/// > 20
/// > 30
/// > 40
/// > 0
/// Those integers in reverse order are:
/// 40
/// 30
/// 20
/// 10

void question_07()
{
    int input;
    Stack<int> nums;

    cout << "Enter a list of integers ending with 0." << endl;

    while (true) {
        input = getInteger(">");
        if (input == 0)
            break;
        nums.push(input);
    }

    while (!nums.isEmpty()) {
        cout << nums.pop() << endl;
    }
}

// ************************************************ Question 08 ************************************************
/// Write a C++ program that checks whether the bracketing operators (parentheses,
/// brackets, and curly braces) in a string are properly matched. As an example of
/// proper matching, consider the string
/// { s = 2 * (a[2] + 3); x = (1 + (2)); }
/// If you go through the string carefully, you discover that all the bracketing operators
/// are correctly nested, with each open parenthesis matched by a close parenthesis, each
/// open bracket matched by a close bracket, and so on. On the other hand, the
/// following strings are all unbalanced for the reasons indicated:
/// (([]) The line is missing a close parenthesis.
/// )( The close parenthesis comes before the open parenthesis.
/// {(}) The bracketing operators are improperly nested.
/// Using Abstract Data Types – 169 –
/// The reason that this exercise fits in this chapter is that one of the simplest strategies
/// for implementing this program is to store the unmatched operators on a stack.

/**
 * @brief checkIsCloseBracket Checks to make sure currentChar is the closing bracket to next char
 * The brackets are reversed due to using stack, it could be reversed first to improve code readability
 * but this is more efficient
 * @param currentChar Closing bracket
 * @param nextChar opening bracket
 * @return True if brackets match
 */
bool checkIsCloseBracket(char currentChar, char nextChar)
{
    return ((nextChar == '(' && currentChar == ')') || (nextChar == '[' && currentChar == ']')
            || (nextChar == '{' && currentChar == '}'));
}

/**
 * @brief checkBracketClosure Checks to make sure the closing and opening brackets in a string match
 * @param str string to check
 * @return True if they match
 */
bool checkBracketClosure(string &str)
{
    Stack<char> foundB;
    const Set<char> BRACKETS = {'(', ')', '{', '}', '[', ']'};

    for (char c : str)
        if (BRACKETS.contains(c)) {
            if (!foundB.isEmpty() && checkIsCloseBracket(c, foundB.peek()))
                foundB.pop();
            else
                foundB.push(c);
        }

    return foundB.isEmpty();
}

void question_08()
{
    string codeLine1 = "{ s = 2 * (a[2] + 3); x = (1 + (2)); }";
    string codeLine2 = "{ s = 2 * ((a[2] + 3)(); x = (1 + (2)); }";
    cout << codeLine1 << endl;
    cout << "The above line has proper bracket closure (should be true): "
         << boolToString(checkBracketClosure(codeLine1)) << endl;
    cout << codeLine2 << endl;
    cout << "The above line does not have proper bracket closure (this should be false): "
         << boolToString(checkBracketClosure(codeLine2)) << endl;
}

// ************************************************ Question 13 ************************************************
/// write a program to simulate the following experiment, which was included in the
/// 1957 Disney film, Our Friend the Atom, to illustrate the chain reactions involved in
/// nuclear fission. The setting for the experiment is a large cubical box, the bottom of
/// which is completely covered with an array of 625 mousetraps, arranged to form a
/// square grid 25 mousetraps on a side. Each of the mousetraps is initially loaded with
/// two ping-pong balls. At the beginning of the simulation, an additional ping-pong
/// ball is released from the top of the box and falls on one of the mousetraps. That
/// mousetrap springs and shoots its two ping-pong balls into the air. The ping-pong
/// balls bounce around the sides of the box and eventually land on the floor, where they
/// are likely to set off more mousetraps.
/// In writing this simulation, you should make the following simplifying
/// assumptions:
/// Using Abstract Data Types – 170 –
/// • Every ping-pong ball that falls always lands on a mousetrap, chosen randomly by
/// selecting a random row and column in the grid. If the trap is loaded, its balls are
/// released into the air. If the trap has already been sprung, having a ball fall on it
/// has no effect.
/// • Once a ball falls on a mousetrap—whether or not the trap is sprung—that ball
/// stops and takes no further role in the simulation.
/// • Balls launched from a mousetrap bounce around the room and land again after a
/// random number of simulation cycles have gone by. That random interval is
/// chosen independently for each ball and is always between one and four cycles.
/// Your simulation should run until there are no balls in the air. At that point, your
/// program should report how many time units have elapsed since the beginning, what
/// percentage of the traps have been sprung, and the maximum number of balls in the
/// air at any time in the simulation.

const int MIN_T_CYCLE = 1;
const int MAX_T_CYCLE = 4;
const int GRID_SIZE = 25;
const char MOUSE_TRAP = 'M';
const char SPRUNG_TRAP = 'S';

void launchBalls(Vector<int> &ballsInAir);
void processTimeForBalls(Vector<int> &ballsInAir);
int getBallsDropped(Vector<int> &ballsInAir);

void question_13()
{
    int gridX;
    int gridY;
    int timeCycle = 0;
    int droppedBalls = 0;
    int remainingTraps = GRID_SIZE * GRID_SIZE;
    Vector<int> ballsInAir = {0};
    Grid<char> floor(GRID_SIZE, GRID_SIZE);
    floor.fill(MOUSE_TRAP);
    launchBalls(ballsInAir);

    while (ballsInAir.size() > 0) {
        processTimeForBalls(ballsInAir);
        droppedBalls = getBallsDropped(ballsInAir);
        for (int i = droppedBalls; i > 0; i--) {
            gridX = randomInt(0, GRID_SIZE);
            gridY = randomInt(0, GRID_SIZE);

            if (floor[gridX][gridY] == MOUSE_TRAP) {
                launchBalls(ballsInAir);
                floor[gridX][gridY] = SPRUNG_TRAP;
                remainingTraps--;
            }
        }
        timeCycle++;
    }

    cout << "It took " << timeCycle << " time cycles to complete the simulation." << endl;
    cout << "Of " << GRID_SIZE * GRID_SIZE << " traps, " << remainingTraps
         << " traps remain unsprung." << endl;
    cout << "Thats " << (remainingTraps / double(GRID_SIZE * GRID_SIZE)) * 100 << " precent."
         << endl;
}

/**
 * @brief processTimeForBalls Iterates over the ballsInAir vector and decreases everything by one time count
 * @param ballsInAir vector of ints representing balls by remaining air time
 */
void processTimeForBalls(Vector<int> &ballsInAir)
{
    for (int i = 0; i < ballsInAir.size(); i++) {
        if (ballsInAir[i] > 0)
            ballsInAir[i]--;
    }
}

/**
 * @brief getBallsDropped Looks for balls in loop which air time has reached zero and removes them from the loop
 * Then returns the total balls removed
 * @param ballsInAir vector of ints representing balls by remaining air time
 * @return Balls that have hit the floor
 */
int getBallsDropped(Vector<int> &ballsInAir)
{
    int dropped = 0;
    for (int i = 0; i < ballsInAir.size(); i++) {
        if (ballsInAir[i] == 0) {
            ballsInAir.remove(i);
            i--;
            dropped++;
        }
    }
    return dropped;
}

/**
 * @brief launchBalls Adds 2 new balls in the air, with a random time cycle
 * @param ballsInAir[in] Vector containing the air time for any current balls in the air to update
 */
void launchBalls(Vector<int> &ballsInAir)
{
    ballsInAir.push_back(randomInt(MIN_T_CYCLE, MAX_T_CYCLE));
    ballsInAir.push_back(randomInt(MIN_T_CYCLE, MAX_T_CYCLE));
}

int main()
{
    srand(time(0));
    question_13();
    return 0;
}
