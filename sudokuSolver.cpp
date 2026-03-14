#include <iostream>
#include <vector>

using namespace std;

// Function to check if placing 'num' in board[row][col] is valid
bool isValid(int board[9][9], int row, int col, int num) {
    for (int i = 0; i < 9; i++) {
        // Check row and column constraints
        if (board[row][i] == num || board[i][col] == num) {
            return false;
        }
        
        // Check 3x3 subgrid constraint
        // (row/3)*3 gives the starting row of the box
        if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == num) {
            return false;
        }
    }
    return true;
}

// Backtracking function to solve the puzzle
bool solveSudoku(int board[9][9]) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            
            if (board[row][col] == 0) { // Find an empty cell
                for (int num = 1; num <= 9; num++) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num; // Tentative assignment
                        
                        if (solveSudoku(board)) {
                            return true; // Success!
                        }
                        
                        board[row][col] = 0; // Backtrack (Reset)
                    }
                }
                return false; // No valid number found for this cell
            }
        }
    }
    return true; // All cells filled
}

void printBoard(int board[9][9]) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) cout << "---------------------" << endl;
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) cout << "| ";
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int board[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(board)) {
        cout << "Sudoku Solved:" << endl << endl;
        printBoard(board);
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}