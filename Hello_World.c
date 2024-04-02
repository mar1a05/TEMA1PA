#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    FILE *in=fopen("date/t1/d.in", "r");
    FILE *out=fopen("out/r.out", "w");
    
    char s[1024];
    while(fgets(s, 1023, in) !=NULL)
    printf("\n");
    fclose(in);
    fclose(out);
    
    
    
        

    return 0;
}