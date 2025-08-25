// Lv0, C++, 옹알이 (1)

/*
    1. 문제 요약
        - 입력 : vector<string>, babbling (문자열 배열)
        - 출력 : int, 문자열 배열 내, 발음할 수 있는 문자열 원소의 개수
        - 핵심 요구사항 : 문자열 배열의 각 원소가 주어진 옹알이로만 구성되어있는지 판정하고 원소 개수 개수 세기

    2. 조건/제약
        - 입력 크기 : 문자열 배열 길이 100 이하, 문자열 배열 내 원소 최대 길이 15글자
        - 시간 제한 : 없음
        - 특이 제약 : 문자열 배열 내 원소에는 옹알이가 중복돼서 나타나지 않음

    3. 핵심 규칙 / 판단 기준
        - 주어진 옹알이 {"aya","ye","woo","ma"}
        - 판단 절차
            1. babbling을 문자열 원소별(for)로 따지기 시작
                1-1. 문자열 원소가 2글자 미만 -> 불가능 (break)
                1-2. 문자열 원소가 2글자 -> 2개짜리 옹알이랑 맞는지 확인
                1-3. 문자열 원소가 3글자 -> 3개짜리 옹알이랑 맞는지 확인
                1-4. 문자열 원소가 4글자 이상 -> 문자열 원소가 0글자가 될 때까지 따져보기 (while)
                    1-4-1. 문자열 원소를 2개로 자름
                        -> 2개짜리 옹알이랑 맞는지 확인
                        -> 1-4-1-1. 맞으면
                            -> 맞게 판단된 문자열 2개 없애기
                            -> 문자열 & 문자열 길이 새로 업데이트
                            -> 다음 문자들 따지러 가기 시작 (continue)
                        -> 1-4-1-2. 안맞으면
                            -> 문자열 원소를 3개로 잘랐을 때는 맞는게 있는지 확인하러 감
                    1-4-2. 문자열 원소를 3개로 자름
                        -> 3개짜리 옹알이랑 맞는지 확인
                        -> 1-4-2-1. 맞으면
                            -> 맞게 판단된 문자열 3개 없애기
                            -> 문자열 & 문자열 길이 새로 업데이트
                            -> 다음 문자들 따지러 가기 시작 (continue)
                        -> 1-4-2-2. 안맞으면
                            -> 지금 따져보는 문자열 원소는 옹알이로 발음하지 못함
                            -> 다음 문자열 원소로 넘어감 (break)
                1-5. 계속 잘린 결과, 문자열 길이 최종 == 0 -> 발음할 수 있는 단어로 판단
            2. 카운트 최종 반환
*/

#include <string>
#include <vector>
using namespace std;

int solution(vector<string> babbling) {
    int answer = 0;

    for (int i = 0; i < (int)babbling.size(); i++) {

        string word = babbling[i];
        int word_len = (int)word.size();

        switch (word_len) {
            case 1:
                break;

            case 2:
                if (word == "ye" || word == "ma") answer += 1;
                break;

            case 3:
                if (word == "aya" || word == "woo") answer += 1;
                break;

            default: {
                string tmp_word = word;
                int tmp_word_len = word_len;
                string prev = "";  // 직전 음절 (연속 사용 금지)

                while (tmp_word_len) {

                    // 먼저 2글자 체크
                    string tmp_sliced_word = tmp_word.substr(0, 2);
                    if ((tmp_sliced_word == "ye" || tmp_sliced_word == "ma") && tmp_sliced_word != prev) {
                        prev = tmp_sliced_word;
                        tmp_word = tmp_word.substr(2);
                        tmp_word_len = (int)tmp_word.size();
                        continue;
                    }

                    // 3글자 체크
                    tmp_sliced_word = tmp_word.substr(0, 3);
                    if ((tmp_sliced_word == "aya" || tmp_sliced_word == "woo") && tmp_sliced_word != prev) {
                        prev = tmp_sliced_word;
                        tmp_word = tmp_word.substr(3);
                        tmp_word_len = (int)tmp_word.size();
                        continue;
                    }

                    // 어느 쪽도 매칭 실패 → 탈출
                    break;
                }

                // 모두 잘 잘렸다면 유효 단어
                if (tmp_word_len == 0) answer += 1;
                break;
            }
        }
    }

    return answer;
}
