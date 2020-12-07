//
// Name :        main.cpp
// Description :  skeleton program that needs to be completed by InsertionSort.h, QuickSort.h and VerifySort.h
//

#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
#include "InsertionSort.h"	 // Edit your insertion sort code in that file
#include "QuickSort.h"		 // Edit your quick sort code in that file
#include "VerifySort.h"		 // Edit your code for verifying sort result in that file
#include <fstream>
#include <time.h>
using namespace std;

int main(int argc, char * argv[]) {
	
	if ( argc != 2 ) {
        cout<<"usage: "<< argv[0] <<" <filename>\n";
    	return 0;
	}
	ifstream infile(argv[1]);
    // check to see if file opening succeeded
    if ( !infile.is_open() ) {
        cout<<"Could not open file\n";
        return 0;
	}
	time_t t1 = 0;
    vector<int> x,y;
    //read input
    int input_t;
    while( infile >> input_t) {
    	x.push_back(input_t);
    	y.push_back(input_t);
    }

//  quick sort
	t1 = time(0);
    long long compCount = quickSort(x); 
    t1 = time(0)-t1;
    cout << x.size() << endl;
    cout << "quick sort \ncomparisons: " << compCount <<endl;
    cout << "time: " << t1 << endl; 
        cout << (verifySort(x)? "Success \n":"Fail\n");
  
//  insertion sort
	t1 = time(0);
    compCount = insertionSort(y); 
    t1 = time(0)-t1;
    cout << "insertion sort \ncomparisons: " << compCount <<endl;
    cout << "time: " << t1 << endl; 
    cout << (verifySort(y)? "Success \n":"Fail\n");

	infile.close();
    return 0;
}


