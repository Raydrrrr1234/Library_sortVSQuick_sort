//
//  library_sort.cpp
//  CS583
//
//  Created by kang on 11/20/14.
//
//


#include <stdio.h>
#include "library_sort.h"
#include "insertion_sort.h"
#include "quick_sort.h"





void generateRandomPermu(int ** data_int, int data_size)
{
    *data_int = (int *)malloc(sizeof(int)*data_size);
    for (int j = 0; j < data_size; j++) {
        (*data_int)[j] = rand();
    }
}
/*******************************************************************************
 *  Generate random permutation
 *******************************************************************************/

void generator(int * data_int, int data_size, char * fileName)
{
    int i;
    ofstream output_stream(fileName);
    
    generateRandomPermu(&data_int, data_size);
    
    output_stream << data_size << " ";
    
    for ( i = 0; i < data_size; i++) {
        output_stream << data_int[i]<<" ";
    }
    output_stream.close();
}
/*******************************************************************************
 *  Read data from file
 *******************************************************************************/
void seeker(int * data_int[], int * data_size, char fileName[], int t)
{
    int i;
    char newfile[] = "./data0";
    ifstream input_stream(fileName);
    if (input_stream.bad()) {
        newfile[sizeof(newfile)-2] += t;
        ifstream input_stream(newfile);
    }
    // first input data must be the length of array
    input_stream>>*data_size;
    if (*data_int == NULL) {
        *data_int = (int *)malloc(sizeof(int)*(*data_size));
    }
    i = 0;
    while (i < *data_size) {
        input_stream>>(*data_int)[i];
        i++;
    }

    input_stream.close();
}

int main()
{
    int * data_int = NULL, data_size = 0;
    
    int t;
    
    char fileName[] = "/Users/kang/Documents/MyOJProject/CS583/CS583/data0";
    char output[128] = "";
//    clock_t start, end;
    
    (void)data_int;
    (void)data_size;
    (void)fileName;
    
    
    
//    for (int i = 0; i < 10; i++) {
        
        /*******************************************************************************
         *  Generate 10 permutation
         *******************************************************************************/
//        data_size = rand()%100000;
//        generator(data_int, data_size, fileName);
        
//        fileName[sizeof(fileName)-2]++;
//    }
    cout << "Please Type the data set you want to test(Press 0~9 then Enter)"<<endl;
    cout << "Please Type -1 to generate random permuation"<<endl;
    while (1) {
        
        cin >> t;
        if (t >= 0 && t <= 9) {
            fileName[sizeof(fileName)-2] += t;
            
            cout <<"File name:" << fileName << endl;
            
            seeker(&data_int, &data_size, fileName, t);
            cout << "Data size:" << data_size<< endl;
            strcpy(output, fileName);
            strcat(output, "_librarySort");
            librarySort(data_int, data_size, output);
            strcpy(output, fileName);
            strcat(output, "_insertionSort");
            insertionSort(data_int, data_size, output);
            strcpy(output, fileName);
            strcat(output, "_quickSort");
            quickSort(data_int, data_size, output);
            
            fileName[sizeof(fileName)-2] -= t;
            
            free(data_int);
            
            data_int = NULL;
        }
        else if(t == -1) {
            cout << "Input the max data size:";
            cin >> t;
            
                data_size = t;
                generateRandomPermu(&data_int, data_size);
                
                librarySort(data_int, data_size, NULL);
                insertionSort(data_int, data_size, NULL);
                quickSort(data_int, data_size, NULL);
                
                free(data_int);
        }
        else
            cout <<"Input error!!"<<endl;
    }
    
    
    
    /*******************************************************************************
     *  Sorting algorithms, the second argument is the last element of the permutation
     *******************************************************************************/
    /*
    librarySort(data_int, data_size);
    insertionSort(data_int, data_size);
    quickSort(data_int, data_size);
    */
    
    
    return 1;
}
