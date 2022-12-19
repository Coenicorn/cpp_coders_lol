#include <iostream>
#include <vector>

using namespace std;

int N; // global variable to store the number of queens

// Function to check if it is safe to place a queen at a given position
bool isSafe(vector<vector<int>> &board, int row, int col)
{
    // check if there is a queen in the same column
    for (int i = 0; i < row; i++)
        if (board[i][col])
            return false;

    // check upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // check upper right diagonal
    for (int i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j])
            return false;

    return true;
}

// Function to solve the N-queens problem
bool solveNQueensUtil(vector<vector<int>> &board, int row)
{
    // base case: if all queens are placed, return true
    if (row == N)
        return true;

    // try placing a queen in each column of the current row
    for (int col = 0; col < N; col++)
    {
        // if it is safe to place a queen at board[row][col]
        if (isSafe(board, row, col))
        {
            // place the queen
            board[row][col] = 1;

            // recursively solve the rest of the problem
            if (solveNQueensUtil(board, row + 1))
                return true;

            // backtrack: remove the queen from board[row][col]
            board[row][col] = 0;
        }
    }

    // if the queen cannot be placed in any column of the current row, return false
    return false;
}

int main()
{
    cout << "Enter the number of queens: ";
    cin >> N;

    // create an empty board
    vector<vector<int>> board(N, vector<int>(N, 0));

    if (solveNQueensUtil(board, 0))
    {
        cout << "Solution found:" << endl;

        // print the solution
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                cout << board[i][j] << "  ";
            cout << endl;
        }
    }
    else
    {
        cout << "No solution found." << endl;
    }

    return 0;
}
