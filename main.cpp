#include "DynamixelHandler.h"

char * serialPort;

void getArgs(const std::string&, char, std::vector<std::string>&);

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        std::cout << "USAGE : " << argv[0] << " <serialPort>" << std::endl;
        return 1;
    }

    serialPort = argv[1];
    DynamixelInterface *interface=createSerialInterface(serialPort);
    interface->begin(9600);

    char orderC[100];
    std::string order = "";
    std::vector<std::string> args = std::vector<std::string>();

    while(order.compare("exit"))
    {
        std::cout << std::endl << "CosmOS Dynamixel Console : ";
        std::cin.getline(orderC, sizeof(orderC));
        order = std::string(orderC);
        std::cout << std::endl;
        args.clear();
        getArgs(order, ' ', args);

        if(!args[0].compare("setid"))
        {
            if(args.size() != 2)
            {
                std::cout << "USAGE : setid <id> ; Sends a broadcast packet to set the id" << std::endl;
                continue;
            }

            int id;
            try
            {
                id = std::stoi(args[1]);
            }
            catch (std::exception const &e)
            {
                std::cout << "BAD ID ; id must be between 0 and 253" << std::endl;
                continue;
            }

            if(id < 0 || id > 253)
            {
                std::cout << "BAD ID ; id must be between 0 and 253" << std::endl;
                continue;
            }

            DynamixelMotor broadcaster = DynamixelMotor(*interface, 0xFE);
            broadcaster.setID((uint8_t)id);
            continue;
        }

        else if(!args[0].compare("select"))
        {
            if(args.size() != 2)
            {
                std::cout << "USAGE : select <id> ; Selects the specified device" << std::endl;
                continue;
            }

            int id;
            try
            {
                id = std::stoi(args[1]);
            }
            catch (std::exception const &e)
            {
                std::cout << "BAD ID ; id must be between 0 and 254 (254 is broadcast)" << std::endl;
                continue;
            }

            if(id < 0 || id > 254)
            {
                std::cout << "BAD ID ; id must be between 0 and 254 (254 is broadcast)" << std::endl;
                continue;
            }

            if(dynamixelHandle((DynamixelID)id, interface) == 1)
            {
                return 1;
            }
            continue;
        }

        else
        {
            std::cout << "No such command" << std::endl;
        }


    }

    delete(interface);
    return 0;
}

