#include <iostream>

#include <iomanip>
#include <string>
#include <fstream>
#include <vector>

using namespace std;


bool isLeapYear(int year);
int daysInMonth(int month, int year);
int dayOfWeek(int month, int day, int year);

string weekdayName(int dow);
int monthFromName(const string& name);
void printCalendar(int month, int year);
void printCalendarToFile(int month, int year, const string& filename);




bool isLeapYear(int year) {
    if (year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    if (year % 4 == 0)   return true;
    return false;

}

int daysInMonth(int month, int year) {

    //switch statement
    switch (month) {
    case 1: case 3: case 5: case 7:
    case 8: case 10: case 12:
        return 31;
    case 4: case 6: case 9: case 11:
        return 30;
    case 2:
        return isLeapYear(year) ? 29 : 28;
    }
    return 0;
}

int dayOfWeek(int month, int day, int year) {
    int q = day;
    int m = month;
    int Y = year;

    if (m == 1) { m = 13; Y--; }
    else if (m == 2) { m = 14; Y--; }

    int K = Y % 100;
    int J = Y / 100;

    int h = (q + (13 * (m + 1)) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
    return h; // 0 = Sat, 1 = Sun, ... 6 = Fri
}

string weekdayName(int dow) {
    string names[] = {
        "Saturday","Sunday","Monday","Tuesday",
        "Wednesday","Thursday","Friday"
    };
    return names[dow];
}

int monthFromName(const string& name) {
    string months[] = { "January","February","March","April","May","June",
                       "July","August","September","October","November","December" };
    for (int i = 0; i < 12; i++)
        if (name == months[i])
            return i + 1;
    return 0;
}


void printCalendar(int month, int year) {
    int dow = dayOfWeek(month, 1, year);
    int startCol = (dow + 6) % 7;
    int dim = daysInMonth(month, year);


    vector<vector<int>> grid(6, vector<int>(7, 0));

    int r = 0, c = startCol;
    for (int d = 1; d <= dim; ++d) {
        grid[r][c] = d;
        ++c;
        if (c == 7) { c = 0; ++r; }
    }


    cout << "Su Mo Tu We Th Fr Sa\n";


    for (int i = 0; i < 6; ++i) {
        bool any = false;
        for (int j = 0; j < 7; ++j) {
            if (grid[i][j] != 0) { any = true; break; }
        }
        if (!any) break;

        for (int j = 0; j < 7; ++j) {
            if (grid[i][j] == 0) cout << "   ";
            else cout << setw(2) << grid[i][j] << " ";
        }
        cout << "\n";
    }
}

void printCalendarToFile(int month, int year, const string& filename) {


    int dow = dayOfWeek(month, 1, year);
    int startCol = (dow + 6) % 7;
    int dim = daysInMonth(month, year);

    vector<vector<int>> grid(6, vector<int>(7, 0));
    int r = 0, c = startCol;
    for (int d = 1; d <= dim; ++d) {
        grid[r][c] = d;
        ++c;
        if (c == 7) { c = 0; ++r; }
    }

    ofstream fout(filename);
    fout << "Su Mo Tu We Th Fr Sa\n";

    for (int i = 0; i < 6; ++i) {
        bool any = false;
        for (int j = 0; j < 7; ++j) {
            if (grid[i][j] != 0) { any = true; break; }
        }
        if (!any) break;

        for (int j = 0; j < 7; ++j) {
            if (grid[i][j] == 0) fout << "   ";
            else fout << setw(2) << grid[i][j] << " ";
        }
        fout << "\n";
    }

    fout.close();
}


int main() {
    string monthName;
    int year;

    cout << "Enter a month and year or Q to quit: ";


    while (cin >> monthName && monthName != "Q") {
        cin >> year;

        int month = monthFromName(monthName);

        cout << monthName << " " << year << "\n";
        printCalendar(month, year);

        string outFile = monthName.substr(0, 3) + to_string(year) + ".txt";
        printCalendarToFile(month, year, outFile);

        cout << "Output file: " << outFile << "\n";
        cout << "Enter a month and year or Q to quit: ";
    }



    return 0;
}