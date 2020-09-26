#include "PrioritySearch.hpp"
namespace PrioritySearch_namespace {

template <class T>
void PrioritySearch() {

    std::priority_queue<node, std::vector<node>, T> frontierSet;

    setMapAndSets();

    frontierSet.push(nodeGrid[1][3]);

    while (!frontierSet.empty()) {
        node currentNode = frontierSet.top();
        frontierSet.pop();

        if (currentNode.status == GOAL) {
            addNodesToGrid(currentNode);
            break;
        }

        currentNode.isVisited = true;
        exploredSet_hashMap.emplace(currentNode.number, currentNode);

        std::vector<node> thisNodeNeighbors = getNodeNeighbors(currentNode.position);

        std::vector<node>::iterator it = thisNodeNeighbors.begin();
        for (; it != thisNodeNeighbors.end(); it++) {
            frontierSet.push(*it);
        }
    }

    time_t now = time(0);
    struct tm tstruct;
    tstruct = *localtime(&now);

    std::cout << "Muaz Alhaidar(omunam) - Time: ";
    std::cout << (((tstruct.tm_hour - 12) < 0) ? tstruct.tm_hour : tstruct.tm_hour - 12);
    std::cout << ":" << tstruct.tm_min << ":" << tstruct.tm_sec << std::endl;

    // Print the map after final Success
    printMap();
}
} // namespace PrioritySearch_namespace