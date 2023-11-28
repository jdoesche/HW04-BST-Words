#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include "BST.h"

//Con-/De-structors
BST::BST()
{ root = NULL; }

BST::~BST()
{
    while (root != NULL)
    {
        destroy(root);
    }
}

//Setup
void BST::add(string newkey, int newdata)
{
    Node* NEWMANN = new Node;
    NEWMANN -> left = NULL;
    NEWMANN -> right = NULL;
    NEWMANN -> key = newkey;
    NEWMANN -> data = newdata;
    
    //Case A: Empty List
    if (root == NULL)
    {
        root = NEWMANN;
        return;
    }

    //Case B: Newuser = HEAD
    if (NEWMANN -> data == root -> data)
    {
        root -> key = NEWMANN -> key;
        delete NEWMANN;
        return;
    }

    //Case C: Newuser != HEAD
    Node* cursor = root;
    addhelper(cursor, NEWMANN);
    return;
}

void BST::addhelper(Node* item, Node* NEWMANN)
{
    //If the Datas match
    if (item -> data == NEWMANN -> data)
    {
        item -> key = NEWMANN -> key;
        delete NEWMANN;
        return;
    }

    //If Both exits are Null
    if (item -> left == NULL && item -> right == NULL)
    {
        if (NEWMANN -> data > item -> data)
        {
            item -> right = NEWMANN;
            return;
        }

        if (NEWMANN -> data < item -> data)
        {
            item -> left = NEWMANN;
            return;
        }
    }

    //If Left (Less) is Null
    if (item -> left == NULL)
    {
        if (NEWMANN -> data > item -> data)
        {
            addhelper(item -> right, NEWMANN);
            return;
        }

        if (NEWMANN -> data < item -> data)
        {
            item -> left = NEWMANN;
            return;
        }
    }

    //If Right (More) is Null
    if (item -> right == NULL)
    {
        if (NEWMANN -> data < item -> data)
        {
            addhelper(item -> left, NEWMANN);
            return;
        }

        if (NEWMANN -> data > item -> data)
        {
            item -> right = NEWMANN;
            return;
        }
    }

    //If Neither are Null
    if (item -> right != NULL && item -> left != NULL)
    {
        if (NEWMANN -> data > item -> data)
        {
            addhelper(item -> right, NEWMANN);
            return;
        }

        if (NEWMANN -> data < item -> data)
        {
            addhelper(item -> left, NEWMANN);
            return;
        }
    }

    //Error break
    cout << "Something went wrong. Activating Emergency Exit." << endl;
    return;
}

/* Note: I am re-coding this entire section from scratch

void BST::remove(string target)
{
    Node* cursor = root;
    Node* item = find(cursor, target);
    if (item == NULL)
    {
        cout << "Item not found." << endl;
        return;
    }
    destroy(item);
    return;
}

void BST::destroy(Node* item)
{
    Node* cursor = root;
    
    cursor = replacementsearch(item);

    if (item == root)
    {
        root = NULL;
        delete item;
        return;
    }
    if (cursor == item)
    {
        item = NULL;
        delete cursor;
        return;
    }
    item -> data = cursor -> data;
    item -> key = cursor -> key;


    delete cursor;

    return;
}

Node* BST::replacementsearch(Node* item)
{
    //Case 1: Both are NULL
    if (item -> left == NULL && item -> right == NULL)
        return item;

    //Case 2: Max in Null
    if (item -> right == NULL)
        return max(item -> left);

    return min(item -> right);
}*/

//Search
Node* BST::find(Node* start, string param)
{
    if (start == NULL)
        start = root;

    if (start -> key == param)
        return start;
    
    Node* lside;
    Node* rside;

    //Left-Side Logic
    if (start -> left != NULL)
        lside = find(start -> left, param);
    else
        lside = NULL;

    if (lside != NULL)
        return lside;

    //Right-Side Logic
    if (start -> right != NULL)
        rside = find(start -> right, param);
    else
        rside = NULL;

    if (rside != NULL)
        return rside;

    return NULL;
}

Node* BST::min(Node* start)
{
    if (start == NULL) //Assume root
        start = root;

    if (start -> left == NULL)
        return start;

    return min(start -> left);
}

Node* BST::max(Node* start)
{
    if (start == NULL) //Assume root
        start = root;

    if (start -> right == NULL)
        return start;

    return max(start -> right);
}


//Stream
void BST::printinitializer()
{
    Node* cursor = root;
    print(cursor, 1);
    return;
}

void BST::print(Node* start, int inlayer)
{
    if (start == NULL)
        return;

    cout << inlayer << ": " << start -> data << " " << start -> key << endl;

    if (start -> left != NULL)
        print (start -> left, inlayer + 1);

    if (start -> right != NULL)
        print (start -> right, inlayer + 1);

    return;
}

void BST::siprint(Node* item)
{
    cout << item -> data << " " << item -> key << endl;
    return;
}

void BST::read(string flnm)
{
    string newkey;
    int newdata;
    ifstream file;
    file.open(flnm);

    file >> newkey;
    file >> newdata;
    while(file)
    {
        add(newkey, newdata);
        file >> newkey;
        file >> newdata;
    }

    file.close();
    return;
}

void BST::write(string flnm)
{
    ofstream file;
    file.open(flnm);
    Node* cursor = root;

    writehelper(cursor, file);

    file.close();
    return;
}

void BST::writehelper(Node* item, ofstream& file)
{
    if (item == NULL)
        return;

    file << item -> key << " " << item -> data << "\n";

    writehelper(item -> left, file);
    writehelper(item -> right, file);
    return;
}