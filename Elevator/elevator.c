

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

PersonList* exitElevator(Elevator *e){
    PersonList* P,* E, *F,*D;
    PersonList* res =NULL;
    P = e->persons;
    D = P;
    if(e->persons!=NULL){
        while ( e->persons != NULL && e->persons->person->dest==e->currentFloor){
            E=(PersonList*) malloc(sizeof(PersonList));
            E->person = e->persons->person;
            if(res==NULL){
                res=E;
                F=res;
            }else{
                F->next = E;
                F = E;
            }
            if(e->persons->next==NULL){
                e->persons=NULL;
            }else{
                e->persons = P->next;
            }
            
            //free(P);
            P=e->persons;

        }
        if(e->persons !=NULL  && e->persons->next!=NULL){
            D = P;
            P=P->next;
            while (P!=NULL)
            {
                if (P->person->dest==e->currentFloor){
                    E=(PersonList*) malloc(sizeof(PersonList));
                    E->person = P->person;
                    if(res==NULL){
                        res=E;
                        F=res;
                    }else{
                        F->next = E;
                        F = E;
                    }
                    if(P->next!=NULL){
                        D->next = P->next;
                    }else{
                        D->next =NULL;
                    }  
                    //free(P);
                    P=D->next;
                }else{
                    P = P->next;
                    D = D->next;
                }
            }
        }
        /*
        while (P->next!=NULL)
        {
            if (P->person->dest==e->currentFloor){
                E=(PersonList*) malloc(sizeof(PersonList));
                E->person = P->person;
                if(res==NULL){
                    res=E;
                    F=res;
                }else{
                    F->next = E;
                    F = E;
                }
                D->next = P->next;
                //free(P);
                P=D->next;
            }
            P = P->next;
            D = D->next;
        }*/
    }
  return res;
}
  //PersonList* res = (PersonList*) malloc(sizeof(PersonList));
  /*
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
}*/

PersonList* enterElevator(Elevator *e, PersonList *waitingList,Building *b){
       PersonList *P;
       PersonList *F;
       PersonList *E;
       int PersonsInE=0;//Nombre de personne dans l'ascensseur
       P= e->persons;
       while(P != NULL){
            PersonsInE++;
            P = P->next;
       }
       if(waitingList!=NULL){
            if(PersonsInE==0){//Cas ou l'ascensseur est vide
                E = (PersonList *)malloc(sizeof(PersonList));
                E->person = waitingList->person;
                e->persons = E;
            }else{
                if(PersonsInE<e->capacity ){
                    F = e->persons;
                    while (F->next != NULL)
                    {
                        F = F->next;
                    }            
                    if (waitingList->person->src==e->currentFloor){
                        E = (PersonList *)malloc(sizeof(PersonList));
                        E->person = waitingList->person;
                        F->next =  E;
                    }
                }
            }
            if(PersonsInE<e->capacity ){
                if(waitingList->next ==NULL){
                    b->waitingLists[e->currentFloor]=NULL;
                }else{
                    P = waitingList->next;
                    F = waitingList;
                    while (P->next !=NULL)
                    {
                        F->person = P->person;
                        F=P;
                        P=P->next;
                    }
                    F->person = P->person;
                    F->next=NULL;
                }
                
                
            }
        }
        
        return waitingList;   
}
void stepElevator(Building *b){
    //Si l'étage courant est bien la destination
    if(b->elevator->currentFloor == b->elevator->targetFloor){
        exitElevator(b->elevator); 
        enterElevator(b->elevator, b->waitingLists[b->elevator->currentFloor],b);
    }
    else {
        //Si l'étage courant est superieur de la destination on descend
        if (b->elevator->currentFloor > b->elevator->targetFloor)
        {
            b->elevator->currentFloor=b->elevator->currentFloor-1;
        }else if (b->elevator->currentFloor < b->elevator->targetFloor){
        //Si l'étage courant est inferieur de la destination on monte
           b->elevator->currentFloor=b->elevator->currentFloor+1;
        }
    }
}