C++에서는 기본적으로 인수가 _값에 의한 전달_ 방식으로 함수에 전달됩니다.  
프로그램이 인수를 사용하여 함수 호출을 수행할 때,  
이 인수들은 복사되어 함수로 전달됩니다.  
따라서 함수의 본문 실행 중에 인수가 변경되더라도,  
호출하는 측에서는 이러한 변경 사항을 알 수 없습니다.  
왜냐하면 호출 측에서는 원본만 가지고 있기 때문입니다.

예를 들어, 다음과 같은 서명을 가진 `swap` 함수 버전을 고려해 보세요:

```c++
void swap(int a, int b) {
    int c = a;
    a = b;
    b = c;
}
```

이 함수는 기대와는 달리 실제로 변수의 내용을 교환하지 않습니다.

```c++
int a = 5;
int b = 7;
swap(a, b);
// 출력: 5
std::cout << a << "\n";
// 출력: 7
std::cout << b << "\n";
```

이는 인수가 값에 의한 전달로 복사되기 때문입니다.

<div class="hint">

이 시점에서 `swap` 함수를 올바르게 구현하는 방법이  
포인터 또는 참조를 사용하는 것이라는 점을 이미 알고 있을 것입니다.  
잠시 후 이 내용으로 다시 돌아오겠습니다.

</div>

또한, 함수가 크고 메모리 집약적인 구조체를 인수로 받아야 할 경우,  
인수 복사는 바람직하지 않을 수 있습니다.

다음 구조체를 고려해 보세요:

```c++
// 왼쪽 상단 및 오른쪽 하단 모서리 점으로 정의된 사각형
struct Rectangle {
    Point2D topLeft;
    Point2D botRight;
};
```

`float`형이 4바이트를 차지한다고 가정하면,  
`Rectangle` 구조체는 4 * 4 = 16바이트를 차지합니다.  

```c++
// 출력: 16
std::cout << sizeof(Rectangle) << "\n";
```

따라서, `Rectangle` 구조체를 값에 의한 전달로 사용하는 함수는  
각 호출 시마다 16바이트를 복사하게 될 것입니다!

게다가 함수가 사각형을 즉석에서 수정해야 한다면,  
복사된 버전만 변경되기 때문에 실제 값을 수정할 수 없습니다!

이러한 제한 사항을 극복하기 위해, C++에서는 인수를 _참조에 의한 전달_로 전달할 수 있습니다.  
참조는 메모리 내 변수의 주소일 뿐이므로,  
변수 유형 크기에 상관없이 4바이트 또는 8바이트만 차지합니다.  
또한, 인수가 참조에 의해 전달되면 함수는 실제로 이를 수정할 수 있습니다.

예를 들어, 사각형을 확장(scale)하기 위한 함수를 정의할 수 있습니다:

```c++
void scale(Rectangle& rect, float factor) {
    float width = rect.botRight.x - rect.topLeft.x;
    float height = rect.topLeft.y - rect.botRight.y;
    rect.botRight.x = rect.topLeft.x + width * factor;
    rect.botRight.y = rect.topLeft.y - height * factor;
}
```

이 함수가 인수로 전달된 사각형을 실제로 수정하는지 확인할 수 있습니다.

```c++
Rectangle rect = { {1, 5}, {6, 3} };
scale(rect, 2);
// 출력: { {1, 5}, {11, 1} }
print(rect);
```

종종 함수는 전달된 인수를 수정할 필요는 없지만,  
과도한 복사를 방지하기 위해 참조가 필요합니다.  
이러한 경우, `const` 참조를 사용합니다.  
위 코드 조각에 언급된 `print` 함수는 이에 대한 좋은 예입니다:

```c++
void print(const Rectangle& rect) {
    std::cout << "{ " 
              << "{ " << rect.topLeft.x  << ", " << rect.topLeft.y  << "}, "
              << "{ " << rect.botRight.x << ", " << rect.botRight.y << "}" 
              << " }";
}
```

사실, 인수를 참조에 의해 전달받지만 이를 수정할 필요가 없는 경우에는  
항상 `const` 참조를 사용해야 합니다.  
이 관례는 함수가 전달받은 인수를 실수로 수정하는 일반적인 오류를 방지하는 데 도움이 됩니다.

`const` 참조를 사용하는 함수는  
C++ 코드베이스에서 자주 보게 될 매우 일반적인 패턴입니다.  

또한 우리가 이미 본 바와 같이, C++ 함수는  
인수를 _포인터에 의해_ 전달받을 수도 있습니다.  
예를 들어, 참조 대신 사각형의 포인터를 인수로 취하는  
`scalePtr` 함수를 살펴보겠습니다:

```c++
void scalePtr(Rectangle* rect, float factor) {
    float width = rect->botRight.x - rect->topLeft.x;
    float height = rect->topLeft.y - rect->botRight.y;
    rect->botRight.x = rect->topLeft.x + width * factor;
    rect->botRight.y = rect->topLeft.y - height * factor;
}
```

보시다시피, 포인터에 의한 전달은 참조에 의한 전달과  
많은 유사점을 공유합니다.  
C++에서는 일반적으로 후자가 대부분의 경우에서 더 선호됩니다.  
그러나 포인터에 의한 전달이 선호되는 몇 가지 경우가 있습니다:

- 함수 구현에 포인터 산술(pointer arithmetic)이 필요한 경우;
- 포인터로 전달되는 구조체가 일부 동적 데이터 구조(예: 이전에 확인했던 연결 리스트의 노드)의 일부인 경우;
- 함수가 포인터로 가리키는 메모리의 소유권을 가져야 하는 경우  
  (예: 메모리를 해제하기 위해).

소유권의 개념은 이 코스에서 나중에 더 자세히 다룰 것입니다.