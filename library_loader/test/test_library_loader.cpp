/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#include "library_loader.hpp"
#include "test_lib/library_animal.hpp"

#include <string>

#include "test.hpp"
#include "log.hpp"

std::string lib_path_1 = "../library_loader/test_lib/liblibrary_animal_1.dylib";
std::string lib_path_2 = "../library_loader/test_lib/liblibrary_animal_2.dylib";

class FakeBase {};

REGISTER_TEST(test_library_loader) {
    LOG(test_library_loader) << "Testing lib 1 :" << std::endl;
    LibraryLoader lib_loader_1(lib_path_1);
    LOG(test_library_loader)
        << "GetLibraryName : " << lib_loader_1.GetLibraryName() << std::endl;
    LOG(test_library_loader)
        << "HasFunction getLibraryManifest : "
        << lib_loader_1.HasFunction("getLibraryManifest") << std::endl;
    LOG(test_library_loader)
        << "HasClass<BaseAnimal>(Cow) : "
        << lib_loader_1.HasClass<BaseAnimal>("Cow") << std::endl;
    LOG(test_library_loader)
        << "HasClass<BaseAnimal>(Sheep) : "
        << lib_loader_1.HasClass<BaseAnimal>("Sheep") << std::endl;
    LOG(test_library_loader)
        << "HasClass<BaseAnimal>(Pig) : "
        << lib_loader_1.HasClass<BaseAnimal>("Pig") << std::endl;
    LOG(test_library_loader)
        << "HasClass<BaseAnimal>(Duck) : "
        << lib_loader_1.HasClass<BaseAnimal>("Duck") << std::endl;
    LOG(test_library_loader)
        << "HasClass<FakeBase>(Duck) : "
        << lib_loader_1.HasClass<FakeBase>("Duck") << std::endl;
    BaseAnimal* duck = lib_loader_1.CreateInstance<BaseAnimal>("Duck");
    duck->saySomething();
    delete duck;
    BaseAnimal* cow = lib_loader_1.CreateInstance<BaseAnimal>("Cow");
    cow->saySomething();
    delete cow;
    BaseAnimal* sheep = lib_loader_1.CreateInstance<BaseAnimal>("Sheep");
    sheep->saySomething();
    delete sheep;

    LOG(test_library_loader) << "Testing lib 2 :" << std::endl;
    LibraryLoader lib_loader_2(lib_path_2);
    LOG(test_library_loader)
        << "GetLibraryName : " << lib_loader_2.GetLibraryName() << std::endl;
    LOG(test_library_loader)
        << "HasFunction getLibraryManifest : "
        << lib_loader_2.HasFunction("getLibraryManifest") << std::endl;
    LOG(test_library_loader)
        << "HasClass<BaseAnimal>(Cow) : "
        << lib_loader_2.HasClass<BaseAnimal>("Cow") << std::endl;
    LOG(test_library_loader)
        << "HasClass<BaseAnimal>(Pig) : "
        << lib_loader_2.HasClass<BaseAnimal>("Pig") << std::endl;
    BaseAnimal* pig = lib_loader_2.CreateInstance<BaseAnimal>("Pig");
    pig->saySomething();
    delete pig;
    return true;
}

int main() {
    InitFailureHandle();
    RunTests();
    return 0;
}