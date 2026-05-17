지금까지 배운 내용에 더해, STL은 요소의 범위에서 사용할 수 있는 다양한 알고리즘도 제공합니다. 이러한 알고리즘은 일반적으로 반복자를 활용하는 함수로 구현되어 있습니다. 이 단원에서는 가장 흔히 사용되는 알고리즘 몇 가지를 살펴보겠습니다. STL에는 이 외에도 많은 알고리즘이 있으며, 전체 목록은 [여기](https://en.cppreference.com/w/cpp/algorithm)에서 확인할 수 있습니다.
여러분이 직접 STL 알고리즘을 탐색하고, 코드에서 사용해 보시길 적극 권장합니다! 이들은 매우 유용하며 많은 시간과 노력을 절약할 수 있습니다.

#### 1. `std::sort()`
[`std::sort()`](https://en.cppreference.com/w/cpp/algorithm/sort) 알고리즘은 요소 범위를 정렬하는 데 사용됩니다. 이는 `O(n log n)` 정렬 알고리즘(대부분 [introsort](https://en.wikipedia.org/wiki/Introsort))의 함수 템플릿으로 구현되며, 구문은 다음과 같습니다.
```cpp
std::sort(start_iterator, end_iterator, comparator);
```
앞의 두 인자는 정렬할 요소 범위를 정의하는 반복자입니다. 세 번째 인자는 두 요소를 비교하는 데 사용되는 선택적 비교자(comparator)입니다. 비교자를 지정하지 않으면 기본적으로 오름차순으로 정렬됩니다. 비교자는 함수 포인터 또는 함수 객체(펑터)가 될 수 있습니다. 예상할 수 있듯이, 이 함수는 임의 접근 반복자(Random Access Iterator)를 필요로 하며, 임의의 순서로 정렬할 수 있습니다.
```cpp
// 정수 벡터를 오름차순으로 정렬
std::vector<int> v1 = {5, 2, 4, 3, 1};
std::sort(v1.begin(), v1.end());
// v = {1, 2, 3, 4, 5}

// 정수 벡터를 내림차순으로 정렬
std::vector<int> v2 = {5, 2, 4, 3, 1};
std::sort(v2.begin(), v2.end(), std::greater<>());
// v = {5, 4, 3, 2, 1}

// 문자열 벡터를 길이에 따라 오름차순으로 정렬
std::vector<std::string> v3 = {"abc", "a", "ab"};
std::sort(v3.begin(), v3.end(), [](const std::string &a, const std::string &b) {
    return a.size() < b.size();
});
// v = {"a", "ab", "abc"}
```

#### 2. `std::reverse()`
[`std::reverse()`](https://en.cppreference.com/w/cpp/algorithm/reverse)는 요소 범위를 뒤집는 데 사용됩니다. 이는 단순한 `O(n)` 알고리즘의 템플릿으로, 다음과 같은 구문을 가지고 있습니다.
```cpp
std::reverse(start_iterator, end_iterator);
```
두 인자는 뒤집을 요소의 범위를 정의하는 반복자입니다. 이 함수는 양방향 반복자(Bidirectional Iterator)를 필요로 합니다.
```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
std::reverse(v.begin(), v.end());
// v = {5, 4, 3, 2, 1}
```

#### 3. `std::find()`
[`std::find()`](https://en.cppreference.com/w/cpp/algorithm/find)는 요소 범위에서 값이 처음 나타나는 위치를 찾는 데 사용됩니다. `O(n)` 알고리즘인 함수 템플릿으로 구현되며, 구문은 다음과 같습니다.
```cpp
std::find(start_iterator, end_iterator, value);
```
앞의 두 인자는 검색할 범위를 정의하는 반복자입니다. 세 번째 인자는 검색할 값입니다. 값을 찾으면 그 값이 처음 나타나는 위치의 반복자를 반환하고, 찾지 못할 경우 범위의 끝 반복자를 반환합니다. 실행 정책이 필요 없으면 입력 반복자(Input Iterator)가, 있으면 전진 반복자(Forward Iterator)가 사용됩니다.
```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
auto it = std::find(v.begin(), v.end(), 3);
if (it != v.end()) {
    std::cout << "Found " << *it << std::endl;
} else {
    std::cout << "Not found" << std::endl;
}
```

#### 4. `std::max_element()` 및 `std::min_element()`
[`std::max_element()`](https://en.cppreference.com/w/cpp/algorithm/max_element)와 [`std::min_element()`](https://en.cppreference.com/w/cpp/algorithm/min_element)는 각각 범위 내 최대값과 최소값을 찾는 데 사용됩니다. 두 함수 모두 `O(n)` 복잡도를 가지며 다음과 같은 인터페이스를 공유합니다.
```cpp
std::max_element(start_iterator, end_iterator, comparator);
std::min_element(start_iterator, end_iterator, comparator);
```
앞의 두 인자는 검색할 범위를 정의하는 반복자입니다. 세 번째 인자는 두 요소를 비교하는 데 사용되는 선택적 비교자입니다. 비교자를 지정하지 않으면 기본적으로 `<` 연산자를 사용해 비교합니다. 이 함수들은 전진 반복자(Forward Iterator)를 필요로 합니다.
```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
auto max_it = std::max_element(v.begin(), v.end());
auto min_it = std::min_element(v.begin(), v.end());
std::cout << "Max: " << *max_it << std::endl;
std::cout << "Min: " << *min_it << std::endl;
```

#### 5. `std::fill()`
[`std::fill()`](https://en.cppreference.com/w/cpp/algorithm/fill)은 특정 값으로 요소 범위를 채우는 데 사용됩니다. 전체 배열을 순회하며 모든 요소를 변경하는 `O(n)` 시간 복잡도를 가집니다. 구문은 매우 간단합니다.
```cpp
std::fill(start_iterator, end_iterator, value);
```
첫 두 인자는 채울 요소의 범위를 정의하는 반복자이며, 세 번째 인자는 채울 값입니다. 이 함수는 전진 반복자(Forward Iterator)를 필요로 합니다.
```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
std::fill(v.begin(), v.end(), 0);
// v = {0, 0, 0, 0, 0}
```

또한 수치 연산에 유용한 여러 알고리즘을 포함하는 [`<numeric>`](https://en.cppreference.com/w/cpp/header/numeric) 헤더도 있습니다.

예를 들어, [`std::accumulate()`](https://en.cppreference.com/w/cpp/algorithm/accumulate)는 요소 범위의 합계를 구하는 데 사용됩니다. 이는 단순한 선형 `O(n)` 순회로 구현되며 다음과 같은 구문을 가집니다.
```cpp
std::accumulate(start_iterator, end_iterator, initial_value);
```
이 함수는 입력 반복자(Input Iterator)를 필요로 하며, 앞의 두 인자는 합계를 구할 범위를 정의하는 반복자입니다. 세 번째 인자는 합의 초기값입니다. 누적자의 타입에 유의하세요. 합이 너무 크면 오버플로가 발생할 수 있습니다. 예를 들어, 정수 범위의 합계를 구할 때는 오버플로를 방지하기 위해 초기값으로 `0LL`을 사용할 수 있습니다.
```cpp
std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
long long sum = std::accumulate(v.begin(), v.end(), 0LL);
std::cout << "Sum: " << sum << std::endl;
```

마지막으로, 위 알고리즘들을 실습해 봅시다. 여러분의 과제는 정수 벡터와 두 개의 주어진 값인 `lowerBound`와 `upperBound` 사이의 값을 갖는 요소들의 합을 반환하는 함수를 작성하는 것입니다.