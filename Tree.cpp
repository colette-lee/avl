#include "Tree.h"
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int max(int a, int b);
Node* insert(Node* node, int key);
bool isLeaf(Node *node);


AVLTree::AVLTree(){
  root = NULL;
}
AVLTree::~AVLTree(){
  delete root;
}

int AVLTree::height(Node *N){
  if(N==NULL)
    return 0;
  return N->height;
}
Node* AVLTree::rightRotate(Node *z){
  //cout <<"rightRotate"<<endl;
  Node *y = z->left;
  Node *t = y->right;
  y->right = z;
  z->left = t;

  z->height = max(height(z->left),height(z->right)) + 1;
  y->height = max(height(y->left),height(y->right)) + 1;

  if(root->key==z->key)
    root = y;
  y->parent = z->parent;
  z->parent = y;
  return y;


}
Node* AVLTree::leftRotate(Node *z){
  //cout <<"leftRotate"<<endl;

  Node *y = z->right;
  Node *t = y->left;
  y->left = z;
  z->right = t;

  z->height = max(height(z->left),height(z->right)) + 1;
  y->height = max(height(y->left),height(y->right)) + 1;
  if(root->key==z->key)
    root = y;
  y->parent = z->parent;
  z->parent = y;
  return y;

}
int AVLTree::getBalance(Node *N){
  if(N==NULL)
    return 0;
  return height(N->left) - height(N->right);
}
bool AVLTree::insertKey(int key, int &visited, int &rotations, bool &inserted){
  if(root==NULL){
    root = new Node(key);
    return true;
  }
  if(key==insert(root, key, visited, rotations, inserted)->key){
    if(key==root->key)
      return true;
    return false;
  }
  return true;
}
Node* AVLTree::insert(Node* node, int key, int &visited, int &rotations, bool &inserted){
  if(node == NULL){
    Node *newNode = new Node(key);
    return newNode;
  }
  visited++;
  if(key<node->key){
    node->left = insert(node->left, key, visited, rotations, inserted);
    node->left->parent = node;
  } else if (key>node->key) {
    node->right = insert(node->right,key, visited, rotations, inserted);
    node->right->parent = node;
  } else{
    inserted = false;
    return node;
  }

  node->height = 1 + max(height(node->left),height(node->right));

  int balance = getBalance(node);
  // Left Left
  if (balance > 1 && key < node->left->key){
      //cout << "left-left"<<endl;
      rotations++;
      return rightRotate(node);
    }

  // Right Right
  if (balance < -1 && key > node->right->key){
      rotations++;
      return leftRotate(node);
    }
  // Left Right
  if (balance > 1 && key > node->left->key) {
      rotations+=2;
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }

  // Right Left
  if (balance < -1 && key < node->right->key) {
      rotations+=2;
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  return node;
}

bool AVLTree::lookup(int key, int &visits){
  if(root==NULL)
    return false;
  Node *temp = root;
  while(temp!=NULL){
    visits++;
    if(key<temp->key){
      temp = temp->left;
    } else if (key>temp->key){
      temp = temp->right;
    } else if (key == temp->key){
      return true;
    }
  }
  return false;
}

void AVLTree::printTree(){
  cout << nodeToString(root, 0)<<endl;

}


string AVLTree::nodeToString(Node *node, int depth){
  char space = ' ';
  string indent = string(depth*2,space);
  string result="";
  if(node==NULL)
    return indent+"Null";
  if(isLeaf(node))
    return indent+"Leaf("+ to_string(node->key)+")";
  result+= indent+"Node("+ to_string(node->key)+", h="+to_string(height(node)-1)+"):";
  result+="\n"+nodeToString(node->left, depth+1);
  result+="\n"+nodeToString(node->right, depth+1);
  return result;
}


void AVLTree::printRotations(string arg){
  ll.clear();
  rr.clear();
  lr.clear();
  rl.clear();
  if(root==NULL) {
    cout << "No inserts would cause a "<<arg<<" rotation."<<endl;
    return;
  }
  char f1 = '0';
  char f2 = '0';
  findBounds(root, f1, f2, -2147483648, 2147483647);
  vector<pair<int,int>> v;
  if(arg=="left-left"){
    v = ll;
  }else if(arg=="right-right"){
    v = rr;
  } else if (arg=="left-right"){
    v = lr;
  } else if (arg=="right-left"){
    v = rl;
  }
  /*
  for(size_t i=0; i<v.size(); i++){
    if(v.at(i).first>v.at(i).second)
      v.erase(v.begin()+i);
  }
  */

  if(v.empty()){
    cout << "No inserts would cause a "<<arg<<" rotation."<<endl;
    return;
  }
  cout << "The following inserts would cause a "<<arg<<" rotation:"<<endl;
  for(size_t i=0; i<v.size(); i++){
    int lower = v.at(i).first;
    int upper = v.at(i).second;
    if(lower==upper)
      cout << v.at(i).first;
    else if (lower<upper)
      cout << v.at(i).first <<" to "<< v.at(i).second;
    if (i<v.size()-1) cout << ", ";
  }
  cout << endl;
}
void AVLTree::findBounds(Node *node, char flag1, char flag2, int lowerBound, int upperBound){
  if(node==NULL)
    return;
  if(isLeaf(node)){
    //cout << "Node "<<node->key<<" flag1: "<<flag1<<" flag2: "<<flag2<<endl;
    bool leftValid = lowerBound<=node->key-1;
    pair<int, int>leftInsert(lowerBound, node->key-1);
    bool rightValid = node->key+1<=upperBound;
    pair<int,int>rightInsert(node->key+1, upperBound);

    if(flag1=='r'){
      if(flag2=='0'){
        if (leftValid)
          rl.push_back(leftInsert);
        if(rightValid)
          rr.push_back(rightInsert);
      } else if(flag2=='r'){
        if(leftValid)
          rr.push_back(leftInsert);
        if(rightValid)
          rr.push_back(rightInsert);
      } else if (flag2=='l'){
        if(leftValid)
          rl.push_back(leftInsert);
        if(rightValid)
          rl.push_back(rightInsert);
      }
    } else if (flag1=='l'){
      if(flag2=='0'){
        if (leftValid)
          ll.push_back(leftInsert);
        if(rightValid)
          lr.push_back(rightInsert);
      } else if (flag2=='l'){
        if (leftValid)
          ll.push_back(leftInsert);
        if(rightValid)
          ll.push_back(rightInsert);
      } else if (flag2=='r'){
        if (leftValid)
          lr.push_back(leftInsert);
        if(rightValid)
          lr.push_back(rightInsert);
      }
    }

}

  int balance = getBalance(node);
  if(balance==-1){ //right side heavier11
    findBounds(node->left, '0', '0', lowerBound, node->key-1); //upperbound = node->key -1
    findBounds(node->right, 'r', '0', node->key+1, upperBound); //lowerbound = node->key+1
  } else if (balance==1){ //left side heavier
    findBounds(node->left, 'l', '0', lowerBound, node->key-1);
    findBounds(node->right, '0', '0', node->key+1, upperBound);
  } else if(balance==0){
    if(flag2!='0'){
      findBounds(node->left, flag1, flag2,lowerBound, node->key-1);
      findBounds(node->right, flag1, flag2, node->key+1, upperBound);
    } else {
      findBounds(node->left, flag1, 'l', lowerBound, node->key-1);
      findBounds(node->right, flag1, 'r', node->key+1, upperBound);
    }
  }

  return;

}



bool isLeaf(Node *node){
  if(node->right==NULL && node->left==NULL)
    return true;
  return false;
}


int max(int a, int b){
  if(a>b)
    return a;
  else
    return b;
}
