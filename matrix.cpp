#include <iostream>
#include <windows.h>
#include <cmath>

using namespace std;

const int N = 1024;     
const int REPEAT = 10;  

double a[N], b[N][N];
double sumcmp1[N], sumcmp2[N], sumcmp3[N];

void init(int N) {
    for (int i = 0; i < N; i++) {
        a[i] = i;
        sumcmp1[i] = 0;
        sumcmp2[i] = 0;
        for (int j = 0; j < N; j++) {
            b[i][j] = i + j;
        }
    }
}

void method1(int N) {
    for (int i = 0; i < N; i++) {
        sumcmp1[i] = 0;
    }

    for (int i = 0; i < N; i++) {          
        for (int j = 0; j < N; j++) {      
            sumcmp1[i] += b[j][i] * a[j];
        }
    }
}

// 方法2：cache优化算法，按行访问
void method2(int N) {
    for (int i = 0; i < N; i++) {
        sumcmp2[i] = 0;
    }

    for (int j = 0; j < N; j++) {          
        double aj = a[j];
        for (int i = 0; i < N; i++) {      
            sumcmp2[i] += b[j][i] * aj;
        }
    }
}

void method3(int N) {
    for (int i = 0; i < N; i++) {
        sumcmp3[i] = 0;
    }

    for (int j = 0; j < N; j++) {
        double aj = a[j];
        int i;
        for (i = 0; i + 3 < N; i += 4) {
            sumcmp3[i]     += b[j][i] * aj;
            sumcmp3[i + 1] += b[j][i + 1] * aj;
            sumcmp3[i + 2] += b[j][i + 2] * aj;
            sumcmp3[i + 3] += b[j][i + 3] * aj;
        }
        for (; i < N; i++) {
            sumcmp3[i] += b[j][i] * aj;
        }
    }
}


bool check() {
    double eps = 1e-6;
    for (int i = 0; i < N; i++) {
        if (fabs(sumcmp1[i] - sumcmp2[i]) > eps) {
            return false;
        }
    }
    for(int i = 0; i < N; i++) {
        if (fabs(sumcmp2[i] - sumcmp3[i]) > eps) {
            return false;
        }
    }
    return true;
}


double test1() {
    LARGE_INTEGER head, tail, freq;
    QueryPerformanceFrequency(&freq);

    QueryPerformanceCounter(&head);
    for (int t = 0; t < REPEAT; t++) {
        init(N);
        method1(N);
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
        method2(N);
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
        method3(N);
    }
    QueryPerformanceCounter(&tail);

    return (tail.QuadPart - head.QuadPart) * 1000.0 / freq.QuadPart / REPEAT;
}

int main() {
    double t1 = test1();
    double t2 = test2();
    double t3 = test3();

    init(N);
    method1(N);
    method2(N);
    method3(N);

    cout << "Matrix size: " << N << " x " << N << endl;
    cout << "Method 1 time (naive): " << t1 << " ms" << endl;
    cout << "Method 2 time (cache optimized): " << t2 << " ms" << endl;
    cout << "Method 3 time (SIMD optimized): " << t3 << " ms" << endl;
    cout << "Method 2 Speedup: " << t1 / t2 << endl;
    cout << "Method 3 Speedup: " << t1 / t3 << endl;

    if (check()) {
        cout << "All methods give the same result." << endl;
    } else {
        cout << "Results differ among methods!" << endl;
    }

    return 0;
}