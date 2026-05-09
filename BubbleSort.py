import threading
import time

# Bubble Sort
def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]


# Parallel Sort
def parallel_sort(arr):
    n = len(arr)
    mid = n // 2

    left = arr[:mid]
    right = arr[mid:]

    # Create threads
    t1 = threading.Thread(target=bubble_sort, args=(left,))
    t2 = threading.Thread(target=bubble_sort, args=(right,))

    # Start threads
    t1.start()
    t2.start()

    # Wait for threads to finish
    t1.join()
    t2.join()

    # Merge manually
    i = j = k = 0
    result = [0] * n

    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            result[k] = left[i]
            i += 1
        else:
            result[k] = right[j]
            j += 1
        k += 1

    while i < len(left):
        result[k] = left[i]
        i += 1
        k += 1

    while j < len(right):
        result[k] = right[j]
        j += 1
        k += 1

    return result


# Main Function
n = int(input("Enter number of elements: "))

arr = list(map(int, input("Enter elements: ").split()))

print("Original:", arr)

# Sequential
a1 = arr.copy()

start = time.time()
bubble_sort(a1)
end = time.time()

print("Sequential:", a1)
print("Time:", end - start, "sec")

# Parallel
a2 = arr.copy()

start = time.time()
a2 = parallel_sort(a2)
end = time.time()

print("Parallel:", a2)
print("Time:", end - start, "sec")