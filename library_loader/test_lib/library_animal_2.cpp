/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#include "library_animal.hpp"

#include "log.hpp"

class Pig : public BaseAnimal {
 public:
    virtual void saySomething();
};

class Dog : public BaseAnimal {
 public:
    virtual void saySomething();
};

void Pig::saySomething() { LINFO(Cow) << "I am a talking pig" << std::endl; }

void Dog::saySomething() { LINFO(Sheep) << "Warf Warf" << std::endl; }

BEGIN_MANIFEST()
EXPORT_CLASS(BaseAnimal, Pig);
EXPORT_CLASS(BaseAnimal, Dog);
END_MANIFEST()