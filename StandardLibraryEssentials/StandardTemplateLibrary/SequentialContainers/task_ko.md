`std::vector` 외에도 STL에는 다양한 시퀀스 컨테이너가 포함되어 있습니다. `std::forward_list`, `std::list`, `std::deque`는 모두 동적 크기 조정을 지원하며, 성능과 기능 면에서 각기 다른 장단점을 제공합니다.

[`std::forward_list`](https://en.cppreference.com/w/cpp/container/forward_list)는 C++11에 도입된 [단일 연결 리스트](https://en.wikipedia.org/wiki/Linked_list)입니다. 이 컨테이너는 다음 요소로의 링크만 유지하기 때문에 `std::list`보다 메모리 사용량이 적지만, 한 방향(전방)으로만 순회할 수 있습니다. 특징적으로, 특정 위치에서 작업을 수행하고자 할 때 그 위치의 이전 요소에 대한 반복자를 가지고 있다면, 리스트의 임의 위치에 요소를 삽입하거나 삭제할 수 있습니다.

[`std::list`](https://en.cppreference.com/w/cpp/container/list)는 [이중 연결 리스트](https://en.wikipedia.org/wiki/Doubly_linked_list)입니다. 시퀀스 내 어디서나 상수 시간에 삽입 및 삭제 작업을 지원하며, 양방향 반복도 가능합니다. 하지만 빠른 임의 접근(random access)을 제공하지 않고, 연속된 메모리 할당이 아니기 때문에 [캐시 친화적](https://stackoverflow.com/questions/16699247/what-is-a-cache-friendly-code)이지 않으며, 각 요소마다 링크 정보를 추가로 저장하므로 메모리 사용량이 더 많습니다.

[`std::deque`](https://en.cppreference.com/w/cpp/container/deque) (double-ended queue, [양쪽 끝에서 삽입/삭제가 가능한 큐](https://en.wikipedia.org/wiki/Double-ended_queue))는 `std::vector`와 유사하지만, 시퀀스의 앞과 뒤 양쪽 모두에서 빠른 삽입 및 삭제가 가능합니다. `std::vector`와 달리 메모리상 모든 요소가 연속적으로 배치된다는 보장은 없지만, 역시 빠른 임의 접근을 지원합니다. 시퀀스의 양쪽 끝을 자주 변경해야 하는 경우에 적합한 범용 자료구조입니다.

아래는 각 컨테이너의 사용 예시입니다.

```cpp
// forward_list 생성 및 조작
std::forward_list<int> fl = {1, 2, 3};
fl.push_front(0); // fl = {0, 1, 2, 3}
//   fl.push_back(4);  오류: push_back은 지원되지 않음
fl.pop_front();   // fl = {1, 2, 3}
//   fl.pop_back();    오류: pop_back은 지원되지 않음
//   fl[1] = 5;        오류: operator[]는 지원되지 않음
auto second_fl = fl.begin();
fl.insert_after(second_fl, 5); // fl = {1, 5, 2, 3}, O(1) 복잡도

// list 생성 및 조작
std::list<int> l = {1, 2, 3};
l.push_front(0); // l = {0, 1, 2, 3}
l.push_back(4);  // l = {0, 1, 2, 3, 4}
l.pop_front();   // l = {1, 2, 3, 4}
l.pop_back();    // l = {1, 2, 3}
//    l[1] = 5;        오류: operator[]는 지원되지 않음
auto second_l = std::next(l.begin());
l.insert(second_l, 5); // l = {1, 5, 2, 3}, O(1) 복잡도

// deque 생성 및 조작
std::deque<int> d = {1, 2, 3};
d.push_front(0); // d = {0, 1, 2, 3}
d.push_back(4);  // d = {0, 1, 2, 3, 4}
d.pop_front();   // d = {1, 2, 3, 4}
d.pop_back();    // d = {1, 2, 3}
d[1] = 5;        // d = {1, 5, 3}
auto second_d = std::next(d.begin());
d.insert(second_d, 0); // d = {1, 0, 5, 3}, O(n) 복잡도
```

이 컨테이너들의 공통적으로 사용되는 주요 메서드는 다음과 같습니다:  
 - `push_front(x)`와 `push_back(x)`는 각 컨테이너의 앞과 뒤에 요소를 추가합니다.
 - `pop_front()`와 `pop_back()`는 각각 컨테이너의 첫 번째와 마지막 요소를 제거합니다.
 - `insert(x)`는 단일 요소 혹은 요소 범위를 컨테이너에 삽입할 때 사용합니다. 단, forward_list에서는 대신 `insert_after(x)`를 사용해야 합니다.
 - `erase(x)`는 단일 요소 또는 요소 범위를 컨테이너에서 제거할 때 사용합니다. forward_list에서는 `erase_after(x)`를 사용합니다.
 - `size()`는 컨테이너에 들어 있는 요소 수를 반환합니다. 단, `std::forward_list`는 `size()` 메서드를 제공하지 않습니다.
 - `empty()`는 컨테이너가 비어있는지 확인합니다.
 - `clear()`는 컨테이너의 모든 요소를 제거합니다.

또 하나 주목할 만한 컨테이너로 [`std::array`](https://en.cppreference.com/w/cpp/container/array)가 있습니다. 이것은 고정 크기 배열을 캡슐화하는 시퀀스 컨테이너로, C 스타일 배열과 유사하지만, STL의 다른 컨테이너들과 비슷한 인터페이스를 제공합니다. `at()`을 통한 범위 확인, `size()` 메서드, 다양한 컨테이너를 인자로 받는 함수들과의 호환성(또한, C 배열과 달리 포인터로 변환되지 않음), 반복자 지원 등의 기능이 포함되어 있습니다. 배열의 크기가 컴파일 타임에 명확할 때는 C 스타일 배열보다 좋은 대체재입니다.

```cpp
// array 생성 및 초기화
std::array<int, 3> a = {1, 2, 3};

// 요소 접근
std::cout << "첫 번째 요소: " << a.front() << "\n";
std::cout << "마지막 요소: " << a.back() << "\n";

// 배열의 크기
std::cout << "배열 크기: " << a.size() << "\n";
```

다음은 여러분이 해결해야 할 과제입니다.  
`sum_adjacent_elements`라는 이름의 함수를 작성하세요. 이 함수는 크기가 `n`인 정수형 컬렉션 `nums`를 입력받아, 같은 타입의 크기 `n/2`인 새 컬렉션을 반환합니다. 반환된 컬렉션에는 원래의 `nums`에서 인접한 쌍의 합이 저장되어야 하며, 나머지로 짝을 이루지 못하는 요소는 새 컬렉션에 복사하지 않습니다.  
이 함수를 `std::list`와 `std::deque` 각각에 대해 구현해야 합니다.

<div class="hint">
  두 컨테이너의 차이를 기억하세요. `std::deque`는 임의 접근을 지원하므로 `[]` 연산자를 사용할 수 있습니다. 반면, `std::list`는 임의 접근을 지원하지 않으므로 반복자를 활용해 요소를 접근해야 합니다.
</div>