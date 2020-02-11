#include<stdio.h>
#include<stdlib.h>
#define size 1000
char arr[size/2][size];


int mylog2(int ii){
  int i=0;
  while(ii>0){
   i++;
    ii=ii/2;
  }
  return i-1;
}
 

int test(int level, int height){
   int tt;
    tt=mylog2(height+1);
    tt=1<<tt;

    if(tt!=height+1){
    printf("ERROR:Height does not allow evenly dividing requested number of level.");
    exit(0);
    }
    if(level>mylog2(height+1)){
    printf("ERROR:Height does not allow evenly dividing requested number of level.");
    exit(0);
    }
    return 0;
    }     

int tri(int row)
{ 
   int star=1;
   int y,x;
   for( y=0; y<row; y++){
         
        for(x=0; x<=(row-1)*2; x++)
             arr[y][x]=' ';
        
     
    }
   for(y=0; y<row; y++){
       
          for(x=0; x<y*2+1; x=x+1)
             arr[y][x+row-y-1]='*';
       
    }     
    
   
    
      
      return 0;       

}


int sier_patten(int x1,int y1,int x2,int y2,int x3,int y3,int level,char c){
  
    
    int x11, y11, x22, y22, x33, y33;
    x11=x1;
    y11=y2;
    x22=(x2-x1)/2+x1;
    y22=(y2-y1)/2+y1;
    x33=(x3-x1)/2+x1;
    y33=(y3-y1)/2+y1;

   
   
    for(int y=y22; y<=y11; y++){
         

         for(int x=x22-1; x<x33; x++){
       
             arr[y+1][x+1]=c;
       }
      x22++;
      x33--;
    }
    
    
    x11=x1;
    y11=y2;
    x22=(x2-x1)/2+x1;
    y22=(y2-y1)/2+y1;
    x33=(x3-x1)/2+x1;
    y33=(y3-y1)/2+y1;

    if(level>2){
      
      sier_patten(x11,y1,x22,y22,x33,y33,level-1,' ');
      sier_patten(x22-1,y22,x2,y2,x11-1,y11,level-1,' ');
      sier_patten(x33+1,y33,x11+1,y11,x3,y3,level-1,' ');
    }
    return 0;

}

int main(int argc, char *argv[])
{
  if(argc !=3){
       printf("ERROR: Wrong number of arguments. Two required.");
     return 0;
  }
  int height, level, row;
  height=atoi(argv[1]);
  level=atoi(argv[2]);
  

  if(height>size-1){
   printf("why would you want to print someting large like this? Please choose again.");
   return 0;
  }
  
  if(height<0|| height%2==0){
     printf("ERROR: Bad argument. Height must be positive odd integer.");
      return 0;
  }
  if(level<1){
      printf("Hey, level can't be smaller than 1, please choose again.");
      return 0;
  }
  test(level,height);
  
  row=height/2+1;
  
  tri(row);
   
  int x1,y1,x2,y2,x3,y3;
  x1= row-1;
  y1=0;
  x2=0;
  y2=row-1;
  x3=height-1;
  y3=row-1;
  if(level>1)
    sier_patten(x1,y1,x2,y2,x3,y3,level,' ');

  int y;

  for(y=0;y<row; y++){
 
      
     for(int x=0; x<=height; x++){
       
       printf("%c", arr[y][x]);
       
       
    }
     printf("\n");
  }
  for(y=row-2; y>=0; y--){
      
        for(int x=0; x<=height; x++){
          printf("%c", arr[y][x]);
    }
     printf("\n");
}
  return 0;

}







