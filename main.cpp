#include <iostream>
#include <vector>

#define SIZE 9 // size of sudoku board 

using namespace std;

bool possible(vector<vector<int>>& board, int row, int col, int value); // basically checks if it doesnt violate sudoku rules
bool solve(vector<vector<int>>& board, int row, int col);
void print(const vector<vector<int>>& board);


int main()
{
    std::vector<std::vector<int>> sb = {
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
  
      cout << "Sudoku Grid:" << endl;
      print(sb);
  
      bool solved = solve(sb, 0, 0);
      
      if (solved) {
          cout << "\nSolved Sudoku:" << endl;
          print(sb);
      } else {
          cout << "\nNo solution exists." << endl;
      }
  


    return 0;
}

bool possible(vector<vector<int>>& board, int row, int col, int value)
{
    for(int i = 0; i < SIZE; i++)
    {
        if(board[row][i] == value) // if value is already in row
        {
            return false;
        }
    }
    for(int i = 0; i < SIZE; i++)
    {
        if(board[i][col] == value) // if value is already in col
        {
            return false;
        }
    }
    int startRow = 3 * (row/3); // determine starting index in 3x3 subgrid 
    int startCol = 3 * (col/3);

    for (int i = startRow; i < startRow + 3; i++)
    {
        for (int j = startCol; j < startCol + 3; j++)
        {
            if(board[i][j] == value)
            {
                return false;
            }
        }
    }
    return true;
}

bool solve(vector<vector<int>>& board, int row, int col)
{
    if(col == SIZE) // if we reach end of row, move to next row if there is a next one
    {
        if(row == SIZE - 1)
        {
            return true;
        }
        col = 0; //reset to 1st col
        row++;
    }
    if (board[row][col] != 0) //if current cell is filled then move next col
    {
        return solve(board, row, col + 1);
    }
    for ( int i = 1; i <= SIZE; i++) //try numbers 1 through SIZE in current cell
    {
        if(possible(board, row, col, i))
        {
            board[row][col] = i; // place # if valid 
            if(solve(board, row, col + 1)) // next cell and return true if good
            {
                return true;
            }
        }
        board[row][col] = 0; //reset if no valid numbers
    }
    return false;
}

void print(const vector<vector<int>>& board)
{
    for(int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            cout << board[row][col] << " ";
            if((col + 1)% 3 == 0 && col < SIZE - 1)
            {
                cout << "| ";
            }
        }
        cout << endl;
        if((row + 1) % 3 == 0 && row < SIZE - 1)
        {
            cout << "------+-------+------" << endl;
        }
    }
}