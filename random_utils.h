//Data will be sellected in it
// random_utils.h
#ifndef RANDOM_UTILS_H
#define RANDOM_UTILS_H

#include <stdlib.h>
#include <time.h>

// 初始化随机数生成器
void init_random();

// 生成一个在[min, max]范围内的随机整数
int random_int(int min, int max);

// 生成一个在[min, max]范围内的随机浮点数
double random_double(double min, double max);

#endif // RANDOM_UTILS_H