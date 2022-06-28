#include <stdio.h>
#include "Graph.h"

#include "GraphController.h"
#include "Dialog.h"



int main() {
    Graph graph = getGraph();

    Response response = {"", ""};
    printf("Type your command or type help\n");
    while (strcmp(response.command, "exit") != 0) {
        ask(&response);

        enum ExecutionCode executionCode;
        if (strcmp(response.command, "exit") == 0) {
            break;
        } else if (strcmp(response.command, "help") == 0) {
            help();
            executionCode = Ok;
        } else if (strcmp(response.command, "addv") == 0) {
            C_addv(&graph, response.args, &executionCode);
        } else if (strcmp(response.command, "adde") == 0) {
            C_adde(&graph, response.args, &executionCode);
        } else if (strcmp(response.command, "delv") == 0) {
            C_delv(&graph, response.args, &executionCode);
        } else if (strcmp(response.command, "dele") == 0) {
            C_dele(&graph, response.args, &executionCode);
        } else if (strcmp(response.command, "find") == 0) {
            C_find(&graph, response.args, &executionCode);
        } else if (strcmp(response.command, "sfind") == 0) {
            C_sfind(&graph, response.args, &executionCode);
        } else if (strcmp(response.command, "print") == 0) {
            C_print(&graph, response.args, &executionCode);
        } else {
            executionCode = CommandError;
        }


        if (executionCode == CommandError) {
            printf("Incorrect command <%s>. Try again\n", response.command);
            continue;
        } else if (executionCode == ExecutionError) {
            printf("Execution error <%s>\n", response.command);
            continue;
        } else if (executionCode == NotFound) {
            printf("Not Found\n");
            continue;
        }
    }

    graphDestructor(&graph);

    return 0;
}




//int main() {
//    Graph graph = getGraph();
//
//    addEdgeGraph(&graph, 1, 2, 3, 4);
//    addEdgeGraph(&graph, 3, 4, 8, 9);
//    addEdgeGraph(&graph, 3, 4, 4, 5);
//    addEdgeGraph(&graph, 1, 2, 8, 9);
//
////    addVertexGraph(&graph, 8, 9);
////    addEdgeGraph(&graph, 1, 2, 3, 4);
////    addEdgeGraph(&graph, 1, 2, 5, 6);
////    addVertexGraph(&graph, 1, 2);
////    addVertexGraph(&graph, 10, 11);
////    addEdgeGraph(&graph, 5, 6, 1, 2);
////    addEdgeGraph(&graph, 5, 6, 3, 4);
////    addEdgeGraph(&graph, 43, 12, 3, 4);
////    addVertexGraph(&graph, 20, 20);
////    addEdgeGraph(&graph, 43, 12, 5, 6);
////    addEdgeGraph(&graph, 3, 4, 43, 12);
//
////    deleteVertexGraph(&graph, 354, 234);
////    deleteEdgeGraph(&graph, 1, 2, 5, 6);
//
//    printGraph(&graph);
//
//    printf("\n");
//
//    sFindGraph(&graph, 1, 2, 8, 9);
//    findGraph(&graph, 1, 2, 8, 9);
//
//
//    graphDestructor(&graph);
//    return 0;
//}
