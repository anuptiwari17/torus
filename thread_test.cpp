#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;
std::mutex mtx;

void work() {
    for (int i = 0; i < 100000; i++) {
        std::lock_guard<std::mutex> lock(mtx);
        counter++;
    }
}

int main() {
    std::thread t1(work);
    std::thread t2(work);

    t1.join();
    t2.join();

    std::cout << counter << '\n';
}