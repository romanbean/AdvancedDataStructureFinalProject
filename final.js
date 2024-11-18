function linearSearch(arr, target) {
    const startTime = process.hrtime.bigint();
    for (let i = 0; i < arr.length; i++) {
        if (arr[i] === target) {
            const endTime = process.hrtime.bigint();
            return Number((endTime - startTime) / BigInt(1e6)); // Convert BigInt to number before division
        }
    }
    return -1;
}

function binarySearch(arr, target) {
    const startTime = process.hrtime.bigint();
    let left = 0, right = arr.length - 1;
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        if (arr[mid] === target) {
            const endTime = process.hrtime.bigint();
            return Number((endTime - startTime) / BigInt(1e6)); // Convert BigInt to number before division
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

function interpolationSearch(arr, target) {
    const startTime = process.hrtime.bigint();
    let left = 0, right = arr.length - 1;
    while (left <= right && arr[left] <= target && arr[right] >= target) {
        const numerator = BigInt(target - arr[left]) * BigInt(right - left);
        const denominator = BigInt(arr[right] - arr[left]);
        const pos = left + Number(numerator / denominator); // Convert to number after division
        if (arr[pos] === target) {
            const endTime = process.hrtime.bigint();
            return Number((endTime - startTime) / BigInt(1e6)); // Convert BigInt to number before division
        } else if (arr[pos] < target) {
            left = pos + 1;
        } else {
            right = pos - 1;
        }
    }
    return -1;
}

function jumpSearch(arr, target) {
    const startTime = process.hrtime.bigint();
    const n = arr.length;
    let step = Math.floor(Math.sqrt(n));
    let prev = 0;
    while (arr[Math.min(step, n) - 1] < target) {
        prev = step;
        step += Math.floor(Math.sqrt(n));
        if (prev >= n) {
            return -1;
        }
    }
    while (arr[prev] < target) {
        prev++;
        if (prev === Math.min(step, n)) {
            return -1;
        }
    }
    if (arr[prev] === target) {
        const endTime = process.hrtime.bigint();
        return Number((endTime - startTime) / BigInt(1e6)); // Convert BigInt to number before division
    }
    return -1;
}

function exponentialSearch(arr, target) {
    const startTime = process.hrtime.bigint();
    const n = arr.length;
    if (arr[0] === target) {
        const endTime = process.hrtime.bigint();
        return Number((endTime - startTime) / BigInt(1e6)); // Convert BigInt to number before division
    }
    let i = 1;
    while (i < n && arr[i] <= target) {
        i *= 2;
    }
    return binarySearch(arr.slice(0, Math.min(i, n)), target);
}

// Generate a sorted array of 1000000 integers
const sortedArray = Array.from({length: 1000000}, () => Math.floor(Math.random() * 10000000)).sort((a, b) => a - b);

// Select a random target element from the array
const target = sortedArray[Math.floor(Math.random() * sortedArray.length)];

// Perform searches and measure time
const numTrials = 100;
let linearTime = 0, binaryTime = 0, interpolationTime = 0, jumpTime = 0, exponentialTime = 0;
for (let i = 0; i < numTrials; i++) {
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
console.log("Target: " + target);
console.log("Linear Search Time: " + linearTime + " milliseconds");
console.log("Binary Search Time: " + binaryTime + " milliseconds");
console.log("Interpolation Search Time: " + interpolationTime + " milliseconds");
console.log("Jump Search Time: " + jumpTime + " milliseconds");
console.log("Exponential Search Time: " + exponentialTime + " milliseconds");
