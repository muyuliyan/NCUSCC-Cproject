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
        row['User Time (s)'] = float(row['User Time (s)'].split('\n')[1].replace('u', '')) if row['User Time (s)'] else None
        row['System Time (s)'] = float(row['System Time (s)'].split('\n')[1].replace('s', '')) if row['System Time (s)'] else None
        row['CPU Time (s)'] = float(row['CPU Time (s)'].split('\n')[1].replace('t', '')) if row['CPU Time (s)'] else None
        # 去除 'Max RSS (MiB)' 中的 'kb' 或 'MiB'，并转换为浮点数
        row['Max RSS (MiB)'] = float(row['Max RSS (MiB)'].split('\n')[1].replace('kb', '').replace('MiB', '').strip()) if row['Max RSS (MiB)'] else None
        data.append(row)

# 准备绘图数据
optimization_levels = sorted(set(row["Optimization"] for row in data))
data_sets = sorted(set(row["Data Set"] for row in data))

# 初始化数据结构来存储每个数据集和优化级别的平均时间
metrics_data = {
    'User Time (s)': {data_set: [] for data_set in data_sets},
    'System Time (s)': {data_set: [] for data_set in data_sets},
    'CPU Time (s)': {data_set: [] for data_set in data_sets},
    'Max RSS (MiB)': {data_set: [] for data_set in data_sets},
}

# 计算每个数据集和优化级别的平均时间
for optimization in optimization_levels:
    for data_set in data_sets:
        for metric in metrics_data:
            times = [float(row[metric]) for row in data if row["Algorithm"] in ["BUBBLE_SORT", "HEAP_SORT"] and row["Optimization"] == optimization and row["Data Set"] == data_set]
            if times:
                metrics_data[metric][data_set].append(sum(times) / len(times))
            else:
                print(f"No data for {metric} {optimization} {data_set}")

# 绘制图表
fig, axs = plt.subplots(2, 2, figsize=(10, 10), tight_layout=True)

metrics_labels = ['User Time (s)', 'System Time (s)', 'CPU Time (s)', 'Max RSS (MiB)']
for ax, metric in zip(axs.flatten(), metrics_labels):
    for data_set in data_sets:
        if data_set in metrics_data[metric] and metrics_data[metric][data_set]:
            ax.plot(optimization_levels, metrics_data[metric][data_set], marker='o', label=data_set)
    ax.set_title(metric)
    ax.set_xlabel("Optimization Level")
    ax.set_ylabel(metric)
    ax.legend()

plt.savefig('performance_metrics.png')
plt.show()