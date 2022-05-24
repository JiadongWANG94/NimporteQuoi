/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#include "library_animal.hpp"

#include "log.hpp"

class Duck : public BaseAnimal {
 public:
    virtual void saySomething();
};

class Cow : public BaseAnimal {
 public:
    virtual void saySomething();
};

class Sheep : public BaseAnimal {
 public:
    virtual void saySomething();
};

void Duck::saySomething() { LINFO(Duck) << "Quack" << std::endl; }

void Cow::saySomething() { LINFO(Cow) << "Moooo" << std::endl; }

void Sheep::saySomething() { LINFO(Sheep) << "Baaah" << std::endl; }

BEGIN_MANIFEST()
EXPORT_CLASS(BaseAnimal, Duck);
EXPORT_CLASS(BaseAnimal, Cow);
EXPORT_CLASS(BaseAnimal, Sheep);
END_MANIFEST()