#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}

void  merge_sort( ElementType list[],  int N )
{
    ElementType extra[MAXN];  /* the extra space required */
    int  length = 1;  /* current length of sublist being merged */
    while( length < N ) { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 


int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);

    return 0;
}

//N is the total length while length is the length of the current sorted component

void merge( ElementType pos1[], ElementType pos2[], int * destPos, int length1, int length2)
{
    int ptr1 = 0, ptr2 = 0;
    int destPtr = 0;
    while (ptr1 < length1 && ptr2 < length2) {
        if (pos1[ptr1] < pos2[ptr2]) {
            destPos[destPtr] = pos1[ptr1];
            destPtr ++;
            ptr1 ++;
        }
        else {
            destPos[destPtr] = pos2[ptr2];
            destPtr ++;
            ptr2 ++;
        }
    }
    while (ptr1 < length1) {
        destPos[destPtr] = pos1[ptr1];
        destPtr ++;
        ptr1 ++;
    }
    while (ptr2 < length2) {
        destPos[destPtr] = pos2[ptr2];
        destPtr ++;
        ptr2 ++;
    }
}

void merge_pass( ElementType list[], ElementType sorted[], int N, int length )
{
    int listPtr = 0, sortedPtr = 0;     //used as the pointer for the list and the sorted list
    int leftLen = 0;                    //the length that are left  
    int i;  
    int leftPtr;
    for (i = 0; i < N / (length * 2); i ++) {
        merge(list+(2*i*length), list+(2*i*length + length), sorted + sortedPtr, length, length);
        sortedPtr += 2 * length;
    }
    //process the possible leftover elements
    leftLen = N - (N/(length * 2) * length * 2);
    leftPtr = i * length * 2;
    if (leftLen <= length) {
        while (leftPtr < N) {
            sorted[sortedPtr] = list[leftPtr];
            sortedPtr ++;
            leftPtr ++;
        }
    }
    else {
        merge(list + leftPtr, list + leftPtr + length, sorted + sortedPtr, length, leftLen - length);
    }
}
