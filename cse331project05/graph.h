 
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <queue>
#include <map>
#include <stdlib.h>
#include <stack>


using namespace std;
//purpose is to create a graph object that stored data in a adjacency matrix


 class Vertex { //purpose is to store vertices in a transversal list to track distance(weight) and previous vertex
    public:
    
		Vertex(const double &w, const int &p, const int &i){ //index of the transversal list stored in the vertex
			weight = w;
			previous = p;
			trav_index = i;
		}
		
		Vertex(const int &i){
			weight = -1;
			previous = -1;
			trav_index = i;
			}
		
		double get_weight() const{
			return weight;
			}
			
		void set_prev(int p){
			previous = p;
			}
			
		int get_prev() const{ //const needed here to satisy the needs of priority queue
			return previous;
			}
		
		int get_index() const{
			return trav_index;
			}
		
		void set_weight(double w){
			weight = w;
			
			}	
		
		bool operator< (const Vertex &v2) const{ //need operator override for priority queue
			return weight < v2.weight;
			
			}
		bool operator> (const Vertex &v2) const{
			return weight > v2.weight;
			
			}
		
		
		
		
    private:
		double weight;
		int previous;
		int trav_index;
 
    };




class Graph { //class that stores data in a file into an adjacency matrix and finds the shortest path between two vertices
private:
    
public:

  
    Graph(char* filename, char* s, char* d) {
		int des = atoi(d);
        string line;

        ifstream infile(filename);
		int vertex_id;
		int vertex_edge;
		double edge_weight;
		priority_queue<int> pq; //priority queue used to find the highest numbered vertex -> this is the dimensions of the matrix
		
		
        while (getline(infile, line)) {

            istringstream each_line(line);
            
			each_line >> vertex_id;
			each_line >> vertex_edge;
			
			pq.push(vertex_id);
			pq.push(vertex_edge);
			
			
        }
        
        int max_size = pq.top();


		double adjacencyMatrix[max_size][max_size];
		
		for (int i =0; i <= max_size; i++){
			for (int j = 0; j <= max_size; j++){
				adjacencyMatrix[i][j] = -1; //fill matrix with -1 (this is used inplace of infinity for simplicity
				}
			}

		infile.clear();
		infile.seekg(0, ios::beg); //go back to the beginning of the file
		
		 while (getline(infile, line)) {

            istringstream each_line(line);
            
			each_line >> vertex_id;
			each_line >> vertex_edge;
			each_line >> edge_weight;
			
			adjacencyMatrix[vertex_id][vertex_edge] = edge_weight; //place appropriate data in matrix
			

        }
        
        infile.close();
       
        int source = atoi(s);
        vector<Vertex> trav; //vector that stores vertex objects -> this tracks graph traversal
        priority_queue<Vertex, vector<Vertex>, greater<Vertex>> fringe; 
        //vertices in the fringe (min priority queue) tell the program which vertex to go to next
		
		//initialization of the traversal list
        for (int i = 0; i <= max_size; i++){ //for each element in a particular row (the source row specifically)
			if(adjacencyMatrix[source][i] != -1){ //if the distance is not infinity, it is a neighbor
				trav.push_back(Vertex(adjacencyMatrix[source][i], source, i));	//set the new weight
				fringe.push(trav[i]); //push all neighbors into the fringe
				}
			else{
				trav.push_back(Vertex(i));	//if distance is infinity, store an "empty vertex" but still tracks index
				
				}
			}

	while (!fringe.empty()){
		int i = fringe.top().get_index();		
		double w = fringe.top().get_weight();
		//top of the priority queue returns minimum weight, so it tracks 
		fringe.pop(); //remove from fringe, the minimum distance has been found
			
		for (int j = 0; j <= max_size; j++){
			if(adjacencyMatrix[i][j] != -1){ //for each neightbor of min elemenet
				if (trav[j].get_weight() == -1){ //if distance in traversal list is infinity
					trav[j].set_weight(w + adjacencyMatrix[i][j]);//set the new weight
					trav[j].set_prev(i);//set the previous vertex, which is the index
					fringe.push(trav[j]);//since it is a neighbor, push to the fringe
					}
				else{//if weight is already set
					if ((w + adjacencyMatrix[i][j]) < trav[j].get_weight()){//compare new weight vs. old weight
							trav[j].set_weight(w + adjacencyMatrix[i][j]);//if lower, set the new weight as weight
							trav[j].set_prev(i);//since weight is changed, set the previous vertex as index
					 
						}
		
					}
				
				}
		}
		
		
    }
	
	double distance = trav[des].get_weight();
	if(distance != -1){ //if distance is not infinity in traversal list, a path exists between source and destination
		stack<int> trav_stack;
		trav_stack.push(des); //add to the stack the destination vertex
		
		
		while (des!= source){ //add to the stack the previous vertex until the source vertex is found
			trav_stack.push(trav[des].get_prev());
			des = trav[des].get_prev();
		}
		
		while (!trav_stack.empty()){ //pop back the stack to get the order
			cout<<trav_stack.top();
			trav_stack.pop();
			if(!trav_stack.empty()){
				cout<<"->";
				}
			}
		
		printf("  %.2f\n", distance); //print distance with 2 decimal significant figures
		
	}
	else{
		cout<<"NO PATH FOUND"<<endl; //if distance is inifinity, a path does not exist
		}	
}

    ~Graph() {
    }

    
};



