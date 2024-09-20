#include <iostream>
#include "bigint.h"
using namespace std;
int main() {
    bigint a = 123456789;
    bigint b = 987654321;
    bigint c = a + b;
    bigint d = a - b;
    std::cout << "a + b = " << c << std::endl;
    std::cout << "a - b = " << d << std::endl;
    return 0;
}
