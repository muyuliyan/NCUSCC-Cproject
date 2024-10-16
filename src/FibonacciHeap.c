#include <stdio.h>
#include <stdlib.h>

// 节点结构
typedef struct Node {
    int key;
    struct Node* parent;
    struct Node* child;
    struct Node* left;
    struct Node* right;
    int degree;
    int mark;
} Node;

// 斐波那契堆结构
typedef struct {
    Node* min;
    int total_nodes;
    int total_degree;
} FibonacciHeap;

// 创建一个新的节点
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    node->degree = 0;
    node->mark = 0;
    return node;
}

// 初始化斐波那契堆
void initFibonacciHeap(FibonacciHeap* heap) {
    heap->min = NULL;
    heap->total_nodes = 0;
    heap->total_degree = 0;
}

// 将节点添加到斐波那契堆中
void insertNode(FibonacciHeap* heap, Node* node) {
    node->left = node;
    node->right = node;
    if (heap->min == NULL) {
        heap->min = node;
    } else {
        node->right = heap->min;
        node->left = heap->min->left;
        heap->min->left->right = node;
        heap->min->left = node;
    }
    heap->total_nodes++;
}

// 合并两个斐波那契堆
void mergeHeaps(FibonacciHeap* heap1, FibonacciHeap* heap2) {
    if (heap1->min == NULL) {
        *heap1 = *heap2;
        free(heap2);
    } else if (heap2->min == NULL) {
        free(heap2);
    } else {
        if (heap1->min->key > heap2->min->key) {
            Node* temp = heap1->min;
            heap1->min = heap2->min;
            heap2->min = temp;
        }
        heap1->min->right->left = heap2->min->left;
        heap2->min->left->right = heap1->min->right;
        heap1->min->right = heap2->min;
        heap2->min->left = heap1->min;
        if (heap1->total_degree < heap2->total_degree) {
            Node* temp = heap1->min;
            heap1->min = heap2->min;
            heap2->min = temp;
        }
        heap1->total_nodes += heap2->total_nodes;
        heap1->total_degree += heap2->total_degree;
        free(heap2);
    }
}

// 提取最小元素
Node* extractMin(FibonacciHeap* heap) {
    Node* minNode = heap->min;
    if (minNode != NULL) {
        if (minNode->child != NULL) {
            Node* child = minNode->child;
            while (child != minNode) {
                child->parent = NULL;
                child->mark = 0;
               insertNode(heap, child);
               child = child->right;
            }
        }
        if (minNode->left == minNode) {
            heap->min = NULL;
        } else {
            heap->min = minNode->right;
            minNode->left->right = minNode->right;
            minNode->right->left = minNode->left;
        }
        heap->total_nodes--;
        free(minNode);
    }
    return minNode;
}

// 斐波那契堆排序
void fibonacciHeapSort(int arr[], int n) {
    FibonacciHeap heap;
    initFibonacciHeap(&heap);

    for (int i = 0; i < n; i++) {
        insertNode(&heap, createNode(arr[i]));
    }

    for (int i = 0; i < n; i++) {
        arr[i] = extractMin(&heap)->key;
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    fibonacciHeapSort(arr, n);

    printf("Sorted array: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}