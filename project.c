#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>

typedef struct node_def {
    int number;
    struct node_def *next;
} Node;

typedef struct {
    int nodeCount;
    Node *head;
    Node *tail;
}Queue;

int* generateArray(int);
void display(int*, int);
int findBiggest(int*, int);
int getNumberOfRuns(int*, int);
void radixSort(int*, int);

void enqueue(Queue*, int);
int dequeue(Queue*);
void initQueue(Queue*);
static Node* createNewNode(int);

void swap(int[], int);
void bubbleSort(int[], int);

int main (int argc, char* argv[]) {
    int bigSize = 100000;
    int* bigArray  = generateArray(bigSize);

    int smallSize = 1000;
    int* smallArray  = generateArray(smallSize);

    int mediumSize = 5000;
    int* mediumArray  = generateArray(mediumSize);



    // radixSort(array, size);
    // display(array, size);

    printf("Number of element: %d\n", bigSize);

    clock_t startRadix = clock();
    radixSort(bigArray, bigSize);
    clock_t finishRadix = clock();
    double radixSortTime = (double)(finishRadix - startRadix)/CLOCKS_PER_SEC;
    printf ("Radix sort time: %f\n", radixSortTime);

    clock_t startBubble = clock();
    bubbleSort(bigArray, bigSize);
    clock_t finishBubble = clock();
    double bubbleSortTime = (double)(finishBubble - startBubble)/CLOCKS_PER_SEC;
    printf ("Bubble sort time: %f\n", bubbleSortTime);

    printf("---------------------------\n");

    printf("Number of element: %d\n", mediumSize);

    startRadix = clock();
    radixSort(mediumArray, mediumSize);
    finishRadix = clock();
    radixSortTime = (double)(finishRadix - startRadix)/CLOCKS_PER_SEC;
    printf ("Radix sort time: %f\n", radixSortTime);

    startBubble = clock();
    bubbleSort(mediumArray, mediumSize);
    finishBubble = clock();
    bubbleSortTime = (double)(finishBubble - startBubble)/CLOCKS_PER_SEC;
    printf ("Bubble sort time: %f\n", bubbleSortTime);

    printf("---------------------------\n");

    printf("Number of element: %d\n", smallSize);

    startRadix = clock();
    radixSort(smallArray, smallSize);
    finishRadix = clock();
    radixSortTime = (double)(finishRadix - startRadix)/CLOCKS_PER_SEC;
    printf ("Radix sort time: %f\n", radixSortTime);

    startBubble = clock();
    bubbleSort(smallArray, smallSize);
    finishBubble = clock();
    bubbleSortTime = (double)(finishBubble - startBubble)/CLOCKS_PER_SEC;
    printf ("Bubble sort time: %f\n", bubbleSortTime);
}

int* generateArray(int size) {
    int* array = malloc(size * sizeof(int));
    srand(time(NULL));

    for (int i = 0; i < size; i++) {
       array[i] = rand();
    }

    return array;
}

void display(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ",array[i]);
    }
    printf("\n");
}

int findBiggest(int* array, int size) {
    int biggest = array[0];

    for (int i = 0; i < size; i++) {       
        if (array[i] > biggest) {
            biggest = array[i];
        }
    }

    return biggest;
}

int getNumberOfRuns(int* array, int size) {
    int biggest = findBiggest(array, size);
    int run = 0;

    while (biggest != 0)
    {
        biggest = biggest/10;
        run++;
    }

    return run;   
}

void radixSort(int* array, int size) {
    
    int runs = getNumberOfRuns(array, size);
    
    Queue queues[10]; //10 digits from 0-9
    for (int i = 0; i < 10; i++) {
        Queue newQueue;
        initQueue(&newQueue);
        queues[i] = newQueue;
    }
    int modulous = 10;
    int divisor = 1;
    
    for (int i = 0; i < runs; i++) {
        
        for (int j = 0; j < size; j++) {
            int digit = (array[j]/divisor) % 10;

            enqueue(&queues[digit], array[j]);
        }

        //dequeue, place elements back to the array in descending order base on the digit of this run
        int index = 0;

        for (int j = 0; j < 10; j++) {
 
            while(queues[j].nodeCount > 0) {
                array[index] = dequeue(&queues[j]);
                index++;
            }   
        }

        modulous *= 10;
        divisor *= 10;
    }
}

static Node* createNewNode(int num) {
    Node *newNode = malloc(sizeof(Node));
    assert(newNode);
    newNode->number = num;
    newNode->next = NULL;

    return newNode;
}

void enqueue(Queue *queue, int num) {

    Node *newNode = createNewNode(num);
    if(queue->head == NULL) {
        queue->head = queue->tail = newNode;
    } else {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
    queue->nodeCount++;


} 

int dequeue(Queue * queue) {
    Node *temp;

    int num = -99999; //rogue number
    
    if(queue->head != NULL) {
        //delete the head
        temp = queue->head;
        num = queue->head->number;
        queue->head = queue->head->next;
        queue->nodeCount--;
        free(temp);
    } else {
        //empty queue - does nothing
        printf("empty queue\n");
    }

    return num;
}

void initQueue(Queue *queue) {
    queue->nodeCount = 0; 
    queue->head = NULL; 
    queue->tail = NULL;
}

void bubbleSort(int array[], int size) {
    Queue queue;
    initQueue(&queue);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (array[j] > array[j + 1]) {

                enqueue(&queue, array[j]);
                array[j] = array[j + 1];
                array[j + 1] = dequeue(&queue);
            }
        }
    }
}