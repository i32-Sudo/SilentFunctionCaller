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
#include "Mem/memory_map.h"
#include "Ae/Ae.h"

#define ID_CHECK1 0x2
#define ID_CHECK2 0x3