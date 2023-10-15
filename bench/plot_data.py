# python3 plot_data.py data.json type_of_bench

import matplotlib.pyplot as plt
import json
import sys

types = ['all-zero', 'small-size', 'equal-size']
if(sys.argv[2] not in types):
    raise Exception('error in benchmark name')
json_file = sys.argv[1]
with open(json_file) as json_data:
    data = json.load(json_data)


real_time = [round(i['real_time'], 2) for i in data['benchmarks'] if sys.argv[2] in i['name']]
sizes = [int(i['name'].rsplit('/')[1]) for i in data['benchmarks'] if sys.argv[2] in i['name']]
# print(sizes)
# print(real_time)

def draw(size, time) -> None:
    
    fig, ax = plt.subplots()
    ax.plot(size, time, 'o-', label='smawk')
    ax.ticklabel_format(useOffset=False, style='plain', axis='both')
    # ax.set_xticklabels([])
    # ax.set_yticklabels([])
    ax.set_xlabel('Input size(elements)', fontsize=11)
    ax.set_ylabel('Average time(ms)', fontsize=11) 
    ax.legend(loc='best')
    
    plt.savefig(sys.argv[2] + '.jpg')

draw(sizes, real_time)
