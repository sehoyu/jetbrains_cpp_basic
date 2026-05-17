C++ 메모리 소유권에서 [std::weak_ptr](https://en.cppreference.com/w/cpp/memory/weak_ptr)는 객체의 수명에 영향을 주지 않으면서 임시 소유권을 관리하는 도구로 두드러집니다.  
`std::shared_ptr`가 공유 소유권을 가능하게 하는 반면,  
`std::weak_ptr`는 이를 보완하여 비침투적이고 관찰자와 같은 역할을 합니다.  
이 포인터는 객체의 참조 카운트에 기여하지 않으므로,  
객체의 수명을 연장하지 않고도 객체 상태를 감지할 수 있습니다.  

`std::weak_ptr`의 주요 사용 사례는 순환 참조 사이클을 끊는 것입니다.  
이 사이클은 그렇지 않으면 메모리 누수를 야기할 수 있습니다.  

이전 강의의 채팅 예제로 돌아가서,  
`Chat` 클래스에 호스트를 할당하는 기능을 추가하고자 한다고 가정해 봅시다.  

이를 위해, `Chat` 클래스를 다음과 같이 수정할 수 있습니다  
(`include/chat.hpp` 파일도 참고하세요):

```c++
class Chat {
public:
    Chat(int id, std::string name, const std::shared_ptr<User>& owner)
        : id(id)
        , name(std::move(name))
        , host(owner)
    {};

    /* ... */
private:
    int id;
    std::string name;
    std::shared_ptr<User> host;
};
```

또한, 이제 `User`의 `createNewChat` 메서드 대신  
동일한 이름의 함수를 선언할 것입니다:

```c++
std::shared_ptr<Chat> createNewChat(std::string name, const std::shared_ptr<User>& host);
```

이 함수는 생성할 채팅 이름과 해당 채팅의 호스트가 될 사용자에 대한  
공유 포인터를 파라미터로 받아야 합니다.

이제, 이 함수가 새로운 `Chat` 객체를 가리키는 공유 포인터 `chat`을 생성하고  
포인터 `chat->host`를 `host`에, 그리고 `host->chat`을 `chat`에 할당한다고 가정해 봅시다.  
이 경우 참조 사이클이 발생하게 됩니다.  
`chat`과 `host`가 서로를 가리키는 공유 포인터를 저장하는 한,  
두 객체의 참조 카운터는 `1` 이하로 내려가지 않습니다.  
즉, 객체가 절대 해제되지 않는다는 뜻이고 —  
다시 말해, 메모리 누수를 초래하게 됩니다!  

이를 방지하기 위해서는 참조 사이클을 끊기 위해 `std::weak_ptr`을 사용해야 합니다.  
특히, `Chat` 객체의 `host` 필드는 약한 포인터로 선언되어야 합니다.  

`Chat` 클래스의 `getHost` 메서드는 여전히  
공유 포인터를 반환해야 한다는 점에 유의하세요:

```c++
inline std::shared_ptr<User> getHost() const;
```

이를 위해, `std::weak_ptr`의 `lock()` 메서드를 사용해야 합니다.  
이 메서드는 주어진 `std::weak_ptr`이 아직 존재하는 경우,  
동일한 객체를 가리키는 새로운 `std::shared_ptr`을 생성합니다.  
존재하지 않을 경우, 비어 있는 `std::shared_ptr`을 반환합니다.  

이 강의를 마치기 위해, `Chat` 클래스의 구현(`include/chat.hpp` 파일 확인)을 수정하여  
`host` 필드에 대해 `std::shared_ptr` 대신 `std::weak_ptr`을 사용하세요.  
또한, `createNewChat` 함수의 구현(`task.cpp` 파일 확인)을 작성하십시오.