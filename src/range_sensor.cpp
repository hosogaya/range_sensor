/**
 * @file RangeSensor.cpp
 * @author Hirotaka Hosogaya (hosogaya.hirotaka@b.mbox.nagoya-u.ac.jp)
 * @brief 
 * @version 0.1
 * @date 2021-12-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "range_sensor.h"

RangeSensor::RangeSensor(TwoWire& s){
    s.begin();
    s.setClock(400000);
    sensor_.setBus(&s);
}

void RangeSensor::init(const uint8_t pin, const uint8_t address) {
    pinMode(pin, OUTPUT);delay(20);
    digitalWrite(pin, HIGH);
    delay(20);
    sensor_.setAddress(address); delay(20);
    sensor_.init(); delay(20);
    sensor_.configureDefault(); delay(20);
    // sensor_.setAddress(address); delay(5);
    sensor_.setTimeout(2);
    delay(20);
}

void RangeSensor::startContinuous(uint16_t period){
    // sensor_.writeReg(VL6180X::SYSRANGE__START, 0x01);
    // sensor_.startRangeContinuous(period);
    uint16_t convergence_time = (float)period * 0.9f - 4;
    sensor_.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, convergence_time);
    sensor_.stopContinuous();
    delay(10);
    sensor_.startRangeContinuous(period);
}

bool RangeSensor::readContinuous() {
    dist_ = std::max((sensor_.readRangeContinuousMillimeters() - offset_), 0.0f);
    if (sensor_.timeoutOccurred()) {dist_ = 255.0f; return false;}
    if (dist_ > vaild_distance_) return false; 
    last_time_millis_ = millis();
    return true;
}

uint16_t RangeSensor::read() {
    return static_cast<uint16_t>(sensor_.readRangeSingleMillimeters());
}