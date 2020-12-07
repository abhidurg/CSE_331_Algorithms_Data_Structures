/* 
 * File:   InsertionSort.h
 * Author: Abhiram Durgaraju
 *
 * Created on September 24, 2017, 8:22 PM
 */

#ifndef _INSERTIONSORT_H_
#define _INSERTIONSORT_H_
#include <vector>
using namespace std;

/*this function takes a vector reference, sorts it, and returns the
 number of comparisons that were made*/
long insertionSort(vector<int>& vector_to_sort){
    long count = 0; //tracks the comparison count
    for (int i = 1; i <= vector_to_sort.vector::size() - 1; i++){
        int p = i-1; 
        //^the index prior the the element compared, before which all is sorted
        int temp_value = vector_to_sort[i]; //store current value in temp
        while (p >= 0 && temp_value < vector_to_sort[p]){
            /*iterate only when the index p is in bound and when current value
            is greater that stored temp*/
            vector_to_sort[p+1] = vector_to_sort[p];
            //shift each element by 1
            p -= 1;
            //decrement the p index since the comparison is done backwards
            count += 1;
            //since a comparison was made, add 1 to count
        }
        vector_to_sort[p+1] = temp_value;
        /*when the value at p index is finally smaller than curent value at
        i index, then replace the next value with the temp value
        this serves to complete a swap*/
    }
    return count;
}
#endif
