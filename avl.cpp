#include "Tree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]){
  if(argc != 2){
    cout << "run with argument\n";
    return 0;
  }
  AVLTree tree;



  string arg1(argv[1]);
  string line;
  ifstream testFile(arg1);
  //char command;
  string command;
  string arg;
  if(testFile.is_open()){

    while (getline(testFile, line)){
      //cout << line << endl;
      //cout << line<<endl;
      if(line==""||line[0]=='#'){
        //cout << "newline"<<endl;
        continue;
      }

      istringstream iss(line);
      vector<string> args;

      iss >> command;
      while(iss >> arg){
        args.push_back(arg);
      }


      if(command=="insert"){
        int inserts=0;
        int visits=0;
        int rotations=0;
        bool inserted = true;
        for(size_t i=0; i<args.size(); i++){
          //cout << args.at(i)<<endl;
          //if(tree.insertKey(stoi(args.at(i)), visits, rotations))
          inserted = true;
          tree.insertKey(stoi(args.at(i)), visits, rotations, inserted);
          if(inserted)
            inserts++;
        }
        cout << "Added "<<inserts<<" of "<<args.size()<<" nodes.\n";
        cout << "Visited "<<visits<<" (" << (1.0*visits)/args.size() << ") nodes and performed "<<rotations<<" ("<<(1.0*rotations)/args.size()<<") rotations."<<endl;
      } else if(command=="print"){
        if(args.at(0)=="tree"){
          tree.printTree();
        } else {
          tree.printRotations(args.at(0));
        }
      } else if (command=="lookup"){
        int found=0;
        int visits=0;
        //int rotations=0;
        string foundNodes="[";
        for(size_t i=0; i<args.size(); i++){
          if(tree.lookup(stoi(args.at(i)), visits)){
            found++;
            foundNodes+=args.at(i)+", ";
          }
        }
        if(found>0)
          foundNodes.erase(foundNodes.length()-2, 2);
        foundNodes+="]";

        cout << "Found "<<found<<" of "<<args.size()<<" nodes: " << foundNodes<<endl;
        cout << "Visited "<<visits<<" ("<<(visits*1.0)/args.size()<<") nodes and performed 0 (0) rotations."<<endl;
      }
      cout << endl;
    }


    testFile.close();
  } else {
    cout << "cannot open file\n";
  }


}
