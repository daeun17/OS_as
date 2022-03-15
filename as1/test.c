#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n, cpu = 0 , io = 0., i, num, j;

    FILE*fp = fopen("batch.inp","r");
    FILE*fo = fopen("batch.out","w");

    fscanf(fp,"%d",&n);

    for(i = 0; i < n ; i++)
    {
        num = 0;
        j = 1;
        while(1)
        {
            fscanf(fp,"%d",&num);
            
            if(num == -1)
            {
                break;
            }else
            {
                if( j % 2 == 0)
                {
                    io += num;
                }
                cpu += num;
            }
            j++;
        }

    }
    fprintf(fo,"%d %d",io, cpu);

    fclose(fp);
    fclose(fo);
    
    return 0;
}