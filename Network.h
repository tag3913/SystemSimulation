#ifndef NETWORK_H
#define NETWORK_H
#include "Model.h"
#include <vector>

using namespace std;


//Network may contain machines and sub-networks
class Network : public Model{
   private:
      vector<Model*> deltas;
      vector<Model*> lambdas;
      vector<Model*> models;
   public:
      class NetworkBuilder{
         private:

         public:
            //lists of models and inputs/outputs
            vector<Model*> models;
            vector<Model*> deltas;
            vector<Model*> lambdas;
            
            //add model methods
            NetworkBuilder* addModel(Model* m);
            NetworkBuilder* addDelta(Model* m);
            NetworkBuilder* addLambda(Model* m);
            
            //builder function
            Network* build();
      };

      static NetworkBuilder* builder();   //returns network builder to build new network
      void setModelType(string mName){}   
      string getModelType(); 
      Network(NetworkBuilder* build);
      void inOut(Model* in, Model* out);  //sets connection between models in network (press to drill)
      
      //returns model lists
      vector<Model*> getDeltas();
      vector<Model*> getLambdas();
      vector<Model*> getModels();
      
      //included to inherit model could potentially be implemented to have sub-network perform machine 
      //functions or process times
      Time* getPreviousTime(){return new Time();}
      double timeAdvance(){return 0;};
      void deltaInt(){}
      void deltaExt(double e, int q){}
      void deltaCon(int q){}
      int lambda(){return 0;}
      void newDelta(Model* in){}
      void newLambda(Model* out){}
};

#endif
