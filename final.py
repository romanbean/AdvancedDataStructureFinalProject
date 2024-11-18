import time
import random
import bisect

def linear_search(arr, target):
    start_time = time.perf_counter()
    for i in range(len(arr)):
        if arr[i] == target:
            return time.perf_counter() - start_time
    return -1

def binary_search(arr, target):
    start_time = time.perf_counter()
    left, right = 0, len(arr) - 1
    while left <= right:
        mid = (left + right) // 2
        if arr[mid] == target:
            return time.perf_counter() - start_time
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    return -1

def interpolation_search(arr, target):
    start_time = time.perf_counter()
    left, right = 0, len(arr) - 1
    while left <= right and arr[left] <= target <= arr[right]:
        mid = left + ((right - left) * (target - arr[left])) // (arr[right] - arr[left])
        if arr[mid] == target:
            return time.perf_counter() - start_time
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    return -1

def jump_search(arr, target):
    start_time = time.perf_counter()
    n = len(arr)
    step = int(n ** 0.5)
    prev = 0
    while arr[min(step, n) - 1] < target:
        prev = step
        step += int(n ** 0.5)
        if prev >= n:
            return -1
    while arr[prev] < target:
        prev += 1
        if prev == min(step, n):
            return -1
    if arr[prev] == target:
        return time.perf_counter() - start_time
    return -1

def exponential_search(arr, target):
    start_time = time.perf_counter()
    n = len(arr)
    if arr[0] == target:
        return time.perf_counter() - start_time
    i = 1
    while i < n and arr[i] <= target:
        i *= 2
    return binary_search(arr[:min(i, n)], target)

# Generate a sorted list of 1000000 integers
sorted_list = sorted(random.sample(range(10000000), 1000000))

# Select a random target element from the list
target = random.choice(sorted_list)

# Perform searches and measure time
num_trials = 100
linear_time = sum(linear_search(sorted_list, target) for _ in range(num_trials)) / num_trials
binary_time = sum(binary_search(sorted_list, target) for _ in range(num_trials)) / num_trials
interpolation_time = sum(interpolation_search(sorted_list, target) for _ in range(num_trials)) / num_trials
jump_time = sum(jump_search(sorted_list, target) for _ in range(num_trials)) / num_trials
exponential_time = sum(exponential_search(sorted_list, target) for _ in range(num_trials)) / num_trials

# Output the results
print(f"Target: {target}")
print(f"Linear Search Time: {linear_time}")
print(f"Binary Search Time: {binary_time}")
print(f"Interpolation Search Time: {interpolation_time}")
print(f"Jump Search Time: {jump_time}")
print(f"Exponential Search Time: {exponential_time}")
