
#ifndef SERIAL_H
#define SERIAL_H

#define BUFF_SIZE 512
#define POLL_TIMEOUT 100

#include <stdint.h>
#include <cstring>
#include <sys/ioctl.h>


typedef struct serial_s serial_t;


/**
 * Create the serial structure.
 * Convenience method to allocate memory
 * and instantiate objects.
 * @return serial structure.
 */
serial_t* serial_create();

/**
 * Destroy the serial structure
 */
void serial_destroy(serial_t* s);

/**
 * Connect to a serial device.
 * @param s - serial structure.
 * @param device - serial device name.
 * @param baud - baud rate for connection.
 * @return -ve on error, 0 on success.
 */
int serial_connect(serial_t* s, char device[], int baud);

/**
 * Send data.
 * @param s - serial structure.
 * @param data - character array to transmit.
 * @param length - size of the data array.
 */
int serial_send(serial_t* s, uint8_t data[], int length);

/**
 * Send a single character.
 * @param s - serial structure.
 * @param data - single character to be sent.
 */
void serial_put(serial_t* s, uint8_t data);

int serial_readStringNoTimeOut(serial_t* s, char *receivedString,char finalChar,unsigned int maxNbBytes);

char serial_writeString(serial_t* s, const char* receivedString);

/**
 * Determine how much data is available
 * in the serial buffer.
 * @param s - serial structure.
 * @return number of characters available.
 */
int serial_available(serial_t* s);

/**
 * Fetch one char from the serial buffer.
 * @param s - serial structure.
 * @return character. Null if empty.
 */
char serial_get(serial_t* s);

/**
 * Fetch one char from the serial buffer.
 * Blocks until data becomes available.
 * @param s - serial structure.
 * @return character.
 */
char serial_blocking_get(serial_t* s);

/**
 * Clear the serial buffer.
 * @param s - serial structure.
 */
void serial_clear(serial_t* s);

/**
 * Close the serial port.
 * @param s - serial structure.
 * @return value of close().
 */
int serial_close(serial_t* s);

void serial_setDTR(serial_t* s);

void serial_setRTS(serial_t* s);

class Serial
{
public:
	Serial()
	{
		_serial = serial_create();
	}
	~Serial()
	{
		serial_destroy(_serial);
	}

	int Connect(char device[], int baud)
	{
		return serial_connect(_serial, device, baud);
	}
	int Send(uint8_t data[], int length)
	{
		return serial_send(_serial, data, length);
	}
	int readString(char *receivedString,char finalChar,unsigned int maxNbBytes)
	{
		return serial_readStringNoTimeOut(_serial,receivedString,finalChar,maxNbBytes);
	}
	char writeString(const char* data)
	{
		return serial_writeString(_serial, data);
	}
	void Put(uint8_t data)
	{
		return serial_put(_serial, data);
	}
	int Available()
	{
		return serial_available(_serial);
	}
	char Get()
	{
		return serial_get(_serial);
	}
	char Blocking_get()
	{
		return serial_blocking_get(_serial);
	}
	void Clear()
	{
		return serial_clear(_serial);
	}
	int Disconnect()
	{
		return serial_close(_serial);
	}
	void setRTS()
	{
		return serial_setRTS(_serial);
	}
	void setDTR()
	{
		return serial_setDTR(_serial);
	}
private:
	serial_t* _serial;
};


#endif
