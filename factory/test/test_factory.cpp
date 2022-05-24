#include "factory.hpp"

#include <memory>
#include <functional>
#include "test.hpp"

class TestBase {
 public:
    virtual ~TestBase() {}
    virtual bool Init() { return true; }
    virtual bool Process() { return true; }
};

class TestDerived1 : public TestBase {
 public:
    TestDerived1() { LINFO(test_factory) << "Construct derived1" << std::endl; }
    virtual ~TestDerived1() {
        LINFO(test_factory) << "Destruct derived1" << std::endl;
    }
    virtual bool Init() override {
        LINFO(test_factory) << "Init derived1" << std::endl;
        return true;
    }
    virtual bool Process() override {
        LINFO(test_factory) << "Process derived1" << std::endl;
        return true;
    }
};

class TestDerived2 : public TestBase {
 public:
    TestDerived2() { LINFO(test_factory) << "Construct derived2" << std::endl; }
    virtual ~TestDerived2() {
        LINFO(test_factory) << "Destruct derived2" << std::endl;
    }
    virtual bool Init() override {
        LINFO(test_factory) << "Init derived2" << std::endl;
        return true;
    }
    virtual bool Process() override {
        LINFO(test_factory) << "Process derived2" << std::endl;
        return true;
    }
};

REGISTER_PRODUCTION_CLASS_IMPL_1(TestDerived1, TestBase);

REGISTER_PRODUCTION_CLASS_IMPL_2(TestDerived2, TestBase);

REGISTER_TEST(test_factory) {
    GetFactory<TestBase>()->CreateInstance("TestDerived1")->Init();
    GetFactory<TestBase>()->CreateInstance("TestDerived2")->Process();
    return true;
}

int main() {
    InitFailureHandle();
    RunTests();
    return 0;
}