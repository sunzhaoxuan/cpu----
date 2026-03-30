#include <iostream>
#include <windows.h>

using namespace std;

const int N=10000;

int a[N], b[N][N], sum[N];

void init(int N){
    for(int i=0;i<N;i++){
        a[i]=i;
        sum[i]=0;
        for(int j=0;j<N;j++){
            b[i][j]=i+j;
        }
    }
}

int main(){
    long long head,tail,freq;
    init(N);
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
    QueryPerformanceCounter((LARGE_INTEGER*)&head);
    for(int j=0;j<N;j++){
        for(int i=0;i<N;i++){
            sum[i]+=b[j][i] * a[j];
        }
    }
    QueryPerformanceCounter((LARGE_INTEGER*)&tail);
    std::cout << "Time taken: " << (tail - head) * 1000.0 / freq << " ms" << std::endl;

    return 0;
}