#include <iostream>
#include <fstream>

using namespace std;

template <class E> class TreeNode{
public:
  TreeNode *right;
  TreeNode *left;
  E data;
  int key;

  TreeNode(){
    left = NULL;
    right = NULL;
  }

  TreeNode(int k, E d){
    data = d;
    key = k;
    left = NULL;
    right = NULL;
  }

  virtual ~TreeNode(){
    left = NULL;
    right = NULL;
  }
};

template <class E> class BST{
private:
  TreeNode<E> *root;
public:

  BST(){
    root = NULL;
  }

  //IMPLEMENT DESTRUCTOR
  virtual ~BST(){
    //delete root;
    //Build more character, need to actual delete all the nodes. Research. Could delete in the methods
    //like we did for the doubly linked list
    //Iterate and delete
  }

  void insert(int key, E data){

    TreeNode<E> *newNode = new TreeNode<E>(key, data);

    if (root == NULL){ //empty tree
      root = newNode;
    }
    else //not empty
    {
      TreeNode<E> *current = root; //Always start at root
      TreeNode<E> *parent;

      while(true)
      {
        parent = current;

        if (key < current->key)
        {
          current = current->left;
          if (current == NULL){
            //Found location for newNode
            parent->left = newNode;
            break;
          }
        }
        else{
          current = current->right;
          if (current == NULL){
            parent->right = newNode;
            break;
          }
        }
      }
    }
  }

  bool contains(int key){

    if (root == NULL){
      return false;
    }
    else{
      TreeNode<E> *current = root;
      while(current->key != key)
      {
        if (key < current->key)
        {
          current = current->left;
        }
        else{
          current = current->right;
        }
        if (current == NULL){
          return false;
        }
      }
    }
    return true;
  }

  bool deleteNode(int k)
  {

    if (root == NULL)
      return false;

    TreeNode<E> *current = root;
    TreeNode<E> *parent = root;
    bool isLeft = true;

    //Find the node that we want to delete
    //Could use our contains method
    while (current->key != k)
    {
      parent = current;
      if (k < current->key)
      {
        isLeft = true;
        current = current->left;
      }
      else
      {
        isLeft = false;
        current = current->right;
      }
      if (current == NULL) //Node doesn't exist
        return false;
    }

    //We have found the node we want to delete

    //The node is a leaf, no children
    if (current->left == NULL && current->right == NULL)
    {
      if (current == root)
      {
        root = NULL;
      }
      else if (isLeft)
      {
        parent->left = NULL;
      }
      else
      {
        parent->right = NULL;
      }
    }
    //One child
    else if (current->right == NULL) //Left child
    {
      if (current == root)
      {
        root = current->left;
      }
      else if (isLeft)
      {
        parent->left = current->left;
      }
      else
      {
        parent->right = current->left;
      }
    }
    else if (current->left == NULL)
    {
      if (current == root)
      {
        root = current->right;
      }
      else if (isLeft)
      {
        parent->left = current->right;
      }
      else{
        parent->right = current->right;
      }
    }
    //The node has two children
    else
    {
      TreeNode<E> *successor = getSuccessor(current);

      if (current == root)
      {
        root = successor;
      }
      else if (isLeft)
      {
        parent->left = successor;
      }
      else
      {
        parent->right = successor;
      }
      successor->left = current->left;
    }
    //delete current;
    return true;
  }

  TreeNode<E>* getSuccessor(TreeNode<E> *d)
  {
    TreeNode<E> *current = d->right;
    TreeNode<E> *successor = d;
    TreeNode<E> *sp = d;

    while(current != NULL)
    {
      sp = successor;
      successor = current;
      current = current->left;
    }

    if (successor != d->right) //Need to update pointers, descendant of right child
    {
      sp->left = successor->right;
      successor->right = d->right;
    }
    return successor;
  }

  //Need to switch type to E
  TreeNode<E>* getMin(){

    TreeNode<E> *current = root; //Always start at root

    if (root == NULL){
      return NULL;
    }
    while (current->left != NULL){
      current = current->left;
    }
    return current->data;
  }

  //Need to switch type to E
  TreeNode<E>* getMax(){

    TreeNode<E> *current = root;

    if (root == NULL){
      return NULL;
    }
    while (current->right != NULL){
      current = current->right;
    }
    return current->data;
  }

  E printTree(TreeNode<E> *d)
  {
    E f;
    d = root;
    return postOrderPrint(d);
  }

  E filePrintStudTree(TreeNode<E> *d)
  {
    E f;
    d = root;
    ofstream outFile;
    outFile.open("studentTable.txt");
    if (outFile.is_open())
    {
      outFile << endl;
      postOrderPrint1(d, outFile);
    }
    else{
      cout << "The student file couldn't be opened" << endl;
    }
    outFile.close();
    return f;
  }

  E filePrintFacTree(TreeNode<E> *d)
  {
    E f;
    d = root;
    ofstream outFile;
    outFile.open("facultyTable.txt");
    if (outFile.is_open())
    {
      outFile << endl;
      postOrderPrint2(d, outFile);
    }
    else{
      cout << "The faculty file couldn't be opened" << endl;
    }
    outFile.close();
    return f;
  }

  void inOrderPrint(TreeNode<E> *d)
  {
    if (d != NULL)
    {
      inOrderPrint(d->left);
      cout << d->data << endl;
      inOrderPrint(d->right);
    }
  }

  void preOrderPrint(TreeNode<E> *d)
  {
    if (d != NULL)
    {
      cout << d->data << endl;
      preOrderPrint(d->left);
      preOrderPrint(d->right);
    }
  }

  E postOrderPrint(TreeNode<E> *d)
  {
    E f;
    if (d!= NULL)
    {
      postOrderPrint(d->left);
      postOrderPrint(d->right);
      cout << d->data << endl;
    }
    return f;
  }

  void postOrderPrint1(TreeNode<E> *d, ofstream &outFile)
  {
    if (d!= NULL)
    {
      postOrderPrint1(d->left, outFile);
      postOrderPrint1(d->right, outFile);
      outFile << d->data << endl;
    }
  }

  void postOrderPrint2(TreeNode<E> *d, ofstream &outFile)
  {
    if (d!= NULL)
    {
      postOrderPrint2(d->left, outFile);
      postOrderPrint2(d->right, outFile);
      outFile << d->data << endl;
    }
  }

  E printSingle(int key)
  {
    TreeNode<E> *current = root;
    if (root == NULL){
      cout << "Coudn't find node" << endl;
    }
    else{
      while(current->key != key)
      {
        if (key < current->key)
        {
          current = current->left;
        }
        else{
          current = current->right;
        }
        if (current == NULL){
          cout << "Couldn't find node. Fatal error. Forced to exit" << endl;
          exit(0);
        }
      }
    }
    return current -> data;
    //return true;
    }

    BST operator = (const BST &obj)
    {
      return *this;
    }
};
