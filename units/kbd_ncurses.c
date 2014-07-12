#include <ncurses/ncurses.h>
#include "kbd.h"

volatile uint8_t KbdData;
volatile uint8_t KbdDataAvail;

//extern PROGMEM uint8_t ps2code2ascii[];
//extern PROGMEM uint8_t ps2code2asciiE0[];

const uint8_t
keyChars[] PROGMEM = {
  /* KCHAR_ROWS x KCHAR_COLS */
  '0', ' ', '.', ',', ')', '+', '?', '_', ':',
  '1', 'a', 'b', 'c', '!', 'A', 'B', 'C', '~',
  '2', 'd', 'e', 'f', '@', 'D', 'E', 'F', '{',
  '3', 'g', 'h', 'i', '#', 'G', 'H', 'I', '}',
  '4', 'j', 'k', 'l', '$', 'J', 'K', 'L', '[',
  '5', 'm', 'n', 'o', '%', 'M', 'N', 'O', ']',
  '6', 'p', 'q', 'r', '^', 'P', 'Q', 'R', '|',
  '7', 's', 't', 'u', '&', 'S', 'T', 'U', '/',
  '8', 'v', 'w', 'x', '*', 'V', 'W', 'X', '<',
  '9', 'y', 'z', '(', '-', 'Y', 'Z', '=', '>',
};

/* ASCII_UNDEF in this table signifies good character */
uint8_t
cursesKbdFixes[] = {
  ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_BACKSPACE, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_ENTER, ASCII_UNDEF, ASCII_UNDEF, /*  0-15 */
  ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, /* 16-31 */
  ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, /* 32-47 */
  ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, /* 48-63 */
  ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, /* 64-79 */
  ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, /* 80-95 */
  ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, /* 96-111 */
  ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_DEFINED, ASCII_UNDEF, /* 112-127 */
  ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_BACKSPACE, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_ENTER, ASCII_UNDEF, ASCII_UNDEF, /*  128-143 */
  ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_BACKSPACE, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_ENTER, ASCII_UNDEF, ASCII_UNDEF, /*  144-159 */
  ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_BACKSPACE, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_ENTER, ASCII_UNDEF, ASCII_UNDEF, /*  160-175 */
  ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_BACKSPACE, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_ENTER, ASCII_UNDEF, ASCII_UNDEF, /*  176-191 */
  ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_BACKSPACE, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_ENTER, ASCII_UNDEF, ASCII_UNDEF, /*  192-207 */
  ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_BACKSPACE, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_ENTER, ASCII_UNDEF, ASCII_UNDEF, /*  208-223 */
  ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_BACKSPACE, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_ENTER, ASCII_UNDEF, ASCII_UNDEF, /*  224-239 */
  ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_BACKSPACE, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_ENTER, ASCII_UNDEF, ASCII_UNDEF, /*  240-255 */
  ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_BACKSPACE, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_ENTER, ASCII_UNDEF, ASCII_UNDEF, /*  256-271 */
  ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_BACKSPACE, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_ENTER, ASCII_UNDEF, ASCII_UNDEF, /*  272-287 */
  ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_BACKSPACE, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_ENTER, ASCII_UNDEF, ASCII_UNDEF, /*  288-303 */
  ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_BACKSPACE, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_ENTER, ASCII_UNDEF, ASCII_UNDEF, /*  304-319 */
  ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_BACKSPACE, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_ENTER, ASCII_UNDEF, ASCII_UNDEF, /*  320-335 */
  ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_BACKSPACE, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_UNDEF, ASCII_ENTER, ASCII_UNDEF, ASCII_UNDEF, /*  336-351 */
};

void
KbdInit(void)
{
  cbreak();
  noecho();
  cursesKbdFixes[KEY_UP] = ASCII_UP;
  cursesKbdFixes[KEY_LEFT] = ASCII_LEFT;
  cursesKbdFixes[KEY_RIGHT] = ASCII_RIGHT;
  cursesKbdFixes[KEY_DOWN] = ASCII_DOWN;
  cursesKbdFixes[KEY_DC] = ASCII_DEL;
  cursesKbdFixes[KEY_DL] = ASCII_DEL;
  cursesKbdFixes[KEY_F(2)] = ASCII_F2;
  cursesKbdFixes[KEY_PRINT] = ASCII_PRNSCRN;
  cursesKbdFixes[KEY_F(4)] = ASCII_NUMLK;
  cursesKbdFixes[KEY_BACKSPACE] = ASCII_BACKSPACE;
  cursesKbdFixes[KEY_ENTER] = ASCII_ENTER;
  cursesKbdFixes[ASCII_LF] = ASCII_ENTER;
  cursesKbdFixes[ASCII_ENTER] = ASCII_ENTER;
}

void
KbdScan(void)
{
  assert(0);
}

#undef KBD_GETCH
#define KBD_GETCH	do {			\
  uint16_t  t_data;				\
  KbdDataAvail = 0;				\
  t_data = getch();				\
  assert(t_data < sizeof(cursesKbdFixes));	\
  /*move(1, 0);*/						\
  /*printw("kbd raw1:0x%x    ", t_data);*/			\
  if (ASCII_UNDEF == cursesKbdFixes[t_data]) {			\
  } else if (ASCII_DEFINED == cursesKbdFixes[t_data]) {	\
    KbdData = t_data;						\
    assert(KbdData == t_data); /* check data size */		\
    KbdDataAvail = 1;				\
  } else {					\
    KbdData = cursesKbdFixes[t_data];		\
    KbdDataAvail = 1;				\
  }						\
  /*move(2, 0);*/						\
  /*printw("kbd raw2:0x%x    ", KbdData);*/			\
} while (0 == KbdDataAvail)

uint8_t
KbdIsShiftPressed(void)
{
}
