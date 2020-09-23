#include "Astar.hpp"
#include "IterativeDeepeningSearch_IDS.hpp"
#include <iostream>
#include <vector>
using namespace std;

void aastar() {

    point _start(3, 0);
    point end(2, 2);

    node start(_start);
    // point end(4,4);
    vector<vect> test = astar(&start, end);
    time_t now = time(0);
    struct tm tstruct;
    tstruct = *localtime(&now);

    std::cout << "Muaz Alhaidar(omunam) and Zakariya Ahmed(zakahmed) - Time: " << tstruct.tm_hour - 12 << ":" << tstruct.tm_min << ":" << tstruct.tm_sec << std::endl;
    cout << "A* Search" << endl;
    string line = "--------------";
    cout << line << endl;
    for (auto row : test) {
        for (auto x : row) {
            if (x.label == -1) {
                cout << "##" << ' ';
            } else {
                if (x.label < 10 && x.label >= 0) {
                    cout << '0';
                }
                cout << x.label << ' ';
            }
        }
        cout << endl;
    }
    cout << line << endl;
}

int main() {

    iterativeDeepeningDFS();
    aastar();
}
