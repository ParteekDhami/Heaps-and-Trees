#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "a3q2_header.h"

/*
 * The downHeap function performs the downheap algorithm.
 * The key at the passed position is swapped with the key of it's child with the smallest value.
 * If the key is smaller, than both of it's children's keys then no swap happens.
 * After swap, the downHeap is called again to the new position of the swapped key and it terminates when it's value is smaller than both children.
*/
void downHeap(int key[20], int pos, int array[20][10]){
  //index of left child
int index_ch = 2* pos +1; 
    int value = key[pos];

    while (index_ch< 20) {    //loop until end of heap
        int index_max =index_ch; 
        //check if right child exists
        if (index_ch+ 1 < 20&& key[index_ch + 1]> key[index_ch]) {
            index_max=index_ch +1; 
        }

        //if largest child is smaller or equal to current value break
        if (key[index_max] <= value) {
            break;
        }

        //swap current node with larger child
        key[pos]= key[index_max];
        swap(pos, index_max, key, array);
        pos =index_max;
        index_ch = 2* pos +1; 
        //print statment used to check if issue faced is from downHeap
          printf("Before swap: key[%d] = %d, key[%d] = %d\n", pos, key[pos], index_max, key[index_max]);

    }

    //place original value in correct position
    key[pos] = value;
    
}

// The isParent function returns true if the passed position has a child or false if there's no child
bool isParent(int keyPos){
  int index_left_child = 2* keyPos +1;
  //check if index is within array
if(index_left_child<20){
  return true; //node has child
}
  return false;//no child exist

}

// The swap function swaps 2 rows in the 2D array and the key array. It receives the position of the 2 rows to be swapped, the key array, and the 2D array in its arguements.
void swap(int key1Pos, int key2Pos, int key[20], int array[20][10]){

//swap values in array
//int x is a temporary variable
    int x =key[key1Pos];//store the value key1Pos in x
    //put value from key2Pos in key1Pos
    key[key1Pos]= key[key2Pos]; 
    key[key2Pos]= x;  //put stored value in key2Pos

    //swap rows in array
    for (int i= 0; i <10; i++) {  //loop all columns in the row
    //y is variable for rows
    //store current row value at key1Pos
        int y =array[key1Pos][i];  
        //copy value from key2Pos row to key1Pos
        array[key1Pos][i]= array[key2Pos][i];  
        //put stored value in key2Pos row
        array[key2Pos][i]= y;  
    }

}
