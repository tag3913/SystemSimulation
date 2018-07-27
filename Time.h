#ifndef TIME_H
#define TIME_H

using namespace std;

class Time{
   private:
      double real;       
      double discrete;
      
   public:
      Time();
      Time(double realParam, double discreteParam);
      double getReal();
      double getDiscrete();
      void setReal(double realParam);
      void setDiscrete(double discreteParam);
      void incrementReal(double elapsed);
      void incrementDiscrete(double elapsed);
};

#endif
