#include "../EasySerialPorting/Port.hpp"
#include <gtest/gtest.h>

int main(int argc, char** argv)
{
    using namespace Easy;

    Port port("/dev/ttyUSB1");
    std::vector<unsigned char> data;
    data.resize(3);
    data[0] = (unsigned char)11;
    data[1] = (unsigned char)12;
    data[2] = (unsigned char)13;
    port.Write(data);
}