import threading
import time

# Merge Function
def merge(left, right):
    result = []
    i = j = 0

    # Compare elements and merge
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1

    # Add remaining elements
    result.extend(left[i:])
    result.extend(right[j:])

    return result


# Sequential Merge Sort
def merge_sort(arr):
    if len(arr) <= 1:
        return arr

    mid = len(arr) // 2

    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])

    return merge(left, right)


# Parallel Merge Sort
def parallel_merge_sort(arr):
    if len(arr) <= 1:
        return arr

    mid = len(arr) // 2

    left = arr[:mid]
    right = arr[mid:]

    left_sorted = []
    right_sorted = []

    # Thread functions
    def sort_left():
        nonlocal left_sorted
        left_sorted = merge_sort(left)

    def sort_right():
        nonlocal right_sorted
        right_sorted = merge_sort(right)

    # Create threads
    t1 = threading.Thread(target=sort_left)
    t2 = threading.Thread(target=sort_right)

    # Start threads
    t1.start()
    t2.start()

    # Wait for completion
    t1.join()
    t2.join()

    # Merge sorted halves
    return merge(left_sorted, right_sorted)


# Main Function
n = int(input("Enter number of elements: "))

arr = list(map(int, input("Enter elements: ").split()))

print("Original:", arr)

# Sequential Merge Sort
start = time.time()
seq_sorted = merge_sort(arr.copy())
end = time.time()

print("Sequential Merge Sort:", seq_sorted)
print("Time:", end - start, "sec")

# Parallel Merge Sort
start = time.time()
par_sorted = parallel_merge_sort(arr.copy())
end = time.time()

print("Parallel Merge Sort:", par_sorted)
print("Time:", end - start, "sec")