#include "../EasySerialPorting/Port.hpp"
#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char** argv)
{
    using namespace Easy;

    Port port("/dev/ttyUSB0");
    std::vector<unsigned char> data;
    port.Read(data);
    std::cout << data.size() << std::endl;
    std::cout << (unsigned int)data[0] << std::endl;
    std::cout << (unsigned int)data[1] << std::endl;
    std::cout << (unsigned int)data[2] << std::endl;
}