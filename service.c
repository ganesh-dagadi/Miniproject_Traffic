#include "TrafficAlgo.h"
#include <stdio.h>
int main() {
	initializeNodes();
	createNode(5 , 8);
	createNode(7, 6);
	createNode(8, 2);
	createNode(5, 4);
	//createNode(2, 2);
	createNode(2, 6);
	//createNode(5, 4);
	addRoads(0, 1 , 2);
	addRoads(1, 2, 1);
	addRoads(1, 3, 1);
	addRoads(2, 3, 3);
	addRoads(0, 4, 3);
	addRoads(4, 3, 3);
	//addRoads(6, 2, 1);
	//addRoads(6, 5, 2);
	//addRoads(5, 4, 4);
	//addRoads(4, 3, 4);
	//addRoads(3, 2, 3);
	node* nodes = getSetupData();
	printf("Here");
	for (int i = 0; i < MAX_JUNCS; i++) {
		if (nodes[i].id == -1) {
			continue;
		}
		printf("Node id is %d coordinates(%d , %d) \n", nodes[i].id, nodes[i].x, nodes[i].y);
		for (int j = 0; j < MAX_ROADS; j++) {
			if (nodes[i].roads[j] == NULL) {
				continue;
			}
			printf("Road is from %d to %d with capacity %d and distance %f \n", nodes[i].id, nodes[i].roads[j]->to, nodes[i].roads[j]->capacity, nodes[i].roads[j]->dis);
		}
		printf("New junction \n");
	}

	int arr[NUM_VEHICLES][MAX_ROADS];
	generateRoutesOutput(arr);
	printf("Here");
	for (int i = 0; i < NUM_VEHICLES; i++) {
		for (int j = 0; j < MAX_ROADS; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}