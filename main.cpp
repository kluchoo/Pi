#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <iomanip>

std::mutex mtx;
double global_sum = 0.0;

// Funkcja podcałkowa f(x) = 4/(1+x^2)
double f(double x) {
    return 4.0 / (1.0 + x * x);
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}