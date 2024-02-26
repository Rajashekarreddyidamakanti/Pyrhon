#include <stdio.h>
#include <stdlib.h>

#define MAX_MEMORY 1000

// Structure to represent a memory block
typedef struct MemoryBlock {
    int startingAddress;
    int size;
    int allocated;
} MemoryBlock;

MemoryBlock memory[MAX_MEMORY];

// Function to initialize the memory blocks
void initializeMemory() {
    memory[0].startingAddress = 0;
    memory[0].size = MAX_MEMORY;
    memory[0].allocated = 0;
}

// Function to allocate memory using First Fit algorithm
void allocateMemory(int processSize) {
    int i;
    for (i = 0; i < MAX_MEMORY; i++) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            // Allocate memory
            memory[i].allocated = 1;
            printf("Memory allocated successfully starting from address %d\n", memory[i].startingAddress);

            // Split block if necessary
            if (memory[i].size > processSize) {
                MemoryBlock newBlock;
                newBlock.startingAddress = memory[i].startingAddress + processSize;
                newBlock.size = memory[i].size - processSize;
                newBlock.allocated = 0;

                // Move existing blocks to make space for the new block
                for (int j = MAX_MEMORY - 1; j > i; j--) {
                    memory[j] = memory[j - 1];
                }

                // Insert the new block
                memory[i + 1] = newBlock;
            }

            // Update size of allocated block
            memory[i].size = processSize;

            break;
        }
    }
    if (i == MAX_MEMORY)
        printf("Memory allocation failed for process of size %d\n", processSize);
}

int main() {
    initializeMemory();

    // Example: allocate memory for processes of sizes 200, 400, 600, and 800
    allocateMemory(200);
    allocateMemory(400);
    allocateMemory(600);
    allocateMemory(800);

    return 0;
}
