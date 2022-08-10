#include <stdio.h>
#include <intrin.h>

/* 집합에 원소 추가 및 삭제 */
#define SET_BIT(x, pos) (x = (x | (0x1 << pos)))
#define CLEAR_BIT(x, pos) (x = (x & ~(0x1 << pos)))

/* 원소 포함 여부 확인 */
#define IS_SET(x, pos) (!!(x & (0x1 << pos)))    

/* 원소 토글 */
#define TOGGLE_BIT(x, pos) (x = (x ^ (0x1<<pos)))

/* 합집합, 교집합, 차집합, 둘중 하나에만 있는 요소 반환 */
#define ADD(a,b) (a | b)
#define AND(a,b) (a & b)
#define SUB(a,b) (a & b)
#define XOR(a,b) (a ^ b)

/* 집합의 크기 */
#define __builtin_popcount(x) __popcount(x)
#define __builtin_ctz(ret, x) _BitScanForward(&ret, x)

/* 최소원소 */
#define last_bit_mask(x) (x & -x)
#define del_last_bit(x) (x = (x & (x - 1)))

/* 부분집합 */
#define for_each_subset(set) \
for(int subset = set; subset; subset = ((subset - 1) & set))

int main()
{
	printf("test\n");
}
