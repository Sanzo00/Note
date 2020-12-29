#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int flg = 10;

    while (flg--) {
        sleep(1);
        printf("flg = %d\n", flg);
    }

    return 0;
}

