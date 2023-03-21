#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <functional>
#include <atomic>
#include <vector>
#include <iostream>
#include <assert>

class ThreadPool {
public:
    explicit ThreadPool(size_t threadCount = 8): pool_(std::make_shared<Pool>()) {
        assert(threadCount > 0);
        setThreadCount(threadCount);
    }

    ThreadPool() = default;

    ThreadPool(ThreadPool&&) = default;
    
    ~ThreadPool() {
        if(static_cast<bool>(pool_)) {
            {
                std::lock_guard<std::mutex> locker(pool_->mtx);
                pool_->isClosed = true;
            }
            pool_->cond.notify_all();
        }
    }

    template<class F>
    void AddTask(F&& task) {
        {
            std::lock_guard<std::mutex> locker(pool_->mtx);
            pool_->tasks.emplace(std::forward<F>(task));
        }
        pool_->cond.notify_one();
    }

    void setThreadCount(size_t threadCount) {
        assert(threadCount > 0);
        std::lock_guard<std::mutex> locker(pool_->mtx);
        resizeThreads(threadCount);
    }

private:
    void resizeThreads(size_t targetThreadCount) {
        while (pool_->activeThreads < targetThreadCount) {
            addThread();
        }

        while (pool_->activeThreads + pool_->idleThreads > targetThreadCount) {
            pool_->cond.notify_one();
        }
    }

    void addThread() {
        std::thread([pool = pool_] {
            std::unique_lock<std::mutex> locker(pool->mtx);
            ++(pool->activeThreads);
            while(true) {
                if(!pool->tasks.empty()) {
                    --(pool->idleThreads);
                    auto task = std::move(pool->tasks.front());
                    pool->tasks.pop();
                    locker.unlock();
                    task();
                    locker.lock();
                    ++(pool->idleThreads);
                } 
                else if(pool->isClosed || (pool->activeThreads + pool->idleThreads > pool->targetThreadCount)) {
                    --(pool->activeThreads);
                    break;
                }
                else {
                    ++(pool->idleThreads);
                    pool->cond.wait(locker);
                    --(pool->idleThreads);
                }
            }
        }).detach();
    }

    struct Pool {
        std::mutex mtx;
        std::condition_variable cond;
        std::atomic<size_t> activeThreads{0};
        std::atomic<size_t> idleThreads{0};
        size_t targetThreadCount{0};
        bool isClosed{false};
        std::queue<std::function<void()>> tasks;
    };
    std::shared_ptr<Pool> pool_;
};

#endif //THREADPOOL_H
