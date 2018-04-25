//
//  binaryTree.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/21.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef binaryTree_hpp
#define binaryTree_hpp

template<typename T>
class binaryTree {
public:
    virtual ~binaryTree() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual void preOrder(void(*)(T *)) = 0;
    virtual void inOrder(void(*)(T *)) = 0;
    virtual void postOrder(void(*)(T *)) = 0;
    virtual void levelOrder(void(*)(T *)) = 0;
};

#endif /* binaryTree_hpp */
