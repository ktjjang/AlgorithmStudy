/*
* 64비트 부호 없는 정수를 [0,15] 범위의 정수 16개를 담는 배열로 사용하기
*/

#include <stdio.h>

#define MAX_N 500

unsigned long long checked[(MAX_N + 15) / 16];

int get(int index)
{
    int trans_index = (index & 15);
    return (checked[(index >> 4)] >> (4 * trans_index)) & 15;
}

void set(int index, unsigned long long val)
{
    int trans_index = (index & 15);
    int mask = 0xf;
    unsigned long long reg = checked[(index >> 4)];

    reg = (reg & ~(mask << (4 * trans_index)));

    val = ((val & mask) << (4 * trans_index));
    reg = reg | val;

    checked[(index >> 4)] = reg;
    return 0;
}

int main()
{
    set(0, 0xf);
    set(1, 0xa);
    set(2, 0x7);
    set(3, 0x3);
    set(4, 0x2);
    set(5, 0x1);
    set(1, 0x2);
    set(4, 0xa);
    printf("0x%x\n", get(0));
    printf("0x%x\n", get(1));
    printf("0x%x\n", get(2));
    printf("0x%x\n", get(3));
    printf("0x%x\n", get(4));
    printf("0x%x\n", get(5));
}

