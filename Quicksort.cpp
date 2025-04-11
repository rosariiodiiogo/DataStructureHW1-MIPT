#include <iostream>

void exchange(int &a, int &b) {
    int c = a;
    a = b;
    b = c;
}

void insertionSort(int A[], int p, int r) {
    for (int i = p + 1; i <= r; i++) {
        int key = A[i];
        int j = i - 1;
        while (j >= p && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}

int medianOfThree(int A[], int p, int r) {
    int mid = p + (r - p) / 2;
    if (A[p] > A[mid])
        exchange(A[p], A[mid]);
    if (A[p] > A[r])
        exchange(A[p], A[r]);
    if (A[mid] > A[r])
        exchange(A[mid], A[r]);
    return mid;
}

int partition(int A[], int p, int r) {
    int medianIndex = medianOfThree(A, p, r);
    exchange(A[medianIndex], A[r]);
    int pivot = A[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] <= pivot) {
            i++;
            exchange(A[i], A[j]);
        }
    }
    exchange(A[i + 1], A[r]);
    return i + 1;
}

int left(int i) {
    return 2 * i + 1;
}

int right(int i) {
    return 2 * i + 2;
}

void maxHeapify(int A[], int i, int heap_size) {
    int l = left(i);
    int r = right(i);
    int largest = i;
    if (l < heap_size && A[l] > A[largest])
        largest = l;
    if (r < heap_size && A[r] > A[largest])
        largest = r;
    if (largest != i) {
        exchange(A[i], A[largest]);
        maxHeapify(A, largest, heap_size);
    }
}

void buildMaxHeap(int A[], int heap_size) {
    for (int i = (heap_size / 2) - 1; i >= 0; i--) {
        maxHeapify(A, i, heap_size);
    }
}

void heapsort(int A[], int n) {
    buildMaxHeap(A, n);
    for (int i = n - 1; i > 0; i--) {
        exchange(A[0], A[i]);
        maxHeapify(A, 0, i);
    }
}

void modifiedQuickSort(int A[], int p, int r, int depthLimit) {
    int n = r - p + 1;
    if (n <= 16) {
        insertionSort(A, p, r);
        return;
    }
    if (depthLimit == 0) {
        heapsort(A + p, n);
        return;
    }
    int q = partition(A, p, r);
    modifiedQuickSort(A, p, q - 1, depthLimit - 1);
    modifiedQuickSort(A, q + 1, r, depthLimit - 1);
}

int main() {
    
    int N;
    std::cin >> N;
    int A[N];
    
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }
    
    int depthLimit = 0;
    for (int x = N; x > 1; x /= 2)
        depthLimit++;
    depthLimit *= 2;
    
    modifiedQuickSort(A, 0, N - 1, depthLimit);
    
    for (int i = 0; i < N; i++) {
        std::cout << A[i] << " ";
    }
    
    std::cout << std::endl;
    return 0;
}
