#pragma once

struct accelerometer_data
{
    float x_accel = 0.f;
    float y_accel = 0.f;
    float z_accel = 0.f;
    float x_gyro = 0.f;
    float y_gyro = 0.f;
    float z_gyro = 0.f;
};

void init_accelerometer();

void get_accelerometer_data(accelerometer_data& data);

void print_accelerometer_data(const accelerometer_data& data);
