/**
 * Arduino - IO Expander Driver
 *
 * IoExpanderMcp23x17.cpp
 *
 * The MCP23X17 driver functions
 *
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_DRIVER_IO_EXPANDER_MCP23X17_CPP__
#define __ARDUINO_DRIVER_IO_EXPANDER_MCP23X17_CPP__ 1

#include "IOExpanderMCP23X17.h"

void IOExpanderMCP23X17::begin(unsigned char device) {
    this->device = 0x20 | (device & 0x07);
    this->isContinuousReading = 0;
    this->isContinuousWriting = 0;
    this->isContinuousEnabled = 0;
    Wire.begin(device);
}

void IOExpanderMCP23X17::pinMode(unsigned char pin, bool mode) {

}

void IOExpanderMCP23X17::digitalWrite(unsigned char pin, bool value) {

}

bool IOExpanderMCP23X17::digitalRead(unsigned char pin) {

}

void IOExpanderMCP23X17::setPin(unsigned char pin) {

}

void IOExpanderMCP23X17::clearPin(unsigned char pin) {

}

void IOExpanderMCP23X17::configureRegisterBits(Register reg, Mask mask,
        unsigned char v) {
    unsigned char n;
    n = readRegister(reg);
    n &= ~((unsigned char) mask);
    n |= v & ((unsigned char) mask);
    writeRegister(reg, n);
}

void IOExpanderMCP23X17::writeRegister(Register reg, unsigned char v) {
    Wire.beginTransmission(address);
    Wire.write((unsigned char) reg);
    Wire.write(v);
    Wire.endTransmission();
}

unsigned char IOExpanderMCP23X17::readRegister(Register reg) {
    Wire.beginTransmission(address);
    Wire.write((unsigned char) reg);
    Wire.endTransmission(false);
    Wire.requestFrom(address, (unsigned char) 1);
    while (!Wire.available()) {
        delay(1);
    }
    return Wire.read();
}

void IOExpanderMCP23X17::continuousWriteStart(Register reg) {
    setSequentialOperationMode(SEQUENTIAL_OP_DISABLE);
    Wire.beginTransmission(address);
    Wire.write((unsigned char) reg);
}

unsigned char IOExpanderMCP23X17::continuousRead() {
    while (!Wire.available());
    return Wire.read();
}


void IOExpanderMCP23X17::continuousReadStart(Register reg, int len) {
    Wire.beginTransmission(address);
    Wire.write((unsigned char) reg);
    Wire.endTransmission(false);
    Wire.requestFrom(address, len);
}

#endif /* __ARDUINO_DRIVER_IO_EXPANDER_MCP23X17_CPP__ */
