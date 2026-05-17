함수에 대한 포인터도 생성할 수 있습니다!  
하지만 함수 포인터 타입의 선언은 조금 더 복잡합니다.

```c++
int (*fptr)(int, int) = nullptr;
```

위 예제에서 함수 포인터 `fptr`는 선언되었고 `nullptr`로 초기화되었습니다.  
`fptr` 포인터는 특정 타입의 함수만 가리킬 수 있습니다:  
즉, 두 개의 `int` 타입 인수를 받고 `int` 타입 결과를 반환하는 함수입니다.

우리는 `fptr`에 일부 실제 함수를 가리키도록 할당할 수 있습니다:

```c++
int plus(int a, int b) {
    return a + b;
}
// ...
fptr = plus;
```

이제 `fptr` 포인터를 사용하여 `plus` 함수를 호출할 수 있습니다:

```c++
// 3을 출력해야 합니다
std::cout << fptr(1, 2) << "\n";
```

이 작업을 완료하기 위해, 배열의 모든 요소에 대해 특정 이진 연산을  
순차적으로 적용한 결과를 계산하는 `fold` 함수를 구현하세요.

```c++
int fold(int* array, size_t size, int init, int (*f)(int, int));
```

`fold` 함수는 다음 인수를 받습니다:  
- `array` – 배열의 시작을 가리키는 포인터,  
- `size` – 배열의 크기,  
- `init` – 초기값,  
- `f` – 적용할 이진 연산을 구현하는 함수에 대한 포인터.

구현 중에는 `array`와 `f`가 null 포인터가 아님을 가정할 수 있습니다.

다음은 `fold`의 사용 예제입니다:

```c++
const int size = 4;
int array[4] = { 1, 2, 3, 4 };
int res = fold(array, size, 0, plus);
// 10을 출력해야 합니다
std::cout << res << "\n";