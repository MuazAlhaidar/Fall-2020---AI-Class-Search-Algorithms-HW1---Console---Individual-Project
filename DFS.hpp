#ifndef IDS
#define IDS
#include <ctime>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

const short MAP_WIDTH = 5;
const short MAP_HEIGHT = 4;

enum grid {
    FREE,
    NOTFREE,
    BLOCK,
    START,
    GOAL
};

struct node {
    std::string number = "  ";
    bool isVisited = false;
    std::pair<int, int> position;
    grid status = grid::FREE;
};

extern node nodeGrid[][MAP_WIDTH];

// Current number to increment and assign to the
// number of a node_IDS
extern int exploredNumber;

extern std::stack<node> frontierSet_stack;
extern std::unordered_map<std::string, node> exploredSet_hashMap;

void setMapAndSets();
void DFS();
void printMap();
void addNodesToGrid(std::vector<node> nodeList);

bool depthFirstSearch(node currentNode);

std::string assignNodeNumber();

grid getNodeStatus(int nodeRow, int nodeColumn);

std::vector<node> getNodeNeighbors(const std::pair<int, int> nodePosition);
std::vector<node> checkExploredSet(const std::vector<node> neighbors);

#endif