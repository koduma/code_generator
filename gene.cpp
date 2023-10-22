//dp
#include <stdio.h>
static int D0[51*2][51*2];
static int D[51*2][51*2];
int main(){
	int N;
	int Q;
	int i, j, k;
	scanf("%d", &N);
	for (i = 1; i <= N; ++i) {
		for (j = 1; j <= N; ++j) {
			int d;
			scanf("%d", &d);
			D0[i][j] = d;
		}
	}
	for (i = 1; i <= N * 2; ++i) {
		for (j = 1; j <= N * 2; ++j) {
			D[i][j] = D0[i][j] + D[i - 1][j] + D[i][j - 1] - D[i - 1][j - 1];
		}
	}
	scanf("%d", &Q);
	for (k = 0; k < Q; ++k) {
		int p;
		int s;
		int taste = 0;
		scanf("%d", &p);
		for (s = 1; s * s <= p; ++s) {
			int t = p / s;
			if (t > N) t = N;
			for (i = 0; i < N; ++i) {
				for (j = 0; j < N; ++j) {
					int taste1 = D[i + s][j + t] - D[i][j + t] - D[i + s][j] + D[i][j];
					int taste2 = D[i + t][j + s] - D[i][j + s] - D[i + t][j] + D[i][j];
					if (taste < taste1) {
						taste = taste1;
					}
					if (taste < taste2) {
						taste = taste2;
					}
				}
			}
		}
		printf("%d\n", taste);
	}
	return 0;
}
