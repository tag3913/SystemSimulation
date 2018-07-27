#include "EventScheduler.h"
#include <iostream>
#include <string>
#include <vector>
#include "Model.h"
#include "Machine.h"
#include "Event.h"
#include "Time.h"
/*
int main(){
   /*
   EventScheduler<int> intScheduler;
   for(int i = 10; i > 0; i--){
      intScheduler.push(new int(i));   
   }
   
   vector<int*> heap = intScheduler.getHeap();
   cout << intScheduler.toString();
   cout << "Success";
   intScheduler.remove(heap[4]);
   cout << intScheduler.toString();
   

   Time* time = new Time(0.5, 0);
   Model* model = new Machine("Press", 1.0);
   Model* model2 = new Machine("Drill", 2.0);
   Time* time2 = new Time(0.8, 0);
   Event* newEvent = new Event(time, model, "External");
   Event* newEvent2 = new Event(time2, model2, "External");
   cout << "Success";
   

   return 0;      
}
*/