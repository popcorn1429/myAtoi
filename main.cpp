
#include <iostream>
#include "simple_atoi.h"
using namespace std;

int main() {
    string str1{ "2147483648" };


    cout << str1 << " -> " << simple_convert(str1) << endl;
    
    system("pause");
    return 0;
}

