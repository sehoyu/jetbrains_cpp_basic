우리가 언급한 바와 같이, `GameObject` 클래스 자체는 게임 객체의 상태를 구체화하지 않습니다. 이는 단지 객체의 동작을 기술할 뿐입니다. 우리는 실제 상태를 가진 `GameObject`를 확장할 또 다른 클래스가 필요합니다.

다행히 객체 지향 프로그래밍에는 이러한 작업을 위한 적합한 개념이 있습니다. 바로 클래스 _상속_(inheritance)입니다. 상속 메커니즘은 기존 클래스를 확장하고, 그 가상 함수들에 대해 구체적인 구현을 제공할 수 있게 해줍니다. _파생_ 클래스(derived class), 혹은 _하위 클래스_(subclass, _서브타입_)는 _기본 클래스_(base class, _기본 타입_)의 모든 메서드와 필드를 상속받으며, 자체 메서드와 필드를 추가할 수 있습니다.

우리의 문제로 돌아와서, `GameObject` 클래스의 하위 클래스인 `CircleGameObject`를 정의해 봅시다. `CircleGameObject` 클래스의 인스턴스는 원형 모양의 게임 객체를 나타냅니다. 예를 들어, 플레이어가 조작하는 행성 객체가 이에 해당합니다.

`CircleGameObject` 클래스 정의를 살펴보겠습니다. 다음과 같은 세미콜론 문법:

```
class CircleGameObject : public GameObject
```

은 `CircleGameObject`가 `GameObject`의 하위 클래스임을 나타냅니다.

우선은 `CircleGameObject` 클래스 정의에서 사용된 `public` 및 `private` 키워드를 무시하도록 하겠습니다.

대신, `CircleGameObject`는 메서드뿐만 아니라 두 개의 필드를 선언하고 있다는 점에 주목하세요:  
* `circle` 필드는 객체의 형상 데이터를 저장합니다.  
* `status` 필드는 객체의 현재 상태를 저장합니다.

`CircleGameObject` 클래스의 첫 번째 메서드는 _생성자_(constructor)라 불리는 특별한 메서드입니다. 생성자는 클래스 이름과 동일한 이름을 가지며, 이 경우 `circle`이라는 단일 인수를 받습니다: `CircleGameObject(Circle circle)`. 생성자는 객체의 인스턴스를 생성하고 그 상태를 초기화하는 데 사용됩니다.

<div class="hint">

생성자 앞의 `explicit` [지정자](https://en.cppreference.com/w/cpp/language/explicit)는 암시적 타입 변환을 방지합니다.  
C++에서, 단일 인수를 가지는 생성자가 `explicit` 키워드로 표시되지 않은 경우, 컴파일러는 필요에 따라 인수 타입을 클래스 타입으로 자동 변환할 수 있습니다.

예를 들어, 생성자가 `CircleGameObject(Circle circle)`로 정의되었으나 `explicit`로 표시되지 않았다면 아래 코드가 컴파일될 수 있습니다:

```c++
void foo(CircleGameObject object) { /* ... */ }

int main() {
    Circle circle = { { 0.0f, 0.0f, }, 10.0f };
    // `Circle`이 `CircleGameObject` 생성자를 호출하여 암시적으로 변환됩니다.
    foo(circle);
}
```

하지만 생성자가 `explicit`으로 표시되었을 경우, 위 코드 조각은 컴파일되지 않으며 다음과 같이 수정해야 합니다:

```c++
void foo(CircleGameObject object) { /* ... */ }

int main() {
    Circle circle = { { 0.0f, 0.0f, }, 10.0f };
    CircleGameObject object(circle);
    foo(object);
}
```

C++ 언어에서는 `explicit` 생성자의 사용이 일반적으로 권장됩니다. 이는 보다 예측 가능한 동작을 보장합니다.

</div>

`CircleGameObject` 생성자 본문의 정의는 새로운 흥미로운 문법을 담고 있습니다:

```c++
CircleGameObject::CircleGameObject(Circle circle)
    : circle(circle)
    , status(GameObjectStatus::NORMAL)
{}
```

인수 목록 다음에 오는 콜론 `:` 뒤에는 객체 필드의 목록이 나옵니다. 필드 이름 옆 괄호 안의 값은 해당 필드를 초기화하는 데 사용됩니다. 생성자의 초기화 목록에서 필드의 순서는 필드가 클래스에 선언된 순서와 일치해야 합니다. 초기화 목록 뒤에는 생성자 본문 `{}`(이 경우 비어 있음)이 옵니다. 일반 메서드처럼, 이 안은 C++ 문장을 포함할 수 있습니다.

생성자에는 대응되는 메서드인 _소멸자_(destructor)가 있으며, 클래스 이름 앞에 `~`가 추가됩니다. 이 메서드는 객체가 소멸되기 직전에 자동으로 호출되어 일부 정리 작업(clean-up)을 수행합니다. 클래스에는 서로 다른 인수를 가진 여러 개의 생성자가 있을 수 있지만, 인수를 받지 않는 단일 소멸자만 존재할 수 있습니다.

사실 이전 단계에서 소멸자를 이미 본 적이 있을 것입니다. `GameObject` 클래스에는 가상 소멸자인 `~GameObject()`가 있습니다. `= default` 문법은 이 소멸자가 기본적으로 자동 생성된 구현을 가지고 있음을 나타냅니다.

이 과정에서 배우게 되겠지만, 생성자와 소멸자는 C++의 핵심적인 역할을 합니다.

다시 `CircleGameObject` 클래스로 돌아가서, 그 메서드를 살펴보겠습니다.  
`getPosition` 및 `setPosition`과 같은 일부 메서드는 단지 `GameObject` 클래스에서 온 메서드의 재선언일 뿐입니다. 이러한 메서드 선언 끝에 존재하는 `override` 키워드는 이 사실을 나타냅니다.

그러나 `GameObject` 클래스와는 달리, `CircleGameObject` 클래스는 실제로 이러한 메서드의 동작을 정의할 수 있습니다. 보다 구체적으로는, 여러분이 이들 메서드를 구현하는 것이 과제입니다. `getPosition`, `setPosition`, `getStatus`, `setStatus`, `getCircle` 메서드가 이에 해당합니다.

<div class="hint">

`CircleGameObject`의 위치(position)는 해당 원(circle)의 중심을 나타낸다는 점에 유의하세요.

</div>