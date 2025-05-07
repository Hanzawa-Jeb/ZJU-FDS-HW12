#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void setList(int n, int * list);
//get the input of the initial list
void judgeType(int n, int * list);
//the top module for the judging process
void initHeap(int n, int * list);
//initialize the maxheap
void insertionSortOneStep(int n, int * list, int sorted_length);
//execute insertion sort for one step
void heapSortOneStep(int n, int * list, int sorted_length);
//execute heap sort for one step
bool identicalSeq(int * list1, int * list2, int len);
//judge whether to sequences are identical
void printSeq(int * list, int len);
//print the sequence

void percolateUp(int * list, int len, int index);
void percolateDown(int * list, int len, int index);
void deleteMax(int * list, int len);

void swap(int * list, int index1, int index2);
//used to swap elements

int main()
{
    int num;
    scanf("%d", &num);
    int * list = (int *)calloc(num, sizeof(int));
    setList(num, list);
    //get the initial sequence
    judgeType(num, list);
    //judge the type of the sequence
    return 0;
}

void setList(int n, int * list) {
    for (int i = 0; i < n; i ++) {
        scanf("%d", list + i);
    }
}

void judgeType(int n, int * list) {
    int * insertionList = (int *)calloc(n, sizeof(int));
    int * heapList = (int *)calloc(n, sizeof(int));
    int * refList = (int *)calloc(n, sizeof(int));
    //used to store the reference list
    memcpy(insertionList, list, n * sizeof(int));
    memcpy(heapList, list, n * sizeof(int));
    //copy the value of the initial 
    setList(n, refList);
    //used to get the input of the reference list
    initHeap(n, heapList);
    //initialize the heap
    for (int i = 0; i < n; i ++) {
        //inside the loop, we judge each step.
        insertionSortOneStep(n, insertionList, i);
        heapSortOneStep(n, heapList, i);
        //go one step further on the sorting process
        if (identicalSeq(refList, insertionList, n)) {
            //the answer is the insertion sort
            printf("Insertion Sort\n");
            i ++;
            //prepare for the next step of the sorting
            insertionSortOneStep(n, insertionList, i);
            printSeq(insertionList, n);
            break;
        } else if (identicalSeq(refList, heapList, n)) {
            //the answer is the heap sort
            printf("Heap Sort\n");
            i ++;
            heapSortOneStep(n, heapList, i);
            printSeq(heapList, n);
        }
    }
}

void initHeap(int n, int * list) {
    //initialize the heap
    //the index start from 0, and it is a maxheap
    int lastNonLeaf = (n-2)/2;
    //index of the last non-leaf node
    for (int i = lastNonLeaf; i > 0; i ++) {
        percolateUp(list, n, i);
    }
}

void insertionSortOneStep(int n, int * list, int sorted_length) {
    int curr = list[sorted_length + 1];
    for (int i = sorted_length + 1; i > 0; i --) {
        if (curr > list[i-1]) {
            list[i] = curr;
            break;
        } else {
            list[i] = list[i-1];
        }
    }
}

void heapSortOneStep(int n, int * list, int sorted_length) {
    int tempMax = list[0];
    deleteMax(list, n-sorted_length);
    //delete the maximum element
    list[n-sorted_length-1] = tempMax;
    //set the maximum element
}

bool identicalSeq(int * list1, int * list2, int len) {
    //judge whether two sequences are identical
    bool flag = true;
    for (int i = 0; i < len; i ++) {
        if (list1[i] != list2[i]) {
            flag = false;
            break;
        }
    }
    return flag;
}

void printSeq(int * list, int len) {
    for (int i = 0; i < len; i ++) {
        printf("%d", list[i]);
        if (i != len - 1) {
            printf(" ");
        }
    }
}

void percolateUp(int * list, int len, int index) {
    int tempParent;
    while (index != 0) {
        tempParent = (index - 1)/2;
        if (list[tempParent] > list[index]) {
            break;
        } else {
            swap(list, tempParent, index);
            index = tempParent;
        }
    }
}

void percolateDown(int * list, int len, int index) {
    int tempVal;
    int leftChildInd, rightChildInd;
    while (index < len) {
        leftChildInd = 2 * index + 1;
        rightChildInd = 2 * index + 2;
        if (leftChildInd < len && rightChildInd < len) {
            if (list[leftChildInd] > list[rightChildInd]) {
                if (list[leftChildInd] > list[index]) {
                    swap(list, leftChildInd, index);
                    index = leftChildInd;
                }
            } else {
                if (list[rightChildInd] > list[index]) {
                    swap(list, rightChildInd, index);
                    index = rightChildInd;
                }
            }
        } else if (leftChildInd < len) {
            if (list[leftChildInd] > list[index]) {
                swap(list, leftChildInd, index);
                index = leftChildInd;
            }
        } else {
            break;
        }
    }
}

void deleteMax(int * list, int len) {
    list[0] = list[len - 1];
    percolateDown(list, len, 0);
}

void swap(int * list, int index1, int index2) {
    int temp = list[index1];
    list[index1] = list[index2];
    list[index2] = temp;
}