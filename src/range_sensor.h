/**
 * @file RangeSensor.h
 * @author Hirotaka Hosogaya (hosogaya.hirotaka@b.mbox.nagoya-u.ac.jp)
 * @brief 
 * @version 0.1
 * @date 2021-12-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include "vl6180x-arduino/VL6180X.h"
#include <Wire.h>
#include <array>

class RangeSensor {
    public: 
        RangeSensor(){}
        RangeSensor(TwoWire& s);
        void init(const uint8_t gpio_pin, const uint8_t address);
        void startContinuous(uint16_t period);
        bool readContinuous();
        uint16_t read();
        inline void seRangeSensorfset(const float value) {offset_ = value;}
        inline float geRangeSensorfset() {return offset_;}
        inline uint8_t getAddr() {return sensor_.getAddress();}

    public:
        bool get_data_ = false;
        bool vaild_data_ = false;
        float dist_ = 255.0f;
        std::array<float, 3> to_ground_;
        float vaild_distance_ = 200.0f;
        unsigned long last_time_millis_ = 0;

    private:
        VL6180X sensor_;
        float offset_ = 15.0f;
        float prev_dist = 255.0f;
};