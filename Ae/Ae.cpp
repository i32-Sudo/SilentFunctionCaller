#include "Ae.h"

int GetFirstDigitFromUInt64(UINT64 value) {
    if (value == 0) {
        return 0;
    }
    while (value >= 10) {
        value /= 10;
    }
    return static_cast<int>(value);
}

void AeInitializeGlobalEncryption() {
    DbgPrint("[--IMPORTING ENCRYPTED BUFFER--]\n");
    int FunctionCells = 0;
    int CurrentFunctionCell = 0;

    int MemoryMapCellsPerFunction = 5;
    int MemoryMapCurrentSelection = 0;
    for (int i = 0; i < sizeof(MemoryMap::R0) / sizeof(MemoryMap::R0[0]); ++i) {
        MemoryMap::Functions Data = MemoryMap::R0[i];
        if (Data.Address != NULL && Data.FunctionID != NULL) {
            FunctionCells++;
        }
    }
    FunctionCells = FunctionCells - 1;

    DbgPrint("[+] (DR0)FunctionCells %d\n", FunctionCells);
    DbgPrint("[--------------------------------------]\n");
    for (int i = 0; i < sizeof(MemoryMap::DR0) / sizeof(MemoryMap::DR0[0]); ++i) {
        if (MemoryMap::DR0[i].FunctionID != NULL) continue;
        MemoryMap::DataRegister data = { };
        if (MemoryMapCurrentSelection != MemoryMapCellsPerFunction) {
            data.key = SimpleXOREncryption::GenerateRandomUINT64();
            data.value = SimpleXOREncryption::xorEncryptDecrypt(MemoryMap::R0[CurrentFunctionCell].Address, data.key);
            data.FunctionID = MemoryMap::R0[CurrentFunctionCell].FunctionID;
            MemoryMap::DR0[i] = data;
            DbgPrint("[+] (DR0)CurrentFunctionCell %d\n", CurrentFunctionCell);
            DbgPrint("[+] (DR0)CurrentMemoryMapCell %d\n", MemoryMapCurrentSelection);
            DbgPrint("[+] (DR0)Key = %I64u\n", data.key);
            DbgPrint("[+] (DR0)Value = %I64u\n", data.value);
            DbgPrint("[+] (DR0)FunctionID = %d\n", data.FunctionID);
            DbgPrint("[--------------------------------------]\n");
        }
        MemoryMapCurrentSelection = MemoryMapCurrentSelection + 1;
        if (MemoryMapCurrentSelection == MemoryMapCellsPerFunction) {
            CurrentFunctionCell = CurrentFunctionCell + 1;
            if (CurrentFunctionCell >= FunctionCells + 1) break;
            MemoryMapCellsPerFunction = MemoryMapCellsPerFunction + MemoryMapCellsPerFunction;
        }
    }

}

UINT64 AeRequestAddress(INT FunctionID) {
    DbgPrint("[--REQUESTING FUNCTION FROM ENCRYPTED BUFFER--]\n");
    int DR1Cells = 1;
    MemoryMap::clearDR1Registers();
    MemoryMap::clearR0Registers();
    for (int i = 0; i < sizeof(MemoryMap::DR0) / sizeof(MemoryMap::DR0[0]); ++i) {
        if (MemoryMap::DR0[i].FunctionID == NULL) continue;
        if (MemoryMap::DR0[i].FunctionID == FunctionID) {
            MemoryMap::DR1[DR1Cells] = MemoryMap::DR0[i];
            DR1Cells = DR1Cells + 1;
        }
    }

    DbgPrint("[+] (DR1)DR1Cells %d\n", DR1Cells);
    for (int i = 0; i < DR1Cells; ++i) {
        UINT64 RNA = SimpleXOREncryption::GenerateRandomUINT64();
        int Index = GetFirstDigitFromUInt64(RNA);
        while (Index > DR1Cells) {
            Index = Index - 1;
        }

        DbgPrint("[+] (DR1)SelectedIndex %d\n", Index);
        DbgPrint("[+] (DR1)EncryptionKey = %I64u\n", MemoryMap::DR1[Index].key);
        DbgPrint("[+] (DR1)EncryptedAddress = %I64u\n", MemoryMap::DR1[Index].value);
        MemoryMap::DataRegister data = MemoryMap::DR1[Index];
        return SimpleXOREncryption::xorEncryptDecrypt(data.value, data.key);
    }
}