#include <iostream>
#include <DummyClass.h>

int main() {
    auto *obj = new DummyClass();
    std::cout << "Hello there" << std::endl;
    std::cout << "Return 15 returns: " << obj->Return15() << std::endl;
    delete obj;
	return 15;
}