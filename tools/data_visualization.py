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
        row['System Time (s)'] = float(row['System Time (s)'].replace('u', '')) if row['System Time (s)'] else None
        row['CPU Time (s)'] = float(row['CPU Time (s)'].replace('u', '')) if row['CPU Time (s)'] else None
        data.append(row)

# 准备绘图数据
optimization_levels = sorted(set(row["Optimization"] for row in data))
data_sets = sorted(set(row["Data Set"] for row in data))

# 初始化数据结构来存储每个数据集和优化级别的平均时间
bubble_sort_data = {data_set: [] for data_set in data_sets}
heap_sort_data = {data_set: [] for data_set in data_sets}

# 计算每个数据集和优化级别的平均时间
for optimization in optimization_levels:
    for data_set in data_sets:
        bubble_times = [float(row["User Time (s)"]) for row in data if row["Algorithm"] == "BUBBLE_SORT" and row["Optimization"] == optimization and row["Data Set"] == data_set]
        heap_times = [float(row["User Time (s)"]) for row in data if row["Algorithm"] == "HEAP_SORT" and row["Optimization"] == optimization and row["Data Set"] == data_set]
        
        # 打印每个数据点的调试信息
        print(f"Bubble Sort times for {optimization} {data_set}: {bubble_times}")
        print(f"Heap Sort times for {optimization} {data_set}: {heap_times}")
        
        if bubble_times:
            bubble_sort_data[data_set].append(sum(bubble_times) / len(bubble_times))
        else:
            print(f"No data for Bubble Sort {optimization} {data_set}")
        
        if heap_times:
            heap_sort_data[data_set].append(sum(heap_times) / len(heap_times))
        else:
            print(f"No data for Heap Sort {optimization} {data_set}")

# 绘制图表
plt.figure(figsize=(10, 6))

legend_labels = []
for data_set in data_sets:
    if data_set in bubble_sort_data and data_set in heap_sort_data:
        if bubble_sort_data[data_set] and heap_sort_data[data_set]:  # Check if lists are not empty
            plt.plot(optimization_levels, bubble_sort_data[data_set], label=f"Bubble Sort {data_set}", marker='o')
            plt.plot(optimization_levels, heap_sort_data[data_set], label=f"Heap Sort {data_set}", marker='o')
            legend_labels.append(f"Bubble Sort {data_set}")
            legend_labels.append(f"Heap Sort {data_set}")
        else:
            print(f"No valid data for {data_set}")

if legend_labels:
    plt.legend(legend_labels)
else:
    print("No valid data to plot.")

plt.xlabel("Optimization Level")
plt.ylabel("Average Time (s)")
plt.title("Sorting Algorithm Performance by Data Set")
plt.savefig('output_image_1.png')
plt.show()