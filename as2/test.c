#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int process_check(int * arrlen, int * task, int n)
{
    int i, end = 0;
    for(i = 0; i < n ; i++)
    {
        if(arrlen[i] > task[i])
        {
            end = i;
            break;
        }else
        {
            end = -1;
        }
    }
    printf("end : %d \n",end);
    return end;
}


int main(void)
{
    int n, i, num, j, cpu = 0, id_t = 0, process = 0 ,check_i = 0, end = 0;
    int**ptr;
    int* arrlen; 
    int* task;
    int* IO_time;

    FILE*fp = fopen("./as2/test_file/2.inp","r");

    fscanf(fp,"%d",&n);
    printf("%d \n", n);
    ptr = (int**)malloc(sizeof(int*)*n);
    arrlen = (int*)malloc(sizeof(int)*n);
    task = (int*)malloc(sizeof(int)*n);
    IO_time = (int*)malloc(sizeof(int)*n);

    memset(arrlen,0,sizeof(int)*n);
    memset(task,0,sizeof(int)*n);
    memset(IO_time,0,sizeof(int)*n);


    for(i = 0; i < n; i++)
    {
        ptr[i] = (int*)malloc(sizeof(int)* 100);
        j = 0;
        while(1)
        {
            fscanf(fp,"%d",&num);
            if(num == -1)
            {
                arrlen[i] = j;
                printf("arrlen = %d\n",arrlen[i]);
                break;
            }
            ptr[i][j] = num;
            printf("ptr = %d ",ptr[i][j]);
            j++;
        }
    }

    while (1)
    {
        for(check_i = 0 ; check_i < n ; check_i++)
        {
            printf("%d %d \n",arrlen[check_i],task[check_i]);
             if(arrlen[check_i] > task[check_i])
            {
                end = check_i;
                break;
            }else
            {
                end = -1;
            }
        }
        printf("end : %d\n ",end);
        if(end == -1)
        {
            break;
        }

        printf("process_check: %d \n",process_check(arrlen,task,n));
        printf("process start\n");
        for(i = 0; i < n ;i++)
        {
            if(IO_time[i] <= cpu )//IO종료
            {
                if(IO_time[i] == 0)
                {
                    printf("first process %d\n",i);
                    process = i;
                    break;
                }
                if(IO_time[i] != -1)
                {
                    printf("process %d IO end\n",i);
                    process = i;
                    task[process]++;
                    printf("process %d task\n",task[process]);
                    break;
                }
            }else
            {
                process = -1;//모두 IO중 이다
            }
           
        }

        if(process == -1)
        {
            id_t += 1;
            cpu += 1;
        }else
        {
            printf("process %d cpu\n",process);
            
            cpu += ptr[process][task[process]];
            task[process]++;
            if(task[process] >= arrlen[process] - 1)
            {
                IO_time[process] = -1;
                task[process]++;
            }else
            {
                IO_time[process] = cpu + ptr[process][task[process]];
            }
            
            printf("process %d IO_time %d task %d cpu %d \n",process,IO_time[process],task[process],cpu);
        }
        
    }

    printf("%d %d",cpu,id_t);
  



    fclose(fp);
    free(ptr);
    free(arrlen);

}