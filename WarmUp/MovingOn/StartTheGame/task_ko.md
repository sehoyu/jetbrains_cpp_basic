축하합니다! 이미 C++에서 변수를 정의하는 방법과 터미널을 통해 프로그램 사용자와 상호작용하는 방법을 배웠습니다.  
이번 레슨에서는 계속해서 C++ 언어를 공부하며 다음 주제를 배울 것입니다:

* 기본 제어 흐름 연산자: 조건문, switch문, 반복문.
* 배열 및 배열 요소에 대한 반복.  
* 사용자 정의 데이터 타입: 구조체와 열거형.  
* 함수를 사용한 프로그램 분해.  

이 개념들은 [SFML](https://www.sfml-dev.org/) 그래픽 라이브러리(Simple and Fast Multimedia Library)을 기반으로 한 간단한 2D 게임을 개발하며 배울 것입니다.  
하지만 먼저, 이 라이브러리를 시스템에 설치해야 합니다.  
시스템에 대한 설치 지침은 아래에서 확인해주세요.  
라이브러리를 설치한 후, 프로젝트를 다시 로드해야 할 수도 있습니다.  
이를 위해 __File | Reload CMake Project__를 선택하세요.  

라이브러리를 성공적으로 설치했는지 확인하려면, 이번 단계에 첨부된 프로그램을 실행하세요.  
새로운 응용 프로그램 창에 우주 공간에 떠 있는 작은 행성이 표시되어야 합니다!

게임을 실행하려면, `Loading CMake project` 작업이 완료될 때까지 기다린 후 오른쪽 상단에 위치한 초록색 삼각형 버튼인 `Run` 버튼을 누르세요.  
적절한 [실행 구성(run configuration)](https://www.jetbrains.com/help/clion/run-debug-configuration.html)이 선택되었는지 확인하세요.  
"WarmUp-MovingOn-StartTheGame-run" 실행 구성이 필요합니다.

### Windows

Windows에서는 별다른 작업이 필요 없습니다 —  
라이브러리는 이 과정과 함께 자동으로 설치될 것입니다.  
라이브러리는 CLion IDE에 [번들된](https://www.jetbrains.com/help/clion/quick-tutorial-on-configuring-clion-on-windows.html#MinGW) 컴파일러를 사용하여 시스템에서 소스 코드로부터 바로 빌드됩니다.  
소스를 다운로드하고 라이브러리를 빌드하는 스크립트가 과정에 포함되어 있습니다.  

### MacOS

MacOS에서는 [brew](https://brew.sh/) 패키지 관리자를 사용하여  
`sfml` 라이브러리를 설치하세요.

```shell
brew install sfml
```

### Ubuntu

Ubuntu에서는 [apt](https://ubuntu.com/server/docs/package-management) 패키지 관리자를 사용하여  
`libsfml-dev` 라이브러리를 설치하세요.

```shell
sudo apt install libsfml-dev
```

### 기타 Linux 배포판

사용 중인 배포판의 패키지 관리자를 사용하여 SFML 라이브러리를 설치하세요.