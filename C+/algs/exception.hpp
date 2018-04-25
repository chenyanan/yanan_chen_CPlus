//
//  exception.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/19.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef exception_hpp
#define exception_hpp

#include <stdio.h>
#include <string>
#include <iostream>

class illegalParameterValue {
public:
    illegalParameterValue(std::string theMessage = "Illegal parameter value") {message = theMessage;}
    void outputMessage() {std::cout << message << std::endl;}
private:
    std::string message;
};

class illegalInputData {
public:
    illegalInputData(std::string theMessage = "Illegal data input") {message = theMessage;}
    void outputMessage() {std::cout << message << std::endl;}
private:
    std::string message;
};

class illegalIndex {
public:
    illegalIndex(std::string theMessage = "Illegal index") {message = theMessage;}
    void outputMessage() {std::cout << message << std::endl;}
private:
    std::string message;
};

class matrixIndexOutOfBounds {
public:
    matrixIndexOutOfBounds(std::string theMessage = "Matrix index out of bounds") {message = theMessage;}
    void outputMessage() {std::cout << message << std::endl;}
private:
    std::string message;
};

class matrixSizeMismatch {
public:
    matrixSizeMismatch(std::string theMessage = "The size of the two matrics doesn't match") {message = theMessage;}
    void outputMessage() {std::cout << message << std::endl;}
private:
    std::string message;
};

class stackEmpty {
public:
    stackEmpty(std::string theMessage = "Invalid operation on empty stack") {message = theMessage;}
    void outputMessage() {std::cout << message << std::endl;}
private:
    std::string message;
};

class queueEmpty {
public:
    queueEmpty(std::string theMessage = "Invalid operation on empty queue") {message = theMessage;}
    void outputMessage() {std::cout << message << std::endl;}
private:
    std::string message;
};

class treeEmpty {
public:
    treeEmpty(std::string theMessage = "Invalid operation on empty tree") {message = theMessage;}
private:
    std::string message;
};

class hashTableFull {
public:
    hashTableFull(std::string theMessage = "The hash table is full") {message = theMessage;}
    void outputMessage() {std::cout << message << std::endl;}
private:
    std::string message;
};

class undefinedEdgeWeight {
public:
    undefinedEdgeWeight(std::string theMessage = "No edge weights defined") {message = theMessage;}
    void outputMessage() {std::cout << message << std::endl;}
private:
    std::string message;
};

class undefinedMethod {
public:
    undefinedMethod(std::string theMessage = "This method is undefined") {message = theMessage;}
    void outputMessage() {std::cout << message << std::endl;}
private:
    std::string message;
};



#endif /* exception_hpp */
