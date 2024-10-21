#pragma once
#include "imports.h"

class SimpleXOREncryption {
public:
    static UINT64 xorEncryptDecrypt(UINT64 value, UINT64 key) {
        return value ^ key; // XOR operation
    }

    static ULONG InitializeRandomSeed()
    {
        LARGE_INTEGER time;
        KeQuerySystemTime(&time);
        return (ULONG)(time.QuadPart & 0xFFFFFFFF); // Use lower 32 bits for seed
    }

    static UINT64 GenerateRandomUINT64()
    {
        UINT64 randomValue = 0;
        ULONG Seed = InitializeRandomSeed();
        for (int i = 0; i < 2; i++) {
            randomValue = (randomValue << 32) | RtlRandomEx(&Seed); // Combine two 32-bit values
        }

        return randomValue;
    }
};

class KeyExchange {
public:
    UINT64 privateKey;
    UINT64 publicKey;

    KeyExchange(UINT64 xorKey) {
        privateKey = SimpleXOREncryption::GenerateRandomUINT64(); // Generate private key
        publicKey = SimpleXOREncryption::xorEncryptDecrypt(privateKey, xorKey); // Simulated public key (in real scenarios, use a proper method)
    }

    // Generate shared secret from received public key
    UINT64 computeSharedSecret(UINT64 receivedPublicKey) {
        return SimpleXOREncryption::xorEncryptDecrypt(receivedPublicKey, privateKey);
    }
};