import numpy as np
import matplotlib.pyplot as plt
import os

# 解决负号显示问题
plt.rcParams['axes.unicode_minus'] = False

# 创建画布，大小与比例调整得更美观
fig = plt.figure(figsize=(10, 6))
ax = fig.add_subplot(1, 1, 1)

# 开启网格线：参考图为淡色实线 (solid)
ax.grid(True, linestyle="-", color="lightgray", linewidth=0.5)

# 确保四周的边框都显示，与作业要求的参考图1格式严格一致
ax.spines['top'].set_visible(True)
ax.spines['right'].set_visible(True)
ax.spines['left'].set_visible(True)
ax.spines['bottom'].set_visible(True)

# 设置输出文件名
outfile = 'graph_line_chart.pdf'
infile = 'result.txt'

# 检查 C++ 的输出文件是否存在
if not os.path.exists(infile):
    print(f"错误：未找到 '{infile}' 文件！请先运行 C++ 程序生成该文件。")
    exit(1)

# 动态读取 C++ 程序输出的文件内容
x = []
res1 = []  # 存储 eps_max
res2 = []  # 存储 eps_avg

with open(infile, 'r') as f:
    for line in f:
        line = line.strip()
        if not line:
            continue
        parts = line.split()
        if len(parts) >= 3:
            x.append(int(parts[0]))        # 第一列是 m
            res1.append(float(parts[1]))   # 第二列是 max_err
            res2.append(float(parts[2]))   # 第三列是 avg_err

# 转换为 numpy 数组方便绘图
x = np.array(x)
res1 = np.array(res1)
res2 = np.array(res2)

# 绘制曲线：上方曲线为黑色(最大误差)，下方曲线为蓝色(平均误差)
ax.plot(x, res1, color="black", linewidth=2.5, label=r"$\epsilon_{max}$")
ax.plot(x, res2, color="blue", linewidth=2.5, label=r"$\epsilon_{avg}$")

# 严格匹配参考图的字体大小与刻度设置
plt.xticks([0, 50, 100, 150, 200, 250, 300], fontsize=14) 
plt.yticks([0.0, 0.2, 0.4, 0.6, 0.8, 1.0], ["0.0", "0.2", "0.4", "0.6", "0.8", "1.0"], fontsize=14)

# 严格匹配作业 PDF 示例参考格式的坐标轴标签
plt.xlabel("Trial", fontsize=18, labelpad=5)
plt.ylabel("Average", fontsize=18, labelpad=5)

# 设置坐标轴显示范围
ax.set_xlim(0, 300)
ax.set_ylim(0.0, 1.01)

# 自动调整布局防止标签切边
plt.tight_layout()

# 保存为 PDF 文件
plt.savefig(outfile, format='pdf', dpi=300)
print(f"成功读取 {infile} 并根据作业要求生成趋势图：{outfile}")