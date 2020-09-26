#include "NodeAndMap.hpp"
namespace NodeAndMap_namespace {

node nodeGrid[MAP_HEIGHT][MAP_WIDTH];

// Current number to increment and assign to the
// number of a node_IDS
int exploredNumber;

std::stack<node> frontierSet_stack;
std::queue<node> frontierSet_queue;
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

    while (!frontierSet_stack.empty())
        frontierSet_stack.pop();

    while (!frontierSet_queue.empty())
        frontierSet_queue.pop();
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
} // namespace NodeAndMap_namespace