#ifndef Map_H
#define Map_H

void map_ini();

void map_G();

void map_window_break(int x, int y);

char map_is_step(int x, int y);

char map_step_use(int x, int y, char com);

char map_is_Bwindow(int x, int y);

void map_rep_Bwindow(int x, int y);

#endif

