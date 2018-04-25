//
//  avlTreeOld.hpp
//  C+
//
//  Created by chenyanan on 2017/3/18.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef avlTreeOld_hpp
#define avlTreeOld_hpp

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
            
            int bf; pp = p;
            
            if (p->elem.pair.first == thePair.first) {
                p->elem.pair.second = thePair.second; return;
            } else
                if (p->elem.pair.first > thePair.first) {
                    p = p->left; bf = 1;
                } else {
                    p = p->right; bf = -1;
                }
            
            nodes[length] = pp;
            balance[length] = bf;
            
            if (pp->elem.bf != 0) {
                a = pp; ia = length;
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
        
        int ib = ia + 1, ipa = ia - 1;
        binaryTreeNode<avlNode<K, E>>* b = nodes[ib], *pa = (ia == 0) ? NULL : nodes[ipa];
        
        if (a->elem.bf + balance[ia] == 2 && b->elem.bf + balance[ib] == 1) {
            
            a->elem.bf = 0;
            b->elem.bf = 0;
            
            binaryTreeNode<avlNode<K, E>>* tmp = rotateLL(a);
            if (a == linkedBinaryTree<avlNode<K, E>>::root)
                linkedBinaryTree<avlNode<K, E>>::root = tmp;
            else
                pa->left = tmp;
            
            for (int i = ib + 1; i < length; ++i)
                nodes[i]->elem.bf = balance[i];
            return;
        }
        
        if(a->elem.bf + balance[ia] == -2 && b->elem.bf + balance[ib] == -1) {
            
            a->elem.bf = 0;
            b->elem.bf = 0;
            
            binaryTreeNode<avlNode<K, E>>* tmp = rotateRR(a);
            if (a == linkedBinaryTree<avlNode<K, E>>::root)
                linkedBinaryTree<avlNode<K, E>>::root = tmp;
            else
                pa->right = tmp;
            
            for (int i = ib + 1; i < length; ++i)
                nodes[i]->elem.bf = balance[i];
            return;
        }
        
        int ic = ib + 1;
        binaryTreeNode<avlNode<K, E>>* c = (ic == length) ? NULL : nodes[ic];
        
        if (a->elem.bf + balance[ia] == 2 && b->elem.bf + balance[ib] == -1) {
            
            if (c == NULL) {
                a->elem.bf = 0; b->elem.bf = 0;
            } else if (c->elem.bf + balance[ic] == 1) {
                a->elem.bf = -1; b->elem.bf = 0;
            } else if (c->elem.bf + balance[ic] == -1) {
                a->elem.bf = 0; b->elem.bf = 1;
            } else throw queueEmpty();
            
            a->left = rotateRR(a->left);
            binaryTreeNode<avlNode<K, E>>* tmp = rotateLL(a);
            if (pa == NULL)
                linkedBinaryTree<avlNode<K, E>>::root = tmp;
            else
                if (a == pa->left)
                    pa->left = tmp;
                else
                    pa->right = tmp;
            
            for (int i = ic + 1; i < length; ++i)
                nodes[i]->elem.bf = balance[i];
            return;
        }
        
        if (a->elem.bf + balance[ia] == -2 && b->elem.bf + balance[ib] == 1) {
            
            if (c == NULL) {
                a->elem.bf = 0; b->elem.bf = 0;
            } else if (c->elem.bf + balance[ic] == 1) {
                a->elem.bf = 0; b->elem.bf = -1;
            } else if (c->elem.bf + balance[ic] == -1) {
                a->elem.bf = 1; b->elem.bf = 0;
            } else throw queueEmpty();
            
            a->right = rotateLL(a->right);
            binaryTreeNode<avlNode<K, E>>* tmp = rotateRR(a);
            if (pa == NULL)
                linkedBinaryTree<avlNode<K, E>>::root = tmp;
            else
                if (a == pa->left)
                    pa->left = tmp;
                else
                    pa->right = tmp;
            
            for (int i = ic + 1; i < length; ++i)
                nodes[i]->elem.bf = balance[i];
            return;
        }
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
            
            binaryTreeNode<avlNode<K, E>> *B;
            binaryTreeNode<avlNode<K, E>> *A = nodes[i - 1];
            binaryTreeNode<avlNode<K, E>> *C = nodes[i];
            
            int balance;
            if (C == A->left) {
                balance = -1; B = A->right;
            } else {
                balance = 1; B = A->left;
            }
            
            A->elem.bf += balance;
            
            if (A->elem.bf == 0)
                continue;
            
            if (A->elem.bf == 1 || A->elem.bf == -1)
                return;
            
            if (A->elem.bf == 2 && B->elem.bf == 0) {
                A->elem.bf = 1;
                B->elem.bf = -1;
                binaryTreeNode<avlNode<K, E>> *tmp = rotateLL(A);
                if (A == linkedBinaryTree<avlNode<K, E>>::root)
                    linkedBinaryTree<avlNode<K, E>>::root = tmp;
                else {
                    binaryTreeNode<avlNode<K, E>> *ppu = nodes[i - 2];
                    if (ppu->left == A)
                        ppu->left = tmp;
                    else
                        ppu->right = tmp;
                }
                return;
            }
            
            if (A->elem.bf == -2 && B->elem.bf == 0) {
                A->elem.bf = -1;
                B->elem.bf = 1;
                binaryTreeNode<avlNode<K, E>> *tmp = rotateRR(A);
                if (A == linkedBinaryTree<avlNode<K, E>>::root)
                    linkedBinaryTree<avlNode<K, E>>::root = tmp;
                else {
                    binaryTreeNode<avlNode<K, E>> *ppu = nodes[i - 2];
                    if (ppu->left == A)
                        ppu->left = tmp;
                    else
                        ppu->right = tmp;
                }
                return;
            }
            
            if (A->elem.bf == 2 && B->elem.bf == 1) {
                A->elem.bf = 0;
                B->elem.bf = 0;
                binaryTreeNode<avlNode<K, E>> *tmp = rotateLL(A);
                if (A == linkedBinaryTree<avlNode<K, E>>::root)
                    linkedBinaryTree<avlNode<K, E>>::root = tmp;
                else {
                    binaryTreeNode<avlNode<K, E>> *ppu = nodes[i - 2];
                    if (ppu->left == A)
                        ppu->left = tmp;
                    else
                        ppu->right = tmp;
                }
                continue;
            }
            
            if (A->elem.bf == -2 && B->elem.bf == -1) {
                A->elem.bf = 0;
                B->elem.bf = 0;
                binaryTreeNode<avlNode<K, E>> *tmp = rotateRR(A);
                if (A == linkedBinaryTree<avlNode<K, E>>::root)
                    linkedBinaryTree<avlNode<K, E>>::root = tmp;
                else {
                    binaryTreeNode<avlNode<K, E>> *ppu = nodes[i - 2];
                    if (ppu->left == A)
                        ppu->left = tmp;
                    else
                        ppu->right = tmp;
                }
                continue;
            }
            
            if (A->elem.bf == 2 && B->elem.bf == -1) {
                if (B->right->elem.bf == 0) {
                    A->elem.bf = 0; B->elem.bf = 0;
                } else if (B->right->elem.bf == 1) {
                    A->elem.bf = -1; B->elem.bf = 0;
                } else if (B->right->elem.bf == -1) {
                    A->elem.bf = 0; B->elem.bf = 1;
                } else throw queueEmpty();
                
                A->left = rotateRR(B);
                binaryTreeNode<avlNode<K, E>> *tmp = rotateLL(A);
                if (A == linkedBinaryTree<avlNode<K, E>>::root)
                    linkedBinaryTree<avlNode<K, E>>::root = tmp;
                else {
                    binaryTreeNode<avlNode<K, E>> *ppu = nodes[i - 2];
                    if (ppu->left == A)
                        ppu->left = tmp;
                    else
                        ppu->right =tmp;
                }
                continue;
            }
            
            if (A->elem.bf == -2 && B->elem.bf == 1) {
                if (B->left->elem.bf == 0) {
                    A->elem.bf = 0; B->elem.bf = 0;
                } else if (B->left->elem.bf == 1) {
                    A->elem.bf = 0; B->elem.bf = -1;
                } else if (B->left->elem.bf == -1) {
                    A->elem.bf = 1; B->elem.bf = 0;
                } else throw queueEmpty();
                
                A->right = rotateLL(B);
                binaryTreeNode<avlNode<K, E>> *tmp = rotateRR(A);
                if (A == linkedBinaryTree<avlNode<K, E>>::root)
                    linkedBinaryTree<avlNode<K, E>>::root = tmp;
                else {
                    binaryTreeNode<avlNode<K, E>> *ppu = nodes[i - 2];
                    if (ppu->left == A)
                        ppu->left = tmp;
                    else
                        ppu->right =tmp;
                }
                continue;
            }
        }
    }
    
    void ascend() {linkedBinaryTree<avlNode<K, E>>::preOrder(avlOutput); std::cout << std::endl;}
    
protected:
    
    static void avlOutput(binaryTreeNode<avlNode<K,E>> *t) {std::cout << t->elem.bf << ":" << t->elem.pair.second << ' '; }
    
    binaryTreeNode<avlNode<K, E>>* rotateLL(binaryTreeNode<avlNode<K, E>>*& a) {
        binaryTreeNode<avlNode<E, E>> *b = a->left;
        a->left = b->right;
        b->right = a;
        return b;
    }
    binaryTreeNode<avlNode<K, E>>* rotateRR(binaryTreeNode<avlNode<K, E>>*& a) {
        binaryTreeNode<avlNode<K, E>> *b = a->right;
        a->right = b->left;
        b->left = a;
        return b;
    }
};


#endif /* avlTreeOld_hpp */


