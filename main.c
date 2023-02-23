#include <stdio.h>
#include <stdlib.h>
#include "fixed.h"

int main()
{
	extern int toBinaryString(char buf[],int a);

	FILE *f_num; //test 숫자리스트를 받아오는 file pointer
	FILE *f_plus_ans; //덧셈 연산의 결과를 받아오는 file pointer
	FILE *f_product_ans; //곱셈 연산의 결과를 받아오는 file pointer
	FILE *f_division_ans; //나눗셈 연산의 결과를 받아오는 file pointer

	char buf[1024];

	fixed num_list[10000];
	fixed ans_plus[9999];
	fixed ans_product[9999];
	fixed ans_division[9999];

	f_num = fopen("/Users/juhong/Library/CloudStorage/OneDrive-아주대학교/대학교/3학년 겨울방학/실전코딩2_2020212223_이주홍/random_list.txt","r");

	if(f_num == NULL || f_plus_ans == NULL || f_product_ans == NULL || f_division_ans == NULL)
	{
		printf("File error\n");
		exit(1);
	}

	for(int i = 0;i<9999;i++)
	{
		fscanf(f_num,"%f",num_list+i);
		fscanf(f_plus_ans,"%f",ans_plus+i);
		fscanf(f_product_ans,"%f",ans_product+i);
		fscanf(f_division_ans,"%f",ans_division+i);
	}
	fscanf(f_num,"%f",&num_list+9999); //number은 index가 하나 많음.
	
	printf("%f %f %f %f\n",f_num[0],f_plus_ans[0],f_product_ans[0],f_division_ans[0]);
	return 0;
}
