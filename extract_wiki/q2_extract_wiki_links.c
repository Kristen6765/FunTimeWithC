#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
    
    FILE *fp=fopen(argv[1], "rb");
    if(!fp){
       printf("the file doesn't exist, please check your file name is correct.");
       return 0;
    }
    size_t sz;
    fseek(fp, 0L, SEEK_END);
    sz=ftell(fp);
    rewind(fp);
    char *ptr;
    ptr=(char*)malloc(sz);
    if(ptr==0){
      printf("there is not enough storage.");
      return 0;
    }
     size_t tt;
     tt=fread(ptr, 1, sz+1, fp);
     char *p1;
     p1=ptr;
     const char *needle="<a href=\"/wiki/";
     
     p1=strstr(ptr, needle);
     const char *needle2="title";
     char *p3;
     const char *needle3="</a>";
     char *print;
     p1=strstr(p1,needle);


     while(p1){
    
   //p2=strstr(p1, needle2);
    p3=strstr(p1, needle3);
    *p3='\0';
     /* then in the following "if", it will check if there is a "title" between this "<a href..." and "</a>"*/
    if(strstr(p1,needle2)){
    
       for (print=p1+15; *print!='\"'; print ++){
            printf("%c", *print);
     }
       printf("\n");
    }
    
    p1=p3+1;
    p1=strstr(p1,needle);
    //start seachering after the  "\0"
     }
    return 0;
}

   
      
