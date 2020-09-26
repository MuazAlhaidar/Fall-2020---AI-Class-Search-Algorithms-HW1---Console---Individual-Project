#include "DFS.hpp"
namespace DFS_namespace {

void DFS() {

    // Set the map
    setMapAndSets();

    // Set start point of maze
    frontierSet_stack.push(nodeGrid[1][3]);

    std::cout << "DFS:\n";

    depthFirstSearch(nodeGrid[1][3]);

    time_t now = time(0);
    struct tm tstruct;
    tstruct = *localtime(&now);

    std::cout << "Muaz Alhaidar(omunam) - Time: ";
    std::cout << (((tstruct.tm_hour - 12) < 0) ? tstruct.tm_hour : tstruct.tm_hour - 12);
    std::cout << ":" << tstruct.tm_min << ":" << tstruct.tm_sec << std::endl;

    // Print the map after final Success
    printMap();
}

bool depthFirstSearch(node currentNode) {

    //   1. Mark current node as visited
    // 1-1. Add node to the explored set (.number, node_IDS)
    exploredSet_hashMap.emplace(currentNode.number, currentNode);

    // 1-2. Pop node off of frontier set
    frontierSet_stack.pop();

    // 1-3. If node is available, mark it as visited
    //      if it is instead the final goal, then the search is done
    if (currentNode.status == FREE) {
        currentNode.status = NOTFREE;
        currentNode.isVisited = true;
    } else if (currentNode.status == GOAL) {
        currentNode.isVisited = true;
        return true;
    }

    //   2. Get neighbors of node
    // 2-1. Get all available childen of node
    // 2-1. Filter them to get only unexplored nodes
    //      by checking if they are in exploredSet
    std::vector<node> thisNodeNeighbors = checkExploredSet(getNodeNeighbors(currentNode.position));

    //   3. If the neighbors list is empty then
    //      this branch is a dead end
    if (thisNodeNeighbors.empty()) {
        return false;
    }

    //   4. Assign a number to all of the neighboring nodes
    //      so that they can be printed later on
    //      and also be added to the explored list
    for (short y = 0; y < thisNodeNeighbors.size(); y++) {
        thisNodeNeighbors[y].number = assignNodeNumber();
        thisNodeNeighbors[y].isVisited = true;
    }

    //   5 Add nodes to node grid so they can be displayed
    //     later on with the print map function
    addNodesToGrid(thisNodeNeighbors);

    //   6. Push the neighbors onto the frontier stack
    //      so we can explore them
    std::vector<node>::iterator it = thisNodeNeighbors.begin();
    for (; it != thisNodeNeighbors.end(); it++) {
        frontierSet_stack.push(*it);
    }

    //   7. If the frontier stack is emty then we have failed the search
    if (frontierSet_stack.empty()) {
        return false;
    }

    //   8. For the amount of neighbors of the current node
    //      run the search to explore all if the options
    //      until we fund the GOAL, and if that doesnt happen
    //      then we fail
    for (short z = 0; z < thisNodeNeighbors.size(); z++) {
        if (depthFirstSearch(frontierSet_stack.top())) {
            return true;
        }
    }

    return false;
}
} // namespace DFS_namespace