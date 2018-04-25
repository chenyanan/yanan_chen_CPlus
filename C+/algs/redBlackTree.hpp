//
//  redBlackTree.hpp
//  C+
//
//  Created by chenyanan on 2017/3/17.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef redBlackTree_hpp
#define redBlackTree_hpp

enum RBT_IST : int {
    RBT_LLb             =   1,  //00000001
    RBT_LLr             =   2,  //00000010
    RBT_LRb             =   4,  //00000100
    RBT_LRr             =   8,  //00001000
    RBT_RRb             =  16,  //00010000
    RBT_RRr             =  32,  //00100000
    RBT_RLb             =  64,  //01000000
    RBT_RLr             = 128,  //10000000
    RBT_LLr_LRr         =  10,  //00001010
    RBT_LLb_RRb         =  17,  //00010001
    RBT_LLr_LRr_RRr_RLr = 170   //10101010
};

enum RBT_ERS : int {
    RBT_Rb0 = 1,  //00000000000001
    RBT_Rb1 = 2,  //00000000000010
    RBT_Rb2 = 4,  //00000000000100
    RBT_Lb0 = 8,  //00000000001000
    RBT_Lb1 = 16,  //00000000010000
    RBT_Lb2 = 32,  //00000000100000
    RBT_Rr0 = 64,  //00000001000000
    RBT_Rr1 = 128,  //00000010000000
    RBT_Rr11 = 256,  //00000100000000
    RBT_Rr2 = 1024,  //00001000000000
    RBT_Lr0 = 2048,  //00010000000000
    RBT_Lr1 = 4096,  //00100000000000
    RBT_Lr11 = 8192,  //01000000000000
    RBT_Lr2 = 16384,  //10000000000000
    RBT_Lb0_Rb0 = 72,  //00000001001000
    RBT_Lb1_Lb2_Rb1_Rb2 = 54  //00000000110110
};

enum rbColor : char {
    rbRed = 'r',
    rbBlack = 'b'
};

template<typename K, typename E>
struct rbNode {
    std::pair<const K,E> pair;
    rbColor color;
    
    rbNode(const std::pair<const K,E>& thePair) : pair(thePair) {};
    rbNode(const std::pair<const K,E>& thePair, rbColor theColor) : pair(thePair) {color = theColor;}
    rbNode(const K& theKey, const E& theValue, rbColor theColor) : pair(theKey, theValue) {color = theColor;}
};

template<typename K, typename E>
class redBlackTree : public bsTree<K,E>, public linkedBinaryTree<rbNode<K,E>> {
public:
    bool empty() const {return linkedBinaryTree<rbNode<K, E>>::treeSize == 0;}
    int size() const {return linkedBinaryTree<rbNode<K, E>>::treeSize;}
    std::pair<const K,E>* find(const K& theKey) const {
        binaryTreeNode<rbNode<K,E>> *p = linkedBinaryTree<rbNode<K,E>>::root;
        
        while (p != NULL) {
            if (p->elem.pair.first < theKey)
                p = p->right;
            else
                if (p->elem.pair.first > theKey)
                    p = p->left;
                else
                    return &p->elem.pair;
        }
        
        return NULL;
    }
    
    void insert(const std::pair<const K,E>& thePair) {
        
        int height = (int)ceil(logf((float)linkedBinaryTree<rbNode<K, E>>::treeSize + 1.0f) / logf(2.0f) * 2.0f), length = 0;
        
        binaryTreeNode<rbNode<K,E>>* nodes[height];
        binaryTreeNode<rbNode<K,E>> *p = linkedBinaryTree<rbNode<K,E>>::root, *pp = NULL;
        
        while (p != NULL) {
            
            pp = p;
            
            if (p->elem.pair.first > thePair.first)
                p = p->left;
            else
                if (p->elem.pair.first < thePair.first)
                    p = p->right;
                else {
                    p->elem.pair.second = thePair.second;
                    return;
                }

            nodes[length] = pp;
            ++length;
        }
        
        binaryTreeNode<rbNode<K,E>> *newNode = new binaryTreeNode<rbNode<K,E>>(rbNode<K, E>(thePair, rbRed));
        
        if (pp == NULL) {
            newNode->elem.color = rbBlack;
            linkedBinaryTree<rbNode<K,E>>::root = newNode;
        } else
            if (pp->elem.pair.first > thePair.first)
                pp->left = newNode;
            else
                pp->right = newNode;
        ++linkedBinaryTree<rbNode<K,E>>::treeSize;
        
        nodes[length] = newNode;
        ++length;
        
        if (length < 3)
            return;
        
        for (int i = length - 1; i > 1; i -= 2) {
            
            if (nodes[i - 1]->elem.color == rbBlack)
                return;
            
            RBT_IST type;
            binaryTreeNode<rbNode<K,E>> *u = nodes[i], *pu = nodes[i - 1], *gu = nodes[i - 2];

            if (pu == gu->left)
                if (u == pu->left)
                    if (gu->right == NULL || gu->right->elem.color == rbBlack)
                        type = RBT_LLb;
                    else
                        type = RBT_LLr;
                else
                    if (gu->right == NULL || gu->right->elem.color == rbBlack)
                        type = RBT_LRb;
                    else
                        type = RBT_LRr;
            else
                if (u == pu->left)
                    if (gu->left == NULL || gu->left->elem.color == rbBlack)
                        type = RBT_RLb;
                    else
                        type = RBT_RLr;
                else
                    if (gu->left == NULL || gu->left->elem.color == rbBlack)
                        type = RBT_RRb;
                    else
                        type = RBT_RRr;
            
            if (type & RBT_LLr_LRr_RRr_RLr) {
                
                if (type & RBT_LLr_LRr)
                    gu->right->elem.color = rbBlack;
                else
                    gu->left->elem.color = rbBlack;
                
                pu->elem.color = rbBlack;
                
                if (gu == linkedBinaryTree<rbNode<K, E>>::root)
                    return;
                else {
                    gu->elem.color = rbRed;
                    continue;
                }
                
            } else {
                
                binaryTreeNode<rbNode<K, E>> *tmp = NULL;
                
                if (type & RBT_LLb_RRb) {
                    
                    gu->elem.color = rbRed;
                    pu->elem.color = rbBlack;
                    
                    binaryTreeNode<rbNode<K, E>>* (*func)(binaryTreeNode<rbNode<K, E>>*&);
                    if (type == RBT_LLb)
                        func = rotateLL;
                    else
                        func = rotateRR;
                    tmp = func(gu);
                    
                } else {
                    
                    u->elem.color = rbBlack;
                    pu->elem.color = rbRed;
                    gu->elem.color = rbRed;
                    
                    binaryTreeNode<rbNode<K, E>> **d;
                    binaryTreeNode<rbNode<K, E>>* (*func1)(binaryTreeNode<rbNode<K, E>>*&);
                    binaryTreeNode<rbNode<K, E>>* (*func2)(binaryTreeNode<rbNode<K, E>>*&);
                    
                    if (type == RBT_LRb) {
                        d = &gu->left;
                        func1 = rotateRR;
                        func2 = rotateLL;
                    } else {
                        d = &gu->right;
                        func1 = rotateLL;
                        func2 = rotateRR;
                    }
                    *d = func1(pu);
                    tmp = func2(gu);
                }
                
                if (gu == linkedBinaryTree<rbNode<K, E>>::root)
                    linkedBinaryTree<rbNode<K, E>>::root = tmp;
                else {
                    binaryTreeNode<rbNode<K, E>> *ggu = nodes[i - 3];
                    if (gu == ggu->left)
                        ggu->left = tmp;
                    else
                        ggu->right = tmp;
                }
                
                return;
            }
        }
    }
    
    void erase(const K& theKey) {
    
        binaryTreeNode<rbNode<K, E>> *p = linkedBinaryTree<rbNode<K, E>>::root, *pp = NULL;
        
        while (p != NULL && p->elem.pair.first != theKey) {
            
            pp = p;
            
            if (p->elem.pair.first > theKey)
                p = p->left;
            else
                p = p->left;
        }
        
        if (p == NULL)
            return;
        
        if (p->left != NULL && p->right != NULL) {
            
            binaryTreeNode<rbNode<K, E>> *s = p->left, *ps = p;
            
            while (s->right != NULL) {
                ps = s;
                s = s->right;
            }
            
            binaryTreeNode<rbNode<K, E>> *q = new binaryTreeNode<rbNode<K, E>>(rbNode<K, E>(s->elem.pair, p->elem.color), p->left, p->right);
            
            if (pp == NULL)
                linkedBinaryTree<rbNode<K, E>>::root = q;
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
        
        binaryTreeNode<rbNode<K, E>> *c;
        
        if (p->left != NULL)
            c = p->left;
        else
            c = p->right;
        
        if (pp == NULL)
            linkedBinaryTree<rbNode<K, E>>::root = c;
        else
            if (p == pp->left)
                pp->left = c;
            else
                pp->right = c;
        
        bool shouldBalance = p->elem.color == rbBlack && linkedBinaryTree<rbNode<K, E>>::root != c;
        
        delete p;
        --linkedBinaryTree<rbNode<K, E>>::treeSize;
        
        if (!shouldBalance)
            return;
        
        RBT_ERS type;
        
        if (c == pp->left)
            if (pp->right->elem.color == rbBlack)
                if (pp->right->left == NULL || pp->right->left->elem.color == rbBlack)
                    if (pp->right->right == NULL || pp->right->right->elem.color == rbBlack)
                        type = RBT_Lb0;
                    else
                        type = RBT_Lb1;
                else
                    if (pp->right->right == NULL || pp->right->right->elem.color == rbBlack)
                        type = RBT_Lb1;
                    else
                        type = RBT_Lb2;
            else
                if (pp->right->left->left == NULL || pp->right->left->left->elem.color == rbBlack)
                    if (pp->right->left->right == NULL || pp->right->left->right->elem.color == rbBlack)
                        type = RBT_Lr0;
                    else
                        type = RBT_Lr1;
                else
                    if (pp->right->left->right == NULL || pp->right->left->right->elem.color == rbBlack)
                        type = RBT_Lr11;
                    else
                        type = RBT_Lr2;
        else
            if (pp->left->elem.color == rbBlack)
                if (pp->left->left == NULL || pp->left->left->elem.color == rbBlack)
                    if (pp->left->right == NULL || pp->left->right->elem.color == rbBlack)
                        type = RBT_Rb0;
                    else
                        type = RBT_Rb1;
                else
                    if (pp->left->right == NULL || pp->left->right->elem.color == rbBlack)
                        type = RBT_Rb1;
                    else
                        type = RBT_Rb2;
            else
                if (pp->left->right->left == NULL || pp->left->right->left->elem.color == rbBlack)
                    if (pp->left->right->right == NULL || pp->left->right->right->elem.color == rbBlack)
                        type = RBT_Rr0;
                    else
                        type = RBT_Rr11;
                else
                    if (pp->left->right->right == NULL || pp->left->right->right->elem.color == rbBlack)
                        type = RBT_Rr1;
                    else
                        type = RBT_Rr2;
        
        if (type & RBT_Lb0_Rb0) {
        
        } else {
        
        }
    }
    
    void ascend() {linkedBinaryTree<rbNode<K, E>>::preOrder(redBlackOutput); printf("\n");}
    
protected:
    
    static void redBlackOutput(binaryTreeNode<rbNode<K, E>> *t) { printf("%c:%d ", t->elem.color, t->elem.pair.second); }
    
    static binaryTreeNode<rbNode<K, E>>* rotateLL(binaryTreeNode<rbNode<K, E>>*& a) {
        binaryTreeNode<rbNode<E, E>> *b = a->left;
        a->left = b->right;
        b->right = a;
        return b;
    }
    
    static binaryTreeNode<rbNode<K, E>>* rotateRR(binaryTreeNode<rbNode<K, E>>*& a) {
        binaryTreeNode<rbNode<K, E>> *b = a->right;
        a->right = b->left;
        b->left = a;
        return b;
    }
};

#endif /* redBlackTree_hpp */
