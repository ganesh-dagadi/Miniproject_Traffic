#include "TrafficAlgo.h"
#include <stdio.h>
#include "service.h"

typedef struct operation {
	char option;
	short int x;
	short int y;
	short int to;
	short int from;
	short int capacity;
	short int nodeId;
	road* rd;
	short int fromNodeId;
}operation;

operation operations[30];
	

node* initialSetup() {
	initializeNodes();
	createNode(4, 8);
	createNode(7, 5);
	createNode(7, 3);
	createNode(2, 3);
	//createNode(1, 2);
	//createNode(2, 0);
	//addRoads(4, 5, 2);
	//addRoads(5, 2, 2);
	//addRoads(0, 4, 2);
	//addRoads(4, 2, 1);
	addRoads(0, 1, 1);
	addRoads(1, 2, 1);
	addRoads(0, 3, 2);
	addRoads(3, 2, 2);
	for (int i = 0; i < 30; i++) {
		operations[i].option = '0';
	}
	return getSetupData();
}

void addOperation(char op, short int x, short int y, short int to, short int from, short int capacity, short int nodeId, road* rd, short int fromNodeId)
{
	/*
	add node : n
	add Road : r
	remove road : k
	remove node : l
	change capacity : c
	*/
	int i;
	for (i = 0; i < 30; i++) {
		if (operations[i].option == '0') {
			break;
		}
	}
	switch (op) {
	case 'n':
		operations[i].option = 'n';
		operations[i].x = x;
		operations[i].y = y;
		break;
	case 'r':
		operations[i].option = 'r';
		operations[i].to = to;
		operations[i].from = from;
		operations[i].capacity = capacity;
		break;
	case 'k':
		operations[i].option = 'k';
		operations[i].nodeId = nodeId;
		break;
	case 'l':
		operations[i].option = 'l';
		operations[i].rd = rd;
		operations[i].fromNodeId = fromNodeId;
		break;
	case 'c':
		operations[i].option = 'c';
		operations[i].capacity = capacity;
	}
}

node* refreshSetup() {
	initializeNodes();
	createNode(4, 8);
	createNode(7, 5);
	createNode(7, 3);
	createNode(2, 3);
	//createNode(1, 2);
	//createNode(2, 0);
	//addRoads(4, 5, 2);
	//addRoads(5, 2, 2);
	//addRoads(0, 4, 2);
	//addRoads(4, 2, 1);
	addRoads(0, 1, 1);
	addRoads(1, 2, 1);
	addRoads(0, 3, 2);
	addRoads(3, 2, 2);
	// user updated operations
	int i;
	for (i = 0; i < 30; i++) {
		if (operations[i].option == '0') {
			break;
		}
		
		switch (operations[i].option) {
		case 'n':
			printf("Ran %d times \n", i);
			createNode(operations[i].x, operations[i].y);
			break;
		case 'r':
			addRoads(operations[i].from, operations[i].to , operations[i].capacity);
			break;
		case 'k':
			removeRoad(operations[i].rd, operations[i].fromNodeId);
			break;
		case 'l':
			removeNode(operations[i].nodeId);
			break;
		case 'c':
			changeRoadCapacity(operations[i].rd, operations[i].capacity);
		}
	}

	return getSetupData();
}

int** SfindPaths(int arr[NUM_VEHICLES][MAX_ROADS]) {
	return generateRoutesOutput(arr);
}