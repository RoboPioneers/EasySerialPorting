#include "Port.hpp"
#include "CRCTool.hpp"

namespace Easy
{
    /// 构造函数
    Port::Port(std::string path) : Path(std::move(path)), Context(), Device(Context)
    {
        using namespace boost::asio;

        // 开启串口
        Device.open(Path);

        // 配置串口设备
        Device.set_option(serial_port_base::baud_rate(115200));
        Device.set_option(serial_port_base::character_size(8));
        Device.set_option(serial_port_base::flow_control(serial_port::flow_control::none));
        Device.set_option(serial_port_base::parity(serial_port::parity::none));
        Device.set_option(serial_port_base::stop_bits(serial_port::stop_bits::one));
    }

    /// 析构时关闭对象
    Port::~Port()
    {
        if (Device.is_open())
        {
            Device.close();
        }
    }

    /// 将内容写入到设备
    void Port::Write(const std::vector<unsigned char> &content)
    {
        std::vector<unsigned char> head, tail;
        head.resize(3);
        head[0] = 0xBE;
        *(unsigned short*)&head[1] = content.size();
        tail.resize(2);
        tail[0] = Utilities::CRCTool::GetCRC8CheckSum(content.data(), content.size());
        tail[1] = 0xED;

        boost::asio::write(Device, boost::asio::buffer(head.data(), head.size()));
        boost::asio::write(Device, boost::asio::buffer(content.data(), content.size()));
        boost::asio::write(Device, boost::asio::buffer(tail.data(), tail.size()));
    }

    /// 从设备中读取内容
    bool Port::Read(std::vector<unsigned char> &bytes)
    {
        std::vector<unsigned char> information;
        information.resize(3);
        boost::asio::read(Device, boost::asio::buffer(information.data(), 3));
        auto length = *(unsigned short*)&information[1];
        bytes.resize(length);
        boost::asio::read(Device, boost::asio::buffer(bytes.data(), bytes.size()));
        boost::asio::read(Device, boost::asio::buffer(information.data(), 2));
        if (information[0] != 0xED)
            return false;
        auto check = Utilities::CRCTool::GetCRC8CheckSum(bytes.data(), bytes.size());
        if (check != information[1])
            return false;
        return true;
    }
}