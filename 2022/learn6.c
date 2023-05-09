
#define _CRT_RUNTIME_WARNINGS
#include <stdio.h>

float find(float[], int, int);
void sub(int* s, int y);

int test0(void);
int test1(void);
int test2(void);

int main()
{
	printf("\n课堂练习 1\n");
	test0();
	printf("\n课堂练习 2\n");
	test1();
	printf("\n课堂练习 3\n");
	test2();
	return 0;
}

int test0()
{
	float s, a[7] = { 2, 6, 3, 8, 3, 12, 9 };
	
	s = find(a, 7, 1);

	printf("%f\n", s); // (1) 打印最大值

	s = find(a, 7, -1); // (2) 调用这个函数 找最小值

	printf("%f\n", s);

	return 0;
}

float find(float p[], int n, int flag)
{
	int i;
	float t, fh;
	if (flag >= 0) fh = 1; else fh = -1;

	t = p[0]; // (3)
	for (i = 1; i < n; i++) {
		if (p[i] * fh > t * fh) {
			t = p[i];
		}
	}

	return t; // (4)
}


int test1()
{
	int a[] = { 3,8,4,2 }, i, x = 0;
	for (i = 0; i < 4; i++)
	{
		sub(a, x);
		printf("%3d", x);
	}
	// 0 0 0 0
	return 0;
}

// 例题使用的是选择排序
// 每一轮遍历中找到最小的一个，并于最前面未排序过的数字交换，如此重复下去完成排序
void sort(float p[], int n) // (1)
{
	int i, j, k;
	float t;
	for (i = 0; i < n - 1; i++) {
		for (k = i, j = i + 1; j < n; j++)
			if (p[k] < p[j]) k = j; // (2)
		if (k != i)// (3)
		{
			t = p[k];
			p[k] = p[i]; // (4)
			p[i] = t; // (5)
		}
	}
}

int test2()
{
	int i;
	float a[7] = { 2,6,3,8,3,12,9 };
	for (i = 0; i < 7; i++) printf("%f ", a[i]);
	// printf("\n", a[i]);
	sort(a, 7); // (6)
	
	for (i = 0; i < 7; i++) printf("%f ", a[i]);
	return 0;
}



void sub(int* s, int y)
{
	static int t = 0;
	y = s[t];
	t++;
}
