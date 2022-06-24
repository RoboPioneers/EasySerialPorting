#include "../EasySerialPorting/Port.hpp"
#include "../EasySerialPorting/Watcher.hpp"
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

    Watcher watcher(port);

    auto func = [](const Watcher::Buffer& data){
        std::cout << "Receive Size:" << data.size() << std::endl;
        std::cout << "Byte 0:" << (unsigned int)data[0] << std::endl;
        std::cout << "Byte 1:" << (unsigned int)data[1] << std::endl;
        std::cout << "Byte 2:" << (unsigned int)data[2] << std::endl;
    };


    auto handler_pointer = std::make_shared<Watcher::Handler>(func);

    watcher.AddHandler(handler_pointer);

    watcher.Start();

    while (true)
        std::this_thread::sleep_for(std::chrono::seconds(1));

    watcher.Stop();
}