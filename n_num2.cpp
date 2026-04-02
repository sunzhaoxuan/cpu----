#include <iostream>
#include <windows.h>

using namespace std;

const int N = 4096;
const int REPEAT = 10;   

double a[N], sum, sumcmp[4] = {0, 0, 0, 0};

void init(int N) {
    sum = 0;
    for (int i = 0; i < N; i++) {
        a[i] = i;
    }
}

void recursion(int N) {
    if (N == 1) return;

    int half = N / 2;
    for (int i = 0; i < half; i++) {
        a[i] += a[N - i - 1];
    }

    recursion(half);
}

void recursion2(int N) {
    if (N == 1) return;

    for (int i = 0; i < N / 2; i++) {
        a[i] = a[i * 2] + a[i * 2 + 1];
    }

    recursion2(N / 2);   
}

bool check() {
    return sumcmp[0] == sumcmp[1] &&
           sumcmp[1] == sumcmp[2] &&
           sumcmp[2] == sumcmp[3];
}

double test1() {
    LARGE_INTEGER head, tail, freq;
    QueryPerformanceFrequency(&freq);

    QueryPerformanceCounter(&head);
    for (int t = 0; t < REPEAT; t++) {
        init(N);
        for (int i = 0; i < N; i++) {
            sum += a[i];
        }
        sumcmp[0] = sum;
    }
    QueryPerformanceCounter(&tail);

    return (tail.QuadPart - head.QuadPart) * 1000.0 / freq.QuadPart / REPEAT;
}

double test2() {
    LARGE_INTEGER head, tail, freq;
    QueryPerformanceFrequency(&freq);

    QueryPerformanceCounter(&head);
    for (int t = 0; t < REPEAT; t++) {
        init(N);
        double sum1 = 0, sum2 = 0;
        for (int i = 0; i < N; i += 2) {
            sum1 += a[i];
            sum2 += a[i + 1];
        }
        sum = sum1 + sum2;
        sumcmp[1] = sum;
    }
    QueryPerformanceCounter(&tail);

    return (tail.QuadPart - head.QuadPart) * 1000.0 / freq.QuadPart / REPEAT;
}

double test3() {
    LARGE_INTEGER head, tail, freq;
    QueryPerformanceFrequency(&freq);

    QueryPerformanceCounter(&head);
    for (int t = 0; t < REPEAT; t++) {
        init(N);
        recursion(N);
        sumcmp[2] = a[0];
    }
    QueryPerformanceCounter(&tail);

    return (tail.QuadPart - head.QuadPart) * 1000.0 / freq.QuadPart / REPEAT;
}

double test4() {
    LARGE_INTEGER head, tail, freq;
    QueryPerformanceFrequency(&freq);

    QueryPerformanceCounter(&head);
    for (int t = 0; t < REPEAT; t++) {
        init(N);
        recursion2(N);
        sumcmp[3] = a[0];
    }
    QueryPerformanceCounter(&tail);

    return (tail.QuadPart - head.QuadPart) * 1000.0 / freq.QuadPart / REPEAT;
}

int main() {
    double t1 = test1();
    double t2 = test2();
    double t3 = test3();
    double t4 = test4();

    cout << "Method 1 time: " << t1 << " ms" << endl;
    cout << "Method 2 time: " << t2 << " ms" << endl;
    cout << "Method 3 time: " << t3 << " ms" << endl;
    cout << "Method 4 time: " << t4 << " ms" << endl;

    if (check()) {
        cout << "All methods give the same result." << endl;
    } else {
        cout << "Results differ among methods!" << endl;
    }

    return 0;
}