import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter

plt.rcParams['axes.unicode_minus'] = False
fig=plt.figure(figsize=(14, 8))
ax = fig.add_subplot(50,1,(1,49))
ax.grid(linestyle = "--")
ax.spines['top'].set_visible(False) 
ax.spines['right'].set_visible(False)

filename = 'res.txt'
outfile = 'dynamic_averaging.pdf'

f = open(filename, "r")
res = []
n = 5000

for i in range(n+1):
	line = f.readline()
	res.append(float(line))
max_num=int(res[-1])
res.pop()
x = np.array(range(1, n + 1))

res = np.array(res)
bst = np.ones_like(x) * max_num

ax.plot(x, res, color="black", linewidth=4)
ax.plot(x, bst, color="red", linestyle = "dashed", linewidth=4)

plt.xticks(fontsize=30.5) 
plt.yticks(fontsize=15.5)
plt.xlabel("Trial", fontsize=37.5)
plt.ylabel("Average", fontsize=37.5)
plt.yticks([0,1475500,1476000, 1476500,1477000,max_num])
ax.yaxis.set_major_formatter(FormatStrFormatter('%d'))
plt.gca().get_yticklabels()[5].set_color('red') 
ax.set_xlim(0, n + 0.1)
ax.set_ylim(1474580, 1479500)

plt.savefig(outfile, format='pdf')

