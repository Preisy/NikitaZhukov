#include <stdio.h>
#include "Graph.h"

int main() {
    Graph graph = getGraph();

    addEdgeGraph(&graph, 1, 2, 3, 4);
    addEdgeGraph(&graph, 3, 4, 8, 9);

//    addVertexGraph(&graph, 8, 9);
//    addEdgeGraph(&graph, 1, 2, 3, 4);
//    addEdgeGraph(&graph, 1, 2, 5, 6);
//    addVertexGraph(&graph, 1, 2);
//    addVertexGraph(&graph, 10, 11);
//    addEdgeGraph(&graph, 5, 6, 1, 2);
//    addEdgeGraph(&graph, 5, 6, 3, 4);
//    addEdgeGraph(&graph, 43, 12, 3, 4);
//    addVertexGraph(&graph, 20, 20);
//    addEdgeGraph(&graph, 43, 12, 5, 6);
//    addEdgeGraph(&graph, 3, 4, 43, 12);

//    deleteVertexGraph(&graph, 354, 234);
//    deleteEdgeGraph(&graph, 1, 2, 5, 6);

    findGraph(&graph, 1, 2, 8, 9);


    printGraph(&graph);

    graphDestructor(&graph);
    return 0;
}
