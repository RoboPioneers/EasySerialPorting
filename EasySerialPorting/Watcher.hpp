#pragma once
#include "Port.hpp"
#include <thread>
#include <atomic>
#include <memory>
#include <list>
#include <functional>
#include <unordered_set>

namespace Easy
{
    class Watcher
    {
    public:
        /// 绑定一个设备
        explicit Watcher(Port& device);

        /// 析构时确保停止
        virtual ~Watcher();

        using Buffer = std::vector<unsigned char>;
        using Handler = std::function<void(const Buffer&)>;

    protected:
        /// 串口设备
        Port& Device;

        /// 后台工作线程
        std::unique_ptr<std::thread> Worker;
        /// 后台工作标志
        std::atomic_bool WorkerFlag;

        /// 事件处理器列表
        std::unordered_set<std::shared_ptr<Handler>> Handlers;

    public:
        /// 添加一个事件处理器
        void AddHandler(const std::shared_ptr<Handler>& handler);

        /// 移除一个事件处理器
        void RemoveHandler(const std::shared_ptr<Handler>& handler);

        /**
         * @brief 启动监听器
         * @details 若监听器已经启动，该方法不会进行任何操作
         */
        void Start();

        /**
         * @brief 停止监听器
         * @details 该方法将在监听线程终止后返回
         */
        void Stop();

        /// 判断监听器是否正在运作
        bool IsRunning() const
        {
            return WorkerFlag.load();
        }
    };
}