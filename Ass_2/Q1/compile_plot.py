import matplotlib.pyplot as plt

with open('compile_time.txt', 'r') as f:    
    heights = []
    p_val = []
    for line in f:
        l = line.split()
        nums = [int(i) for i in l[:3]]
        p_val += nums
        nums = [float(i) for i in l[3::]]
        heights += nums
    x_pos = []
    for i in range(6):
        x_pos += [4*i + 1, 4*i + 2, 4*i + 3]
    plt.bar(x_pos, heights)
    plt.title("Runtime of compile.c for different priorities")
    plt.ylabel("Runtime (s)")
    plt.xticks(x_pos, p_val)
    plt.show()