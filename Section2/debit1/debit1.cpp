// debit1.cpp 对应书上 S2 的 习题35

#include <stdio.h>

#define scanf scanf_s						//替换scanf为scanf_s，因为在VS2019里使用scanf会报错。用DEVC++调试时将此行注释掉。


int main()
{
	float loan, IR, Mpay,rate;
	printf("Enter amount; of loan:");
	scanf("%f", &loan);
	printf("Enter interest rate:");
	scanf("%f", &IR);
	printf("Enter monthly payment:");
	scanf("%f", &Mpay);

	for (int i = 1; i <= 3; i++)			//计算3次
	{
		loan = loan - Mpay + loan * ((IR / 100.0f) / 12.0f);
		printf("M%d:$%.2f\n", i, loan);
	}
	
}