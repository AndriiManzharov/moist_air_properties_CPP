// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include "Water.h"
#include "DryAir.h"
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    Water::LoadData();
    DryAir::LoadData();
    break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        //delete water_heat_capacity;
        break;
    }
    return TRUE;
}

