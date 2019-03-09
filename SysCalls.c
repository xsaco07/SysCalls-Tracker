#include "SysCalls.h"

void initialize_sys_calls(){
  for (int i = 0; i < SYS_CALLS_CONUT; i++) {
    struct sys_call current_sys_call;
    initialize_sys_call_struct(&current_sys_call, -1, "", 0);
    sys_calls_array[i] = current_sys_call;
  }
}

void initialize_sys_call_struct(struct sys_call* sys_call_struct, long number, char* name, int times_called){
  sys_call_struct->name = name;
  sys_call_struct->times_called = times_called;
  sys_call_struct->number = number;
}

void print_array_sys_calls(){
  for (int i = 0; i < SYS_CALLS_CONUT; i++) {
    print_sys_call_info(&sys_calls_array[i]);
  }
}

void print_sys_call_info(struct sys_call* sys_call_struct){
  printf("\nName: %s\n", sys_call_struct->name);
  printf("Sys call number: %ld\n", sys_call_struct->number);
  printf("\nTimes Called: %d\n", sys_call_struct->times_called);
}
