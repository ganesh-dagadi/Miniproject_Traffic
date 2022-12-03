#include <stdio.h>
#include <stdlib.h>

#define MAX_JUNCS 10
#define MAX_ROADS 10
#define NUM_JUNCS 5
#define NUM_VEHICLES 5
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
int startNode = 0;
int endNode = 4;
void initialzeGraph();
void addRoad(int nodeId, int to, int dis, int capacity);
void displayRoads(int nodeId);
void prepareRoutes(int arr[NUM_VEHICLES][MAX_ROADS]);
void printOutput(int arr[NUM_VEHICLES][MAX_ROADS]);

short int  main(void) {
    //Creating our graph
    initialzeGraph();
    int numVehicles = 5;
    int output[NUM_VEHICLES][MAX_ROADS];
    for (int i = 0; i < NUM_VEHICLES; i++) {
        for (int j = 0; j < MAX_ROADS; j++) {
            output[i][j] = -1;
        }
    }

    printOutput(output);
}
void prepareRoutes(int arr[NUM_VEHICLES][MAX_ROADS]) {
    int remainingVehicles = NUM_VEHICLES;
    int currentNode = startNode;
    //initial current distance being set to infinity
    for (int i = 0; i < NUM_JUNCS; i++) {
        nodes[i].shortestDis = INT_MAX;
    }
    //starting main loop
    // exit when either all vehicles have passed or road has been blocked.
    while (remainingVehicles) {
        short int laneFound = 0;
        nodes[startNode].explored = 1;
        nodes[startNode].prev = nodes[startNode].id;
        nodes[startNode].shortestDis = 0;
        nodes[startNode].currDis = 0;

        while (currentNode != endNode) {
            for (int i = 0; i < MAX_ROADS; i++) {
                if (nodes[currentNode].roads[i] == NULL) break;
                road currentRoad = *(nodes[currentNode].roads[i]);
                if (!nodes[currentRoad.to].explored && (currentRoad.capacity > 0)) {
                    nodes[currentRoad.to].currDis = nodes[currentNode].shortestDis + currentRoad.dis;
                    laneFound = 1;
                    if (nodes[currentRoad.to].currDis < nodes[currentRoad.to].shortestDis) {
                        nodes[currentRoad.to].shortestDis = nodes[currentRoad.to].currDis;
                        nodes[currentRoad.to].prev = nodes[currentNode].id;
                    }
                }
            }
            if (!laneFound) goto laneNotFound;
            int nearestNode;
            
            for (int i = 0; i < MAX_ROADS; i++) {
                if (nodes[currentNode].roads[i] == NULL) break;
                road currentRoad = *(nodes[currentNode].roads[i]);
                //setting first unexplored node to be nearest
                if (!nodes[currentRoad.to].explored) nearestNode = nodes[currentRoad.to].id;
                else continue;

                if (!nodes[currentRoad.to].explored && (!nodes[currentRoad.to].shortestDis < nodes[nearestNode].shortestDis)) {
                    nearestNode = nodes[currentRoad.to].id;
                }
            }

            nodes[nearestNode].explored = 1;
            currentNode = nearestNode;

            if (currentNode == endNode) {

            }
        }

    }

        laneNotFound:
            printf("Lane not found");
            return 0;
}
void printOutput(int arr[NUM_VEHICLES][MAX_ROADS]) {
    for (int i = 0; i < NUM_VEHICLES; i++) {
        for (int j = 0; j < MAX_ROADS; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
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