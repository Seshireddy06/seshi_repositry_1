#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <stdexcept>
#include <algorithm>
using namespace std;

class AccidentReport {
private:
    string reportID;
    string vehicleNumber;
    string location;
    double damageCost;

public:
    // Constructor
    AccidentReport(string id = "", string vnum = "", string loc = "", double cost = 0.0) {
        if (cost <= 0) throw invalid_argument("Damage cost must be positive!");
        reportID = id;
        vehicleNumber = vnum;
        location = loc;
        damageCost = cost;
    }

    // Display report details
    void displayReport() const {
        cout << "Report ID: " << reportID << "\n"
             << "Vehicle Number: " << vehicleNumber << "\n"
             << "Location: " << location << "\n"
             << "Damage Cost: ₹ " << damageCost << "\n"
             << "---------------------------\n";
    }

    // Append to file
    void logAccident(const string &filename) const {
        ofstream fout(filename, ios::app);
        if (!fout) throw runtime_error("Error opening file for writing!");
        fout << reportID << "," << vehicleNumber << "," << location << "," << damageCost << "\n";
        fout.close();
    }

    // Getter for cost
    double getDamageCost() const { return damageCost; }
    string getReportID() const { return reportID; }

    // Operator overloading to compare severity
    bool operator>(const AccidentReport &other) const {
        return this->damageCost > other.damageCost;
    }
};

// Read reports from file into list
void loadReports(const string &filename, list<AccidentReport> &reports) {
    ifstream fin(filename);
    if (!fin) return; // No file yet, skip

    string id, vnum, loc;
    double cost;
    while (getline(fin, id, ',') && getline(fin, vnum, ',') && getline(fin, loc, ',') && (fin >> cost)) {
        fin.ignore(); // skip newline
        try {
            reports.emplace_back(id, vnum, loc, cost);
        } catch (...) {
            // skip invalid records
        }
    }
    fin.close();
}

// Menu functions
void addReport(list<AccidentReport> &reports, const string &filename) {
    string id, vnum, loc;
    double cost;
    cout << "Enter Report ID: ";
    cin >> id;
    cout << "Enter Vehicle Number: ";
    cin >> vnum;
    cout << "Enter Location: ";
    cin.ignore();
    getline(cin, loc);
    cout << "Enter Damage Cost: ";
    cin >> cost;

    try {
        AccidentReport report(id, vnum, loc, cost);
        reports.push_back(report);
        report.logAccident(filename);
        cout << "Report added successfully!\n";
    } catch (const invalid_argument &e) {
        cerr << "Error: " << e.what() << "\n";
    } catch (const runtime_error &e) {
        cerr << "File Error: " << e.what() << "\n";
    }
}

void viewReports(const list<AccidentReport> &reports) {
    if (reports.empty()) {
        cout << "No reports found.\n";
        return;
    }
    for (const auto &r : reports) {
        r.displayReport();
    }
}

void compareReports(const list<AccidentReport> &reports) {
    string id1, id2;
    cout << "Enter first Report ID: ";
    cin >> id1;
    cout << "Enter second Report ID: ";
    cin >> id2;

    auto it1 = find_if(reports.begin(), reports.end(), [&](const AccidentReport &r) { return r.getReportID() == id1; });
    auto it2 = find_if(reports.begin(), reports.end(), [&](const AccidentReport &r) { return r.getReportID() == id2; });

    if (it1 == reports.end() || it2 == reports.end()) {
        cout << "One or both reports not found.\n";
        return;
    }

    if (*it1 > *it2)
        cout << "Report " << id1 << " has higher severity.\n";
    else if (*it2 > *it1)
        cout << "Report " << id2 << " has higher severity.\n";
    else
        cout << "Both reports have the same severity.\n";
}

void sortReports(list<AccidentReport> &reports) {
    reports.sort([](const AccidentReport &a, const AccidentReport &b) {
        return a.getDamageCost() > b.getDamageCost();
    });
    cout << "Reports sorted by damage cost (High to Low).\n";
}

int main() {
    list<AccidentReport> reports;
    string filename = "accidents.txt";

    // Load from file on startup
    loadReports(filename, reports);

    int choice;
    do {
        cout << "\n=== Vehicle Accident Report System ===\n";
        cout << "1. Add New Accident Report\n";
        cout << "2. View All Reports\n";
        cout << "3. Compare Severity Between Two Reports\n";
        cout << "4. Sort Reports by Damage Cost\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addReport(reports, filename); break;
            case 2: viewReports(reports); break;
            case 3: compareReports(reports); break;
            case 4: sortReports(reports); break;
            case 5: cout << "Exiting... Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}