#include "Queue.h"
#include <iostream>
using namespace std;
// Constructor to initialize an empty queue
Queue::Queue() {
    this->rear=-1;
    this->front=-1;
}

// Adds a province to the end of the queue
void Queue::enqueue(int province) {
    if(this->front==((this->rear+1)%MAX_QUEUE_SIZE)){
        
        return;
    }
    this->rear=(this->rear+1)%MAX_QUEUE_SIZE;
    if(this->front==-1){
        this->front=0;
    }
    this->data[this->rear]=province;
}

// Removes and returns the front province from the queue
int Queue::dequeue() {
    if(this->front==-1){
        
        return -1;     
    }
    if(this->front==this->rear){
        int temp=this->data[this->front];
        this->front=this->rear=-1;
        return temp;
    }
    int dequeue_elemant=this->data[this->front];
    this->front=(this->front+1)%MAX_QUEUE_SIZE;
    return dequeue_elemant;
    
}

// Returns the front province without removing it
int Queue::peek() const {
    if(this->isEmpty()){
        
        return -1;
    }
    else{
        return this->data[this->front];
    }
}

// Checks if the queue is empty
bool Queue::isEmpty() const {
    return this->front==-1;
}

// Add a priority neighboring province in a way that will be dequeued and explored before other non-priority neighbors
void Queue::enqueuePriority(int province) {
    if(this->front == (this->rear + 1) % MAX_QUEUE_SIZE){

        return;
    }
    if(this->isEmpty()){
        this->enqueue(province);
    }
    else{
        this->rear=(this->rear+1)%MAX_QUEUE_SIZE;
        int i=this->rear;
        while(i!=this->front){
            int prevIndex=(i-1+MAX_QUEUE_SIZE)%MAX_QUEUE_SIZE;
            this->data[i]=this->data[prevIndex];
            i=prevIndex;
        }
        this->data[this->front]=province;
        
    }
}


