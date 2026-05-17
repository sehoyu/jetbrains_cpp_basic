컨테이너를 탐색하는 동안 반복자(iterator)를 여러 번 접하게 될 것입니다. 이는 컨테이너와 반복자가 긴밀하게 연결되어 있기 때문에 놀라운 일이 아닙니다.

C++에서 [반복자](https://en.cppreference.com/w/cpp/iterator)는 컨테이너를 순회하고 그 요소들에 접근할 수 있게 해주는 객체입니다. 기본적으로 반복자는 컨테이너의 요소들을 바라볼 수 있는 시각을 제공하며, 이들에게 통합된 인터페이스를 제공합니다.

반복자는 포인터와 비슷하게 동작하며, 일부 컨테이너 타입의 경우 실제로 포인터입니다. 반복자는 배열이나 다른 어떤 컨테이너의 요소들을 내부 구조를 노출하지 않고 순차적으로 접근할 수 있는 수단입니다.

반복자는 사용 전에 반드시 초기화해야 합니다. `begin()` 함수를 사용하여 반복자를 컨테이너의 시작 위치로 초기화할 수 있으며, `end()` 함수를 사용하면 컨테이너 끝을 지난 한 위치로 초기화할 수 있습니다.

반복자를 `++` 연산자 또는 `std::next` 함수를 사용하여 컨테이너 내 다음 요소로 이동시킬 수 있습니다. 이전 요소로 이동하려면 `--` 연산자나 `std::prev` 함수를 사용하세요. 지정한 개수만큼 반복자를 이동시키려면 `+=`, `-=` 연산자나 `std::advance` 함수를 사용할 수 있습니다.

대부분 반복자의 타입은 길고 복잡한 표현입니다. 반복자를 선언할 때는 `auto` 키워드를 사용하는 것이 일반적인 관례입니다.

```cpp
std::vector<int> numbers = {1, 2, 3, 4, 5};
std::vector<int>::iterator it = numbers.begin(); // 길고 복잡한 타입
auto it = numbers.begin(); // auto 사용
```

두 반복자의 비교는 `==` 및 `!=` 연산자로 이루어지며, 이는 컨테이너의 끝에 도달했는지 확인할 때 유용하게 사용됩니다.

반복자가 가리키는 요소에 접근하려면 `*` 연산자를 사용합니다. 하지만 `end()` 반복자를 역참조(dereference)하면 정의되지 않은 동작(undefined behavior)이 발생합니다.

```cpp
std::vector<char> characters = {'i', 'a', 'm', 's', 'h', 'o', 'u', 't', 'i', 'n', 'g'};

// 반복자를 사용하여 요소 수정
for (auto it = characters.begin(); it != characters.end(); ++it) {
    *it = std::toupper(*it);
}

// 반복자를 사용하여 요소 접근
auto it = characters.begin();
while (it != characters.end()) {
    std::cout << *it++;
}
```

범위 기반 for 루프는 C++11에서 도입된 새로운 기능입니다. 반복자를 사용하여 컨테이너를 간결하게 순회할 수 있는 방법을 제공합니다. 범위 기반 for 루프는 모든 표준 컨테이너와 배열, 초기화 리스트에서도 사용할 수 있습니다. 범위 기반 for 루프의 문법은 다음과 같습니다:
```cpp
for (range_declaration : range_expression) loop_statement
```

예를 들어 다음 코드는:
```cpp
std::vector<int> v = {0, 1, 2, 3, 4, 5};

for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << ' ';
}

std::cout << '\n';

for (auto &i : v) {
    std::cout << i << ' ';
}
```
아래와 같이 동일한 결과를 출력합니다:
```
0 1 2 3 4 5
0 1 2 3 4 5
```

가능하다면 범위 기반 for 루프 사용을 고려하세요. 더 간결하고 오류가 발생할 확률이 적습니다.

정수형 벡터가 주어졌을 때, `find_maximum` 함수를 구현해야 합니다. 이 함수는 벡터 내에서 최대 요소에 대한 메시지를 반환해야 합니다. 함수는 반복자를 사용해 벡터를 순회하며 최대 요소를 찾아야 합니다.

메시지의 형식은 `"Maximum element is <max_element>"` 이어야 합니다.
만약 벡터가 비어있다면 `"Vector is empty"`를 반환하세요.