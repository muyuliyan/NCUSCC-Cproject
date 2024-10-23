# <font face="仿宋" font color=orange>NCUSCC选拔考核-C语言项目实验报告</font>  
## <center><font face=“楷体” size=5>严李阳</font></center>  
## <font face="仿宋" font color=bule>考核要求</font>  
1. 安装虚拟机：
    - 在虚拟机中安装 Ubuntu 22.04 LTS 操作系统。
    - 配置虚拟机的网络连接，确保可以正常联网。
2. 安装 C 语言编译器：
    - 安装最新版本的 gcc（可通过 PPA 安装最新稳定版）。
    - 验证编译器安装成功，并确保其正常工作。
3. 实现排序算法：
    - 使用 C 语言手动实现以下排序算法：冒泡排序、基础堆排序以及斐波那契堆排序，不调用任何库函数。
    - 运行测试代码，确认各排序算法的正确性。
4. 生成测试数据：
    - 编写代码或脚本自动生成测试数据（随机生成浮点数或整数）。
    - 测试数据应覆盖不同规模的数据集，其中必须包含至少 100 000 条数据的排序任务。
5. 编译与性能测试：
    - 使用不同等级的 gcc 编译优化选项（如 -O0, -O1, -O2, -O3, -Ofast 等）对冒泡排序和堆排序代码进行编译。
    - 记录各优化等级下的排序算法性能表现（如执行时间和资源占用）。
6. 数据记录与可视化：
    - 收集每个编译等级的运行结果和性能数据。
    - 分析算法的时间复杂度，并将其与实验数据进行对比。
    - 将数据记录在 CSV 或其他格式文件中。
    - 使用 Python、MATLAB 等工具绘制矢量图，展示实验结论。
7. 撰写实验报告：
    - 撰写一份详细的实验报告，内容应包括：
        - 实验环境的搭建过程（虚拟机安装、网络配置、gcc 安装等）。
        - 冒泡排序、基础堆排序和斐波那契堆排序的实现细节。
        - 测试数据的生成方法。
        - 不同编译优化等级下的性能对比结果。
        - 数据可视化部分（附图表）。
        - 实验过程中遇到的问题及解决方案。
    - 报告必须采用 LaTeX 或 Markdown 格式撰写。  
_____  
## <font face="仿宋" font color=orang>实验报告正式部分</font>  
### 一、实验环境的搭建
**实验目的：熟悉虚拟机的安装流程和Linux系统的基础操作，提高自身在不同编程环境下的适应力，并学会在不同操作系统中创造适合自己的编程环境，同时试错一些不必要的操作失误问题。**  

**实验流程：**
***1. 使用Oraccle VirtualBox创建虚拟机，并在虚拟机上安装Ubuntu 22.04 LTS操作系统***  
(1)前往[Ubuntu官方网站]获取Ubuntu-22.04-desktop的ISO文件，桌面板具有一定的图形界面，适合新手操作  
[![pAdSSNF.png](https://s21.ax1x.com/2024/10/21/pAdSSNF.png)](https://imgse.com/i/pAdSSNF)  
(2)新建虚拟机，适当增加内存、处理器、硬盘分配，以便匹配后续性能和存储需求，勾选跳过自动安装  
[![pAdpYs1.png](https://s21.ax1x.com/2024/10/21/pAdpYs1.png)](https://imgse.com/i/pAdpYs1)  
[![pAazjBV.png](https://s21.ax1x.com/2024/10/21/pAazjBV.png)](https://imgse.com/i/pAazjBV)  
[![pAdp6sI.png](https://s21.ax1x.com/2024/10/21/pAdp6sI.png)](https://imgse.com/i/pAdp6sI)  
(3)系统安装，手动重启  
[![pAdpOoT.jpg](https://s21.ax1x.com/2024/10/21/pAdpOoT.jpg)](https://imgse.com/i/pAdpOoT)  
***2.网络配置***  
(1)连接到互联网安装提示界面选择我现在不想连接到互联网，方便后续调整网络连接方式  
[![pAdpLwV.jpg](https://s21.ax1x.com/2024/10/21/pAdpLwV.jpg)](https://imgse.com/i/pAdpLwV)  
[![pAdKCdg.png](https://s21.ax1x.com/2024/10/22/pAdKCdg.png)](https://imgse.com/i/pAdKCdg)  
***3.gcc安装***  
(1)右键鼠标打开终端  
[![pAd1in0.png](https://s21.ax1x.com/2024/10/22/pAd1in0.png)](https://imgse.com/i/pAd1in0)
(2)输入指令更新并下载  
> sudo apt update  
> sudo apt install build-essential

(3)检查版本，确认是否安装  
> gcc --version  

**发现问题：**  
*1.同时安装多个相同系统的虚拟机，删除文件时会删除共有文件，导致原机映像文件受损  
2.第一次安装系统后可能会陷入黑屏无响应情况*  
**解决方案：**  
*1.如果处理时间较短可以考虑用[Data Numen]大海捞针；如果你已经像我一样使用了重启大法，导致硬盘数据碎片丢失，那就只能选择重装系统，调用备份数据了  
2.第一次装好系统黑屏的话，重启虚拟机一般就能解决问题，如果重启了三四次仍然黑屏或进入选择系统界面，那大概率需要重装系统（以我现在的技术力确实无法对点解决缺失文件问题）*  
[![pAd1Rvn.jpg](https://s21.ax1x.com/2024/10/22/pAd1Rvn.jpg)](https://imgse.com/i/pAd1Rvn)
[![pAd1IET.jpg](https://s21.ax1x.com/2024/10/22/pAd1IET.jpg)](https://imgse.com/i/pAd1IET)  

### 二、冒泡排序、基础堆排序和斐波那契堆排序的实现细节  
**实验目的：考验代码书写硬实力，理解排序结构和实现原理，并学会导入数据基本测试查错和实际运用**  
***1.冒泡排序***  
```
void bubbleSortInt(int arr[], int n) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}  
```  
**代码实现：冒泡排序真正的代码实现实际上只有两个嵌套for循环结构和一个if判断语句的使用，用于遍历元素进行像冒泡泡一样的对比筛选机制使较大的“泡泡”逐渐上浮排序。外循环利用bool值设定用于表示这次遍历开始时没有发生元素交换，内循环进行元素交换和排序的工作，每次循环后最后i个数是已经排序好的，所以只需要遍历到n-i-1即可。内循环中的三行代码是执行对比交换工作的核心，排好序后bool值表示经过交换，则循环继续进行。如果数据一开始就排好序，则系统直接执行外部if语句，跳出循环避免不必要的空耗运行。读取浮点数数据只需要修改数据类型即可**  
```  
#include <stdio.h>
#include <stdbool.h>

void bubbleSortInt(int arr[], int n) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Original array: \n");
    printArray(arr, n);
    
    bubbleSortInt(arr, n);
    
    printf("Sorted array: \n");
    printArray(arr, n);
    
    return 0;
}  
```  
**运行测试：**  
键入
> gcc -o bubble_test bubble_test.c  
> ./bubble_test  

在gcc编译器中编译并成功执行  
[![pAdGg8e.png](https://s21.ax1x.com/2024/10/22/pAdGg8e.png)](https://imgse.com/i/pAdGg8e)  
**数据读取的实现**   
```  
    // Read and sort integer data
    for (int i = 0; i < 3; i++) {
        sizes[i] = readIntDataFromFile(filenames[i], intArrays[i]);
        bubbleSortInt(intArrays[i], sizes[i]);
        printf("Sorted %s: ", filenames[i]);
        printIntArray(intArrays[i], sizes[i]);
    }  
    // Read and sort float data
    sizes[3] = readFloatDataFromFile(filenames[3], floatArray);
    bubbleSortFloat(floatArray, sizes[3]);
    printf("Sorted %s: ", filenames[3]);
    printFloatArray(floatArray, sizes[3]);
```
**<font face="仿宋" font color=bule>对于我所生成的浮点数</font>  




























































[Ubuntu官方网站]:https://ubuntu.com/desktop   
[Data Numen]:https://www.datanumen.com/download/