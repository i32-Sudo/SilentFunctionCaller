#include "memory_map.h"

namespace MemoryMap {
    UINT64 BaseAddress;

    // Create arrays for DR0 and DR1 registers (40 Items)
    DataRegister DR0[40]; // Encrypted Cache Table
    DataRegister DR1[40]; // Temporary Request Cache Table
    Functions R0[26];     // Init Table

    // Function to initialize the data registers
    void initializeRegisters() {
        for (int i = 0; i < 40; ++i) {
            DR0[i] = { 0, 0, 0 }; // Initialize DR0 registers
            DR1[i] = { 0, 0, 0 }; // Initialize DR1 registers
        }
        for (int i = 0; i < 26; ++i) {
            R0[i] = { 0, 0 }; // Initialize R0 functions
        }
    }

    void clearDR0Registers() {
        for (int i = 0; i < 40; ++i) {
            DR0[i] = { 0, 0, 0 }; // Clear DR0 registers
        }
    }

    void clearDR1Registers() {
        for (int i = 0; i < 40; ++i) {
            DR1[i] = { 0, 0, 0 }; // Clear DR1 registers
        }
    }

    void clearR0Registers() {
        for (int i = 0; i < 26; ++i) {
            R0[i] = { 0, 0 }; // Clear R0 functions
        }
    }
}
