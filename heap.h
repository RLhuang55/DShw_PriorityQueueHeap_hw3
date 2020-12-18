#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
typedef struct HeapType
{
    void *elements; // element array
    int numElements; // number of elements
} Heap_t;

typedef enum
{
    MINHEAP=0,
    MAXHEAP
} H_class;

typedef struct PQ
{
    H_class pqClass;
    Heap_t  heap;
    int maxSize;
    int elementSize;
    int (*compare)(void* elementA, void* elementB);
} PQ_t;

void createPQ(PQ_t *pq, H_class pqClass, int elementSize, int maxSize, int (*compare)(void* elementA, void *elementB));
void createHeap(Heap_t *heap, int elementSize, int maxSize);
void Enqueue(PQ_t *pq, void* newItem);
void Dequeue(PQ_t *pq);
int IsEmpty(PQ_t *pq);
int IsFull(PQ_t *pq);
static void ReheapDown(PQ_t *, int root, int bottom);
static void ReheapUp(PQ_t*, int root, int bottom);
static void Swap(void *elementA, void* elementB, int elementSize);
#endif
