#include "GBFS.hpp"
#include <iostream>
namespace GBFS_namespace {

void GBFS() {

    // Set the map
    setMapAndSets();

    // Set start point of maze
    frontierSet_queue.push(nodeGrid[1][3]);

    std::cout << "GBFS:\n";

    greadyBreadthFirstSearch(nodeGrid[1][3]);

    time_t now = time(0);
    struct tm tstruct;
    tstruct = *localtime(&now);

    std::cout << "Muaz Alhaidar(omunam) - Time: ";
    std::cout << (((tstruct.tm_hour - 12) < 0) ? tstruct.tm_hour : tstruct.tm_hour - 12);
    std::cout << ":" << tstruct.tm_min << ":" << tstruct.tm_sec << std::endl;

    // Print the map after final Success
    printMap();
}

bool greadyBreadthFirstSearch(node currentNode) {
    return false;
}
} // namespace GBFS_namespace