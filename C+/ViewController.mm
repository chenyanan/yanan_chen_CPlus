//
//  ViewController.m
//  C+
//
//  Created by chenyanan on 2017/3/4.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#import "ViewController.h"
#import <string>
#import <iostream>
#import "./algs/linkedBinaryTree.hpp"
#import "./algs/binarySearchTree.hpp"
#import "./algs/avlTree.hpp"
#import "./algs/redBlackTree.hpp"

template<> int linkedBinaryTree<avlNode<int, int>>::count = 0;
template<> void (*linkedBinaryTree<avlNode<int, int>>::visit)(binaryTreeNode<avlNode<int, int>>* t) = NULL;

template<> int linkedBinaryTree<rbNode<int, int>>::count = 0;
template<> void (*linkedBinaryTree<rbNode<int, int>>::visit)(binaryTreeNode<rbNode<int, int>>* t) = NULL;

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    avlTree<int, int> avl;
    redBlackTree<int, int> rb;
    
//    avl.insert({1,1});
//    avl.insert({2,2});
//    avl.insert({7,7});
//    avl.insert({9,9});
//    avl.insert({10,10});
//    avl.insert({6,6});
    
//    avl.insert({20,20});
//    avl.insert({10,10});
//    avl.insert({5,5});
//    avl.insert({30,30});
//    avl.insert({40,40});
//    avl.insert({3,3});
//    avl.insert({4,4});
//    avl.insert({25,25});
//    avl.insert({23,23});
//    avl.insert({27,27});
//    avl.insert({50,50});
    
//    avl.insert({4,4});
//    avl.insert({2,2});
//    avl.insert({3,3});
    
//    avl.ascend();
//    NSLog(@"xixi");
    
    for (int i = 15; i > 0; --i)
        avl.insert({i,i});
    avl.ascend();
    printf("\n");

//    for (int i = 15; i > 0; --i) {
//        avl.erase(i);
//        avl.ascend();
//        printf("\n");
//    }
    
    printf("remove 6  \n");  avl.erase(6);  avl.ascend(); printf("\n");
    printf("remove 7  \n");  avl.erase(7);  avl.ascend(); printf("\n");
    printf("remove 5  \n");  avl.erase(5);  avl.ascend(); printf("\n");
    printf("remove 10 \n");  avl.erase(10); avl.ascend(); printf("\n");
    printf("remove 9  \n");  avl.erase(9);  avl.ascend(); printf("\n");
    printf("remove 11 \n");  avl.erase(11); avl.ascend(); printf("\n");
    printf("remove 15 \n");  avl.erase(15); avl.ascend(); printf("\n");
    printf("remove 12 \n");  avl.erase(12); avl.ascend(); printf("\n");
    printf("remove 13 \n");  avl.erase(13); avl.ascend(); printf("\n");
    printf("remove 1  \n");  avl.erase(1);  avl.ascend(); printf("\n");
    printf("remove 2  \n");  avl.erase(2);  avl.ascend(); printf("\n");
    printf("remove 3  \n");  avl.erase(3);  avl.ascend(); printf("\n");
    
//    printf("remove 11 \n");  avl.erase(11); avl.ascend(); printf("\n");
//    printf("remove 14 \n");  avl.erase(14); avl.ascend(); printf("\n");
//    printf("remove 13 \n");  avl.erase(13); avl.ascend(); printf("\n");
//    printf("remove 15 \n");  avl.erase(15); avl.ascend(); printf("\n");
//    printf("remove 9  \n");  avl.erase(9);  avl.ascend(); printf("\n");
//    printf("remove 2  \n");  avl.erase(2);  avl.ascend(); printf("\n");
//    printf("remove 3  \n");  avl.erase(3);  avl.ascend(); printf("\n");
//    printf("remove 1  \n");  avl.erase(1);  avl.ascend(); printf("\n");
//    printf("remove 6  \n");  avl.erase(6);  avl.ascend(); printf("\n");
//    printf("remove 5  \n");  avl.erase(5);  avl.ascend(); printf("\n");
//    printf("remove 7  \n");  avl.erase(7);  avl.ascend(); printf("\n");
    
//    for (int i = 15; i > 0; --i) {
//        rb.insert({i,i}); rb.ascend(); printf("\n");
//    }
//    rb.ascend();
    
    rb.insert({20,20}); rb.ascend(); printf("\n");
    rb.insert({10,10}); rb.ascend(); printf("\n");
    rb.insert({5,5}); rb.ascend(); printf("\n");
    rb.insert({30,30}); rb.ascend(); printf("\n");
    rb.insert({57,57}); rb.ascend(); printf("\n");
    rb.insert({3,3}); rb.ascend(); printf("\n");
    rb.insert({2,2}); rb.ascend(); printf("\n");
    rb.insert({4,4}); rb.ascend(); printf("\n");
    rb.insert({35,35}); rb.ascend(); printf("\n");
    rb.insert({25,25}); rb.ascend(); printf("\n");
    rb.insert({18,18}); rb.ascend(); printf("\n");
    rb.insert({22,22}); rb.ascend(); printf("\n");
    rb.insert({21,21}); rb.ascend(); printf("\n");

    // Do any additional setup after loading the view, typically from a nib.
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
