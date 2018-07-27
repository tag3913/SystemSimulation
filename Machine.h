#ifndef MACHINE_H
#define MACHINE_H
#include <string>
#include <vector>
#include "EventScheduler.h"
#include "Model.h"
#include "Time.h"
#include "Event.h"
#include "Network.h"

using namespace std;

class Machine : public Model{
   private: 
      string type;
      double timeToComplete;
      const double INF = 9999;   
      int finishedParts = 0;

      //model lists
      vector<Model*> deltas;
      vector<Model*> lambdas;

      Time* previousTime = new Time();
   public:
       
      string name;  //name of machine
      int partsNum; //parts waiting to be processed
      double processTime;  //time to process a part
      
      //public time and scheduler for all machines
      static Time* currentTime;
      static EventScheduler<Event>* es;
      
      //constructor for new machine gives name and process time to complete work on a part
      Machine(string machineName, double t){
         timeToComplete = t;
         name = machineName;
         processTime = 0;
         partsNum = 0;
      }
      double timeAdvance();
      void deltaInt();
      void deltaExt(double elapsedTime, int newParts);
      void deltaCon(int newParts);
      int lambda();
      
      //get the current time the machine has been active
      static void setTime(Time* t);
      static Time* getTime();
      
      Time* getPreviousTime(){
         return previousTime;
      }
      
      //sets the scheduler for all active machines
      static void setScheduler(EventScheduler<Event>* e);
      
      //print definition for machines 
      virtual void print(ostream& str) const{
          str << "Machine:" << name << " P:" << partsNum << " S:" << processTime;
      }
      
      //adds input/output model to lists
      void newLambda(Model* m);
      void newDelta(Model* m);
      
      //save myself from using typeid
      string getModelType(){
          return "Machine";
      }
      void setModelType(string mName){
          type = mName;
      }
};

#endif
