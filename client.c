#include <stdio.h>
#include "service.h"
#include "TrafficAlgo.h";
int main() {
	node* nodes = initialSetup();
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
	SfindPaths(arr);
	for (int i = 0; i < NUM_VEHICLES; i++) {
		for (int j = 0; j < MAX_ROADS; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	addOperation('n', 1, 2 , 0 , 0 , 0 , 0 , 0 , 0);
	addOperation('n', 2, 0, 0, 0, 0, 0, 0, 0);
	addOperation('r', 0, 0, 4, 0, 2, 0, 0, 0);
	addOperation('r' , 0 , 0 , 5 , 4 , 2 , 0 , 0 , 0);
	addOperation('r', 0, 0, 2, 5, 1, 0, 0, 0);
	addOperation('r', 0, 0, 2, 4, 1, 0, 0, 0);
	printf("Done operations \n \n");
	nodes = refreshSetup();
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
	SfindPaths(arr);
	for (int i = 0; i < NUM_VEHICLES; i++) {
		for (int j = 0; j < MAX_ROADS; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	return 0;
}