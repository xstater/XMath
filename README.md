# XMath
This is a header-only linear algebra library.

### a simple example
```
#include <iostream>
#include "XMath.h"

using namespace std;
using namespace xmath;

int main(){
    auto v1 = Vector4f{1,2,3,1};//a 4d float COL vector
    auto t = Vector3f{1,1,1}.translate();//construct a Translation matrix
    v1 = t % v1;//apply to v1
    cout << v1 << endl;//[2,3,4,1]
    return 0;
}
```
