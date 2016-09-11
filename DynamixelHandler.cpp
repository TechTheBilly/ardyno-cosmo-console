#include "DynamixelHandler.h"

int dynamixelHandle(DynamixelID id, DynamixelInterface* interface)
{

    DynamixelMotor device = DynamixelMotor(*interface, id);

    char orderC[100];
    std::string order = "";
    std::vector<std::string> args = std::vector<std::string>();

    while(order.compare("exit"))
    {
        std::cout << std::endl << "CosmOS Dynamixel Console <Device " << (int)id << "> : ";
        std::cin.getline(orderC, sizeof(orderC));
        order = std::string(orderC);
        std::cout << std::endl;
        args.clear();
        getArgs(order, ' ', args);

        if(!args[0].compare("setpos"))
        {
            if(args.size() != 2)
            {
                std::cout << "USAGE : setpos <position> ; Sets the specified angular position [0;1023] " << std::endl;
                continue;
            }

            int goal;
            try
            {
                goal = std::stoi(args[1]);
            }
            catch (std::exception const &e)
            {
                std::cout << "BAD POSITION ; position must be between 0 and 1023" << std::endl;
                continue;
            }

            if(goal < 0 || goal > 0x3ff)
            {
                std::cout << "BAD POSITION ; position must be between 0 and 1023" << std::endl;
                continue;
            }

            device.goalPosition((uint16_t) goal);
            continue;
        }

        else if(!args[0].compare("setled"))
        {
            if(args.size() != 2)
            {
                std::cout << "USAGE : setled <on/off> ; Sets the led state" << std::endl;
                continue;
            }

            if(!args[1].compare("on"))
            {
                device.write(0x19, true);
            }
            else if(!args[1].compare("off"))
            {
                device.write(0x19, false);
            }
            else
            {
                std::cout << "BAD STATE : should be 'on' or 'off' " << std::endl;
            }
            continue;
        }

        else
        {
            std::cout << "No such command" << std::endl;
        }

    }

    return 0;
}


void getArgs(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss;
    ss.str(s);
    std::string item;

    while (getline(ss, item, delim)) {
        std::cout << item << std::endl;
        elems.push_back(item);
    }
}