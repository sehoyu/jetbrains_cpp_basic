함수 `swap`을 구현하세요. 이 함수는 두 개의 정수 포인터를 받아 그들이 가리키는 값(즉, 내용)을 서로 교환합니다.

```c++
void swap(int* p, int* q);
```

아래는 `swap` 함수 사용 예제입니다.

```c++
int a = 42;
int b = 23;
swap(&a, &b);
// 23 출력
std::cout << a << "\n";
// 42 출력
std::cout << b << "\n";