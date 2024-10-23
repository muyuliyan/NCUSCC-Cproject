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
test_data_files=("small_data.txt" "medium_data.txt" "large_data.txt" "small_data_float.txt" "medium_data_float.txt" "large_data_float.txt")

# 写入CSV文件头部
echo "Algorithm,Optimization,Data Set,User Time (s),System Time (s),CPU Time (s),Max RSS (MiB)" >> $output_csv

# 循环遍历每个排序算法
for algorithm in "${sorting_algorithms[@]}"; do
    # 循环遍历每个优化等级
    for optimization in "${optimization_levels[@]}"; do
        # 编译排序算法
        gcc $optimization -o "${algorithm}_opt_$optimization" "$algorithm.c"
        
        # 检查编译是否成功
        if [ $? -ne 0 ]; then
            echo "Compilation failed for $algorithm with optimization $optimization."
            continue
        fi
        
        # 循环遍历每个数据集文件
        for data_file in "${test_data_files[@]}"; do
            # 执行排序算法并测量执行时间以及资源占用
            echo "Testing $algorithm with $optimization optimization on $data_file"
            time_output=$(/usr/bin/time -f "%Uu %Ss %et %Mkb" -o temp_results.txt "./${algorithm}_opt_$optimization" < "$data_file" > /dev/null 2>&1)
            
            # 检查程序是否正常退出
            if echo "$time_output" | grep -q "Command"; then
                echo "Error: $algorithm with $optimization optimization terminated abnormally."
                continue
            fi
            
            # 读取资源占用数据
            user_time=$(awk '{print $1}' temp_results.txt)
            system_time=$(awk '{print $2}' temp_results.txt)
            cpu_time=$(awk '{print $3}' temp_results.txt)
            max_rss=$(awk '{print $4}' temp_results.txt)

            # 将结果写入CSV文件
            echo "$algorithm,$optimization,$data_file,\"$user_time\",\"$system_time\",\"$cpu_time\",\"$max_rss\"" >> $output_csv

            # 清理临时文件
            rm temp_results.txt
        done
        
        # 清理编译生成的可执行文件
        rm -f "${algorithm}_opt_$optimization"
    done
done

# 输出完成消息
echo "Performance data collection is complete. CSV file: $output_csv"