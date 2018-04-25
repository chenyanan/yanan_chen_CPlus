//
//  queue.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/19.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef queue_hpp
#define queue_hpp

#include "chain.hpp"
#include "exception.hpp"
#include "arrayList.hpp"


template<class T>
class queue
{
public:
    virtual ~queue() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& front() = 0;
    virtual T& back() = 0;
    virtual void pop() = 0;
    virtual void push(const T& theElement) = 0;
};

template<class T>
class arrayQueue : public queue<T>
{
public:
    arrayQueue(int initialCapacity = 10);
    ~arrayQueue() {delete [] queue;}
    bool empty() const {return theFront == theBack;}
    int size() const {return (theBack - theFront + arrayLength) % arrayLength;}
    T& front()
    {
        if (theFront == theBack)
            throw queueEmpty();
        return queue[(theFront + 1) % arrayLength];
    }
    T& back()
    {
        if (theFront == theBack)
            throw queueEmpty();
        return queue[theBack];
    }
    void pop()
    {
        if (theFront == theBack)
            throw queueEmpty();
        theFront = (theFront + 1) % arrayLength;
        queue[theFront].~T();
    }
    void push(const T& theElement);
private:
    int theFront;
    int theBack;
    int arrayLength;
    T *queue;
};

template<typename T>
arrayQueue<T>::arrayQueue(int initialCapacity) {
    if (initialCapacity) {
        std::string s = "Initial capacity = " + std::string(1, initialCapacity) + " Must be > 0";
        throw illegalParameterValue(s);
    }
    arrayLength = initialCapacity;
    queue = new T[arrayLength];
    theFront = 0;
    theBack = 0;
}

template<typename T>
void arrayQueue<T>::push(const T& theElement) {
    if ((theBack + 1) % arrayLength == theFront) {
        T *newQueue = new T[2 * arrayLength];
        
        int start = (theFront + 1) % arrayLength;
        if (start < 2)
            std::copy(queue + start, queue + start + arrayLength - 1, newQueue);
        else {
            std::copy(queue + start, queue + arrayLength, newQueue);
            std::copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
        }
        theFront = 2 * arrayLength - 1;
        theBack = arrayLength - 2;
        arrayLength *= 2;
        queue = newQueue;
    }
    
    theBack = (theBack + 1) % arrayLength;
    queue[theBack] = theElement;
}

template<typename T>
class linkedQueue : public queue<T> {
public:
    linkedQueue(int initialCapacity = 10) {queueFront = NULL; queueSize = 0;}
    ~linkedQueue();
    bool empty() const {return queueSize==0;}
    int size() const {return queueSize;}
    T& front() {
        if (queueSize == 0)
            throw queueEmpty();
        return queueFront->element;
    }
    T& back() {
        if (queueSize == 0)
            throw queueEmpty();
        return queueBack->element;
    }
    void pop();
    void push(const T&);
private:
    chainNode<T>* queueFront;
    chainNode<T>* queueBack;
    int queueSize;
};

template<typename T>
linkedQueue<T>::~linkedQueue() {
    while (queueFront != NULL) {
        chainNode<T>* nextNode = queueFront->next;
        delete queueFront;
        queueFront = nextNode;
    }
}

template<typename T>
void linkedQueue<T>::pop() {
    if (queueFront == NULL)
        throw queueEmpty();
    
    chainNode<T>* nextNode = queueFront->next;
    delete queueFront;
    queueFront = nextNode;
    queueSize--;
}

template<typename T>
void linkedQueue<T>::push(const T& theElement) {
    chainNode<T>* newNode = new chainNode<T>(theElement, NULL);
    
    if (queueSize == 0)
        queueFront = newNode;
    else
        queueBack->next = newNode;
    queueBack = newNode;
    queueSize++;
}

#endif /* queue_hpp */
