클래스 `CircleGameObject`가 `GameObject` 클래스에 몇 가지 데이터 필드를 추가했음에도 불구하고,  
여전히 `GameObject`의 가상 메서드 일부를 구현하지 않았습니다.  
따라서, 이 클래스는 여전히 _추상 클래스_ 입니다 — 인스턴스화할 수 없습니다.  

우리는 기본 클래스의 동작을 구현할 구체적인 하위 클래스를 도입해야 합니다.  
이 하위 클래스의 인스턴스는 기본 클래스의 인스턴스가 기대되는 곳에서 사용할 수 있습니다.  
객체의 구체적인 하위 클래스를 대체함으로써,  
이 객체를 사용하는 함수의 코드를 변경하지 않고도 프로그램의 동작을 변경할 수 있습니다!  
이렇게 서로 다른 동작을 구현하는 서로 다른 클래스의 객체를  
공통된 기본 클래스의 객체로 취급할 수 있는 능력을 _하위형 다형성_이라고 부릅니다.  

`CircleGameObject` 클래스의 두 가지 구체적인 하위 클래스를 도입해보겠습니다 —  
플레이어가 제어하는 객체를 나타내는 `PlayerObject` 클래스와  
소모 가능한 객체를 나타내는 `ConsumableObject` 클래스입니다.  
마지막으로, 이 두 클래스 모두 `GameObject` 클래스에서 요구하는 모든 기능을 구현합니다.  

이 클래스들의 선언은 `player.hpp`와 `consumable.hpp` 파일에서 확인할 수 있습니다.  
여기에 새로운 문법 구조가 없으므로, 해당 파일의 코드를 이해할 수 있을 것입니다.  

이 클래스들의 구현은 `player.cpp`와 `consumable.cpp` 파일에서 찾을 수 있습니다.  
몇 가지 메서드의 전체 구현이 이미 제공되어 있음을 참고하세요.  
예를 들어, `PlayerObject` 클래스의 `getVelocity` 메서드는 현재 속도 벡터를 계산하는데,  
이는 플레이어가 현재 어떤 키를 누르고 있는지를 결정하는 `SFML` 함수를 호출하여 수행됩니다.  

여러분의 작업은 두 클래스의 `getTexture` 메서드를 구현하는 것입니다.  
이 메서드는 객체의 현재 상태에 따라 표시될 객체의 현재 텍스처를 반환해야 합니다.  
비록 아직 객체 상태를 실제로 업데이트하는 메서드는 구현하지 않았지만,  
먼저 `getTexture` 메서드를 구현함으로써 메서드 호출 문법을 배우고 연습할 수 있는 좋은 기회가 될 것입니다.  

`getTexture` 메서드는 `TextureManager` 클래스의 객체를 참조로 전달받는 하나의 인수를 취합니다.  
이 클래스는 우리가 미리 정의해둔 클래스로, 게임에 필요한 텍스처를 로드하는 책임을 집니다.  
`TextureManager` 클래스의 `getTexture` 메서드를 호출하여 텍스처 포인터를 요청할 수 있습니다.  
이 메서드는 텍스처의 ID를 인수로 받으며, 이러한 ID는 `GameTextureID` 열거형으로 표현됩니다.  

<div class="hint">  

이전에 `enum` 키워드를 사용했지만,  
`GameTextureID` 타입은 `enum class`라는 두 키워드로 정의된다는 점에 유의하세요.  
그렇다면 `enum`과 `enum class` 선언 사이의 차이점은 무엇일까요?  

사실 `enum class` (일명 _범위 지정 열거형_)은  
일반 `enum`의 몇 가지 문제점을 해결하기 위해 C++ 언어에 도입된  
제한된 형태의 열거형입니다.  

첫째, `enum class`의 경우 열거 값의 이름이 열거 이름의 범위 내에 유지됩니다.  
이렇게 하면 열거 값이 전역 범위를 오염시키지 않아  
실수로 이름 충돌이 발생할 위험이 없게 됩니다.  

예제를 살펴봅시다.  
일반 `enum`의 경우, 다음과 같은 문법이 사용됩니다:  
```c++
enum Color { RED, GREEN, BLUE };
// RED, GREEN, BLUE는 전역적으로 접근 가능한 이름이 됩니다.
Color green = GREEN;
```  
반면 `enum class`의 경우, 열거 값은 열거 이름을 통해서만 접근할 수 있습니다:  
```c++
enum class Color { RED, GREEN, BLUE };
// RED, GREEN, BLUE는 전역 범위를 오염시키지 않습니다.
Color green = Color::GREEN;
```  

둘째, `enum class`는 `int`로의 암시적 변환을 허용하지 않습니다.  
예를 들어, 다음 코드에는 문제가 없습니다:  
```c++
enum Color { RED, GREEN, BLUE };
// 컴파일 오류 없음, 변수 green은 1로 설정됩니다.
int green = GREEN;
```  
하지만 `enum class`를 사용하면 코드는 컴파일되지 않습니다:  
```c++
enum class Color { RED, GREEN, BLUE };
// 컴파일 오류: Color에서 int로의 암시적 변환은 허용되지 않습니다.
int green = Color::GREEN;
```  

</div>  

`PlayerObject`와 `ConsumableObject`의 `getTexture` 메서드를  
다음 논리를 사용하여 구현하십시오:  
* `NORMAL` 또는 `WARNED` 상태에서는, 플레이어 객체는 `PLANET` 텍스처를 가져야 합니다;  
* `DESTROYED` 상태에서는, 플레이어 객체는 `PLANET_DEAD` 텍스처를 가져야 합니다;  
* `NORMAL` 상태에서는, 소비 가능한 객체는 `STAR` 텍스처를 가져야 합니다;  
* `WARNED` 상태에서는, 소비 가능한 객체는 `STAR_CONCERNED` 텍스처를 가져야 합니다;  
* `DESTROYED` 상태에서는, 소비 가능한 객체가 표시되지 않아야 합니다.  

<div class="hint">  

마지막 경우를 구현하는 데 문제가 있다면,  
`GameObject`의 `getTexture` 메서드의 문서를 참조하세요.  

</div>  

이 메서드를 구현하려면, `TextureManager` 클래스의 `getTexture` 메서드를 호출해야 합니다.  
이를 위해, 구조체의 필드에 접근하는 것과 동일한 점(`.`) 문법을 사용하세요:  

```c++
const sf::Texture* texture = textureManaged.getTexture(id);