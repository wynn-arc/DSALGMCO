/**
   queues for traversing
*/

#include "queue.h"

void InitQueue(Queue *q)
{
    q->front = 0;
    q->count = 0;
}

int IsQueueEmpty(Queue *q)
{
    return q->count == 0;
}

void Enqueue(Queue *q, int value)
{
    int rearIndex = (q->front + q->count) % QUEUE_CAPACITY;
    q->items[rearIndex] = value;
    q->count++;
}

int Dequeue(Queue *q)
{
    int value;
    if (IsQueueEmpty(q)) {
        return -1;
    }
    value = q->items[q->front];
    q->front = (q->front + 1) % QUEUE_CAPACITY;
    q->count--;
    return value;
}
