#!/usr/bin/env python3
import csv
import matplotlib.pyplot as plt

# 读取CSV文件中的数据
data = []
with open('performance_data.csv', 'r') as file:
    reader = csv.DictReader(file)
    for row in reader:
        # 将 Algorithm 列的值转换为大写
        row['Algorithm'] = row['Algorithm'].upper()
        # 去除时间列中的 'u' 字符，并转换为浮点数
        row['User Time (s)'] = float(row['User Time (s)'].replace('u', '')) if row['User Time (s)'] else None
        row['System Time (s)'] = float(row['System Time (s)'].replace('s', '')) if row['System Time (s)'] else None
        row['CPU Time (s)'] = float(row['CPU Time (s)'].replace('t', '')) if row['CPU Time (s)'] else None
        # 去除 'Max RSS (MiB)' 中的 'kb' 或 'MiB'，并转换为浮点数
        row['Max RSS (MiB)'] = float(row['Max RSS (MiB)'].replace('kb', '').replace('MiB', '').strip()) if row['Max RSS (MiB)'] else None
        data.append(row)

# 准备绘图数据
optimization_levels = sorted(set(row["Optimization"] for row in data))
algorithm_types = sorted(set(row["Algorithm"] for row in data))

# 初始化数据结构来存储每个算法类型和优化级别的平均时间
metrics_data = {
    'User Time (s)': {algorithm: {opt: [] for opt in optimization_levels} for algorithm in algorithm_types},
    'System Time (s)': {algorithm: {opt: [] for opt in optimization_levels} for algorithm in algorithm_types},
    'CPU Time (s)': {algorithm: {opt: [] for opt in optimization_levels} for algorithm in algorithm_types},
    'Max RSS (MiB)': {algorithm: {opt: [] for opt in optimization_levels} for algorithm in algorithm_types},
}

# 计算每个算法类型和优化级别的平均时间
for row in data:
    algorithm = row["Algorithm"]
    optimization = row["Optimization"]
    for metric in metrics_data:
        if row[metric] is not None:
            metrics_data[metric][algorithm][optimization].append(row[metric])

# 绘制图表
fig, axs = plt.subplots(2, 2, figsize=(10, 10), tight_layout=True)
metrics_labels = ['User Time (s)', 'System Time (s)', 'CPU Time (s)', 'Max RSS (MiB)']

for ax, metric in zip(axs.flatten(), metrics_labels):
    for algorithm in algorithm_types:
        if algorithm in metrics_data[metric]:
            for optimization in optimization_levels:
                values = metrics_data[metric][algorithm][optimization]
                if values:
                    avg_value = sum(values) / len(values)
                    ax.plot(optimization, avg_value, marker='o', label=f"{algorithm} {optimization}")

    ax.set_title(metric)
    ax.set_xlabel("Optimization Level")
    ax.set_ylabel(metric)
    ax.legend()

plt.savefig('performance_metrics_by_algorithm.png')
plt.show()