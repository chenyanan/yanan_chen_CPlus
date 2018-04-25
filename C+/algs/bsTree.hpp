//
//  bsTree.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/22.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef bsTree_hpp
#define bsTree_hpp

#include "dictionary.hpp"

template<typename K, typename E>
class bsTree : public dictionary<K,E> {
public:
    virtual void ascend() = 0;
};

#endif /* bsTree_hpp */
