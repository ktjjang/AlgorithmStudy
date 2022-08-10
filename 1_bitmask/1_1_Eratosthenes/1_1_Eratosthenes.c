/* Q. 1부터 N까지의 소수를 구하는 에라토스테네스의 체 소수를 빠르게 구할수 있지만, 
* 배열을 사용해서 check 해야 한다는 점 때문에 메모리르 많이 사용한다.
* 에라토스테네스의 체를 bitmask를 이용해 구현함으로써 memory 사용량을 줄여라
*/

#include <stdio.h>
#define MAX_N (1<<20)

int checked[(MAX_N + sizeof(int) - 1) / sizeof(int)];

int is_set(int index)
{
    return !!(checked[(index >> sizeof(int))] & (1 << (index & (sizeof(int) - 1))));
}

void set_bit(int index)
{
    checked[index >> sizeof(int)] |= (1 << (index & sizeof(int) - 1));
    return;
}

int main()
{
    
    printf("test\n");
    return 0;
}
