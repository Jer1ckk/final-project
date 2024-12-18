#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>

using namespace std;
int main() {
    set<int> uniqueNumbers;
    srand(time(0));

    while (uniqueNumbers.size() < 10) {
        int randomNumber = (rand() % 50) + 1; 
        uniqueNumbers.insert(randomNumber);  
    }

    cout << "10 Unique Random Numbers between 1 and 50:\n";
    for (int num : uniqueNumbers) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
