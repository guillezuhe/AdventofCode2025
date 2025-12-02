#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

long long findInvalid(long long start, long long end) {
  long long sum = 0;
  // Invalid IDs are those that are composed by a sequence of digits repeated twice
  // For example: 55, 6464, 123123
  
  // To save computation, we will restrict to IDs with an even number of digits
  // First we check the number of digits in start and end
  int start_digits = to_string(start).length();
  int end_digits = to_string(end).length();

  if (start_digits % 2 != 0) {
    start_digits++;
    start = pow(10, start_digits - 1); // Move to the next even digit number
  }

  if (end_digits % 2 != 0) {
    end_digits--;
    end = pow(10, end_digits) - 1; // Move to the previous even digit number
  }


  for (long long num = start; num <= end; num++) {
    string num_str = to_string(num);
    int len = num_str.length();
    if (len % 2 != 0) continue; // Skip odd length numbers

    string first_half = num_str.substr(0, len / 2);
    string second_half = num_str.substr(len / 2);

    if (first_half == second_half) {
      sum += num;
    }
  }
  return sum;
}



long long CountInvalidId() {
  long long invalid_sum = 0;

  // Read file of ID ranges
  ifstream file("input.dat");
  string line;

  while (getline(file, line)) {
    // Ranges are in a single line, separated by commas
    while(line.length() > 0) {
      size_t comma_pos = line.find(',');
      string range;
      if (comma_pos == string::npos) {
        // Last range without a comma at the end
        range = line;
        line = "";
      } else {
        range = line.substr(0, comma_pos);
        line = line.substr(comma_pos + 1);
      }

      // Each range has format "start-end"
      size_t dash_pos = range.find('-');
      long long start = stoll(range.substr(0, dash_pos));
      long long end = stoll(range.substr(dash_pos + 1));

      // Find the number of invalid IDs in this range
      invalid_sum += findInvalid(start, end);
    }
  }

  return invalid_sum;
}



int main() {

  cout << "Total number of invalid IDs: " << CountInvalidId() << endl;

  return 0;
}