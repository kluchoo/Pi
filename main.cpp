#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <iomanip>
#include <fstream>

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
    std::vector<long long> num_points_list = { 100000000, 1000000000, 3000000000 };
    int max_threads = 50;

    std::ofstream outfile("results.csv", std::ios::app);
    if (!outfile) {
        std::cerr << "Nie mozna otworzyc pliku do zapisu!" << std::endl;
        return 1;
    }

    // Tworzenie nagłówka pliku CSV, jeśli plik jest pusty
    std::ifstream infile("results.csv");
    if (infile.peek() == std::ifstream::traits_type::eof()) {
        outfile << "Liczba punktow,Liczba watkow,Przyblizenie liczby PI,Czas wykonania (sekundy)" << std::endl;
    }
    infile.close();

    for (unsigned int num_points : num_points_list) {
        for (int num_threads = 1; num_threads <= max_threads; num_threads++) {
            std::vector<std::thread> threads;
            global_sum = 0.0;

            // Pomiar czasu - start
            auto start_time = std::chrono::high_resolution_clock::now();

            // Tworzenie wątków
            unsigned int points_per_thread = num_points / num_threads;
            double interval_per_thread = 1.0 / num_threads;

            for (int i = 0; i < num_threads; i++) {
                double start = i * interval_per_thread;
                double end = (i + 1) * interval_per_thread;
                threads.emplace_back(integrate, start, end, points_per_thread);
            }

            // Czekanie na zakończenie wszystkich wątków
            for (auto& thread : threads) {
                thread.join();
            }

            // Pomiar czasu - koniec
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

            std::cout << std::fixed << std::setprecision(10);
            std::cout << "Liczba punktow: " << num_points << ", Liczba watkow: " << num_threads << std::endl;
            std::cout << "Przyblizenie liczby PI: " << global_sum << std::endl;
            std::cout << "Czas wykonania: " << duration.count() / 1000000.0 << " sekund" << std::endl;

            outfile << num_points << "," << num_threads << "," << global_sum << "," << duration.count() / 1000000.0 << std::endl;
        }
    }

    outfile.close();

    return 0;
}