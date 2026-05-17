우리 행성의 움직임에 방향을 부여할 시간입니다!  
이 단계에서는 사용자가 키보드의 화살표 키를 사용하여 행성을 제어할 수 있도록 할 것입니다.

움직임의 방향을 모델링하려면 또 다른 새로운 데이터 타입이 필요합니다.

```c++
enum Direction {
    North,
    East,
    South,
    West
};
```

여기에서는 
[_열거형_](https://en.cppreference.com/w/cpp/language/enum)  
타입을 정의하며, 따라서 `enum` 키워드를 사용합니다.  
열거형 타입의 값은 정의된 열거형 내에 나열된 선택지 중 하나가 될 수 있습니다.

```c++
Direction direction = North;
```

사용자의 입력, 즉 특정 화살표 키를 누르는 이벤트를 처리하기 위해  
[main.cpp](course://WarmUp/MovingOn/GivingDirection/src/main.cpp)에 이미 관련 코드를 추가했습니다.  
이 새로운 코드 부분을 찾아보고 이해하려고 노력하세요.  
먼저 이해가 되지 않아도 걱정하지 마세요.  
현재 단계에서는 단순히 다음 함수를 구현하는 것이 여러분의 목표입니다: 

```c++
Point2D getDirection(Direction direction)
``` 

방향을 주기 위해서는 해당 방향의 _단위 벡터_를 계산해야 합니다.  
예를 들어:  
* 방향이 `North`일 경우, 단위 벡터는 `{ 0.0f, -1.0f }`입니다.  
* 방향이 `East`일 경우, 단위 벡터는 `{ 1.0f, 0.0f }`가 됩니다.  
이외의 경우도 이와 유사합니다.

어떤 방향이 전달되었는지 결정하려면 `case` 문을 사용할 수 있습니다:

```c++
switch (direction) {
    case North:
        std::cout << "North";
        break;
    case East:
        std::cout << "East";
        break;
    default:
        std::cout << " ";
        break; 
}
```  

실행 로직은 다음과 같이 진행됩니다.  
변수 `direction`의 실제 값이 검사된 다음:  
* 값이 `North`와 같다면, `case North:` 분기의 코드가 실행됩니다;  
* 값이 `East`와 같다면, `case East:` 분기의 코드가 실행됩니다;  
* 그렇지 않은 경우, `default:` 분기의 코드가 실행됩니다.

`break` 문은 분기를 떠나는 데 필요하다는 점에 주목하세요.  
그렇지 않으면 실행은 분기를 벗어나지 않고 다음 분기로 계속 진행됩니다:

```c++
switch (direction) {
    case North:
        std::cout << "North" << " ";
    case East:
        std::cout << "East";
    // direction이 North일 경우, "North East"를 출력합니다.
    // direction이 East일 경우, "East"를 출력합니다.
}
```

함수 내부에서 `break` 대신 `return`을 사용하여  
`case` 분기를 벗어나 함수 전체에서 종료할 수도 있습니다.