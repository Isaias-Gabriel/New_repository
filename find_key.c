#include <stdio.h>
#include <string.h>

int main(void){
char letras[3] = "efg", test[10]="Hihihihi", test2[10];
int i, j, k;

strncpy(test2,test,6);
printf("%s",test2);

/*
for(i=0;i<3;i++){
    for(j=0;j<3;j++){
        for(k=0;k<3;k++){
            char pal[4];
            if(i!=j && i != k && k != j){
                pal[0]=letras[i];
                pal[1]=letras[j];
                pal[2]=letras[k];
                pal[3]='\0';
                printf("%s\n",pal);
            }
        }
    }
}
*/


return 0;
}
