#!/usr/bin/env python3
import csv
import matplotlib.pyplot as plt

def clean_and_convert_time(time_str):
    """清理时间数据字符串，并尝试将其转换为浮点数。"""
    # 检查字符串是否包含非数字字符，这些字符可能是由于程序异常终止导致的
    if 'Command' in time_str or 'terminated' in time_str or 'by' in time_str or 'signal' in time_str:
        return None  # 返回None，表示数据无效
    try:
        # 尝试去除 'u' 或其他非数字字符，并转换为浮点数
        time_str = time_str.replace('u', '').replace('s', '').replace('t', '').replace('Command', '').replace('terminated', '').replace('by', '').replace('signal', '').strip()
        return float(time_str)
    except ValueError:
        return None  # 如果转换失败，返回None

# 读取CSV文件中的数据
data = []
with open('performance_data.csv', 'r') as file:
    reader = csv.DictReader(file)
    for row in reader:
        row['Algorithm'] = row['Algorithm'].upper()
        # 使用辅助函数清理和转换时间数据
        row['User Time (s)'] = clean_and_convert_time(row['User Time (s)'])
        row['System Time (s)'] = clean_and_convert_time(row['System Time (s)'])
        row['CPU Time (s)'] = clean_and_convert_time(row['CPU Time (s)'])
        row['Max RSS (MiB)'] = clean_and_convert_time(row['Max RSS (MiB)'])
        if row['Max RSS (MiB)'] is not None:
            row['Max RSS (MiB)'] /= 1024  # 转换为MiB
        data.append(row)

# 准备绘图数据
optimization_levels = sorted(set(row["Optimization"] for row in data))
data_sets = sorted(set(row["Data Set"] for row in data))

# 初始化数据结构来存储每个数据集和优化级别的平均时间
metrics = ['User Time (s)', 'System Time (s)', 'CPU Time (s)', 'Max RSS (MiB)']
algorithms = ['BUBBLE_SORT', 'HEAP_SORT']  # 确保这些与CSV文件中的算法名称匹配
all_data = {algorithm: {metric: {data_set: {optimization: [] for optimization in optimization_levels} for data_set in data_sets} for metric in metrics} for algorithm in algorithms}

# 计算每个数据集和优化级别的平均时间
for row in data:
    algorithm = row['Algorithm']
    if algorithm in algorithms:
        for metric in metrics:
            if row[metric] is not None:
                all_data[algorithm][metric][row["Data Set"]][row["Optimization"]].append(row[metric])

# 绘制图表
for algorithm in algorithms:
    plt.figure(figsize=(12, 18))
    for i, data_set in enumerate(data_sets, start=1):
        plt.subplot(3, 2, i)
        for optimization in optimization_levels:
            times = all_data[algorithm][metric][data_set].get(optimization, [])
            if times:
                plt.plot([optimization] * len(times), times, label=f'{data_set} {optimization}', marker='o')
        
        plt.title(f'{metric} - {data_set}')
        plt.xlabel('Optimization Level')
        plt.ylabel(metric)
        plt.legend()
    
    plt.tight_layout()
    plt.savefig(f'{algorithm}.png')
    plt.close()

print("Plotting complete. Each algorithm is saved in a separate PNG file.")