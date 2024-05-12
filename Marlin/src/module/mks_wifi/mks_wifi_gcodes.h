#pragma once

#include "../../gcode/gcode.h"
#include "../temperature.h"
#include "../../sd/cardreader.h"

#include "mks_wifi.h"
#include "mks_wifi_sd.h"

#ifdef MKS_WIFI

void mks_m991();
void mks_m992();
void mks_m994();
void mks_m997();
void mks_m115();
void mks_m105();
void mks_m23(char *filename);
void mks_m27();
void mks_m30(char *filename);

#endif