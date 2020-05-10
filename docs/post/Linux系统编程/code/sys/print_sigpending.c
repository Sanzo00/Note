#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void print_ped(sigset_t *ped) {
    for (int i = 0; i < 32; ++i) {
        if (sigismember(ped, i) == 1) { // 判断信号是否在集合中
            putchar('1');
        }else {
            putchar('0');
        }
    }
    printf("\n");
}
int main() {
    sigset_t myset, oldset, ped;
    sigemptyset(&myset); // 置空信号集
    sigaddset(&myset, SIGQUIT); // 添加对应信号置1
    sigaddset(&myset, SIGINT);
    sigaddset(&myset, SIGTSTP);

    sigprocmask(SIG_BLOCK, &myset, &oldset); // 修改阻塞信号集
    
    while (1) {
        sigpending(&ped); // 获取未决信号集
        print_ped(&ped);
        sleep(1);
    } 
    return 0;
}
