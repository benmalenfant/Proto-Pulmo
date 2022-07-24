#include <errno.h> // Error integer and strerror() function
#include <fcntl.h> // Contains file controls like O_RDWR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <iostream>


#define SERIAL_PORT "/dev/ttyACM0"

void init_serial();
