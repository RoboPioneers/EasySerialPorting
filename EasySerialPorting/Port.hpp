#pragma once
#include <string>
#include <vector>
#include <boost/asio.hpp>

namespace Easy
{
    class Port
    {
    public:
        /// @brief 构造一个串口对象并绑定设备地址
        /// @param path 设备地址
        explicit Port(std::string path);
        /// 析构时关闭串口对象
        virtual ~Port();

    protected:
        /// 设备路径
        const std::string Path;

        /// 上下文对象
        boost::asio::io_context Context;
        /// 串口设备对象
        boost::asio::serial_port Device;

    public:
        /**
         * @brief 将字节写入到串口
         * @param bytes 需要写入的字节，全部都会被写入到设备中
         * @details 该函数将自动添加包头和包尾。
         */
        void Write(const std::vector<unsigned char>& bytes);

        /**
         * @brief 从设备中读取数据
         * @param bytes 用于存储读取的字节的容器
         * @details 将自动去除包头包尾
         */
        bool Read(std::vector<unsigned char>& bytes);
    };
}
