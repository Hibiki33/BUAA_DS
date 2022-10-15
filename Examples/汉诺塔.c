#include <stdio.h>

int cnt = 1;
int n;

void stepdisplay(int i, int a, int b)
{
	printf("step %3d: move tower %-3d from %d to %d\n", cnt, i, a, b);
	cnt++;
}

void move(int i, int a, int b, int c)
{
	if (i == 1)
		stepdisplay(1, a, b);
	else
	{
		move(i - 1, a, c, b);
		stepdisplay(i, a, b);
		move(i - 1, c, b, a);
	}
}

int main()
{
	scanf("%d", &n);
	move(n, 1, 2, 3);
	return 0;
}