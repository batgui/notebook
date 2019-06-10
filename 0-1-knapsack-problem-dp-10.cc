// #include <stdio.h>

// int  max(int a, int b) {return (a > b) ? a : b;}
// int knapSack(int W, int wt[], int val[], int n) {
// 	if (W == 0 || n == 0)
// 		 return 0;
// 	if (W < wt[n - 1])
// 		return knapSack(W, wt, val, n - 1);
// 	return max(val[n - 1] + knapSack(W - wt[n - 1], wt, val, n - 1), knapSack(W, wt, val, n - 1));
// }

// int main() {
// 	int wt[] = {10, 20, 30};
// 	int val[] = {60, 100, 120};
// 	int W = 50;
// 	int n = sizeof(val) / sizeof(val[0]);
// 	printf("%d", knapSack(W, wt, val, n));
// 	return 0;
// }


#include <stdio.h>

int  max(int a, int b) {return (a > b) ? a : b;}
int knapSack(int W, int wt[], int val[], int n) {
	int K[n + 1][W + 1];
	for (int i = 0; i <= n; i++) {
		for (int w = 0; w <= W; w++) {
			if (i==0 || w==0) 
               K[i][w] = 0; 
			if (wt[i - 1] <= w) {
				K[i][w] = max(K[i - 1][w - wt[i - 1]] + val[i - 1], K[i - 1][w]);
			}
			else 
				K[i][w] = K[i - 1][w];

		}
	}
	return K[n][W];
	

}

int main() {
	int wt[] = {10, 20, 30};
	int val[] = {60, 100, 120};
	int W = 50;
	int n = sizeof(val) / sizeof(val[0]);
	printf("%d", knapSack(W, wt, val, n));
	return 0;
}





