//
//  linkedBinaryTree.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/21.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef linkedBinaryTree_hpp
#define linkedBinaryTree_hpp

#include "queue.hpp"
#include "exception.hpp"
#include "binaryTree.hpp"
#include "binaryTreeNode.hpp"
#include <iostream>

template<typename E>
class linkedBinaryTree : public binaryTree<binaryTreeNode<E>> {
public:
    linkedBinaryTree() {root = NULL; treeSize = 0; visit = NULL; count = 0;}
    ~linkedBinaryTree() {erase();}
    bool empty() const {return treeSize == 0;}
    int size() const {return treeSize;}
    E* rootElement() const;
    void makeTree(const E& elem, linkedBinaryTree<E>&, linkedBinaryTree<E>&);
    linkedBinaryTree<E>& removeLeftSubtree();
    linkedBinaryTree<E>& removeRightSubtree();
    
    void preOrder(void(*theVisit)(binaryTreeNode<E>*)) {visit = theVisit; preOrder(root);}
    void inOrder(void(*theVisit)(binaryTreeNode<E>*)) {visit = theVisit; inOrder(root);}
    void postOrder(void(theVisit)(binaryTreeNode<E>*)) {visit = theVisit; postOrder(root);}
    void levelOrder(void(*)(binaryTreeNode<E>*));
    
    void preOrderOutput() {preOrder(output); std::cout << std::endl;}
    void inOrderOutput() {inOrder(output); std::cout << std::endl;}
    void postOrderOutput() {postOrder(output); std::cout << std::endl;}
    void levelOrderOutput() {levelOrder(output); std::cout << std::endl;}
    
    void erase() {
        postOrder(dispose);
        root = NULL;
        treeSize = 0;
    }
    int height() const { return height(root);}
    
protected:
    binaryTreeNode<E> *root;
    int treeSize;
    static void (*visit)(binaryTreeNode<E>*);
    static int count;
    static void preOrder(binaryTreeNode<E>*);
    static void inOrder(binaryTreeNode<E>*);
    static void postOrder(binaryTreeNode<E>*);
    static void countNodes(binaryTreeNode<E>* t) {
        visit = addToCount;
        count = 0;
        preOrder(t);
    }
    static void dispose(binaryTreeNode<E>* t) {delete t;}
    static void output(binaryTreeNode<E>* t) { std::cout << t->elem << ' ';}
    static void addToCount(binaryTreeNode<E>* t) {count++;}
    static int height(binaryTreeNode<E>* t);
};

template<typename E>
E* linkedBinaryTree<E>::rootElement() const {
    if (treeSize == 0)
        return NULL;
    else
        return &root->elem;
}

template<typename E>
void linkedBinaryTree<E>::makeTree(const E& elem, linkedBinaryTree<E>& left, linkedBinaryTree<E>& right) {
    root = new binaryTreeNode<E>(elem, left.root, right.root);
    treeSize= left.treeSize + right.treeSize + 1;
    
    left.root = right.root = NULL;
    left.treeSize = right.treeSize = 0;
}

template<typename E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeLeftSubtree() {
    if (treeSize == 0)
        throw treeEmpty();
    
    linkedBinaryTree<E> leftSubtree;
    leftSubtree.root = root->left;
    count = 0;
    leftSubtree.treeSize = countNodes(leftSubtree.root);
    root->left = NULL;
    treeSize -= leftSubtree.treeSize;
    
    return leftSubtree;
}

template<typename E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeRightSubtree() {
    if (treeSize == 0)
        throw treeEmpty();
    
    linkedBinaryTree<E> rightSubtree;
    rightSubtree.root = root->right;
    count = 0;
    rightSubtree.treeSize = countNodes(rightSubtree.root);
    root->right = NULL;
    treeSize -= rightSubtree.treeSize;
    
    return rightSubtree;
}

template<typename E>
void linkedBinaryTree<E>::preOrder(binaryTreeNode<E>* t) {
    if (t != NULL) {
        linkedBinaryTree<E>::visit(t);
        preOrder(t->left);
        preOrder(t->right);
    }
}

template<typename E>
void linkedBinaryTree<E>::inOrder(binaryTreeNode<E>* t) {
    if (t != NULL) {
        inOrder(t->left);
        linkedBinaryTree<E>::visit(t);
        inOrder(t->right);
    }
}

template<typename E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E>* t) {
    if (t != NULL) {
        postOrder(t->left);
        postOrder(t->right);
        linkedBinaryTree<E>::visit(t);
    }
}

template<typename E>
void linkedBinaryTree<E>::levelOrder(void(*theVisit)(binaryTreeNode<E>*)) {
    arrayQueue<binaryTreeNode<E>*> q;
    binaryTreeNode<E>* t = root;
    while (t != NULL) {
        theVisit(t);
        if (t->left != NULL)
            q.push(t->left);
        if (t->right != NULL)
            q.push(t->right);
        
        try{t = q.front();}
        catch (queueEmpty) {return;}
        q.pop();
    }
}

template<typename E>
int linkedBinaryTree<E>::height(binaryTreeNode<E>* t) {
    if (t == NULL)
        return 0;
    int hl = height(t->left);
    int hr = height(t->right);
    if (hl > hr)
        return ++hl;
    else
        return ++hr;
}

#endif /* linkedBinaryTree_hpp */
