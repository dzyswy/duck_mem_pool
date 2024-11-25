#pragma once

 
#include "object/object_pool.h"

using namespace duck::object;

namespace duck {
namespace user {

class Person
{
public:
    Person(int age, const std::string& name) : age_(age), name_(name) {}

    void set_age(int age) {
        age_ = age;
    }

    int age() {
        return age_;
    }

protected:
    int age_;
    std::string name_;
};
 


class PersonPool : public ObjectPool<Person>
{
public:
    PersonPool(int age, const std::string& name, int init_num, int inc_num, int max_num) 
        : ObjectPool(init_num, inc_num, max_num), age_(age), name_(name) {}

    Person* allocate() override {
        Person* p = new Person(age_, name_);
        LOG(INFO) << "allocate person object: " << ((void*)p);
        return p;
    }

    void deallocate(Person* p) override {
        LOG(INFO) << "deallocate person object: " << ((void*)p);
        delete p;
    }

    

protected:
    int age_;
    std::string name_;
};



}//namespace user
}//namespace duck
















