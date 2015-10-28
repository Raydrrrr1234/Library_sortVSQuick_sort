
//
//  library_sort.cpp
//  CS583
//
//  Created by kang on 11/22/14.
//  Copyright (c) 2014 kang. All rights reserved.
//

#include "library_sort.h"

int EPSILON;
int lib_clock_count;

/*
 * uncommon operation move left
 */
void moveLeft(int * array, int pos)
{
    if (array[pos-1] != NIL) {
        moveLeft(array, pos-1);
    }
    array[pos-1] = array[pos];
}
/*
 * common operation move right
 */
int moveRight(int * array, int pos, int range)
{
    /* fail to move right */
    if (array[pos] == NIL) {
        return 1;
    }
    if (pos+1 >= range) {
        return 0;
    }
    
    
    if (moveRight(array, pos+1, range)) {
        array[pos+1] = array[pos];
        return 1;
    }
    else return 0;
}

/* insert operation in article */
void insertPos(int * array, int pos, int * o_array, int o_pos, int range)
{
    if (array[pos] == NIL) {
        array[pos] = o_array[o_pos];
    }
    else{
        if (moveRight(array, pos, range)) {
            array[pos] = o_array[o_pos];
        }
        else{
            moveLeft(array, pos-1);
            array[pos-1] = o_array[o_pos];
        }
    }
}

int binarySearchLib(int * e_array, int next_element, int start, int end)
{
    int i;
    if (end-start <= 2*(1+EPSILON)) {
        if (e_array[end-1] != NIL) {
            for (i = end-1; i >= start; i--) {
                if (e_array[i] < next_element)
                {
                    if(e_array[i] != NIL)
                        return i+1;
                }
            }
        }
        else {
            for (i = start; i < end ; i++) {
                if (e_array[i] >= next_element || e_array[i] == NIL) {
                    return i;
                }
            }
        }
    }
    else {
        if (e_array[(start+end)/2] > next_element) {
            return binarySearchLib(e_array, next_element, start, (start+end)/2);
        }
        else {
            return binarySearchLib(e_array, next_element, (start+end)/2, end);
        }
    }
    return -1;
}

/*
 * e_array = expansion_array
 * range is the expanded range
 */
int findPosition(int * e_array, int next_element, int range)
{
    return binarySearchLib(e_array, next_element, 0, range);
}
/*
 * rebalance operation
 */
void rebalance(int * array, int range)
{
    int i = range/2-1;
    int new_pos=range - (2+2*EPSILON);
    while (i >= 0 && new_pos > i) {
        lib_clock_count++;
        if (array[i] != NIL) {
            array[new_pos] = array[i];
            array[i] = NIL;
            new_pos -= (2+2*EPSILON);
            
        }
        i--;
    }
}
/*
 * epsilon control the size of expansion array
 *
 */
void librarySort(int * data_int, int data_size, char fileName[])
{
    int *expansion_array;
    int i;     /* Round */
    int range; /* Range the number inserted every round in original array */
    int expanded_range;
    int intercalated;
    int supported;
    int pos;
    int next;
    int k;

    
    clock_t start, end;
    
    cout << "Library sort need a EPSILON:";
    cin >> EPSILON;
    
    expansion_array = (int*) malloc(sizeof(int)*(data_size)*(1+EPSILON));
    memset(expansion_array, NIL, sizeof(int)*(data_size)*(1+EPSILON));
    
    next = intercalated = supported = i = 0;
    range = 1;
    expanded_range = range * (1+EPSILON);
    start = clock();
    lib_clock_count = 0;
    
    while (range < data_size) {
        lib_clock_count++;
        
        if (supported != 0) {
            /* expand the array */
            if(range*2 < data_size){
                range *= 2;
                expanded_range *= 2;
                rebalance(expansion_array, expanded_range);
            }
            else {
                range = data_size;
            }
            
            while (next < range) {
                lib_clock_count++;
                pos = findPosition(expansion_array, data_int[next] ,expanded_range);
                lib_clock_count++;
                if (pos == -1) {
                    printf("binary sort error!");
                }
                insertPos(expansion_array, pos, data_int, next, expanded_range);
                lib_clock_count++;
                next++;
                /*
                for (k = 0; k < expanded_range; k++) {
                    cout << expansion_array[k] << " ";
                }
                cout << endl;
                 */
            }
            
        }
        else{
            expansion_array[next] = data_int[next];
            next++;
        }
        supported = next;
        
    }
    end = clock();
    cout << "Library sort time:" << float(end - start)/CLOCKS_PER_SEC<< endl;
    cout << "Library sort clock:" << lib_clock_count<<endl<<endl;
    
    ofstream out(fileName);
    if (fileName != NULL)
    for (k = 0; k < expanded_range; k++) {
        if (expansion_array[k] != NIL) {
            out << expansion_array[k] << " ";
        }
    }
    
    out.close();
    free(expansion_array);
}