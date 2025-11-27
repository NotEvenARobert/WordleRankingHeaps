/* COP 3502C PA6
   This program is written by: ANH NHAT LE (Robert) */

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

const int freq[26] = {

    8, 2, 3, 4, 13, 3, 2, 6, 7, 0, 1, 4, 2,  // a-m
    7, 7, 2, 0, 6, 6, 9, 3, 1, 2, 0, 2, 0    // n-z

};

typedef struct Entry {

    char word[6];
    int score;

} Entry;

typedef struct heapStruct {

    Entry* heaparray;
    int capacity;
    int size;

} heapStruct;

int calculateScore(char* word) {
  
    int totalScore = 0;
    for(int a = 0; a < 5; a++) {

        int letterIndex = word[a] - 'a';
        totalScore += freq[letterIndex];
      
    }
    return totalScore;
  
}

void swap(Entry* a, Entry* b) {
   
    Entry temp = *a;
    *a = *b;
    *b = temp;
   
}

void percolateDown(heapStruct* h, int index) {
   
    int maxIndex;
    int leftChild;
    int rightChild;
    while(1) {
       
        maxIndex = index;
        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;

        if(leftChild < h->size) {

            if(h->heaparray[leftChild].score > h->heaparray[maxIndex].score) {
               
                maxIndex = leftChild;
               
            } else if(h->heaparray[leftChild].score == h->heaparray[maxIndex].score) {
               
                if(strcmp(h->heaparray[leftChild].word, h->heaparray[maxIndex].word) < 0) {
                   
                    maxIndex = leftChild;
                   
                }
               
            }
           
        }

        if(rightChild < h->size) {

            if(h->heaparray[rightChild].score > h->heaparray[maxIndex].score) {
               
                maxIndex = rightChild;
               
            } else if(h->heaparray[rightChild].score == h->heaparray[maxIndex].score) {
               
                if(strcmp(h->heaparray[rightChild].word, h->heaparray[maxIndex].word) < 0) {
                   
                    maxIndex = rightChild;
                   
                }
               
            }
           
        }

        if(index != maxIndex) {
           
            swap(&h->heaparray[index], &h->heaparray[maxIndex]);
            index = maxIndex;
           
        } else {
           
            break; 
           
        }
       
    }
   
}

void heapify(heapStruct* h) {

    for(int c = (h->size / 2) - 1; c >= 0; c--) {
       
        percolateDown(h, c);
       
    }
   
}

Entry deleteMax(heapStruct* h) {

    Entry maxEntry = h->heaparray[0];
    h->heaparray[0] = h->heaparray[h->size - 1];
    h->size--;

    if(h->size > 0) {
       
        percolateDown(h, 0);
       
    }
    return maxEntry;
   
}

int main(void) {

    int numWords;
    scanf("%d", &numWords);

    heapStruct* myHeap = (heapStruct*)malloc(sizeof(heapStruct));
    myHeap->heaparray = (Entry*)malloc(sizeof(Entry) * numWords);
    myHeap->capacity = numWords;
    myHeap->size = numWords;

    for(int b = 0; b < numWords; b++) {
      
        scanf("%s", myHeap->heaparray[b].word);
        myHeap->heaparray[b].score = calculateScore(myHeap->heaparray[b].word);
      
    }
   
    heapify(myHeap);

    free(myHeap->heaparray);
    free(myHeap);

    return 0;
  
}
