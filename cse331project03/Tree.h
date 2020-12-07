#ifndef CTREE_H
#define CTREE_H

#include <iostream>

template<class T> class CTree
{
public:
    CTree() {m_root = 0;}
    ~CTree() {delete m_root;}

    //
    // class Node
    // The nested node class for objects in our tree.
    //

    class Node 
    {
    public:
        friend class CTree;

        Node() {m_ll = 0;  m_rl = 0;}
        Node(const T &t) {m_number = t;  m_ll = 0;  m_rl = 0;}
        ~Node() {delete m_ll;  delete m_rl;}

        T &Data() {return m_number;}
        const T &Data() const {return m_number;}

    private:
        Node    *m_ll;
        Node    *m_rl;
        T       m_number;

    };

    void Insert(const T &t) { //overload the function to have pointer to a node
        Node*& current = m_root;
        Insert(t, current);
    }
    
    void Insert(const T &t, Node*& current_node){
        if(current_node != NULL){ //as long as node not null, keep traversing
            if(t < current_node->Data()){
                Insert(t, current_node->m_ll); //recursive call
            }
            else{
                Insert(t, current_node->m_rl);
            }
            
            
        }
        else{ //once node is finally node, create a new node and insert it
            current_node = new Node(t);
            //std::cout<<"Created Root: "<<current_node->Data();
        
        }
    
    }
    

    void Preorder(std::ostream &p_str) { //overload the function have node pointer

        Node* current = m_root;
        Preorder(p_str, current);
      
    }
    
    void Preorder(std::ostream &p_str, Node* current_node){
        p_str << current_node->Data() << "    "; //4 spaces as shown in example output
        if (current_node->m_ll != NULL){
            Preorder(p_str, current_node->m_ll); //recursive call for each subtree
        }
        if (current_node->m_rl != NULL){
            Preorder(p_str, current_node->m_rl);
        }
    
    }
    
    T max_of_two(const T &t1, const T &t2){ //simple templated fucntion to find the max of 2 values
        if (t1 >= t2){return t1;}
        if (t2 > t1){return t2;}
    
    }
    
    int Depth() { //overload to take a node pointer
        Node* current = m_root;
        
        return Depth(current);
    }
    
    int Depth(Node* current_node){
        
        if (current_node == NULL){return 0;} //if node has not kids return 0
        else{
            int count = 1; //if node exists at the level, return 1 for height
            int total = max_of_two(Depth(current_node->m_ll), Depth(current_node->m_rl));
            //add the height to the recursive call of max depth of the subtree
            return (total + count); //return these combined values
        }
        
    
    }

    const Node *Find(const T &t) const {//overload to take a node pointer
        Node*& current = m_root;
        return Find(t, current);
    
    
    }
    
    
    const Node *Find(const T &t, Node*& current_node ) const {
        if (current_node == NULL) {return current_node;} //node does not exist in tree
        else{
            if(t < current_node->Data()){
                Find(t,current_node->m_ll); //keep traversing list until found
             }
            else if(t > current_node->Data()){
                Find(t, current_node->m_rl);
             }
            else{
                return current_node;
             }
        }
     
     
     }
    
    
    Node *Find(const T &t) { //exact replica of the const Node*Find function
        Node*& current = m_root;
        return Find(t, current);

    }
    
    Node *Find(const T &t, Node*& current_node ){
        if (current_node == NULL) {return current_node;}
        else{
            if(t < current_node->Data()){
                Find(t,current_node->m_ll);
             }
            else if(t > current_node->Data()){
                Find(t, current_node->m_rl);
             }
            else{
                return current_node;
             }
        }
     
     }

    T deletemin(Node*& current_node){ 
        //subfunction that deletes the smallest value in a tree and returns its payload
        T temp_data;
        if(current_node != NULL){
            if (current_node->m_ll == NULL){//node has no left children so its min
                temp_data = current_node->Data();
                current_node = current_node->m_rl; //point to the right subtree
            }
            else{//node has a left child
                temp_data = deletemin(current_node->m_ll);
            }
            return temp_data;
        }
    }
    
   
    void Delete(const T &t) //overload to take an extra node pointer
    {
        Node*& current = m_root;
        Delete(t, current);    
    }
    
    void Delete(const T &t, Node*& current_node)
    {
        if(current_node != NULL){ //can't delete what doesn't exist
            if(t < current_node->Data()){ //Find the node via recursive call similar to function Find
                Delete(t, current_node->m_ll);
            }
            else if( t > current_node->Data()){
                Delete(t, current_node->m_rl);
            }
            else{//found node to delete
                if ((current_node->m_ll == NULL) & (current_node->m_rl == NULL)){
                    //if node to delete has no children
                    current_node = NULL;
                }
                else{//node must have 1 or 2 children
                    Node* temp = current_node;
                    if(current_node->m_rl == NULL){//only has left child
                        current_node = current_node->m_ll; //replace empty spot with left child
                        temp = NULL;
                    }
                    else if(current_node->m_ll == NULL){//only has right child
                        current_node = current_node->m_rl; //replace empty spot with right child
                        temp = NULL;
                    }
                    else{//must have 2 children
                        T data = deletemin(current_node->m_rl); 
                        //delete and replace lowest value of right subtree with current position on tree
                        current_node->Data() = data;

                    }

                }
            }
        }
        
    }

private:
    Node *m_root;


};


#endif
