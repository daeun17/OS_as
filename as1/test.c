#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n, cpu = 0 , io = 0., i, num, j;

    FILE*fp = fopen("test_files/2.inp","r");
    FILE*fo = fopen("batch.out","w");

    fscanf(fp,"%d",&n);

    for(i = 0; i < n ; i++)
    {
        num = 0;
        for(j = 1; ; j++)
        {

            fscanf(fp,"%d",&num);
            printf("num = %d %d \n",num, j);
            if(num == -1)
            {
                break;
            }

            if( j % 2 == 0)
            {
                printf("io = %d \n",num);
                io += num;
            }
            cpu += num;
        
        }

    }
    printf("%d %d", io, cpu);
    fprintf(fo,"%d %d",io, cpu);

    fclose(fp);
    fclose(fo);
    
    return 0;
}