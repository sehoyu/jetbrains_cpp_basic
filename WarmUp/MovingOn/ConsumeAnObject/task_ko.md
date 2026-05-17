장면에 작은 별 형태의 소모 가능한 객체를 하나 더 추가해봅시다.  
플레이 가능한 객체가 이 소모 가능한 객체를 터치하면, 해당 객체는 사라져야 합니다.

이를 위해,  
[충돌 감지기](https://en.wikipedia.org/wiki/Collision_detection)를 구현해야 합니다.  
이 감지기는 두 객체가 장면에서 충돌했는지 신호를 보내는 역할을 합니다.  
둘 다 원형 모양을 가지고 있다는 사실을 활용할 것이며,  
이 가정을 통해 작업이 상당히 간단해질 것입니다.

또 다른 유형을 만들어 원형 모양을 표현해봅시다.

```c++
struct Circle {
    Point2D center;
    float radius;
};
```

이제 다음 함수를 구현해야 합니다.

```c++
bool collision(Circle circle1, Circle circle2);
```

이 함수는 두 원을 받아  
* 두 원이 충돌하면 `true`를 반환하고,  
* 그렇지 않으면 `false`를 반환합니다.  

두 원이 충돌했는지 감지하려면  
중심 간의 거리가 두 반지름의 합보다 작은지 확인하는 것으로 충분합니다.  
두 점 사이의 거리를 계산하려면,  
해당하는 함수를 구현하세요:

```c++
float distance(Point2D a, Point2D b);
```

2차원 공간에서 두 점 사이의 거리는 다음과 같이 계산할 수 있습니다:

```
dx = x1 - x2
dy = y1 - y2
d = sqrt(dx * dx + dy * dy)
```

여기서,  
* `x1`, `y1`, `x2`, `y2`는 두 점의 좌표,  
* `d`는 결과 거리,  
* `dx`와 `dy`는 `x`축과 `y`축에서의 두 점 간의 차이,  
* `sqrt`는 제곱근입니다.  

다행히도, C++ 언어에는 이미 `sqrt`라는  
[함수](https://en.cppreference.com/w/cpp/numeric/math/sqrt)가 구현되어 있어 직접 구현할 필요는 없습니다:

```c++
float sqrt(float x);