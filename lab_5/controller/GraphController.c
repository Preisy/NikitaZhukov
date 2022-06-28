#include <string.h>
#include "GraphController.h"


int validate(char sym) {
    if ('0' <= sym && sym <= '9')
        return 1;
    else
        return 0;
}

int convertToInt(char* begin, char* end) {
    int res = 0;
    for (; begin != end; ++begin) {
        if (validate(*begin))
            res = res * 10 + (*begin - '0');
        else
            return -1;
    }

    return res;
}

void C_addv(Graph* graph, char* args, enum ExecutionCode* responseCode) {
    *responseCode = Ok;
    char *istr;

    istr = strtok (args, " ");

    int ns[2] = {0};

    int i = 0;
    while (istr != NULL) {
        if (i >= 2) {
            *responseCode = CommandError;
            return;
        }
        ns[i] = convertToInt(istr, istr + strlen(istr));
        if (ns[i] == -1) {
            *responseCode = ExecutionError;
            return;
        }
        ++i;

        istr = strtok (NULL, " ");
    }
    if (i < 2) {
        *responseCode = CommandError;
        return;
    }

    if (addVertexGraph(graph, ns[0], ns[1])) {
        *responseCode = ExecutionError;
    }
}

void C_adde(Graph* graph, char* args, enum ExecutionCode* responseCode) {
    *responseCode = Ok;
    char *istr;

    istr = strtok (args, " ");

    int ns[4] = {0};

    int i = 0;
    while (istr != NULL) {
        if (i >= 4) {
            *responseCode = CommandError;
            return;
        }
        ns[i] = convertToInt(istr, istr + strlen(istr));
        if (ns[i] == -1) {
            *responseCode = ExecutionError;
            return;
        }
        ++i;

        istr = strtok (NULL, " ");
    }
    if (i < 4) {
        *responseCode = CommandError;
        return;
    }

    if (addEdgeGraph(graph, ns[0], ns[1], ns[2], ns[3])) {
        *responseCode = ExecutionError;
    }
}

void C_delv(Graph* graph, char* args, enum ExecutionCode* responseCode) {
    *responseCode = Ok;
    char *istr;

    istr = strtok (args, " ");

    int ns[2] = {0};

    int i = 0;
    while (istr != NULL) {
        if (i >= 2) {
            *responseCode = CommandError;
            return;
        }
        ns[i] = convertToInt(istr, istr + strlen(istr));
        if (ns[i] == -1) {
            *responseCode = ExecutionError;
            return;
        }
        ++i;

        istr = strtok (NULL, " ");
    }
    if (i < 2) {
        *responseCode = CommandError;
        return;
    }

    if (deleteVertexGraph(graph, ns[0], ns[1])) {
        *responseCode = NotFound;
    }
}

void C_dele(Graph* graph, char* args, enum ExecutionCode* responseCode) {
    *responseCode = Ok;
    char *istr;

    istr = strtok (args, " ");

    int ns[4] = {0};

    int i = 0;
    while (istr != NULL) {
        if (i >= 4) {
            *responseCode = CommandError;
            return;
        }
        ns[i] = convertToInt(istr, istr + strlen(istr));
        if (ns[i] == -1) {
            *responseCode = ExecutionError;
            return;
        }
        ++i;

        istr = strtok (NULL, " ");
    }
    if (i < 4) {
        *responseCode = CommandError;
        return;
    }

    if (deleteEdgeGraph(graph, ns[0], ns[1], ns[2], ns[3])) {
        *responseCode = NotFound;
    }
}

void C_find(Graph* graph, char* args, enum ExecutionCode* responseCode) {
    *responseCode = Ok;
    char *istr;

    istr = strtok (args, " ");

    int ns[4] = {0};

    int i = 0;
    while (istr != NULL) {
        if (i >= 4) {
            *responseCode = CommandError;
            return;
        }
        ns[i] = convertToInt(istr, istr + strlen(istr));
        if (ns[i] == -1) {
            *responseCode = ExecutionError;
            return;
        }
        ++i;

        istr = strtok (NULL, " ");
    }
    if (i < 4) {
        *responseCode = CommandError;
        return;
    }

    if (findGraph(graph, ns[0], ns[1], ns[2], ns[3])) {
        *responseCode = NotFound;
    }
}

void C_sfind(Graph* graph, char* args, enum ExecutionCode* responseCode) {
    *responseCode = Ok;
    char *istr;

    istr = strtok (args, " ");

    int ns[4] = {0};

    int i = 0;
    while (istr != NULL) {
        if (i >= 4) {
            *responseCode = CommandError;
            return;
        }
        ns[i] = convertToInt(istr, istr + strlen(istr));
        if (ns[i] == -1) {
            *responseCode = ExecutionError;
            return;
        }
        ++i;

        istr = strtok (NULL, " ");
    }
    if (i < 4) {
        *responseCode = CommandError;
        return;
    }

    if (sFindGraph(graph, ns[0], ns[1], ns[2], ns[3])) {
        *responseCode = NotFound;
    }
}

void C_print(Graph* graph, char* args, enum ExecutionCode* responseCode) {
    *responseCode = Ok;
    if (strcmp(args, "") != 0) {
        *responseCode = CommandError;
    }

    printGraph(graph);
}
