#include <iostream>
#include <vector>
#include "pi.h"

int main() {
    std::vector<long long> num_points_list = { 100000000, 1000000000, 3000000000 };
    int max_threads = 50;

    Pi pi(max_threads);
    pi.calculate(num_points_list);

    return 0;
}