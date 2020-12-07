/* 
 * File:   QuickSort.h
 * Author: Abhiram Durgaraju
 *
 * Created on September 24, 2017, 8:56 PM
 */

#ifndef _QUICKSORT_H_
#define	_QUICKSORT_H_
#include <vector>
#include "InsertionSort.h"
#include <cstdlib>

using namespace std;

/*This function takes 3 inputs: the vecfor reference, the starting index, and
 the ending index of the vector. It then returns count, the number of
 comparisons that were made in the sorting process*/
long quickSort(vector<int>& vector_to_sort, int start_index, int end_index){
    long count = 0; //this tracks the # of comparisons
    if (start_index < end_index){ //quicksort ONLY if the indexes are in range
        int pivot_index = (rand()% (end_index-start_index)) + start_index;
        //cout<<"pivot_index"<<pivot_index<<endl;
        int pivot = vector_to_sort[pivot_index]; //choose 1st # as pivot
        int partition_index = start_index; //The index before this is partitioned
        swap (vector_to_sort[pivot_index], vector_to_sort[end_index]);
        //swap the pivot with the last element
        for (int i = start_index; i <= end_index - 1; i++){
            //for all indices except the last (the pivot after swapped)
            if (vector_to_sort[i] <= pivot){
                swap(vector_to_sort[i], vector_to_sort[partition_index]);
                partition_index += 1;   //increment the current partition    
            }
        }
        swap (vector_to_sort[end_index], vector_to_sort[partition_index]);
        //swap the pivot, which is at the end, with the current partition
        
        count += (end_index - start_index) -1;
        //add m-1 to the count where m is the size of the subarray
        count += quickSort(vector_to_sort, start_index, partition_index -1 );
        count += quickSort(vector_to_sort, partition_index+1, end_index);
        //recursive call to quicksort and add those counts as well
    }
    return count;
}


/*This function takes a vector reference and passes it through another quicksort
function that 3 variables as input */
long quickSort(vector<int>& vector_to_sort){
        int start_index = 0;
	int end_index = vector_to_sort.vector::size() -1;
	long count = quickSort(vector_to_sort, start_index, end_index);
	return count;
}

#endif	/* QUICKSORT_H */

