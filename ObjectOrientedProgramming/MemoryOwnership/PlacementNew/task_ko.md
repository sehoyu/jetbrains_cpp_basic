`placement new` 연산자는 `new` 연산자의 특별한 버전입니다.  
이 연산자를 사용하면 미리 할당된 메모리 영역에서 객체를 생성할 수 있습니다.  
이는 메모리 단편화를 줄이고 성능을 향상시키는 등 다양한 상황에서 유용합니다.

`placement new` 연산자를 사용하려면,  
먼저 적절한 크기의 메모리 영역을 할당해야 합니다.  
그런 다음, 이 메모리 영역을 `placement new` 연산자에 전달해야 합니다.  
연산자는 전달받은 메모리 영역 내에서 지정된 타입의 객체를 생성합니다.

`placement new` 연산자를 사용해 생성된 객체가 더 이상 필요 없을 때는  
소멸자를 명시적으로 호출하여 객체를 삭제해야 합니다.  
배열을 사용하는 경우, 배열의 각 객체에 대해 소멸자를 호출해야 합니다.

다음은 `placement new` 연산자를 사용하여  
미리 할당된 메모리 영역에 정수 객체를 생성하는 예제입니다:

```cpp
#include <new>

class Cat {
public:
    explicit Cat(const std::string& name) { /* ... */ }
    ~Cat() { ... }
    std::string getName() { /* ... */ } 
    /* ... */
};

int main() {
  // 적절한 크기의 메모리 영역을 할당합니다.
  char buffer[sizeof(Cat)];

  // 지정된 메모리 영역에 Cat 객체를 생성합니다.
  Cat* cat = new (buffer) Cat("Garfield");

  // 객체에 접근합니다.
  std::cout << cat->getName(); << std::endl;

  // 객체를 소멸시킵니다.
  cat->~Cat();

  return 0;
}
```

`placement new` 연산자를 사용하면 여러 객체의 생존 기간을  
동일한 저장 기간 내에 맞출 수 있습니다.  
예를 들어, 메모리 영역을 재사용하여 새 객체를 생성하면,  
이전 객체의 생존 기간은 종료되고 새 객체의 생존 기간이 시작됩니다.  
그러나 메모리 영역의 저장 기간은 동일하게 유지됩니다.

이 작업을 완료하기 위해 다음 함수를 구현하세요.

`createCat` 함수는 주어진 메모리 블록에 이름이 `"Tom"`인 `Cat` 객체를 생성해야 합니다:

```c++
Cat* createCat(char* memory);
```

`destroyCat` 함수는 주어진 메모리 블록에 위치한 `Cat` 객체를 삭제해야 합니다:

```c++
void destroyCat(char* memory);
```

`createMouse` 함수는 주어진 메모리 블록에 이름이 `"Jerry"`인 `Mouse` 객체를 생성해야 합니다:

```c++
Mouse* createMouse(char* memory);
```

`destroyMouse` 함수는 주어진 메모리 블록에 위치한 `Cat` 객체를 삭제해야 합니다:

```c++
void destroyMouse(char* memory);