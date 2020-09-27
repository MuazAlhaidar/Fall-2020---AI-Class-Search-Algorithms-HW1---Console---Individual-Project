#ifndef _NODE_
#define _NODE_
#include <ctime>
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
const short SIDE_COST = 2;
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
    int pathCost = 0;
    int predPathCost = 0;
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
void addNodesToGrid_vector(std::vector<node> nodeList);
void addNodesToGrid(node currentNode);

int manhattanDistance(std::pair<int, int> start, std::pair<int, int> goal);

bool isInExploredSet(int x, int y);

std::string assignNodeNumber();

grid getNodeStatus(int nodeRow, int nodeColumn);

std::vector<node> getNodeNeighbors(const std::pair<int, int> nodePos);

// Comprison Functions
struct UCS_compare {
    bool operator()(const node &firstNode, const node &secNode) {
        if (firstNode.pathCost == secNode.pathCost) {
            return firstNode.number > secNode.number;
        }
        return firstNode.pathCost > secNode.pathCost;
    }
};

struct GBFS_compare {
    bool operator()(const node &firstNode, const node &secNode) {
        if (firstNode.predPathCost == secNode.predPathCost) {
            return firstNode.number > secNode.number;
        }
        return firstNode.predPathCost > secNode.predPathCost;
    }
};

struct A_compare {
    bool operator()(const node &firstNode, const node &secNode) {
        int firstCost = firstNode.predPathCost + firstNode.pathCost;
        int secCost = secNode.predPathCost + secNode.pathCost;
        if (firstCost == secCost) {
            return firstNode.number > secNode.number;
        }
        return firstCost > secCost;
    }
};

template <class T>
void temp();

} // namespace NodeAndMap_namespace

#endif