#include "imports.h"
extern "C" int ASMJe(int condition, int true_value, int false_value);

ULONG Check1(const char* message) {
    return (DbgPrint("DEBUG: %s\n", message));
}

ULONG Check2(const char* message) {
    return (DbgPrint("DEBUG: %s\n", message));
}


void DriverUnload(PDRIVER_OBJECT DriverObject);
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    DriverObject->DriverUnload = DriverUnload;

    MemoryMap::initializeRegisters();
    MemoryMap::BaseAddress = (UINT64)(ULONG_PTR)DriverObject->DriverStart;
    MemoryMap::R0[0] = { (UINT64)&Check1, ID_CHECK1};
    MemoryMap::R0[1] = { (UINT64)&Check2, ID_CHECK2};
    AeInitializeGlobalEncryption();
    ULONG Check1Dbg = SilentCALLAddress<ULONG>(ID_CHECK1, "Hello From Check1 Function!");

    DbgPrint("[--PROGRAM END--]\n");

    return STATUS_SUCCESS;
}

void DriverUnload(PDRIVER_OBJECT DriverObject) {
    MemoryMap::clearDR1Registers();
    MemoryMap::clearDR0Registers();
    MemoryMap::clearR0Registers();

    DbgPrint("Driver Unloaded\n");
}