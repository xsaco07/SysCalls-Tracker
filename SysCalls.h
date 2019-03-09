#ifndef SYS_CALLS_MODULE
#define SYS_CALLS_MODULE

#include <unistd.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <stdlib.h>

#define SYS_CALLS_CONUT 190

struct sys_call{
  long number;
  char* name;
  int times_called;
};

struct sys_call sys_calls_array[SYS_CALLS_CONUT];

void initialize_sys_calls();
void initialize_sys_call_struct(struct sys_call* sys_call_struct, long number, char* name, int times_called);
void print_sys_call_info(struct sys_call* sys_call_struct);
void print_array_sys_calls();

#endif
