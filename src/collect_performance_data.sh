#!/bin/bash

# 定义输出CSV文件的名称
output_csv="performance_data.csv"

# 确保CSV文件存在且为空
> $output_csv

# 定义优化等级数组
optimization_levels=(-O0 -O1 -O2 -O3 -Ofast)

# 定义排序算法数组
sorting_algorithms=("bubble_sort" "heap_sort")

# 定义测试数据文件数组
test_data_files=("small_data.txt" "medium_data.txt" "large_data.txt" "large_data_float.txt")

# 写入CSV文件头部
echo "Algorithm,Optimization,Data Set,Time (s)" >> $output_csv

# 循环遍历每个排序算法
for algorithm in "${sorting_algorithms[@]}"; do
    # 循环遍历每个优化等级
    for optimization in "${optimization_levels[@]}"; do
        # 编译排序算法
        gcc $optimization -o "$algorithm"_"$optimization" "$algorithm.c"
        
        # 循环遍历每个数据集文件
        for data_file in "${test_data_files[@]}"; do
            # 执行排序算法并测量执行时间
            echo "Testing $algorithm with $optimization optimization on $data_file"
            start_time=$(date +%s%3N) # 获取当前时间（毫秒）
            ./"$algorithm"_"$optimization" < "$data_file" > /dev/null 2>&1
            end_time=$(date +%s%3N) # 获取结束时间（毫秒）
            exec_time=$(echo "scale=4; ($end_time - $start_time) / 1000" | bc) # 计算执行时间（秒）
            
            # 将结果写入CSV文件
            echo "$algorithm,$optimization,$data_file,$exec_time" >> $output_csv
        done
        
        # 清理编译生成的可执行文件
        rm -f ./"$algorithm"_"$optimization"
    done
done

# 输出完成消息
echo "Performance data collection is complete. CSV file: $output_csv"