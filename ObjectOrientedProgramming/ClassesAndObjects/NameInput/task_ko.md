플레이어가 적과 충돌하면 게임이 종료되고, 새로운 장면이 나타나야 합니다. 이 장면에서 플레이어는 자신의 이름을 입력하고 리더보드를 볼 수 있습니다. 이름은 키보드를 사용해 입력해야 하며, 영문자와 숫자만 허용됩니다. 닉네임의 최대 길이는 16자입니다.

`LeaderboardScene` 클래스는 두 가지 상태를 가집니다: `INSERTNAME`과 `SHOWLEADERBOARD`. 게임이 종료되면 상태는 자동으로 `INSERTNAME`으로 설정됩니다. 플레이어가 이름을 입력하면 상태는 `SHOWLEADERBOARD`로 변경되어야 합니다.
이 논리는 `processEvent` 함수에서 처리됩니다. 모든 입력은 `INSERTNAME` 상태에서만 처리됩니다. 다음 세 가지 상황을 관리해야 합니다:
 - 문자가 입력된 경우(`event.type == sf::Event::TextEntered`), 해당 문자가 규칙을 준수하는지 확인해야 합니다. 유효하다면, 닉네임의 길이가 16자 미만인 경우 이름에 추가합니다.
 - 백스페이스 키가 눌린 경우(`event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace`), 이름에서 마지막 문자를 제거합니다.
 - 엔터 키가 눌린 경우(`event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter`), 상태를 `SHOWLEADERBOARD`로 변경하고, `Leaderboard` 클래스의 `updateScore(score, name)` 함수를 호출해야 합니다. 이 기능은 다음 과제에서 구현할 예정입니다.

`processEvent` 함수는 이미 구현되어 있으며, 이 함수는 `processText`, `processBackspace`, `processEnter` 함수를 호출합니다. 여러분은 이 함수들을 구현해야 합니다.