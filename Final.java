import java.util.Arrays;
import java.util.Random;

public class Final {
    public static double linearSearch(int[] arr, int target) {
        long startTime = System.nanoTime();
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == target) {
                return (System.nanoTime() - startTime) / 1e6; // Convert to milliseconds
            }
        }
        return -1;
    }

    public static double binarySearch(int[] arr, int target) {
        long startTime = System.nanoTime();
        int left = 0, right = arr.length - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target) {
                return (System.nanoTime() - startTime) / 1e6; // Convert to milliseconds
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }

    public static double interpolationSearch(int[] arr, int target) {
        long startTime = System.nanoTime();
        int left = 0, right = arr.length - 1;
        while (left <= right && arr[left] <= target && arr[right] >= target) {
            // Calculate the position using interpolation formula
            int pos = left + ((target - arr[left]) * (right - left)) / (arr[right] - arr[left]);
            if (pos < 0 || pos >= arr.length) {
                // The calculated position is out of bounds, adjust it to stay within bounds
                break;
            }
            if (arr[pos] == target) {
                long endTime = System.nanoTime();
                return (endTime - startTime) / 1e6; // Convert to milliseconds
            } else if (arr[pos] < target) {
                left = pos + 1;
            } else {
                right = pos - 1;
            }
        }
        return -1;
    }

    public static double jumpSearch(int[] arr, int target) {
        long startTime = System.nanoTime();
        int n = arr.length;
        int step = (int) Math.sqrt(n);
        int prev = 0;
        while (arr[Math.min(step, n) - 1] < target) {
            prev = step;
            step += Math.sqrt(n);
            if (prev >= n) {
                return -1;
            }
        }
        while (arr[prev] < target) {
            prev++;
            if (prev == Math.min(step, n)) {
                return -1;
            }
        }
        if (arr[prev] == target) {
            return (System.nanoTime() - startTime) / 1e6; // Convert to milliseconds
        }
        return -1;
    }

    public static double exponentialSearch(int[] arr, int target) {
        long startTime = System.nanoTime();
        int n = arr.length;
        if (arr[0] == target) {
            return (System.nanoTime() - startTime) / 1e6; // Convert to milliseconds
        }
        int i = 1;
        while (i < n && arr[i] <= target) {
            i *= 2;
        }
        return binarySearch(Arrays.copyOfRange(arr, 0, Math.min(i, n)), target);
    }

    public static void main(String[] args) {
        Random rand = new Random();
        
        // Generate a sorted array of 1000000 integers
        int[] sortedArray = new int[1000000];
        for (int i = 0; i < sortedArray.length; i++) {
            sortedArray[i] = rand.nextInt(10000000);
        }
        Arrays.sort(sortedArray);

        // Select a random target element from the array
        int target = sortedArray[rand.nextInt(sortedArray.length)];

        // Perform searches and measure time
        int numTrials = 100;
        double linearTime = 0, binaryTime = 0, interpolationTime = 0, jumpTime = 0, exponentialTime = 0;
        for (int i = 0; i < numTrials; i++) {
            linearTime += linearSearch(sortedArray, target);
            binaryTime += binarySearch(sortedArray, target);
            interpolationTime += interpolationSearch(sortedArray, target);
            jumpTime += jumpSearch(sortedArray, target);
            exponentialTime += exponentialSearch(sortedArray, target);
        }
        linearTime /= numTrials;
        binaryTime /= numTrials;
        interpolationTime /= numTrials;
        jumpTime /= numTrials;
        exponentialTime /= numTrials;

        // Output the results
        System.out.println("Target: " + target);
        System.out.println("Linear Search Time: " + linearTime + " milliseconds");
        System.out.println("Binary Search Time: " + binaryTime + " milliseconds");
        System.out.println("Interpolation Search Time: " + interpolationTime + " milliseconds");
        System.out.println("Jump Search Time: " + jumpTime + " milliseconds");
        System.out.println("Exponential Search Time: " + exponentialTime + " milliseconds");
    }
}
