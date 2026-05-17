또 다른 형태의 연관 컨테이너에는 [`std::map`](http://en.cppreference.com/w/cpp/container/map)이 있습니다. `std::set`과 유사하지만, 키-값 쌍을 저장합니다. 사전(dictionary)과 비슷하다고 생각할 수 있습니다.

키는 고유하며, 기본적으로 오름차순으로 정렬됩니다. 키는 불변이므로 값을 변경할 수 없습니다.
값은 정렬되지 않으며, 중복이 허용됩니다.

사용자 지정 비교자(comparator)를 제공하여 직접 정렬 기준을 정의할 수도 있습니다.

`std::set`, `std::multiset`과 비교했을 때, `std::map`과 `std::multimap`은 `operator[]`와 `at()` 메서드를 사용하여 요소에 직접 접근할 수 있습니다. 그러나 다음 동작에 유의해야 합니다: 만약 키가 존재하지 않으면, `operator[]`는 해당 키와 기본값을 가지는 새 요소를 삽입합니다. 반면, `at()` 메서드는 키가 존재하지 않을 경우 예외를 발생시킵니다.

```cpp
std::map<std::string, int> people;
people.insert(std::make_pair("John", 25));
people.insert({"Jane", 20});
people["John"] = 30; // 이전 값을 덮어씁니다
people["Alex"] = 15; // 새로운 요소를 추가합니다
people["John"] += 5; // 값을 증가시킵니다
std::cout << "Number of people: " << people.size() << std::endl;
```

[`std::multimap`](http://en.cppreference.com/w/cpp/container/multimap)은 `std::map`과 동일한 기능을 제공하지만, 키의 중복을 허용합니다.

`find()`를 사용한 검색은 오직 키를 통해서만 할 수 있습니다. 값을 기준으로 검색하려면 컨테이너 전체를 순회해야 하며, 그 외의 방법은 존재하지 않습니다.

`std::set`과 `std::map` 모두 메모리에서 연속된 블록으로 저장되지 않습니다. 따라서 아래와 같이 `std::vector`에는 동작하는 코드가:

```cpp
std::vector<int> v = {1, 2, 3};
int* p = &v[0];
p += 1;
std::cout << *p << std::endl; // 2를 출력합니다
```

연관 컨테이너에서는 정의되지 않은 동작(Undefined behavior)을 초래합니다:

```cpp
std::map<int, int> m = {{1, 2}, {3, 4}};
std::pair<const int, int>* p2 = &*m.begin();
p2 += 1;
std::cout << p2->first << ' ' << p2->second << std::endl; // 정의되지 않은 동작
```

내부적으로, set과 map 컨테이너는 [레드-블랙 트리](https://en.wikipedia.org/wiki/Red–black_tree)라는 균형 잡힌 이진 탐색 트리 자료구조 위에 구현되어 있습니다. 이를 통해 요소의 삽입과 탐색 연산이 로그 복잡도를 가질 수 있습니다.

과제로, 텍스트 내 각 문자의 등장 횟수를 세는 함수를 구현해야 합니다. 이 함수는 문자(알파벳)를 키, 등장 횟수를 값으로 가지는 `std::map`을 반환해야 합니다. 문자는 알파벳 순으로 정렬되어야 합니다. 함수는 대소문자를 구분하지 않아야 하며("A"와 "a"는 동일하게 처리), 구두점과 숫자는 무시해야 합니다.