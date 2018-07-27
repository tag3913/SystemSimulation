#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <iostream>
#include "Model.h"
#include "Time.h"

using namespace std;

//Event Class which represents an action in the simulations world
class Event{
   private:
      Time* time;        //time which event occurs
      Model* model;      //model in the process that is taking action
      string delta;      //action being performed
      int quantity;      //parts added in event
      double elapsedTime;//time since last event 
   public:
      //constructor takes time model and delta operation
      Event(Time* newTime, Model* m, string d);
      
      //overloaded greater than operator to use binary heap
      bool operator>(Event &e);
      
      //overloaded equality operator to compare events
      bool operator==(Event &e);
      
      //overloaded text output
      friend ostream& operator<<(ostream& os, const Event& event);  
      
      
      string getDelta();    //returns delta operation (internal, external, confluent)
      Model* getModel();    //return model
      Time* getTime();      //return time
      //string toString();  
      
      //getters / setters
      void setQuantity(int q);
      void setElapsed(double e);
      int getQuantity();
      double getElapsed();
};

#endif
