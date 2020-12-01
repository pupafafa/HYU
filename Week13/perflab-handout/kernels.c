/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "Leewonseok",              /* name */

    "2016024957",     /* student ID */
    "wishluz1997@gmail.com",  /* student email */

    "",                   /* Second member full name (leave blank if none) */
    ""                    /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst){
    //naive_rotate(dim, src, dst);
    int block=32;
    int dim_b=dim-1;
    int block1,block2,i,j;
    for(block1=0;block1<dim;block1+=block){
	    for(block2=0;block2<dim;block2+=block){
		    int end_row=block1+block;
		    for(i=block1;i<end_row;i++){
			    int end_col=block2+block;
			    for(j=block2;j<end_col;j++){
				    dst[(dim_b-i)*dim+j]=src[j*dim+i];
			    }
		    }
	    }
    }
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);   
    add_rotate_function(&rotate, rotate_descr);   
    /* ... Register additional test functions here */
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) 
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	    accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst) 
{
    //naive_smooth(dim, src, dst);
    int i,j,k;
    //angle init
	dst[0].red = (src[0].red+src[1].red+src[dim].red+src[dim+1].red)/4;
	dst[0].green = (src[0].green+src[1].green+src[dim].green+src[dim+1].green)/4;
	dst[0].blue = (src[0].blue+src[1].blue+src[dim].blue+src[dim+1].blue)/4;
	i=dim-1;
	dst[i].red = (src[i-1].red+src[i].red+src[i-1+dim].red+src[i+dim].red)/4;
	dst[i].green = (src[i-1].green+src[i].green+src[i-1+dim].green+src[i+dim].green)/4;
	dst[i].blue = (src[i-1].blue+src[i].blue+src[i-1+dim].blue+src[i+dim].blue)/4;
	i=(dim-1)*dim;
	dst[i].red = (src[i-dim].red+src[i-dim+1].red+src[i].red+src[i+1].red)/4;
	dst[i].green = (src[i-dim].green+src[i-dim+1].green+src[i].green+src[i+1].green)/4;
	dst[i].blue = (src[i-dim].blue+src[i-dim+1].blue+src[i].blue+src[i+1].blue)/4;
	i=dim*dim-1;
	dst[i].red = (src[i-dim].red+src[i-dim-1].red+src[i-1].red+src[i].red)/4;
	dst[i].green = (src[i-dim].green+src[i-dim-1].green+src[i-1].green+src[i].green)/4;
	dst[i].blue = (src[i-dim].blue+src[i-dim-1].blue+src[i-1].blue+src[i].blue)/4;

	//center first
	for(i=1;i<dim-1;i++)
		for(j=1;j<dim-1;j++)
		{
			k=(i*dim)+j;
			dst[k].red = (src[k-dim-1].red+src[k-dim].red+src[k-dim+1].red+src[k-1].red+src[k].red+src[k+1].red+src[k-1+dim].red+src[k+dim].red+src[k+dim+1].red)/9;
			dst[k].green = (src[k-dim-1].green+src[k-dim].green+src[k-dim+1].green+src[k-1].green+src[k].green+src[k+1].green+src[k-1+dim].green+src[k+dim].green+src[k+dim+1].green)/9;
			dst[k].blue = (src[k-dim-1].blue+src[k-dim].blue+src[k-dim+1].blue+src[k-1].blue+src[k].blue+src[k+1].blue+src[k-1+dim].blue+src[k+dim].blue+src[k+dim+1].blue)/9;
		}
	// Edge next
	j=dim-1;
	for(i=1;i<j;i++)
	{
		dst[i].red = (src[i-1].red+src[i].red+src[i+1].red+src[i-1+dim].red+src[i+dim].red+src[i+1+dim].red)/6;
		dst[i].green = (src[i-1].green +src[i].green+src[i+1].green+src[i-1+dim].green+src[i+dim].green+src[i+1+dim].green)/6;
		dst[i].blue = (src[i-1].blue+src[i].blue+src[i+1].blue+src[i-1+dim].blue+src[i+dim].blue+src[i+1+dim].blue)/6;
	}
	i=(dim-1)*(dim)+1;
	j=(dim*dim)-1;
	for(;i<j;i++)
	{
		dst[i].red = (src[i-1].red+src[i].red+src[i+1].red+src[i-dim].red+src[i-1-dim].red+src[i+1-dim].red)/6;
		dst[i].green = (src[i-1].green +src[i].green+src[i+1].green+src[i-dim].green+src[i-1-dim].green+src[i+1-dim].green)/6;
		dst[i].blue = (src[i-1].blue+src[i].blue+src[i+1].blue+src[i-dim].blue+src[i-1-dim].blue+src[i+1-dim].blue)/6;		
	}
	i=dim;j=(dim-1)*dim;
	for(;i<j;i+=dim)
	{
		dst[i].red = (src[i-dim].red+src[i-dim+1].red+src[i].red+src[i+1].red+src[i+dim].red+src[i+dim+1].red)/6;
		dst[i].green = (src[i-dim].green+src[i-dim+1].green+src[i].green+src[i+1].green+src[i+dim].green+src[i+dim+1].green)/6;
		dst[i].blue = (src[i-dim].blue+src[i-dim+1].blue+src[i].blue+src[i+1].blue+src[i+dim].blue+src[i+dim+1].blue)/6;
	}
	i=dim*2-1;j=(dim)*(dim)-1;
	for(;i<j;i+=dim)
	{
		dst[i].red = (src[i-dim].red+src[i-dim-1].red+src[i-1].red+src[i].red+src[i+dim-1].red+src[i+dim].red)/6;
		dst[i].green = (src[i-dim].green +src[i-dim-1].green +src[i-1].green +src[i].green +src[i+dim-1].green +src[i+dim].green )/6;
		dst[i].blue = (src[i-dim].blue+src[i-dim-1].blue+src[i-1].blue+src[i].blue+src[i+dim-1].blue+src[i+dim].blue)/6;
	}

}


/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* ... Register additional test functions here */
}

