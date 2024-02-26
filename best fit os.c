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

// Function to allocate memory using Best Fit algorithm
void allocateMemory(int processSize) {
    int bestFitIndex = -1;
    int minFragmentation = MAX_MEMORY + 1;

    // Find the block with smallest fragmentation that can accommodate the process
    for (int i = 0; i < MAX_MEMORY; i++) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            int fragmentation = memory[i].size - processSize;
            if (fragmentation < minFragmentation) {
                minFragmentation = fragmentation;
                bestFitIndex = i;
            }
        }
    }

    // Allocate memory if a suitable block is found
    if (bestFitIndex != -1) {
        memory[bestFitIndex].allocated = 1;
        printf("Memory allocated successfully starting from address %d\n", memory[bestFitIndex].startingAddress);

        // Split block if necessary
        if (memory[bestFitIndex].size > processSize) {
            MemoryBlock newBlock;
            newBlock.startingAddress = memory[bestFitIndex].startingAddress + processSize;
            newBlock.size = memory[bestFitIndex].size - processSize;
            newBlock.allocated = 0;

            // Move existing blocks to make space for the new block
            for (int j = MAX_MEMORY - 1; j > bestFitIndex; j--) {
                memory[j] = memory[j - 1];
            }

            // Insert the new block
            memory[bestFitIndex + 1] = newBlock;
        }

        // Update size of allocated block
        memory[bestFitIndex].size = processSize;
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
