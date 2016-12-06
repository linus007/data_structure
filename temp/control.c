#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"string_split.h"
#include"string_base.h"

void printHelp() {
    printf("show   - show all the students information\n");
    printf("insert - insert one student information as follow\n");
    printf("         insert NAME ID AGE GENDER\n");
    printf("delete - delete one students information as follow\n");
    printf("         delete NAME(xx) ID(xx) AGE(xx) GENDER(xx)\n");
    printf("search - search students information as follow\n");
    printf("         search NAME XX or ID xx or AGE xx or GENDER XX\n");
    printf("exit   - exit current software\n");
    printf("?      - print this help menu\n");
    printf("help   - print this help menu\n");
}
int main() {
    char s[100];
    word_LinkList l;
    createWordLinkList(&l);
    while(1) {
        printf("> ");
        getString(s);
        readString(l, s, strlen(s));
        char *firstWord;
        int len = len_WordLinkList(l);
        if (len > 0) {
            firstWord = l->next->word;
        }
        if (len == 1) {
            if (strcmp(firstWord, "?") == 0 || strcmp(firstWord, "help") == 0) {
                printHelp();
            } else if (strcmp(firstWord, "exit") == 0) {
                break;
            } else if (strcmp(firstWord, "show") == 0) {
                printf("show\n");
            }
        } else if (strcmp(firstWord, "insert") == 0) {
            printf("insert\n");
        } else if (strcmp(firstWord, "search") == 0) {
            printf("search\n");
        } else if (strcmp(firstWord, "delete") == 0) {
            printf("delete\n");
        }
        clear_WordLinkList(&l);
    }
    printf("%s\n", s);
}
