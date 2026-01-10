import matplotlib.pyplot as plt


file_names = [
    "boyer_moore_results.txt",
    "knuth_morris_prath_results.txt",
    "robin_karp_results.txt",
    "naive_search_results.txt"
]

# Read and parse data
data = {}
for file_name in file_names:
    data[file_name] = {"words": [], "times": []}
    with open(file_name, 'r') as f:
        for line in f:
            parts = line.strip().split(',')
            word = parts[0]
            time = float(parts[2])
            data[file_name]["words"].append(word)
            data[file_name]["times"].append(time)

# Plot comparison
plt.figure(figsize=(12, 6))
for file_name in file_names:
    plt.plot(data[file_name]["words"], data[file_name]["times"], marker='o', label=file_name.replace("_results.txt", ""))

plt.xlabel("Szukane słowo")
plt.ylabel("Czas wykonania (ms)")
plt.title("Porównanie szybkości algorytmów wyszukiwania")
plt.legend()
plt.xticks(rotation=45, ha='right')
plt.tight_layout()
plt.savefig("comparison_plot.png")