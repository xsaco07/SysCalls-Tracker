#ifndef SYS_CALLS_MODULE
#define SYS_CALLS_MODULE

#include <unistd.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <stdlib.h>

#define SYS_CALLS_CONUT 334

struct sys_call{
  int number;
  char* name;
  int times_called;
};

struct sys_call sys_calls_array[SYS_CALLS_CONUT];

void initialize_sys_calls_array();
struct sys_call create_sys_call_struct(int number, char* name, int times_called);
void print_sys_call_info(int sys_call_number);
void print_sys_calls_array();
void set_sys_calls_names();
struct sys_call get_sys_call(int position);
void sys_call_seen(int sys_call_number);

#endif
