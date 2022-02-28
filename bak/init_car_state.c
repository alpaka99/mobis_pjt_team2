#include "init_car_state.h"
#include <stdio.h>
#include <string.h>

char *inputline(FILE *fp)
{
   	char c, i;
   	static char line[256];
 	int flag = 0;

    for(i=0; i<255; i++) {
        c=fgetc(fp);
        if (feof(fp)!=0)
            return NULL;
        if(c=='\n')
            break;
	    if(c=='#')
		    flag=1;
	    if(!flag)
        	line[i] = c;
    }
    line[i] = '\0';
    return line;
}

int init_car_state(Car_state *car){
    char *line, *token_1, *token_2, *token_3;
    int cnt=1;

    FILE *fp = fopen("car_state.txt", "r");
    if (fp == NULL){
        printf("Can not open car_state.txt");
        return 1;
    }
    while(1){
        line = inputline(fp);  
        printf("[%d]\n",cnt);
        if (line == NULL)
            break;
        if(line[0]=='\0')
            continue;
        token_1 = strtok(line, ":");
        token_2 = strtok(NULL, ":");
        if(token_2!=NULL){
            printf("field1 : %s, field2 : %s\n",token_1, token_2);
        }
        switch(cnt){
            case 1:
                car->car_type=token_2;
                printf("case 1\n");
                break;
            case 2:
                car->color=token_2;
                printf("case 2\n");
                break;
            default:
                printf("default\n");
                break;
        }
        cnt++;
    }
    return 0;
}
