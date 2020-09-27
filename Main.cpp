#include "BFS.hpp"
#include "DFS.hpp"
#include "NodeAndMap.hpp"
#include "PrioritySearch.hpp"
using namespace std;

int main() {

    DFS_namespace::DFS();
    BFS_namespace::BFS();

    std::cout << "UCS\n";
    PrioritySearch_namespace::PrioritySearch<UCS_compare>();

    std::cout << "GBFS\n";
    PrioritySearch_namespace::PrioritySearch<GBFS_compare>();

    std::cout << "A*\n";
    PrioritySearch_namespace::PrioritySearch<A_compare>();

    return 0;
}
