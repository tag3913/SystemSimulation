#include "Event.h"
#include <string>
#include <sstream>

using namespace std;

Event::Event(Time* newTime, Model* m, string d){
   time = newTime;
   model = m;
   delta = d;
}

Time* Event::getTime(){
   return time;
}

Model* Event::getModel(){
   return model;
}

string Event::getDelta(){
   return delta;
}

//greater than overload for heap insertion/removal
bool Event::operator> (Event &e){
   if(time->getReal() > e.getTime()->getReal()){
      return 1;
   }
   else
      return 0;
}

std::ostream& operator<<(std::ostream& os, const Event& event){
      os << "\t(Delta: " << event.delta << " Time: " << event.time->getReal() << " " << *event.model << " Q: " << event.quantity << " E: " << event.elapsedTime << ")";
      return os;
}

/*
 * not needed
string Event::toString(){
   ostringstream oss;
   oss <<  "\t(Delta: " << delta << " Time: " << time->getReal() << " " << model  << " Q: " << quantity << " E: " << elapsedTime << ")";
   return oss.str();
}
 */


//getters and setters for quantity and elapsed time
int Event::getQuantity(){
   return quantity;
}

double Event::getElapsed(){
   return elapsedTime;
}

void Event::setQuantity(int q){
   quantity = q;
}

void Event::setElapsed(double e){
   elapsedTime = e;
}


