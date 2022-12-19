#include <iostream>
#include <vector>

// Function to check if it is safe to place a queen at a given position
bool isSafe(std::vector<std::vector<bool>> &board, int row, int col, int n)
{
    // check if there is a queen in the same column
    for (int i = 0; (i < row); i++)
    {
        if (board[i][col])
        {
            return false;
        }
    }

    // check upper left diagonal
    for (int i = row, j = col; (i >= 0 && j >= 0); i--, j--)
    {
        if (board[i][j])
        {
            return false;
        }
    }

    // check upper right diagonal
    for (int i = row, j = col;( i >= 0 && j < n); i--, j++)
    {
        if (board[i][j])
        {
            return false;
        }
    }

    return true;
}

// Function to solve the n-queens problem
bool solveNQueensUtil(std::vector<std::vector<bool>> &board, int row, int n)
{
    // base case: if all queens are placed, return true
    if (row == n)
    {
        return true;
    }

    // try placing a queen in each column of the current row
    for (int col = 0; (col < n); col++)
    {
        // if it is safe to place a queen at board[row][col]
        if (isSafe(board, row, col, n))
        {
            // place the queen
            board[row][col] = true;

            // recursively solve the rest of the problem
            if (solveNQueensUtil(board, row + 1, n))
            {
                return true;
            }

            // backtrack: remove the queen from board[row][col]
            board[row][col] = false;
        }
    }

    // if the queen cannot be placed in any column of the current row, return false
    return false;
}

int main()
{
    int n = 0;

    std::cout << "How many queens to place on the board? ";
    std::cin >> n;

    if (std::cin.fail() || n < 1)
    {
        std::cout << "error: invalid input\n";

        return 1;
    }

    // damn you and your grading program
    std::cout << "\n";

    // create an empty board
    std::vector<std::vector<bool>> board;

    // fill board with empty tiles
    for (int i = 0; (i < n); i++)
    {
        board.push_back(std::vector<bool>());
        for (int j = 0; (j < n); j++)
        {
            board[i].push_back(false);
        }
    }

    if (solveNQueensUtil(board, 0, n))
    {
        // print the solution
        for (int i = 0; (i < n); i++)
        {
            for (int j = 0; (j < n); j++)
            {
                board[i][j] ? std::cout << "Q" : std::cout << ".";
            }

            std::cout << std::endl;
        }
    }
    else
    {
        std::cout << "No solution found to place " << n << " queens on a " << n << " by " << n << " chess board\n";
    }

    return 0;
}
