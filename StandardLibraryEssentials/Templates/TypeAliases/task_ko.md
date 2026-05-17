타입 별칭(type alias)은 C++에서 기존 타입에 새로운 이름을 지정할 수 있게 해주는 기능입니다. 이를 사용하면 복잡한 타입(예: 템플릿, 클래스, 함수가 네임스페이스 안에 깊이 중첩되어 있는 경우 등)을 다룰 때 코드가 보다 읽기 쉽고 이해하기 쉬워집니다. 타입 별칭은 `typedef`나 `using` 키워드를 이용해서 만들 수 있습니다.

`typedef` 키워드는 C++ 초기부터 존재해온 기능으로, 기존 타입에 새로운 이름을 부여할 때 사용됩니다. 문법은 다음과 같습니다: ```typedef <기존_타입_이름> <별칭_이름>;```. 아래는 `long long` 타입에 대한 타입 별칭을 생성하는 예시입니다:
```cpp
typedef long long ll;
ll x = 1'234'567'890'987'654'321;
```

`using` 키워드는 C++11에서 도입된 더 현대적인 타입 별칭 정의 방법입니다. 같은 목적을 지니지만, 문법이 더 간결하고 읽기 쉽습니다. 형식은 다음과 같습니다: ```using <별칭_이름> = <기존_타입_이름>;```. 다음은 `using`을 활용하여 `long long` 타입에 대한 별칭을 만드는 예입니다:
```cpp
using ll = long long;
ll x = 1'234'567'890'987'654'321;
```

뿐만 아니라, `using` 키워드는 템플릿의 타입 별칭을 만드는데도 활용할 수 있습니다. 이는 여러 개의 템플릿 매개변수를 가진 타입에 별칭을 만들고자 할 때 특히 유용합니다. 다음은 배열을 가리키는 `std::unique_ptr`에 대해 타입 별칭을 생성하는 예시입니다:
```cpp
template <typename T>
using unique_array = std::unique_ptr<T[]>;

unique_array<int> arr = std::make_unique<int[]>(10);
```

타입 별칭을 이용해 복잡한 타입에 읽기 쉬운 이름을 부여할 수도 있습니다. 예를 들어, 아래와 같이 복잡한 타입에 대한 별칭을 만들 수 있습니다:
```cpp
std::pair<std::pair<int, int>, std::pair<std::string, std::string>> complex_type;

// 타입 별칭 사용
using ComplexType = std::pair<std::pair<int, int>, std::pair<std::string, std::string>>;
ComplexType complex_type;