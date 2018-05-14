/*
 /
 /File: Huffman.c
 /
 /
 /
 /
 /
 /
 /
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


#include "tree.h"
#include "pack.h"

#define END 256
#define p(x)  ((x-1)/2)
#define l(x)  ((x*2) + 1)
#define r(x)  ((x*2) + 2)


int freq[257] ={0};
struct tree *heap[257];
int heapCount = 0;
struct tree *leaf[257] = {NULL};


//The printHeap function is unused, but the calls are commented out
//They can be uncommented out to see how the Huffman tree is built
//   from the heap array
void printHeap(void){
    //print statement to show heap
   // printf("Sorted from heap: \n");
    
    for(int j = 0; j < heapCount; j++)
        printf("%d  ", getData(heap[j]));
    printf("\n");
    //end print statement for heap
    

}

void insertion(struct tree *tp){
    heap[heapCount] = tp;       //insert new data into heap
    int hIndex = heapCount;
    while(getData(heap[p(hIndex)]) > getData(heap[hIndex]))
    {   //reheap
        struct tree *temp;
        temp = heap[p(hIndex)];
        heap[p(hIndex)] =  heap[hIndex];
        heap[hIndex] = temp;
        hIndex = p(hIndex);
    }
    heapCount++;    //increment heapCount
   // printHeap();
}

struct tree *delete(void){
    struct tree *del;
    
    del = heap[0];
    heap[0] = heap[heapCount-1];

    heapCount--;
   
    int hdIndex = 0;
    
    
    //Heap Down

    while(l(hdIndex) < heapCount)
    {
       // printHeap();
       
        if(r(hdIndex) < heapCount && getData(heap[r(hdIndex)]) < getData(heap[hdIndex]))
        {   //if right child exists and is less than the parent, swap them
           // printf("Swap Right \n");
            struct tree *temp;
            temp = heap[hdIndex];
            heap[hdIndex] =  heap[r(hdIndex)];
            heap[r(hdIndex)] = temp;
            hdIndex = r(hdIndex);
            
            
        }
        else if(getData(heap[l(hdIndex)]) < getData(heap[hdIndex]) )
        {   //if the left child is smaller than the parent, swap them
            
           // printf("Swap Left \n");
            struct tree *temp;
            temp = heap[hdIndex];
            heap[hdIndex] =  heap[l(hdIndex)];
            heap[l(hdIndex)] = temp;
            hdIndex = l(hdIndex);
        }else{ //if heap[hdIndex] = Right and Left Child
        
            return del;
        }

        
    }
    
    

  //  printHeap();
    return del;
}

void printbin(struct tree *np){
    if(getParent(getParent(np)) != NULL){
	printbin(getParent(np));
    }
    // print 0 or 1
    if(getLeft(getParent(np)) == np){
	printf("0");
    }else if(getRight(getParent(np)) == np){
	printf("1");
    }
	return;
}

void printCode(struct tree *np[END + 1]){
    for(int i = 0; i < 257; i++)
    {
        if(np[i] != NULL)
        {
            if(isprint(i) == 0)
                printf("%03o   %d   ", i, getData(np[i]));
            else
                printf("'%c'   %d   ",i, getData(np[i]));
            printbin(np[i]);
            printf(" \n");
        }
    }
}

int main(int argc, char *argv[2]){
    
    //set up file stream
    FILE *p;
    int ch;
    p = fopen(argv[1], "r");
  
    
    
//Step 1: Create a Frequency Array
 

    
    
    //fill freq array with chars from file
    
    if(p == NULL){                          //Make sure the file opens
        printf("File was not opened \n");
        return 0;
    }
    while((ch = getc(p)) != EOF)            //get character, make sure != EOF
    {
        freq[ch]++;                         //increase freq count
    }
 
 /*
   //Print Statement for freq array
    for(int i = 0; i < 256; i++){           //print statement for all nonzero
        if(freq[i] != 0){                   //frequencies
            printf("%d      '%c' ", freq[i], i);
            printf("\n");
        }
    }
        
    printf(" \n");
    //End print statement for freq array
    
    
    printf("Indexes: \n");
    printf("0  1  2  3  4  5  6  7  8  9  10 \n");
 */
    //end file stream
    fclose(p);
    
//Step 2: construct a min heap
    
    for(int i = 0; i < 256; i++){
        if(freq[i] != 0){          //when the char occurs  
            leaf[i] = createTree(freq[i], NULL, NULL);
            insertion(leaf[i]);
        }
    }
    leaf[256] = createTree(0, NULL, NULL);
    insertion(leaf[256]);
   

    //print statement to show heap
    printf("Sorted heap: \n");
    
    for(int j = 0; j < heapCount; j++)
        printf("%d  ", getData(heap[j]));
    printf("\n");
    printf("\n");
    //end print statement for heap

    
//Step 3: Build Huffman tree
    while(heapCount > 1)
    {
        //delete 2 nodes from the heap
        struct tree *leftC = delete();
       // printf("Left Succuess  \n");
       // printHeap();
        
        
        struct tree *rightC = delete();
      //  printf("Right Success \n");
      //  printf("\n");
      //  printHeap();
        
        int sum = getData(leftC) + getData(rightC);
       // printf("The sum is: %d\n", sum);
        struct tree *new = createTree(sum, leftC, rightC);
        insertion(new);
    
       
        
    }//end build Huffman tree

    
    
//Step 4: Encoding
    
    printCode(leaf);
    printf("\n");
    
//Step 5: Call the pack function
    pack(argv[1], argv[2], leaf);
    
   

    
//end program
    
    return 0;
    
    
}
