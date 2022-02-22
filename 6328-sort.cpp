#include <iostream>
#include <fstream>
#include <pthread.h>
#include <vector>
#include <cstdlib>
#include <time.h>
int *arr;
int size;
struct arrayStatus
{
    int high;
    int low;
    int mid;
};
using namespace std;
///////////////////////////////////////////////
void merge(int low, int mid, int high)
{

    int* left = new int[mid - low + 1];
    int* right = new int[high - mid];

    // s1 is size of left array and s2 is size
    // of right array
    int s1 = mid - low + 1, s2 = high - mid, i, j;

    // storing values in left part
    for (i = 0; i < s1; i++)
        left[i] = arr[i + low];

    // storing values in right part
    for (i = 0; i < s2; i++)
        right[i] = arr[i + mid + 1];

    int l = low;
    i = j = 0;

    // merge left and right in ascending order
    while (i < s1 && j < s2)
    {
        if (left[i] <= right[j])
            arr[l++] = left[i++];
        else
            arr[l++] = right[j++];
    }

    // insert remaining values from left
    while (i < s1)
    {

        arr[l++] = left[i++];

    }

    // insert remaining values from right
    while (j < s2)
    {
        arr[l++] = right[j++];
    }
}
//////////////////////////////////////////////////////////////
void *mergeSort(void* arg)
{
    arrayStatus *as=(arrayStatus *)arg;
    pthread_t threads[2];
    // evaluating mid point
    as->mid = as->low + (as->high - as->low) / 2;

    arrayStatus as1,as2;
    // first array that will be sent to merge sort
    as1.low=as->low;
    as1.high=as->mid;
    // second array that will be sent to merge sort
    as2.low=as->mid+1;
    as2.high=as->high;
    if (as->low < as->high)
    {
        pthread_create(&threads[0], NULL, &mergeSort,&as1);
        pthread_create(&threads[1], NULL, &mergeSort,&as2);
        pthread_join(threads[0], NULL);
        pthread_join(threads[1], NULL);
        merge(as->low, as->mid, as->high);
    }

    pthread_exit(NULL);

}


int main()
{
    ifstream is("m.txt");
    is >>size;
    // creating the array
    arr=new int[size];
    for(int i=0; i<size; i++)
        is >>arr[i];

    arrayStatus ass;
    ass.low=0;
    ass.high=size-1;

    pthread_t thread;

    pthread_create(&thread, NULL, &mergeSort,&ass);
    pthread_join(thread,NULL);

    ofstream out("out.txt");
    out<<"sorted array: ";
    for(int i=0; i<size; i++)
    {
        out<<arr[i]<<"  ";
    }



    return 0;
}
