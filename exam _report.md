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