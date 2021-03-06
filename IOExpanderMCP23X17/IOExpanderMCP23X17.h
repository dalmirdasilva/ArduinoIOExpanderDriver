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

#include <Wire.h>
#include <Arduino.h>
#include <IOExpander.h>
#include <RegisterBasedWiredDevice.h>

#define IO_EX_MAX_PINS                          16

#define MCP23X17_ADDRESS                        0x20

#define IO_EXP_NORMALIZE_PIN(p)                 (((p) >= IO_EX_MAX_PINS ? IO_EX_MAX_PINS - 1 : (((p) < 0) ? 0 : (p)))
#define IO_EXP_IS_PIN_VALID(p)                  ((p) < IO_EX_MAX_IO && (p) >= 0)
#define IO_EXP_PIN_TO_GPIO_REG(p)               ((p) < 8 ? GPIOA : GPIOB)
#define IO_EXP_PIN_TO_IODIR_REG(p)              ((p) < 8 ? IODIRA : IODIRB)
#define IO_EXP_PORT_TO_IODIR_REG(p)             ((p) == PORT_A ? IODIRA : IODIRB)
#define IO_EXP_PIN_TO_GPPU_REG(p)               ((p) < 8 ? GPPUA : GPPUB)
#define IO_EXP_PIN_TO_IPOL_REG(p)               ((p) < 8 ? IPOLA : IPOLB)
#define IO_EXP_PIN_TO_GPINTEN_REG(p)            ((p) < 8 ? GPINTENA : GPINTENB)

class IOExpanderMCP23X17 : public RegisterBasedWiredDevice {

public:

    enum SequentialOperationMode {
        SEQUENTIAL_MODE_ENABLE = 0x00, SEQUENTIAL_MODE_DISABLE = 0xff,
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
//        IOCON = 0x0b,
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

    enum Port {
        PORT_A = GPIOA, PORT_B = GPIOB
    };

    enum Direction {
        OUT = 0x00, IN = 0xff
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

    enum Pin {
        IO_PIN_A0 = 0,
        IO_PIN_A1 = 1,
        IO_PIN_A2 = 2,
        IO_PIN_A3 = 3,
        IO_PIN_A4 = 4,
        IO_PIN_A5 = 5,
        IO_PIN_A6 = 6,
        IO_PIN_A7 = 7,
        IO_PIN_B0 = 8,
        IO_PIN_B1 = 9,
        IO_PIN_B2 = 10,
        IO_PIN_B3 = 11,
        IO_PIN_B4 = 12,
        IO_PIN_B5 = 13,
        IO_PIN_B6 = 14,
        IO_PIN_B7 = 15
    };

    /**
     * Public constructor.
     *
     * @param device            The device address, or just the last 3 pins combination;
     */
    IOExpanderMCP23X17(unsigned char deviceAddress);

    /**
     * Configures the specified pin to behave either as an input or an output.
     *
     * @param pin               The pin number.
     * @param mode              1 means input, 0 means output.
     */
    void pinMode(unsigned char pin, bool mode);

    /**
     * Configures a port to behave either as an input or an output.
     *
     * @param port              The port.
     * @param mode              The mode.
     */
    void portMode(Port port, unsigned char mode);

    /**
     * Write a HIGH or a LOW value to a pin.
     *
     * @param pin               The pin number.
     * @param value             LOW or WRITE.
     */
    void digitalWrite(unsigned char pin, bool value);

    /**
     * Reads the value from a specified pin, either HIGH or LOW.
     *
     * @param pin               The pin number.
     */
    bool digitalRead(unsigned char pin);

    /**
     * Writes value to a port.
     *
     * @param port              The port to write.
     * @param value             The value to write to the port.
     */
    void inline portWrite(Port port, unsigned char value) {
        writeRegister((Register) port, value);
    }

    /**
     * Reads a port.
     *
     * @param port              The port to write.
     * @return                  The value associated with the port.
     */
    unsigned char inline portRead(Port port) {
        return readRegister((Register) port);
    }

    /**
     * Configures the pullup resistor for a given pin.
     *
     * @param pin               The pin number.
     * @param pullUp            0 means with, 1 means witout pullup.
     */
    void setPinPullUp(unsigned char pin, bool pullUp);

    /**
     * Configures the polarity for a given pin.
     *
     * @param pin               The pin number.
     * @param pullUp            0 means normal, 1 means inverted polarity.
     */
    void setPinPolarity(unsigned char pin, bool polarity);

    /**
     * Configures a pin to clear or set the interrupt.
     *
     * @param pin               The pin number.
     * @param pullUp            0 means interrupt disable, 1 means interrupt enable.
     */
    void setPinInterrupt(unsigned char pin, bool interrupt);

    /**
     * Configures the sequential/continuous operation mode.
     *
     * @param mode              The operation mode.
     */
    void setSequentialOperationMode(SequentialOperationMode mode);
};

#endif /* __ARDUINO_DRIVER_IO_EXPANDER_MCP23X17_H__ */
