#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int *pages;
int *frames;
typedef struct clockFrames
{
    int star;
    int pageNumber;
} clockFrames;

clockFrames *clockframes;

int optimal(int n,int sizeOfpages)
{
    int f1,f2,f3,future[n],fault=0,position,max,f=0;
    int q=0;
    for (int i=0; i<sizeOfpages; i++)
    {
        f1=0;
        f2=0;
        f=0;
        for(int j=0; j<n; j++)
        {
            if(frames[j]==pages[i])
            {
                f1=f2=1;
                break;
            }
        }
        if(f1==0)
        {
            for(int j=0; j<n; j++)
                if(frames[j]==-1)
                {
                    f2=1;
                    frames[j]=pages[i];
                    break;
                }
        }
        if(f2==0)
        {
            fault++;
            f=1;
            f3=0;
            for(int j=0; j<n; j++)
            {
                future[j]=-1;
                for (int q=i+1; q<sizeOfpages; q++)
                {
                    if(pages[q]==frames[j])
                    {
                        future[j]=q;
                        break;
                    }

                }
            }
            for(int j=0; j<n; j++)
            {
                if(future[j]==-1)
                {
                    position=j;
                    f3=1;
                    break;
                }
            }
            if(f3 ==0)
            {
                max = future[0];
                position = 0;

                for(int j = 1; j < n; j++)
                {
                    if(future[j] > max)
                    {
                        max = future[j];
                        position = j;
                    }
                }
            }
            frames[position] = pages[i];



        }
        printf("\n");
        if(pages[i]<10)
            printf("0%d",pages[i]);
        else
            printf("%d",pages[i]);
        if(f==1)
            printf(" F   ");
        else
            printf("     ");


        for(int j = 0; j < n ; ++j)
        {
            if(frames[j]!=-1)
            {
                if(frames[j]<10)
                    printf("0%d ",frames[j]);
                else
                    printf("%d ",frames[j]);
            }

        }

    }
    return fault;


}
int LRU(int n,int sizeOfpages)
{
    int f1,f2,f3,past[n],fault=0,position,min,f=0;
    int q=0;
    for (int i=0; i<sizeOfpages; i++)
    {
        f1=0;
        f2=0;
        f=0;
        for(int j=0; j<n; j++)
        {
            if(frames[j]==pages[i])
            {
                f1=f2=1;
                break;
            }
        }
        if(f1==0)
        {
            for(int j=0; j<n; j++)
                if(frames[j]==-1)
                {
                    f2=1;
                    frames[j]=pages[i];
                    break;
                }
        }
        if(f2==0)
        {
            fault++;
            f=1;
            f3=0;
            for(int j=0; j<n; j++)
            {
                past[j]=-1;
                for (int q=i-1; q>0; q--)
                {
                    if(pages[q]==frames[j])
                    {
                        past[j]=q;
                        break;
                    }

                }
            }

            if(f3 ==0)
            {
                min = past[0];
                position = 0;

                for(int j = 1; j < n; j++)
                {
                    if(past[j] <min)
                    {
                        min = past[j];
                        position = j;
                    }
                }
            }
            frames[position] = pages[i];



        }
        printf("\n");
        if(pages[i]<10)
            printf("0%d",pages[i]);
        else
            printf("%d",pages[i]);
        if(f==1)
            printf(" F   ");
        else
            printf("     ");


        for(int j = 0; j < n ; ++j)
        {
            if(frames[j]!=-1)
            {
                if(frames[j]<10)
                    printf("0%d ",frames[j]);
                else
                    printf("%d ",frames[j]);
            }

        }
    }
    return fault;


}
int FIFO(int n,int sizeOfpages)
{
    int f1,f2,f3,index,fault=0,f=0;
    int q=0;
    for (int i=0; i<sizeOfpages; i++)
    {
        f1=0;
        f2=0;
        f=0;
        for(int j=0; j<n; j++)
        {
            if(frames[j]==pages[i])
            {
                f1=f2=1;
                break;
            }
        }
        if(f1==0)
        {
            for(int j=0; j<n; j++)
                if(frames[j]==-1)
                {
                    f2=1;
                    frames[j]=pages[i];
                    break;
                }
        }
        if(f2==0)
        {
            fault++;
            f=1;

            frames[index++]=pages[i];
            if(index==n)
                index=0;

        }
        printf("\n");
        if(pages[i]<10)
            printf("0%d",pages[i]);
        else
            printf("%d",pages[i]);
        if(f==1)
            printf(" F   ");
        else
            printf("     ");


        for(int j = 0; j < n ; ++j)
        {
            if(frames[j]!=-1)
            {
                if(frames[j]<10)
                    printf("0%d ",frames[j]);
                else
                    printf("%d ",frames[j]);
            }

        }
    }
    return fault;
}

int CLOCK(int n,int sizeOfpages)
{
    int f1,f2,f3,clockIndex=0,fault=0,f=0;
    int q=0;
    for (int i=0; i<sizeOfpages; i++)
    {
        f1=0;
        f2=0;
        f=0;
        for(int j=0; j<n; j++)
        {
            if(clockframes[j].pageNumber==pages[i])
            {
                f1=f2=1;
                clockframes[j].star=1;

                break;
            }
        }
        if(f1==0)
        {
            for(int j=0; j<n; j++)
                if(clockframes[j].pageNumber==-1)
                {
                    f2=1;
                    clockframes[j].pageNumber=pages[i];
                    clockframes[j].star=1;
                    clockIndex++;
                    if(clockIndex==n)
                        clockIndex=0;
                    break;
                }
        }
        if(f2==0)
        {
            fault++;
            f=1;
            f3=0;
            while(1)
            {
                if(clockframes[clockIndex].star==0)
                {
                    clockframes[clockIndex].pageNumber=pages[i];
                    clockframes[clockIndex].star=1;
                    clockIndex++;
                    if(clockIndex==n)
                        clockIndex=0;

                    break;
                }
                else
                {
                    clockframes[clockIndex].star=0;
                    clockIndex++;
                    if(clockIndex==n)
                        clockIndex=0;

                }
            }


        }
        printf("\n");
        if(pages[i]<10)
            printf("0%d",pages[i]);
        else
            printf("%d",pages[i]);
        if(f==1)
            printf(" F   ");
        else
            printf("     ");


        for(int j = 0; j < n ; ++j)
        {
            if(clockframes[j].pageNumber!=-1)
            {
                if(clockframes[j].pageNumber<10)
                    printf("0%d ",clockframes[j].pageNumber);
                else
                    printf("%d ",clockframes[j].pageNumber);
            }

        }
    }
    return fault;


}



int main()
{


    int n;
    scanf("%d",&n);
    char *option;
    scanf("%s",option);
    frames= (int*)malloc(n*sizeof(int));
    pages= (int*)malloc(5000*sizeof(int));

    int sizeOfpages=0;

    for(int i = 0; i < n; ++i)
    {
        frames[i] = -1;
    }
    while(1)
    {
        int x;
        scanf("%d",&x);

        if(x>-1)
        {

            pages[sizeOfpages++]=x;
        }
        else
            break;
    }
    if(!strcmp(option,"FIFO"))
    {
        printf("Replacement Policy = FIFO\n-------------------------------------");
        printf("\nPage   Content of Frames\n----   -----------------");
        int faults=FIFO(n,sizeOfpages);
        printf("\n-------------------------------------");
        printf("\nNumber of page faults = %d\n",faults);
    }
    else if(!strcmp(option,"LRU"))
    {
        printf("Replacement Policy = LRU\n-------------------------------------");
        printf("\nPage   Content of Frames\n----   -----------------");
        int faults=LRU(n,sizeOfpages);
        printf("\n-------------------------------------");
        printf("\nNumber of page faults = %d\n",faults);
    }
    else if(!strcmp(option,"OPTIMAL"))
    {
        printf("Replacement Policy = OPTIMAL\n-------------------------------------");
        printf("\nPage   Content of Frames\n----   -----------------");
        int faults=optimal(n,sizeOfpages);
        printf("\n-------------------------------------");
        printf("\nNumber of page faults = %d\n",faults);
    }
    else if(!strcmp(option,"CLOCK"))
    {

        clockframes=(clockFrames*)malloc(n*sizeof(clockFrames));

        for(int i = 0; i < n; ++i)
        {
            clockframes[i].pageNumber = -1;
        }

        printf("Replacement Policy = CLOCK\n-------------------------------------");
        printf("\nPage   Content of Frames\n----   -----------------");
        int faults=CLOCK(n,sizeOfpages);
        printf("\n-------------------------------------");
        printf("\nNumber of page faults = %d\n",faults);
    }


    return 0;
}

