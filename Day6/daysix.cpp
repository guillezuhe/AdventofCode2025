#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

long long totalSum() {
  long long sum = 0;
  vector<vector <int>> numbers;
  vector<string> symbols;
  bool lastLine = false;

  string filename = "input.dat";

  // Read the matrix from file
  ifstream file(filename);
  string line;
  while (getline(file, line)) {
    vector<int> row;

    stringstream ss(line);
    string word;
    while(getline(ss, word, ' ')) {
      if (word.empty()) {
        continue; // Skip empty strings from multiple spaces
      }
      if (word == "*" || word == "+") {
        symbols.push_back(word);
        lastLine = true;
      } else {
        row.push_back(stoi(word));
      }
    }
    if (lastLine) {
      break;
    }
    numbers.push_back(row);
  }
  file.close();

  long long colResult = 0;
  for (int j = 0; j < numbers[0].size(); j++) {
    if (symbols[j] == "+") {
      colResult = 0;
      for (int i = 0; i < numbers.size(); i++) {
        colResult += numbers[i][j];
      }
      cout << "Column " << j << " sum: " << colResult << endl;
    } else if (symbols[j] == "*") {
      colResult = 1;
      for (int i = 0; i < numbers.size(); i++) {
        colResult *= numbers[i][j];
      }
      cout << "Column " << j << " product: " << colResult << endl;
    }
    sum += colResult;
  }

  return sum;
}

int main() {
  long long sum = totalSum();
  cout << "Total sum: " << sum << endl;
  return 0;
}