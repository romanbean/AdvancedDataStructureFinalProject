#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <cmath>

using namespace std;
using namespace std::chrono;

double linear_search(const vector<int>& arr, int target) {
    auto start_time = high_resolution_clock::now();
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            auto end_time = high_resolution_clock::now();
            return duration_cast<nanoseconds>(end_time - start_time).count();
        }
    }
    return -1;
}

double binary_search(const vector<int>& arr, int target) {
    auto start_time = high_resolution_clock::now();
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            auto end_time = high_resolution_clock::now();
            return duration_cast<nanoseconds>(end_time - start_time).count();
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

double interpolation_search(const vector<int>& arr, int target) {
    auto start_time = high_resolution_clock::now();
    int left = 0, right = arr.size() - 1;
    while (left <= right && arr[left] <= target && arr[right] >= target) {
        int pos = left + ((target - arr[left]) * (right - left)) / (arr[right] - arr[left]);
        if (arr[pos] == target) {
            auto end_time = high_resolution_clock::now();
            return duration_cast<nanoseconds>(end_time - start_time).count();
        } else if (arr[pos] < target) {
            left = pos + 1;
        } else {
            right = pos - 1;
        }
    }
    return -1;
}

double jump_search(const vector<int>& arr, int target) {
    auto start_time = high_resolution_clock::now();
    int n = arr.size();
    int step = sqrt(n);
    int prev = 0;
    while (arr[min(step, n) - 1] < target) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            return -1;
        }
    }
    while (arr[prev] < target) {
        prev++;
        if (prev == min(step, n)) {
            return -1;
        }
    }
    if (arr[prev] == target) {
        auto end_time = high_resolution_clock::now();
        return duration_cast<nanoseconds>(end_time - start_time).count();
    }
    return -1;
}

double exponential_search(const vector<int>& arr, int target) {
    auto start_time = high_resolution_clock::now();
    int n = arr.size();
    if (arr[0] == target) {
        auto end_time = high_resolution_clock::now();
        return duration_cast<nanoseconds>(end_time - start_time).count();
    }
    int i = 1;
    while (i < n && arr[i] <= target) {
        i *= 2;
    }
    auto end_time = high_resolution_clock::now();
    return duration_cast<nanoseconds>(end_time - start_time).count();
}

int main() {
    // Generate a sorted vector of 1000000 integers
    vector<int> sorted_list(1000000);
    iota(sorted_list.begin(), sorted_list.end(), 0);
    random_device rd;
    mt19937 g(rd());
    shuffle(sorted_list.begin(), sorted_list.end(), g);

    // Select a random target element from the vector
    int target = sorted_list[rand() % sorted_list.size()];

    // Perform searches and measure time
    int num_trials = 100;
    double linear_time = 0, binary_time = 0, interpolation_time = 0, jump_time = 0, exponential_time = 0;
    for (int i = 0; i < num_trials; ++i) {
        linear_time += linear_search(sorted_list, target);
        binary_time += binary_search(sorted_list, target);
        interpolation_time += interpolation_search(sorted_list, target);
        jump_time += jump_search(sorted_list, target);
        exponential_time += exponential_search(sorted_list, target);
    }
    linear_time /= num_trials;
    binary_time /= num_trials;
    interpolation_time /= num_trials;
    jump_time /= num_trials;
    exponential_time /= num_trials;

    // Output the results
    cout << "Target: " << target << endl;
    cout << "Linear Search Time: " << linear_time << " nanoseconds" << endl;
    cout << "Binary Search Time: " << binary_time << " nanoseconds" << endl;
    cout << "Interpolation Search Time: " << interpolation_time << " nanoseconds" << endl;
    cout << "Jump Search Time: " << jump_time << " nanoseconds" << endl;
    cout << "Exponential Search Time: " << exponential_time << " nanoseconds" << endl;

    return 0;
}
