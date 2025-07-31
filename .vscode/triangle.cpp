#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of rows: ";
    cin >> n;

    // Left-aligned triangle
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= i; ++j) {
            cout << "*";
        }
        cout << endl;
    }
    
    // Equilateral triangle
    cout << "\nEquilateral triangle pattern:\n";
    for(int i = 1; i <= n; ++i) {
        // Print spaces
        for(int s = 1; s <= n - i; ++s) {
            cout << "  ";
        }
        // Print stars
        for(int j = 1; j <= 2 * i - 1; ++j) {
            cout << "* ";
        }
        cout << endl;
    }
    return 0;
}