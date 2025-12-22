import re

import matplotlib.pyplot as plt

def parse_results(filename):
    sizes = []
    data = {}
    
    with open(filename, 'r') as f:
        content = f.read()
    
    # pattern z czata do wyodrębniania danych
    pattern = r'(\w+(?:\s+\w+)?), Size: (\d+), Time: ([\d.]+) ms, Comparisons: (\d+), Swaps: (\d+)'
    matches = re.findall(pattern, content)
    
    for match in matches:
        algo, size, time, comparisons, swaps = match
        size = int(size)
        
        if size not in sizes:
            sizes.append(size)
        
        if algo not in data:
            data[algo] = {"time": [], "comparisons": [], "swaps": []}
        
        data[algo]["time"].append(float(time))
        data[algo]["comparisons"].append(int(comparisons))
        data[algo]["swaps"].append(int(swaps))
    
    return sizes, data

def main():
    sizes, data = parse_results("sorting_results.txt")
    
    fig, axes = plt.subplots(1, 2, figsize=(14, 6))
    
    ax1 = axes[0]
    for algo, values in data.items():
        operations = [c + s for c, s in zip(values["comparisons"], values["swaps"])]
        ax1.plot(sizes, operations, marker='o', label=algo)
    ax1.set_xlabel("Rozmiar zbioru")
    ax1.set_ylabel("Liczba operacji")
    ax1.set_title("Liczba operacji w zależności od rozmiaru zbioru")
    ax1.legend()
    ax1.grid(True)
    ax1.set_yscale('log')
    
    ax2 = axes[1]
    for algo, values in data.items():
        ax2.plot(sizes, values["time"], marker='o', label=algo)
    ax2.set_xlabel("Rozmiar zbioru")
    ax2.set_ylabel("Czas wykonania (ms)")
    ax2.set_title("Czas wykonania w zależności od rozmiaru zbioru")
    ax2.legend()
    ax2.grid(True)
    ax2.set_yscale('log')
    
    plt.tight_layout()
    plt.savefig("sorting_comparison.png")
    plt.show()
    

if __name__ == "__main__":
    main()
