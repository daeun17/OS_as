#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int taskend (int * tasklen , int * taskcheck , int * task_end_time, int num)
{
    int i;
    for(i = 0; i < num; i++)
    {
        if(tasklen[i] != taskcheck[i])
        {
            return taskcheck[i];
        }else
        {
            task_end_time[i];
        }
    }
    return -1;
}

int main (void)
{
    FILE * fp = fopen("./as3/test_file/test.inp","r");
    FILE * fout = fopen("test.out","w");

    int num = 0;
    int numi = 0;
    int ** task;
    int * tasklen;
    int tasknum = 0;
    int taski = 0;

    int * taskcheck;
    int * task_end_time;

    int time = 0;
    int cpu = 0;
    int qi = 0;
    int i;
    int end = 0;

    int q[1000] = {-1};



    fscanf(fp, "%d", &num);
    printf("num = %d \n",num); //
    task = (int**)malloc(sizeof(int*)*num);
    tasklen = (int*)malloc (sizeof(int)*num);
    taskcheck = (int*)malloc(sizeof(int)*num);
    memset(taskcheck, -1  ,sizeof(int)*num);
    task_end_time = (int*)malloc(sizeof(int)*num);

    for(numi = 0 ; numi <num ; numi++)
    {
        task[numi] = (int*)malloc(sizeof(int*)*100);
        taski = 0;
        tasknum = 0; 
        while(1)
        {
            fscanf(fp,"%d",&tasknum);
            printf("task = %d",tasknum);//
            if(tasknum == -1)
            {
                printf("taski = %d \n",taski);//
                tasklen[numi] = taski;
                break;
            }
            task[numi][taski] = tasknum;
            printf("task = %d",task[numi][taski]);//
            taski++; 
        }

    }

    taski = 0;
    numi = 0;
    qi = 0;

    while (1)
    {
        printf("task = %d time = %d",numi,time);
        /*if(taskend(tasklen, taskcheck,task_end_time, num ) == -1)
        {
            break; // 테스크 전체 종료 확인
        }*/
        end = -1;
        for(i = 0 ; i < num ; i++)
        {
            printf("Tasklen %d\n",tasklen[i]);
            if(tasklen[i] != taskcheck[i])
            {
                end = 0;
                break;
            }else
            {
                task_end_time[i] = time;
            }
        }
        if(end == -1)
        {
            break;
        }
        printf("1\n");
        if(taskcheck[numi] == 0)
        {
            q[qi] = numi;
            taskcheck[numi]++;
            qi++;
        }else
        {
            printf("2\n");
            if(taskcheck[numi]%2 == 1)//홀수(cpu)
            {
                printf("%d %d %d\n", numi, q[0], taskcheck[q[0]]);
                taski = q[0];
                time += task[taski][taskcheck[taski]];
                task[taski][taskcheck[taski]] += time;
                taskcheck[taski]++;

                for(i = 0 ; i < qi ; i++)
                {
                    q[i] = q[i+1];
                }
                q[qi] = -1;
                qi--;
                numi++;
                
                printf("%d %d %d \n",numi, q[0], time);
            }else//짝수 IO
            {
                printf("3\n");
                if(task[numi][taskcheck[numi]] < time)
                {
                    if(q[0] == -1)
                    {
                        numi++;
                    }else
                    {
                        numi = q[0];
                    }
                }else
                {
                    if(numi == num)
                    {
                        time++;
                        cpu++;
                    }else{
                        taskcheck[numi]++;
                        q[qi] = numi;
                    }
                   
                }
            }

        }

    }
    
    printf("%d\n",time);
    for(i=0; i < num; i++)
    {
        printf("%d\n",task_end_time[i]);
    }
    

    free(task);
    free(tasklen);
    free(taskcheck);
    free(task_end_time);

    fclose(fp);
    fclose(fout);


}