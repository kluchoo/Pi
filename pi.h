#ifndef PI_H
#define PI_H

#include <vector>
#include <mutex>

class Pi {
    public:
    Pi(int max_threads);
    void calculate(std::vector<long long> num_points_list);

    private:
    int max_threads;
    double global_sum;
    std::mutex mtx;

    double f(double x);
    void integrate(double start, double end, int n);
};

#endif // PI_H
