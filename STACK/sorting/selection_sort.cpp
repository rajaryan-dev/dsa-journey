# include <iostream>
using namespace std;



void printArray(int arr[], int n) {

    for(int i=0; i<n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void selectionSort(int arr[], int n) { //T_C => O(n^2)

    for( int i=0; i<n-1; i++) {
        int smallestIdx = i; //unsorted part starting
        for(int j=i+1; j<n; j++) {
            if(arr[j] < arr[smallestIdx]) {
                smallestIdx = j;
            }
        }
        swap(arr[i], arr[smallestIdx]);
    }
}

int main() {
    int n = 5;  
    int arr[] = {4, 1, 5, 2, 3};
    printArray(arr, n);
    selectionSort(arr, n);
    printArray(arr, n);

    return 0;

    
}