주어진 C 문자열을 특정 구분자 문자들로 나누는 함수를 구현하세요:

```c++
size_t split(const char* str, const char* seps, char**& res);
```

다음은 이 함수의 사용 예제입니다:

```c++
const char* str = "Hello, World!";
const char** res = nullptr;
size_t size = split(str, " ,!", res);
// 2가 출력되어야 합니다
std::cout << size << "\n";
// "Hello"가 출력되어야 합니다
std::cout << res[0] << "\n";
// "World"가 출력되어야 합니다
std::cout << res[1] << "\n";
```

이 함수는 세 개의 인자를 받습니다. 첫 번째 인자인 `str`은 분할되어야 할 문자열입니다.  
두 번째 인자인 `seps`는 구분자 문자들로 이루어진 문자열입니다.  
세 번째 인자인 `res`는 결과 문자열 배열의 포인터에 대한 참조입니다. 이 배열의 포인터는 함수가 저장해야 합니다.  
마지막으로, 함수는 결과 배열의 크기(즉, 나뉜 하위 문자열의 개수)를 반환해야 합니다.

만약 원본 문자열에 여러 개의 연속된 구분자 문자가 포함되어 있다면,  
이들을 모두 건너뛰어야 합니다. 즉, 연속된 구분자 문자들 사이에 발생하는 빈 문자열은  
결과에 추가되지 않아야 합니다.

하위 문자열이 없는 경우 함수는 `0`을 반환하고,   
`res` 인자에 `nullptr`을 저장해야 합니다.

그 외의 경우, 함수는 결과 배열과 모든 하위 문자열을 저장할 충분한 메모리를 할당해야 합니다.  
각 하위 문자열은 개별적으로 할당되어야 합니다.  
위의 예제로 돌아가서, 사용자는 아래 방식으로 함수가 할당한 메모리를 해제할 수 있어야 합니다:

```c++
free(res[0]);
free(res[1]);
free(res);
```

<div class="hint">

`split`을 구현하기 위해, 표준 라이브러리의 다음 함수들이 유용할 수 있습니다:

- [`strpbrk`](https://en.cppreference.com/w/cpp/string/byte/strpbrk) --- 
      주어진 문자열에서 구분자 문자의 첫 번째 발생 위치를 찾습니다;
- [`strspn`](https://en.cppreference.com/w/cpp/string/byte/strspn) --- 
      주어진 문자열에서 구분자 문자로만 이루어진 부분 문자열의 길이를 반환합니다;
- [https://en.cppreference.com/w/cpp/string/byte/strncpy](https://en.cppreference.com/w/cpp/string/byte/strncpy) ---
      한 문자열에서 다른 문자열로 일정 개수의 문자를 복사합니다.

```c++
const char* str = "Hello, World!";
// ", World!"를 반환합니다 --- (str + 5) 포인터
const char* substr = strpbrk(str, " ,!");
// 2를 반환합니다
strspn(substr, " ,!"); 
// 부분 문자열 "Hello"를 복사합니다
char hello[6] = { 0 };
strncpy(hello, str, 5);
```

</div>