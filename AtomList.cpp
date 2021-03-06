#include <windows.h>

extern "C" IMAGE_DOS_HEADER __ImageBase;
HANDLE out;

DWORD wtn;
WNDCLASSEX wc;
wchar_t name [256];
wchar_t text [512];

#ifndef _WIN64
__declspec(naked)
#endif
__declspec (noreturn) void main () {

    out = GetStdHandle (STD_OUTPUT_HANDLE);
    wc.cbSize = sizeof wc;

    for (unsigned short atom = 0xC000u; atom != 0; ++atom) {
        bool validFormat = GetClipboardFormatName (atom, name, 255u);
        bool validAtom = GlobalGetAtomName (( ATOM) atom, name, 255u);
        bool validClass = GetClassInfoEx (NULL, ( LPCTSTR) atom, &wc);

        if (validAtom || validClass || validFormat) {
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
    ExitProcess (0);
};
