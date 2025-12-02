#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int CountZeros(const int init_val = 50){
  int count = 0;
  int current_val = init_val;

  // Read file the operations
  ifstream file("input.dat");
  string line;

  while (getline(file, line)) {
    // Line has format Ln, with L being a letter and n being a number
    char operation = line[0];
    int number = stoi(line.substr(1));

    if (operation == 'R') {
      current_val += number;
    } else if (operation == 'L') {
      current_val -= number;
    }

    // Apply boundary conditions.
    // Value wraps around if it goes below 0 or above 99.
    current_val = current_val % 100;


    if (current_val == 0) {
      count++;
    }
  }
  file.close();

  return count;
}

int main() {

  cout << "Number of times value reaches zero: " << CountZeros(50) << endl;

  return 0;
}