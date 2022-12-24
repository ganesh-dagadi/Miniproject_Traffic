#pragma once
#include "TrafficAlgo.h"
node* initialSetup();
node* refreshSetup();
int** SfindPaths(int arr[NUM_VEHICLES][MAX_ROADS]);
void addOperation(char op, short int x, short int y, short int to, short int from, short int capacity, short int nodeId, road* rd, short int fromNodeId , int src , int dest);