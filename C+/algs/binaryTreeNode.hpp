//
//  binaryTreeNode.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/21.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef binaryTreeNode_hpp
#define binaryTreeNode_hpp

template<typename T>
struct binaryTreeNode {
    T elem;
    binaryTreeNode<T> *left, *right;
    
    binaryTreeNode() {left = right = NULL;}
    binaryTreeNode(const T& theElem) : elem(theElem) {
        left = right = NULL;
    }
    binaryTreeNode(const T& theElem,
                   binaryTreeNode<T> *theLeft,
                   binaryTreeNode<T> *theRight) : elem(theElem) {
        left = theLeft;
        right = theRight;
    }
};

#endif /* binaryTreeNode_hpp */
