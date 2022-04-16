import json
import matplotlib.pyplot as plt
from requests import head

with open('result.json') as f:
    data = json.load(f)
scale = []
Heap_sort = []
Merge_sort = []
Quick_sort = []
Shell_sort = []
for i in range(len(data)):
    scale.append(data[i]['scale'])
    Heap_sort.append(data[i]['Heap_sort'])
    Merge_sort.append(data[i]['Merge_sort'])
    Quick_sort.append(data[i]['Quick_sort'])
    Shell_sort.append(data[i]['Shell_sort'])
plt.figure(figsize=(10,8),dpi=100,linewidth = 2)
plt.plot(scale,Heap_sort,'s-',color = 'r', label="Heap_sort")
plt.plot(scale,Merge_sort,'o-',color = 'g', label="Merge_sort")
plt.plot(scale,Quick_sort,'d-',color = 'b', label="Quick_sort")
plt.plot(scale,Shell_sort,'x-',color = 'k', label="Shell_sort")
plt.ylabel("time spend(s)", fontsize=30, labelpad = 20)
plt.xlabel("n scale(1e6)", fontsize=30, labelpad = 15)
plt.title("Sort Result", fontsize=20)
plt.legend(loc = "best", fontsize=20)
plt.savefig("result.jpg")
plt.show()