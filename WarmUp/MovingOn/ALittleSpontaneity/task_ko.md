소모품 객체가 항상 같은 위치에 나타나는 것은 조금 지루합니다.  
위치에 약간의 무작위성을 추가해 보겠습니다.

이번 단계에서 여러분의 작업은 다음 함수를 구현하는 것입니다:

```c++
Circle generateCircle(float radius);
```

이 함수는 주어진 반지름을 갖는 무작위 원을  
장면의 경계 내에서 생성해야 합니다.  
본질적으로, 이 함수는 이 원의 중심점을 생성해야 합니다.  
즉, 이 작업은 특정 범위 내에서 부동 소수점 숫자를  
생성하는 작업으로 축소될 수 있습니다.

```c++
float generateCoordinate(float min, float max);
```

`generateCoordinate`를 사용하여 무작위 2D 점을 생성할 때,  
다음 상수들이 장면의 경계를 정의한다는 것을 기억하세요:
* `NORTH_BORDER`
* `SOUTH_BORDER`
* `WEST_BORDER`
* `EAST_BORDER`

또한, 생성된 원이 경계 내에 맞도록 해야 합니다.

`generateCoordinate` 자체를 구현할 때,  
C++에서 제공하는 `rand` [함수](https://en.cppreference.com/w/c/numeric/random/rand)를  
활용할 수 있습니다.

```c++
// 0과 RAND_MAX 사이의 무작위 정수 값을 생성
int i = rand();
```

`RAND_MAX`는 C++에서 정의된 특수한  
[상수](https://en.cppreference.com/w/cpp/numeric/random/RAND_MAX)입니다.

코드에서 `rand` 함수를 처음 사용하기 전에  
C++의 난수 생성기를 초기화해야 한다는 것을 유의하세요.

```c++
// 현재 시간을 무작위성의 소스로 전달하여 난수 생성기를 초기화
srand(time(NULL));
```

이번 작업에서는 `main` 함수에서 이미 이 작업을 수행했으므로,  
여러분은 그냥 `rand`를 호출하기만 하면 됩니다.

하지만 `rand`는 무작위 정수 값을 생성하는 반면,  
우리는 특정 범위 내에서 부동 소수점 값을 생성해야 합니다.  
이를 위해 다음 공식을 사용할 수 있습니다:

```
x = min + r / (R / (max - min)) 
```

여기서  
* `x`는 결과로 나올 무작위 부동 소수점 값,  
* `min`과 `max`는 범위의 경계,  
* `r`은 무작위 정수 값,  
* `R`은 최대 정수 값 `RAND_MAX`입니다.