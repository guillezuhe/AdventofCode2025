#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

int numberOfRolls() {
  string filename = "input.dat";
  // Read the matrix from file
  ifstream file(filename);
  string line;

  // Count the rows and columns of the matrix
  int nrows = 0;
  int ncols = 0;
  while (getline(file, line)) {
    ncols = line.length();
    nrows++;
  }
  file.close();
  // Define the matrix and store the values
  char matrix[nrows][ncols];
  char new_matrix[nrows][ncols];
  file.open(filename);
  int row = 0;
  while (getline(file, line)) {
    for (int col = 0; col < ncols; ++col) {
      matrix[row][col] = line[col];
      new_matrix[row][col] = line[col];
    }
    row++;
  }
  file.close();

  int nrolls = 0;
  bool accesible = true;

  while (accesible) {
    accesible = false;
    // Check the neighbors of each element
    for (int i = 0; i < nrows; ++i) {
      for (int j = 0; j < ncols; ++j) {
        int neigh_rolls = 0;
        // Check neighbors
        for (int ni = i-1; ni <= i+1; ++ni) {
          for (int nj = j-1; nj <= j+1; ++nj) {
            if (ni == i && nj == j) continue; // Skip itself
            if (ni >= 0 && ni < nrows && nj >= 0 && nj < ncols) {
              if (matrix[ni][nj] == '@') {
                neigh_rolls++;
              }
            }
          }
        }
        if (neigh_rolls < 4 && matrix[i][j] == '@') {
          nrolls++;
          accesible = true;
          new_matrix[i][j] = '.';
        }
      }
    }

      // Copy new_matrix to matrix
    for (int i = 0; i < nrows; ++i) {
      for (int j = 0; j < ncols; ++j) {
        matrix[i][j] = new_matrix[i][j];
      }
    }
  }
  return nrolls;
}

int main() {
  int nrolls = numberOfRolls();
  cout << "Number of rolls: " << nrolls << endl;
  return 0;
}