#!/usr/bin/env python3
import csv
import matplotlib.pyplot as plt
import os

def clean_and_convert_time(time_str):
    """清理时间数据字符串，并尝试将其转换为浮点数。"""
    if 'Command' in time_str or 'terminated' in time_str or 'by' in time_str or 'signal' in time_str:
        return None
    try:
        time_str = time_str.split('\n')[-1].replace('u', '').replace('s', '').replace('t', '').strip()
        return float(time_str)
    except ValueError:
        return None

# 读取CSV文件中的数据
data = []
csv_file_path = 'performance_data.csv'  # CSV文件名
with open(csv_file_path, 'r') as file:
    reader = csv.DictReader(file)
    for row in reader:
        print(f"Reading row: {row}")  # 打印读取的行数据
        row['Algorithm'] = row['Algorithm'].upper()
        row['User Time (s)'] = clean_and_convert_time(row['User Time (s)'])
        row['System Time (s)'] = clean_and_convert_time(row['System Time (s)'])
        row['CPU Time (s)'] = clean_and_convert_time(row['CPU Time (s)'])
        row['Max RSS (MiB)'] = clean_and_convert_time(row['Max RSS (MiB)'])
        if row['Max RSS (MiB)'] is not None:
            row['Max RSS (MiB)'] /= 1024
        data.append(row)

# 准备绘图数据
optimization_levels = sorted(set(row["Optimization"] for row in data))
data_sets = sorted(set(row["Data Set"] for row in data))

# 初始化数据结构来存储每个数据集和优化级别的平均时间
metrics = ['User Time (s)', 'System Time (s)', 'CPU Time (s)', 'Max RSS (MiB)']
all_data = {metric: {data_set: {optimization: [] for optimization in optimization_levels} for data_set in data_sets} for metric in metrics}

# 计算每个数据集和优化级别的平均时间
for row in data:
    for metric in metrics:
        if row[metric] is not None:
            all_data[metric][row["Data Set"]][row["Optimization"]].append(row[metric])

# 绘制图表
for metric in metrics:
    plt.figure(figsize=(12, 18))
    for i, data_set in enumerate(data_sets, start=1):
        plt.subplot(3, 2, i)
        for optimization in optimization_levels:
            times = all_data[metric][data_set].get(optimization, [])
            if times:
                plt.plot([optimization] * len(times), times, label=f'{data_set} {optimization}', marker='o')
        
        plt.title(f'{metric} - {data_set}')
        plt.xlabel('Optimization Level')
        plt.ylabel(metric)
        plt.legend()
    
    plt.tight_layout()
    plt.savefig(f'{metric}.png')
    plt.close()

print("Plotting complete. Each metric is saved in a separate PNG file.")

# 编译冒泡排序和堆排序程序
sorting_algorithms = ["bubble_sort.c", "heap_sort.c"]  # 源代码文件名
for algorithm_file in sorting_algorithms:
    if not os.path.exists(algorithm_file):
        print(f"File {algorithm_file} does not exist.")
    else:
        print(f"Compiling {algorithm_file}...")
        # 编译命令，这里假设gcc编译器已安装
        compilation_command = f"gcc -o {algorithm_file.replace('.c', '')} {algorithm_file}"
        os.system(compilation_command)