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

void Duck::saySomething() { LINFO(Duck) << "Quack"; }

void Cow::saySomething() { LINFO(Cow) << "Moooo"; }

void Sheep::saySomething() { LINFO(Sheep) << "Baaah"; }

BEGIN_MANIFEST()
EXPORT_CLASS(BaseAnimal, Duck);
EXPORT_CLASS(BaseAnimal, Cow);
EXPORT_CLASS(BaseAnimal, Sheep);
END_MANIFEST()