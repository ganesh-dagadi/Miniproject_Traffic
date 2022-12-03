#include <stdio.h>
#include <stdlib.h>

#define MAX_JUNCS 10
#define MAX_ROADS 10
#define NUM_JUNCS 5
typedef struct road {
    int to;
    int dis;
    int capacity;
}road;

typedef struct node {
    int id;
    int explored;
    road* roads[MAX_ROADS];
    int* prev;
    int shortestDis;
    int currDis;
}node;
node nodes[MAX_JUNCS];

void initialzeGraph();
void addRoad(int nodeId, int to, int dis, int capacity);
void displayRoads(int nodeId);


void main(void) {
    //Creating our graph
    initialzeGraph();
}


void initialzeGraph() {
    //creating our nodes
    int i = 0;
    int j = 0;
    for (i; i < MAX_JUNCS; i++) {
        nodes[i].id = i;
        nodes[i].explored = 0;
        for (j; j < MAX_ROADS; j++) {
            nodes[i].roads[j] = NULL;
        }
    }

    //creating our roads.
    //A=0 B=1 C=2 D=3 E=4

    addRoad(0, 1, 3, 2);
    addRoad(0, 2, 5, 3);
    addRoad(1, 0, 3, 2);
    addRoad(1, 2, 5, 1);
    addRoad(1, 4, 2, 1);
    addRoad(2, 0, 5, 3);
    addRoad(2, 1, 5, 1);
    addRoad(2, 3, 4, 3);
    addRoad(3, 2, 4, 3);
    addRoad(3, 4, 3, 2);
    addRoad(4, 3, 3, 2);
    addRoad(4, 1, 2, 1);

    displayRoads(4);
}

void addRoad(int nodeId, int to, int dis, int capacity) {
    int i = 0;
    int j = 0;
    for (i; i < MAX_JUNCS; i++) {
        if (i == nodeId) {
            for (j; j < MAX_ROADS; j++) {
                if (nodes[i].roads[j] == NULL) {
                    road* newRoad = (road*)malloc(sizeof(road));
                    newRoad->capacity = capacity;
                    newRoad->to = to;
                    newRoad->dis = dis;
                    nodes[i].roads[j] = newRoad;
                    break;
                }
            }
        }
    }
}

void displayRoads(int nodeId) {
    int i = 0;
    for (i; i < MAX_ROADS; i++) {
        if (nodes[nodeId].roads[i] == NULL) {
            return;
        }
        printf("Road %d is to %d dis %d capacity %d \n", i, nodes[nodeId].roads[i]->to, nodes[nodeId].roads[i]->dis, nodes[nodeId].roads[i]->capacity);
    }
}