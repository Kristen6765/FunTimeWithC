/* FILE: A3_solutions.c is where you will code your answers for Assignment 3.
 * 
 * Each of the functions below can be considered a start for you. They have 
 * the correct specification and are set up correctly with the header file to
 * be run by the tester programs.  
 *
 * You should leave all of the code as is, especially making sure not to change
 * any return types, function name, or argument lists, as this will break
 * the automated testing. 
 *
 * Your code should only go within the sections surrounded by
 * comments like "REPLACE EVERTHING FROM HERE... TO HERE.
 *
 * The assignment document and the header A3_solutions.h should help
 * to find out how to complete and test the functions. Good luck!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "A3_provided_functions.h"

unsigned char*
bmp_open( char* bmp_filename,        unsigned int *width, 
          unsigned int *height,      unsigned int *bits_per_pixel, 
          unsigned int *padding,     unsigned int *data_size, 
          unsigned int *data_offset                                  )
{
  unsigned char *img_data=NULL;
  
  FILE *bmpfile = fopen(bmp_filename, "rb");
   if(bmpfile ==NULL){
      printf("unbale to open the file. \n");
      return NULL;
//because the fuction want to retrun a char*, retun -1 gets warning
   }
   char b, m;
   fread (&b,1,1,bmpfile);
   fread (&m,1,1,bmpfile);
   unsigned int overallFileSize;
   fread(&overallFileSize, 1, sizeof(int), bmpfile);
   rewind(bmpfile);
   
   
   
//sign memory to img_data)
   img_data=(char*)malloc(sizeof(char)*overallFileSize);
     if(img_data==NULL)
      printf("unble to sign memory to the char");

   if(fread(img_data, 1, overallFileSize, bmpfile) != overallFileSize ){
      printf("unable to read the requested %d bytes.\n", overallFileSize);
      return NULL;
    }
    unsigned int* p =(unsigned int*)(img_data+18);
    *width=*p;
    *height=*(unsigned int *)(img_data+22);
    *bits_per_pixel=*(unsigned int*)(img_data+28);
    *bits_per_pixel=*bits_per_pixel&65535;
     //printf("bpp:%d", *bits_per_pixel);
    //get ride of the first 2 btyes in the memory
    unsigned int totalbits=(*bits_per_pixel)*(*width);
     
    *padding =0;
     
    if((totalbits/8)%4!=0)
      *padding=4-(totalbits/8)%4;

    
   
    *data_size=overallFileSize;
    *data_offset=*(unsigned int *)(img_data+10);
   


    
    
    
  return img_data;  
}

void 
bmp_close( unsigned char **img_data )
{
free(*img_data);
*img_data=NULL;
}

unsigned char***  
bmp_scale( unsigned char*** pixel_array, unsigned char* header_data, unsigned int header_size,
           unsigned int* width, unsigned int* height, unsigned int num_colors,
           float scale )
{
  //unsigned char*** new_pixel_array = NULL; 
  unsigned int new_h=(*height)*scale;
  unsigned int new_w=(*width)*scale;
  unsigned char*** new_pixel_array=(unsigned char***)malloc(sizeof(unsigned char**)*new_h);
  if( pixel_array == NULL ){
    printf( "Error: bmp_to_3D_array failed to allocate memory for image of height %d.\n", (*height) );
    return NULL;
  }
 
   for( int row=0; row<new_h; row++ ){
    new_pixel_array[row] = (unsigned char**)malloc( sizeof(unsigned char*) *( new_w) );
    for( int col=0; col<new_w; col++ ){
      new_pixel_array[row][col] = (unsigned char*)malloc( sizeof(unsigned char) * (num_colors) );
    }
  }
  
  unsigned int new_img_size=(new_h*(((new_w*num_colors+3)/4)*4));
   *(unsigned int*) (header_data + 2)=header_size+new_img_size;
   *(unsigned int*)(header_data+18)=new_w;
   *(unsigned int*)(header_data+22)=new_h;
   *width=new_w;
   *height=new_h;
int pre_i, pre_j,post_i,post_j;
int i,j,k;
for(i=0; i<new_h;i++){
  for(j=0;j<new_w;j++){
     for(k=0; k<num_colors;k++){
    
    post_i=i;
    post_j=j;
   pre_i=(unsigned int )(post_i/scale);
    pre_j=(unsigned int)(post_j/scale);
   if(pre_i>=0&&pre_i<(*height)&&pre_j>=0&&pre_j<(*width));
      new_pixel_array[i][j][k]=pixel_array[pre_i][pre_j][k];
     }
   }
}
  
 return new_pixel_array;
}
int 
bmp_collage( char* background_image_filename,     char* foreground_image_filename, 
             char* output_collage_image_filename, int row_offset,                  
             int col_offset,                      float scale )
{
 unsigned char* b_header_data;
 unsigned int b_header_size, b_width, b_height, b_num_colors;
  unsigned char*** b_pixel_array=NULL;

unsigned char* f_header_data;
unsigned int f_header_size, f_width, f_height, f_num_colors;
unsigned char*** f_pixel_array=NULL;

b_pixel_array =bmp_to_3D_array(background_image_filename, &b_header_data, &b_header_size, &b_width, &b_height, &b_num_colors);

if(b_pixel_array==NULL){
  printf("Error: bmp_collage failed for file %s.\n", background_image_filename);
  return -1;
}


f_pixel_array=bmp_to_3D_array(foreground_image_filename, &f_header_data, &f_header_size, &f_width, &f_height, &f_num_colors);

if(f_pixel_array==NULL){
  printf("Error: bmp_collage failed for file %s.\n", foreground_image_filename);
  return -1;
}

printf("You entered %f.\n", scale);
  if(scale<0.1 || scale>10.0){
    printf("Error: sclae argument must be a floating point bewtween 0.1 and 10.0. you entered %f.\n", scale);
    return -1;
}

 unsigned char*** scaled_pixel_array=bmp_scale(f_pixel_array, f_header_data, f_header_size, &f_width, &f_height, f_num_colors, scale);

if(scaled_pixel_array==NULL){
  printf("Error: call to bmp_scale failed!\n");
  return -1;
}


if(row_offset+f_height>b_height||row_offset<0){
  return -1;
}

if(col_offset+f_width>b_width||row_offset<0){
   return -1;
}

int i, j;

for(i=0; i<f_height; i++){
   for(j=0; j<f_width; j++){
     if(scaled_pixel_array[i][j][0]>0){
       b_pixel_array[i+row_offset][j+col_offset][0]=scaled_pixel_array[i][j][0];
       b_pixel_array[i+row_offset][j+col_offset][1]=scaled_pixel_array[i][j][1];
       b_pixel_array[i+row_offset][j+col_offset][2]=scaled_pixel_array[i][j][2];
       b_pixel_array[i+row_offset][j+col_offset][3]=scaled_pixel_array[i][j][3];
      }
     }
    }
        
bmp_from_3D_array(output_collage_image_filename, b_header_data, b_header_size, b_pixel_array, b_width, b_height,b_num_colors);



  
  return 0;
}              

