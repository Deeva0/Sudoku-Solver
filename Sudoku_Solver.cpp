#include <iostream>
using namespace std;

// Function to print the Sudoku grid
void printGrid(int **grid, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if it is safe to place the number in the given row and column
bool isSafe(int **grid, int row, int col, int num, int size)
{
    // Check if the number already exists in the row
    for (int i = 0; i < size; i++)
    {
        if (grid[row][i] == num)
        {
            return false;
        }
    }

    // Check if the number already exists in the column
    for (int i = 0; i < size; i++)
    {
        if (grid[i][col] == num)
        {
            return false;
        }
    }

    // Check if the number already exists in the box
    int boxSize = size / 3;
    int startRow = row - row % boxSize;
    int startCol = col - col % boxSize;
    for (int i = 0; i < boxSize; i++)
    {
        for (int j = 0; j < boxSize; j++)
        {
            if (grid[i + startRow][j + startCol] == num)
            {
                return false;
            }
        }
    }

    // If no conflicts, it is safe to place the number
    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int **grid, int size)
{
    int row, col;
    bool isEmpty = false;

    // Find an empty cell
    for (row = 0; row < size; row++)
    {
        for (col = 0; col < size; col++)
        {
            if (grid[row][col] == 0)
            {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty)
        {
            break;
        }
    }

    // If no empty cell found, the puzzle is solved
    if (!isEmpty)
    {
        return true;
    }

    // Try placing numbers from 1 to size in the empty cell
    for (int num = 1; num <= size; num++)
    {
        if (isSafe(grid, row, col, num, size))
        {
            grid[row][col] = num;

            // Recursively solve the puzzle
            if (solveSudoku(grid, size))
            {
                return true;
            }

            // If the number doesn't lead to a solution, undo the placement
            grid[row][col] = 0;
        }
    }

    // If no number can be placed, backtrack and try a different number
    return false;
}

int main()
{
    int size;

    cout << "Enter the size of the Sudoku grid: ";
    cin >> size;

    int **grid = new int *[size];
    for (int i = 0; i < size; i++)
    {
        grid[i] = new int[size];
    }

    cout << "Enter the Sudoku grid (use 0 for empty cells):\n";
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cin >> grid[i][j];
        }
    }

    if (solveSudoku(grid, size))
    {
        cout << "Sudoku puzzle solved successfully:\n";
        printGrid(grid, size);
    }
    else
    {
        cout << "No solution exists for the given Sudoku puzzle.\n";
    }

    // Deallocate memory
    for (int i = 0; i < size; i++)
    {
        delete[] grid[i];
    }
    delete[] grid;

    return 0;
}