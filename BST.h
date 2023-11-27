#ifndef BST_H
#define BST_H

#include <iostream>
using namespace std;
#include <fstream>

struct Node
{
    Node* left;
    Node* right;
    int data;
    string key;
}

class BST
{
 private:
    Node* root;

    //Helper Functions
    void addhelper(Node* item, Node* NEWMANN);
    void destroy(Node* item);
    void writehelper(Node* item, ofstream file);

    void print(Node* start, int inlayer);
 
 public:
    //Con-/De-structors
    BST();
    ~BST();

    //Setup
    void add(string newkey, int newdata);
    void remove(string target)

    //Find
    Node* find(Node* start, string param);
    Node* minmax();
    Node* min(Node* start);
    Node* max(Node* start);

    //Stream
    void printinitializer();
    void read(string flnm);
    void write(string flnm);
} 
#endif //BST_H