/*
 Class Graph is a mockup class, thus you must not assume that this is a completed implementation. 
 Please add codes/comments to complete this class and where you think there is a need.
 */
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <queue>


using namespace std;
//purpose is to create a graph object that stored data in a vector of vector of ints from an adjacency list



class Graph {
private:
    vector<vector<int> > vector_of_vertices; //vector of all data from text file
public:

    class Vertex {
    public:
        friend class Graph;

        Vertex() { //vertex class with atrribute data, isvisit, color, and swapcount
            isVisit = false;
            color = "N/A";
            swapped = 0;
        }

        Vertex(const int &t) {
            isVisit = false;
            color = "N/A";
            data = t;
            swapped = 0;
        }

        bool get_visit_status() {
            return isVisit;
        }

        string get_color() {
            return color;
        }

        int get_data() {
            return data;
        }

        void set_visit_status(bool v) {
            isVisit = v;
        }

        void set_color(string c) {
            if (c != color && color != "N/A") {
				//when swapping a color: if color has been set before and is different from the new color, add 1 to swap
                swapped += 1;
            } else {
                color = c;
            }
        }

        int get_swap_count() {

            return swapped;
        }

    private:
        bool isVisit; //tracks if a vertex is visited or not
        string color;
        int data;
        int swapped;
    };

    Graph(char* filename) {

        string line;

        ifstream infile(filename);


        while (getline(infile, line)) {

            istringstream each_line(line);
            int vertex = 0;

            vector<int> vertex_list;
            while (each_line >> vertex) { //using stringstream and >> operator to obtain each single vertex

                vertex_list.push_back(vertex);
            }

            vector_of_vertices.push_back(vertex_list);
        }

        infile.close();


    }

    ~Graph() {
    }

    // function to determine whether a graph is bipartite
    // start traverse a graph from node u
    // return true if a graph is bipartite. Otherwise, return false
    bool isBipartitePrintTraversePath(int u);
};

// function to determine whether a graph is bipartite
// start traverse a graph from node u
// return true if a graph is bipartite. Otherwise, return false

bool Graph::isBipartitePrintTraversePath(int u) {
    // add you code here
    queue<Vertex> bfs; //queue to traverse via BFS
    vector<Vertex> visit_color_list; //tracks which vertices are traversed

    for (int i = 0; i < vector_of_vertices.size(); i++) {

        visit_color_list.push_back(Vertex(vector_of_vertices[i][0]));

    }


    int start_vertex = u;

    if ((vector_of_vertices[start_vertex][0]) % 2 == 0) { //if even, color white, otherwise color black
        visit_color_list[start_vertex].set_color("WHITE");
    } else {
        visit_color_list[start_vertex].set_color("BLACK");
    }

    cout << start_vertex << "   " << visit_color_list[start_vertex].get_color() << endl;

    visit_color_list[start_vertex].set_visit_status(true);
    bfs.push(visit_color_list[vector_of_vertices[start_vertex][0]]);
    do {

        bfs.pop();
        for (int i = 1; i < vector_of_vertices[start_vertex].size(); i++) {
			
			//appropriately color each vertex. Getcolor will automatically update swapped to see if graph is bipartite
            if (visit_color_list[vector_of_vertices[start_vertex][0]].get_color() == "WHITE") {
                visit_color_list[vector_of_vertices[start_vertex][i]].set_color("BLACK");
            } else {
                visit_color_list[vector_of_vertices[start_vertex][i]].set_color("WHITE");
            }
            
            if (visit_color_list[vector_of_vertices[start_vertex][i]].get_swap_count() > 0){ //if swapped is ever > 0, not bipartite, stop traversal
                cout<<"CONFLICT: "<<visit_color_list[vector_of_vertices[start_vertex][i]].get_data()<<"  "<<visit_color_list[vector_of_vertices[start_vertex][0]].get_data()<<endl;
                cout<<"FALSE"<<endl;
                return false;
            }

            if (visit_color_list[vector_of_vertices[start_vertex][i]].get_visit_status() == false) {
                visit_color_list[vector_of_vertices[start_vertex][i]].set_visit_status(true);



                cout << visit_color_list[vector_of_vertices[start_vertex][i]].get_data() << "   " << visit_color_list[vector_of_vertices[start_vertex][i]].get_color() << endl;
                bfs.push(visit_color_list[vector_of_vertices[start_vertex][i]]); //push visited vertex in queue
            }

        }
        start_vertex = bfs.front().get_data(); //data corresponds to index so grab that value
        //cout << "Start vertex: " << start_vertex << endl;



    } while (!bfs.empty());
    
    cout<<"TRUE"<<endl; //if swap is always 0. then graph is bipartite, return true
    return true;

}
