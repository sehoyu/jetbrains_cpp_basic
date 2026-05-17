C++의 순차 컨테이너 어댑터는 순차 컨테이너를 위한 독특한 인터페이스를 제공합니다. `std::stack`, `std::queue`, `std::priority_queue`는 각각 특정 동작을 제공하는 컨테이너 어댑터입니다.

[`std::queue`](https://en.cppreference.com/w/cpp/container/queue)는 [선입선출(FIFO)](https://en.wikipedia.org/wiki/FIFO_(computing_and_electronics)) 방식의 큐 자료구조를 제공하는 컨테이너 어댑터입니다. 요소는 끝에 추가되고, 앞에서 제거됩니다.

[`std::stack`](https://en.cppreference.com/w/cpp/container/stack)은 [후입선출(LIFO)](https://en.wikipedia.org/wiki/Stack_(abstract_data_type)) 방식의 스택 자료구조를 제공하는 컨테이너 어댑터입니다. 요소는 시퀀스의 끝에만 추가되거나 제거됩니다.

아래는 `std::stack` 및 `std::queue`의 사용 예시입니다:

```cpp
// 스택 생성 및 조작
std::stack<int> s;
s.push(1); // s = {1}
s.push(2); // s = {1, 2}
s.pop();   // s = {1}
std::cout << "스택의 맨 위: " << s.top() << "\n";

// 큐 생성 및 조작
std::queue<int> q;
q.push(1); // q = {1}
q.push(2); // q = {1, 2}
q.pop();   // q = {2}
std::cout << "큐의 맨 앞: " << q.front() << "\n";
```

[`std::priority_queue`](https://en.cppreference.com/w/cpp/container/priority_queue)는 [우선순위 큐](https://en.wikipedia.org/wiki/Priority_queue) 자료구조를 제공하는 컨테이너 어댑터입니다. 요소는 임의의 순서로 삽입되며, 우선순위에 따라 제거됩니다. 우선순위는 `Compare` 템플릿 매개변수로 정의되며, 기본값은 `std::less<T>`로 요소를 내림차순으로 정렬합니다.

다음은 `std::priority_queue`의 사용 예제입니다:

```cpp
std::priority_queue<int> pq;
pq.push(2); // pq = {2}
pq.push(1); // pq = {2, 1}
pq.push(3); // pq = {3, 2, 1}
pq.pop();   // pq = {2, 1}
std::cout << "우선순위 큐의 맨 위: " << pq.top() << "\n"; // 출력: 2

std::priority_queue<int, std::vector<int>, std::greater<int>> pq; // 비교자는 std::greater<int>
pq.push(2); // pq = {2}
pq.push(1); // pq = {1, 2}
pq.push(3); // pq = {1, 2, 3}
pq.pop();   // pq = {2, 3}
std::cout << "우선순위 큐의 맨 위: " << pq.top() << "\n"; // 출력: 2
```

연습을 위해 다음과 같은 연산을 지원하는 간단한 텍스트 편집기를 구현해봅니다:
- `insert(w, pos)` - 문자열 `w`를 위치 `pos`에 추가
- `erase(pos, len)` - 위치 `pos`부터 시작하여 `len`개의 문자를 삭제
- `undo()` - 마지막 연산(`append` 또는 `delete`)을 되돌리기
- `redo()` - 마지막으로 되돌린 연산을 다시 실행

`TextEditor` 클래스는 `/include/textEditor.h`에 정의되어 있습니다.