#include <time.h>
#include <stdlib.h>
#include <ncurses.h>

#include "elevator.h"
#include "person.h"

Person* createPerson(int src, int dest){
    Person* p = (Person*) malloc(sizeof(Person));
    p->src =src;
    p->dest =dest;
    return p;
}

PersonList* insert(Person *p, PersonList *list){
    PersonList* res = (PersonList*) malloc(sizeof(PersonList));
    res->person= p;
    res->next=list;
    return res;
}

PersonList* exitElevator(Elevator *e){
  
    PersonList* res = (PersonList*) malloc(sizeof(PersonList));
  
    if (e->persons->person->dest==e->currentFloor){
        res->person= e->persons->person;
        free(e->persons->person);
        e->persons= e->persons->next;
        res= res->next;
        exitElevator(e);
    }
    else {
        e->persons= e->persons->next;
        exitElevator(e);
    }
    return res;
}
PersonList* enterElevator(Elevator *e, PersonList *waitingList){
        while (sizeof(e->persons)<e->capacity ){
            if (waitingList->person->dest==e->currentFloor){
                e->persons->person= waitingList->person;
                free(waitingList->person);
                e->persons= e->persons->next;
                enterElevator(e,waitingList->next);
            }
            else {
                enterElevator(e,waitingList->next);

            } 
        }
        return waitingList;   
}
