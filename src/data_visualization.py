import matplotlib.pyplot as plt
import csv

# 读取CSV文件中的数据
data = []
with open('performance_data.csv', 'r') as file:
    reader = csv.DictReader(file)
    for row in reader:
        data.append(row)

# 准备绘图数据
optimization_levels = []  # 优化级别的标签
bubble_sort_data = []  # 冒泡排序的时间数据
heap_sort_data = []  # 堆排序的时间数据

for optimization in sorted(set(row["Optimization"] for row in data)):
    optimization_levels.append(optimization)
    bubble_times = [float(row["Time"]) for row in data if row["Algorithm"] == "Bubble Sort" and row["Optimization"] == optimization]
    heap_times = [float(row["Time"]) for row in data if row["Algorithm"] == "Heap Sort" and row["Optimization"] == optimization]
    bubble_sort_data.append(sum(bubble_times) / len(bubble_times) if bubble_times else 0)
    heap_sort_data.append(sum(heap_times) / len(heap_times) if heap_times else 0)

# 绘制图表
plt.plot(optimization_levels, bubble_sort_data, label="Bubble Sort", marker='o')
plt.plot(optimization_levels, heap_sort_data, label="Heap Sort", marker='o')
plt.xlabel("Optimization Level")
plt.ylabel("Average Time (s)")
plt.title("Sorting Algorithm Performance")
plt.legend()
plt.savefig('output_image.png')
#plt.show()