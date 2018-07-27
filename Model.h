#ifndef MODEL_H
#define MODEL_H
#include <iostream>
#include "Time.h"
#include "string"

using namespace std;

//Model Template inherited by both network and Machine
class Model {
    
   private:
      //none in template    
   public:
      //pure virtual functions
      virtual Time* getPreviousTime() =0;
      virtual string getModelType() =0;
      virtual void setModelType(string mName) =0;
      virtual double timeAdvance() =0;
      virtual void deltaInt() =0;
      virtual void deltaExt(double e, int q) =0;
      virtual void deltaCon(int q) =0;
      virtual int lambda() =0;
      virtual void newDelta(Model* in) =0;
      virtual void newLambda(Model* out) =0;
      
      //print to be changed in Machine 
      virtual void print(ostream& str) const{
          str << "Model Template";
      }
      
      friend ostream& operator<<(ostream& os, const Model& model){
          model.print(os);
          return os;
      }
};

#endif
