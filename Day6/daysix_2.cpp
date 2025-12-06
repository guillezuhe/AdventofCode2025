#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

long long totalSum() {
  long long sum = 0;
  vector<vector <char>> numbers;
  vector<char> symbols;
  bool lastLine = false;
  int max_row_length = 0;

  string filename = "input.dat";

  // Read the matrix from file
  ifstream file(filename);
  string line;
  while (getline(file, line)) {
    vector<char> row;
    // Iterate over characters in the line
    for (char& ch : line) {
      if (ch == '*' || ch == '+') {
        symbols.push_back(ch);
        lastLine = true;
      } else if (!lastLine) {
        row.push_back(ch);
      }
    }
    if (!lastLine) {
      numbers.push_back(row);
      if (row.size() > max_row_length) {
        max_row_length = row.size();
      }
    }
  }

  // Add white spaces to shorter rows at the end
  for (auto& row : numbers) {
    while (row.size() < max_row_length) {
      row.push_back(' ');
    }
  }

  file.close();

  long long colResult = 0;
  int sym_index = symbols.size() - 1;
  if (symbols[sym_index] == '*') {
    colResult = 1;
  }
  for (int j = max_row_length - 1; j >= -1; j--) {
    // Check if all the characters in this column are spaces
    bool allSpaces = true;
    if (j < 0) {
      allSpaces = false;
      sum += colResult;
      break;
    }
    for (int i = 0; i < numbers.size(); i++) {
      if (numbers[i][j] != ' ') {
        allSpaces = false;
      }
    }
    if (allSpaces) {
      sym_index--;
      sum += colResult;
      if (symbols[sym_index] == '*') {
        colResult = 1;
      } else {
        colResult = 0;
      }
      continue;
    }
    // Build the column number
    string colNumberStr = "";
    for (int i = 0; i < numbers.size(); i++) {
      if (numbers[i][j] != ' ') {
        colNumberStr += numbers[i][j];
      }
    }
    if (symbols[sym_index] == '+') {
      colResult += stoi(colNumberStr);
    } else if (symbols[sym_index] == '*') {
      colResult *= stoi(colNumberStr);
    }
    
  }
  return sum;
}

int main() {
  long long sum = totalSum();
  cout << "Total sum: " << sum << endl;
  return 0;
}