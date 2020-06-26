
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>

#include "elevator.h"
#include "person.h"

Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons){
    Elevator* p = (Elevator*) malloc(sizeof(Elevator));
    p->capacity = capacity;
    p->currentFloor= currentFloor;
    p->persons= persons;
    return p;
}
Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists){
    Building* p = (Building*) malloc(sizeof(Building));
    p->nbFloor = nbFloor;
    p->elevator= elevator;
    p->waitingLists = waitingLists;
    return p;
}

void stepElevator(Building *b){
}