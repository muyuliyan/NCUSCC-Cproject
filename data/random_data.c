#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // 用于生成随机数的种子
    srand((unsigned int)time(NULL));

    // 生成随机整数
    int randomInt = rand();
    printf("Random Integer: %d\n", randomInt);

    // 如果需要指定范围，比如从 min 到 max 的随机整数
    int min = 1, max = 100;
    int boundedRandomInt = rand() % (max - min + 1) + min;
    printf("Random Integer between %d and %d: %d\n", min, max, boundedRandomInt);

    // 生成随机浮点数
    // drand48() 函数返回一个随机浮点数，介于 0 到 1 之间
    double randomDouble = drand48();
    printf("Random Double between 0 and 1: %f\n", randomDouble);

    // 如果需要指定范围，比如从 min 到 max 的随机浮点数
    double minDouble = 1.0, maxDouble = 100.0;
    double boundedRandomDouble = minDouble + (maxDouble - minDouble) * drand48();
    printf("Random Double between %lf and %lf: %lf\n", minDouble, maxDouble, boundedRandomDouble);

    return 0;
}