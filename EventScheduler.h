#ifndef EVENTSCHEDULER_H
#define EVENTSCHEDULER_H
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

//generic min binary heap to store events of the simulation
template <class T>
class EventScheduler{
   private:
      vector<T*> heap;
      void percUp();
      void percDown(int s);
      bool greaterThan(int first, int second);
      void swap(int first, int second);
      
   public:
      EventScheduler();
      void push(T* newT);
      T* peek();
      bool remove(T* value);
      T* poll();
      
      bool isEmpty();
      vector<T*> getHeap();
      void toString();
};

//constructor
template <class T>
EventScheduler<T>::EventScheduler(){
   //set the first value of the vector to Null 
   heap.push_back(NULL);
}

//heap insertion of new event
template <class T>
void EventScheduler<T>::push(T* newT){

   //push the new value onto the heap and check 
   heap.push_back(newT);
   percUp();
}

//bubble up method
template <class T>
void EventScheduler<T>::percUp(){
   int s = heap.size() - 1;         //get number of elements in heap 
   //while parent is greater than child and more than one element in heap
   while(s > 1 && greaterThan(s/2, s)){    
      //bubble up in heap 
      swap(s, s/2);
      s = s/2;
   }
}

//check for seeing if element in first position is greater than the one in second
template <class T>
bool EventScheduler<T>::greaterThan(int first, int second){
    return *heap[first] > *heap[second];
}

//if the vector contains any element beside initial null value
template <class T>
bool EventScheduler<T>::isEmpty(){
   return(heap.size() == 1);
}

//peak at first element in heap
template <class T>
T* EventScheduler<T>::peek(){
   if(!isEmpty()){
      return heap[1];
   }
   else{
      return NULL;
   }
}


//swaps the pointers in the vector of input positions
template <class T>
void EventScheduler<T>::swap(int first, int second){
   T* temp = heap[first];
   heap[first] = heap[second];
   heap[second] = temp;
}

//bubble down method 
template <class T>
void EventScheduler<T>::percDown(int s){
   while((s * 2) < heap.size()){
        int p = s * 2;
        if(!(p + 1 == heap.size())){
            if(greaterThan(p, p + 1)){
                p++;
            }
        }
        if(!(greaterThan(s, p))){
            break;
        }
        swap(s , p);
        s = p;
   }
}

//removes specified T pointer from the heap
template <class T>
bool EventScheduler<T>::remove(T* e){
   if(e != NULL){
      for(int i = 1; i < heap.size(); i++){
         if(heap[i] == e){
            swap(i, (heap.size() - 1));
            heap.pop_back();
            percDown(i);
            delete e;
            return 1;
            
         }
      }
      
   }   
   return 0;
}

//return and remove first element of heap
template <class T>
T* EventScheduler<T>::poll(){
    if(isEmpty()){
        return NULL;
    }
    T* result = peek();
    swap(1, heap.size() - 1);
    heap[heap.size() - 1] = NULL;
    
    heap.resize(heap.size() - 1);
    percDown(1);
    return result;
}

template <class T>
void EventScheduler<T>::toString(){
   string returnString = "";
   for(int i = 0; i < heap.size(); i++){
      if(heap[i]){ 
         cout << *heap[i] << "\n";
      }
   }
}

template <class T>
vector<T*> EventScheduler<T>::getHeap(){
   return heap;
}


#endif
