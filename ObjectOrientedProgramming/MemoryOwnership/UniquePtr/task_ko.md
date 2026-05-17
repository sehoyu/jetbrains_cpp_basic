C++에서 우리가 처음 살펴볼 스마트 포인터는 [std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr)입니다.

이 스마트 포인터는 동적으로 할당된 객체의 생명 주기를 관리하고 독점 소유권(Ownership) 의미를 제공합니다. 독점 소유권 모델은 특정 동적 객체를 특정 시점에 오직 하나의 `std::unique_ptr`만 소유하도록 보장합니다. 소유하는 `std::unique_ptr`이 소멸되거나 명시적으로 리셋되면, 해당 객체는 자동으로 소멸되고 관련 메모리는 해제됩니다.

`std::unique_ptr`의 또 다른 장점은 메모리 누수(memory leak)나 이중 삭제(double deletion)와 같은 메모리 오류를 방지하는 데 도움을 준다는 점입니다. `std::unique_ptr`은 객체가 더 이상 필요 없을 때 삭제되며, 삭제는 한 번만 이루어지도록 보장합니다.

추가적으로 `std::unique_ptr`의 사용은 코드 가독성을 향상시켜 어떤 포인터가 객체를 소유하고 삭제 책임이 있는지를 명확히 나타냅니다.

다음은 몇 가지 예제를 살펴보겠습니다. 
클래스 `Dog`가 아래와 같이 정의되어 있다고 가정합니다:

```c++
class Dog {
public:
    explicit Dog(const std::string& name) : name(name) {}
    ~Dog() {}

    std::string bark() const {
        std::cout << "Woof!\n";
    }
private:
    std::string name;
};
```

다음 코드 스니핏은 `unique_ptr`에 의해 소유되는 새로운 `Dog` 객체를 생성하는 방법을 보여줍니다:

```c++
void makeBark() {
    // unique pointer 생성
    std::unique_ptr<Dog> dog = std::make_unique<Dog>("Snoopy");
    // unique pointer가 null 포인터인지 검사할 수 있음
    // 이는 일반 포인터를 다루는 방법과 유사
    if (!dog) {
        return;
    }
    // unique pointer는
    // 일반 포인터처럼 사용할 수 있음
    dog->bark();
    // 함수가 종료될 때,
    // unique_ptr은 자동으로 Dog 객체를 삭제하고
    // 메모리를 해제함
}
```

<div class="hint">

어떻게 `std::unique_ptr`이 가리키는 객체를 자동으로 삭제할 수 있을까요? 실제로 표준 라이브러리의 `std::unique_ptr` 클래스 구현은 이 클래스의 소멸자를 단순히 재정의(overrides)하는 방식으로 이를 달성합니다.

</div>

대안으로, 포인터를 명시적으로 리셋하여 가리키는 객체를 삭제하도록 할 수 있습니다:

```c++
std::unique_ptr<Dog> dog = std::make_unique<Dog>("Snoopy");
dog->bark();
// 이 시점에서 포인터는 null로 리셋되고,
// 가리키던 객체는 소멸됨
dog.reset();
assert(dog == nullptr);
```

기존의 일반 포인터를 새로운 `std::unique_ptr`로 소유권을 이전하는 것도 가능합니다:

```c++
Dog* dog = new Dog("Snoopy");
// Dog 객체의 소유권은 unique_ptr이 가져감
// 수동으로 객체를 삭제해서는 안 됨
// unique pointer가 이를 대신 처리할 것이기 때문
std::unique_ptr smartDog(dog);
```

반대로, `std::unique_ptr` 명령에서 포인터와 그 소유권을 함께 제거할 수도 있습니다:

```c++
std::unique_ptr<Dog> smartDog = std::make_unique<Dog>("Snoopy");
// Dog 객체는 일반 포인터로 이동됨
// 이후 수동으로 삭제해야 함
// unique pointer는 이를 더 이상 관리하지 않기 때문
Dog* dog = smartDog.release();
// release 후, unique pointer는 null 상태가 됨
assert(smartDog == nullptr);
```

소유권을 해제하지 않고 일반 포인터를 얻는 것도 가능합니다. 하지만 일반 포인터는 unique pointer보다 오래 사용돼서는 안 됩니다; 그렇지 않으면 해제된 메모리를 사용하는 오류(use-after-free)가 발생할 수 있습니다.

```c++
std::unique_ptr<Dog> smartDog = std::make_unique<Dog>("Snoopy");
// 이제 dog와 smartDog는 동일 객체를 가리킴
// 소유권은 여전히 smartDog 포인터에 있음
Dog* dog = smartDog.get();
```

<div class="hint">

`get()` 메서드는 일반적으로 일반 포인터를 기대하는 함수에 unique pointer를 전달할 때 사용됩니다. 이는 특히 C++ 코드가 C 라이브러리와 상호작용해야 할 때 자주 발생합니다.

</div>

주의할 점은, 위에서 설명한 메서드를 사용해 일반 포인터를 unique pointer로 변환하거나 그 반대로 변환할 때, 동일한 객체를 가리키는 두 개의 unique pointer가 생성될 수 있습니다. 이는 `std::unique_ptr`의 소유권 규칙을 위반하며, 정의되지 않은 동작을 일으킵니다:

```c++
std::unique_ptr<Dog> dog = std::make_unique<Dog>("Snoopy");
// dog와 anotherDog는 동일 객체를 가리키며,
// 둘 다 객체의 독점 소유권을 가졌다고 잘못 판단함
// 따라서 둘 다 객체를 삭제하려 하여
// 정의되지 않은 동작이 발생함
std::unique_ptr<Dog> anotherDog(dog.get());
```

따라서 일반 포인터와 unique pointer 간 변환을 할 때는 특별히 주의해야 합니다. 일반적으로, 코드에서 이러한 변환을 완전히 피하는 것이 좋습니다.

기본적으로, `std::unique_ptr`은 이러한 잘못된 사용을 방지하고 단일 소유권 규칙을 강제합니다. 예를 들어, `std::unique_ptr`의 복사 생성자는 비활성화되어 있습니다:

```c++
std::unique_ptr<Dog> dog = std::make_unique<Dog>("Snoopy");
// 컴파일 에러 발생
std::unique_ptr<Dog> anotherDog = dog;
```

이 단원의 내용을 정리하기 위해, `copy` 함수를 구현해 보세요. 이 함수는 일반 포인터로 주어진 정수 배열과 배열 크기를 인자로 받고, 복사된 배열을 unique pointer로 반환해야 합니다. 주어진 배열의 크기가 `0`인 경우, 함수는 null pointer를 반환해야 합니다.

<div class="hint">

배열용 unique pointer를 생성하려면 다음 문법을 사용하세요:
```c++
std::make_unique<int[]>(size)
```

</div>