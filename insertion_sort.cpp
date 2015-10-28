//
//  insertion_sort.cpp
//  CS583
//
//  Created by kang on 11/22/14.
//  Copyright (c) 2014 kang. All rights reserved.
//

#include "insertion_sort.h"


int ins_clock_count;

void insertionSort(int * data_int, int data_size, char fileName[])
{
    int * sorted_array, i, j, k, tmp;
    
    sorted_array = (int*) malloc(sizeof(int)*data_size);
    memcpy(sorted_array, data_int, sizeof(int)*data_size);
    
    clock_t start, end;
    
    start = clock();
    ins_clock_count = 0;
    
    for (j = 1; j < data_size; j++) {
        ins_clock_count++;
        tmp = sorted_array[j];
        i = j - 1;
        while (i >= 0 && sorted_array[i] > tmp) {
            ins_clock_count++;
            sorted_array[i+1] = sorted_array[i];
            i--;
        }
        sorted_array[i+1] = tmp;
    }
    end = clock();
    cout << "Insertion sort time:" << float(end - start)/CLOCKS_PER_SEC<< endl;
    cout << "Insertion sort clock:" << ins_clock_count<< endl<< endl;
    
    ofstream out(fileName);
    if (fileName != NULL)
    for (k = 0; k < data_size; k++) {
        out << sorted_array[k] << " ";
    }
    
    out.close();
    free(sorted_array);
}
