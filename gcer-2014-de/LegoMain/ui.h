// Created on Tue May 13 2014

#ifndef _UI_H_
#define _UI_H_

#define SLEEP_MSECONDS_IN_TOURNAMENT_MODE 100
#define DISPLAY_PRINTF_LINES_ON_LINK 10

int confirm_selection(int message_line_number);
void press_a_to_continue();
void set_mode(int mode);
void get_robot();
int select_strategy();

#endif
