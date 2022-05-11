#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (void)
{
    FILE * fp = fopen("banker.inp","r");
    FILE * fout = fopen("banker.out","w");

    int process, resource, Pnum, num , i ,j;
    int * resourceMAX;
    int ** MAX;
    int * req;
    char s1[10];
    int check = -1;

    fscanf(fp,"%d",&process);
    fscanf(fp,"%d", &resource);

    resourceMAX = (int*)malloc (sizeof(int)*process);
    req = (int*)malloc (sizeof(int)*process);
    MAX = (int**)malloc(sizeof(int*)*process);

    
    for( i = 0 ; i < process ; i++ )
    {
        MAX[i] = (int*) malloc(sizeof(int)*resource);
    }

    ////printf("읽어오기 시작\n");
    for( i = 0 ; i < resource ; i++)
    {
       fscanf(fp,"%d",&num); 
       resourceMAX[i] = num;
    }
    
    fscanf(fp,"\n");

    for(i = 0 ; i < process ; i++)
    {
        for(j = 0; j < resource ; j++)
        {
            fscanf(fp,"%d",&num);
            //printf("%d ",num);
            MAX[i][j] = num;
        }
        //printf("\n");
    }
    //printf("\n");
    
    
    for(i = 0 ; i < process ; i++)
    {
        for(j = 0 ; j < resource ; j++)
        {
            fscanf(fp,"%d",&num);
            //printf("%d ",num);
            resourceMAX[j] = resourceMAX[j] - num;
            MAX[i][j] = MAX[i][j] - num;
        }
    }
    //printf("읽어오기 종료\n");
    
    //printf("리퀘스트 시작\n");
    while(1)
    {
        fscanf(fp,"%s",s1);
        ////printf("%s \n",s1);
        check = -1;
        if(strcmp(s1,"request") == 0)
        {
            //printf("리퀘스트\n");
            fscanf(fp,"%d",&Pnum);
            for(i = 0 ; i <resource ; i++)
            {
                fscanf(fp,"%d",&num);
                //printf("%d ",num);
                req[i] = num;
                if(resourceMAX[i] >= num)
                {
                    if(MAX[Pnum][i] < num)
                    {
                        check = 0;
                        break;
                    }

                }else
                {
                    check = 0;
                    break;
                }
            }
            if(check == -1)
            {
                for(i = 0 ; i < resource ; i++ )
                {
                    MAX[Pnum][i] -= req[i];
                    resourceMAX[i] -= req[i];
                    fprintf(fout,"%d ",resourceMAX[i]);
                    //printf("%d ",resourceMAX[i]);
                }
                fprintf(fout,"\n");
                //printf("\n");
            }else
            {
                for(i = 0 ; i < resource ; i++ )
                {
                    fprintf(fout,"%d ",resourceMAX[i]);
                    //printf("%d ",resourceMAX[i]);
                }
                fprintf(fout,"\n");
                //printf("\n");
            }

        }else if(strcmp(s1,"release") == 0)
        {
            //printf("릴리즈 \n");
            fscanf(fp,"%d",&Pnum);
            //printf("%d \n",Pnum);
            for(i = 0 ; i < resource ; i++ )
            {
                fscanf(fp,"%d",&num);
                MAX[Pnum][i] += num;
                resourceMAX[i] += num;
                fprintf(fout,"%d ",resourceMAX[i]);
                //printf("%d ",resourceMAX[i]);
            }
            fprintf(fout,"\n");
            //printf("\n");

        }else if(strcmp(s1,"quit") == 0)
        {
            //printf("끝\n");
            break;
        }
    }
    





    free(resourceMAX);
    free(MAX);
    free(req);
    fclose(fp);
    fclose(fout);
}