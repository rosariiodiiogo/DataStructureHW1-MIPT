#include <iostream>

using ull = unsigned long long;

int main() {

    size_t N;
    if (!(std::cin >> N)) return 0;

    ull* a = new ull[N];
    ull* b = new ull[N];
    for (size_t i = 0; i < N; ++i) {
        std::cin >> a[i];
    }

    const int RADIX = 256;
    size_t count[RADIX];

    for (int byte = 0; byte < 8; ++byte) {
        for (int i = 0; i < RADIX; ++i) count[i] = 0;
        int shift = byte * 8;
        for (size_t i = 0; i < N; ++i) {
            unsigned key = (unsigned)((a[i] >> shift) & 0xFFULL);
            ++count[key];
        }
        size_t sum = 0;
        for (int i = 0; i < RADIX; ++i) {
            size_t tmp = count[i];
            count[i] = sum;
            sum += tmp;
        }
        for (size_t i = 0; i < N; ++i) {
            unsigned key = (unsigned)((a[i] >> shift) & 0xFFULL);
            b[count[key]++] = a[i];
        }
        ull* tmpPtr = a;
        a = b;
        b = tmpPtr;
    }

    for (size_t i = 0; i < N; ++i) {
        std::cout << a[i] << '\n';
    }

    delete[] a;
    delete[] b;
    return 0;
}
