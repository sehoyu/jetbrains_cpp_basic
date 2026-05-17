C 스타일 캐스트와 관련된 잠재적 위험을 완화하기 위해  
C++는 추가적인 안전 검사를 구현하는 여러 캐스팅 기본 요소를 도입했습니다.  
C 스타일 형 변환 연산자와 달리, 각 C++ 캐스트 연산자는  
자신만의 사용 사례를 가지고 있으며, 이를 사용하면  
프로그래머의 의도를 코드에서 명확히 전달할 수 있습니다.

C++에는 네 가지 형 변환 연산자가 있습니다:

- `static_cast`
- `reinterpret_cast`
- `const_cast`
- `dynamic_cast`

이번 강의에서는 첫 두 가지를 다룰 예정이며,  
마지막 두 연산자는 이 과정 후반부에서 논의할 예정입니다.

`static_cast` [연산자](https://en.cppreference.com/w/cpp/language/static_cast)는  
_암시적 및 사용자 정의 타입 변환_ 시퀀스를 수행할 수 있으며,  
수행된 변환의 안전성을 검사하고 컴파일 시 오류를 보고합니다.  
예를 들어, `static_cast`는 `double`을 `int`로 변환하는 데 사용할 수 있습니다.

```c++
double pi = 3.14;
int a = static_cast<int>(pi);
// 출력: 3
std::cout << a << "\n";
```

C++에서는 변환이 암시적으로 수행될 수 있는 경우라도  
`static_cast`를 사용하는 것이 일반적으로 권장됩니다  
(위 코드 스니펫의 경우처럼).  
`static_cast`의 명시성 덕분에 코드베이스에서  
모든 타입 변환을 쉽게 검색할 수 있으며,  
잠재적으로 에러가 발생할 가능성이 있는 코드 조각을 명확히 표시할 수 있습니다  
(타입 변환은 항상 까다롭고 오류가 발생하기 쉬운 작업입니다).

_사용자 정의_ 변환의 예는 사용자 정의 `enum`과 `int` 간의 변환입니다.

```c++
enum Color { RED, GREEN, BLUE };
int red_code    = static_cast<int>(RED);
int green_code  = static_cast<int>(GREEN);
int blue_code   = static_cast<int>(BLUE);
// 출력: 0, 1, 2
std::cout << red_code << ", " << green_code << ", " << blue_code << "\n";
```

우리는 과정 전반에 걸쳐 사용자 정의 변환에 대한 더 많은 예제를 다룰 것입니다.

모든 타입 변환을 `static_cast`로 수행할 수 있는 것은 아닙니다.  
예를 들어, 다음 예시에서와 같이 포인터 타입의  
포인터 대상을 변환하는 데는 사용할 수 없습니다:

```c++
void*  q = malloc(2 * sizeof(int));
// void*에서 int*로 캐스팅은 가능합니다
int*  qi = static_cast<int*> (q);
// void가 아닌 포인터 타입 간 변환은 금지되며,
// 다음 줄은 컴파일 오류를 발생시킵니다
char* qc = static_cast<char*>(qi);
```

다른 연산자인 `reinterpret_cast`  
[형 변환 연산자](https://en.cppreference.com/w/cpp/language/reinterpret_cast)는  
바로 이러한 시나리오를 위해 설계되었습니다.

```c++
// void가 아닌 포인터 타입 간 변환은
// reinterpret_cast를 사용하면 가능합니다
char* qr = reinterpret_cast<char*>(qi);
```

`reinterpret_cast`는 포인터 대상 값을 변경하지 않고  
특정 메모리 영역에 대한 "다른 시각"을 제공합니다.  
즉, 포인터 대상 메모리 영역의 타입을 재해석할 수 있도록 합니다.

하지만 C 스타일 캐스트와 마찬가지로, `reinterpret_cast`는  
어떠한 안전 검사도 수행하지 않습니다.  
따라서 미정의 동작이 발생할 수 있는 영역에 쉽게 발을 들여놓을 수 있습니다.

```c++
void* r = malloc(2);
int* ri = reinterpret_cast<int*>(r);
// 미정의 동작이 발생합니다, 다시 한 번 !!!
ri[0] = 42;
```

`static_cast`의 경우처럼 `reinterpret_cast`를 사용하는 것은  
잠재적으로 위험한 모든 타입 캐스트를 명시적으로 표시하고,  
코드 작성자의 의도를 명확히 전달할 수 있는 방법을 제공합니다.