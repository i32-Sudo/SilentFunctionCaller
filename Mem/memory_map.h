#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#include <cstdint>
#include "../imports.h"

namespace MemoryMap {
    const int MAX_FUNCTIONS = 26;  // Size for R0
    const int MAX_DR0 = 40;         // Size for DR0
    const int MAX_DR1 = 40;         // Size for DR1

    struct Functions {
        UINT64 Address;
        INT FunctionID;
    };

    struct DataRegister {
        UINT64 key;
        UINT64 value;
        INT FunctionID;
    };

    extern Functions R0[MAX_FUNCTIONS]; // Function table
    extern DataRegister DR0[MAX_DR0];    // Encrypted Cache Table
    extern DataRegister DR1[MAX_DR1];    // Temporary Request Cache Table
    extern UINT64 BaseAddress;            // Base address for the driver

    void initializeRegisters();
    void clearDR1Registers();
    void clearDR0Registers();
    void clearR0Registers();
}

#endif // MEMORY_MAP_H
