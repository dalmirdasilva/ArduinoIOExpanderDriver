/**
 * Arduino - IO Expander Driver
 *
 * IoExpanderMcp23x17.h
 *
 * The MCP23X17 driver functions
 *
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_DRIVER_IO_EXPANDER_MCP23X17_H__
#define __ARDUINO_DRIVER_IO_EXPANDER_MCP23X17_H__ 1

#include <Arduino.h>
#include <Wire.h>
#include <IOExpander.h>

#define pinNormalized(p)    ((p) & 0x0f)
#define isPinValid(p)       ((pinNormalized(p) < 16)

class IOExpanderMCP23X17 {

    /**
     * I2C address.
     */
    unsigned char device;
    
    /**
     * Continuous actions flags.
     */
    unsigned char isContinuousReading;
    unsigned char isContinuousWriting;
    SequentialOperationMode currentSequentialMode;

public:

    enum SequentialOperationMode {
        SEQUENTIAL_OP_ENABLE = 0x00,
        SEQUENTIAL_OP_DISABLE = 0xff,
    };

    enum Register {
        IODIRA = 0x00,
        IODIRB = 0x01,
        IPOLA = 0x02,
        IPOLB = 0x03,
        GPINTENA = 0x04,
        GPINTENB = 0x05,
        DEFVALA = 0x06,
        DEFVALB = 0x07,
        INTCONA = 0x08,
        INTCONB = 0x09,
        IOCON = 0x0a,
        IOCON = 0x0b,
        GPPUA = 0x0c,
        GPPUB = 0x0d,
        INTFA = 0x0e,
        INTFB = 0x0f,
        INTCAPA = 0x10,
        INTCAPB = 0x11,
        GPIOA = 0x12,
        GPIOB = 0x13,
        OLATA = 0x14,
        OLATB = 0x15
    };

    enum Mask {
        IOCON_BANK = 0x80,
        IOCON_MIRROR = 0x40,
        IOCON_SEQOP = 0x20,
        IOCON_DISSLW = 0x10,
        IOCON_HAEN = 0x08,
        IOCON_ODR = 0x04,
        IOCON_INTPOL = 0x02
    };

    void begin(unsigned char device);

    void pinMode(unsigned char pin, bool mode);

    void digitalWrite(unsigned char pin, bool value);

    bool digitalRead(unsigned char pin);

    void setPin(unsigned char pin);

    void clearPin(unsigned char pin);

    void setPullUp(unsigned char pin, bool up);

    void inline setSequentialOperationMode(SequentialOperationMode mode) {
        if (mode != currentSequentialMode) {
            configureRegisterBits(IOCON, IOCON_SEQOP, mode);
        }
    }


    /**
     * Configures a registers inside the camera.
     *
     * @param reg           The register number.
     * @param mask          The mask to be used.
     * @param v             The value to be used.
     */
    void configureRegisterBits(Register reg, unsigned char mask, unsigned char value);

    /**
     * Writes a value to a register.
     *
     * @param reg           The register number.
     * @param v             The value to be used.
     */
    void writeRegister(Register reg, unsigned char value);

    /**
     * Reades a value from a register.
     *
     * @param reg           The register number.
     * @return              The register value.
     */
    unsigned char readRegister(Register reg);

    /**
     * Starts a continuous writing transaction.
     * 
     * @param reg           The register to write on.
     */
    void continuousWriteStart(Register reg);

    /**
     * Writes in a continuous writing transaction.
     * 
     * @param valu          The value to be written.
     */
    void inline continuousWrite(unsigned char value) {
        Wire.write(v);
    }

    /**
     * Stops a continuous writing transaction.
     */
    void inline continuousWriteStop() {
        Wire.endTransmission();
    }

    /**
     * Starts a continuous reading transaction.
     * 
     * @param reg           The register to read from.
     */
    void continuousReadStart(Register reg);

    /**
     * Reades from a continuous reading transaction.
     * 
     * @return value        The value to be written.
     */
    unsigned char continuousRead();

    /**
     * Stops a continuous reading transaction.
     */
    void inline continuousReadStop() {
    }
};

#endif /* __ARDUINO_DRIVER_IO_EXPANDER_MCP23X17_H__ */
