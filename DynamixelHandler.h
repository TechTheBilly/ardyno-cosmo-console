#ifndef ARDYNO_COSMO_CONSOLE_DYNAMIXELHANDLER_H
#define ARDYNO_COSMO_CONSOLE_DYNAMIXELHANDLER_H

#include <iostream>
#include <DynamixelMotor.h>
#include <vector>
#include <sstream>

int dynamixelHandle(DynamixelID, DynamixelInterface*);

void getArgs(const std::string &s, char delim, std::vector<std::string> &elems);


#endif //ARDYNO_COSMO_CONSOLE_DYNAMIXELHANDLER_H
