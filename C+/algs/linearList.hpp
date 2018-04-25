//
//  linearList.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/17.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef linearList_hpp
#define linearList_hpp

template<typename T>
class linearList {
public:
    virtual ~linearList() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& get(int theIndex) const = 0;
    virtual int indexOf(const T& theElement) const = 0;
    virtual void erase(int theIndex) = 0;
    virtual void insert(int theIndex, const T& theElement) = 0;
};


#endif /* linearList_hpp */
