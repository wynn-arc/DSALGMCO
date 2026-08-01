#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_CAPACITY 20

typedef struct {
    int items[QUEUE_CAPACITY];
    int front;
    int count;
} Queue;
/* initialize queueue functions lng */
void InitQueue(Queue *q);
int IsQueueEmpty(Queue *q);
void Enqueue(Queue *q, int value);
int Dequeue(Queue *q);

#endif
