#pragma once

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

int win_init(void);
void win_put(int, int);
void win_update();
void win_mainloop();
void win_clear();