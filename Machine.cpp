#include "Machine.h"
#include "EventScheduler.h"
#include <string>
#include <iostream>
#include <stdio.h>

using namespace std;

//initialize Machine Time and Scheduler
Time* Machine::currentTime = new Time();
EventScheduler<Event>* Machine::es = new EventScheduler<Event>();

//time advance function, infinity if no parts waiting 
double Machine::timeAdvance(){
   if(partsNum > 0){
      return processTime;
   }
   else{
      return INF;
   }
}

//Delta internal function 
void Machine::deltaInt(){
   previousTime = currentTime;
   partsNum--;
   processTime = timeToComplete;
   for(Model* m : lambdas){
      //if model is an instance of network
      if(m->getModelType().compare("Network") == 0){
         //then part is finished
         finishedParts = finishedParts + 1;
         cout << "Parts Completed: " << finishedParts << endl;
      }
      else{
         //else create a new External function event for each output machine
         Time* eventTime = new Time(currentTime->getReal(), 0);
         Event* event = new Event(eventTime, m, "External");
         event->setQuantity(lambda());
         es->push(event);
      }
   }
   //if Machine still has parts to be processed
   if(partsNum > 0){
      //create new internal event to process next part
      Time* eventTime = new Time(currentTime->getReal() + timeAdvance(), 0);
      Event* event = new Event(eventTime, this, "Internal");
      es->push(event);
   }
}

//Delta External Function
void Machine::deltaExt(double elapsedTime, int newParts){
   previousTime = currentTime;
   Event* newEvent = NULL;
   if(partsNum > 0){
      partsNum += newParts;
      processTime = processTime - elapsedTime;
      
      for(Event* e : es->getHeap()){
         if(e != NULL && e->getModel() == this && e->getDelta() == "Internal"){
            if(es->remove(e)){
               Time* eventTime = new Time(currentTime->getReal() + timeAdvance(), 0);
               newEvent = new Event(eventTime, this, "Internal");
            }
         }
      }
   }
   else{
      partsNum += newParts;
      processTime = timeToComplete;
      Time* eventTime = new Time(currentTime->getReal() + timeToComplete, 0);
      newEvent = new Event(eventTime, this, "Internal");
   }
   es->push(newEvent);
}

//delta confluent function
void Machine::deltaCon(int newParts){
    
    previousTime = currentTime;
    processTime = timeToComplete;
    partsNum += (newParts - 1);

    Time* eventTime = new Time(currentTime->getReal() + timeAdvance(), 0);
    Event* newEvent = new Event(eventTime, this, "Internal");
    es->push(newEvent);

    for(Model* m : lambdas){
        if(m->getModelType().compare("Network") == 0){
           finishedParts = finishedParts + 1;
           cout << "Parts Completed: " << finishedParts << endl;
        }
        else{
           Time* nextEventTime = new Time(currentTime->getReal(), 0);
           newEvent = new Event(nextEventTime, m, "Internal");
           newEvent->setQuantity(lambda());
           es->push(newEvent);
        }
    }
}


//Machine always returns one finished part
int Machine::lambda(){
   return 1;
}

//set and get global time for machines
void Machine::setTime(Time* t){
   currentTime = t;
}

Time* Machine::getTime(){
   return currentTime;
}

//set global Scheduler for machines
void Machine::setScheduler(EventScheduler<Event>* e){
   es = e;
}

//add a new input or output Model for this particular machine
void Machine::newLambda(Model* m){
   lambdas.push_back(m);
}

void Machine::newDelta(Model* m){
   deltas.push_back(m);
}





