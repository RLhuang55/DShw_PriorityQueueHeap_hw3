#include"heap.h"
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<string.h>
void createPQ(PQ_t *pq, H_class pqClass, int elementSize, int maxSize, int (*compare)(void* elementA, void *elementB))
{
    createHeap(&(pq->heap), elementSize, maxSize);
    pq->pqClass = pqClass;
    pq->maxSize = maxSize;
    pq->elementSize = elementSize;
    pq->compare = compare;
};
void createHeap(Heap_t *heap, int elementSize, int maxSize)
{
    heap->numElements = 0; //陣列0有東西
    heap->elements = calloc(maxSize,elementSize);
};

void Enqueue(PQ_t *pq, void* newItem)
{
    pq->heap.numElements++;
    memcpy((pq->heap.elements+(pq->heap.numElements-1)*(pq->elementSize)),newItem, pq->elementSize);
    ReheapUp(pq, 0, pq->heap.numElements-1);
};
void Dequeue(PQ_t *pq)
{
    memcpy(pq->heap.elements,(pq->heap.elements+(pq->heap.numElements-1)*(pq->elementSize)),pq->elementSize);
    pq->heap.numElements--;
    ReheapDown(pq, 0, pq->heap.numElements-1);
};

int IsFull(PQ_t *pq)
{
    if(pq->maxSize == pq->heap.numElements)
        return 1;
};

int IsEmpty(PQ_t *pq)
{
    return (pq->heap.numElements == 0);
} ;

static void ReheapDown(PQ_t *pq, int root, int bottom)
{
    int maxChild, minChild, leftChild, rightChild;
    leftChild = 2*root+1;
    rightChild = 2*root+2;
    if(leftChild <= bottom)    // left child is part of the heap
    {
        if(pq->pqClass==1)//maxheap
        {
            if(leftChild == bottom) // only one child
                maxChild = leftChild;
            else
            {
                if(pq->compare((pq->heap.elements+leftChild*(pq->elementSize)),(pq->heap.elements+rightChild*(pq->elementSize)))!=1) //leftchild<=rightchild
                    maxChild = rightChild;
                else
                    maxChild = leftChild;
            }

            if(pq->compare(pq->heap.elements+root*(pq->elementSize),pq->heap.elements+maxChild*(pq->elementSize))!=1)
            {
                Swap(pq->heap.elements+root*(pq->elementSize),pq->heap.elements+(pq->elementSize)*maxChild,pq->elementSize);
                ReheapDown(pq,maxChild,bottom);
            }
        }
        else
        {
            if(leftChild == bottom) // only one child
                minChild = leftChild;
            else
            {
                if(pq->compare((pq->heap.elements+leftChild*(pq->elementSize)),(pq->heap.elements+rightChild*(pq->elementSize)))!=-1) //leftchild<=rightchild
                    minChild = rightChild;
                else
                    minChild = leftChild;
            }

            if(pq->compare(pq->heap.elements+root*pq->elementSize,pq->heap.elements+minChild*(pq->elementSize))!=-1)
            {
                Swap(pq->heap.elements+root*pq->elementSize,pq->heap.elements+(pq->elementSize)*minChild,pq->elementSize);
                ReheapDown(pq,minChild,bottom);
            }

        }
    }
};
static void ReheapUp(PQ_t *pq, int root, int bottom)
{
    int parent;
    if(bottom > root)   // tree is not empty
    {
        parent = (bottom-1)/2;
        if(pq->pqClass==1)//maxheap
        {
                if(pq->compare(pq->heap.elements+parent*pq->elementSize,pq->heap.elements+bottom*pq->elementSize)==-1)
                {
                    Swap(pq->heap.elements+parent*pq->elementSize,pq->heap.elements+bottom*pq->elementSize, pq->elementSize);
                    ReheapUp(pq,root, parent);
                }
        }
        else
        {
            if(pq->compare(pq->heap.elements+parent*pq->elementSize,pq->heap.elements+bottom*pq->elementSize)==1)
            {
                Swap(pq->heap.elements+parent*pq->elementSize,pq->heap.elements+bottom*pq->elementSize, pq->elementSize);
                ReheapUp(pq,root, parent);
            }
        }
    }

};

static void Swap(void *elementA, void* elementB, int elementSize)
{
    void * tmp = calloc(1,elementSize);
    memcpy(tmp,elementA,elementSize);
    memcpy(elementA,elementB,elementSize);
    memcpy(elementB,tmp,elementSize);
    free(tmp);
}; //利用 memcpy 實作 swap

