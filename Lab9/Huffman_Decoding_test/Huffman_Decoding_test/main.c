// C Program for Efficient Huffman Coding for Sorted input
#include <stdio.h>
#include <stdlib.h>

// This constant can be avoided by explicitly calculating
// height of Huffman Tree
#define MAX_TREE_HT 100
unsigned int str_len(const char *s)
{
    unsigned int count = 0;
    while(*s!='\0')
    {
        count++;
        s++;
    }
    return count;
}
void str_descending(char *S)
{
    char temp = S[0];
    for(unsigned int i=0; i<str_len(S); i++)
    {
        for(unsigned int j=0; j<str_len(S)-1; j++)
        {
            if(S[j]<S[j+1])
            {
                temp = S[j];
                S[j] = S[j+1];
                S[j+1] = temp;
            }
        }
    }
}
char *remove_duplicate(char S[])
{
    int j = 1;
    char *temp;
    temp =(char*)malloc(str_len(S)*sizeof(char));
    temp[0] = S[0];
    for(int i=1; S[i]; i++)
    {
        temp[i] = S[i];
        if(S[i] != S[i-1])
        {
            temp[j] = temp[i];
            j++;
        }
    }
    temp[j] = '\0';
    return temp;
}
unsigned int frequency(char *S, char character)
{
    unsigned int freq =0;
    for(int i = 0; i<str_len(S); i++)
    {
        if(character==S[i])
        {
            freq++;
        }
    }
    return freq;
}
void merge_arrays(int *arr_1, char *arr_2, unsigned long int start, unsigned long int middle, unsigned long int end, unsigned long int N)
{
    int i = start;
    int j = middle+1;
    int k = 0;
    int temp_1[end-start+1];
    char temp_2[end-start+1];
    while(i<=middle && j<=end)
    {
        if(arr_1[i]<=arr_1[j])
        {
            temp_1[k] = arr_1[i];
            temp_2[k] = arr_2[i];
            k++;
            i++;
        }
        else
        {
            temp_1[k] = arr_1[j];
            temp_2[k] = arr_2[j];
            k++;
            j++;
        }
    }
    while(i<=middle)
    {
        temp_1[k] = arr_1[i];
        temp_2[k] = arr_2[i];
        k++;
        i++;
    }
    while(j<=end)
    {
        temp_1[k] = arr_1[j];
        temp_2[k] = arr_2[j];
        k++;
        j++;
    }
    for(i=start ; i<=end ; i++)
    {
        arr_1[i] = temp_1[i-start];
        arr_2[i] = temp_2[i-start];
    }
}
void merge_sort_arrays(int *arr_1, char *arr_2, unsigned long int start, unsigned long int end,  unsigned long int N)
{
    if(start<end)
    {
        int middle = (start+end)/2;
        merge_sort_arrays(arr_1,arr_2,start,middle,N);
        merge_sort_arrays(arr_1,arr_2,middle+1,end,N);
        merge_arrays(arr_1,arr_2,start,middle,end,N);
    }
}
// A node of huffman tree
struct QueueNode {
    char data;
    unsigned freq;
    struct QueueNode *left, *right;
};

// Structure for Queue: collection of Huffman Tree nodes (or
// QueueNodes)
struct Queue {
    int front, rear;
    int capacity;
    struct QueueNode** array;
};

// A utility function to create a new Queuenode
struct QueueNode* newNode(char data, unsigned freq)
{
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// A utility function to create a Queue of given capacity
struct Queue* createQueue(int capacity)
{
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = -1;
    queue->capacity = capacity;
    queue->array = (struct QueueNode**)malloc(queue->capacity * sizeof(struct QueueNode*));
    return queue;
}
// A utility function to check if size of given queue is 1
int isSizeOne(struct Queue* queue)
{
    return queue->front == queue->rear
           && queue->front != -1;
}

// A utility function to check if given queue is empty
int isEmpty(struct Queue* queue)
{
    return queue->front == -1;
}

// A utility function to check if given queue is full
int isFull(struct Queue* queue)
{
    return queue->rear == queue->capacity - 1;
}

// A utility function to add an item to queue
void enQueue(struct Queue* queue, struct QueueNode* item)
{
    if (isFull(queue))
        return;
    queue->array[++queue->rear] = item;
    if (queue->front == -1)
        ++queue->front;
}

// A utility function to remove an item from queue
struct QueueNode* deQueue(struct Queue* queue)
{
    if (isEmpty(queue))
        return NULL;
    struct QueueNode* temp = queue->array[queue->front];
    if (queue->front == queue->rear) // If there is only one item in queue
        queue->front = queue->rear = -1;
    else
        ++queue->front;
    return temp;
}

// A utility function to get from of queue
struct QueueNode* getFront(struct Queue* queue)
{
    if (isEmpty(queue))
        return NULL;
    return queue->array[queue->front];
}

/* A function to get minimum item from two queues */
struct QueueNode* findMin(struct Queue* firstQueue, struct Queue* secondQueue)
{
    // Step 3.a: If first queue is empty, dequeue from
    // second queue
    if (isEmpty(firstQueue))
        return deQueue(secondQueue);

    // Step 3.b: If second queue is empty, dequeue from
    // first queue
    if (isEmpty(secondQueue))
        return deQueue(firstQueue);

    // Step 3.c:  Else, compare the front of two queues and
    // dequeue minimum
    if (getFront(firstQueue)->freq <= getFront(secondQueue)->freq)
        return deQueue(firstQueue);

    return deQueue(secondQueue);
}

// Utility function to check if this node is leaf
int isLeaf(struct QueueNode* root)
{
    return !(root->left) && !(root->right);
}

// A utility function to print an array of size n
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}

// The main function that builds Huffman tree
struct QueueNode* buildHuffmanTree(char data[], int freq[], int size)
{
    struct QueueNode *left, *right, *top;

    // Step 1: Create two empty queues
    struct Queue* firstQueue = createQueue(size);
    struct Queue* secondQueue = createQueue(size);

    // Step 2:Create a leaf node for each unique character
    // and Enqueue it to the first queue in non-decreasing
    // order of frequency. Initially second queue is empty
    for (int i = 0; i < size; ++i)
        enQueue(firstQueue, newNode(data[i], freq[i]));

    // Run while Queues contain more than one node. Finally,
    // first queue will be empty and second queue will
    // contain only one node
    while (
        !(isEmpty(firstQueue) && isSizeOne(secondQueue))) {
        // Step 3: Dequeue two nodes with the minimum
        // frequency by examining the front of both queues
        left = findMin(firstQueue, secondQueue);
        right = findMin(firstQueue, secondQueue);

        // Step 4: Create a new internal node with frequency
        // equal to the sum of the two nodes frequencies.
        // Enqueue this node to second queue.
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        enQueue(secondQueue, top);
    }

    return deQueue(secondQueue);
}

// Prints huffman codes from the root of Huffman Tree.  It
// uses arr[] to store codes
void printCodes(struct QueueNode* root, int arr[], int top)
{
    // Assign 0 to left edge and recur
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    // Assign 1 to right edge and recur
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    // If this is a leaf node, then it contains one of the
    // input characters, print the character and its code
    // from arr[]
    if (isLeaf(root)) {
        printf("%c: ", root->data);
        printArr(arr, top);
    }
}

// The main function that builds a Huffman Tree and print
// codes by traversing the built Huffman Tree
void HuffmanCodes(char data[], int freq[], int size)
{
    //  Construct Huffman Tree
    struct QueueNode* root = buildHuffmanTree(data, freq, size);

    // Print Huffman codes using the Huffman tree built
    // above
    int arr[MAX_TREE_HT], top = 0;
    printCodes(root, arr, top);
}
struct QueueNode* encoded_huffman_tree(char *S)
{
    str_descending(S);
    char *arr;
    arr = remove_duplicate(S);
    int *freq;
    freq =(int*)malloc(str_len(arr)*sizeof(int));
    for(long int i=0; i<str_len(arr); i++)
    {
        freq[i] = frequency(S,arr[i]);
    }
    merge_sort_arrays(freq,arr,0,str_len(arr)-1,str_len(arr));

    struct QueueNode* root = buildHuffmanTree(arr, freq, str_len(arr));

    return root;
}

char *decode_huffman(struct QueueNode* root, char str[]) // min heap
{

    static char decoded_msg[100000] = "";

    //MinHeapNode is a structure Which basically defines the node of the tree
    //storing input character,their frequency and
    //also left and right child of node.

    struct QueueNode* current = root;
    for(int i=0; i<str_len(str); i++)
    {
        if (str[i] == '0')
        {
            //if current bit is 0 move to the left node.
            current = current->left;
        }
        else
        {
            //if current bit is 1 move to the right node.
            current = current->right;
        }

        if(isLeaf(current))
        {
            decoded_msg[str_len(decoded_msg)] = current->data;
            current = root;
        }
    }
    return decoded_msg;
}
// Driver program to test above functions
int main()
{
    char S[100000], E[100000];
    scanf("%[^\n]%*c",S);
    if(str_len(S) < 2 || str_len(S) > 100000)
    {
        return 0;
    }
    scanf(" %s",E);
    if(str_len(E) < 1 || str_len(E) > 100000)
    {
        return 0;
    }
    //int arr[MAX_TREE_HT], top = 0;

    printf("%s",decode_huffman(encoded_huffman_tree(S),E));

    return 0;
}
