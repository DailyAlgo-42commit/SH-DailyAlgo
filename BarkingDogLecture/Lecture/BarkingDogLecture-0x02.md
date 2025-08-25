# 0x02. 기초 코드 작성 요령 II

# 0x00 STL과 함수 인자

## 함수 인자

### 출력 예측해보기

1번

```cpp
void func(int a) {
	a = 5;
}
int main(void) {
	int t = 0;
	func(t);
	cout << t;
}
```

2번

```cpp
void func(int arr[]) {
	arr[0] = 10;
}

int main(void){
	int arr[3] = { 1, 2, 3 };
	func(arr);
	cout << arr[0];
}
```

3번

```cpp
struct pt {
	int x, y;
};

void func(pt, a) {
	a.x = 10;
}

int main(void) {
	pt tmp = { 0, 0 };
	func(tmp);
	cout << tmp.x;
}
```

- 풀이
    
    
    |  | 예상 | 실제 |
    | --- | --- | --- |
    | 1번 | 0 | 0 |
    | 2번 | 10 | 10 |
    | 3번 | 10 | **0** |

- 해설
    - 1번, 3번 : 변수와 구조체는 값이 **복사**됨 → 원본에 영향을 주지 않음
    - 2번 : 배열 이름 = 주소값 → 값이 바뀜

### 참조자(Reference)

- C++에는 C와 다르게 **참조자**라는 개념이 존재함
- 참조자를 사용하면…
    - 포인터로 넘겨줄 필요 없이 바로 원본에 접근이 가능함
    - 일반 변수 쓰듯이 사용할 수 있음
    - null 포인터에 값을 넣는다던지, 타입이 다른걸 멋대로 캐스팅하지 않게 해줌
- 참조자 사용 예시
    
    ```cpp
    void swap(int &a, int &b){
    	int tmp = a;
    	a = b;
    	b = tmp;
    }
    ```
    

## STL(Standard Template Library) - vector

- STL이란?
    - C++에서 제공하는 라이브러리
    - C++에는 미리 다양한 알고리즘과 자료구조가 STL에 구현되어 있음 → STL에서 가져와서 그냥 쓰면 됨
- vector STL
    - 배열과 비슷한 기능을 수행함
    - 일종의 가변배열로 크기를 마음대로 늘렸다 줄였다 할 수 있음
    - `<vector>`헤더에 선언되어있음
- vector STL 사용 예시
    
    ```cpp
    void func1(vector<int> v) {
    	v[10] = 7;
    }
    
    int main(void) {
    	vector<int> v(100); // 100칸짜리, 0으로 초기화된 vector를 만듦
    	func1(v);
    	cout << v[10];
    }
    ```
    
    - [Q] 위와 같은 경우 출력값은 어떻게 되는가? → [A] 0
        - STL도 구조체랑 비슷하게 함수 인자로 실어보내면 **복사본을 만들어서 보냄** → 원본에 영향을 주지 않음
- STL을 함수 인자에 넣으면 복사해서 보낸다
    
    ```cpp
    bool cmp1(vector<int> v1, vector<int> v2, int idx) {
    	return v1[idx] > v2[idx];
    }
    ```
    
    - 위의 코드의 시간복잡도는? $O(N)$
        - 함수 안에서는 연산을 딱 한 번만 하긴 함
        - but ! **원본으로부터 복사본을 만드는 비용이 듦** → 의도치 않게 시간복잡도가  $O(N)$이 됨
    - 해결 방법은? → **참조자** 활용
        
        ```cpp
        bool cmp2(vector<int> &v1, vector<int> &v2, int idx) {
        	return v1[idx] > v2[idx];
        }
        ```
        
        - 위와 같이 만들면 시간복잡도는 $O(1)$이 됨

# 0x01 표준 입출력

## `cin`/`cout`을 사용할 것

- 문자열 처리에는 `char*`보다는 C++ string이 월등하게 편한데, `scanf`/`printf`는 C++ string 처리가 안됨

## `cin` 사용시 주의할 점

- `scanf`든 `cin`이든 공백을 포함한 문자열을 입력받기 쉽지 않음
- `getline`을 사용을 추천
    - 사용 예시
        
        ```cpp
        string s;
        getline(cin, s);
        cout << s;
        ```
        

## `ios::sync_with_stdio(0)`, `cin.tie(0)` 사용하기

> `cin`/`cout`의 입출력으로 인한 시간초과를 막기 위해서 사용
> 

### `ios::sync_with_stdio(0)`

- `printf`와 `cout`의 동기화를 끊는 명령어
- 사용하면 `cout`과 `printf`를 섞어쓰면 안됨. 무조건 `cout` 사용
- Visual Studio 2017/2019에서는 `sync_with_stdio`를 그냥 무시하고 무조건 동기화를 유지하고 있음
→ 실습시에는 `ios::sync_with_stdio(0)`가 의미가 없을 수도 있음
- but! **채점서버는 gcc라서 차이가 생김**

### `cin.tie(0)`

- 온라인 저지 사이트에서는 채점을 할 때 그냥 출력 글자만 확인함
- cin 명령 수행 전에 cout 버퍼를 비울 필요가 없음

### 사용 예시

```cpp
#include <iostream>

using namespace std;

int main(void){
	std::ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n, x, t;
	...
}
```

## `endl` 쓰지 않기

- 줄바꿈이 필요하면 endl말고 그냥 개행문자 `\n`을 사용

# 0x02 코드 작성

## 코딩테스트 =! 개발

- 코딩테스트의 목표는 남이 알아볼 수 있는 클린코드를 작성하는 것이 아님
- 어떻게든 제한된 시간 안에 정답을 받아야 함
- 빠르게 짜는게 중요함

## 출력 맨 마지막에 공백/줄바꿈은 있어도 상관없음

## 디버거는 굳이 상용하지 않아도 됨