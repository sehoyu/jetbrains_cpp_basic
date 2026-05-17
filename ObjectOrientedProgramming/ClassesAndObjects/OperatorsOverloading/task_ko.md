객체 지향 프로그래밍에 들어가기 전에,  
C++ 언어의 또 다른 유용한 기능에 대해 배우게 될 것입니다.  
이 기능은 코드를 더 읽기 쉽고 이해하기 쉽게 만드는 데 도움을 줄 수 있습니다.  
이 기능은 바로 __연산자 오버로딩__입니다.  
이를 통해 사용자 정의 데이터 타입에 대해 `+`, `-`, `*`와 같은 산술 연산자를 정의할 수 있습니다.

이전에 구현했던 `move` 함수를 떠올려 보세요.  
처음에는, `move`를 구현하여 객체를 `x` 축을 따라 이동시키는 것이 과제였습니다.  
해당 코드의 형태는 다음과 같았을 것입니다:

```c++
float move(float position, float velocity, float delta) {
    return position + delta * velocity;
}
```

그다음 단계에서는 `move`를 다시 구현하는 과제가 주어졌습니다.  
이번에는 `Point2D`라는 사용자 정의 데이터 타입과 두 개의 함수  
`add`와 `mul`을 사용하여 객체를 `x`와 `y` 축 모두를 따라 이동시키는 작업이었습니다:

```c++
Point2D move(Point2D position, Point2D velocity, float delta) {
    return add(position, mul(delta, velocity));
}
```

코드만 봐도 알 수 있듯이, 두 번째 코드 조각은  
무슨 일이 일어나고 있는지 이해하기 훨씬 더 어렵습니다.  
다행히도, 연산자 오버로딩을 사용하면,  
이 두 버전의 `move` 함수가 동일한 형태로 보이게 만들 수 있습니다!

```c++
Point2D move(Point2D position, Point2D velocity, float delta) {
    return position + delta * velocity;
}
```

이 구문을 가능하게 하려면, 이름에 `operator` 접두어가 붙은  
특별한 함수를 정의하기만 하면 됩니다:

```c++
Point2D operator+(Point2D a, Point2D b) {
    // 여기에 코드를 작성하세요.
}
```

C++ 언어는 [다양한 연산자](https://en.cppreference.com/w/cpp/language/operators)를 오버로드할 수 있습니다.  
다만, 다른 기능과 마찬가지로 연산자 오버로딩 기능도 남용될 가능성이 있다는 것을 기억하세요.  
연산자가 사용자 정의 데이터 타입에 대해 자연스러운 해석을 가질 경우에만  
연산자를 오버로드하는 것이 권장됩니다!

다음 과제로는 게임에서 사용되는 데이터 타입에 대해  
여러 연산자를 오버로드하는 작업입니다.  

`Point2D` 데이터 타입에 대한 익숙한 연산부터 시작해 봅시다.  
이 데이터 타입에 대해 산술 연산자 `+`, `-`, `*`를 오버로드하세요  
(이 연산자의 서명은 과제 템플릿에 이미 제공되어 있습니다).  
이전에 구현된 `add`와 `mul` 함수를 사용하는 것이 허용됩니다.  
뺄셈 연산자와 단항 마이너스 연산자의 차이점에 주의하세요.  
뺄셈 연산자는 한 점의 좌표에서 다른 점의 좌표를 빼는 반면,  
단항 마이너스 연산자는 단일 점의 좌표 부호를 모두 변경합니다.

산술 연산자는 `Circle` 및 `Rectangle`과 같은  
도형 데이터 타입에도 자연스러운 해석을 가질 수 있습니다.

<div class="hint">

사각형은 두 점(왼쪽 위 모서리와 오른쪽 아래 모서리)으로 정의된다는 점에 유의하세요:

```c++
struct Rectangle {
    Point2D topLeft;
    Point2D botRight;
};
```

점과 도형을 더할 때 점은 벡터로 해석되며,  
해당 벡터의 방향으로 도형을 이동시켜야 합니다.  
* `Circle` 도형의 경우, 원의 중심에 점을 더하는 것으로 충분합니다.  
* `Rectangle`의 경우, 사각형의 두 모서리에 모두 점을 더해야 합니다.  

도형을 스칼라와 곱하는 연산은 도형을 스케일링하는 결과를 가져와야 합니다.  
* `Circle`의 경우, 반지름에 스칼라를 곱하는 것으로 충분합니다.  
* `Rectangle`의 경우, 구현이 조금 더 복잡합니다.  
  사각형의 너비와 높이를 스케일링한 다음, 오른쪽 아래 모서리를 다시 계산해야 합니다.  
  사각형의 해당 속성을 가져오기 위해  
  미리 정의된 `width`와 `height` 함수를 사용할 수 있습니다(`rectangle.hpp` 파일에 정의됨).  

```c++
float width(const Rectangle& rect) {
    return rect.botRight.x - rect.topLeft.x;
}

float height(const Rectangle& rect) {
    return rect.botRight.y - rect.topLeft.y;
}
```

</div>

마지막으로, 위에서 언급된 모든 데이터 타입에 대해  
동등 비교 연산자를 오버로드하는 것이 편리할 것입니다.  

<div class="hint">

C++ 언어에서는 터미널에서 읽거나 쓰기 위해  
입력/출력 연산자를 오버로드하는 것도 가능합니다.  
다음은 `Point2D` 데이터 타입에 대해  
각각의 오버로드를 구현한 예제입니다:

```c++
// 출력 연산자 오버로드
std::ostream& operator<<(std::ostream& os, const Point2D& p) {
    return os << "(" << p.x << ", " << p.y << ")";
}

// 입력 연산자 오버로드
std::istream& operator>>(std::istream& is, Point2D& p) {
    return is >> p.x >> p.y;
}
```

`std::ostream`과 `std::istream` 타입의 인자에 주목하세요.  
이것은 각각 출력 스트림과 입력 스트림을 나타냅니다.  
이 스트림에 대해 아직 다루지 않았지만,  
향후 수업에서 다룰 예정입니다.  
지금은 `std::cout`과 `std::cin`이  
(이전 수업에서 보았던) 이 클래스의 특정 객체라는 사실만 알아두면 됩니다.

따라서 위의 오버로드를 통해 다음과 같은 코드를 작성할 수 있습니다:
```c++
Point2D point;
std::cout << "점의 좌표를 입력하세요 (x, y)" << std::endl;
std::cin >> point;
std::cout << "입력한 점은 " << point << "입니다." << std::endl;
```

게임에서 사용되는 다른 데이터 타입에 대한  
입력/출력 연산자의 오버로드는 `operators.hpp` 파일에서  
찾을 수 있습니다.

</div>