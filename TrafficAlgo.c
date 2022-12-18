#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_JUNCS 10
#define MAX_ROADS 10
#define NUM_JUNCS 10
#define NUM_VEHICLES 4

int sourceNode = 0;
int destNode = 3;

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
    float shortestDis;
    float currDis;
    int comingFrom;
    int x;
    int y;
}node;
node nodes[MAX_JUNCS];

void initializeNodes() {
    int i = 0;
    for (i; i < MAX_JUNCS; i++) {
        nodes[i].id = -1;
    }
}
void createNode(int x, int y) {
    int i;
    int j;
    for (i = 0; i < MAX_JUNCS; i++) {
        if (nodes[i].id == -1) {
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
    int i = 0;
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
//TODO VERIFY The next 2 FUNC WORK
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

void changeRoadCapacity(road* rd , int capacity) {
    rd->capacity = capacity;
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
    toRemove->id = -1;
}

node* getSetupData() {
   return nodes;
} 

// return 0 if lane not found
int setShortestPaths(int currentNode , int laneFound) {
    for (int i = 0; i < MAX_ROADS; i++) {
        node* currentJunc = getNode(currentNode);
        
        if ((*currentJunc).roads[i] == NULL) continue;
        road currentRoad = *((*currentJunc).roads[i]);
        node* toJunc = getNode(currentRoad.to);
        
        if (!(*toJunc).explored && (currentRoad.capacity > 0)) {
            (*toJunc).currDis = (*currentJunc).shortestDis + currentRoad.dis;
            (*toJunc).comingFrom = (*currentJunc).id;
            laneFound = 1;
            if ((*toJunc).currDis < (*toJunc).shortestDis) {
                (*toJunc).shortestDis = (*toJunc).currDis;
                (*toJunc).prev = (*currentJunc).id;
            }
        }
    }

    return laneFound;
}
int generatePathsCopy(int arr[NUM_VEHICLES][MAX_ROADS]) {
    int remainingVehicles = NUM_VEHICLES;
    int currentNode = sourceNode;
    //initial shortest distance being set to infinity
    for (int i = 0; i < NUM_JUNCS; i++) {
        nodes[i].shortestDis = INT_MAX;
    }

    while (remainingVehicles) {
        short int laneFound = 0;
        node* currentJunc = getNode(sourceNode);
        (*currentJunc).explored = 1;
        (*currentJunc).prev = (*currentJunc).id;
        (*currentJunc).shortestDis = 0;
        (*currentJunc).currDis = 0;
        (*currentJunc).comingFrom = (*currentJunc).id;

        while (currentNode != destNode) {
            laneFound = 0;
            laneFound = setShortestPaths(currentNode, laneFound);

            if (!laneFound) {
                while (currentNode != sourceNode && !laneFound) {
                    node * currentJunc = getNode(currentNode);
                    currentNode = (*currentJunc).comingFrom;
                    laneFound = setShortestPaths(currentNode , laneFound);
                }
                if (currentNode == sourceNode) {
                    laneFound = setShortestPaths(currentNode , 0);
                    if (!laneFound) {
                        return 0;
                    }
                }
            }

            int nearestNode = 0;
            currentJunc = getNode(currentNode);
            for (int i = 0; i < MAX_ROADS; i++) {
                if ((*currentJunc).roads[i] == NULL) continue;
                road currentRoad = *((*currentJunc).roads[i]);
                node* toJunc = getNode(currentRoad.to);
                if (!(*toJunc).explored) nearestNode = (*toJunc).id;
                else continue;
            }
            node* nearestJunc = getNode(nearestNode);
            currentJunc = getNode(currentNode);
            for (int i = 0; i < MAX_ROADS; i++) {
                if ((*currentJunc).roads[i] == NULL) continue;
                road currentRoad = *((*currentJunc).roads[i]);
                node* toJunc = getNode(currentRoad.to);
                if (!(*toJunc).explored && ((*toJunc).shortestDis < (*nearestJunc).shortestDis)) {
                    nearestNode = (*toJunc).id;
                }
            }
            
            nearestJunc = getNode(nearestNode);
            (*nearestJunc).explored = 1;
            currentNode = nearestNode;
        }

        //traverse back to start
        int juncNum = 0;
        while (1) {
            currentJunc = getNode(currentNode);
            for (int i = 0; i < MAX_ROADS; i++) {
                if ((*currentJunc).roads[i]->to == (*currentJunc).prev) {
                    (*currentJunc).roads[i]->capacity -= 1;
                    break;
                }
            }
            int prev = (*currentJunc).prev;
            for (int i = 0; i < MAX_ROADS; i++) {
                node* prevNode = getNode(prev);
                if ((*prevNode).roads[i]->to == currentNode) {
                    (*prevNode).roads[i]->capacity -= 1;
                    break;
                }
            }

            //registering the path
            currentJunc = getNode(currentNode);
            arr[NUM_VEHICLES - remainingVehicles][juncNum] = currentNode;
            currentNode = (*currentJunc).prev;
            ++juncNum;
            if (currentNode == sourceNode) {
                arr[NUM_VEHICLES - remainingVehicles][juncNum] = currentNode;
                break;
            };
        }

        remainingVehicles -= 1;
        currentNode = sourceNode;
        for (int i = 0; i < MAX_JUNCS; i++) {
            nodes[i].explored = 0;
            nodes[i].currDis = INT_MAX;
            nodes[i].shortestDis = INT_MAX;
            nodes[i].comingFrom = NULL;
        }
    }
    return 1;
}
void printRouteOutput(int arr[NUM_VEHICLES][MAX_ROADS]) {
    for (int i = 0; i < NUM_VEHICLES; i++) {
        for (int j = 0; j < MAX_ROADS; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int** generateRoutesOutput(int arr[NUM_VEHICLES][MAX_ROADS]) {
    
    for (int i = 0; i < NUM_VEHICLES; i++) {
        for (int j = 0; j < MAX_ROADS; j++) {
            arr[i][j] = -1;
        }
    }
    
    if (generatePathsCopy(arr)) {
        printf("\nLane Found \n");
    }
    else {
        printf("\n Lane not found \n");
    }
    return arr;
}

