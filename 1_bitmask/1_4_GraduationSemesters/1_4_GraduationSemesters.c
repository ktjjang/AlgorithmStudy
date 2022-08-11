#include <stdio.h>

#define MAX_SUBJECT 12
#define MAX_NUM_SEMESTER 32

#define MAX_VAL ((int)(0x7FFFFFFF))

// global 결과값.
int min = MAX_VAL;

int cache[MAX_NUM_SEMESTER][MAX_SUBJECT];

//TC별 변수들
int N, K, M, L;
int prerequisite[MAX_SUBJECT];
int semester[MAX_NUM_SEMESTER];

#define __builtin_popcount(x) (__popcnt(x))
#define IS_SET(x, pos) (!!(x & (1<<pos)))
#define BIT_SET(x, pos) (x = (x | (1<<pos)))
#define BIT_CLEAR(x, pos) (x = (x & ~(1<<pos)))

void graduate(int semester_idx, int taken, int sem_acc)
{
    int target = semester[semester_idx] & ~taken;

    if (semester_idx > M)
        return;

    if (__builtin_popcount(taken) >= K) {
        min = sem_acc < min ? sem_acc : min;
        return;
    }

    //같은 상태인데 더 작은 값이 caching 되어있다? -> 팅겨내기
#ifdef CAHCING
    if (cache[semester_idx][taken] < sem_acc)
        return;
    cache[semester_idx][taken] = sem_acc;
#endif

    //bitmask로 구현한다면 부분집합 돌리는 방법은 easy하다.
    for (int subset = target; subset > 0; subset = (subset - 1) & target) {
        int not_eligible = 0;
        if (__builtin_popcount(subset) > L) continue;

        for (int i = 0; i < 32; i++) {
            if (IS_SET(subset, i)) {
                if ((taken & prerequisite[i]) != prerequisite[i]) {
                    not_eligible = 1;
                    break;
                }
            }
        }

        if (not_eligible == 0) {
            graduate(semester_idx + 1, taken | subset, sem_acc + 1);
        }
    }
    graduate(semester_idx + 1, taken, sem_acc);
}

void init_vars()
{
    min = MAX_VAL;
    N = 0, K = 0, M = 0, L = 0;
    for (int i = 0; i < MAX_NUM_SEMESTER; i++) {
        for (int j = 0; j < MAX_SUBJECT; j++) {
            cache[i][j] = MAX_VAL;
        }
    }
    for (int i = 0; i < sizeof(prerequisite); i++)
        prerequisite[i] = 0;
    for (int i = 0; i < sizeof(semester); i++)
        semester[i] = 0;
}

int main()
{
    int C;
    freopen("input.txt", "r", stdin);

    scanf("%d", &C);
    for (int c = 0; c < C; c++) {
        init_vars();
        scanf("%d %d %d %d", &N, &K, &M, &L);
        for (int n = 0; n < N; n++) {
            int num_prerequisite;
            scanf("%d", &num_prerequisite);
            for (int each = 0; each < num_prerequisite; each++) {
                scanf("%d", &each);
                BIT_SET(prerequisite[n], each);
            }
        }
        for (int m = 0; m < M; m++) {
            int num_subject;
            scanf("%d", &num_subject);
            for (int each = 0; each < num_subject; each++) {
                scanf("%d", &each);
                BIT_SET(semester[m], each);
            }
        }

        graduate(0, 0, 0);
        if (min == MAX_VAL)
            printf("IMPOSSIBLE\n");
        else
            printf("%d\n", min);
    }
}
