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

    free(myHeap->heaparray);
    free(myHeap);

    return 0;
  
}
