//
//  changeLength1D.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/20.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef changeLength1D_hpp
#define changeLength1D_hpp

#include "exception.hpp"

template<typename T>
void changeLength1D(T*& a, int oldLength, int newLength) {
    if (newLength < 0)
        throw illegalParameterValue("new length must be >= 0");
    
    T* temp = new T[newLength];
    int number = std::min(oldLength, newLength);
    std::copy(a, a + number, temp);
    delete[] a;
    a = temp;
}


#endif /* changeLength1D_hpp */
