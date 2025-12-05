#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

long long numberOfIngredients() {
  long long ningred = 0;

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

  file.close();

  for (int i = 0; i < ranges.size(); i++) {
    long long start = get<0>(ranges[i]);
    long long end = get<1>(ranges[i]);

    if (start > end) {
      continue; // Skip invalidated ranges
    }

    // Check if this range overlaps with any future range
    // and adjust the start and end accordingly to avoid double counting
    for (int j = i + 1; j < ranges.size(); j++) {
      long long futureStart = get<0>(ranges[j]);
      long long futureEnd = get<1>(ranges[j]);
      if (futureStart > futureEnd) {
        continue; // Skip invalidated ranges
      }
      if (start <= futureEnd && end >= futureStart) {
        // Case 1: Future end is inside current range
        if (futureStart < start && futureEnd <= end) {
          ranges[j] = make_tuple(get<0>(ranges[j]), start - 1);
        }
        // Case 2: Future start and future end are inside current range
        else if (futureStart >= start && futureEnd <= end) {
          ranges[j] = make_tuple(0, -1); // Invalidate this range
        }
        // Case 3: Future start is inside current range
        else if (futureStart >= start && futureEnd > end) {
          ranges[j] = make_tuple(end + 1, get<1>(ranges[j]));
        }
        // Case 4: Current range is inside future range
        else if (futureStart < start && futureEnd > end) {
          ranges[i] = make_tuple(0, -1); // Invalidate current range
        }
      }
    }
  }

  // Now count the valid ranges
  for (const auto& range : ranges) {
    long long start = get<0>(range);
    long long end = get<1>(range);
    if (start <= end) {
      ningred += (end - start + 1);
    }
  }
  return ningred;
}

int main() {
  long long ningred = numberOfIngredients();
  cout << "Number of ingredients: " << ningred << endl;
  return 0;
}