#include "BFS.hpp"
#include "DFS.hpp"
#include "NodeAndMap.hpp"
#include "PrioritySearch.hpp"
#include <iostream>
using namespace std;

int main() {

    DFS_namespace::DFS();
    BFS_namespace::BFS();

    PrioritySearch_namespace::PrioritySearch<NodeAndMap_namespace::UCS_compare>();

    return 0;
}
