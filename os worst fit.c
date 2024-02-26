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

// Function to allocate memory using Worst Fit algorithm
void allocateMemory(int processSize) {
    int worstFitIndex = -1;
    int maxFragmentation = -1;

    // Find the block with largest fragmentation that can accommodate the process
    for (int i = 0; i < MAX_MEMORY; i++) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            int fragmentation = memory[i].size - processSize;
            if (fragmentation > maxFragmentation) {
                maxFragmentation = fragmentation;
                worstFitIndex = i;
            }
        }
    }

    // Allocate memory if a suitable block is found
    if (worstFitIndex != -1) {
        memory[worstFitIndex].allocated = 1;
        printf("Memory allocated successfully starting from address %d\n", memory[worstFitIndex].startingAddress);

        // Split block if necessary
        if (memory[worstFitIndex].size > processSize) {
            MemoryBlock newBlock;
            newBlock.startingAddress = memory[worstFitIndex].startingAddress + processSize;
            newBlock.size = memory[worstFitIndex].size - processSize;
            newBlock.allocated = 0;

            // Move existing blocks to make space for the new block
            for (int j = MAX_MEMORY - 1; j > worstFitIndex; j--) {
                memory[j] = memory[j - 1];
            }

            // Insert the new block
            memory[worstFitIndex + 1] = newBlock;
        }

        // Update size of allocated block
        memory[worstFitIndex].size = processSize;
    } else {
        printf("Memory allocation failed for process of size %d\n", processSize);
    }
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
