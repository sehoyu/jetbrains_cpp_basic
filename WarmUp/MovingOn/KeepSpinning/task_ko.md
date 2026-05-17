`for` 루프 문 외에도 C++에는  
`while` [루프 문](https://en.cppreference.com/w/cpp/language/while)  
및 `do-while` [루프 문](https://en.cppreference.com/w/cpp/language/do)도 제공됩니다.

```c++
int x = 3;
while (x > 0) {
    std::cout << x << " ";
    --x;
}
std::cout << "...";
// "3 2 1 ..." 출력
```

`while` 루프는 조건식(condition expression)과 루프 본문(loop body)으로 구성됩니다.  
`while` 루프 문 본문은 조건식이 `true`로 평가되는 동안 실행됩니다.  
조건이 처음부터 `false`로 평가되면 본문이 한 번도 실행되지 않을 수 있음을 유의하세요.  
본문을 최소 한 번 이상 실행해야 한다면 `do-while` 루프 문을 사용하세요.

```c++
int x = 3;
do {
    std::cout << x << " ";
    --x;
} while (x > 0);
std::cout << "...";
// "3 2 1 ..." 출력
```

다음은 사용해야 할 루프 유형에 대한 일반적인 권장 사항입니다.

* 배열 또는 기타 요소 컬렉션을 반복(iterate)해야 한다면 `for` 루프를 선호하세요.  
* 특정 조건이 충족될 때까지 코드 블록을 반복 실행해야 한다면 `while` 루프를 선호하세요.  
  추가로 이 코드 블록이 최소 한 번 이상 실행되도록 보장해야 한다면 `do-while` 루프를 사용하세요.  

예를 들어, `while` 또는 `do-while` 루프는 대화형 애플리케이션에서  
이른바 애플리케이션의 "메인 루프(main loop)"를 구현하는 데 흔히 사용됩니다.  
이 경우 루프의 각 반복(iteration)마다 프로그램은 사용자로부터 입력을 읽고  
사용자가 애플리케이션을 종료하도록 신호를 보낼 때까지 사용자 제공 데이터를 처리하는  
함수를 호출합니다.

```c++
// DoNothing 애플리케이션.
// 사용자 입력을 읽고 아무것도 수행하지 않습니다.
// 단, 종료를 위해 "exit" 문자열을 전달하면 애플리케이션이 종료됩니다.
std::string input;
do {
    std::cin >> input;
} while (input != "exit");