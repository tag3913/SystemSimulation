#include "Network.h"
#include <iostream>
#include <vector>
#include "Model.h"

using namespace std;

Network::Network(NetworkBuilder* build){
   deltas = build->deltas;
   lambdas = build->lambdas;
   models = build->models;
}

void Network::inOut(Model* in, Model* out){
   in->newLambda(out);
   out->newDelta(in);
}
  
vector<Model*> Network::getDeltas(){
   return deltas;
}

vector<Model*> Network::getLambdas(){
   return lambdas;
}

vector<Model*> Network::getModels(){
   return models;
}

Network::NetworkBuilder* Network::NetworkBuilder::addModel(Model* m){
   this->models.push_back(m);
   return this;
}

Network::NetworkBuilder* Network::NetworkBuilder::addDelta(Model* m){
   this->deltas.push_back(m);
   return this;
}

Network::NetworkBuilder* Network::NetworkBuilder::addLambda(Model* m){
   this->lambdas.push_back(m);
   return this;
}

Network* Network::NetworkBuilder::build(){
   return new Network(this);
}

string Network::getModelType(){
    return "Network";
}

Network::NetworkBuilder* Network::builder(){
    return new NetworkBuilder();
}




