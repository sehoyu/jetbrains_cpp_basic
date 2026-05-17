C++에서 입출력(I/O) 연산은 스트림을 사용하여 수행합니다. 스트림이란, 소스(예: 키보드, 파일, 네트워크 연결)에서 목적지(예: 화면, 파일, 네트워크 연결)로 흐르는 바이트의 연속입니다. C++ 표준 라이브러리는 I/O 연산을 수행하기 위한 여러 클래스를 제공합니다. 관련 클래스의 계층 구조는 [여기](https://en.cppreference.com/w/cpp/io#Hierarchy)에서 확인할 수 있습니다.

가장 기본이 되는 스트림 타입은 입력 스트림 타입인 `istream`과 출력 스트림 타입인 `ostream`이며, 각각 `std::cin`과 `std::cout` 함수가 이에 해당합니다. `istream` 타입은 입력을 위한 `>>` 연산자가 오버로드되어 있고, `ostream` 타입은 출력을 위한 `<<` 연산자가 오버로드되어 있습니다.

```cpp
// 표준 출력(콘솔)
std::cout << "Hello, World!" << std::endl;

// 표준 입력(콘솔)
int inputNumber;
std::cout << "Enter a number: ";
std::cin >> inputNumber;
std::cout << "You entered: " << inputNumber << std::endl;
```

콘솔 입출력 외에도, C++에서는 파일 입출력을 처리하기 위해 `fstream` 라이브러리를 제공합니다. 파일에 대한 입력 및 출력은 각각 `ifstream`(입력 파일 스트림)과 `ofstream`(출력 파일 스트림)을 사용하여 구현합니다. 이 클래스들은 각각 `istream`과 `ostream`에서 파생되어 있습니다.
아래는 파일에 데이터를 쓰고 읽는 간단한 예시입니다:

```cpp
std::string inputFile = "input.txt";
std::string outputFile = "output.txt";

// 파일에 쓰기
std::ofstream outFile(outputFile);
if (outFile.is_open()) {
    outFile << "Hello, File!" << std::endl;
    outFile.close();
}

// 파일에서 읽기
std::ifstream inFile(inputFile);
std::string line;
if (inFile.is_open()) {
    while (getline(inFile, line)) {
        std::cout << line << '\n';
    }
    inFile.close();
}
```

파일에 접근하기 위해서는 파일이 프로그램과 동일한 디렉터리에 있거나, 파일의 전체 경로를 지정해주어야 한다는 점에 유의하세요.

또 다른 중요한 스트림 타입으로는 `stringstream`이 있습니다. 이는 메모리 기반 문자열에서 입출력 연산을 가능하게 해주며, 텍스트를 파싱하거나 포맷팅할 때 유용하게 사용할 수 있습니다. 다음은 `stringstream`의 사용 예시입니다:

```cpp
    std::string inputString = "Hello, World!";
    std::istringstream inputStream(inputString);
    std::string word;

    while (inputStream >> word) {
        std::cout << word << std::endl;
    }
    
    std::ostringstream outputStream;
    outputStream << "Hello, World!" << std::endl;

    std::cout << outputStream.str();
```

또한, 표준 라이브러리는 I/O 오류를 확인하고 처리하기 위한 여러 메서드를 제공합니다. 예를 들면, `fail()`, `bad()`, `eof()`, `good()`과 같은 함수가 있습니다. 이 메서드들은 스트림의 상태를 확인하거나 오류 플래그를 초기화하는 데 사용할 수 있습니다.

각 스트림에는 *failbit*, *badbit*, *eofbit*, *goodbit*와 같은 상태 비트가 있습니다. 스트림의 상태를 확인할 때 이 비트들을 사용할 수 있습니다. *failbit*는 문자 시퀀스를 유효한 값으로 변환하지 못하는 등, 치명적이지 않은 I/O 오류가 발생하면 설정됩니다. *badbit*는 디스크 공간 부족으로 파일 쓰기 실패와 같이 치명적인 I/O 오류가 발생하면 설정됩니다. *eofbit*는 입력 연산이 입력 시퀀스의 끝에 도달했을 때 설정됩니다. *goodbit*는 다른 비트가 하나도 설정되지 않은 경우를 의미합니다.
다음은 스트림의 상태를 확인하는 방법입니다:

```cpp
std::ifstream file("input.txt");
if (file.good()) {
    std::cout << "File opened successfully" << std::endl;
} else {
    if (file.eof()) {
        std::cout << "End of file reached" << std::endl;
    } else if (file.fail()) {
        std::cout << "Non-fatal I/O error" << std::endl;
    } else if (file.bad()) {
        std::cout << "Fatal I/O error" << std::endl;
    }
}
```

스트림 상태를 확인하는 것 외에도, `clear()` 함수를 사용하여 오류 상태 플래그를 초기화하거나 `setstate()` 함수로 플래그를 설정할 수 있습니다.

__스트림 조정자(Stream Manipulator)__ 는 스트림의 동작을 수정하는 특별한 함수입니다. 예를 들어, `std::endl`은 개행 문자를 삽입하고 출력 버퍼를 비우는 조정자입니다. 출력 폭을 설정하는 `std::setw`, 부동 소수점 숫자의 정밀도를 지정하는 `std::setprecision`, 소수점 고정 표기법을 설정하는 `std::fixed` 등의 조정자를 사용할 수도 있습니다. 모든 조정자 목록은 [여기](https://en.cppreference.com/w/cpp/io/manip)에서 확인할 수 있습니다.

아래는 몇 가지 예시입니다:
```cpp
std::cout << std::setw(10) << std::left << "Top left" << std::setw(26) << std::right << "Top right" << std::endl;
std::cout << std::setw(10) << std::left << "Bottom left" << std::setw(25) << std::right << "Bottom right" << std::endl;

std::cout << std::fixed << std::setprecision(3) << M_PI << std::endl;
std::cout << std::scientific << std::setprecision(10) << M_PI << std::endl;

std::cout << std::hex << 123456 << std::endl;
std::cout << std::oct << 123456 << std::endl;
std::cout << std::dec << 123456 << std::endl;
```

프로그램의 출력은 다음과 같습니다:
```
Top left                   Top right
Bottom left             Bottom right
3.142
3.1415926536e+00
1e240
361100
123456
```

모든 입력을 문자열 단위로 읽다가, "end"라는 문자열을 읽으면 입력을 멈추는 프로그램을 작성해야 합니다. 이후, 각 토큰에 대해 다음 형식으로 결과를 출력해야 합니다:

 - 숫자를 읽은 경우, "Got number: <number>"를 소수점 아래 3자리까지 출력합니다.
 - 숫자가 아닌 토큰을 읽은 경우, "Got string: <string>"을 출력합니다.
<div class="hint">
  입력을 파싱하고 토큰을 수집할 때 `stringstream`을 사용하는 것을 권장합니다. 이는 동적으로 문자열을 변경할 때 가장 효율적인 방법입니다.

  숫자는 숫자로만 이루어진 문자열이며, 맨 앞에 음수 부호와 소수점이 한 번 올 수 있습니다.
</div>

*이 모듈을 성공적으로 마치셨습니다! [Scoreboard](course://ObjectOrientedProgramming/ClassesAndObjects/Scoreboard) 과제로 돌아가 Planet Game에 새로운 기능을 추가해보시길 적극 권장합니다!*