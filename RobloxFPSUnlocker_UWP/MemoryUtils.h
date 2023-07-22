#pragma once

// utils used for sig scanner
#define INRANGE(x, a, b) (x >= a && x <= b)
#define GET_BYTE(x) ((GET_BITS(x[0]) << 4) | GET_BITS(x[1]))
#define GET_BITS(x) (INRANGE((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xa) : (INRANGE(x, '0', '9') ? (x - '0') : 0))

// util used to call functions by their uintptr_t address
template <typename R, typename... Args>
R CallFunc(uintptr_t func, Args... args) {
    return ((R(*)(Args...))func)(args...);
}

// roblox base address
uintptr_t roblox = (uintptr_t)GetModuleHandleA("Windows10Universal.exe");

// tbh i dont recall where i got this sig scanner but props to whoever made it
static uintptr_t findSig(const char* sig) {

    const char* pattern = sig;
    uintptr_t first_match = 0;
    static MODULEINFO mi_mod_info;
    static bool init = false;
    if (!init)
    {
        init = true;
        GetModuleInformation(GetCurrentProcess(), reinterpret_cast<HMODULE>(roblox), &mi_mod_info, sizeof(MODULEINFO));
    }
    static const uintptr_t range_end = roblox + mi_mod_info.SizeOfImage;

    BYTE pat_byte = GET_BYTE(pattern);
    const char* old_pat = pattern;

    for (uintptr_t p_cur = roblox; p_cur < range_end; p_cur++) // eevrything we use is over 0x100000 so we can just skip that part of memory
    {
        if (!*pattern)
        {
            return first_match;
        }

        while (*(PBYTE)pattern == ' ')
        {
            pattern++;
        }

        if (!*pattern)
        {
            return first_match;
        }

        if (old_pat != pattern)
        {
            old_pat = pattern;
            if (*(PBYTE)pattern != '\?') {
                pat_byte = GET_BYTE(pattern);
            }
        }

        if (*(PBYTE)pattern == '\?' || *(BYTE*)p_cur == pat_byte)
        {
            if (!first_match)
            {
                first_match = p_cur;
            }

            if (!pattern[2])
            {
                return first_match;
            }

            pattern += 2;
        }
        else
        {
            pattern = sig;
            first_match = 0;
        }
    }

    return 0;

}