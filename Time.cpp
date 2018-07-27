#include "Time.h"

using namespace std;

Time::Time() : 
   real(0),
   discrete(0)
{ 

}

Time::Time(double realParam, double discreteParam) :
   real(realParam),
   discrete(discreteParam)
{

}

double Time::getReal(){
   return real;
}

double Time::getDiscrete(){
   return discrete;
}

void Time::setReal(double realParam){
   real = realParam;
}

void Time::setDiscrete(double discreteParam){
   discrete = discreteParam;
}

void Time::incrementReal(double elapsed){
   real += elapsed;
}


void Time::incrementDiscrete(double elapsed){
   discrete += elapsed;
}


