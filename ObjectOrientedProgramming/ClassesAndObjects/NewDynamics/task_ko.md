다음으로, 게임의 동적 동작, 즉 플레이 중 객체를 동적으로 추가하고 제거할 수 있는 기능을 복원해야 합니다.  
이를 위해, 객체 지향 프로그래밍을 이용해 이중 연결 리스트 데이터 구조를 다시 구현할 것입니다.  
이 작업을 진행하기 전에, `Ownership` 모듈을 먼저 완료하세요.  
이 모듈에서 가르치는 몇 가지 개념이 필요할 것입니다.  

먼저, `GameplayStaticScene` 클래스를 완전히 다시 작성하는 대신,  
새 클래스인 `GameplayDynamicScene`을 추가할 것입니다.  
여기서 우리는 새로운 동적 기능을 구현할 것입니다.  

`GameplayDynamicScene` 클래스의 선언(`dynscene.hpp` 파일)과 정의(`dynscene.cpp` 파일)를 확인하세요.  
해당 메서드에 대한 간단한 설명은 문서화 주석에 있습니다.  

`GameplayDynamicScene` 클래스는 `GameObjectList` 클래스의 필드 `objects`를 가지고 있습니다.  
이는 이 작업에서 다룰 주요 클래스이며, 이중 연결 리스트를 구현할 것입니다.  
클래스의 선언과 정의는 각각 `gobjectlist.hpp`와 `gobjectlist.cpp` 파일에서 찾을 수 있습니다.  

이번에는 객체 지향 프로그래밍과 소유권 모델을 이용해 노드를 소유하는 리스트를 구현할 것입니다.  
리스트 자체가 파괴되면 노드가 자동으로 소멸 및 할당 해제될 것이며,  
리스트가 복사되면 모든 노드의 복사본도 복사됩니다.  

리스트의 노드는 `Node` 구조체로 표현되며,  
여기서 각 노드는 다음 노드를 소유하는 소유권 개념을 구현합니다.  
`Node` 구조체의 필드를 자세히 살펴보겠습니다.  

- `next` 필드는 소유 포인터인 `std::unique_ptr<Node>`입니다.  
  노드가 소멸되면, 소유권 개념에 의해 해당 노드 다음의 모든 노드가 함께 소멸됩니다.  
- `prev` 필드는 일반 포인터인 `Node*`입니다.   
  이전 노드의 포인터를 저장합니다.  
  이는 소유하지 않는(non-owning) 포인터로, 만약 소유 포인터라면 소유권 순환이 발생할 수 있기 때문입니다.  
  예를 들어, 노드 `x`가 있고, `x.prev`가 노드 `y`를 가리키며, `y.next`가 다시 `x`를 가리키는 순환(cycle)이 발생할 수 있습니다.  
- `object` 필드는 노드에 저장된 게임 객체를 가리키는 공유 포인터인 `std::shared_ptr<GameObject>`입니다.  
  공유 소유권 개념을 가지며, 이를 통해 `GameObjectList` 클래스의 메서드에서 게임 객체를 안전하게 반환할 수 있습니다.  
  또한, 게임 객체의 공유 소유권은 리스트의 복사를 구현할 수 있도록 해줍니다.  
  복사본은 공유 포인터의 복사본을 간단히 저장합니다.  

`link` 및 `unlink`라는 정적 메서드는 각각 노드의 연결과 연결 해제를 구현합니다.  
이 함수들은 이미 `LinkedList` 작업에서 본 적이 있습니다.  
다시 보기 위해 해당 함수의 동작을 간단히 설명하겠습니다:

```c++
static void link(Node* cursor, std::unique_ptr<Node>&& node);
```

- `cursor`와 `node` 노드를 연결하며, `cursor` 바로 뒤에 `node`를 배치합니다.

```c++
static void unlink(Node* node);
```

- 노드를 인접 노드들과의 연결에서 해제합니다.

이 메서드들을 구현하세요.  
`next`, `prev`, 그리고 `object` 포인터의 서로 다른 소유권 개념에 주의하며, 소유권 관리를 위해 `std::move`를 사용하세요.  
`std::unique_ptr`는 소유권 이전 후 `nullptr` 상태로 전환되므로,  
`std::move`와 포인터 역참조 순서가 중요하다는 점을 기억하세요!

다음으로, `GameObjectList` 클래스의 필드를 살펴보겠습니다.

- `head`는 리스트의 첫 번째 노드에 대한 소유 포인터인 `std::unique_ptr<Node>`입니다.  
- `tail`은 리스트의 마지막 노드에 대한 소유하지 않는(non-owning) 포인터인 `Node*`입니다.  
  이는 이전 노드의 `next` 포인터를 통해 실제로 소유된 상태이기 때문에 소유하지 않는 포인터입니다.

리스트의 `head` 포인터는 소유 포인터이므로,  
리스트에 속하는 노드의 전체 시퀀스는 리스트가 소멸될 때 자동으로 소멸됩니다.  
따라서 클래스 소멸자의 기본 구현을 유지했습니다:

```c++
~GameObjectList() = default;
```

<div class="hint">

실제로, `GameObjectList`의 소멸자는   
`head` 필드의 `~std::unique_ptr()` 소멸자를 호출할 것입니다.  
이는 이어서 `Node`의 소멸자를 호출하며,  
또한 자신의 `next` 필드에 있는 `~std::unique_ptr()` 소멸자를 호출해,  
모든 노드가 소멸될 때까지 순차적으로 진행됩니다.  

</div>

이전 작업(`LinkedList`)에서 구현한 리스트에서는  
몇 가지 리스트 작동 함수를 단순화하기 위해 하나의 센티널 노드를 사용했습니다.  
더욱이, 리스트는 사이클 리스트로 조직되었습니다:  
마지막 노드의 `next` 필드는 첫 번째(센티널) 노드를 가리켰습니다.  
이번에는 이러한 트릭을 다시 사용할 수 없습니다.  
사이클 리스트는 소유권 순환을 초래하기 때문입니다.  
따라서 첫 번째 노드와 마지막 노드를 위한 두 개의 센티널 노드가 필요합니다.

리스트 표현을 활용하는 리스트의 사전 정의된 `foreach` 및 `remove` 메서드를 살펴보세요:  
- `foreach`는 리스트에 저장된 각 게임 객체에 대해 주어진 함수를 적용합니다.  
- `remove`는 주어진 조건자를 만족하는 게임 객체를 포함한 노드를 연결 해제(사실상 삭제)합니다.  

<div class="hint">

`std::function<...>` 유형이 익숙하지 않을 수 있습니다.  
본질적으로 이는 함수 포인터의 객체 지향 버전일 뿐입니다.  
이 유형에 대해 자세히는 코스의 이후 모듈에서 다룰 예정입니다.  

</div>

이제 리스트의 두 센티널 노드를 초기화해야 하는  
`GameObjectList` 클래스의 기본 생성자를 구현하세요:

```c++
GameObjectList();
```

다음으로, 리스트 끝(마지막 센티널 노드 바로 앞)에  
게임 객체를 삽입하는 메서드를 구현하세요:

```c++
void insert(const std::shared_ptr<GameObject>& object);
```

다음 사항을 기억하세요:
- 첫 번째 노드와 마지막 노드는 센티널 노드로 유지되어야 합니다.  
- 오직 센티널 노드만 `nullptr` 포인터를 `object` 필드에 저장할 수 있습니다.  

이 작업을 완료하려면 규칙-오브-파이브(rule-of-five)와  
복사 및 교환(copied-and-swap) 관용구를 따라  
`GameObjectList` 클래스의 소유권 개념 구현을 마무리하세요.  
특히, 다음을 구현하세요:

- 복사 생성자  
```c++
GameObjectList(const GameObjectList& other);
```

- 이동 생성자  
```c++
GameObjectList(GameObjectList&& other) noexcept;
```

- 할당 연산자  
```c++
GameObjectList& operator=(GameObjectList other);
```

- 교환 함수  
```c++
friend void swap(GameObjectList& first, GameObjectList& second);
```

이 작업을 모두 완료하면 새로운 동적 장면과 함께 게임 인스턴스를 실행할 수 있을 것입니다!