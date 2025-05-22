#include "Stack.h"
#include <iostream>
using namespace std;
// Constructor to initialize an empty stack
Stack::Stack() {
    this->top=-1;
}

// Adds a province to the top of the stack
void Stack::push(int province) {
     if(this->top==MAX_SIZE-1){
        cerr<<"Error: Stack overflow. Cannot push more elements."<<endl;
        return;
    }

    this->top++;
    this->data[this->top]=province;

}

// Removes and returns the top province from the stack
int Stack::pop() {
    if(this->isEmpty()){
         cerr << "Error: Stack underflow. Cannot pop elements from an empty stack." << endl;
        return -1;
    }
    return this->data[this->top--];
}

// Returns the top province without removing it
int Stack::peek() const {
    if(this->isEmpty()){
        cerr<<"Error: Stack is empty. Cannot peek."<<endl;
        return -1;
    }

    return this->data[this->top];
    
}

// Checks if the stack is empty
bool Stack::isEmpty() const {
    return this->top == -1;
    
}

// Function to get the current size of the stack
int Stack::getSize() const {

    return ((this->top)+1);
}
