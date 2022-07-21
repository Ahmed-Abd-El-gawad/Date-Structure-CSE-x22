/*
    lab9 task: Huffman Decoding
*/
#include <stdio.h>
#include <stdlib.h>

unsigned int str_len(const char *s)
{
    unsigned int count = 0;
    while((*s)!='\0')
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
        for(unsigned int j=0; j<str_len(S)- 1; j++)
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
    for(int i=1; i<S[i]; i++)
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
    while((*S)!='\0')
    {
        if(character==(*S))
        {
            freq++;
        }
        S++;
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

// node for huffman tree
struct QueueNode {
    char data;
    unsigned freq;
    struct QueueNode *left, *right;
};

// queue for huffman nodes
struct Queue {
    int front, rear;
    int capacity;
    struct QueueNode** array;
};

// new huffman node
struct QueueNode* new_huffman_node(char data, unsigned freq)
{
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->left = NULL;
    temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

struct Queue* create_queue(int capacity)
{
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    queue->capacity = capacity;
    queue->array = (struct QueueNode**)malloc(queue->capacity * sizeof(struct QueueNode*));
    return queue;
}

void enqueue(struct Queue* queue, struct QueueNode* item)
{
    // if queue is full
    if(queue->rear == queue->capacity - 1)
    {
        return;
    }
    queue->array[++queue->rear] = item;
    if (queue->front == -1)
        ++queue->front;
}

struct QueueNode* dequeue(struct Queue* queue)
{
    if(queue->front==-1)
    {
        return NULL;
    }
    struct QueueNode* temp = queue->array[queue->front];
    // If there is only one item in queue
    if(queue->front == queue->rear)
    {
        queue->front = queue->rear = -1;
    }
    else
    {
        ++queue->front;
    }
    return temp;
}

struct QueueNode* get_front(struct Queue* queue)
{
    if (queue->front==-1)
    {
        return NULL;
    }
    return queue->array[queue->front];
}

struct QueueNode* find_minimum_node(struct Queue* first_queue, struct Queue* second_queue)
{
    if(first_queue->front==-1)
    {
        return dequeue(second_queue);
    }
    if(second_queue->front==-1)
    {
        return dequeue(first_queue);
    }
    if(get_front(first_queue)->freq <= get_front(second_queue)->freq)
    {
        return dequeue(first_queue);
    }
    return dequeue(second_queue);
}

struct QueueNode* buildHuffmanTree(char data[], int freq[], int n) //minheap
{
    struct QueueNode *left, *right, *top;

    struct Queue* first_queue = create_queue(n);
    struct Queue* second_queue = create_queue(n);

    // build huffman node and put it in the first queue
    for (int i=0; i<n; i++)
    {
        enqueue(first_queue, new_huffman_node(data[i], freq[i]));
    }

    // loop till the first queue is empty which holds the huffman nodes
    // and the second queue has only one element which will be the huffman tree
    while(!( first_queue->front==-1 && ( (second_queue->front == second_queue->rear) && second_queue->front!=-1) ))
    {
        // detect from which queue you will take the huffman node or tree
        left = find_minimum_node(first_queue, second_queue);
        right = find_minimum_node(first_queue, second_queue);

        // give the internal node a non usable character in this case '?'
        // also give it the sum of the freq of its children
        top = new_huffman_node('?', left->freq + right->freq);

        // now give it the links for its children
        top->left = left;
        top->right = right;

        // add the new sub-tree to the queue
        enqueue(second_queue, top);
    }

    // return the huffman tree
    return dequeue(second_queue);
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
    merge_sort_arrays(freq,arr,0,str_len(arr)- 1,str_len(arr));

    struct QueueNode* root = buildHuffmanTree(arr, freq, str_len(arr));

    return root;
}

char *decode_huffman(struct QueueNode* root, char str[]) // min heap
{
    static char decoded_msg[100000] = "";
    struct QueueNode* current = root;
    for(int i=0; i<str_len(str); i++)
    {
        if (str[i] == '0')
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }

        // if its a leaf node
        if(current->left==NULL && current->right==NULL)
        {
            decoded_msg[str_len(decoded_msg)] = current->data;
            current = root;
        }
    }
    return decoded_msg;
}

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

    printf("%s",decode_huffman(encoded_huffman_tree(S),E));

    return 0;
}
