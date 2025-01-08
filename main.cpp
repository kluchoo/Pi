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

// Funkcja wykonująca całkowanie na zadanym przedziale
void integrate(double start, double end, int n) {
    double width = (end - start) / n;
    double local_sum = 0.0;

    for (int i = 0; i < n; i++) {
        double x = start + i * width;
        local_sum += f(x) * width;
    }

    std::lock_guard<std::mutex> lock(mtx);
    global_sum += local_sum;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}