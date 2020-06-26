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
    if res


}

PersonList* enterElevator(Elevator *e, PersonList *list){
    PersonList* res = (PersonList*) malloc(sizeof(PersonList));

}

