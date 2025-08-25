# 250820_PCCE_4.cpp
## C++ 문자열 리터럴 접미사 `s`

### 1. 의미
- `"..."s` 는 **C++14 이후** 도입된 **문자열 리터럴 접미사**
- `std::string{"..."}` 과 동일하게 동작  
- 예: `"_eye"s` → `std::string("_eye")`

### 2. 왜 사용하는가?
- **std::string 타입으로 강제 변환** → `std::string`끼리의 비교 보장
- `"skin"` (const char*)와 달리 의도를 명확히 표현
- `sv`(string_view) 같은 다른 접미사와 함께 가독성 향상

### 3. 사용 조건
```cpp
#include <string>
using namespace std::string_literals;
// 또는
using namespace std::literals;
```

### 4. 비교 예시
```cpp
// 동작은 같음
if (last_four == "skin")   { ... }   // const char* 과 std::string 비교
if (last_four == "skin"s)  { ... }   // std::string 과 std::string 비교
```

### 5. 안전한 코드 예시
```cpp
#include <iostream>
#include <string>
using namespace std;
using namespace std::string_literals;

int main() {
    string code;
    cin >> code;

    if (code.size() < 4) {
        cout << "direct recommendation";
        return 0;
    }

    string last_four = code.substr(code.size() - 4, 4);

    if (last_four == "_eye"s) {
        cout << "Ophthalmologyc";
    } else if (last_four == "head"s) {
        cout << "Neurosurgery";
    } else if (last_four == "infl"s) {
        cout << "Orthopedics";
    } else if (last_four == "skin"s) {
        cout << "Dermatology";
    } else {
        cout << "direct recommendation";
    }
}
```
# 250820_PCCE_5.cpp
## C++ `<vector>` 헤더파일 정리

### 1. `std::vector`란?

-   일반 배열(`int arr[10]`)은 크기가 고정되어 있지만, `std::vector`는 **크기를 자동으로 늘리거나 줄일 수 있는 가변 배열**임
-   내부적으로는 연속된 메모리를 사용하기 때문에 **빠른 인덱스 접근**이 가능하고, 필요할 때 자동으로 더 큰 메모리 공간을 할당해서 확장함

------------------------------------------------------------------------

### 2. 기본 문법

``` cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // 정수형 벡터 선언
    vector<int> v;

    // 원소 추가
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    // 크기 확인
    cout << "크기: " << v.size() << endl;

    // 인덱스 접근
    cout << "첫 번째 원소: " << v[0] << endl;

    // 반복문 순회
    for (int x : v) {
        cout << x << " ";
    }
}
```

------------------------------------------------------------------------

### 3. 주요 기능

  함수/연산        설명
  ---------------- -------------------------------------------
  `push_back(x)`   맨 뒤에 원소 추가
  `pop_back()`     맨 뒤 원소 제거
  `size()`         현재 원소 개수
  `empty()`        비어있는지 확인
  `clear()`        모든 원소 삭제
  `[]` 연산자      인덱스로 원소 접근 (빠름)
  `at(i)`          인덱스로 원소 접근 (범위 검사 포함, 안전)
  `front()`        첫 번째 원소
  `back()`         마지막 원소
  `insert()`       특정 위치에 원소 삽입
  `erase()`        특정 위치 원소 제거

------------------------------------------------------------------------

### 4. 장단점

✅ 장점  
- 동적 크기 관리 → 배열처럼 크기 신경 안써도 됨
- 인덱스 접근이 빠름 (O(1))
- STL 알고리즘들과 호환성이 좋음

⚠️ 단점  
- 중간 삽입/삭제는 느림 (O(N), 뒤에서만 빠름)
- 크기를 늘릴 때는 내부적으로 새 메모리를 할당하고 복사해야 해서 성능이 순간적으로 떨어질 수 있음

------------------------------------------------------------------------

### 5. 자주 쓰이는 패턴

``` cpp
// 초기 크기 지정 및 초기화
vector<int> v1(5);        // 크기 5, 값은 0
vector<int> v2(5, 42);    // 크기 5, 모두 42

// 2차원 벡터
vector<vector<int>> grid(3, vector<int>(4, 0));
// 3x4 행렬 (모두 0으로 초기화)

// 정렬
sort(v.begin(), v.end());
```

------------------------------------------------------------------------

👉 요약:
- `<vector>`는 **크기 조절이 자유로운 배열**을 제공하는 C++ 표준 컨테이너  
- 코딩테스트나 실무에서 가장 많이 쓰이는 STL 중 하나  

# 250820_PCCE_6.cpp
## C++ 정수 나눗셈과 퍼센트 계산 주의점

### 1. 문제 상황
```cpp
usage *= (1 + change[i] / 100);
```

- `change[i] / 100` 은 **정수 나눗셈**이라, `change[i] < 100`이면 항상 0이 됨
- 따라서 `(1 + 0) = 1` → `usage` 값이 변하지 않음 ❌

---

### 2. 다른 풀이가 된 이유
```cpp
usage += usage * change[i] / 100;
```

- 곱셈이 먼저 수행되므로 `(usage * change[i]) / 100` 결과가 살아남음
- 예: `usage = 200`, `change[i] = 10`  
  → `200 * 10 / 100 = 20`  
  → 최종 `usage = 220` ✅
- 하지만 여전히 정수 나눗셈이라 `(usage * change[i]) < 100` 이면 0으로 잘려 손실 발생

---

### 3. 내가 제출한 풀이 (실수 캐스팅)
```cpp
#include <string>
#include <vector>
using namespace std;

int solution(int storage, int usage, vector<int> change) {
    int total_usage = 0;
    for (int i = 0; i < change.size(); i++) {
        usage *= (1 + double(change[i]) / 100); // 실수 연산
        total_usage += usage;
        if (total_usage > storage) {
            return i;
        }
    }
    return -1;
}
```

- `(double)change[i] / 100` 을 통해 **실수 나눗셈**으로 변환
- 손실 없는 정확한 퍼센트 연산 가능
- 문제에서 요구하는 정수 리턴은 그대로 유지

---

### 4. 비교 요약
| 방식                           | 특징 | 문제점 |
|--------------------------------|------|--------|
| `usage *= (1 + change[i] / 100)` | 단순하지만 정수 나눗셈 → 변화 없음 | 잘못된 결과 |
| `usage += usage * change[i] / 100` | 곱셈 후 나눗셈이라 큰 값은 반영됨 | 작은 값은 0으로 소실 |
| `usage *= (1 + double(change[i]) / 100)` | 실수 연산으로 정확한 비율 반영 | 가장 안정적 ✅ |

---

👉 정리:  
- 퍼센트 연산은 **실수 변환**을 반드시 해주는 것이 안전하다.  
- 정수만 사용하면 작은 변화율이 반영되지 않을 수 있다.  
- 최종적으로는 `double` 캐스팅 방식이 정석 풀이.

# 250825_옹알이_(1).cpp
## C++ 문자열 & 벡터 관련 정리

### 1. `continue`와 `break` 차이
- `continue`  
  - 현재 반복문의 **나머지 부분 건너뛰고** 다음 반복 조건 검사로 이동  
  - 조건문을 무시하는 게 아니라, 조건이 참일 때 실행되면 **그 아래 코드만 생략**됨  
- `break`  
  - **현재 반복문 전체를 탈출**  
  - 바깥 반복문이나 함수까지는 나가지 않음  
- `return`  
  - 현재 함수 전체 종료  

```cpp
for (int i=0; i<5; i++) {
    if (i == 2) continue; // 2 건너뜀
    if (i == 4) break;    // 반복문 종료
    cout << i << " ";
}
// 출력: 0 1 3
```
### 2. 문자열 비교 방법
* `std::string`
    * ==, != 연산자 사용 가능
    * 내부적으로는 string::compare() 호출
```
string a = "hello", b = "world";
if (a == "hello") { ... }
if (a != b) { ... }
```
* C 스타일 문자열 (`char*`)
`strcmp(a, b) == 0` 이어야 같음 (`<cstring>` 필요)

```
const char* a = "hi";
const char* b = "hi";
if (strcmp(a, b) == 0) cout << "same";
```
### 3. 문자열 vs 벡터 혼동 문제
* 실수: `vector<string> word = babbling[i];`
* `b`abbling[i]`는 string인데, `vector<string>`에 대입 → 타입 불일치 에러
* 해결: `string word = babbling[i];`
* 실수: `tmp_word.substr(...)` 호출 시 `tmp_word`를 `vector<string>`로 선언함
    * substr는 string 전용 메서드
* 해결: `tmp_word`를 `string`으로 선언

### 4. substr 동작
* `substr(pos, len)`
    * pos에서 시작해서 최대 len 길이 문자열 반환
    * 남은 길이가 len보다 짧으면 가능한 만큼 반환
    * 단, pos > size()면 예외 발생

```
string s = "hello";
cout << s.substr(0,2); // "he"
cout << s.substr(2,3); // "llo"
cout << s.substr(4,5); // "o"
```

### 5. 매칭 실패 처리 로직
* while 내부에서 2글자, 3글자 모두 매칭 실패 시 → break → while문 탈출

* 탈출 후 tmp_word_len == 0 검증 필요
    * 0 → 유효 단어
    * 0 아님 → 잘 안 잘린 남은 글자가 있으므로 invalid
# 250825_PCCE_6.cpp
## vector 자료형에서 마지막 원소 가져오기
* `a.back()` 같이 가져오면 됨