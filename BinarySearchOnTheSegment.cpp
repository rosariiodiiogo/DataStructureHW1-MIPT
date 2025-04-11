#include <iostream>

bool BinarySearch(const int *begin, const int *end, int target)
{
    while(begin < end)
    {
        const int * mid = begin + (end - begin) / 2;

        if(*mid == target)
            return true;
        else if(*mid < target)
            begin = mid + 1;
        else
            end = mid;
    }

    return false;
}

int main()
{
    int N;
    std::cin >> N;
    int A[N];

    for (size_t i = 0; i < N; i++)
    {
        std::cin >> A[i];
    }

    int Q;
    std::cin >> Q;
    for (int k = 0; k < Q; k++)
    {
        int i, j, t;
        std:: cin >> i >> j >> t;
        bool answer = BinarySearch(A + i,A + j, t);
        
        if(answer == 1)
            std::cout << "YES\n";
        else
            std::cout << "NO\n";
    }
}