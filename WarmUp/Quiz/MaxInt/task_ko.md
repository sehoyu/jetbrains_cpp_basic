두 정수 중 더 큰 값을 반환하는 함수를 구현하세요.

```c++
int maxInt(int a, int b);
```

예를 들어, `maxInt(-1, 5)`는 5를 반환해야 합니다.

이 작업을 완료하려면 아래 힌트에서 설명된 조건 연산자를 사용하는 것이 편리할 수 있습니다.

<div class="hint">

조건문인 `if` 문 외에도 C++ 언어에는 [_삼항 조건 연산자_](https://en.cppreference.com/w/cpp/language/operator_other#Conditional_operator) `?:`가 있으며, 이를 표현식으로 사용할 수 있습니다.

식 `b ? t : e`는 다음과 같이 평가됩니다:
* `b`가 `true`(또는 0이 아닌 정수 값)로 평가되면 `t`,
* `b`가 `false`(또는 0 정수 값)로 평가되면 `e`.

</div>