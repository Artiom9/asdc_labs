#include <iostream>
#include <vector>

struct GraphNode {
    int value;
    std::vector<GraphNode*> neighbors;

    GraphNode(int val) : value(val) {}
};

int sumNeighbors(const GraphNode* node) {
    int sum = 0;
    for (const auto& neighbor : node->neighbors) {
        sum += neighbor->value;
    }
    return sum;
}

void createDirectedGraph() {
    //It's better to use unique_ptr
    GraphNode* nodeA = new GraphNode(1);
    GraphNode* nodeB = new GraphNode(2);
    GraphNode* nodeC = new GraphNode(3);
    GraphNode* nodeE = new GraphNode(4);

    //Create graph
    nodeA->neighbors.push_back(nodeB);
    nodeA->neighbors.push_back(nodeC);
    nodeA->neighbors.push_back(nodeE);
    nodeB->neighbors.push_back(nodeC);
    nodeC->neighbors.push_back(nodeE);
    nodeE->neighbors.push_back(nodeA);

    //Calculate sum of neighbors
    std::cout << "Sum of neighbors for node A: " << sumNeighbors(nodeA) << std::endl;
    std::cout << "Sum of neighbors for node B: " << sumNeighbors(nodeB) << std::endl;
    std::cout << "Sum of neighbors for node C: " << sumNeighbors(nodeC) << std::endl;
    std::cout << "Sum of neighbors for node C: " << sumNeighbors(nodeE) << std::endl;

    //Freeing up memory
    delete nodeA;
    delete nodeB;
    delete nodeC;
    delete nodeE;
}

int main() {
    createDirectedGraph();
    return 0;
}
