#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int getFileNum(char *root) {
    // 打开目录
    DIR *dir = NULL;
    dir = opendir(root);
    if (dir == NULL) {
        perror("opendir");
        exit(1);
    }

	// 遍历当前目录
    int cnt = 0;
    char buf[1024] = {0};
    struct dirent *ptr = NULL;

    while((ptr = readdir(dir)) != NULL) {
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0) continue;
        if (ptr->d_type == DT_DIR) { // 目录文件

            sprintf(buf, "%s/%s", root, ptr->d_name);
            cnt += getFileNum(buf);

        }else if (ptr->d_type == DT_REG) cnt++; // 普通文件
    }

    // 关闭目录
    closedir(dir);
    return cnt;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("./fileNum dir\n");
        exit(1);
    }

    int cnt = 0;
    cnt = getFileNum(argv[1]);
    printf("%s %d\n", argv[1], cnt);
    
	return 0;
}
