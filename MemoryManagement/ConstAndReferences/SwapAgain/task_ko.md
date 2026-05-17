`swap` 함수를 다시 구현하되, 이번에는 매개변수를 참조로 받도록 하세요.

```c++
void swap(int& a, int& b);
```

사용 예시:

```c++
int a = 42;
int b = 23;
swap(a, b);
// 23 출력
std::cout << a << "\n";
// 42 출력
std::cout << b << "\n";