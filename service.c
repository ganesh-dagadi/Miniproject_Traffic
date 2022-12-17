#include "TrafficAlgo.h"
#include <stdio.h>
int main() {
	initializeNodes();
	createNode(5 , 8);
	createNode(7, 6);
	createNode(8, 2);
	createNode(2, 2);
	addRoads(1, 2 , 2);
	addRoads(2, 3, 2);
	printNodes();
	printf("Removing node \n");
	removeNode(2);
	printf("printing node \n");
	printNodes();
	createNode(7, 6);
	printf("Printing Nodes \n");
	printNodes();
	return 0;
}