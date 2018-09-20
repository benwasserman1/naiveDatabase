#include <iostream>
#include <string>

using namespace std;

template <class E> class ListNode
{
public:
  ListNode *next;
  ListNode *prev;
  E data;
//   ListNode();
//   ListNode(int data);
//   ~ListNode();
// };

  ListNode()
  {
    next = NULL;
    prev = NULL;
  }

  ListNode(E d)
  {
    data = d;
    next = NULL;
    prev = NULL;
  }

  ~ListNode(){
    next = NULL;
    prev = NULL;
  }
};

// template <class E>
// class List{
// protected:
//   // ListNode<E> *front;
//   // ListNode<E> *back;
//   // unsigned int size;
//   virtual void insertFront(E d);
//   virtual void insertBack(E d);
//   virtual E removeFront();
//   virtual E removeBack();
//   virtual E remove(int key);
//   virtual void printList();
//   virtual int find(E value);
//   virtual E deletePos(int pos);
// };


template <class E>
class DoublyLinkedList //: protected List
{
private:
  ListNode<E> *front;
  ListNode<E> *back;
  unsigned int size;

public:
//   DoublyLinkedList();
//   ~DoublyLinkedList();
//   void insertFront(int data);
//   void insertBack(int data);
//   int removeFront();
//   int removeBack();
//   int remove(int key);
//   void printList();
//   int deletePos(int pos);
//   int find (int value);
//   bool insertAfter(int pos, int val);
//   bool isEmpty();
//   unsigned int getSize();
// };



  DoublyLinkedList()
  {
    size = 0;
    front = NULL;
    back = NULL;
  }

  ~DoublyLinkedList()
  {
    //cout << "Object deleted" << endl;
    ListNode<E> *curr = front;
    ListNode<E> *temp = front;
    while(curr != NULL){
      curr = curr -> next;
      temp = curr;
      //delete curr;
      curr = temp;
    }
    delete curr;
    delete temp;
    front = NULL;
    back = NULL;
  }

  E checkFront(){
    ListNode<E> *node = front;
    return node-> data;
  }

  void insertFront(E d)
  {
    ListNode<E> *node = new ListNode<E>(d);
    if (size == 0)
    {
      back = node;
    }
    else
    {
      front -> prev = node;
      node -> next = front;
    }
    front = node;
    ++size;
  }

  void insertBack(E d)
  {
    ListNode<E> *node = new ListNode<E>(d);

    if (size == 0){
      front = node; //think about this..
    }
    else{
      back -> next = node;
      node -> prev = back;
    }
    back = node;
    ++size;
    //scout << "Made it here" << endl;
  }

  E removeFront()
  {
    ListNode<E> *node = front;
    if (front -> next == NULL)
    {
      back = NULL;
    }
    else
    {
      front -> next -> prev = NULL;
    }
    front = front -> next;
    --size;
    node-> next = NULL;
    E temp = node-> data;

    //delete node;
    //node = NULL;
    return temp;
  }

  E removeBack()
  {
    ListNode<E> *node = back;
    if (back -> prev == NULL)
    {
      front = NULL;
    }
    else
    {
      back -> prev -> next = NULL;
    }
    back = back -> prev;
    --size;
    node -> prev = NULL;
    E temp = node-> data;

    delete node;
    return temp;
  }

  E remove(int key)
  {
    ListNode<E> *curr = front;

    while(curr->data != key)
    {
      curr = curr-> next;
      if (curr == NULL){
        return 0;
      }
    }
    //found it - now let's delete it
    if (curr == front)
    {
      //removeFront();
      front = curr-> next;
    }
    else
    {
      curr->prev->next = curr-> next;

    }
    if (curr == back)
    {
      //removeBack();
      back = curr-> prev;
    }
    else{
      curr-> next-> prev = curr-> prev;
    }

    curr -> next = NULL;
    curr -> prev = NULL;
    --size;

    E temp = curr -> data;
    //delete curr;
    //curr = NULL;

    return temp;
  }

  string printList() const
  {
    ListNode<E> *curr = front;
    string list;

    while(curr)
    {
      list += to_string(curr -> data) + ", ";
      curr = curr -> next;
    }
    return list;
  }

  //Doesn't find all instances at this point
  int find(E value)
  {
    int idx = -1;
    ListNode<E> *curr = front;

    while(curr!=NULL) //while current is not equal to null or while the size is empty
    {
      ++idx;
      if (curr->data == value)
      {
        break;
      }
      else{
        curr = curr->next;
      }
    }
    if (curr == NULL)
      idx = -1;

    return idx;
  }

  bool insertAfter(int pos, int value)
  {
    return true;
  }

  E deletePos(int pos)
  {
    int idx = 0;
    ListNode<E> *curr = front;
    ListNode<E> *prev = front;

    while(idx != pos) //while the index isn't equal to the position we're looking for
    {
      prev = curr;
      curr = curr->next;
      idx++;
    }
    //found it
    prev->next = curr->next;
    curr->next = NULL;
    E d = curr->data;
    size--;

    delete curr;
    return d;

  }

  int getSize()
  {
    return size;
  }
};
