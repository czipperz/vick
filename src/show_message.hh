#ifndef HEADER_GUARD_SHOW_MESSAGE_H
#define HEADER_GUARD_SHOW_MESSAGE_H

extern bool showing_message;

void hook_show_message();
void show_message(const char* message);
void clear_message();

#endif
