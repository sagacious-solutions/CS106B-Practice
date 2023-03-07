#include <console.h>
#include <ctime>
#include <fstream>
#include <grid.h>
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
    Grid<char> board(3, 3);
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

int main()
{
    srand(time(0));
    question_04();
    return 0;
}
