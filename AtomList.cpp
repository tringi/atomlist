#include <windows.h>

extern "C" IMAGE_DOS_HEADER __ImageBase;

#ifndef _WIN64
DWORD wtn;
WNDCLASSEX wc;
wchar_t name [0x8000];
wchar_t text [0x8000];
#endif

void main () {
#ifdef _WIN64
    DWORD wtn;
    WNDCLASSEX wc;
    wchar_t name [0x8000];
    wchar_t text [0x8000];
#endif

    auto out = GetStdHandle (STD_OUTPUT_HANDLE);
    wc.cbSize = sizeof wc;

    for (unsigned int atom = 0xC000u; atom < 0x10000u; ++atom) {
        bool validAtom = GlobalGetAtomName ((ATOM) atom, name, 0x8000);
        bool validClass = GetClassInfoEx (NULL, (LPCTSTR) atom, &wc);
        bool validFormat = GetClipboardFormatName (atom, name, 0x8000);

        if (validAtom || validFormat || validClass) {
            auto length =
            wsprintf (text, L"%04X: %c%c%c: %s\n",
                      atom,
                      validAtom ? L'A' : L' ',
                      validClass ? L'C' : L' ',
                      validFormat ? L'F' : L' ',
                      name);
            WriteConsole (out, text, length, &wtn, NULL);
        }
    }
    ExitProcess (__ImageBase.e_magic);
};
/*
extern "C" char * __cdecl __unDName (void *, const void *, int, void *, void *, unsigned short) {
    return nullptr;
}
extern "C" LCID __cdecl __acrt_DownlevelLocaleNameToLCID (LPCWSTR localeName) {
    return 0;
}
extern "C" int __cdecl __acrt_DownlevelLCIDToLocaleName (
    LCID   lcid,
    LPWSTR outLocaleName,
    int    cchLocaleName
) {
    return 0;
}*/