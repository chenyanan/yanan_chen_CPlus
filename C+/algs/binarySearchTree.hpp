//
//  binarySearchTree.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/22.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef binarySearchTree_hpp
#define binarySearchTree_hpp

#include "bsTree.hpp"
#include "linkedBinaryTree.hpp"

template<typename K, typename E>
class binarySearchTree : public bsTree<K,E>, public linkedBinaryTree<std::pair<const K, E>> {
public:
    bool empty() const {return linkedBinaryTree<std::pair<const K, E>>::treeSize == 0;}
    int size() const {return linkedBinaryTree<std::pair<const K, E>>::treeSize;}
    std::pair<const K,E>* find(const K& theKey) const;
    void insert(const std::pair<const K,E>& thePair);
    void erase(const K& theKey);
    void ascend() {linkedBinaryTree<std::pair<const K, E>>::inOrderOutput();}
};

template<typename K, typename E>
std::pair<const K,E>* binarySearchTree<K,E>::find(const K& theKey) const {
    binaryTreeNode<std::pair<const K,E>>* p = linkedBinaryTree<std::pair<const K, E>>::root;
    while (p != NULL)
        if (theKey < p->elem.first)
            p = p->left;
        else
            if (theKey > p->elem.first)
                p = p->right;
            else
                return &p->elem;
    return NULL;
}

template<typename K, typename E>
void binarySearchTree<K,E>::insert(const std::pair<const K,E>& thePair) {
    binaryTreeNode<std::pair<const K,E>>* p = linkedBinaryTree<std::pair<const K, E>>::root, *pp = NULL;
    
    while (p != NULL) {
        pp = p;
        
        if (thePair.first < p->elem.first)
            p = p->left;
        else
            if (thePair.first > p->elem.first)
                p = p->right;
            else
            {
                p->elem.second = thePair.second;
                return;
            }
    }
    
    binaryTreeNode<std::pair<const K,E>>* newNode = new binaryTreeNode<std::pair<const K,E>>(thePair);
    if (linkedBinaryTree<std::pair<const K, E>>::root != NULL)
        if (thePair.first < pp->elem.first)
            pp->left = newNode;
        else
            pp->right = newNode;
    else
        linkedBinaryTree<std::pair<const K, E>>::root = newNode;
    linkedBinaryTree<std::pair<const K, E>>::treeSize++;
}

template<typename K, typename E>
void binarySearchTree<K,E>::erase(const K& theKey) {
    binaryTreeNode<std::pair<const K,E>>* p = linkedBinaryTree<std::pair<const K, E>>::root, *pp = NULL;
    
    while (p != NULL && p->elem.first != theKey) {
        pp = p;
        if (theKey < p->elem.first)
            p = p->left;
        else
            p = p->right;
    }
    
    if (p == NULL)
        return;
    
    if (p->left != NULL && p->right != NULL) {
        binaryTreeNode<std::pair<const K,E>>* s = p->left, *ps = p;
        
        while (s->right != NULL) {
            ps = s;
            s = s->right;
        }
        
        binaryTreeNode<std::pair<const K,E>>* q = new binaryTreeNode<std::pair<const K,E>>(s->elem, p->left, p->right);
        
        if (pp == NULL)
            linkedBinaryTree<std::pair<const K, E>>::root = q;
        else
            if (p == pp->left)
                pp->left = q;
            else
                pp->right = q;
        
        if (ps == p) pp = q;
        else pp = ps;
        
        delete p;
        p = s;
    }
    
    binaryTreeNode<std::pair<const K,E>>* c;
    if (p->left != NULL)
        c = p->left;
    else
        c = p->right;
    
    if (p == linkedBinaryTree<std::pair<const K,E>>::root)
        linkedBinaryTree<std::pair<const K,E>>::root = c;
    else {
        if (p == pp->left)
            pp->left = c;
        else
            pp->right = c;
    }
    
    --linkedBinaryTree<std::pair<const K,E>>::treeSize;
    delete p;
}

#endif /* binarySearchTree_hpp */
