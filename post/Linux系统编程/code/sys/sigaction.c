#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void docatch(int signo) {
    printf("%d signal is catch\n", signo);
    sleep(5);
    printf("catch is done\n");
}

int main() {
    struct sigaction act;
    act.sa_handler = docatch;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGQUIT); // 设置捕捉期间的屏蔽
    act.sa_flags = 0; // 默认属性, 信号捕捉执行期间, 自动屏蔽本信号

    int ret = sigaction(SIGINT, &act, NULL);
    if (ret < 0) {
        perror("sigaction error");
        exit(1);
    }
    while (1);
    return 0;
}
