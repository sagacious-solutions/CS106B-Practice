#include <console.h>
#include <ctime>
#include <fstream>
#include <grid.h>
#include <set.h>
#include <simpio.h>
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
    bool winner = false;
    char player = 'X';

    while (!winner) {
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
        if (winner = CheckForWin(board, 'O')) {
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
    cout << "The first line is okay - This should be True : " << boolToString(firstLineOkay)
         << endl;
    bool firstLinebad = checkSodukoLine(sBoard2, 0, 0, 0, 1);
    cout << "The first line is bad - This should be False : " << boolToString(firstLinebad) << endl;
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

bool checkSodukoSolution()
{
    return true;
}

int main()
{
    srand(time(0));
    question_06();
    return 0;
}
