#include "UserDefVar.h"

void createNode(int x, int y);
void printNodes();
void initializeNodes();
void addRoads(int from, int to, int capacity);
void removeNode(int nodeId);
void removeRoad(road * rd, int fromNodeId);
int** generateRoutesOutput(int arr[NUM_VEHICLES][MAX_ROADS]);
void changeRoadCapacity(road* rd, int capacity);
node* getSetupData();
node* getNode(int nodeId);
void setSourceNode(int nodeId);
int getSrcNode();
void setDestNode(int nodeId);
int getDestNode();
