// Stack class used to hold stuff suchg as function calls e.t.c.
#ifndef STACK_H_
#define STACK_H_

#include "stackFrame.h"
#include <vector>

class Stack {
public:
    
    Stack(unsigned int size) {
      this->stack =
    }

    bool push(StackFrame sf) {
        
    }


    StackFrame pop() {
        
    }

    StackFrame peek() {

    }

private:
    std::vector<StackFrame> stack;
    int _size, _sp;

};


#endif