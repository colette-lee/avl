#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <vector>
#include <utility>

struct Node {
  int key;
  Node *parent;
  Node *left;
  Node *right;
  int height;
  Node(int key){
    this->key = key;
    left = nullptr;
    right = nullptr;
    height = 1;
    parent = NULL;
  }
  ~Node(){
    delete left;
    delete right;
  }

};
class AVLTree {

  //Node *root;
  std::vector<std::pair<int,int>> ll;
  std::vector<std::pair<int,int>> rr;
  std::vector<std::pair<int,int>> lr;
  std::vector<std::pair<int,int>> rl;


  public:
    Node *root;

    AVLTree();
    ~AVLTree();
    int height(Node *N);
    Node *rightRotate(Node *z);
    Node *leftRotate(Node *z);
    int getBalance(Node *N);
    bool insertKey(int key, int &visited, int &rotations, bool &inserted);
    bool lookup(int key, int &visits);
    void printTree();
    Node *insert(Node* node, int key, int &visited, int &rotations, bool &inserted);
    std::string nodeToString(Node *node, int depth);

    void findBounds(Node *node, char flag1, char flag2, int lowerBound, int upperBound);



    void printRotations(std::string arg);


};

#endif
