#include "Global.h"
#include "../Library/LightHook.h"

static HookInformation g_Hook;
typedef RPC_STATUS(*TargetFunction_t)(UUID* uuid);

RPC_STATUS HookedUuidCreate(UUID* uuid)
{
    MessageBoxA(nullptr, "UuidCreate() was called, auth related strings should now be in memory", "InternalHelper", MB_OK | MB_ICONINFORMATION);

    auto original = static_cast<TargetFunction_t>(g_Hook.Trampoline);
    return original(uuid);
}

void Entry()
{
    MessageBoxA(nullptr, "Press OK to continue", "InternalHelper", MB_OK | MB_ICONINFORMATION);

    HMODULE targetModule = LoadLibraryA("rpcrt4.dll");
    if (!targetModule)
    {
        MessageBoxA(nullptr, "Failed to load rpcrt4.dll", "InternalHelper", MB_OK | MB_ICONERROR);
        return;
    }

    FARPROC targetProc = GetProcAddress(targetModule, "UuidCreate");
    if (!targetProc)
    {
        MessageBoxA(nullptr, "Failed to find UuidCreate", "InternalHelper", MB_OK | MB_ICONERROR);
        return;
    }

    g_Hook = CreateHook(targetProc, (void*)&HookedUuidCreate);
    int status = EnableHook(&g_Hook);
    if (!status)
    {
        MessageBoxA(nullptr, "Failed to hook UuidCreate", "InternalHelper", MB_OK | MB_ICONERROR);
        return;
    }

    MessageBoxA(nullptr, "Everything ready", "InternalHelper", MB_OK | MB_ICONINFORMATION);
}

BOOL APIENTRY DllMain(HMODULE moduleHandle, DWORD reason, LPVOID reserved)
{
    UNREFERENCED_PARAMETER(moduleHandle);
    UNREFERENCED_PARAMETER(reserved);

    if (reason == DLL_PROCESS_ATTACH)
        Entry();

    return true;
}