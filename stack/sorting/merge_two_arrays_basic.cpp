#include <iostream>
using namespace std;

void merge(int arrA[], int m, int arrB[], int n) {
    int idx = m+n-1, i = m-1, j = n-1;

    while(i >= 0 && j>= 0) {
        if(arrA[i] >= arrB[j]) {
            arrA[idx--] = arrA[i--];
        } else {
            arrA[idx--] = arrB[j--];  
        }
    }
    while(j >= 0) {
        arrA[idx--] = arrB[j--];
    }
}

void printArray(int arr[], int n) {

    for(int i=0; i<n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    
    int arrA[] = {1, 2, 3, 0, 0, 0};
    int arrB[] = {2, 5, 6};
    int m = 3;
    int n = 3;

   printArray(arrA, m+n);
   printArray(arrB, n);

   merge(arrA, m, arrB, n);

   printArray(arrA, m+n);
    

    return 0;
}

