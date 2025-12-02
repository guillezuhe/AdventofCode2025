#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

long long findInvalid(long long start, long long end) {
  long long sum = 0;
  // Invalid IDs are those that are composed by a sequence of digits repeated at least twice.
  // For example: 11, 1212, 777777, 123123123 are invalid IDs.

  for (long long num = start; num <= end; ++num) {
    bool is_invalid = false;
    string num_str = to_string(num);
    int tot_len = num_str.length();
    // Check for each possible length of the repeating sequence
    for (int len = 1; len <= tot_len / 2; ++len) {
      if (tot_len % len != 0) continue; // The total length must be a multiple of the sequence length
      string pattern = num_str.substr(0, len);
      for (int i = len; i < tot_len; i += len) {
        if (num_str.substr(i, len) != pattern) {
          break;
        }
        if (i + len == tot_len) {
          is_invalid = true;
        }
      }
    }
    if (is_invalid) {
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