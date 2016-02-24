#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

#include "NemoLogic.h"

// input.txt 참고
void NemoLogic::input(istream &input) {
    input >> row_size >> col_size;
    input.ignore(1);

    row_hints.resize(row_size, vector<int>());
    for (int ri = 0; ri < row_size; ri++) {
        string line;
        getline(input, line);

        stringstream ss(line); int temp;
        while (ss >> temp) row_hints[ri].push_back(temp);
    }

    col_hints.resize(col_size, vector<int>());
    for (int ci = 0; ci < col_size; ci++) {
        string line;
        getline(input, line);

        stringstream ss(line); int temp;
        while (ss >> temp) col_hints[ci].push_back(temp);
    }

    board.resize(row_size, vector<int>(col_size));
}

void NemoLogic::output(ostream &output) {
    if (&output == &cout) {
        system("cls");
    }

    // margin_left : board 왼쪽 hint 부분의 너비
    // max_cnt_row_hints : 왼쪽의 hint 중에서 그 갯수가 가장 많은 것
    // left_max_digits : 왼쪽의 hint 중에서 자릿수가 가장 많은 것
    // max_cnt_col_hints : 위쪽의 hint 중에서 그 갯수가 가장 많은 것
    // top_max_digits : 위쪽의 hint 중에서 자릿수가 가장 많은 것
    int margin_left = 0, max_cnt_row_hints = 0, left_max_digits = 0;
    int max_cnt_col_hints = 0, top_max_digits = 0;

    for (int ri = 0; ri < row_size; ri++) {
        max_cnt_row_hints = max((int)row_hints[ri].size(), max_cnt_row_hints);
        for (int hi = 0; hi < row_hints[ri].size(); hi++) {
            left_max_digits = max((int)to_string(row_hints[ri][hi]).size(), left_max_digits);
        }
    }
    for (int ci = 0; ci < col_size; ci++) {
        max_cnt_col_hints = max((int)col_hints[ci].size(), max_cnt_col_hints);
        for (int hi = 0; hi < col_hints[ci].size(); hi++) {
            top_max_digits = max((int)to_string(col_hints[ci][hi]).size(), top_max_digits);
        }
    }

    margin_left = (left_max_digits + 1) * max_cnt_row_hints;

    // 위쪽의 힌트들을 출력
    for (int hi = 0; hi < max_cnt_col_hints; hi++) {
        output << setw(margin_left) << ' ';
        for (int ci = 0; ci < col_size; ci++) {
            output << setw(top_max_digits + 1);
            // 이번 행에서 출력해야 할 hint가 있을 때
            if (hi >= max_cnt_col_hints - col_hints[ci].size()) {
                output << col_hints[ci][hi - max_cnt_col_hints + col_hints[ci].size()];
            }
            else {
                output << ' ';
            }
        }
        output << endl;
    }

    for (int ri = 0; ri < row_size; ri++) {
        // 왼쪽의 힌트들을 출력
        for (int hi = 0; hi < max_cnt_row_hints; hi++) {
            output << setw(left_max_digits + 1);
            // 이번 열에서 출력해야 할 hint가 있을 때
            if (hi >= max_cnt_row_hints - row_hints[ri].size()) {
                output << row_hints[ri][hi - max_cnt_row_hints + row_hints[ri].size()];
            }
            else {
                output << ' ';
            }
        }

        // 현재 board의 상태 출력
        for (int ci = 0; ci < col_size; ci++) {
            output << setw(top_max_digits + 1);
            if (board[ri][ci] == 1) output << "■";
            else if (board[ri][ci] == -1) output << "Ⅹ";
            else output << "□";
        }

        output << endl;
    }
}

bool NemoLogic::solve(int ri, bool debug = false) {
    // 만들어온 board가 이상하면 false를 반환
    for (int ci = 0; ci < col_size; ci++)
        if (check_col(ci) == false) return false;
    if (ri == row_size)
        return true;

    // 과정 출력
    if (debug == true)
        output(cout);

    // 행을 전부 비우거나 전부 채우는 경우
    if (row_hints[ri].size() == 1) {
        if (row_hints[ri][0] == 0) {
            for (int ci = 0; ci < col_size; ci++)
                board[ri][ci] = -1;
            return solve(ri + 1, debug);
        }
        else if (row_hints[ri][0] == col_size) {
            for (int ci = 0; ci < col_size; ci++)
                board[ri][ci] = 1;
            return solve(ri + 1, debug);
        }
    }

    // hint들이 빈칸 하나씩만 끼고 딱 들어맞는 경우
    int hints_sum = sum(row_hints[ri]);
    if (hints_sum + row_hints[ri].size() - 1 == col_size) {
        // pos는 블록의 시작 위치
        int pos = 0;
        for (int rhi = 0; rhi < row_hints[ri].size(); rhi++) {
            // "■" 체크
            for (int ci = 0; ci < row_hints[ri][rhi]; ci++) {
                board[ri][pos + ci] = 1;
            }
            pos += row_hints[ri][rhi];

            // 마지막 블록 오른쪽의 빈칸은 처리하지 않음
            if (rhi == (int)row_hints[ri].size() - 1) continue;

            // "Ⅹ" 체크
            board[ri][pos] = -1;
            pos += 1;
        }
        return solve(ri + 1, debug);
    }

    // gap[i] 는 (i - 1)번째 블록 오른쪽 빈칸의 크기
    // => gap[i + 1] 는 i번째 블록 오른쪽 빈칸의 크기 
    vector<int> gap(row_hints[ri].size(), 1);
    gap[0] = 0; // 첫 블록 왼쪽 빈칸의 크기
    do {
        int pos = gap[0];
        // 처음 빈칸에 "Ⅹ" 체크
        for (int ci = 0; ci < gap[0]; ci++)
            board[ri][ci] = -1;
        // 미리 설정한 gap에 맞춰서 hint 블록들을 채워줌
        for (int rhi = 0; rhi < row_hints[ri].size(); rhi++) {
            // "■" 체크
            for (int ci = 0; ci < row_hints[ri][rhi]; ci++) {
                board[ri][pos + ci] = 1;
            }
            pos += row_hints[ri][rhi];

            // 마지막 블록 오른쪽의 빈칸은 처리하지 않음
            if (rhi == row_hints[ri].size() - 1) continue;

            // "Ⅹ" 체크
            for (int ci = 0; ci < gap[rhi + 1]; ci++) {
                board[ri][pos + ci] = -1;
            }
            pos += gap[rhi + 1];
        }
        // 오른쪽 나머지 빈칸에 "Ⅹ" 체크
        for (int ci = pos; ci < col_size; ci++) board[ri][ci] = -1;

        // 백트래킹 시도
        // 다음 단계에서 check_col로 옳고그름을 판별함
        // 탐색 중 한번이라도 true가 반환되면 연속해서 true를 반환함
        if (solve(ri + 1, debug) == true)
            return true;

        // 초기화
        for (int ci = 0; ci < col_size; ci++)
            board[ri][ci] = 0;

        // 다음 gap 으로 바꾸기
        // 자릿수 올림을 하듯이 맨 뒤부터 증가시킨다
        int gi = gap.size() - 1;
        gap[gi]++;
        while (hints_sum + sum(gap) > col_size && gi > 0) {
            gap[gi - 1]++;
            gap[gi] = 1;
            gi--;
        }

        // 모든 gap을 대입했는데도 답을 찾지 못 한다면 종료
    } while (hints_sum + sum(gap) <= col_size);

    // 답을 찾지 못 한 경우
    return false;
}

bool NemoLogic::check_col(int ci) {
    int run = 0, chi = 0;
    for (int ri = 0; ri < row_size; ri++) {
        if (board[ri][ci] == 1) {
            run++;
            // 더 이상 블록이 필요없는데 나타나거나, 블록이 필요 이상으로 큰 경우에 false
            if (chi >= (int)col_hints[ci].size() || run > col_hints[ci][chi])
                return false;
        }
        // 아직 판단할 수 없으면 일단 true를 반환해 solve 함수가 계속 돌 수 있도록 함
        else if (board[ri][ci] == 0) return true;
        else if (board[ri][ci] == -1 && run > 0) {
            if (run != col_hints[ci][chi])
                return false;
            run = 0;
            chi++;
        }
    }
    if (run > 0 && run != col_hints[ci][chi])
        return false;

    return true;
}

int sum(vector<int> &vi) {
    int ret = 0;
    for (int i = 0; i < vi.size(); i++)
        ret += vi[i];
    return ret;
}