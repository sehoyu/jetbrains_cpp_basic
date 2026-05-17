[C++ 이동 의미론](https://en.cppreference.com/w/cpp/language/move_constructor)은 객체의 복사 없이 소유권을 효율적으로 이전할 수 있는 기능입니다. 이는 성능을 향상시키고 불필요한 메모리 할당을 피하는 데 유용합니다. 이동 의미론의 세부 사항을 살펴보기 전에 [값 범주](https://en.cppreference.com/w/cpp/language/value_category)의 개념을 간단히 이해해 봅시다.

* __lvalue__ 표현식은 이름이나 식별자가 있는 객체를 나타냅니다.  
  메모리에 존재하며 일반적으로 단일 표현을 넘어 지속됩니다.  
  보통 할당 연산자(`=`)의 왼쪽에 위치하기 때문에 __lvalue__라는 이름이 붙었습니다.  

* __rvalue__ 표현식은 임시 또는 임의로 처리 가능한 값을 나타냅니다.  
  보통 이름이 붙은 메모리 위치를 가지지 않는 특정 계산의 중간 결과입니다.  
  일반적으로 할당 연산자(`=`)의 오른쪽에 위치하기 때문에 __rvalue__라는 이름이 붙었습니다.  

예를 들어, 아래에서 변수 `a`, `b`, 그리고 `c`는 lvalue이고,  
표현식 `a + b`는 rvalue입니다.

```c++
int a = 2;
int b = 3;
int c = a + b;
```

이동 의미론은 rvalues를 활용합니다.  
rvalues는 임시 객체 또는 삭제 예정인 객체를 나타냅니다.  
다른 객체가 삭제 예정인 rvalue 객체를 복사하고자 할 때,  
실제 복사 대신, rvalue 객체의 내용을 이동할 수 있습니다.

예를 들어, `int_array` 클래스와  
사용자가 정의한 복사 생성자가 있다고 가정합시다  
(파일 `include/int_array.hpp` 참고):

```c++
class int_array {
public:
    /* ... */
    int_array(const int_array& other) 
        : data_(new int[other.size_])
        , size_(other.size_) 
    {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    };
    /* ... */
private:
    int* data_;
    size_t size_;
};
```

특정 값을 채운 배열을 생성하는 함수가 있다고 합시다:

```c++
int_array create_array(int value, size_t size) {
    if (size == 0) {
        return int_array();
    }
    int_array array = int_array(size);
    for (size_t i = 0; i < size; ++i) {
        array[i] = value;
    }
    return array;
}
```

그리고 이 함수가 다음과 같이 호출됩니다:

```c++
// 복사 생성자가 여기에서 호출됩니다 (!)
int_array a = create_array(0, 4);
```

위 코드에서는 불필요한 복사가 발생합니다.  
이는 함수에서 반환된 객체에서  
새로 생성된 객체로 배열을 복사합니다.

그러나 반환된 객체는 실제로 삭제될 예정인  
임시 rvalue이기 때문에,  
이를 이용해 배열을 복사하는 대신,  
포인터를 _이동_만 하면 됩니다.

이를 위해 복사 생성자에 추가하여,  
rvalue 참조(`&&`)를 인수로 받는 _이동 생성자_를 정의할 수 있습니다:

```c++
class int_array {
public:
    /* ... */
    int_array(int_array&& other) 
        : data_(other.data_)
        , size_(other.size_) 
    {
        other.data_ = nullptr;
        other.size_ = 0;
    };
    /* ... */
private:
    int* data_;
    size_t size_;
};
```

`int_array` 클래스의 이동 생성자는  
포인터를 복사하는 것 외에도  
rvalue 참조로 전달된 원래 객체의 포인터를  
널로 설정합니다.  
이는 원래 객체의 소멸자가 호출될 때,  
`data` 필드가 가리키는 메모리를 해제하지 않도록 하기 위함입니다.  
이렇게 구현된 이동 생성자는  
소유권 이전이 발생함을 반영합니다.

복사 할당 연산자와 유사하게,  
클래스에 대해 이동 할당 연산자도 정의할 수 있습니다:

```c++
class int_array {
public:
    /* ... */
    int_array& operator=(int_array&& other) {
        // ...
    }
    /* ... */
private:
    int *data;
    std::size_t size;
};
```

이동 할당 연산자와 표준 함수 `std::move`를 사용하면  
다른 객체에서 소유권을 수동으로 이전할 수 있습니다:

```c++
int_array b = create_array(1, 4);
int_array c = create_array(2, 4);
// 소유권 이전
b = std::move(c);
```

<div class="hint">

기술적으로, `std::move` 함수는 lvalue를 rvalue 참조로 변환합니다.

</div>

이동 할당 연산자의 사용자 정의 구현은  
이동된 후 객체가 유효한 상태를 유지하도록  
보장해야 합니다.  
보통 이는 null 상태의 일부 형태를 뜻합니다.  
즉, 객체를 안전하게 소멸시킬 수는 있지만,  
메서드 호출이나 연산자 사용 등의 다른 작업은  
정의되지 않은 동작을 초래할 수 있습니다.  
일반적으로 객체가 이동된 후에는  
새 값을 할당하거나 소멸시키는 것을 제외하고  
사용을 피하세요.

스마트 포인터 `std::unique_ptr`도  
이동 의미론을 지원합니다.  
이 클래스의 이동 의미론은 객체의 소유권을  
소스 `std::unique_ptr`에서 대상 포인터로 이전합니다.  
소스 `std::unique_ptr`은  
null 상태로 남게 됩니다.

```c++
std::unique_ptr<Dog> p1 = std::make_unique<Dog>("Beethoven");
std::unique_ptr<Dog> p2;
// 소유권을 p1에서 p2로 이전합니다.
p2 = std::move(p1);
// p1은 이제 null 상태입니다.
assert(p1 == nullptr);
// p2는 이제 Dog 객체를 소유합니다.
assert(p2 != nullptr);