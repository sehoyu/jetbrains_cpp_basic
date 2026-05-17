여러분이 이미 익숙한 컨테이너 중 하나는 [`std::string`](https://en.cppreference.com/w/cpp/string/basic_string)입니다. 이는 문자 시퀀스를 저장하는 데 사용되는 구조체입니다. 그렇다면 왜 `std::vector<char>` 대신 `std::string`을 사용할까요? 두 컨테이너는 공통점이 많습니다. 예를 들면, 인덱스를 통해 원소에 접근할 수 있고, 둘 다 메모리를 자동으로 관리합니다. 그리고 `push_back()`, `pop_back()`, `insert()`, `erase()`, `size()`, `empty()` 등과 같은 메서드도 공유합니다. 

주요 차이점은 `std::string`에는 문자열에 특화된 다양한 메서드(예: `find()`, `substr()`, `replace()` 등)가 있다는 점입니다. 또한, `std::string`은 문자열을 연결할 수 있는 `+` 연산자를 지원하며, 널 종료를 보장하여 `c_str()` 메서드를 통해 널 종료된 문자열 포인터를 얻을 수 있습니다. 또한, 여러 생성자를 제공하여 문자, 부분 문자열, 널 종료된 문자열 포인터, 문자열 포인터, 문자 범위 등 다양한 형태로 문자열 객체를 생성할 수 있습니다.

일반적으로 `std::string`은 문자열을 다루는 데 있어 `std::vector<char>`보다 훨씬 편리합니다.

매우 유용한 컨테이너이지만 성능 저하를 유발할 수 있는 몇 가지 요인이 있습니다. 이번 강의에서는 `std::string`을 효율적으로 사용하는 방법을 배웁니다.

먼저, `std::vector`와 마찬가지로 `reserve()` 메서드를 이용해 필요한 용량을 미리 알 경우 특정 문자 개수만큼 메모리를 예약할 수 있습니다.

<div class="hint">
  또한 **Small String Optimization(작은 문자열 최적화)**이라는 기능이 있습니다. 이는 문자열이 충분히 작으면, 힙이 아니라 스택에 직접 저장된다는 의미입니다. 자세한 내용은 다음 글을 참고하세요: https://giodicanio.com/2023/04/26/cpp-small-string-optimization/.
</div>

문자열을 함수로 전달해야 할 때에는, 상수 참조(const reference)로 전달하는 것이 유리한 경우가 많습니다. 그렇게 전달하지 않으면 문자열이 복사되기 때문입니다. 예를 들어, 문자열을 출력하고 싶다면 상수 참조로 전달할 수 있습니다:

```cpp
void print(const std::string& str) {
    std::cout << str << '\n';
}

int main() {
    std::string str = "Imagine a very long string here that will take a loooooot of time to copy";
    print(str);
}
```

이전 모듈에서 배운 것처럼, 이동 시맨틱(move semantics)은 리소스를 더욱 효율적으로 관리할 수 있는 방법입니다. 문자열을 전달하면서 원본 객체가 더이상 필요하지 않다면 `std::move()`를 사용하는 것을 고려해보세요.

```cpp
class person {
private:
    std::string person_name;
    std::string person_surname;
    
public:
    person(std::string name, std::string surname)
    : person_name(std::move(name)), person_surname(std::move(surname)) {}
};

void createPerson() {
    std::string name = "Alex";
    std::string surname = "Johns";
    person great_guy(name, surname);
}
```

C++에는 [`std::string_view`](https://en.cppreference.com/w/cpp/string/basic_string_view)라는 특수한 타입이 있습니다. 이것은 문자열을 소유하지 않고 문자열에 대한 뷰만 제공하는 타입으로, 문자열 자체를 저장하지 않고 문자열의 포인터만을 가집니다. 함수나 컨테이너에 문자열을 전달할 때, 복사 없이 변경할 계획이 없을 때 매우 편리하며, 부분 문자열을 얻고자 할 때도 유용합니다.

```cpp
std::string input1 = {"mindyourlegs"};
std::string input2 = {"whenusingcpp"};
std::vector<std::string_view> inputs {input1, input2};

std::vector<std::string_view> substrings;
for (std::size_t i = 0; i < inputs.size(); ++i) {
    const auto & string = inputs[i];
    for (std::size_t j = 0; j < string.size() - 2; ++j) {
        substrings.emplace_back(string.data() + j, 3);
    }
}
for (std::size_t i = 0; i < substrings.size(); ++i) {
    std::cout << substrings[i] << '\n';
}
```

`std::string_view`에서 `std::string`으로의 암시적 변환은 지원하지 않는 점에 유의하세요. `std::string_view`로부터 `std::string`을 생성하려면 다음과 같이 할 수 있습니다:
```cpp 
std::string_view sv = "Hello, World!";
std::string str {sv};
```
또는,
```cpp
static_cast<std::string>(your_sv_object)
```
처럼 형변환을 사용할 수 있습니다.

또한, `std::string_view` 객체는 포인터와 크기 등 소규모 데이터만으로 구성되어 있으므로 값으로 전달하는 것이 더 좋습니다. 이에 대한 자세한 설명은 [여기](https://quuxplusone.github.io/blog/2021/11/09/pass-string-view-by-value/)를 참고하세요.

`std::string`의 주요 메서드는 다음과 같습니다:
* `size()` — 문자열의 크기를 반환합니다
* `empty()` — 문자열이 비어 있으면 `true`를 반환합니다
* `clear()` — 문자열을 초기화(비움)합니다
* `push_back()` — 문자열의 끝에 문자를 추가합니다
* `pop_back()` — 문자열의 마지막 문자를 제거합니다
* `replace()` — 지정 위치의 문자를 대체합니다
* `substr()` — 문자열의 부분 문자열을 반환합니다
* `find()` — 문자열 내 부분 문자열을 찾습니다

`std::vector`와 마찬가지로, `std::string`도 지정 위치에 문자를 삽입하거나 삭제(erase)하는 메서드를 제공합니다. 하지만 이러한 연산은 비효율적일 수 있습니다. 이 메서드들은 선형 복잡도를 가지므로 가능하다면 사용을 피하는 것이 좋습니다.
* `insert()` — 지정 위치에 문자를 삽입하거나, 부분 문자열을 삽입할 수 있습니다.
* `erase()` — 지정 위치의 문자 또는 부분 문자열을 삭제합니다.

여러분의 과제는 입력 문자열이 팰린드롬인지 검사하는 프로그램을 구현하는 것입니다. 팰린드롬은 공백, 구두점, 대소문자를 무시하고 앞뒤로 동일하게 읽을 수 있는 단어, 숫자, 구문, 기타 문자 시퀀스를 말합니다.

`preprocess` 함수는 입력 문자열의 전처리를 담당하도록 구현하는 것이 좋습니다. 전처리를 통해 팰린드롬 판별이 더 쉬워집니다.

`isPalindrome` 함수는 입력 문자열이 팰린드롬이라면 `true`를, 아니라면 `false`를 반환해야 합니다.