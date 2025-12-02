#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int CountZeros(const int init_val = 50){
  int count = 0;
  int current_val = init_val;
  int prev_val = init_val;

  // Read file the operations
  ifstream file("input.dat");
  string line;

  while (getline(file, line)) {
    // Line has format Ln, with L being a letter and n being a number
    char operation = line[0];
    int number = stoi(line.substr(1));

    if (operation == 'R') {
      count += (current_val + number) / 100;
      current_val = (current_val + number) % 100;
    } else if (operation == 'L') {
      count += -(current_val - number - 100) / 100 + (current_val - 100) / 100;
      current_val = ((current_val - number) % 100 + 100) % 100;
    }

  }
  file.close();

  return count;
}

int main() {

  cout << "Number of times zero is crossed: " << CountZeros(50) << endl;

  return 0;
}