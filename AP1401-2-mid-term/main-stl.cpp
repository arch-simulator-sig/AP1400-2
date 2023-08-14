#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

int main()
{
    // Create a random number generator
    std::default_random_engine generator;

    // Create a normal distribution with mean 0 and standard deviation 1
    std::normal_distribution<double> distribution(0.0, 1.0);

    // Create a vector to store our data
    std::vector<double> data(100000);

    // Generate the data
    std::generate_n(data.begin(), data.size(), [&]() { return distribution(generator); });

    // Compute average
    double avg { std::accumulate(data.cbegin(), data.cend(), 0.0) / data.size() };
    std::cout << "avg=" << avg << std::endl;

    // Compute std
    std::vector<double> sq_error(data.size());
    std::transform(data.cbegin(), data.cend(), sq_error.begin(), [&avg](double x) { return std::pow(x - avg, 2); });
    double std { std::sqrt(std::accumulate(sq_error.cbegin(), sq_error.cend(), 0)) / static_cast<double>(data.size()) };
    std::cout << "std=" << std << std::endl;

    // Remove outliers
    auto it { std::remove_if(data.begin(), data.end(), [&avg, &std](double x) { return std::abs(x - avg) > 2 * std; }) };
    data.erase(it, end(data));

    // Compute average
    avg = std::accumulate(data.cbegin(), data.cend(), 0.0) / data.size();
    std::cout << "avg=" << avg << std::endl;

    // Compute std
    std::fill(sq_error.begin(), sq_error.end(), 0); // optional
    std::transform(data.cbegin(), data.cend(), sq_error.begin(), [&avg](double x) { return std::pow(x - avg, 2); });
    std = std::sqrt(std::accumulate(sq_error.cbegin(), sq_error.cend(), 0)) / static_cast<double>(data.size());
    std::cout << "std=" << std << std::endl;
}
