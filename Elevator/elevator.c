
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>

#include "elevator.h"
#include "person.h"

Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons){
    Elevator* e = (Elevator*) malloc(sizeof(Elevator));
    e->capacity = capacity;
    e->currentFloor= currentFloor;
    e->persons= persons;
    return e;
}
Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists){
    Building* b = (Building*) malloc(sizeof(Building));
    b->nbFloor = nbFloor;
    b->elevator= elevator;
    b->waitingLists = waitingLists;
    return b;
}

void stepElevator(Building *b){
    if(b->elevator->currentFloor == b->nbFloor){
        PersonList* exitElevator(Elevator *e);
        PersonList* enterElevator(Elevator *e, PersonList *list);
    }
    else {
        b->elevator->currentFloor=b->elevator->currentFloor+1;
    }
}