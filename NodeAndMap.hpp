#ifndef _NodeAndMap_
#define _NodeAndMap_
#include <ctime>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace NodeAndMap_namespace {

const short MAP_WIDTH = 5;
const short MAP_HEIGHT = 4;

const short UP_COST = 3;
const short RIGHT_COST = 2;
const short LEFT_COST = 2;
const short DOWN_COST = 1;

enum grid {
    FREE,
    NOTFREE,
    BLOCK,
    START,
    GOAL
};

struct node {
    std::string number = "  ";
    std::pair<int, int> position;
    bool isVisited = false;
    int pathCost;
    int predictedPathCost;
    grid status = grid::FREE;
};

extern node nodeGrid[][MAP_WIDTH];

// Current number to increment and assign to the
// number of a node_IDS
extern int exploredNumber;

extern std::stack<node> frontierSet_stack;
extern std::queue<node> frontierSet_queue;
extern std::unordered_map<std::string, node> exploredSet_hashMap;

void setMapAndSets();
void printMap();
void addNodesToGrid(std::vector<node> nodeList);

std::string assignNodeNumber();

grid getNodeStatus(int nodeRow, int nodeColumn);

std::vector<node> getNodeNeighbors(const std::pair<int, int> nodePos);
std::vector<node> checkExploredSet(const std::vector<node> neighbors);
std::vector<node> checkExploredSet_UCS(const std::vector<node> neighbors);
} // namespace NodeAndMap_namespace

#endif