#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <climits>
#include <limits>

class PigeonholeSort {
private:
    // Find min and max in the array
    static std::pair<int, int> findMinMax(const std::vector<int>& arr) {
        if (arr.empty()) return {0, 0};
        
        int min_val = arr[0];
        int max_val = arr[0];
        
        for (int num : arr) {
            if (num < min_val) min_val = num;
            if (num > max_val) max_val = num;
        }
        
        return {min_val, max_val};
    }

public:
    // Pigeonhole Sort algorithm
    static void sort(std::vector<int>& arr) {
        if (arr.empty()) {
            std::cout << "Array is empty. Nothing to sort.\n";
            return;
        }
        
        // Find min and max values
        auto [min_val, max_val] = findMinMax(arr);
        
        std::cout << "Range of values: " << min_val << " to " << max_val << "\n";
        std::cout << "Number of pigeonholes needed: " << (max_val - min_val + 1) << "\n";
        
        // Calculate range and number of pigeonholes
        int range = max_val - min_val + 1;
        
        // Check if range is too large for memory
        if (range > 10000000) { // 10 million is arbitrary limit
            std::cout << "Warning: Range is very large (" << range 
                      << "). This might use a lot of memory!\n";
            char choice;
            std::cout << "Continue anyway? (y/n): ";
            std::cin >> choice;
            if (choice != 'y' && choice != 'Y') {
                std::cout << "Sort cancelled.\n";
                return;
            }
        }
        
        // Create pigeonholes (vectors to store elements)
        std::vector<std::vector<int>> holes(range);
        
        // Put elements into their respective pigeonholes
        for (int num : arr) {
            holes[num - min_val].push_back(num);
        }
        
        // Collect elements from pigeonholes in order
        int index = 0;
        for (auto& hole : holes) {
            for (int num : hole) {
                arr[index++] = num;
            }
        }
        
        std::cout << "Sorting completed successfully!\n";
    }
    
    // Display the array
    static void displayArray(const std::vector<int>& arr, const std::string& message) {
        std::cout << message;
        if (arr.empty()) {
            std::cout << "Array is empty\n";
            return;
        }
        
        // Show limited number of elements for large arrays
        if (arr.size() > 50) {
            std::cout << "(showing first 20 and last 20 elements)\n";
            
            // First 20
            for (size_t i = 0; i < 20; i++) {
                std::cout << arr[i];
                if (i < 19) std::cout << ", ";
            }
            std::cout << " ... ";
            
            // Last 20
            for (size_t i = arr.size() - 20; i < arr.size(); i++) {
                std::cout << arr[i];
                if (i < arr.size() - 1) std::cout << ", ";
            }
        } else {
            // Show all elements for small arrays
            for (size_t i = 0; i < arr.size(); i++) {
                std::cout << arr[i];
                if (i < arr.size() - 1) std::cout << ", ";
            }
        }
        std::cout << "\n";
    }
    
    // Verify if array is sorted
    static bool isSorted(const std::vector<int>& arr) {
        for (size_t i = 1; i < arr.size(); i++) {
            if (arr[i] < arr[i-1]) return false;
        }
        return true;
    }
};

// Function to clear input buffer
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Function to get integer input with validation
int getIntegerInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clearInputBuffer();
            return value;
        } else {
            std::cout << "Invalid input. Please enter a valid integer.\n";
            clearInputBuffer();
        }
    }
}

int main() {
    std::cout << "========================================\n";
    std::cout << "     PIGEONHOLE SORT PROGRAM\n";
    std::cout << "========================================\n\n";
    
    std::vector<int> numbers;
    int choice;
    
    do {
        std::cout << "\n--- MENU ---\n";
        std::cout << "1. Enter numbers manually\n";
        std::cout << "2. Generate random numbers\n";
        std::cout << "3. Display current array\n";
        std::cout << "4. Sort array using Pigeonhole Sort\n";
        std::cout << "5. Clear array\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        
        std::cin >> choice;
        clearInputBuffer();
        
        switch(choice) {
            case 1: {
                // Manual entry
                std::cout << "\n--- Manual Entry ---\n";
                int num_count = getIntegerInput("How many numbers do you want to enter? ");
                
                if (num_count <= 0) {
                    std::cout << "Invalid count. Please enter a positive number.\n";
                    break;
                }
                
                if (num_count > 1000000) {
                    std::cout << "Warning: Entering " << num_count 
                              << " numbers manually might be tedious!\n";
                    char confirm;
                    std::cout << "Are you sure you want to continue? (y/n): ";
                    std::cin >> confirm;
                    clearInputBuffer();
                    if (confirm != 'y' && confirm != 'Y') {
                        std::cout << "Operation cancelled.\n";
                        break;
                    }
                }
                
                numbers.clear();
                std::cout << "Enter " << num_count << " numbers (press Enter after each):\n";
                
                for (int i = 0; i < num_count; i++) {
                    int num = getIntegerInput("Number " + std::to_string(i + 1) + ": ");
                    numbers.push_back(num);
                }
                
                std::cout << "Successfully entered " << numbers.size() << " numbers.\n";
                break;
            }
            
            case 2: {
                // Generate random numbers
                std::cout << "\n--- Generate Random Numbers ---\n";
                int num_count = getIntegerInput("How many random numbers to generate? ");
                
                if (num_count <= 0) {
                    std::cout << "Invalid count. Please enter a positive number.\n";
                    break;
                }
                
                int min_val = getIntegerInput("Enter minimum value: ");
                int max_val = getIntegerInput("Enter maximum value: ");
                
                if (min_val > max_val) {
                    std::cout << "Invalid range. Minimum should be less than or equal to maximum.\n";
                    break;
                }
                
                // Generate random numbers
                numbers.clear();
                srand(time(nullptr));
                
                for (int i = 0; i < num_count; i++) {
                    int range = max_val - min_val + 1;
                    int num = min_val + (rand() % range);
                    numbers.push_back(num);
                }
                
                std::cout << "Generated " << numbers.size() << " random numbers.\n";
                std::cout << "Range: " << min_val << " to " << max_val << "\n";
                break;
            }
            
            case 3: {
                // Display current array
                std::cout << "\n--- Current Array ---\n";
                if (numbers.empty()) {
                    std::cout << "Array is empty. Add some numbers first.\n";
                } else {
                    std::cout << "Array size: " << numbers.size() << " elements\n";
                    PigeonholeSort::displayArray(numbers, "Array contents: ");
                    
                    // Check if already sorted
                    if (PigeonholeSort::isSorted(numbers)) {
                        std::cout << "Array is currently sorted.\n";
                    } else {
                        std::cout << "Array is currently unsorted.\n";
                    }
                }
                break;
            }
            
            case 4: {
                // Sort the array
                std::cout << "\n--- Sorting Array ---\n";
                
                if (numbers.empty()) {
                    std::cout << "Array is empty. Add some numbers first.\n";
                    break;
                }
                
                if (numbers.size() > 1000000) {
                    std::cout << "Warning: Sorting " << numbers.size() 
                              << " elements might take some time and memory.\n";
                    char confirm;
                    std::cout << "Continue? (y/n): ";
                    std::cin >> confirm;
                    clearInputBuffer();
                    if (confirm != 'y' && confirm != 'Y') {
                        std::cout << "Sort cancelled.\n";
                        break;
                    }
                }
                
                std::cout << "Sorting " << numbers.size() << " elements...\n";
                
                // Create a copy for timing demonstration
                std::vector<int> sorted_numbers = numbers;
                
                // Measure sorting time
                auto start = std::chrono::high_resolution_clock::now();
                PigeonholeSort::sort(sorted_numbers);
                auto end = std::chrono::high_resolution_clock::now();
                
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                
                // Verify sorting
                if (PigeonholeSort::isSorted(sorted_numbers)) {
                    std::cout << "✓ Array is correctly sorted!\n";
                    std::cout << "Sorting time: " << duration.count() << " milliseconds\n";
                    
                    // Ask if user wants to see the sorted array
                    char show;
                    std::cout << "\nDo you want to update the original array with sorted version? (y/n): ";
                    std::cin >> show;
                    clearInputBuffer();
                    
                    if (show == 'y' || show == 'Y') {
                        numbers = sorted_numbers;
                        std::cout << "Original array updated with sorted version.\n";
                    } else {
                        std::cout << "Sorted array is in temporary copy.\n";
                    }
                } else {
                    std::cout << "✗ Sorting verification failed! Something went wrong.\n";
                }
                break;
            }
            
            case 5: {
                // Clear array
                std::cout << "\n--- Clear Array ---\n";
                if (numbers.empty()) {
                    std::cout << "Array is already empty.\n";
                } else {
                    char confirm;
                    std::cout << "Are you sure you want to clear " << numbers.size() 
                              << " elements? (y/n): ";
                    std::cin >> confirm;
                    clearInputBuffer();
                    
                    if (confirm == 'y' || confirm == 'Y') {
                        numbers.clear();
                        std::cout << "Array cleared.\n";
                    } else {
                        std::cout << "Operation cancelled.\n";
                    }
                }
                break;
            }
            
            case 6: {
                std::cout << "\nExiting program. Goodbye!\n";
                break;
            }
            
            default: {
                std::cout << "Invalid choice. Please enter a number between 1 and 6.\n";
                break;
            }
        }
        
    } while (choice != 6);
    
    std::cout << "\n========================================\n";
    return 0;
}
