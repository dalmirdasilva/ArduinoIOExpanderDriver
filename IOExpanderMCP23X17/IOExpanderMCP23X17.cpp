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
    currentSequentialOperationMode = SEQUENTIAL_MODE_ENABLE;
    Wire.begin(device);
}

void IOExpanderMCP23X17::pinMode(unsigned char pin, bool mode) {
    Register reg = IO_EXP_PIN_TO_IODIR_REG(pin);
    configureRegisterBits(reg, (1 << (pin % 8)), ((mode) ? 0xff : 0x00));
}

void IOExpanderMCP23X17::portMode(Port port, unsigned char mode) {
    Register reg = IO_EXP_PORT_TO_IODIR_REG(port);
    writeRegister(reg, mode);
}

void IOExpanderMCP23X17::digitalWrite(unsigned char pin, bool value) {
    Register reg = IO_EXP_PIN_TO_GPIO_REG(pin);
    configureRegisterBits(reg, (1 << (pin % 8)), ((value) ? 0xff : 0x00));
}

bool IOExpanderMCP23X17::digitalRead(unsigned char pin) {
    Register reg = IO_EXP_PIN_TO_GPIO_REG(pin);
    return (bool) (readRegister(reg) & (1 << (pin % 8)));
}

void IOExpanderMCP23X17::configureRegisterBits(Register reg, unsigned char mask, unsigned char v) {
    unsigned char n;
    n = readRegister(reg);
    n &= ~(mask);
    n |= v & mask;
    writeRegister(reg, n);
}

void IOExpanderMCP23X17::writeRegister(Register reg, unsigned char v) {
    Wire.beginTransmission(device);
    Wire.write((unsigned char) reg);
    Wire.write(v);
    Wire.endTransmission();
}

unsigned char IOExpanderMCP23X17::readRegister(Register reg) {
    Wire.beginTransmission(device);
    Wire.write((unsigned char) reg);
    Wire.endTransmission(false);
    Wire.requestFrom(device, (unsigned char) 1);
    while (!Wire.available());
    return Wire.read();
}

void IOExpanderMCP23X17::setPinPullUp(unsigned char pin, bool pullUp) {
    Register reg = IO_EXP_PIN_TO_GPPU_REG(pin);
    configureRegisterBits(reg, (1 << (pin % 8)), ((pullUp) ? 0xff : 0x00));
}

void IOExpanderMCP23X17::setPinPolarity(unsigned char pin, bool polarity) {
    Register reg = IO_EXP_PIN_TO_IPOL_REG(pin);
    configureRegisterBits(reg, (1 << (pin % 8)), ((polarity) ? 0xff : 0x00));
}

void IOExpanderMCP23X17::setPinInterrupt(unsigned char pin, bool interrupt) {
    Register reg = IO_EXP_PIN_TO_GPINTEN_REG(pin);
    configureRegisterBits(reg, (1 << (pin % 8)), ((interrupt) ? 0xff : 0x00));
}

void IOExpanderMCP23X17::setSequentialOperationMode(SequentialOperationMode mode) {
    if (mode != currentSequentialOperationMode) {
        currentSequentialOperationMode = mode;
        configureRegisterBits(IOCON, IOCON_SEQOP, mode);
    }
}

void IOExpanderMCP23X17::continuousWriteStart(Register reg) {
    setSequentialOperationMode(SEQUENTIAL_MODE_DISABLE);
    Wire.beginTransmission(device);
    Wire.write((unsigned char) reg);
}

unsigned char IOExpanderMCP23X17::continuousRead() {
    while (!Wire.available());
    return Wire.read();
}

void IOExpanderMCP23X17::continuousReadStart(Register reg, int times) {
    setSequentialOperationMode(SEQUENTIAL_MODE_DISABLE);
    Wire.beginTransmission(device);
    Wire.write((unsigned char) reg);
    Wire.endTransmission(false);
    Wire.requestFrom((int) device, times);
}

#endif /* __ARDUINO_DRIVER_IO_EXPANDER_MCP23X17_CPP__ */
