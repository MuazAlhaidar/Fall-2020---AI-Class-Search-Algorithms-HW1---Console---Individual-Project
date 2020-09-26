#include "DFS.hpp"

node nodeGrid[MAP_HEIGHT][MAP_WIDTH];

// Current number to increment and assign to the
// number of a node_IDS
int exploredNumber;
int currentDepth;

std::stack<node> frontierSet_stack;
std::unordered_map<std::string, node> exploredSet_hashMap;

void setMapAndSets() {

    // Set Entire Board
    for (short x = 0; x < MAP_HEIGHT; x++) {
        for (short y = 0; y < MAP_WIDTH; y++) {
            nodeGrid[x][y].number = "  ";
            nodeGrid[x][y].isVisited = false;
            nodeGrid[x][y].status = grid::FREE;
            nodeGrid[x][y].position = std::make_pair(x, y);
        }
    }

    // Set Block Location
    nodeGrid[2][3].number = "##";
    nodeGrid[2][3].isVisited = false;
    nodeGrid[2][3].status = grid::BLOCK;

    nodeGrid[1][1].number = "##";
    nodeGrid[1][1].isVisited = false;
    nodeGrid[1][1].status = grid::BLOCK;

    nodeGrid[1][2].number = "##";
    nodeGrid[1][2].isVisited = false;
    nodeGrid[1][2].status = grid::BLOCK;

    // Set Start Location
    nodeGrid[1][3].number = "00";
    nodeGrid[1][3].isVisited = true;
    nodeGrid[1][3].status = grid::START;

    // Set End Location
    nodeGrid[2][2].number = "  ";
    nodeGrid[2][2].isVisited = false;
    nodeGrid[2][2].status = grid::GOAL;

    exploredNumber = 0;
    exploredSet_hashMap.clear();

    while (!frontierSet_stack.empty()) {
        frontierSet_stack.pop();
    }
}

void DFS() {

    // Set the map
    setMapAndSets();

    // Set start point of maze
    frontierSet_stack.push(nodeGrid[1][3]);

    std::cout << "IDS:\n";

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

void printMap() {
    std::cout << "--------------\n";
    for (short x = 0; x < MAP_HEIGHT; x++) {
        for (short y = 0; y < MAP_WIDTH; y++) {
            std::cout << nodeGrid[x][y].number << " ";
        }
        std::cout << "\n";
    }
    std::cout << "--------------\n";
}

void addNodesToGrid(std::vector<node> nodeList) {
    for (short w = 0; w < nodeList.size(); w++)
        nodeGrid[nodeList[w].position.first][nodeList[w].position.second] = nodeList[w];
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

std::string assignNodeNumber() {

    exploredNumber++;
    if (exploredNumber < 10) {

        return "0" + std::to_string(exploredNumber);
    }
    return std::to_string(exploredNumber);
}

std::vector<node> getNodeNeighbors(const std::pair<int, int> nodePosition) {

    std::vector<node> neighbors{};
    grid nodeStatus;

    // Left
    nodeStatus = getNodeStatus(nodePosition.first, nodePosition.second - 1);
    if ((nodeStatus == FREE || nodeStatus == GOAL) &&
        !nodeGrid[nodePosition.first][nodePosition.second - 1].isVisited) {
        neighbors.push_back(
            nodeGrid[nodePosition.first][nodePosition.second - 1]);
    }

    // Up
    nodeStatus = getNodeStatus(nodePosition.first - 1, nodePosition.second);
    if ((nodeStatus == FREE || nodeStatus == GOAL) &&
        !nodeGrid[nodePosition.first - 1][nodePosition.second].isVisited) {
        neighbors.push_back(
            nodeGrid[nodePosition.first - 1][nodePosition.second]);
    }

    // Right
    nodeStatus = getNodeStatus(nodePosition.first, nodePosition.second + 1);
    if ((nodeStatus == FREE || nodeStatus == GOAL) &&
        !nodeGrid[nodePosition.first][nodePosition.second + 1].isVisited) {
        neighbors.push_back(
            nodeGrid[nodePosition.first][nodePosition.second + 1]);
    }

    // Down
    nodeStatus = getNodeStatus(nodePosition.first + 1, nodePosition.second);
    if ((nodeStatus == FREE || nodeStatus == GOAL) &&
        !nodeGrid[nodePosition.first + 1][nodePosition.second].isVisited) {
        neighbors.push_back(
            nodeGrid[nodePosition.first + 1][nodePosition.second]);
    }

    return neighbors;
}

std::vector<node> checkExploredSet(const std::vector<node> neighbors) {
    std::vector<node> filteredNeighbors{};

    for (node temp : neighbors) {
        std::unordered_map<std::string, node>::const_iterator got = exploredSet_hashMap.find(temp.number);

        if (got == exploredSet_hashMap.end())
            filteredNeighbors.push_back(temp);
    }

    return filteredNeighbors;
}

grid getNodeStatus(int nodeRow, int nodeColumn) {
    if (nodeColumn < 0 || nodeColumn >= MAP_WIDTH) {
        return BLOCK;
    }

    if (nodeRow < 0 || nodeRow >= MAP_HEIGHT) {
        return BLOCK;
    }

    return nodeGrid[nodeRow][nodeColumn].status;
}
