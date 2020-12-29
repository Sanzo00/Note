#include <stdio.h>
#include <string.h>

#define MAXARG 8			
#define MAX 1024		
#define MAXCMD 16	

typedef struct command {
    char *argv[MAXARG];		  //ls -l -F -a -R   
    char *in, *out;
} cmd_t;

int parse(char *buf, cmd_t *cmdp)
{
    char *tmp = buf, *curcmd;
    int cmdnum = 0, i = 0, j = 0;
		
    if ((cmdp[cmdnum].argv[0] = strtok(tmp, "|"))) {	  //strsep
		puts(cmdp[cmdnum].argv[0]);					
        cmdnum++;
	}
    while ((cmdp[cmdnum].argv[0] = strtok(NULL, "|"))) {	
        cmdnum++;										
	}
    for (i = 0; i < cmdnum; i++) {		
        curcmd = cmdp[i].argv[0];		
        cmdp[i].in = cmdp[i].out = NULL;

        while (*curcmd) {
            if (*curcmd == ' ') {				
                *curcmd++ = '\0';			
                continue;
            }
            if (*curcmd == '<') {				
                *curcmd = '\0';				
                while (*(++curcmd) == ' ')	
                    ;
                cmdp[i].in = curcmd;		
                if (*curcmd == '\0')
                    return -1;				
                continue;
            }
            if (*curcmd == '>') {				
                *curcmd = '\0';
                while (*(++curcmd) == ' ')
                    ;
                cmdp[i].out = curcmd;
                if (*curcmd == '\0')
                    return -1;
                continue;
            }
            if (*curcmd != ' ' && ((curcmd == cmdp[i].argv[0]) || *(curcmd - 1) == '\0')) {
                cmdp[i].argv[j++] = curcmd++;	
                continue;					
            }
            curcmd++;
        }
        cmdp[i].argv[j] = NULL;
        j = 0;
    }

    return cmdnum;
}

void show(cmd_t *cmdp, int cmdnum)    
{
    int i, j;

    for (i = 0; i < cmdnum; i++) {
        printf("cmd-show:%s,", cmdp[i].argv[0]);

        for(j = 1; cmdp[i].argv[j]; j++)
            printf("argv:%s,", cmdp[i].argv[j]);

        printf("in:%s, out:%s\n", cmdp[i].in, cmdp[i].out);
    }
}

int main(void)
{
    char buf[MAX];		
    int cmdnum;
    cmd_t cmd[MAXCMD];   

    while (1) {
        printf("sh%%");
        fflush(stdout);				
        fgets(buf, MAX, stdin);

        if (buf[strlen(buf) - 1] == '\n')	
            buf[strlen(buf) - 1] = '\0';
        if (strcasecmp(buf, "exit") == 0 || strcasecmp(buf, "quit") == 0 
           ||strcasecmp(buf, "EXIT") == 0 || strcasecmp(buf, "bye") == 0)	
            break;

        cmdnum = parse(buf, cmd);	
        show(cmd, cmdnum);		
    }

    return 0;
}
