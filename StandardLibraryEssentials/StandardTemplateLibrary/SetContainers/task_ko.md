지금까지 다룬 모든 시퀀스 컨테이너 외에도, C++는 여러 연관 컨테이너도 제공합니다. 이러한 컨테이너는 요소들을 정렬된 순서로 저장하도록 설계되었습니다.

[`std::set`](http://en.cppreference.com/w/cpp/container/set)은 중복되지 않는 요소들을 정렬된 순서로 저장하는 컨테이너입니다. 사용자 정의 클래스를 `std::set`에 저장하려면, 비교 연산자를 정의해야 합니다. 기본적으로 비교 함수는 `std::less`로, 이는 `<` 연산자와 동일합니다.  
비교 함수는 집합의 요소와 같은 유형의 두 인수를 받아, 첫 번째 인수가 두 번째 인수보다 작으면(또는 객체가 수치적으로 비교할 수 없다면 단순히 왼쪽에 있어야 한다면) `true`를 반환하고, 그렇지 않으면 `false`를 반환해야 합니다. 비교 함수는 보통 클래스의 `friend`로 정의됩니다. 다음 예시는 사람의 이름과 나이를 저장하는 `person` 클래스에 대한 비교 함수를 정의하는 방법을 보여줍니다.

```cpp
class person {
public:
    person(std::string name, int age) : person_name(std::move(name)), person_age(age) {}
    std::string name() const { return person_name; }
    int age() const { return person_age; }
    friend bool operator<(const person& lhs, const person& rhs);
private:
    std::string person_name;
    int person_age;
};

bool operator<(const person& lhs, const person& rhs) {
    return lhs.name() < rhs.name();
}

int main() {
    std::set<person> people;
    people.insert(person("John", 25));
    people.insert(person("Jane", 20));
    people.insert(person("John", 25)); // 중복 요소는 삽입되지 않음
    std::cout << "Number of people: " << people.size() << std::endl;
    return 0;
}
```

[`std::multiset`](http://en.cppreference.com/w/cpp/container/multiset)은 `std::set`과 동일한 기능을 제공하지만, 중복 요소를 허용합니다. 집합을 정렬된 상태로 유지해야 하지만, 중복이 문제가 되지 않을 경우 유용할 수 있습니다. 삽입 및 탐색 연산의 복잡도는 로그 시간으로 동일하게 유지됩니다.

시퀀스 컨테이너와 달리, `std::set`과 `std::multiset`는 요소에 직접 접근하는 기능(`at()` 또는 `operator[]`)을 제공하지 않습니다. 요소에는 반복자를 통해서만 접근할 수 있습니다.

`find()` 메서드는 지정된 값과 일치하는 요소에 대한 반복자를 반환합니다. 요소를 찾을 수 없으면, 반복자는 `end()`와 같게 됩니다. `count()` 메서드는 지정된 값과 일치하는 요소의 개수를 반환하며, `std::set`의 경우 0 또는 1, `std::multiset`의 경우 0 이상이 될 수 있습니다.

`lower_bound()`와 `upper_bound()`는 각각 지정된 값보다 작지 않은(하한), 또는 지정된 값보다 큰(상한) 첫 번째 요소에 대한 반복자를 반환합니다. 해당 요소를 찾지 못하면 반복자는 `end()`가 됩니다.

탐색 연산이 자주 필요한 경우, 이러한 컨테이너를 사용하는 것이 좋습니다. 시퀀스 컨테이너보다 훨씬 빠른 연산 성능을 제공합니다.

여러분의 과제는 문자열을 받아 단어별로 분리하고, 고유한 단어의 `std::set`을 반환하는 함수를 구현하는 것입니다. 단어들은 알파벳 순으로 정렬되어야 하며, 대소문자를 구분하지 않아야 합니다. 즉, "Hello"와 "hello"는 동일한 단어로 간주해야 합니다. 또한, 구두점 및 숫자는 무시해야 합니다.

문자를 소문자로 변환하고, 글자만 고려하는 방법을 찾아보세요. 추가적인 헤더 파일이 필요할 수도 있습니다. 방법을 찾지 못한다면, 아래의 힌트를 참고할 수 있습니다.

<div class="hint">
  문자가 알파벳인지 확인하려면 <code>&lt;cctype&gt;</code> 헤더의 <code>std::isalpha</code> 함수를 사용할 수 있습니다. 문자를 소문자로 변환하려면 같은 헤더의 <code>std::tolower</code> 함수를 사용할 수 있습니다.
</div>