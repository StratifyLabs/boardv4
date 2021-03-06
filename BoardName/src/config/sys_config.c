//Copyright 2021 Stratify Labs, See LICENSE.md for details

#include "sys_config.h"

void sys_initialize() {
  //initialize the board
  //this is one of the first things called
  //it should initialize the CLOCK/PLL
  //run in ROOT mode before the scheduler is started
  #error "sys_initialize() not implemented"
}

void sys_get_serial_number(mcu_sn_t *serial_number) {
  //populate serial_number
  #error "sys_get_serial_number() not implemented"
}

int sys_kernel_request(int request, void *arg) {
  //these are custom requests to allow applications
  //to execute kernel functions
  #error "sys_kernel_request() not implemented"
  return -1;
}

const void *sys_kernel_request_api(u32 request) {
  //this allows creatined "shared" libraries
  //you return a pointer to a function table
  #error "sys_kernel_request_api() not implemented"
  return NULL;
}

void sys_pio_set_attributes(int port, const pio_attr_t *attr) {
  //convenience function to configuring IO
  //always called in ROOT mode
  #error "sys_pio_set_attributes() not implemented"

}

void sys_pio_write(int port, u32 mask, int value) {
  //convenience function to writing IO
  //always called in ROOT mode
  #error "sys_pio_write() not implemented"
}

u32 sys_pio_read(int port, u32 mask) { 
    //convenience function to reading IO
  //always called in ROOT mode
  #error "sys_pio_read() not implemented"
  return 0; 
}
