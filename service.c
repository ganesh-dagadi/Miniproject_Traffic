#include "TrafficAlgo.h"
#include <stdio.h>
int main() {
	initializeNodes();
	createNode(4, 8);
	createNode(7, 5);
	createNode(7, 3);
	createNode(2, 3);
	createNode(1, 2);
	createNode(2, 0);
	addRoads(4, 5, 2);
	addRoads(5, 2, 2);
	addRoads(0, 4, 2);
	addRoads(4, 2, 1);
	addRoads(0, 1, 1);
	addRoads(1, 2, 1);
	addRoads(0, 3, 2);
	addRoads(3, 2, 2);
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
	for (int i = 0; i < NUM_VEHICLES; i++) {
		for (int j = 0; j < MAX_ROADS; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}