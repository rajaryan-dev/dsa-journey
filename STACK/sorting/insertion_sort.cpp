# include <iostream>
using namespace std;

void printArray(int arr[], int n) {

    for(int i=0; i<n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void insertionSort(int arr[], int n) { //T_C => O(n^2)

    for( int i=1; i<n; i++) {
        int curr = arr[i]; 
        int prev = i-1;
        
        while(prev >= 0 && arr[prev] > curr) {
            arr[prev+1] = arr[prev] ; 
                prev--;
        }
        arr[prev+1] = curr; //placing the curr el in its correct position
    }
}

int main() {
    int n = 5;  
    int arr[] = {4, 1, 5, 2, 3};
    printArray(arr, n);
    insertionSort(arr, n);
    printArray(arr, n);

    return 0;

    
}