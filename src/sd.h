#pragma once

#include "accelerometer.h"

void init_sd_card();

void save_entry(const accelerometer_data& data);
