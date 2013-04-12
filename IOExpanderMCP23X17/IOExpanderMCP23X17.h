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

class IOExpanderMCP23X17 {

    /**
     * I2C address.
     */
   unsigned char address;



public:

   IOExpanderMCP23X17(unsigned char address);



};

#endif /* __ARDUINO_DRIVER_IO_EXPANDER_MCP23X17_H__ */
