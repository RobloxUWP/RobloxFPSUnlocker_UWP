#include <windows.h>
#include <psapi.h>

#include "MemoryUtils.h"

#include "RBX.h"

// all our init code here
void InitClient(HMODULE module) {
    // set per frame delay to 1/10000
    RBX::TaskScheduler::SetFPS(10000);
}

// dll entry point
BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH) {

        // stop library from being injected more then once
        DisableThreadLibraryCalls(module);

        // initialize main C++ thread
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)InitClient, module, 0, 0);
    }

    return TRUE;
}