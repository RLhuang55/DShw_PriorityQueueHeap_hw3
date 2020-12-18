#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "heap.h"

typedef struct myElement {
    char ID[10];
    int math;
    int eng;
}student_t;

int compareMath(void *elementA, void *elementB) {
   int mathA = ((student_t *)elementA)->math;
   int mathB = ((student_t *)elementB)->math;
   if(mathA>mathB) {
        return 1;
   }else if(mathA<mathB){
        return -1;
   }
   return 0;
}

void print(PQ_t *pq) {
    student_t *temp;
    for (int i=0; i<pq->heap.numElements;i++){
        temp = (student_t *)(pq->heap.elements+i*sizeof(student_t));
        printf("index=%d, ID=%s,math=%d, eng=%d\n",i,temp->ID, temp->math, temp->eng);
    }
}

int main() {

    student_t node[6]={
        {"C120308001", 70, 100},
        {"B220406001", 60, 90},
        {"D120306001", 80, 95},
        {"A220407001", 65, 90},
        {"D220506001", 10, 70},
        {"A120406001", 90, 90}
    };

    PQ_t maxPQ, minPQ;

    createPQ(&maxPQ, MAXHEAP, sizeof(student_t), 100, compareMath);

    for(int i=0;i<6;i++)
        Enqueue(&maxPQ, &node[i]);
    print(&maxPQ);
    printf("\n");
    createPQ(&minPQ, MINHEAP,sizeof(student_t),100,compareMath);
    for(int i=0;i<6;i++)
        Enqueue(&minPQ, &node[i]);
    print(&minPQ);
    printf("\n");
    Dequeue(&maxPQ);
    print(&maxPQ);
    printf("\n");

    Dequeue(&minPQ);
    print(&minPQ);
    printf("\n");

}

