여러 변수의 선언을 아래에서 확인하세요:

```c++
int a = 0;
double e = 2.71828;
int* p = (int*) malloc(8 * sizeof(int));
```

컴파일 오류 없이 성공적으로 실행될 수 있는 유효한 타입 변환 문장을 선택하세요:

```c++
// (1)
double x = static_cast<double>(a);

// (2)
int b = e;

// (3)
int b = (int) e;

// (4)
char* q = static_cast<char*>(p);

// (5)
char* r = reinterpret_cast<char*>(p);

// (6)
std::intptr_t c = reinterpret_cast<std::intptr_t>(p);
```

<div class="hint">

`std::intptr_t`는 포인터 타입의 크기와 동일한 크기를 가지는 것이 보장된 특수한 서명된 정수 타입입니다.

</div>