/*
  courtesy of: https://github.com/tuxmark5
*/

#ifndef CON_LIB_H
#define CON_LIB_H

// Colours
#define COLOR_BLACK     0
#define COLOR_RED       1
#define COLOR_GREEN     2
#define COLOR_ORANGE    3
#define COLOR_BLUE      4
#define COLOR_MAGENTA   5
#define COLOR_CYAN      6
#define COLOR_GRAY      7

void con_clear();
int con_read_key();

// * bg - background colour (COLOR_*)
// * fg - text colour (COLOR_*)
void con_set_color(int bg, int fg);

void con_set_pos(int x, int y);
void con_show_cursor(int show);
void con_show_echo(int show);
void con_sleep(float seconds);

#endif // CON_LIB_H
