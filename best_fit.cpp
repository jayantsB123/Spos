#include <iostream>
#include <vector>

using namespace std;

struct MemoryBlock {
    int id;
    int size;
    bool allocated;
};

void bestFit(vector<MemoryBlock>& memory, int processId, int processSize) {
    int bestFitIndex = -1;
    int bestFitSize = INT_MAX;

    for (int i = 0; i < memory.size(); i++) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            if (memory[i].size < bestFitSize) {
                bestFitIndex = i;
                bestFitSize = memory[i].size;
            }
        }
    }

    if (bestFitIndex != -1) {
        memory[bestFitIndex].allocated = true;
        cout << "Allocated Process " << processId << " to Block " << memory[bestFitIndex].id << endl;
    } else {
        cout << "Process " << processId << " cannot be allocated." << endl;
    }
}

void deallocate(vector<MemoryBlock>& memory, int processId) {
    for (int i = 0; i < memory.size(); i++) {
        if (memory[i].allocated && memory[i].id == processId) {
            memory[i].allocated = false;
            cout << "Deallocated Process " << processId << " from Block " << memory[i].id << endl;
            break;
        }
    }
}

int main() {
    int blockSize, numBlocks, numProcesses;
    cout << "Enter the number of memory blocks: ";
    cin >> numBlocks;
    
    vector<MemoryBlock> memory(numBlocks);

    for (int i = 0; i < numBlocks; i++) {
        memory[i].id = i + 1;
        cout << "Enter size of Memory Block " << memory[i].id << ": ";
        cin >> memory[i].size;
        memory[i].allocated = false;
    }

    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    for (int i = 0; i < numProcesses; i++) {
        int processSize;
        cout << "Enter size of Process " << i + 1 << ": ";
        cin >> processSize;
        bestFit(memory, i + 1, processSize);
    }

    cout << "Memory Block Status after allocation:" << endl;
    for (const MemoryBlock& block : memory) {
        cout << "Block " << block.id << ": ";
        if (block.allocated) {
            cout << "Allocated (Size: " << block.size << ")";
        } else {
            cout << "Free (Size: " << block.size << ")";
        }
        cout << endl;
    }

    // Deallocate processes
    int processToDeallocate;
    cout << "Enter the process to deallocate (0 to exit): ";
    cin >> processToDeallocate;
    while (processToDeallocate != 0) {
        deallocate(memory, processToDeallocate);
        cout << "Memory Block Status after deallocation:" << endl;
        for (const MemoryBlock& block : memory) {
            cout << "Block " << block.id << ": ";
            if (block.allocated) {
                cout << "Allocated (Size: " << block.size << ")";
            } else {
                cout << "Free (Size: " << block.size << ")";
            }
            cout << endl;
        }
        cout << "Enter the process to deallocate (0 to exit): ";
        cin >> processToDeallocate;
    }

    return 0;
}
