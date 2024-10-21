#pragma once
#include "../imports.h"

int GetFirstDigitFromUInt64(UINT64 value);
void AeInitializeGlobalEncryption();
UINT64 AeRequestAddress(INT FunctionID);

template<typename ReturnType, typename... Args>
ReturnType SilentCALLAddress(INT FunctionID, Args... args) {
    UINT64 Address = AeRequestAddress(FunctionID);
    DbgPrint("[+] (DR1)DecryptedAddress = %I64u\n", Address);
    DbgPrint("[--EXECUTING FUNCTION PTR(DECRYPTED)--]\n");
    using FunctionPtrType = ReturnType(*)(Args...);
    FunctionPtrType func = reinterpret_cast<FunctionPtrType>(Address);
    DbgPrint("[--RETURNING--]\n");
    return func(args...);
}