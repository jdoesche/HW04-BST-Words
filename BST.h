#ifndef BST_H
#define BST_H

#include <iostream>
using namespace std;
#include <fstream>
#include <string>

struct Node
{
    Node* left;
    Node* right;
    int data;
    string key;
};

class BST
{
 private:
    Node* root;
    void print(Node* start, int inlayer);

    //Helper Functions
    void addhelper(Node* item, Node* NEWMANN);
    void destroy(Node* marked);
    void writehelper(Node* item, ofstream& file);
  //Node* finddagoshdangnode(Node* start, Node* marked);
    Node* findparent(Node* start, Node* marked, bool& isleft);
    Node* findreplacement(Node* marked);

  
 public:
    //Con-/De-structors
    BST();
    ~BST();

    //Setup
    void add(string newkey, int newdata);
    void remove(string target);

    //Find
    Node* find(Node* start, string param);
    Node* min(Node* start);
    Node* max(Node* start);

    //Stream
    void read(string flnm);
    void write(string flnm);

    //Initializers (Public Helpers)
    void printinitializer();
    void siprint(Node* item);
};
#endif //BST_H
