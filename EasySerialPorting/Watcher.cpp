#include "Watcher.hpp"

namespace Easy
{
    Watcher::Watcher(Port &device) : Device(device), WorkerFlag(false)
    {}

    Watcher::~Watcher()
    {
        if (IsRunning())
            Stop();
    }

    void Watcher::AddHandler(const std::shared_ptr<Handler>& handler)
    {
        Handlers.emplace(handler);
    }

    void Watcher::RemoveHandler(const std::shared_ptr<Handler>& handler)
    {
        Handlers.erase(handler);
    }

    void Watcher::Start()
    {
        if (WorkerFlag)
            return;
        // 设置工作线程旗标
        WorkerFlag = true;
        // 启动工作线程
        Worker = std::make_unique<std::thread>([this](){
            while (this->WorkerFlag.load())
            {
                std::vector<unsigned char> data;
                // 阻塞直到读取到完整的包
                try
                {
                    this->Device.Read(data);
                } catch(boost::wrapexcept<boost::system::system_error>& error)
                {
                    // 长时间未收到数据时会超时返回，异常内容为"read: End of file"
                    continue;
                }
                // 触发事件
                for(const auto& handler : this->Handlers)
                {
                    (*handler)(data);
                }
            }
        });
    }

    void Watcher::Stop()
    {
        WorkerFlag = false;
        if (Worker)
        {
            Worker->join();
            Worker = nullptr;
        }
    }
}