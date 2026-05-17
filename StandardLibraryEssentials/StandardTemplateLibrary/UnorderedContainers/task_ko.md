O(1) 복잡도로 삽입, 삭제, 탐색이 가능한 컨테이너를 만들 수 있는 방법이 있을까요? 마치 마법 같죠?  
하지만 사실 그렇지 않습니다. STL은 해시 테이블([hash table](https://en.wikipedia.org/wiki/Hash_table))을 이용해 구현된 `std::unordered_set`과 `std::unordered_map` 컨테이너를 제공합니다.

일반적인 `std::set`과 `std::map`이 비순서 버전과 구별되는 점은 무엇일까요? 구현 방식의 차이(이 부분은 뒤에서 더 설명합니다)로 인해 두 컨테이너의 주요 차이점은 요소들의 순서가 안정적으로 유지되지 않는다는 점입니다. 이러한 컨테이너에도 반복자(iterator)가 있지만, 반복자를 이용해 요소를 순회할 때 요소들이 오름차순으로 정렬되어 있지 않다는 것을 알 수 있습니다.  
하지만 이러한 특성은 탐색, 삽입, 삭제 연산이 O(1) 복잡도로 처리된다는 큰 장점에 비하면 감수할 만한 작은 단점입니다.

`std::unordered_set`과 `std::unordered_map`의 주요 메서드는 다음과 같습니다:  
* `insert(value)` - 요소 `value`를 컨테이너에 삽입합니다.  
* `emplace(args...)` - 요소를 직접 컨테이너 내에서 생성합니다.  
* `erase(value)` - 요소 `value`를 컨테이너에서 삭제합니다.  
* `find(value)` - 요소 `value`를 찾으면 해당 요소에 대한 반복자를 반환하며, 찾지 못하면 `end()`를 반환합니다.

해시 테이블은 키를 버킷(bucket)에 매핑하기 위해 [해시 함수](https://en.wikipedia.org/wiki/Hash_function)를 사용하는 자료구조입니다. 요소 삽입이나 탐색을 할 때, 먼저 키에 해시 함수를 적용해 버킷 번호를 얻고, 해당 버킷 안에서 요소를 삽입하거나 탐색합니다.

표준 라이브러리는 기본 타입에 대해 `std::hash` 함수를 제공하며, 사용자가 정의한 타입에 대해서는 직접 해시 함수를 정의할 수 있습니다.

<div class="hint">
  사실 공정하게 말하면, 이러한 모든 메서드는 amortized 기준 O(1) 복잡도를 가집니다. 왜냐하면 서로 다른 키들의 해시 값이 같아지는 경우(충돌, collision: https://en.wikipedia.org/wiki/Hash_table#Collision_resolution)가 발생할 수 있기 때문입니다. 이러한 경우에는 전체 테이블을 다시 해싱(rehash)해야 하므로, 비순서 컨테이너의 메서드가 최악의 경우 O(n) 시간에 수행될 수 있습니다.
</div>

버킷을 조작하는 여러 함수도 있습니다:
* `bucket_count()` - 버킷의 개수를 반환합니다.
* `bucket_size(n)` - n번째 버킷에 들어 있는 요소의 수를 반환합니다.
* `bucket(k)` - 키 `k`에 해당하는 버킷 번호를 반환합니다.
* `load_factor()` - 버킷당 평균 요소 개수를 반환합니다.
* `max_load_factor()` - 최대 로드 팩터를 반환합니다.
* `rehash(n)` - 버킷의 개수를 n개 이상으로 재설정합니다.

사용자 정의 해시 함수가 필요할 때에는 다음과 같이 정의할 수 있습니다:
```cpp
struct my_type {
private:
    int x;
    int y;

public:
    my_type(const int x, const int y) : x(x), y(y) {};
    
    bool operator==(const my_type& other) const {
        return x == other.x && y == other.y;
    }

    friend struct my_hash;
};

struct my_hash {
    std::size_t operator()(const my_type& t) const {
        return std::hash<int>()(t.x) ^ std::hash<int>()(t.y);
    }
};

int main() {
    std::unordered_set<my_type, my_hash> s;
    s.emplace(1, 2);
}
```

이 컨테이너들의 멀티버전으로는 `std::unordered_multiset`과 `std::unordered_multimap`이 있습니다. 이들은 동일한 키를 가진 여러 요소를 저장할 수 있도록 허용합니다.

예시로, 아래 코드를 살펴보겠습니다:
```cpp
#include <iostream>
#include <unordered_set>
#include <string>

int main() {
    std::unordered_set<std::string> set;
    set.insert("Greetings, traveler!");
    set.insert("How are you?");
    set.insert("Come join us!");
    
    if (set.find("How are you?") != set.end()) {
        std::cout << "Found!" << std::endl;
    }
    
    // C++20 이상을 사용한다면 아래처럼 사용할 수 있습니다.
    
    // if (set.contains("How are you?")) {
    //     std::cout << "Found!" << std::endl;
    // }
    
    // 모든 요소를 출력, 순서는 보장되지 않음
    for (const auto& s : set) {
        std::cout << s << std::endl;
    }
}
```

[캐시](https://en.wikipedia.org/wiki/Cache_(computing)) 시스템을 [LRU](https://en.wikipedia.org/wiki/Cache_replacement_policies#Least_recently_used_(LRU)) (Least Recently Used, 가장 최근에 사용되지 않은) 정책으로 구현해야 합니다. 해당 클래스의 멤버 함수는 `/include/Cache.h` 파일에 정의되어 있습니다. 캐시는 매우 빠른 저장소의 한 종류이므로, 해싱을 이용해 구현해야 합니다. 먼저 `/include/Cache.h` 파일 내부에 키-값 쌍을 저장할 구조체를 정의하세요. 그 다음, 키와 리스트 내 해당 요소에 대한 반복자를 저장할 또 다른 구조체를 정의하세요. 이 구조체들을 정의한 뒤, `task.cpp`에서 캐시 연산을 구현할 수 있습니다.

<div class="hint">
  작성자의 정답 예시에서는 `std::list`에 키+값의 쌍(`std::pair`)을 요소로 담고, `std::unordered_map`에는 키와, 이 리스트 요소에 대한 반복자를 값으로 저장하여 사용합니다.
</div>

캐시에는 다음과 같은 메서드가 필요합니다:
* `LRUCache(size_t capacity)` - 캐시의 최대 요소 개수를 설정하는 생성자입니다.
* `void put(const std::string& key, const std::string& value)` - 키-값 쌍을 캐시에 삽입합니다. 캐시가 가득 찼을 경우에는 가장 오래 사용되지 않은 요소를 제거해야 합니다.
* `std::string get(const std::string& key)` - 지정한 키와 연결된 값을 반환합니다. 키를 찾지 못할 경우 `std::nullptr`을 반환합니다.