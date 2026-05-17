두 개의 C 스타일 문자열을 연결하는 함수를 구현하십시오:

```c++
char* concat(const char* fst, const char* snd);
```

이 함수는 충분한 메모리를 할당하여 두 문자열의 내용을 복사하고, 결과 문자열의 끝에 널 종료 문자 `\0`을 배치해야 합니다.  
`concat` 함수에는 null이 아닌 포인터만 전달된다고 가정할 수 있습니다.

다음은 `concat` 사용 예제입니다:

```c++
const char* hello = "Hello ";
const char* world = "World!";
const char* helloWorld = concat(hello, world);
// "Hello World!"를 출력해야 합니다.
std::cout << helloWorld << "\n";
```

<div class="hint">

C 표준 라이브러리에는 아래와 같이 유사한 함수가 있습니다:

```c++
char* strcat(char* dest, const char* src);
```

그러나, 구현해야 할 `concat` 함수와는 달리,  
`strcat` 함수는 연결된 문자열을 위한 메모리를 스스로 할당하지 않습니다.  
대신 첫 번째 인자로 전달된 문자열 `dest`가 결과를 저장할 수 있을 만큼  
충분한 메모리가 미리 할당되어 있다고 가정합니다.  
그 후, 결과를 `dest`에 저장하며, 인자로 전달된 원래의 문자열을 변경합니다.

</div>