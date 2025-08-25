// Lv0, C++, 다음에 올 숫자

#include <string>
#include <vector>

using namespace std;

int solution(vector<int> common) {
    int answer = 0;

    int e1 = common[0], e2 = common[1], e3 = common[2];

    if ((e2 - e1) == (e3 - e2)){
        return common.back() + (e2-e1);
    }

    if((e2/e1) == (e3/e2)){
        return common.back() * (e2/e1);
    }

    return answer;
}