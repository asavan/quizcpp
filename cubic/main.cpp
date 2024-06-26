#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>

bool check(int * v) {
    int f[6];
    f[0] = v[0] + v[1] + v[2] + v[3];
    f[1] = v[3] + v[2] + v[6] + v[7];
    f[2] = v[4] + v[5] + v[6] + v[7];
    f[3] = v[0] + v[1] + v[4] + v[5];
    f[4] = v[5] + v[1] + v[2] + v[6];
    f[5] = v[0] + v[3] + v[4] + v[7];
    std::sort(f, f+6);
    for (int i = 1; i < 6; ++i) {
        if (f[i] == f[i - 1]) {
            return false;
        }
    }
    return true;
}

void swap(int* v, int i, int j)
{
    int temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int globalCount = 0;

void print(int* v, int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

void HeapPermute(int* v, int n)
{
    // Print the sequence if the heap top reaches to the 1.
    if (n == 1) {
        bool res = check(v);
        if (res) {
            ++globalCount;
        }
    }
    else
    {
        // Fix a number at the heap top until only two one element remaining and permute remaining.
        for (int i = 0; i < n; i++)
        {
            HeapPermute(v, n - 1);
            // If odd then swap the value at the start index with the n-1.
            if (n % 2 == 1) {
                swap(v, 0, n - 1);
            }
            // If even then swap the value at the 'i' index with the n-1.
            else {
                swap(v, i, n - 1);
            }
        }
    }
}

int main1(int argc, char* argv[])
{
    if (argc < 9) {
        printf("Usage: ./cube a b c d e f g h\n");
        printf("   b---c       \n");
        printf("  /|  /|       \n");
        printf(" a-+-d |       \n");
        printf(" | f-|-g       \n");
        printf(" |/  |/        \n");
        printf(" e---h         \n");
        return -1;
    }
    int arr[8];
    for (int i = 0; i < 8; ++i) {
        arr[i] = std::stoi(argv[i + 1]);
    }

    bool res = check(arr);
    if (res) {
        std::cout << "OK" << std::endl;
    }
    else {
        std::cout << "FAIL" << std::endl;
    }
    return 0;
}


int main() {
    int arr[8];
    for (int i = 0; i < 8; ++i) {
        arr[i] = i + 1;
    }
    print(arr, 8);
    HeapPermute(arr, 8);
    std::cout << globalCount << std::endl;
}
