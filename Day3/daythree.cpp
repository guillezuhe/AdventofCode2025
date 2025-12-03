#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

long long CountBatteries() {
  long long sum = 0;
  int max = 0;

  // Read battery banks from file
  ifstream file("input.dat");
  string line;

  while (getline(file, line)) {
    max = 0;
    // Test possible configurations
    for (int i=0; i<line.length(); ++i) {
      for (int j=i+1; j<line.length(); ++j) {
        int battery_id = (line[i] - '0') * 10 + (line[j] - '0');
        if (battery_id > max) {
          max = battery_id;
        }
      }
    }
    sum += max;
  }
  return sum;
}

int main() {
  long long sum = CountBatteries();
  cout << "Battery IDs sum: " << sum << endl;
  return 0;
}