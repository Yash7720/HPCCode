#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;


// Sequential Bubble Sort


void bubbleSort(vector<int>& a, int n) {

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n - i - 1; j++) {

            if(a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}


// Parallel Bubble Sort


void parallelBubbleSort(vector<int>& a, int n) {

    for(int i = 0; i < n; i++) {

        #pragma omp parallel for
        for(int j = i % 2; j < n - 1; j += 2) {

            if(a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}


// Merge Function

void merge(vector<int>& a, int l, int m, int r) {

    vector<int> temp;

    int i = l;
    int j = m + 1;

    while(i <= m && j <= r) {

        if(a[i] < a[j])
            temp.push_back(a[i++]);
        else
            temp.push_back(a[j++]);
    }

    while(i <= m)
        temp.push_back(a[i++]);

    while(j <= r)
        temp.push_back(a[j++]);

    for(int k = l; k <= r; k++)
        a[k] = temp[k - l];
}


// Sequential Merge Sort
void mergeSort(vector<int>& a, int l, int r) {

    if(l < r) {

        int m = (l + r) / 2;

        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);

        merge(a, l, m, r);
    }
}


// Parallel Merge Sort


void parallelMergeSort(vector<int>& a, int l, int r) {

    if(l < r) {

        int m = (l + r) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(a, l, m);

            #pragma omp section
            parallelMergeSort(a, m + 1, r);
        }

        merge(a, l, m, r);
    }
}


// Main Function


int main() {

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter elements:\n";

    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> a1 = arr;
    vector<int> a2 = arr;
    vector<int> a3 = arr;
    vector<int> a4 = arr;

    double start, end;

 
    // Sequential Bubble Sort


    start = omp_get_wtime();

    bubbleSort(a1, n);

    end = omp_get_wtime();

    cout << "\nSequential Bubble Sort:\n";

    for(int x : a1)
        cout << x << " ";

    cout << "\nTime = " << end - start << " sec\n";

    
    // Parallel Bubble Sort
   

    start = omp_get_wtime();

    parallelBubbleSort(a2, n);

    end = omp_get_wtime();

    cout << "\nParallel Bubble Sort:\n";

    for(int x : a2)
        cout << x << " ";

    cout << "\nTime = " << end - start << " sec\n";

    
    // Sequential Merge Sort
  

    start = omp_get_wtime();

    mergeSort(a3, 0, n - 1);

    end = omp_get_wtime();

    cout << "\nSequential Merge Sort:\n";

    for(int x : a3)
        cout << x << " ";

    cout << "\nTime = " << end - start << " sec\n";

    
    // Parallel Merge Sort
    

    start = omp_get_wtime();

    parallelMergeSort(a4, 0, n - 1);

    end = omp_get_wtime();

    cout << "\nParallel Merge Sort:\n";

    for(int x : a4)
        cout << x << " ";

    cout << "\nTime = " << end - start << " sec\n";

    return 0;
}