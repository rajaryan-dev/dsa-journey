#include <iostream>
#include <cstring>

using namespace std;

/*
 * ============================================================================
 * CUSTOM STRING CLASS IMPLEMENTATION
 * ============================================================================
 * 
 * This file demonstrates how a string class works under the hood.
 * It follows the same pattern as the Queue implementation:
 * 1. Class-based encapsulation
 * 2. Manual memory management (dynamic arrays)
 * 3. Member functions for operations
 * 
 * We will implement a 'CustomString' that manages a char array dynamically.
 */

class CustomString {
    // ========================================================================
    // PRIVATE MEMBERS
    // ========================================================================
    char* str;      // Pointer to dynamic character array
    int length;     // Current number of characters
    int capacity;   // Total allocated size (to avoid resizing every time)

public:
    // ========================================================================
    // CONSTRUCTOR
    // ========================================================================
    
    // Default constructor: creates empty string
    CustomString(int initialCapacity = 10) {
        capacity = initialCapacity;
        length = 0;
        
        // Step 1: Allocate memory for array
        str = new char[capacity]; 
        
        // Step 2: Ensure it's null-terminated
        str[0] = '\0';
        
        cout << "String initialized with capacity " << capacity << "\n";
    }
    
    // Copy constructor: creates string from C-style string
    CustomString(const char* inputStr) {
        // Step 1: Calculate needed size
        int inputLen = strlen(inputStr);
        length = inputLen;
        capacity = inputLen + 10; // Allocate extra space for future growth
        
        // Step 2: Allocate memory
        str = new char[capacity];
        
        // Step 3: Copy characters
        strcpy(str, inputStr);
        
        cout << "String created: " << str << "\n";
    }

    // ========================================================================
    // DESTRUCTOR
    // ========================================================================
    
    // Clean up memory when object is destroyed
    ~CustomString() {
        delete[] str;
        cout << "Memory freed\n";
    }

    // ========================================================================
    // CORE OPERATIONS
    // ========================================================================

    // 1. PUSH_BACK (Append character to end)
    void push_back(char ch) {
        // Step 1: Check if full
        if (length == capacity - 1) { // -1 for null terminator
            cout << "Resize needed! (Not implemented for this demo -> increasing manually)\n";
            // ideally we would resize here
            return;
        }
        
        // Step 2: Add character at end
        str[length] = ch;
        
        // Step 3: Increment length
        length++;
        
        // Step 4: Add null terminator
        str[length] = '\0';
        
        cout << "Pushed '" << ch << "'. String is now: " << str << "\n";
    }
    
    // 2. POP_BACK (Remove last character)
    void pop_back() {
        // Step 1: Check if empty
        if (length == 0) {
            cout << "String is empty, cannot pop!\n";
            return;
        }
        
        // Step 2: Get character being removed
        char popped = str[length-1];
        
        // Step 3: Simply decrease length (data remains but ignored)
        length--;
        
        // Step 4: Update null terminator
        str[length] = '\0';
        
        cout << "Popped '" << popped << "'. String is now: " << str << "\n";
    }
    
    // 3. GET ELEMENT (Access via index)
    char get(int index) {
        if (index < 0 || index >= length) {
            cout << "Index out of bounds!\n";
            return '\0';
        }
        return str[index];
    }
    
    // 4. INSERT (Add character at specific index)
    // Similar to how Queue might insert or array shift
    void insert(int index, char ch) {
        if (index < 0 || index > length || length == capacity - 1) {
            cout << "Invalid index or full!\n";
            return;
        }
        
        // Step 1: Shift elements to RIGHT to make space
        // Loop from end down to index
        for (int i = length; i >= index; i--) {
            str[i+1] = str[i];
        }
        
        // Step 2: Insert new character
        str[index] = ch;
        
        // Step 3: Update length
        length++;
        
        cout << "Inserted '" << ch << "' at " << index << ". String: " << str << "\n";
    }
    
    // 5. ERASE (Remove character at specific index)
    void erase(int index) {
        if (index < 0 || index >= length) {
            cout << "Index out of bounds!\n";
            return;
        }
        
        char removed = str[index];
        
        // Step 1: Shift elements to LEFT to fill gap
        // Loop from index up to end
        for (int i = index; i < length; i++) {
            str[i] = str[i+1];
        }
        
        // Step 2: Update length
        length--;
        
        cout << "Erased '" << removed << "' from " << index << ". String: " << str << "\n";
    }
    
    // 6. FIND (Search for character)
    int find(char ch) {
        for(int i = 0; i < length; i++) {
            if(str[i] == ch) {
                return i;
            }
        }
        return -1; // Not found
    }
    
    // 7. REVERSE (In-place reversal)
    void reverse() {
        int start = 0;
        int end = length - 1;
        
        while(start < end) {
            // Swap characters
            char temp = str[start];
            str[start] = str[end];
            str[end] = temp;
            
            start++;
            end--;
        }
        cout << "Reversed string: " << str << "\n";
    }

    // Displays current state
    void printInfo() {
        cout << "[Info] Content: \"" << str << "\" | Length: " << length << " | Capacity: " << capacity << "\n";
    }
};

// ============================================================================
// MAIN FUNCTION - TEST DRIVER
// ============================================================================

int main() {
    cout << "=== Custom String Class Demo ===\n\n";
    
    // 1. Initialize
    CustomString s("Hello");
    s.printInfo();
    
    // 2. Append operations
    cout << "\n--- Append Operations ---\n";
    s.push_back('!');
    s.push_back(' ');
    s.push_back('W');
    
    // 3. Insert internal
    cout << "\n--- Insert Operation ---\n";
    s.insert(6, 'D'); // Insert 'D' before 'W'
    
    // 4. Access and Find
    cout << "\n--- Search Operations ---\n";
    cout << "Character at index 1: " << s.get(1) << "\n";
    cout << "Find 'D': Index " << s.find('D') << "\n";
    
    // 5. Reverse
    cout << "\n--- Reverse Operation ---\n";
    s.reverse();
    
    // 6. Erase/Pop
    cout << "\n--- Delete Operations ---\n";
    s.pop_back(); // Remove first char of original (now last due to reverse)
    s.erase(0);   // Remove first char
    
    cout << "\n=== Final State ===\n";
    s.printInfo();

    return 0;
}
