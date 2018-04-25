//
//  dictionary.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/20.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef dictionary_hpp
#define dictionary_hpp

template<typename K, typename E>
class dictionary {
public:
    virtual ~dictionary() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual std::pair<const K, E>* find(const K&) const = 0;
    virtual void erase(const K&) = 0;
    virtual void insert(const std::pair<const K, E>&) = 0;
};

#endif /* dictionary_hpp */
