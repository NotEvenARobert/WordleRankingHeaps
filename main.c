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

int checkCandidate(char* word, char* correctPos, int minCounts[], int cannotBeAt[][26], int seenGray[]) {

    for(int d = 0; d < 5; d++) {

        if(correctPos[d] != '\0' && word[d] != correctPos[d]) {
           
            return 0;
           
        }
       
        if(cannotBeAt[d][word[d] - 'a']) {
           
            return 0;
           
        }
       
    }

    int wordCounts[26] = {0};
    for(int e = 0; e < 5; e++) {
       
        wordCounts[word[e] - 'a']++;
       
    }

    for(int f = 0; f < 26; f++) {

        if(wordCounts[f] < minCounts[f]) {
           
            return 0;
           
        }

        if(minCounts[f] == 0 && seenGray[f] && wordCounts[f] > 0) {
           
            return 0;
           
        }
       
    }
    return 1;
   
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

    char correctPos[6] = {0};
    int minCounts[26] = {0};
    int cannotBeAt[5][26] = {{0}};
    int seenGray[26] = {0};

    int numGuesses;
    scanf("%d", &numGuesses);
    for(int g = 0; g < numGuesses; g++) {
       
        char guessWord[6];
        char feedback[6];
        scanf("%s %s", guessWord, feedback);

        int currentGuessCounts[26] = {0};
        for(int h = 0; h < 5; h++) {
           
            int letterIdx = guessWord[h] - 'a';
            if(feedback[h] == 'G') {
               
                correctPos[h] = guessWord[h];
                currentGuessCounts[letterIdx]++;
               
            } else if(feedback[h] == 'Y') {
               
                cannotBeAt[h][letterIdx] = 1;
                currentGuessCounts[letterIdx]++;
               
            } else {
               
                cannotBeAt[h][letterIdx] = 1;
                seenGray[letterIdx] = 1;
               
            }
           
        }

        for(int i = 0; i < 26; i++) {
           
            if(currentGuessCounts[i] > minCounts[i]) {
               
                minCounts[i] = currentGuessCounts[i];
               
            }
           
        }
       
    }

    int foundAny = 0;
    while(myHeap->size > 0) {
       
        Entry candidate = deleteMax(myHeap);
        if(checkCandidate(candidate.word, correctPos, minCounts, cannotBeAt, seenGray)) {
           
            printf("%d %s\n", candidate.score, candidate.word);
            foundAny = 1;
           
        }
       
    }

    if(!foundAny) {
       
        printf("No candidates found.\n");
       
    }

    free(myHeap->heaparray);
    free(myHeap);
    return 0;
  
}
