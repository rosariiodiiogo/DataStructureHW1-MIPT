#include <iostream>

void exchange(int &a, int &b) {
    int c = a;
    a = b;
    b = c;
}

int partition(int A[], int l, int r) {
    int pivot = A[r];
    int i = l - 1;
    for (int j = l; j < r; ++j) {
        if (A[j] <= pivot) {
            ++i;
            exchange(A[i], A[j]);
        }
    }
    exchange(A[i + 1], A[r]);
    return i + 1;
}

int quicksort(int A[], int l, int r, int k) {
    if (l == r)
        return A[l];
    int pivotIndex = partition(A, l, r);
    int leftSize = pivotIndex - l + 1;
    if (k == leftSize)
        return A[pivotIndex];
    else if (k < leftSize)
        return quicksort(A, l, pivotIndex - 1, k);
    else
        return quicksort(A, pivotIndex + 1, r, k - leftSize);
}

int main() {
    long long n;
    int k, A0, A1;
    std::cin >> n >> k >> A0 >> A1;

    const int MOD = 10000000 + 4321;
    int *A = new int[(n < 2 ? 2 : n)];

    A[0] = A0;
    A[1] = A1;
    for (long long i = 2; i < n; ++i) {
        A[i] = static_cast<int>(((long long)A[i-1] * 123 + (long long)A[i-2] * 45) % MOD);
    }

    int answer = quicksort(A, 0, n - 1, k);
    std::cout << answer << '\n';

    delete[] A;
    return 0;
}
