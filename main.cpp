#include <chrono>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

// Helper: add two lists representing big numbers (LSB first internally)
list<int> addLists(list<int> &a, list<int> &b) {
  list<int> result;
  auto it = a.begin();
  auto jt = b.begin();
  int carry = 0;
  while (it != a.end() || jt != b.end() || carry) {
    int sum = carry;
    if (it != a.end()) {
      sum += *it++;
    }
    if (jt != b.end()) {
      sum += *jt++;
    }
    result.push_back(sum % 10);
    carry = sum / 10;
  }
  return result;
}

void normal_multiplication(list<int> num1, list<int> num2) {
  // Work right-to-left (LSB first), so reverse both
  list<int> r1(num1.rbegin(), num1.rend());
  list<int> r2(num2.rbegin(), num2.rend());

  list<int> result = {0}; // accumulator

  int shift = 0; // how many zeros to pad at the end (positional offset)
  for (auto it = r1.begin(); it != r1.end(); ++it, ++shift) {
    int carry = 0;
    list<int> partial;

    // Pad with 'shift' zeros for positional value (units, tens, hundreds...)
    for (int s = 0; s < shift; s++)
      partial.push_back(0);

    for (auto jt = r2.begin(); jt != r2.end(); ++jt) {
      int prod = (*it) * (*jt) + carry;
      partial.push_back(prod % 10);
      carry = prod / 10;
    }
    if (carry)
      partial.push_back(carry);

    result = addLists(result, partial);
  }

  // Result is stored LSB-first, print in reverse (MSD first)
  // Strip leading zeros
  while (result.size() > 1 && result.back() == 0)
    result.pop_back();

  cout << "Product: ";
  for (auto it = result.rbegin(); it != result.rend(); ++it)
    cout << *it;
  cout << endl;
}

int main() {
  freopen("input.txt", "r", stdin);
  int n1, n2;
  cin >> n1;
  cin >> n2;

  list<int> num1, num2;
  for (int i = 0; i < n1; i++) {
    int x;
    cin >> x;
    num1.push_back(x);
  }
  for (int i = 0; i < n2; i++) {
    int x;
    cin >> x;
    num2.push_back(x);
  }
  auto start = chrono::high_resolution_clock::now();

  // your function call here
  normal_multiplication(num1, num2);

  auto end = chrono::high_resolution_clock::now();

  // cast to whatever precision you need
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Time: " << duration.count() << " microseconds" << endl;
}
