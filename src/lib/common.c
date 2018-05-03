#include <common.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

// definido par nao dar warnings ao usar a funcao da GNU
char * mystrdup (const char *s) {
    if(s == NULL) return NULL;
    char *d = malloc (strlen (s) + 1);
    if (d == NULL) return NULL;
    strcpy (d,s);
    return d;
}

char** mystrdups(char** s) {
    if(!s) return NULL;
    int l = nTags(s);
    char** n=malloc((l+1)*sizeof(char*));
    if (n == NULL){
        printf("Algo está errado\n");
        return NULL;
    }
    int i = 0;
    while(s[i]!=NULL){
       n[i]= mystrdup(s[i]);
       i++;
    }
    return n;
}
