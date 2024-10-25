#include <stdio.h>
#include <stdlib.h>

// 定义节点结构体
typedef struct Node {
    int key;                  // 节点的键值
    struct Node* parent;      // 指向父节点的指针
    struct Node* child;       // 指向子节点的指针
    struct Node* left;        // 左兄弟节点
    struct Node* right;       // 右兄弟节点
    int degree;               // 节点的度数，即子节点的数量
    int mark;                 // 用于标记节点是否被删除
} Node;

// 定义斐波那契堆结构体
typedef struct {
    Node* min;                // 指向最小节点的指针
    int total_nodes;          // 堆中节点的总数
    int total_degree;          // 堆中所有节点的度数之和
} FibonacciHeap;

// 创建一个新的节点
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        perror("Failed to allocate memory for node");
        exit(EXIT_FAILURE);
    }
    node->key = key;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;        // 初始时节点是自己的左兄弟
    node->right = node;       // 初始时节点是自己的右兄弟
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
    if (heap2->min == NULL) {
        free(heap2);
        return;
    }
    if (heap1->min == NULL) {
        *heap1 = *heap2;
        free(heap2);
        return;
    }
    if (heap1->min->key > heap2->min->key) {
        Node* temp = heap1->min;
        heap1->min = heap2->min;
        heap2->min = temp;
    }
    Node* temp_left = heap1->min->left;
    Node* temp_right = heap1->min->right;
    temp_left->right = heap2->min;
    heap2->min->left = temp_left;
    temp_right->left = heap2->min->right;
    heap2->min->right = temp_right;
    heap1->total_nodes += heap2->total_nodes;
    heap1->total_degree += heap2->total_degree;
    free(heap2);
}

// 提取斐波那契堆中的最小元素
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
    }
    return minNode;
}

// 使用斐波那契堆对数组进行排序
void fibonacciHeapSort(int arr[], int n) {
    FibonacciHeap heap;
    initFibonacciHeap(&heap);

    for (int i = 0; i < n; i++) {
        insertNode(&heap, createNode(arr[i]));
    }

    for (int i = 0; i < n; i++) {
        Node* minNode = extractMin(&heap);
        if (minNode != NULL) {
            arr[i] = minNode->key;
            free(minNode);
        }
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