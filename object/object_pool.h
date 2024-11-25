#pragma once

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <list>
#include <vector>
#include <memory>
#include <glog/logging.h>


namespace duck {
namespace object {

 


template<typename T>
class ObjectPool
{
public:
    ObjectPool(int init_num, int inc_num, int max_num) : init_num_(init_num), inc_num_(inc_num), max_num_(max_num) {

        alloc_block(init_num_);
    }

    ~ObjectPool() {
        release();
    }

    T* get() {
        std::unique_lock<std::mutex> lock(mutex_);

        while (free_list_.empty()) {

            lock.unlock();

            alloc_block(inc_num_);
        }
 

        T* p = free_list_.front();
        free_list_.pop_front();
        used_list_.push_back(p);

        return p;
    }

    void put(T* p) {

        std::unique_lock<std::mutex> lock(mutex_);

        for (auto it = used_list_.begin(); it != used_list_.end(); it++) {
            if ((*it) == p) {
                free_list_.push_back(p);
                used_list_.erase(it);
            }
        }
    }

    virtual T* allocate() = 0;
    virtual void deallocate(T* p) = 0;

    void alloc_block(int num) {
        std::unique_lock<std::mutex> lock(mutex_);

        for (int i = 0; i < num; i++) {
            T* p = allocate();
            obj_vec_.push_back(p);
            free_list_.push_back(p);
        }

        if (obj_vec_.size() > max_num_) {
            std::cout << "object pool alloc too much object!" << std::endl;
        }
    }

    void release() {
        for (size_t i = 0; i < obj_vec_.size(); i++) {
            deallocate(obj_vec_[i]);
        }
    }

protected: 

    int init_num_;
    int inc_num_;
    int max_num_;

    std::mutex mutex_;
    std::vector<T*> obj_vec_;
    std::list<T*> free_list_;
    std::list<T*> used_list_;
};


}//namespace object
}//namespace duck
















