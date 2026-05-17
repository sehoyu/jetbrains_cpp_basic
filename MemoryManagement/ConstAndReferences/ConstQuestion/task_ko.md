여러 변수 선언을 아래에 고려하세요:

```c++
int a = 0;
const int b = 0;
int* p = &a;
const int* q = &b;
const int* const r = &b; 
```

오류 없이 성공적으로 컴파일할 수 있는 
유효한 할당 문을 선택하세요:

```c++
// (1)
a = 1;

// (2)
b = 2;

// (3)
p = q;

// (4)
q = p;

// (5)
*q = 5;

// (6)
r = q;