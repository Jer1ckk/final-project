#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(static_cast<unsigned>(time(0))); // Seed for random numbers

    // Create a vector with numbers 1 to 50
    vector<int> numbers;
    for (int i = 1; i <= 50; ++i) {
        numbers.push_back(i);
    }

    // Shuffle the vector randomly
    random_shuffle(numbers.begin(), numbers.end());

    // Print the first 10 numbers
    cout << "Random numbers (no duplicates): ";
    for (int i = 0; i < 10; ++i) {
        cout << numbers[i] << " ";
    }
    
    cout << endl;
    return 0;
}
