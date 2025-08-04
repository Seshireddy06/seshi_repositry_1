#include <iostream>
#include <cmath>
using namespace std;

class Calculator {
public:
    double add(double a, double b) { return a + b; }
    double subtract(double a, double b) { return a - b; }
    double multiply(double a, double b) { return a * b; }
    double divide(double a, double b) {
        if (b == 0) throw runtime_error("Division by zero");
        return a / b;
    }
    double sqrt(double a) {
        if (a < 0) throw runtime_error("Cannot take square root of negative number");
        return std::sqrt(a);
    }
};

class CalculatorUI {
public:
    void run() {
        Calculator calc;
        double num1, num2, result;
        char op;

        cout << "Enter first number: ";
        cin >> num1;
        cout << "Enter operator (+, -, *, /, s for sqrt): ";
        cin >> op;

        try {
            if (op == 's') {
                result = calc.sqrt(num1);
                cout << "Result: " << result << endl;
                return;
            }

            cout << "Enter second number: ";
            cin >> num2;

            switch (op) {
                case '+': result = calc.add(num1, num2); break;
                case '-': result = calc.subtract(num1, num2); break;
                case '*': result = calc.multiply(num1, num2); break;
                case '/': result = calc.divide(num1, num2); break;
                default:
                    cout << "Invalid operator\n";
                    return;
            }
            cout << "Result: " << result << endl;
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
};

#include <thread>

using namespace std;

int main() {
    CalculatorUI ui;
    thread uiThread(&CalculatorUI::run, &ui);
    uiThread.join();
    return 0;
}
