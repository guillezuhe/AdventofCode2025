#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

int numberOfIngredients() {
  int ningred = 0;

  vector<tuple<long long, long long>> ranges;
  string filename = "input.dat";
  // Read the matrix from file
  ifstream file(filename);
  string line;

  while (getline(file, line)) {
    if (line.empty()) {
      break; // Stop reading on empty line
    }
    int dashPos = line.find('-');

    long long start = stoll(line.substr(0, dashPos));
    long long end = stoll(line.substr(dashPos + 1, line.length() - dashPos - 1));

    ranges.push_back(make_tuple(start, end));
  }

  // Continue now reading the ingredient ids
  while (getline(file, line)) {
    long long ingredientId = stoll(line);

    // Check if the ingredientId falls within any of the ranges
    for (const auto& range : ranges) {
      if (ingredientId >= get<0>(range) && ingredientId <= get<1>(range)) {
        ningred++;
        break; // No need to check other ranges
      }
    }
  
  }
  file.close();
  return ningred;
}

int main() {
  int ningred = numberOfIngredients();
  cout << "Number of ingredients: " << ningred << endl;
  return 0;
}