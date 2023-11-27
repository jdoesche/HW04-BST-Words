#include <iostream>
using namespace std;
#include "BST.h"

//Con-/De-structors
BST()
{ root = NULL; }

~BST()
{
    while (root != NULL)
    {
        destroy(root);
    }
}

//Setup
void add(string newkey, int newdata)
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
        Node* hold = root;
        root = NEWMANN;
        NEWMANN -> left = hold -> left;
        NEWMANN -> right = hold -> right;
        delete hold;

        return;
    }

    //Case C: Newuser != HEAD
    Node* cursor = root;
    addhelper(cursor, NEWMANN);
    return;
}

void addhelper(Node* item, Node* NEWMANN);
{
    //If the Datas match
    if (item -> data == NEWMANN -> data)
    {
        Node* hold = item;
        item = NEWMANN;
        NEWMANN -> left = hold -> left;
        NEWMANN -> right = hold -> right;
        delete hold;
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

void remove(string target)
{
    Node* cursor = head;
    Node* item = find(cursor, target);
    if (item == NULL)
    {
        cout << "Item not found." << endl;
        return;
    }
    destroy(item);
    return;
}

void destroy(Node* item)
{
    Node* cursor;
    
    cursor = replacementsearch(item);
    if (item == root)
    {
        if (cursor == item)
            root = NULL;
    }
    if (cursor != item)
    {
        item -> data = cursor -> data;
        item -> key = cursor -> key;
    }

    delete(cursor);

    return;
}

Node* replacementsearch(Node* item)
{
    //Case 1: Both are NULL
    if (item -> left == NULL && item -> right == NULL)
        return item;

    //Case 2: Max in Null
    if (item -> right == NULL)
        return max(item -> left);

    return min(item -> right);
}

//Search
Node* find(Node* start, string param)
{
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

Node* minmax()
{
    return root;
}

Node* min(Node* start)
{
    if (start -> left == NULL)
        return start;

    return min(start -> left);
}

Node* max(Node* start);
{
    if (start -> right == NULL)
        return start;

    return max(start -> right);
}


//Stream
void printinitializer()
{
    Node* cursor = root;
    print(cursor, 1)
    return;
}

void print(Node* start, int inlayer)
{
    if (start == NULL)
        return;
    cout << inlayer << ": " << start -> data << " " << start -> key << endl;

    if (start -> left != NULL)
        print (start -> left, inlayer + 1)

    if (start -> right != NULL)
        print (start -> right, inlayer + 1)

    return;
}

void siprint(Node* item)
{
    cout << item -> data << " " << item -> key << endl;
    return;
}

void read(string flnm)
{
    int newkey;
    string newdata;
    ifstream file;
    file.open(flnm);
    
    while(file)
    {
        file >> newkey;
        file >> newdata;
        add(newkey, newdata);
    }

    file.close();
    return;
}

void write(string flnm);
{
    ofstream file;
    file.open(flnm);
    Node* cursor = head;

    writehelper(cursor, file);

    file.close();
    return;
}

void writehelper(Node* item, ofstream file);
{
    if (item == NULL)
        return;

    file << item -> key << " " << item -> data << "\n";

    writehelper(item -> left, file);
    writehelper(item -> right, file);
    return;
}