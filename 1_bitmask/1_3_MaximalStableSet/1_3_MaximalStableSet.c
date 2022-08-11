/*
* 네 개의 화학물질 A,B,C,D가 있을 때 
* A와 B를 같은 상자에 넣거나, C와 D를 같은 상자에 넣으면 폭발한다고 한다면
* 극대안정집합은 {A,C}, {A,D}, {B,C}, {B,D}
* 같이넣으면 폭발하는 물질이 bitmask로 explodes배열로 표현되었을 때,
* 극대안정집합을 구하라
*/

#include <stdio.h>

#define MAX_N 4
int explodes[MAX_N] = {0x2, 0x1, 0x8, 0x4};

inline int is_set(int set, int index)
{
    if (((set >> index) & 0x1))
        return 1;
    else
        return 0;
}

int is_stable(int set)
{
    for (int i = 0; i < sizeof(int); i++) {
        if (is_set(set, i)) {
            if (explodes[i] & set)
                return 0;
        }
    }
    return 1;
}

int main()
{
    int all_set = ((1 << MAX_N) - 1);

    for (int subset = all_set; subset > 0; subset = (subset - 1) & all_set) {
        int can_extend = 0;

        if (!is_stable(subset)) continue;

        for (int i = 0; i < MAX_N; i++) {
            if ((is_set(subset, i) == 0) && ((explodes[i] & subset) == 0)) {
                can_extend = 1;
                break;
            }
        }

        if (can_extend == 0) printf("%x ", subset);
    }

    return 0;
}
