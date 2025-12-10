#include <iostream>
#include <vector> // Required header for using dynamic arrays (vectors)
using namespace std;

int main() {
    // OPTIONAL OPTIMIZATION: Fast I/O
    // In Competitive Programming, toggling off sync with C-style I/O speeds up execution.
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    // DECLARATION
    // vector<Type> name;
    // Vectors are dynamic arrays that can grow or shrink in size.
    vector<int> vec; // Initial size is 0, capacity is 0 (implementation dependent)

    // INSERTION
    // push_back(val): Adds element to the end.
    // emplace_back(val): Construct element in-place at the end (slightly faster for complex objects).
    vec.push_back(1);
    vec.emplace_back(9);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(1);
   
    // REMOVAL
    // pop_back(): Removes the last element. O(1) time complexity.
    vec.pop_back(); // Removes the last added '1'
    
    // TRAVERSAL
    // Range-based for loop: Cleaner way to iterate over containers.
    // Use 'const int& val' if iterating over objects to avoid copying. 
    cout << "Elements: ";
    for(int val: vec) {
        cout << val << " " ;
    } 
    // OPTIMIZATION: Use '\n' instead of endl. 
    // endl forces a flush of the output buffer which is slower.
    cout << "\n";

    // ACCESSING ELEMENTS
    // vec[i]: Access element at index i (No bounds checking - Faster but safe only if you know index exists)
    // vec.at(i): Access element at index i (Throws exception if index is out of bounds - Safer)
    cout << "Val at index 1: " << vec[1] << " or " << vec.at(1) << "\n";

    // SIZE VS CAPACITY
    // size(): Number of elements currently holding values.
    // capacity(): Number of elements it CAN hold before it needs to reallocate more memory.
    // Vector doubles its capacity when it runs out of space.
    cout << "Size: " << vec.size() << "\n";
    cout << "Capacity: " << vec.capacity() << "\n";

    // FRONT & BACK
    // Access the first and last elements directly
    cout << "Front: " << vec.front() << "\n";
    cout << "Back: " << vec.back() << "\n";

    return 0;
}