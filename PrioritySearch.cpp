#include "PrioritySearch.hpp"
namespace PrioritySearch_namespace {

template <class T>
void ProritySearch() {

    std::priority_queue<node, std::vector<node>, T> frontierSet;

    setMapAndSets();

    frontierSet.push(nodeGrid[1][3]);

    std::cout << "DFS:\n";

    time_t now = time(0);
    struct tm tstruct;
    tstruct = *localtime(&now);

    std::cout << "Muaz Alhaidar(omunam) - Time: ";
    std::cout << (((tstruct.tm_hour - 12) < 0) ? tstruct.tm_hour : tstruct.tm_hour - 12);
    std::cout << ":" << tstruct.tm_min << ":" << tstruct.tm_sec << std::endl;

    // Print the map after final Success
    printMap();
}
} 