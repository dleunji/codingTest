#include <iostream>
#define MAX_N	1005
using namespace std;

int N;
int arr[MAX_N];
int L[MAX_N], R[MAX_N];

void mergeSort(int arr[], int l, int r) {
	if (l >= r) return;
	int m = (l + r) / 2;
	mergeSort(arr, l, m);
	mergeSort(arr, m + 1, r);

	// merge
	int lidx = m - l + 1;
	int ridx = r - m;

	for (int i = 0; i < lidx; ++i) L[i] = arr[i + l];
	for (int j = 0; j < ridx; ++j) R[j] = arr[j + m + 1];

	int i = 0, j = 0, k = l;
	while (i < lidx && j < ridx) {
		if (L[i] < R[j]) {
			arr[k] = L[i];
			i += 1;
		}
		else {
			arr[k] = R[j];
			j += 1;
		}
		k += 1;
	}

	while (i < lidx) {
		arr[k] = L[i];
		i += 1;
		k += 1;
	}
	while (j < ridx) {
		arr[k] = R[j];
		j += 1;
		k += 1;
	}
}

int main() {
	cin >> N;

	for (int i = 0; i < N; ++i) cin >> arr[i];
	
	mergeSort(arr, 0, N - 1);

	int ans = 0, cnt = N;
	for (int i = 0; i < N; ++i, --cnt) {
		ans += arr[i] * cnt;
	}

	cout << ans;

	return 0;
}
