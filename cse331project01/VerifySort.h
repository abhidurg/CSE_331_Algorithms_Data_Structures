/* 
 * File:   VerifySort.h
 * Author: Abhiram Durgaraju
 *
 * Created on September 24, 2017, 8:20 PM
 */
#ifndef _VERIFYSORT_H_
#define _VERIFYSORT_H_
#include <vector>
using namespace std;

/*this function takes a vector refernce as input and passes true or false
based on if or not the function is sorted*/
bool verifySort(vector<int> sorted_or_not){
    bool sorted = true;
    for (int i=1; i <= sorted_or_not.vector::size()-1; i++){
        //cout<<sorted_or_not[i]<<endl;
        if (sorted_or_not[i] < sorted_or_not[i-1]){
            return false; 
            //if ever the current is less than the prior element return false 
        }
    
    }
    
    return sorted;
    //else, return true
}

#endif

