#ifndef HEADER_GUARD_SHOW_MESSAGE_H
#define HEADER_GUARD_SHOW_MESSAGE_H

extern bool showing_message;

void hook_show_message();
void show_message(std::string message);
void clear_message();

#endif
