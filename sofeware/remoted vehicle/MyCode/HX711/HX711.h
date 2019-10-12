#ifndef __HX711_H
#define __HX711_H

#include "sys.h"

#define HX711_SCK PBout(0)// PB0
#define HX711_DOUT PBout(1)// PB1


extern void Init_HX711pin(void);
extern unsigned long HX711_Read(void);


#endif

