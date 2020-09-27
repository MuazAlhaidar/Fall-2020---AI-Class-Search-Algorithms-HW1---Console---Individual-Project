#include "NodeAndMap.hpp"
#include <iostream>
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
            nodeGrid[x][y].pathCost = 0;
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

void addNodesToGrid_vector(std::vector<node> nodeList) {
    for (short w = 0; w < nodeList.size(); w++)
        nodeGrid[nodeList[w].position.first][nodeList[w].position.second] = nodeList[w];
}

void addNodesToGrid(node currentNode) {
    nodeGrid[currentNode.position.first][currentNode.position.second] = currentNode;
}

int manhattanDistance(std::pair<int, int> start, std::pair<int, int> goal) {
    std::pair<int, int> distance = {goal.first - start.first, goal.second - start.second};

    // If the y distance is positive then
    // the goal is above the start
    if (distance.first > 0) {
        // If values are negative
        // Make them posiitive to find the positive distance
        distance.second = abs(distance.second);
        return distance.first * UP_COST + distance.second * SIDE_COST;
    } else {
        distance.first = abs(distance.first);
        distance.second = abs(distance.second);
        return distance.first * DOWN_COST + distance.second * SIDE_COST;
    }
}

std::string assignNodeNumber() {

    exploredNumber++;
    if (exploredNumber < 10) {

        return "0" + std::to_string(exploredNumber);
    }
    return std::to_string(exploredNumber);
}

std::vector<node> getNodeNeighbors(const std::pair<int, int> nodePos) {

    std::vector<node> neighbors{};
    grid nodeStatus;
    std::pair<int, int> goal(2, 2);

    auto nodePushNeighbor = [](int x,
                               int y,
                               int parentCost,
                               short DIR,
                               std::vector<node> &neighbors,
                               std::pair<int, int> goal) {
        grid nodeStatus = getNodeStatus(x, y);
        if ((nodeStatus == FREE || nodeStatus == GOAL) &&
            !nodeGrid[x][y].isVisited) {
            if (!isInExploredSet(x, y)) {
                nodeGrid[x][y].pathCost = DIR + parentCost;
                nodeGrid[x][y].predPathCost = manhattanDistance(std::pair<int, int>(x, y), goal);
                neighbors.push_back(nodeGrid[x][y]);
            }
        }
    };

    int pastPath = nodeGrid[nodePos.first][nodePos.second].pathCost;

    nodePushNeighbor(nodePos.first, nodePos.second - 1, pastPath, SIDE_COST, neighbors, goal);
    nodePushNeighbor(nodePos.first - 1, nodePos.second, pastPath, UP_COST, neighbors, goal);
    nodePushNeighbor(nodePos.first, nodePos.second + 1, pastPath, SIDE_COST, neighbors, goal);
    nodePushNeighbor(nodePos.first + 1, nodePos.second, pastPath, DOWN_COST, neighbors, goal);

    return neighbors;
}

bool isInExploredSet(int x, int y) {
    std::unordered_map<std::string, node>::const_iterator got = exploredSet_hashMap.find(nodeGrid[x][y].number);

    if (got == exploredSet_hashMap.end()) {
        return false;
    }

    return true;
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

template <class T>
void temp() {
    std::priority_queue<node, std::vector<node>, T> frontierSet;
}

/*
std::vector<node> checkExploredSet(const std::vector<node> neighbors) {
    std::vector<node> filteredNeighbors{};

    for (node temp : neighbors) {
        std::unordered_map<std::string, node>::const_iterator got = exploredSet_hashMap.find(temp.number);

        if (got == exploredSet_hashMap.end()) {
            filteredNeighbors.push_back(temp);
        } else if (exploredSet_hashMap[temp.number].pathCost > temp.pathCost) {
            exploredSet_hashMap[temp.number].pathCost = temp.pathCost;
            filteredNeighbors.push_back(temp);
        }
    }

    return filteredNeighbors;
}
*/

} // namespace NodeAndMap_namespace