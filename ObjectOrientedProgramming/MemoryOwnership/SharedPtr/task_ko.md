`std::unique_ptr`와 대조적으로, 스마트 포인터 클래스 [`std::shared_ptr`](https://en.cppreference.com/w/cpp/memory/shared_ptr)는 공유 소유권 개념(shared ownership semantics)을 도입하여 여러 스마트 포인터가 동일한 동적으로 할당된 객체를 공유해 제어할 수 있도록 합니다.

`std::shared_ptr`는 내부적으로 참조 카운트(reference count)를 구현하여 동일한 객체를 가리키는 공유 포인터의 수를 추적합니다. 공유 포인터가 생성되거나 삭제될 때 참조 카운트는 동적으로 조정됩니다. 참조 카운트가 0에 도달하면 관리 중인 객체는 자동으로 파괴됩니다.

`std::unique_ptr`는 이동 가능(movable)하지만 복사할 수 없지만, `std::shared_ptr`는 이동 가능하며 동시에 복사도 가능합니다. `std::shared_ptr`를 복사하면 공유 소유권이 발생합니다. 이는 참조 카운트를 증가시킵니다. 기저 객체는 마지막 공유 포인터가 소유권을 해제할 때만 할당이 해제됩니다.

다음은 `std::shared_ptr` 사용 예제입니다:

```c++
void test() {
    // 공유 포인터 생성
    std::shared_ptr<Dog> dog = std::make_shared<Dog>("Pluto");
    // 포인터 사용
    dog->bark();
    // 공유 포인터 복사본 생성
    std::shared_ptr<Dog> copy = dog;
    // dog와 copy는 동일한 객체의 소유권을 공유
    std::cout << *dog << " " << *copy << "\n";
    // 주어진 객체를 가리키는 공유 포인터의 수를 쿼리할 수 있음
    std::cout << "dog.use_count() = " << dog.use_count() << "\n";
    // std::unique_ptr와 유사하게 일반 포인터를 얻을 수 있음
    std::cout << dog.get() << "\n";
    // 함수가 종료되면,
    // 두 공유 포인터의 소멸자가 호출되고,
    // 참조 카운트가 0으로 떨어져
    // Dog 객체의 메모리 할당이 해제됨
}
```

연습 문제로 간단한 채팅 시스템을 구현해 봅시다.  
이 시스템은 `Chat`과 `User`라는 두 개의 클래스로 구성됩니다 (`include/chat.hpp` 파일을 참고하세요).  
각 사용자는 자신이 현재 접속한 채팅 객체의 공유 포인터를 가지고 있습니다.  
다음은 여러분이 `User` 클래스에 대해 구현해야 할 메서드들입니다.

```c++
void createNewChat(std::string name);
```

* `createNewChat` 메서드는 주어진 이름으로 새로운 채팅을 생성하고 사용자를 해당 채팅에 로그인시켜야 합니다.

<div class="hint">

새로운 객체를 공유 포인터가 가리킬 수 있게 생성하려면  
`std::make_shared` 함수를 사용하세요.

</div>  

<div class="hint">

새로 생성된 `Chat` 객체에 고유 식별자를 부여하려면  
정적 필드 `nextChatId`를 사용하세요.

</div>

```c++
void joinChatByInvite(const User& user);
```

* `joinChatByInvite` 메서드는 해당 사용자를 다른 사용자의 채팅에 로그인시켜야 합니다  
  (채팅 포인터를 재할당하여 구현).

```c++
void leaveChat();
```

* `leaveChat` 메서드는 사용자를 채팅에서 로그아웃시켜야 합니다.