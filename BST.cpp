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

void BST::remove(string target)
{
  //1.) Find the Target
  Node* marked = find(root, target);
  if (marked == NULL)
    {
      cout << "Item not found." << endl;
      return;
    }
  destroy(marked);
  return;
}

void BST::destroy(Node* marked)
{
  //2.) ID the Target
  //  a.) Target = Leaf
  //    i.) Change prior pointer to NULL
  //  b.) Target = Branch
  //    i.) Find a replacement leaf/Node
  //   ii.) Change prior pointer to replacement
  //  iii.) Delete or Re-direct leaf
  //  c.) Target = Root
  //    i.) Find a replacement leaf/Node
  //   ii.) Change Root to Replacement
  //  iii.) Delete or Re-direct leaf

  bool isroot = false; //If the Marked is Root, set true
  bool isleaf = true; //If the Marked is a Leaf, set true

  if (marked == root)
    isroot = true;
  else
    isroot = false;

  if (marked -> left == NULL && marked -> right == NULL)
    isleaf = true;
  else
    isleaf = false;


  //Special case exception: IsLeaf && IsRoot
  if (isleaf == true && isroot == true) //Last item in the list (Destroying the List)
    {
      root = NULL;
      delete marked;
      return;
    }

  //set paramaeters
  //  If it is a branch, we need to find a replacement variable
  //     If not, we can safely ignore it
  //  If it is !root, we need to find its parent node
  //     If not, we can set Parent to root;

  //Setup
  Node* parent; //Parent of the thing being deleted - Marked (Leaf) or Replacment (Branch)
  Node* replacement; //Replacement variable
  bool isleft; //True if Marked is the left child of Parent, False is Marked is the right child of Parent

  if (isleaf == false)
    {
      replacement = findreplacement(marked);

      parent = findparent(marked, replacement, isleft);
    }
  else
    {
      parent = findparent(root, marked, isleft);
    }

  //Setup done.
  //We've got 2 situations to consider:
  //a.) Head or Branch
  //  i.) Reolace values with Replacement
  //  ii.) Reroute Parent
  //  iii.) Delete Replacement
  //b.) Leaf
  //  i.) Reroute Parent
  //  ii.) Delete marked

  if (isleaf == false)
    {
      marked -> key = replacement -> key;
      marked -> data = replacement -> data;

      if (isleft == true)
	parent -> left = NULL;
      else
	parent -> right = NULL;

      delete replacement;
      return;
    }

  if (isleft == true)
    parent -> left = NULL;
  else
    parent -> right = NULL;

  delete marked;
  return;
}

Node* BST::findparent(Node* start, Node* marked, bool& isleft)
{
  //exit
  if (start -> left == NULL && start -> right == NULL)
    return NULL;

  if (start -> left == marked)
    {
      isleft = true;
      return start;
    }
  if (start -> right == marked)
    {
      isleft = false;
      return start;
    }
  Node* item;

  item = findparent(start -> left, marked, isleft);
  if (item != NULL)
    return item;

  item = findparent(start -> right, marked, isleft);
  if (item != NULL)
    return item;

  return NULL;
}

Node* BST::findreplacement(Node* marked)
{
  if (marked -> left != NULL)
    return max(marked -> left);

  if (marked -> right != NULL)
    return min(marked -> right);

  return marked;
}

/*
void BST::destroy(Node* marked)
{
  //2.) Identify the Target
  //  a.) Target = Head
  //    i.) Find a Replacement
  //  b.) Target = Node
  //    i.) Find a Replacement
  //  c.) Target = Leaf
  Node* placeholder;
  Node* replacement;

  bool ishead = false;
  bool isleaf = true;
  bool isleft;

  
  if (marked == root)
    {
      ishead = true;
    }
  
  if (marked -> left != NULL || marked -> right != NULL)
    {
      isleaf = false;
      
      if (marked -> right != NULL)
      {
	replacement = min(marked -> right);
      }
      else
      {
	replacement = max(marked -> left);
      }

      if(ishead == false)
	{
	  placeholder = finddagoshdangnode(root, marked);
	  
	  if (placeholder -> left != NULL)
	    isleft = true;
	  else
	    isleft = false;
	}
    }
      
  
  //3.) Destroy the Target
  //  a.) Target = Node or Root
  //    i.) isleaf = false
  //  b.) Target = Root & Leaf
  //    i.) ishead = true
  //  c.) Target = Leaf
  //    i.) ishead = false

  if (isleaf == false)
    {
      marked -> key = replacement -> key;
      marked -> data = replacement -> data;
      if (isleft == true)
	{
	  if (max(replacement) == replacement)
	    {
	      placeholder -> left = NULL;
	    }
	  else
	    {
	      placeholder -> left = replacement -> right;
	    }
	}
      else
	{
	  if (min(replacement) == replacement)
	    {
	      placeholder -> right = NULL;
	    }
	  else
	    {
	      placeholder -> right = replacement -> left;
	    }
	}
      
      delete replacement;
      return;
    }
  //We can assume that, if root is !leaf, it was already taken care of 
  if (ishead == true)
    {
      root = NULL;
    }
  else //Find the node prior
    {
      Node* replaceholder = finddagoshdangnode(root, marked);
      if (replaceholder -> left == marked)
	replaceholder -> left = NULL;
      else
	replaceholder -> right = NULL;
    }
  delete marked;
  return;
}

Node* BST::finddagoshdangnode(Node* start, Node* marked)
{
  if (start -> left == NULL && start -> right == NULL)
    return NULL;
  
  if (start -> left == marked || start -> right == marked)
    return start;

  Node* sideholder;

  if (start -> left != NULL)
    sideholder = finddagoshdangnode(start -> left, marked);

  if (sideholder -> left == marked)
    return sideholder;
  
  if (start -> right != NULL)
    sideholder = finddagoshdangnode(start -> right, marked);

  if (sideholder -> right == marked)
    return sideholder;

  
  return NULL;
}
*/
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
    int i = 0;
    while (i < inlayer)
    {
      cout << " ";
      i++;
    }
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
