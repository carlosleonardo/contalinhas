//
// Created by carlo on 07/02/2026.
//

#include "terminal.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

std::size_t obter_largura_terminal() {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)==FALSE) {
        return 80; // Valor padrão se não conseguir obter informações do console
    }
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
#endif
}