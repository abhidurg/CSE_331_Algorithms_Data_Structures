//
// Name :         RevList.h
// Description :  Simple doubly linked list with reversing feature.
//

#ifndef REVLIST_H
#define REVLIST_H
//#include <iostream>
//using namespace std;
template<class T> class CRevList
{

public:
  // Constructor.  Sets to an empty list.
  CRevList() 
  //initialize the first and last pointers to NULL since list is empty
  {first = NULL;
   last = NULL;
   size = 0;
   list_reverse = false;
  }

  // Destructor.  Deletes everything in the list.
  ~CRevList()
  //call Clear, reset first and last pointers to NULL since list empty
  {Clear();
   first = NULL;
   last = NULL;
   size = 0;
   list_reverse = false;
  }

  // Copy constructor.  Copies another list.
  CRevList(const CRevList &b)
  {//create a deep copy using "new" Node pointer
	  Node temp = new Node*;
	  temp = first;
	  for (int i=0; i < size; i++){
		  b.PushBack(temp);
		  temp = temp->m_next;
	  //using pushback or pushfront each node can be added
	  }
  }

  // Assignment operator.  Copies another list.
  void operator=(const CRevList &b);

  // Clear the list.
  void Clear()
  //size is being tracked as a private variable, += 1 every pushback
  {for(int i = 0; i < size; i++){PopBack();}
  }


  //
  // class Node
  // The nested node class for objects in our linked list.
  //
  // YOU MAY NOT MODIFY THIS CLASS!
  class Node 
  {
  public:
    friend class CRevList;
  
    Node() {m_next = 0;  m_prev = 0;}
    Node(const T &t) {m_payload = t;  m_next = 0;  m_prev = 0;}
  
    T Data() {return m_payload;}
    const T Data() const {return m_payload;}
  
  private:
    Node    *m_next;
    Node    *m_prev;
    T       m_payload;
  };
  
  // Determines if the list is empty
  bool IsEmpty() const {
	  if (size != 0){return false;}
	  else {return true;}
	  }

  //methods to add data to the front or the back of the list
  void PushFront(const T &t) {
	  Node* temp = new Node(t); //create a node with value t
	  if (list_reverse == false){ //Do PushFront if list is normal
		  if (size == 0){
			  //if list is empty, new node should be first and last
			  first = temp;
			  last = temp;
			  first->m_next = last;
			  first->m_prev = last;
			  last->m_prev = first;
			  last->m_next = first;}
		  else if (size == 1){
			  //if list has 1 node, new node should be put before first
			  temp->m_next = last;
			  temp->m_prev = last;
			  last->m_next = temp;
			  last->m_prev = temp;
			  first = temp;
			  }
		  else{//else do the normal logic
			  temp->m_next = first;
			  temp->m_prev = last;
			  last->m_next = temp;
			  first->m_prev = temp;
			  first = temp;
			  }
		  size += 1; //increase the size everytime a node is added
		}
	  else{
		  list_reverse = false;
		  /*if list is reversed, call PushBack instead of PushFront.
		  First need to temporarily tag list_reverse as false so that
		  PushFront and PushBack don't infinately loop each other*/
		  PushBack(t);
		  list_reverse = true;
		  //need to make list_reverse true again because it was changed
		  }
	  }
  void PushBack(const T &t) {
	  Node* temp = new Node(t);
	  if (list_reverse == false){ //Do PushBack if list is normal
		  if (size == 0){
			  //if list is empty, new node should be first and last
			  first = temp;
			  last = temp;
			  first->m_next = last;
			  first->m_prev = last;
			  last->m_prev = first;
			  last->m_next = first;}
		  else if (size == 1){
			  //if list has 1 node, new node should be put before first
			  temp->m_prev = first;
			  temp->m_next = first;
			  first->m_next = temp;
			  first->m_prev = temp;
			  last = temp;
			  first = last->m_prev;
			  }
		  else{//else do normal logic
			  first->m_prev = temp;
			  temp->m_next = first;
			  temp->m_prev = last;
			  last->m_next = temp;
			  last = temp;
			  first = temp->m_next;
			  }
		  size += 1;//increase the size everytime a node is added
		  }  
	  else{
		  /*if list is reversed, call PushFront instead of PushBack.
		  First need to temporarily tag list_reverse as false so that
		  PushFront and PushBack don't infinately loop each other*/
		  list_reverse = false;
		  PushFront(t);
		  list_reverse = true;
		  //need to make list_reverse true again because it was changed
		  } 
	  }
  void PopFront() { //similar structure to PushBack and PushFront
	  if (list_reverse == false){
		  if (size != 0){ //Only PopFront or PopBack if list non-empty
			  if (size == 1){
					first = NULL;
					last = NULL; 
				  }
			  else if (size == 2){
				  last->m_next = last;
				  last->m_prev = last;
				  first = last;
				  }
			  else{
				  last->m_next = first->m_next;
				  first->m_next->m_prev = last;
				  first = first->m_next;
				  }
			  size -= 1;}//decrease size by 1 since a node is removed
	       }
	   else{
		   list_reverse = false;
		   PopBack();
		   list_reverse = true;
		   }   
	  }
  void PopBack() {//similar structure to PushBack and PushFront
	   if (list_reverse == false){
		   if (size != 0){//Only PopFront or PopBack if list non-empty
			  if (size == 1){
					first = NULL;
					last = NULL; 
				  }
			  else if (size == 2){
				  first->m_next = first;
				  first->m_prev = last;
				  last = first;
				  }
			  else{
				  last->m_prev->m_next = first;
				  first->m_prev = last->m_prev;
				  last = last->m_prev;}
			 size -= 1;}//decrease size by 1 since a node is removed
		    }
		else{
			list_reverse = false;
		    PopFront();
		    list_reverse = true;
			}
	  }

  //Get a pointer to the first node in the list
  const Node *Begin() const {
	  //if reversed return last node instead of first
	  if(list_reverse == false){
		return this->first;
		}
	  else{
		  return this->last;
		  }
	  }
  Node *Begin() {
	  if (list_reverse == false){
		  return this->first;
		  }
	  else{
		  return this->last;
		  }
	  }

  //get a pointer to the last node in the list
  const Node *End() const {
	  //if reversed return first node instead of last
	  if (list_reverse == false){
		  return this->last;
		  }
	  else{
		  return this->first;
		  }
	  }
  Node *End() {
	  if (list_reverse == false){
		  return this->last;
		  }
	  else{
		  return this->first;
		  }
	  }

  //get a pointer to node next in the list
  const Node *Next(const Node *n) const {
		Node* temp = new Node();
		//if reversed, return previous node instead of next node
		if (list_reverse == true){
				temp = n->m_prev;}
		else{
			temp = n->m_next;}
		return temp;
		}
  Node *Next(const Node *n) {
	  Node* temp = new Node();
		if (list_reverse == true){
				temp = n->m_prev;}
		else{
			temp = n->m_next;}
		return temp;
	  }

  //Find a node with the specified key
  const Node *Find(const T &t) const {
	  Node * find_node = new Node();
	  find_node = first;
	  /*for each node in the list of some size, go through each node
	  until the node's payload matches the supplied value*/
	  for (int i = 0; i < size; i++){
		  if (find_node->m_payload == t){
			  return find_node;}
		  else{
			  find_node = find_node->m_next;}
	  
	    }
	}
  Node *Find(const T &t) {
	  Node * find_node = new Node();
	  find_node = first;
	  for (int i = 0; i < size; i++){
		  if (find_node->m_payload == t){
			  return find_node;}
		  else{
			  find_node = find_node->m_next;}
	    }
	  }

  //Delete the given node
  void Delete(Node *n){
	  //since the first node and last node are special cases, they have
	  //their own if conditions
	  if (n == first){
		  first = n->m_next;
		  first->m_prev = last;
		  last->m_next = first;
		  }
	  else if (n == last){
		  last = n->m_prev;
		  first->m_prev = last;
		  last->m_next = first;	  
		  }
	  else{
		  n->m_prev->m_next = n->m_next;
		  n->m_next->m_prev = n->m_prev;
		  }
	  delete n; //remove the actual node after pointers have rearranged
	  size -= 1; //decrease the size
	  }

  //Reverse the list in O(1) time
  void Reverse() {
	  //flip the variable list_reverse everytime this is called
	  if (list_reverse == true){
		  list_reverse = false;}
	  else if (list_reverse == false){
		  list_reverse = true;}
	  }


private:

  //NOTE: you may add any private member variables or 
  //      methods you need to complete the implementation

  //Node    m_head;             // Head node
  Node *first; //first node
  Node *last;  //last node
  unsigned size; //size of linked list
  bool list_reverse; //tracks if the list is reversed
};

// Assignment operator.  Copies another list.
template<class T> void CRevList<T>::operator=(const CRevList<T> &b)
{}

//template<class T> (CRevList<T>::Node *) CRevList<T>::Begin1() {return m_reverse ? m_head.m_prev : m_head.m_next;}


#endif
