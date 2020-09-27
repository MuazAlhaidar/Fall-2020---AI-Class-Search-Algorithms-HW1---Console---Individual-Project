#ifndef _PRIORITY_
#define _PRIORITY_

#include "NodeAndMap.hpp"
#include <iostream>
using namespace NodeAndMap_namespace;

namespace PrioritySearch_namespace {

template <class T>
void PrioritySearch() {

    std::priority_queue<node, std::vector<node>, T> frontierSet;

    setMapAndSets();

    frontierSet.push(nodeGrid[1][3]);

    while (!frontierSet.empty()) {

        node currentNode = frontierSet.top();

        exploredSet_hashMap.emplace(currentNode.number, currentNode);

        frontierSet.pop();

        if (currentNode.status == FREE) {
            currentNode.status = NOTFREE;
            currentNode.isVisited = true;
        } else if (currentNode.status == GOAL) {
            currentNode.isVisited = true;
            break;
        }

        std::vector<node> thisNodeNeighbors = getNodeNeighbors(currentNode.position);

        for (short y = 0; y < thisNodeNeighbors.size(); y++) {
            thisNodeNeighbors[y].number = assignNodeNumber();
            thisNodeNeighbors[y].isVisited = true;
            addNodesToGrid(thisNodeNeighbors[y]);
        }

        for (auto x : thisNodeNeighbors) {
            frontierSet.push(x);
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

#endif