#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_JUNCS 10
#define MAX_ROADS 10
#define NUM_JUNCS 5
#define NUM_VEHICLES 7

typedef struct road {
    int to;
    float dis;
    int capacity;
}road;

typedef struct node {
    int id;
    int explored;
    road* roads[MAX_ROADS];
    int prev;
    int shortestDis;
    int currDis;
    int x;
    int y;
}node;
node nodes[MAX_JUNCS];

void initializeNodes() {
    int i = 0;
    for (i; i < MAX_JUNCS; i++) {
        nodes[i].id = 0;
    }
}
void createNode(int x, int y) {
    int i;
    int j;
    for (i = 1; i < MAX_JUNCS; i++) {
        if (nodes[i].id == 0) {
            nodes[i].id = i;
            nodes[i].x = x;
            nodes[i].y = y;
            nodes[i].explored = 0;
            for (j = 0; j < MAX_ROADS; j++) {
                nodes[i].roads[j] = NULL;
            }
            break;
        }  
    }
}

void printNodes() {
    int i = 1;
    int j = 0;
    for (i; i < MAX_JUNCS; i++) {
        printf("Node is %d x %d y %d \n" , nodes[i].id , nodes[i].x , nodes[i].y);
        for (j = 0; j < MAX_ROADS; j++) {
            if (nodes[i].roads[j] == NULL) break;
            printf("%d road \n", nodes[i].roads[j]->capacity);
        }
    }
}

node* getNode(int nodeId) {
    for (int i = 0; i < MAX_JUNCS; i++) {
        if (nodes[i].id == nodeId) {
            return &nodes[i];
        }
    }
}

float findDistanceBetweenNodes(node node1 , node node2 ) {
    int x1 = node1.x;
    int y1 = node1.y;

    int x2 = node2.x;
    int y2 = node2.y;

    return (sqrt( ( pow((x2 - x1), 2) + pow((y2 - y1), 2) ) ));
}
void addRoads(int from , int to , int capacity) {
    node* fromNodeptr = getNode(from);
    node* toNodeptr = getNode(to);
    float distance = findDistanceBetweenNodes(*toNodeptr, *fromNodeptr);
    int j = 0;
    for (j; j < MAX_ROADS; j++) {
        if ((*fromNodeptr).roads[j] == NULL) {
            road* newRoad = (road*)malloc(sizeof(road));
            newRoad->capacity = capacity;
            newRoad->to = to;
            newRoad->dis = distance;
            (*fromNodeptr).roads[j] = newRoad;
            break;
        }
    }
    j = 0;

    for (j; j < MAX_ROADS; j++) {
        if ((*toNodeptr).roads[j] == NULL) {
            road* newRoad = (road*)malloc(sizeof(road));
            newRoad->capacity = capacity;
            newRoad->to = from;
            newRoad->dis = distance;
            (*toNodeptr).roads[j] = newRoad;
            break;
        }
    }
}

void removeRoad(road* rd, int fromNodeId) {
    node* toNode = getNode(rd->to);
    printf("%d \n ", toNode->id);
    rd = NULL;
    int j;
    for (j = 0; j < MAX_ROADS; j++) {
        if (! (*toNode).roads[j]) {
            continue;
        }
        if (toNode->roads[j]->to == fromNodeId) {
            toNode->roads[j] = NULL;
        }
    }
}
void removeNode(int nodeId) {
    node* toRemove = getNode(nodeId);
    //set node id to 0 (it is not valid)
    int j;
    for (j = 0; j < MAX_ROADS; j++) {
        if (toRemove->roads[j] != NULL) {
            removeRoad(toRemove->roads[j] , toRemove->id);
            toRemove->roads[j] = NULL;
        }
    }
    toRemove->id = 0;
}

