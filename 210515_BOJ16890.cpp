#include <cstdio>
#define MAX_LEN		300005

/*** 16890 :: 창업 ***
두 사람이 고른 문자열에서 순서대로 하나씩 골라 길이 N의 문자열 완성
***/

int N;
char koo[MAX_LEN], cube[MAX_LEN], result[MAX_LEN];
char L[MAX_LEN], R[MAX_LEN];
bool v[MAX_LEN];

void ascending_sort(char *arr, int l, int r) {
	if (l >= r) return;
	int m = (l + r) / 2;
	ascending_sort(arr, l, m);
	ascending_sort(arr, m + 1, r);

	// merge
	int lidx = m - l + 1;
	int ridx = r - m;
	for (int i = 0; i < lidx; ++i) L[i] = arr[i + l];
	for (int j = 0; j < ridx; ++j) R[j] = arr[j + m + 1];

	int i = 0, j = 0, k = l;
	while (i < lidx && j < ridx) {
		if (L[i] < R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < lidx) {
		arr[k] = L[i];
		i++; k++;
	}
	while (j < ridx) {
		arr[k] = R[j];
		j++; k++;
	}
}

void descending_sort(char *arr, int l, int r) {
	if (l >= r) return;
	int m = (l + r) / 2;
	descending_sort(arr, l, m);
	descending_sort(arr, m + 1, r);

	// merge
	int lidx = m - l + 1;
	int ridx = r - m;
	for (int i = 0; i < lidx; ++i) L[i] = arr[i + l];
	for (int j = 0; j < ridx; ++j) R[j] = arr[j + m + 1];

	int i = 0, j = 0, k = l;
	while (i < lidx && j < ridx) {
		if (L[i] > R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < lidx) {
		arr[k] = L[i];
		i++; k++;
	}
	while (j < ridx) {
		arr[k] = R[j];
		j++; k++;
	}
}

int main() {
	scanf("%s %s", &koo, &cube);

	N = 0;
	while (koo[N] != '\0') {
		N++;
	}

	ascending_sort(koo, 0, N - 1);
	descending_sort(cube, 0, N - 1);

	int idx, cidx = 0, kidx = 0;
	for (int i = 0; i < N; ++i) {
		int ktmp = kidx, ctmp = cidx;
		int jump = 0;
		if (i & 1) {
			// cubelover's turn
			while (i + jump < N - 1 && cube[ctmp] < koo[ktmp]) {
				ktmp++; jump++;
			}
			if (i == N - 1) {
				while (result[jump] != '\0') jump++;
				result[jump] = cube[cidx];
			}
			else {
				idx = i + jump; // index of "remain"
				while (v[idx]) {

				}
				result[idx] = cube[cidx];
				cidx++;
			}
		}
		else {
			// koosaga's turn (start!)
			while (i + jump < N - 1 && cube[ctmp] < koo[ktmp]) {
				ctmp++; jump++;
			}
			if (i == N - 1) {
				while (result[jump] != '\0') jump++;
				result[jump] = koo[kidx];
			}
			else {
				idx = i + jump; // index of "remain"
				result[idx] = koo[kidx];
				kidx++;
			}
		}
		v[idx] = true;
	}
	result[N] = '\0';

	printf("%s", result);


	return 0;
}