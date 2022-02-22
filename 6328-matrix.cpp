#include <iostream>
#include <fstream>
#include <pthread.h>
#include <vector>
#include <cstdlib>
#include <time.h>
using namespace std;
int r1,c1,r2,c2;
int **matA,**matB,**matC,**matC2;
//struct for the postion of the element
struct position
{
    int row;
    int col;
};

//multpliction by element function
void *elementMultpication(void *p1)
{

    position *pos= (position *)p1;
    int r=pos->row;
    int c=pos->col;

    for (int n=0; n<c1; n++)
    {
        matC[r][c]+=matA[r][n]*matB[n][c];
    }
    pthread_exit(NULL);
}
////////////////////////////////////////////////////////

//multiplication by row
void *rowMultpication(void *p2)
{

    int *row= (int *)p2;
    int x=*row;
    for (int n=0; n<c2; n++)
    {
        for(int q=0; q<c1; q++)
        {
            matC2[x][n]+=matA[x][q]*matB[q][n];
        }
    }
    pthread_exit(NULL);
}
///////////////////////////////////////////////////////

int main(int argc, char *argv[])
{

    clock_t t1, t2;
    //the input file
    ifstream is("m.txt");
    is >>r1;
    is >> c1;
    //the first matrix creation
    matA=new int*[r1];
    for(int i=0; i<r1; i++)
        matA[i]=new int [c1];
    for(int i=0; i<r1; i++)
    {
        for(int j=0; j<c1; j++)
        {
            is  >> matA[i][j];
        }
    }
    //the second row and col
    is >>r2;
    is >> c2;
    // matrix b creation
    matB=new int*[r2];
    for(int i=0; i<r2; i++)
        matB[i]=new int [c2];
    for(int i=0; i<r2; i++)
    {
        for(int j=0; j<c2; j++)
            is  >> matB[i][j];
    }

    // the first output matrix creation
    matC=new int*[r1];
    for(int i=0; i<r1; i++)
        matC[i]=new int [c2];
    // the second output matrix creation
    matC2=new int*[r1];
    for(int i=0; i<r1; i++)
        matC2[i]=new int [c2];
    //numnber of the threads and elements
    long int numberOfElements=r1*c2;
    if(c1==r2){

    //////////////////////////////////////////////////
    // the element multiplication threads
    t1 = clock();
    pthread_t threads[numberOfElements];
    int p=0;
    for(int i=0; i<r1; i++)
    {
        for (int j=0; j<c2; j++)
        {
            position *pos;
            pos=(position*)malloc(sizeof(position));

            pos->col=j;
            pos->row=i;

            int rc =pthread_create(&threads[p], NULL, &elementMultpication,pos);
            p++;

        }
    }
    p=0;
    for(int i=0; i<r1; i++)
    {
        for (int j=0; j<c2; j++)
        {
            pthread_join(threads[p],NULL);
            p++;

        }
    }
    t2 = clock();
    double t3 =(t2 - t1) /(double)CLOCKS_PER_SEC;
    /////////////////////////////////////////////////////
    //the row multiplcation threads
    t1 = clock();
    pthread_t threads2[r1];
    int x[r1];
    for(int i=0; i<r1; i++)
    {

        x[i]=i;
        int rc2 =pthread_create(&threads2[i], NULL, rowMultpication,&x[i]);

    }
    for(int i=0; i<r1; i++)
        pthread_join(threads2[i],NULL);
    t2 = clock();
    double t4 =(t2 - t1) /(double)CLOCKS_PER_SEC;

    //////////////////////////////////////////////////////////////////

    ofstream out("out.txt");
    out<<"by Row:\n";
    for(int i=0; i<r1; i++)
    {
        for (int j=0; j<c2; j++)
        {
            out << matC2[i][j]<<" ";
        }
        out<<"\n";
    }
    out<<"time :"<<t4<<"\n\n";
    out<<"by element:\n";
    for(int i=0; i<r1; i++)
    {
        for (int j=0; j<c2; j++)
        {
            out << matC[i][j]<<" ";
        }
        out << "\n";
    }
    out<<"time :"<<t3;
    }else
    {
    ofstream out("out.txt");
    out<<"Multipication of Matrix is not Possible !!";

    }


    return 0;
}
