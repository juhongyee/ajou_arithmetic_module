#include <stdio.h>
#include <stdlib.h>
#include "fixed.h"
#define PRECISION_TEST 0
#define SPEED_TEST 1
#define DEBUG 0
int main()
{
#if PRECISION_TEST
#define NUM_DATA 99999
	extern int toBinaryString(char buf[],int a);

	FILE *f_num; //test 숫자리스트를 받아오는 file pointer
	FILE *f_plus_ans; //덧셈 연산의 결과를 받아오는 file pointer
	FILE *f_product_ans; //곱셈 연산의 결과를 받아오는 file pointer
	FILE *f_division_ans; //나눗셈 연산의 결과를 받아오는 file pointer

	char buf[1024];

	float num_list[NUM_DATA+1];
	float ans_plus[NUM_DATA];
	float ans_product[NUM_DATA];
	float ans_division[NUM_DATA];

	f_num = fopen("./random_list2.txt","r");
	f_plus_ans = fopen("./plus_answer2.txt","r");
	f_product_ans = fopen("./product_answer2.txt","r");
	f_division_ans = fopen("./divide_answer2.txt","r");

	if(f_num == NULL || f_plus_ans == NULL || f_product_ans == NULL || f_division_ans == NULL)
	{
		printf("File error\n");
		exit(1);
	}
	
	for(int i = 0;i<NUM_DATA;i++)
	{
		fscanf(f_num,"%f",num_list+i);
		fscanf(f_plus_ans,"%f",ans_plus+i);
		fscanf(f_product_ans,"%f",ans_product+i);
		fscanf(f_division_ans,"%f",ans_division+i);
	}
	fscanf(f_num,"%f",num_list+NUM_DATA); //number은 index가 하나 많음.
	
	float allow_error = 0.01;
	
	int add_count = 0;
	int mul_f_count = 0;
	int mul_o_count = 0;
	int mul_64_count = 0;
	int div_f_count = 0;
	int div_count = 0;
	int div_64_count = 0;
	int div_reciprocal_count = 0;

	//precision_test_start
	for(int i = 0;i<NUM_DATA;i++)
	{
		fixed fx = fromFloat(num_list[i]);
		fixed gx = fromFloat(num_list[i+1]);

		//add test
		fixed add_ret = add(2,fx,gx);

		//product test
		fixed mul_f_ret = fx_mul_f(fx,gx);
		fixed mul_o_ret = fx_mul_o(fx,gx);
		fixed mul_64_ret = fx_mul_64(fx,gx);
		//mul_with_integer는 따로 test

		//division test
		fixed div_f_ret = fx_div_f(fx,gx);
		fixed div_ret = fx_div(fx,gx); //error 위험 있음.
		fixed div_64_ret = fx_div_64(fx,gx);
		fixed div_reciprocal_ret = fx_div_reciprocal(fx,gx);

		//Check whether the diffence is smaller than allow error.
		if(ans_plus[i]-fromFloat(add_ret)<allow_error) add_count++;
		//else printf("i : %d ans_plus : %f result : %f difference : %f",i,ans_plus[i],toFloat(add_ret),ans_plus[i]-fromFloat(add_ret));

		if(ans_product[i]-toFloat(mul_f_ret)<allow_error) mul_f_count++;
		if(ans_product[i]-toFloat(mul_o_ret)<allow_error) mul_o_count++;
		if(ans_product[i]-toFloat(mul_64_ret)<allow_error) mul_64_count++;

		if(ans_division[i]-toFloat(div_f_ret)<allow_error) div_f_count++;
		if(ans_division[i]-toFloat(div_ret)<allow_error) div_count++;
		if(ans_division[i]-toFloat(div_64_ret)<allow_error) div_64_count++;
		if(ans_division[i]-toFloat(div_reciprocal_ret)<allow_error) div_reciprocal_count++;

	}

	printf("add: %d mul_f : %d mul_o : %d mul_64 : %d div_f : %d div : %d div_64 : %d div_reciprocal : %d\n",add_count,mul_f_count,mul_o_count,mul_64_count,div_f_count,div_count,div_64_count,div_reciprocal_count);

#endif

#if SPEED_TEST
#define NUM_DATA 9999999

	FILE *f_num; //test 숫자리스트를 받아오는 file pointer
#if DEBUG
	printf("0\n");
#endif
	f_num = fopen("./random_list2.txt","r");
	
	//FILE CHECK
	if(f_num == NULL)
	{
		printf("File error\n");
		exit(1);
	}

	float* num_list = (float*)malloc(sizeof(float)*(NUM_DATA)+1);

	//input num_list
	for(int i = 0;i<=NUM_DATA;i++)	fscanf(f_num,"%f",num_list+i);

#if DEBUG
	printf("1\n");
#endif
	fixed(*fp[7])(fixed,fixed);
	fp[0] = fx_mul_f;
	fp[1] = fx_mul_o;
	fp[2] = fx_mul_64;
	fp[3] = fx_div_f;
	fp[4] = fx_div;
	fp[5] = fx_div_64;
	fp[6] = fx_div_reciprocal;

	for(int i = 0;i<NUM_DATA;i++)
	{
		fixed fx = fromFloat(num_list[i]);
		fixed gx = fromFloat(num_list[i+1]);
		add(2,fx,gx);
	}
#if DEBUG
	printf("2\n");
#endif
	for(int i = 0; i<7;i++)
	{
		for(int j = 0;j<NUM_DATA;j++)
		{
			fixed fx = fromFloat(num_list[j]);
			fixed gx = fromFloat(num_list[j+1]);
			gx==0 ? :fp[i](fx,gx);
		}
	}
#if DEBUG
	printf("3\n");
#endif
	printf("SPEED TEST COMPLETE\n");
	free(num_list);
#endif
	return 0;
}
