#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

long long CountBatteries() {
  long long sum = 0;
  long long max = 0;
  int n_digits = 12;

  // Read battery banks from file
  ifstream file("input.dat");
  string line;

  while (getline(file, line)) {
    max = 0;
    int prev_dig_pos = -1;
    for (int n=n_digits; n>0; --n) {
      int max_dig = 0;
      int max_dig_pos = 0;
      for (int i=line.length() - n; i>prev_dig_pos; --i) {
        int dig = line[i] - '0';
        if (dig >= max_dig) {
          max_dig = dig;
          max_dig_pos = i;
        }
      }
      max += max_dig * pow(10, n - 1);
      prev_dig_pos = max_dig_pos;
    }
    sum += max;
  }
  return sum;
}

// The idea of the code is to construct the largest possible 12-digit battery ID
// by selecting digits from the input line while maintaining their relative order.

// For each digit position from the most significant to the least significant,
// we find the maximum digit that can be placed in that position without violating
// the relative order constraint. That is, for the of order n, we look for the maximum digit
// in the substring of the line that has enough remaining digits to fill the subsequent positions.
// For equal digits, we choose the leftmost one to maximize the subsequent opportunities.

int main() {
  long long sum = CountBatteries();
  cout << "Battery IDs sum: " << sum << endl;
  return 0;
}