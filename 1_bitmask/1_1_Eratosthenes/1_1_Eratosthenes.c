/* Q. 1부터 N까지의 소수를 구하는 에라토스테네스의 체 소수를 빠르게 구할수 있지만, 
* 배열을 사용해서 check 해야 한다는 점 때문에 메모리르 많이 사용한다.
* 에라토스테네스의 체를 bitmask를 이용해 구현함으로써 memory 사용량을 줄여라
*/

#include <stdio.h>
#define MAX_N (1<<20)

int N = 120;
int checked[(MAX_N + sizeof(int) - 1) / sizeof(int)];

int is_set(int index)
{
    return !!(checked[(index >> 5)] & (1 << (index & 31)));
}

void set_bit(int index)
{
    checked[index >> 5] |= (1 << (index & 31));
    return;
}

int sqrt(int N)
{
    int i = 0;
    for (i = 0; i < N - 1; i++) {
        if (i * i > N)
            break;
    }
    return i;
}

void init_vars()
{
    for (int i = 0; i < sizeof(checked); i++) {
        checked[i] = 0;
    }
}

int main()
{
    int sqrt_N = sqrt(N);
    printf("N: %d, sqrt_N\n", N, sqrt_N);
    set_bit(0);
    set_bit(1);
    for (int i = 2; i <= sqrt_N; i++) {
        if (is_set(i) == 0) {
            for (int j = i * i; j <= N; j+=i) {
                set_bit(j);
            }
        }
    }
    
    int k = 0;
    for (int i = 0; i < N; i++) {
        if (is_set(i) == 0) {
            printf("%d ", i);
            if ((++k) % 10 == 0)
                printf("\n");
        }
    }
    return 0;
}
