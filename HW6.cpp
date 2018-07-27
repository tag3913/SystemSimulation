#include "EventScheduler.h"
#include "Machine.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void check(EventScheduler<Event> es);


/*  Machine Process Simulator
 *  Thomas Glenister
 *
 *  Generates Events based on the input file which 
 *  provides a point in time and the number of parts
 *  provided at that time. The two machines (press and drill)
 *  perform a action on that part and push the part to 
 *  the next model in line.
 *  The output gives a rundown of each action performed during the
 *  process, and shows the events being run, being created, and to be run.
 */
int main(){
   //get input file
   ifstream inFile;
   inFile.open("/home/thom/c++/454/454HW6/inputs.txt");
 
   //check to see if file is opened
   if(!inFile){
      cerr << "Unable to open input File";
      return 1;
   }
   
   //create scheduler and Machines
   static EventScheduler<Event> es;
   Model* press = new Machine("Press", 1.0);
   Model* drill = new Machine("Drill", 2.0);
   
   //set global scheduler and time for all machines in the network
   Machine::setScheduler(&es);
   Time* mTime = new Time();
   Machine::setTime(mTime);
   
   //create network and set connections between it and machines present inside
   Network* network = Network::builder()->addModel(press)->addModel(drill)->addDelta(press)->addLambda(drill)->build();
   network->inOut(press, drill);
   press->newDelta(network);
   drill->newLambda(network);
   
   //variables to gather info from file
   double previousTime = 0;
   int quantity;
   double time;
   //while the input file has next line
   while(!inFile.eof()){
      inFile >> time;
      inFile >> quantity;
      
      double elapsed = time - previousTime;
      previousTime = time;
      
      //for each delta model in the network 
      for(Model* m: network->getDeltas()){
          //create new external event and push onto heap
          Time* eventTime = new Time(time, 0);
          Event* newEvent = new Event(eventTime, m, "External");
          newEvent->setQuantity(quantity);
          newEvent->setElapsed(elapsed);
          es.push(newEvent);
      }
      
   }
   //print events
   cout << "Events:\n";
   es.toString();
   
   //while the scheduler has events to be executed
   while(!es.isEmpty()){
       check(es);    //see if new confluent event is present
       cout << "TIME: " << Machine::getTime()->getReal() << " | ";   //print current machine time
       Event* nextEvent = es.poll();   //gather next event
       
       //adjust machine time
       double changeInTime = nextEvent->getTime()->getReal() - Machine::getTime()->getReal();
       Time* machineTime = new Time(Machine::getTime()->getReal() + changeInTime, 0);
       Machine::setTime(machineTime);
       
       //for each model in the network
       for(Model* m : network->getModels()){
           //if the events model matches networks model
           if(nextEvent->getModel() == m){
               
               if(m->getPreviousTime()->getReal() == 0){
                   nextEvent->setElapsed(0);
               }
               else{
                   nextEvent->setElapsed(Machine::getTime()->getReal() - m->getPreviousTime()->getReal());
               }
               
               //execute whatever the next event is depending on delta action
               if(nextEvent->getDelta().compare("Internal") == 0){
                   m->deltaInt();
               }
               else if(nextEvent->getDelta().compare("External") == 0){
                   m->deltaExt(nextEvent->getElapsed(), nextEvent->getQuantity());
               }
               else if(nextEvent->getDelta().compare("Confluent") == 0){
                   m->deltaCon(nextEvent->getQuantity());
               }
               else{
                   //doesn't happen as every event must have one of three delta actions
                   cout << "This should not happen";
               }//end if
               cout << "Executing " << *nextEvent << endl;
           }//end if
       }//end for 
       delete(nextEvent); //delete completed event
       
       //print out list of events in the heap
       cout << "Events:\n";
       es.toString();
   }

   return 0;      
}

//checks to see if confluent event needs to be created
void check(EventScheduler<Event> es){
    //function variables
    int quantity;   
    
    //for each event in the heap
    for(Event* e : es.getHeap()){
        if(e != NULL && e != es.peek()){
            if(es.peek()->getTime() == e->getTime()){
                Event first = *es.peek();
                
                if(first.getQuantity() != 0){
                    quantity = first.getQuantity();
                }
                else if(e->getQuantity() != 0){
                    quantity = e->getQuantity();
                }
                //remove both events
                es.remove(e);
                es.remove(es.peek());
                //create new confluent event and push to heap
                Event* newEvent = new Event(first.getTime(), first.getModel(), "Confluent");
                newEvent->setQuantity(quantity);
                es.push(newEvent);
            }
        }
    }
}
