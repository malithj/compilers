#include <stdio.h>

#define N 10

void bubble_sort(int * a);
void recursive_bubble_sort(int * a);
int r_bubble_sort(int * a, int idx);

int main() {
	int a[N] = {11, 34, 22, 67, 46, 12, 89, 34, 56, 10};

	int i = 0;
	int j = 0;
	int tmp = 0;
	for (i = 0; i < N; i ++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	recursive_bubble_sort(a);

	for (i = 0; i < N; i ++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	return 0;
}


/*int r_bubble_sort(int * a, int idx) {
	int tmp = 0;
	if (idx == N - 1)
		return a[idx];
	if (r_bubble_sort(a, idx + 1) < a[idx]) {
		tmp = a[idx];
		a[idx] = a[idx + 1];
		a[idx + 1] = tmp;
	}
}*/
