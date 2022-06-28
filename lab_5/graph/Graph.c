#include "Graph.h"
#include <math.h>
#include <stdio.h>
#include "PQueue.h"
#include "limits.h"
#include <float.h>

Graph getGraph() {
    Graph res;
    res.nodeHead = NULL;
    return res;
}

Node* getNode() {
    Node* res = calloc(1, sizeof (Node));
    return res;
}

Dot* getDot(int x, int y) {
    Dot* res = calloc(1, sizeof (Dot));
    res->x = x;
    res->y = y;
    res->r = -1;
    return res;
}

void _dotDestructor(Dot* this) {
    free(this);
}

void _nodeDestructor(Node* this) {
    if (this == NULL) return;
    _dotDestructor(this->dot);
    free(this);
}

double calculateR(Dot* dot1, Dot* dot2) {
    return sqrt( pow(dot1->x - dot2->x, 2) + pow (dot1->y - dot2->y, 2) );
}

int addVertexGraph(Graph* this, int x, int y) {
    if (this == NULL) return 1;

    if (this->nodeHead == NULL) {
        this->nodeHead = getNode();
        this->nodeHead->dot = getDot(x, y);
        return 0;
    }
    Node* prevNode;
    Node* it = this->nodeHead;
    while (it != NULL) {
        if (it->dot->x == x && it->dot->y == y) {
            return 0;
        }
        prevNode = it;
        it = it->next;
    }
    prevNode->next = getNode();
    it = prevNode->next;
    it->dot = getDot(x, y);

    return 0;
}

int addEdgeGraph(Graph* this, int x1, int y1, int x2, int y2) {
    if (this == NULL) return 1;

    if (this->nodeHead == NULL) {
        this->nodeHead = getNode();
        this->nodeHead->dot = getDot(x1, y1);
        this->nodeHead->dotHead = getDot(x2, y2);
        this->nodeHead->dotHead->r =
                calculateR(this->nodeHead->dot,
                           this->nodeHead->dotHead);
        return 0;
    }

    Node* prevNode;
    Node* it = this->nodeHead;
    while (it != NULL) {
        if (it->dot->x == x1 && it->dot->y == y1) {
            break;
        }
        prevNode = it;
        it = it->next;
    }
    if (it == NULL) {
        prevNode->next = getNode();
        it = prevNode->next;
        it->dot = getDot(x1, y1);
    }

    Dot* prevDot = NULL;
    Dot* jt = it->dotHead;
    while(jt != NULL) {
        if (jt->x == x2 && jt->y == y2) {
            return 0;
        }
        prevDot = jt;
        jt = jt->next;
    }
    if (prevDot == NULL) {
        it->dotHead = getDot(x2, y2);
        it->dotHead->r = calculateR(it->dot, it->dotHead);
    } else {
        prevDot->next = getDot(x2, y2);
        prevDot->next->r = calculateR(it->dot, prevDot->next);
    }
    return 0;
}

int deleteVertexGraph(Graph* this, int x, int y) {
    if (this == NULL) return 1;

    int flag = 1;

    Node* prevNode = NULL;
    for (Node* it = this->nodeHead; it != NULL; it = it->next) {
        if (it->dot->x == x && it->dot->y == y) {
            flag = 0;
            if (prevNode == NULL) {
                this->nodeHead = it->next;
            } else {
                prevNode->next = it->next;
            }

            Dot* jt = it->dotHead;
            Dot* prevDot = NULL;
            for (; jt != NULL; jt = jt->next) {
                _dotDestructor(prevDot);
                prevDot = jt;
            }
            _dotDestructor(prevDot);

            _nodeDestructor(it);

            break;
        }
        prevNode = it;
    }


    for (Node* it = this->nodeHead; it != NULL; it = it->next) {
        Dot* prev = NULL;
        for (Dot* jt = it->dotHead; jt != NULL; jt = jt->next) {
            if (jt->x == x && jt->y == y) {
                flag = 0;
                if (prev == NULL) {
                    it->dotHead = jt->next;
                } else {
                    prev->next = jt->next;
                }
                _dotDestructor(jt);
                break;
            }
            prev = jt;
        }
    }
    return flag;
}

int deleteEdgeGraph(Graph* this, int x1, int y1, int x2, int y2) {
    if (this == NULL) return 1;

    for (Node* it = this->nodeHead; it != NULL; it = it->next) {
        if (it->dot->x != x1 || it->dot->y != y1) continue;

        Dot* prev = NULL;
        for (Dot* jt = it->dotHead; jt != NULL; jt = jt->next) {
            if (jt->x == x2 && jt->y == y2) {
                if (prev == NULL) {
                    it->dotHead = jt->next;
                } else {
                    prev->next = jt->next;
                }
                _dotDestructor(jt);
                return 0;
            }
            prev = jt;
        }
    }
    return 1;
}


int _recFindGraph(Graph* this, Node* node, int** colors, int*** path, int prevX, int prevY, int destX, int destY) {
    if (node == NULL) return 1;
    colors[node->dot->x][node->dot->y] = 1;
    path[node->dot->x][node->dot->y][0] = prevX;
    path[node->dot->x][node->dot->y][1] = prevY;
    for (Dot* it = node->dotHead; it != NULL; it = it->next) {
        if (colors[it->x][it->y])
            continue;

        if (it->x == destX && it->y == destY) {
            path[destX][destY][0] = node->dot->x;
            path[destX][destY][1] = node->dot->y;
            return 0;
        }

        Node* start = NULL;
        for (Node* jt = this->nodeHead; jt != NULL; jt = jt->next) {
            if (jt->dot->x == it->x && jt->dot->y == it->y) {
                start = jt;
                break;
            }
        }

        _recFindGraph(this, start, colors, path, node->dot->x, node->dot->y, destX, destY);

    }
}


int findGraph(Graph* this, int x1, int y1, int x2, int y2) {
    if (this == NULL) return 1;

    int maxX = -1;
    int maxY = -1;
    for (Node* it = this->nodeHead; it != NULL; it = it->next) {
        maxX = maxX > it->dot->x ? maxX : it->dot->x;
        maxY = maxY > it->dot->y ? maxY : it->dot->y;
        for (Dot* jt = it->dotHead; jt != NULL; jt = jt->next) {
            maxX = maxX > jt->x ? maxX : jt->x;
            maxY = maxY > jt->y ? maxY : jt->y;
        }
    }

    if (x1 > maxX || y1 > maxY ||
        x2 > maxX || y2 > maxY) {
        return 1;
    }

    Node* start = NULL;
    for (Node* it = this->nodeHead; it != NULL; it = it->next) {
        if (it->dot->x == x1 && it->dot->y == y1) {
            start = it;
            break;
        }
    }
    
    if (start == NULL) return 1;


    int** colors = (int**) calloc(maxX + 1, sizeof(int*));
    for (int i = 0; i < maxX + 1; ++i)
        colors[i] = (int*) calloc(maxY + 1, sizeof (int));


    if (colors == NULL) {
        printf("colors == NULL"); return 1;
    }

    int*** path = (int***) calloc(maxX + 2, sizeof(int**));
    for (int i = 0; i < maxY + 1; ++i) {
        path[i] = (int**) calloc(maxY + 2, sizeof (int*));
        for (int j = 0; j < maxY + 1; ++j) {
            path[i][j] = (int*) calloc(2, sizeof(int));
            for (int k = 0; k < 2; ++k) {
                path[i][j][k] = -2;
            }
        }
    }
    if (path == NULL) {
        printf("path == NULL"); return 1;
    }


    _recFindGraph(this, start, colors, path, -1, -1, x2, y2);


    int* el = path[x2][y2];
    int flag = 1;
    int count = 0;
    while (1) {
        if (path[el[0]][el[1]][0] == -1 &&
            path[el[0]][el[1]][1] == -1) {
            flag = 0;
            break;
        }
        if (path[el[0]][el[1]][0] == -2 &&
            path[el[0]][el[1]][1] == -2) {
            flag = 1;
            break;
        }
        count += 1;
        el = path[el[0]][el[1]];
    }
    count += 1;

    if (flag) return 1;

    int** res = (int**) calloc(count + 2, sizeof(int*));
    for (int i = 0; i < count; ++i) {
        res[i] = (int*) calloc(2, sizeof (int));
    }
    if (res == NULL) {
        printf("res == NULL"); return 1;
    }

    el = path[x2][y2];
    int k = count - 1;
    res[k--] = el;
    while (k >= 0) {
        if (path[el[0]][el[1]][0] == -1 &&
            path[el[0]][el[1]][1] == -1) {
            break;
        }
        el = path[el[0]][el[1]];
        res[k] = el;
        --k;
    }
    for (int i = 0; i < count; ++i) {
        printf("(%d, %d) ", res[i][0], res[i][1]);
    }
    printf("(%d, %d)", x2, y2);
    printf("\n");

    return 0;
}

typedef struct DictDotDot {
    Dot*** arr;
    int len;
} DictDotDot;

DictDotDot getDictDotDot(int len) {
    DictDotDot res;
    res.arr = (Dot***) calloc(len, sizeof (Dot**));
    for (int i = 0; i < len; ++i) {
        res.arr[i] = (Dot**) calloc(2, sizeof (Dot*));
    }
    res.len = len;
    return res;
}

typedef struct DictDotDouble {
    Dot** dotArr;
    double* doubleArr;
    int len;
} DictDotDouble;

DictDotDouble getDictDotDouble(int len) {
    DictDotDouble res;
    res.dotArr = (Dot**) calloc(len, sizeof (Dot*));
    res.doubleArr = (double*) calloc(len, sizeof (double));
    for (int i = 0; i < len; ++i) {
        res.doubleArr[i] = DBL_MAX;
    }
    res.len = len;
    return res;
}


void dictDestructor(DictDotDot* this) {
    for (int i = 0; i < this->len; ++i) {
        free(this->arr[i]);
    }
    free(this->arr);
}

int sFindGraph(Graph* this, int x1, int y1, int x2, int y2) {
    if (this == NULL) return 1;

    PQueue pQueue = getPQueue();

    Node* start = NULL;
    for (start = this->nodeHead; start != NULL; start = start->next) {
        if (start->dot->x == x1 && start->dot->y == y1) {
            break;
        }
    }
    if (start == NULL) return 1;

    int flag2 = 1;
    int count = 0;
    for (Node* it = this->nodeHead; it != NULL; it = it->next) {
        if (it->dot->x == x2 && it->dot->y == y2) {
            flag2 = 0;
        }
        for (Dot* jt = it->dotHead; jt != NULL; jt = jt->next) {
            if (jt->x == x2 && jt->y == y2) {
                flag2 = 0;
            }
            ++count;
        }
        ++count;
    }

    if (flag2) return 1;

    Dot** buf = (Dot**) calloc(count, sizeof (Dot*));
    int bufIt = 0;
    for (Node* it = this->nodeHead; it != NULL; it = it->next) {
        int flag = 0;
        for (int i = 0; i < bufIt; ++i) {
            if (buf[i]->x == it->dot->x &&
                buf[i]->y == it->dot->y) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            buf[bufIt] = it->dot;
            ++bufIt;
        }
        for (Dot* jt = it->dotHead; jt != NULL; jt = jt->next) {
            flag = 0;
            for (int i = 0; i < bufIt; ++i) {
                if (buf[i]->x == jt->x &&
                    buf[i]->y == jt->y) {
                    flag = 1;
                    break;
                }
            }
            if (flag) continue;

            buf[bufIt] = jt;
            ++bufIt;
        }
    }
    count = bufIt;

    free(buf);



    DictDotDot path = getDictDotDot(count);
    int pathIt = 0;

    for (Node* it = this->nodeHead; it != NULL; it = it->next) {
        int flag = 0;
        for (int i = 0; i < pathIt; ++i) {
            if (path.arr[i][0]->x == it->dot->x &&
                path.arr[i][0]->y == it->dot->y) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            path.arr[pathIt][0] = it->dot;
            ++pathIt;
        }
        for (Dot* jt = it->dotHead; jt != NULL; jt = jt->next) {
            flag = 0;
            for (int i = 0; i < pathIt; ++i) {
                if (path.arr[i][0]->x == jt->x &&
                    path.arr[i][0]->y == jt->y) {
                    flag = 1;
                    break;
                }
            }
            if (flag) continue;

            path.arr[pathIt][0] = jt;
            ++pathIt;
        }
    }

    for (int i = 0; i < count; ++i) {
        path.arr[i][1] = NULL;
    }



    DictDotDouble dist = getDictDotDouble(count);
    int distIt = 0;

    for (Node* it = this->nodeHead; it != NULL; it = it->next) {
        int flag = 0;
        for (int i = 0; i < distIt; ++i) {
            if (dist.dotArr[i]->x == it->dot->x &&
                dist.dotArr[i]->y == it->dot->y) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            dist.dotArr[distIt] = it->dot;
            ++distIt;
        }
        for (Dot* jt = it->dotHead; jt != NULL; jt = jt->next) {
            flag = 0;
            for (int i = 0; i < distIt; ++i) {
                if (dist.dotArr[i]->x == jt->x &&
                    dist.dotArr[i]->y == jt->y) {
                    flag = 1;
                    break;
                }
            }
            if (flag) continue;

            dist.dotArr[distIt] = jt;
            ++distIt;
        }
    }

    for (int i = 0; i < count; ++i) {
        dist.doubleArr[i] = DBL_MAX;
    }



    for (int i = 0; i < dist.len; ++i) {
        if (dist.dotArr[i]->x == start->dot->x &&
            dist.dotArr[i]->y == start->dot->y) {
            dist.doubleArr[i] = 0;
            break;
        }
    }

    addPQueue(&pQueue, start->dot, 0);

    while(!isEmpty(&pQueue)) {
        Dot* top = popPQueue(&pQueue);


        Node* node = NULL;
        for (Node* it = this->nodeHead; it != NULL; it = it->next) {
            if (it->dot->x == top->x && it->dot->y == top->y) {
                node = it;
                break;
            }
        }
        if (node == NULL) {
            continue;
        }
        double dNode = -1;
        for (int i = 0; i < dist.len; ++i) {
            if (dist.dotArr[i]->x == node->dot->x &&
                dist.dotArr[i]->y == node->dot->y) {
                dNode = dist.doubleArr[i];
                break;
            }
        }

        for (Dot* it = node->dotHead; it != NULL; it = it->next) {


            double dDot = -1;
            for (int i = 0; i < dist.len; ++i) {
                if (dist.dotArr[i]->x == it->x &&
                    dist.dotArr[i]->y == it->y) {
                    dDot = dist.doubleArr[i];
                    break;
                }
            }
            if (dDot > dNode + it->r) {
                for (int i = 0; i < dist.len; ++i) {
                    if (dist.dotArr[i]->x == it->x &&
                        dist.dotArr[i]->y == it->y) {
                        dist.doubleArr[i] = dNode + it->r;
                        break;
                    }
                }

                for (int i = 0; i < path.len; ++i) {
                    if (path.arr[i][0]->x == it->x &&
                        path.arr[i][0]->y == it->y) {
                        path.arr[i][1] = node->dot;
                        break;
                    }
                }
                if (it->x != x2 || it->y != y2) {
                    addPQueue(&pQueue, it, dNode + it->r);
                }
            }
        }
    }

    Dot* it = NULL;
    for (int i = 0; i < path.len; ++i) {
        if (path.arr[i][0]->x == x2 &&
            path.arr[i][0]->y == y2) {
            it = path.arr[i][0];
            break;
        }
    }


    int bufCount = 0;
    while (it != NULL) {
        if (it->x == x1 && it->y == y1) {
            break;
        }
        for (int i = 0; i < path.len; ++i) {
            if (path.arr[i][0]->x == it->x &&
                path.arr[i][0]->y == it->y) {
                ++bufCount;
                it = path.arr[i][1];
                break;
            }
        }
    }

    if (it == NULL || !(it->x == x1 && it->y == y1)) return 1;


    Dot** res = calloc(bufCount, sizeof (Dot*));
    int resIt = 0;
    int bufbufCount = bufCount;
    bufCount -= 1;


    it = NULL;
    for (int i = 0; i < path.len; ++i) {
        if (path.arr[i][0]->x == x2 &&
            path.arr[i][0]->y == y2) {
            it = path.arr[i][0];
            break;
        }
    }
    res[bufCount] = it;
    while (it != NULL) {
        if (it->x == x1 && it->y == y1) {
            break;
        }
        for (int i = 0; i < path.len; ++i) {
            if (path.arr[i][0]->x == it->x &&
                path.arr[i][0]->y == it->y) {
                it = path.arr[i][1];
                res[bufCount] = it;
                bufCount -= 1;
                break;
            }
        }
    }

    for (int i = 0; i < bufbufCount; ++i) {
        printf("(%d, %d), ", res[i]->x, res[i]->y);
    }
    printf("(%d, %d)", x2, y2);
    printf("\n");






    free(res);



    return 0;
}

void printGraph(Graph* this) {
    if (this == NULL) return;

    for (Node* it = this->nodeHead; it != NULL; it = it->next) {
        printf("(%d, %d) : ", it->dot->x, it->dot->y);
        for (Dot* jt = it->dotHead; jt != NULL; jt = jt->next) {
            printf("(%d, %d)_%f", jt->x, jt->y, jt->r);
            if (jt->next != NULL)
                printf(", ");
        }
        printf("\n");
    }
}



void graphDestructor(Graph* this) {
    if (this == NULL) return;

    Node* prevIt = NULL;
    Node* it = this->nodeHead;
    for (; it != NULL; it = it->next) {
        _nodeDestructor(prevIt);
        Dot* prevJt = NULL;
        Dot* jt = it->dotHead;
        for (; jt != NULL; jt = jt->next) {
            _dotDestructor(prevJt);
            prevJt = jt;
        }
        _dotDestructor(prevJt);

        prevIt = it;
    }
    _nodeDestructor(prevIt);

}
