#pragma once
#include <ntdef.h>
#include <ntifs.h>
#include <ntddk.h>
#include <ntimage.h>
#include <windef.h>
#include <intrin.h>
#include <ntstrsafe.h>
#include <wdm.h>
#include "Encryption.hpp"

enum {
	JMP = 0x1,
	JMP_CONDITION = 0x2
} Conditions;

enum {
    ID_CHECK1 = 0x1,
    ID_CHECK2 = 0x2
} Functions;

namespace MemoryMap {
    UINT64 BaseAddress;
    // Structure to represent a data register
    struct Functions {
        UINT64 Address;
        INT FunctionID;
    };

    struct DataRegister {
        UINT64 value;
        UINT64 key;
        INT FunctionID;
    };

    // Create arrays for DR0 and DR1 registers (40 Items)
    DataRegister DR0[40]; // Encrypted Cache Table
    DataRegister DR1[40]; // Temporary Request Cache Table
    Functions R0[26]; // Init Table

    // Function to initialize the data registers
    void initializeRegisters() {
        for (int i = 0; i < 40; ++i) {
            DR0[i] = { 0, 0, 0 }; // Initialize DR0 registers
            DR1[i] = { 0, 0, 0 }; // Initialize DR1 registers
        }
        for (int i = 0; i < 26; ++i) {
            R0[i] = { 0, 0 };
        }
    }

    void clearDR0Registers() {
        for (int i = 0; i < 40; ++i) {
            DR0[i] = { 0, 0, 0 };
        }
    }

    void clearDR1Registers() {
        for (int i = 0; i < 40; ++i) {
            DR1[i] = { 0, 0, 0 };
        }
    }

    void clearR0Registers() {
        for (int i = 0; i < 26; ++i) {
            R0[i] = { 0, 0 };
        }
    }

}