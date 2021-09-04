#include <windows.h>
#include <iostream>
#include <thread>
#include "events.h"

using namespace std;

HANDLE hEvent2;

const int N = 100;
int a = 0;
int b = 0;

void thread1() {
    for(int i = 0; i < N; i++) {
        a = b + 3;
        b--;
        cout << "[Thread 1: a = " << a << ", b = " << b << ']' << endl;
    }
    SetEvent(hEvent2);
}

void thread2() {
    for(int i = 0; i < N; i++) {
        WaitForSingleObject( hEvent2, INFINITE );
        b += 2;
        cout << "[Thread 2: b = " << b << ']' << endl;
        SetEvent(hEvent2);
    }
}

int main() {
    Timer t;
    hEvent2 = CreateEvent( nullptr, FALSE, FALSE, nullptr );

    thread thr1(thread1);
    thread thr2(thread2);
    thr1.join();

    thr2.join();
    cout << endl << "Time of execution = " << t.elapsed() << endl;
    return 0;
}