package main

import (
	"fmt"
	"math"
	"math/rand"
	"sort"
	"time"
)

func linearSearch(arr []int, target int) float64 {
	startTime := time.Now()
	for _, num := range arr {
		if num == target {
			endTime := time.Now()
			return float64(endTime.Sub(startTime).Milliseconds())
		}
	}
	return -1
}

func binarySearch(arr []int, target int) float64 {
	startTime := time.Now()
	left, right := 0, len(arr)-1
	for left <= right {
		mid := left + (right-left)/2
		if arr[mid] == target {
			endTime := time.Now()
			return float64(endTime.Sub(startTime).Milliseconds())
		} else if arr[mid] < target {
			left = mid + 1
		} else {
			right = mid - 1
		}
	}
	return -1
}

func exponentialSearch(arr []int, target int) float64 {
	startTime := time.Now()
	if arr[0] == target {
		endTime := time.Now()
		return float64(endTime.Sub(startTime).Milliseconds())
	}
	i := 1
	for i < len(arr) && arr[i] <= target {
		i *= 2
	}
	return binarySearch(arr[:int(math.Min(float64(i), float64(len(arr))))], target)
}

func jumpSearch(arr []int, target int) float64 {
	startTime := time.Now()
	n := len(arr)
	step := int(math.Sqrt(float64(n)))
	prev := 0
	for arr[int(math.Min(float64(step), float64(n)))-1] < target {
		prev = step
		step += int(math.Sqrt(float64(n)))
		if prev >= n {
			return -1
		}
	}
	for arr[prev] < target {
		prev++
		if prev == int(math.Min(float64(step), float64(n))) {
			return -1
		}
	}
	if arr[prev] == target {
		endTime := time.Now()
		return float64(endTime.Sub(startTime).Milliseconds())
	}
	return -1
}

func interpolationSearch(arr []int, target int) float64 {
	startTime := time.Now()
	left, right := 0, len(arr)-1
	for left <= right && arr[left] <= target && arr[right] >= target {
		pos := left + int((float64(target-arr[left])/float64(arr[right]-arr[left]))*float64(right-left))
		if pos < 0 || pos >= len(arr) {
			break
		}
		if arr[pos] == target {
			endTime := time.Now()
			return float64(endTime.Sub(startTime).Milliseconds())
		} else if arr[pos] < target {
			left = pos + 1
		} else {
			right = pos - 1
		}
	}
	return -1
}

func main() {
	rand.Seed(time.Now().UnixNano())

	// Generate a sorted array of 1000000 integers
	sortedArray := make([]int, 1000000)
	for i := range sortedArray {
		sortedArray[i] = rand.Intn(10000000)
	}
	sort.Ints(sortedArray)

	// Select a random target element from the array
	target := sortedArray[rand.Intn(len(sortedArray))]

	// Perform searches and measure time
	numTrials := 100
	var linearTime, binaryTime, exponentialTime, jumpTime, interpolationTime float64
	for i := 0; i < numTrials; i++ {
		linearTime += linearSearch(sortedArray, target)
		binaryTime += binarySearch(sortedArray, target)
		exponentialTime += exponentialSearch(sortedArray, target)
		jumpTime += jumpSearch(sortedArray, target)
		interpolationTime += interpolationSearch(sortedArray, target)
	}
	linearTime /= float64(numTrials)
	binaryTime /= float64(numTrials)
	exponentialTime /= float64(numTrials)
	jumpTime /= float64(numTrials)
	interpolationTime /= float64(numTrials)

	// Output the results
	fmt.Println("Target:", target)
	fmt.Println("Linear Search Time:", linearTime, "milliseconds")
	fmt.Println("Binary Search Time:", binaryTime, "milliseconds")
	fmt.Println("Exponential Search Time:", exponentialTime, "milliseconds")
	fmt.Println("Jump Search Time:", jumpTime, "milliseconds")
	fmt.Println("Interpolation Search Time:", interpolationTime, "milliseconds")
}
