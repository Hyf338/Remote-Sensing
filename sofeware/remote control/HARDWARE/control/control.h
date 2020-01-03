#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"

u8 mode_select(u8 mode);
void display(u8 mode);
void adc_data_process(void);
void data_send_process(u8 mode);


#endif


