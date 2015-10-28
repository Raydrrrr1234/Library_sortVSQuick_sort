//
//  quick_sort.cpp
//  CS583
//
//  Created by kang on 11/22/14.
//  Copyright (c) 2014 kang. All rights reserved.
//

#include "quick_sort.h"

int qui_clock_count;

int partition(int * data_int, int start, int end)
{
    int x = data_int[end];
    int i = start-1;
    int tmp;
    
    for (int j = start; j < end; j++) {
        qui_clock_count++;
        if (data_int[j] < x) {
            i++;
            tmp = data_int[i];
            data_int[i] = data_int[j];
            data_int[j] = tmp;
        }
    }
    data_int[end] = data_int[i+1];
    data_int[i+1] = x;
    return i+1;
}

void QUICKSORT(int * data_int, int start, int end)
{
    int mid;
    if (start < end) {
        qui_clock_count++;
        mid = partition(data_int,start,end);
        QUICKSORT(data_int, start, mid-1);
        QUICKSORT(data_int, mid+1, end);
    }
}

void quickSort(int * data_int, int data_size, char fileName[])
{
    int * sorted_array,k;
    
    sorted_array = (int *)malloc(sizeof(int)*data_size);
    memcpy(sorted_array, data_int, sizeof(int)*data_size);
    
    clock_t start, end;

    start = clock();
    
    qui_clock_count = 0;
    
    QUICKSORT(sorted_array, 0, data_size-1);
    
    end = clock();
    
    cout << "Quick sort time:" << float(end - start)/CLOCKS_PER_SEC << endl;
    cout << "Quick sort clock:" << qui_clock_count<<endl<<endl;
    
    ofstream out(fileName);
    if (fileName != NULL)
    for (k = 0; k < data_size; k++) {
        out << sorted_array[k] << " ";
    }
    
    out.close();
    free(sorted_array);
}