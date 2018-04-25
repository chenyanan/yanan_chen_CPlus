//
//  avlTree.hpp
//  c+
//
//  Created by chenyanan on 2017/3/4.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef avlTree_hpp
#define avlTree_hpp

// erase
//.
//.
//. -> != NULL because p != NULL
//.
//.
//q -> != NULL bacause (p->left != NULL && p->right != NULL) do exit a node that his key less than p, so q can not be NULL
//.
//.
//. -> != NULL because s->right != NULL so ps != NULL
//.
//.
//c = s->left can be NULL 记录a->left == NULL a->right == NULL的情况 用一个Key去记录删除前的情况

// erase
//R_1 L_1记得调整b另外一边的bf

// erase
//R_1 L_1 R1 L1需要变换nodes[i - 1]的节点方便继续向上查找

// insert
// RL LR 中c在旋转之后都是0，不需要手动去设置

// erase
// R_1 L_1 中c在旋转之后需要主动设置成0

// erase
// a->left == a->right == 0 主动调整bf=0

enum AVL_IST : int {
    AVL_LL    = 1, //0001
    AVL_RR    = 2, //0010
    AVL_LR    = 4, //0100
    AVL_RL    = 8, //1000
    AVL_LL_RR = 3, //0011
};
    
enum AVL_ERS : int {
    AVL_R0      = 1,   //000001
    AVL_R1      = 2,   //000010
    AVL_R_1     = 4,   //000100
    AVL_L0      = 8,   //001000
    AVL_L1      = 16,  //010000
    AVL_L_1     = 32,  //100000
    AVL_R0_R1   = 3,   //000011
    AVL_L0_R0   = 9,   //001001
    AVL_L1_R1   = 18,  //010010
    AVL_R_1_L_1 = 36,  //100100
};

template<typename K, typename E>
struct avlNode {
    std::pair<const K,E> pair;
    int bf;
    
    avlNode(const std::pair<const K,E>& thePair) : pair(thePair) {}
    avlNode(const std::pair<const K,E>& thePair, int theBF) : pair(thePair) {bf = theBF;}
    avlNode(const K& theKey, const E& theValue, int theBF) : pair(theKey, theValue) {bf = theBF;}
};

template<typename K, typename E>
class avlTree : public bsTree<K, E>, public linkedBinaryTree<avlNode<K, E>> {
public:
    
    bool empty() const {return linkedBinaryTree<avlNode<K, E>>::treeSize == 0;}
    
    int size() const {return linkedBinaryTree<avlNode<K, E>>::treeSize;}
    
    std::pair<const K, E>* find(const K& theKey) const {
        
        binaryTreeNode<avlNode<K, E>> *p = linkedBinaryTree<avlNode<K, E>>::root;
        
        arrayList<binaryTreeNode<avlNode<K, E>>*> arr(linkedBinaryTree<avlNode<K, E>>::height());
        
        while (p != NULL)
            if (p->elem.pair.first < theKey)
                p = p->right;
            else
                if (p->elem.pair.first > theKey)
                    p = p->left;
                else
                    return &p->elem.pair;
        
        return NULL;
    }
    
    void insert(const std::pair<const K,E>& thePair) {
        
        int height = (int)ceil(logf((float)linkedBinaryTree<avlNode<K, E>>::treeSize + 2.0f) / logf(2.0f) * 1.44f);
        
        int balance[height], ia = 0, length = 0;
        binaryTreeNode<avlNode<K, E>>* nodes[height], *a = NULL, *pp = NULL, *p = linkedBinaryTree<avlNode<K, E>>::root;
        
        while (p != NULL) {
            
            int bf;
            pp = p;
            
            if (p->elem.pair.first == thePair.first) {
                p->elem.pair.second = thePair.second;
                return;
                
            } else
                if (p->elem.pair.first > thePair.first) {
                    bf = 1;
                    p = p->left;
        
                } else {
                    bf = -1;
                    p = p->right;
                }
            
            nodes[length] = pp;
            balance[length] = bf;
            
            if (pp->elem.bf != 0) {
                a = pp;
                ia = length;
            }
        
            ++length;
        }
        
        binaryTreeNode<avlNode<K, E>> *newNode = new binaryTreeNode<avlNode<K, E>>(avlNode<K, E>(thePair, 0));
        if (linkedBinaryTree<avlNode<K, E>>::root == NULL) {
            linkedBinaryTree<avlNode<K, E>>::root = newNode;
            ++linkedBinaryTree<avlNode<K, E>>::treeSize;
            return;
        }
        else
            if (pp->elem.pair.first < thePair.first)
                pp->right = newNode;
            else
                pp->left = newNode;
        ++linkedBinaryTree<avlNode<K, E>>::treeSize;
        
        if (a == NULL) {
            for (int i = 0; i < length; ++i)
                nodes[i]->elem.bf = balance[i];
            return;
        }
        
        if (a->elem.bf + balance[ia] == 0) {
            a->elem.bf = 0;
            for (int i = ia + 1; i < length; ++i)
                nodes[i]->elem.bf = balance[i];
            return;
        }
        
        int ib = ia + 1;
        binaryTreeNode<avlNode<K, E>>* b = nodes[ib];
        
        int ic = ib + 1;
        binaryTreeNode<avlNode<K, E>>* c = (ic == length) ? NULL : nodes[ic];
        
        AVL_IST type;
        
        if (a->elem.bf + balance[ia] == 2)
            if (b->elem.bf + balance[ib] == 1)
                type = AVL_LL;
            else
                type = AVL_LR;
        else
            if (b->elem.bf + balance[ib] == -1)
                type = AVL_RR;
            else
                type = AVL_RL;
        
        binaryTreeNode<avlNode<K, E>>* tmp = NULL;
        
        if(type & AVL_LL_RR) {
            a->elem.bf = 0;
            b->elem.bf = 0;
            
            binaryTreeNode<avlNode<K, E>>* (*func)(binaryTreeNode<avlNode<K, E>>*& a);
            if (type == AVL_LL)
                func = rotateLL;
            else
                func = rotateRR;
            tmp = func(a);
            
        } else {
        
            int bfc;
            
            if (c == NULL)
                bfc = 0;
            else
                bfc = c->elem.bf + balance[ic];
            
            binaryTreeNode<avlNode<K, E>> **d;
            binaryTreeNode<avlNode<K, E>>* (*func1)(binaryTreeNode<avlNode<K, E>>*& a);
            binaryTreeNode<avlNode<K, E>>* (*func2)(binaryTreeNode<avlNode<K, E>>*& a);
            
            if (type == AVL_LR) {
                switch (bfc) {
                    case  0: a->elem.bf =  0; b->elem.bf = 0; break;
                    case  1: a->elem.bf = -1; b->elem.bf = 0; break;
                    case -1: a->elem.bf =  0; b->elem.bf = 1; break;
                    default: break;
                }
                d = &a->left;
                func1 = rotateRR;
                func2 = rotateLL;
                
            } else {
                switch (bfc) {
                    case  0: a->elem.bf = 0; b->elem.bf =  0; break;
                    case  1: a->elem.bf = 0; b->elem.bf = -1; break;
                    case -1: a->elem.bf = 1; b->elem.bf =  0; break;
                    default: break;
                }
                d = &a->right;
                func1 = rotateLL;
                func2 = rotateRR;
            }
            *d = func1(*d);
            tmp = func2(a);
        }
        
        if (a == linkedBinaryTree<avlNode<K, E>>::root)
            linkedBinaryTree<avlNode<K, E>>::root = tmp;
        else {
            
            int ipa = ia - 1;
            binaryTreeNode<avlNode<K, E>> *pa = nodes[ipa];
            
            if (a == pa->left)
                pa->left = tmp;
            else
                pa->right = tmp;
        }
        
        if (type & AVL_LL_RR)
            for (int i = ib + 1; i < length; ++i)
                nodes[i]->elem.bf = balance[i];
        else
            for (int i = ic + 1; i < length; ++i)
                nodes[i]->elem.bf = balance[i];

        return;
    }
    
    void erase(const K& theKey) {
        
        int height = (int)ceil(logf((float)linkedBinaryTree<avlNode<K, E>>::treeSize + 2.0f) / logf(2.0f) * 1.44f), length = 0;
        
        binaryTreeNode<avlNode<K, E>>* nodes[height];
        binaryTreeNode<avlNode<K, E>> *p = linkedBinaryTree<avlNode<K, E>>::root, *pp = NULL;
        
        while (p != NULL && p->elem.pair.first != theKey) {
            
            pp = p;
            
            if (p->elem.pair.first > theKey)
                p = p->left;
            else
                p = p->right;
            
            nodes[length] = pp;
            ++length;
        }
        
        if (p == NULL)
            return;
        
        if (p->left != NULL && p->right != NULL) {
            
            int locationOfP = length;
            ++length;
            
            binaryTreeNode<avlNode<K, E>> *s = p->left, *ps = p;
            
            while (s->right != NULL) {
                ps = s;
                s = s->right;
                
                nodes[length] = ps;
                ++length;
            }
            
            binaryTreeNode<avlNode<K, E>> *q = new binaryTreeNode<avlNode<K, E>>(avlNode<K, E>(s->elem.pair, p->elem.bf), p->left, p->right);
            nodes[locationOfP] = q;
            
            if (pp == NULL)
                linkedBinaryTree<avlNode<K, E>>::root = q;
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
        
        binaryTreeNode<avlNode<K, E>> *c;
    
        if (p->left != NULL)
            c = p->left;
        else
            c = p->right;
        
        if (linkedBinaryTree<avlNode<K, E>>::root == p)
            linkedBinaryTree<avlNode<K, E>>::root = c;
        else
            if (p == pp->left)
                pp->left = c;
            else
                pp->right = c;
    
        --linkedBinaryTree<avlNode<K, E>>::treeSize;
        delete p;
        
        nodes[length] = c;
        ++length;
        
        if (length == 1)
            return;
        
        for (int i = length - 1; i > 0; --i) {
            
            binaryTreeNode<avlNode<K, E>> *a = nodes[i - 1], *d = nodes[i], *b = NULL;
            
            if (a->left == a->right)
                a->elem.bf = 0;
            else {
                int balance;
                if (d == a->left) {
                    balance = -1; b = a->right;
                } else {
                    balance =  1; b = a->left;
                }
                a->elem.bf += balance;
            }
            
            if (a->elem.bf == 0)
                continue;
            
            if (a->elem.bf == 1 || a->elem.bf == -1)
                return;
            
            AVL_ERS type;
            
            if (a->elem.bf == 2)
                if (b == NULL || b->elem.bf == 0)
                    type = AVL_R0;
                else
                    if(b->elem.bf == 1)
                        type = AVL_R1;
                    else
                        type = AVL_R_1;
            else
                if (b == NULL || b->elem.bf == 0)
                    type = AVL_L0;
                else
                    if (b->elem.bf == 1)
                        type = AVL_L_1;
                    else
                        type = AVL_L1;
            
            binaryTreeNode<avlNode<K, E>> *tmp;
            
            if (type & AVL_R_1_L_1) {
                
                binaryTreeNode<avlNode<K, E>> *c, **d;
                binaryTreeNode<avlNode<K, E>>* (*func1)(binaryTreeNode<avlNode<K, E>>*& a);
                binaryTreeNode<avlNode<K, E>>* (*func2)(binaryTreeNode<avlNode<K, E>>*& a);
                
                if (type == AVL_R_1) {
                    c = b->right;
                    switch (c->elem.bf) {
                        case  0: a->elem.bf =  0; b->elem.bf = 0; break;
                        case  1: a->elem.bf = -1; b->elem.bf = 0; c->elem.bf = 0; break;
                        case -1: a->elem.bf =  0; b->elem.bf = 1; c->elem.bf = 0; break;
                        default: break;
                    }
                    d = &a->left;
                    func1 = rotateRR;
                    func2 = rotateLL;
                    
                } else {
                    c = b->left;
                    switch (c->elem.bf) {
                        case  0: a->elem.bf = 0; b->elem.bf =  0; break;
                        case  1: a->elem.bf = 0; b->elem.bf = -1; c->elem.bf = 0; break;
                        case -1: a->elem.bf = 1; b->elem.bf =  0; c->elem.bf = 0; break;
                        default:break;
                    }
                    d = &a->right;
                    func1 = rotateLL;
                    func2 = rotateRR;
                }
                *d = func1(b);
                tmp = func2(a);
                
            } else {
                
                if (type == AVL_R0) {
                    a->elem.bf = 1;
                    b->elem.bf = -1;
                    
                } else
                    if (type == AVL_L0) {
                        a->elem.bf = -1;
                        b->elem.bf = 1;
                        
                    } else {
                        a->elem.bf = 0;
                        b->elem.bf = 0;
                    }
                
                binaryTreeNode<avlNode<K, E>>* (*func)(binaryTreeNode<avlNode<K, E>>*&);
                if (type & AVL_R0_R1)
                    func = rotateLL;
                else
                    func = rotateRR;
                tmp = func(a);
            }
            
            if (a == linkedBinaryTree<avlNode<K, E>>::root)
                linkedBinaryTree<avlNode<K, E>>::root = tmp;
            else {
                binaryTreeNode<avlNode<K, E>> *pa = nodes[i - 2];
                if (pa->left == a)
                    pa->left = tmp;
                else
                    pa->right = tmp;
            }
            
            if (type & AVL_L0_R0)
                return;
            else {
                if (type & AVL_R_1_L_1)
                    nodes[i - 1] = c;
                else
                    nodes[i - 1] = b;
                continue;
            }
        }
    }
    
    void ascend() {linkedBinaryTree<avlNode<K, E>>::preOrder(avlOutput); std::cout << std::endl;}
    
protected:
    
    static void avlOutput(binaryTreeNode<avlNode<K,E>> *t) {std::cout << t->elem.bf << ":" << t->elem.pair.second << ' '; }
    
    static binaryTreeNode<avlNode<K, E>>* rotateLL(binaryTreeNode<avlNode<K, E>>*& a) {
        binaryTreeNode<avlNode<E, E>> *b = a->left;
        a->left = b->right;
        b->right = a;
        return b;
    }
    static binaryTreeNode<avlNode<K, E>>* rotateRR(binaryTreeNode<avlNode<K, E>>*& a) {
        binaryTreeNode<avlNode<K, E>> *b = a->right;
        a->right = b->left;
        b->left = a;
        return b;
    }
};

#endif /* avlTree_hpp */
