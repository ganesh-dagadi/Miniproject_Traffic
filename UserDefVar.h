#pragma once

#define MAX_JUNCS 10
#define MAX_ROADS 10
#define NUM_JUNCS 10
#define NUM_VEHICLES 10
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
