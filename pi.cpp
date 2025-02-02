#include "pi.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <fstream>

Pi::Pi(int max_threads) : max_threads(max_threads), global_sum(0.0) {}

void Pi::calculate(std::vector<long long> num_points_list) {
    std::ofstream outfile("results.csv", std::ios::app);
    if (!outfile) {
        std::cerr << "Nie mozna otworzyc pliku do zapisu!" << std::endl;
        return;
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
                threads.emplace_back(&Pi::integrate, this, start, end, points_per_thread);
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
}

double Pi::f(double x) {
    return 4.0 / (1.0 + x * x);
}

void Pi::integrate(double start, double end, int n) {
    double width = (end - start) / n;
    double local_sum = 0.0;

    for (int i = 0; i < n; i++) {
        double x = start + i * width;
        local_sum += f(x) * width;
    }

    std::lock_guard<std::mutex> lock(mtx);
    global_sum += local_sum;
}
