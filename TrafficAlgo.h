#pragma once
#define MAX_JUNCS 10
#define MAX_ROADS 10
#define NUM_JUNCS 10
#define NUM_VEHICLES 4
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

void createNode(int x, int y);
void printNodes();
void initializeNodes();
void addRoads(int from, int to, int capacity);
void removeNode(int nodeId);
void removeRoad(road * rd, int fromNodeId);
int** generateRoutesOutput(int arr[NUM_VEHICLES][MAX_ROADS]);
void changeRoadCapacity(road* rd, int capacity);
node* getSetupData();
