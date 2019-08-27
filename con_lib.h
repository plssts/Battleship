#ifndef CON_LIB_H
#define CON_LIB_H

// Spalvos
#define COLOR_BLACK     0
#define COLOR_RED       1
#define COLOR_GREEN     2
#define COLOR_ORANGE    3
#define COLOR_BLUE      4
#define COLOR_MAGENTA   5
#define COLOR_CYAN      6
#define COLOR_GRAY      7

// I�valo ekran�
void con_clear();

// Nuskaito vien� klavi��. 
// Gra�ina 0, jei n�ra ko daugiau skaityti
int con_read_key();

// Nustato fono ir teksto spalv�
// * bg - fono spalva (COLOR_*)
// * fg - teksto spalva (COLOR_*)
void con_set_color(int bg, int fg);

// Nustato dabartin� i�vedimo pozicij�. x, y - koordinat�s:
// * vir�utinis kairys terminalo kampas yra (0, 0)
// * x-ai did�ja i� kair�s � de�in�
// * y-ai did�ja i� vir�aus � apa�i�
void con_set_pos(int x, int y);

// Nustato cursoriaus rodymo r��im�.
// * Jei show == 0, cursori� paslepia
// * Jei show == 1, cursori� rodo
void con_show_cursor(int show);

// Padaro, kad nesimatyt� �vedam� simboli� (tik LINUX os)
// * Jei show == 0, tai �vedam� simboli� neatkartoja � ekran�
// * Jei show == 1, tai �vedamus simbolius rodo 
// * Ant Windows nieko nedaro 
void con_show_echo(int show);

// Miega nurodyt� sekund�i� skai�i�.
// * seconds turi b�ti intervale [0.01; 100.0]
void con_sleep(float seconds);

#endif // CON_LIB_H