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


class PersonAllocator : public ObjectAllocator
{
public:
    PersonAllocator(int age, const std::string& name) : age_(age), name_(name) {}

    void* allocate() override {
        Person* p = new Person(age_, name_);
        LOG(INFO) << "allocate person object: " << ((void*)p);
        return (void*)p;
    }

    void deallocate(void** p) override {
        LOG(INFO) << "deallocate person object: " << (*(void**)p);
        Person** person = (Person**)p;
        delete *person;
        *person = nullptr;
    }

protected:
    int age_;
    std::string name_;
};

 

class PersonPool 
{
public:
    PersonPool(int age, const std::string& name, int init_num, int inc_num, int max_num) 
        : allocator_(age, name), pool_(init_num, inc_num, max_num, &allocator_) {}

    Person* get() {
        return pool_.get();
    }

    void put(Person** p) {
        pool_.put(p);
    }

protected:
    PersonAllocator allocator_;
    ObjectPool<Person> pool_;
};





}//namespace user
}//namespace duck
















