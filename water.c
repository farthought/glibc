#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i;
    int j;
    int sum = 0;
    
    i = atoi(argv[1]);
    sum += i;
    printf("i=%d, sum=%d\n",i,sum);

    while(i>=4)
    {
        j = i / 4;
        i = i % 4;
        i = i + j;
        sum += j;
        printf("%d\n", sum);
    }

    printf("The max num is %d\n", sum);

    return 0;
}
