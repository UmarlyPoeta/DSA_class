#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Ustawienia dla polskich znaków
plt.rcParams['font.family'] = 'DejaVu Sans'
plt.rcParams['font.size'] = 10

# Wczytanie danych
df = pd.read_csv('sorting_results.csv')

# Konwersja czasu z mikrosekund na milisekundy dla lepszej czytelności
df_ms = df.copy()
for col in df.columns[1:]:
    df_ms[col] = df[col] / 1000  # μs -> ms

# Kolory dla algorytmów
colors = {
    'BucketSort': '#FF6B6B',
    'QuickSort': '#4ECDC4',
    'MergeSort': '#45B7D1',
    'HeapSort': '#FFA07A',
    'HybridSort': '#98D8C8'
}

# ====================================
# WYKRES 1: Porównanie wszystkich algorytmów
# ====================================
fig, ax = plt.subplots(figsize=(12, 7))

for algorithm in df.columns[1:]:
    ax.plot(df['Size'], df_ms[algorithm], marker='o', linewidth=2.5, 
            label=algorithm, color=colors[algorithm], markersize=8)

ax.set_xlabel('Rozmiar tablicy (n)', fontsize=12, fontweight='bold')
ax.set_ylabel('Czas wykonania (ms)', fontsize=12, fontweight='bold')
ax.set_title('Porównanie wydajności algorytmów sortowania', 
             fontsize=14, fontweight='bold', pad=20)
ax.legend(fontsize=11, loc='upper left', framealpha=0.9)
ax.grid(True, alpha=0.3, linestyle='--')
ax.set_xlim(left=0)
ax.set_ylim(bottom=0)

plt.tight_layout()
plt.savefig('comparison_all.png', dpi=300, bbox_inches='tight')
print("✓ Wykres 1 zapisany: comparison_all.png")

# ====================================
# WYKRES 2: Porównanie w skali logarytmicznej
# ====================================
fig, ax = plt.subplots(figsize=(12, 7))

for algorithm in df.columns[1:]:
    ax.loglog(df['Size'], df_ms[algorithm], marker='o', linewidth=2.5,
              label=algorithm, color=colors[algorithm], markersize=8)

ax.set_xlabel('Rozmiar tablicy (n)', fontsize=12, fontweight='bold')
ax.set_ylabel('Czas wykonania (ms) [skala log]', fontsize=12, fontweight='bold')
ax.set_title('Porównanie wydajności algorytmów (skala logarytmiczna)', 
             fontsize=14, fontweight='bold', pad=20)
ax.legend(fontsize=11, loc='upper left', framealpha=0.9)
ax.grid(True, alpha=0.3, linestyle='--', which='both')

plt.tight_layout()
plt.savefig('comparison_log.png', dpi=300, bbox_inches='tight')
print("✓ Wykres 2 zapisany: comparison_log.png")

# ====================================
# WYKRES 3: Wykresy słupkowe dla każdego rozmiaru
# ====================================
fig, axes = plt.subplots(2, 2, figsize=(14, 10))
axes = axes.flatten()

selected_sizes = [df['Size'].iloc[i] for i in [1, 3, 5, 7]]  # Wybrane rozmiary

for idx, size in enumerate(selected_sizes):
    row = df_ms[df_ms['Size'] == size].iloc[0]
    algorithms = df.columns[1:]
    times = [row[algo] for algo in algorithms]
    
    bars = axes[idx].bar(range(len(algorithms)), times, 
                         color=[colors[algo] for algo in algorithms],
                         alpha=0.8, edgecolor='black', linewidth=1.5)
    
    axes[idx].set_xlabel('Algorytm', fontsize=10, fontweight='bold')
    axes[idx].set_ylabel('Czas (ms)', fontsize=10, fontweight='bold')
    axes[idx].set_title(f'n = {int(size):,}', fontsize=12, fontweight='bold')
    axes[idx].set_xticks(range(len(algorithms)))
    axes[idx].set_xticklabels(algorithms, rotation=45, ha='right')
    axes[idx].grid(True, alpha=0.3, axis='y', linestyle='--')
    
    # Dodanie wartości na słupkach
    for bar in bars:
        height = bar.get_height()
        axes[idx].text(bar.get_x() + bar.get_width()/2., height,
                      f'{height:.1f}',
                      ha='center', va='bottom', fontsize=8)

plt.tight_layout()
plt.savefig('comparison_bars.png', dpi=300, bbox_inches='tight')
print("✓ Wykres 3 zapisany: comparison_bars.png")

# ====================================
# WYKRES 4: Heatmapa wydajności
# ====================================
fig, ax = plt.subplots(figsize=(10, 8))

# Przygotowanie danych do heatmapy
heatmap_data = df_ms.set_index('Size').T

# Utworzenie heatmapy
im = ax.imshow(heatmap_data.values, cmap='YlOrRd', aspect='auto')

# Ustawienia osi
ax.set_xticks(np.arange(len(heatmap_data.columns)))
ax.set_yticks(np.arange(len(heatmap_data.index)))
ax.set_xticklabels([f'{int(x):,}' for x in heatmap_data.columns])
ax.set_yticklabels(heatmap_data.index)

# Obrót etykiet
plt.setp(ax.get_xticklabels(), rotation=45, ha="right", rotation_mode="anchor")

# Dodanie wartości w komórkach
for i in range(len(heatmap_data.index)):
    for j in range(len(heatmap_data.columns)):
        text = ax.text(j, i, f'{heatmap_data.values[i, j]:.1f}',
                      ha="center", va="center", color="black", fontsize=8)

ax.set_title('Heatmapa czasu wykonania (ms)', fontsize=14, fontweight='bold', pad=20)
ax.set_xlabel('Rozmiar tablicy (n)', fontsize=12, fontweight='bold')
ax.set_ylabel('Algorytm', fontsize=12, fontweight='bold')

# Dodanie colorbar
cbar = plt.colorbar(im, ax=ax)
cbar.set_label('Czas (ms)', rotation=270, labelpad=20, fontweight='bold')

plt.tight_layout()
plt.savefig('comparison_heatmap.png', dpi=300, bbox_inches='tight')
print("✓ Wykres 4 zapisany: comparison_heatmap.png")

# ====================================
# WYKRES 5: Wykres względnej wydajności
# ====================================
fig, ax = plt.subplots(figsize=(12, 7))

# Normalizacja względem QuickSort
df_relative = df_ms.copy()
for col in df.columns[1:]:
    df_relative[col] = df_ms[col] / df_ms['QuickSort']

for algorithm in df.columns[1:]:
    if algorithm != 'QuickSort':
        ax.plot(df['Size'], df_relative[algorithm], marker='o', linewidth=2.5,
                label=f'{algorithm} / QuickSort', color=colors[algorithm], markersize=8)

ax.axhline(y=1.0, color='#4ECDC4', linestyle='--', linewidth=2, label='QuickSort (baseline)')
ax.set_xlabel('Rozmiar tablicy (n)', fontsize=12, fontweight='bold')
ax.set_ylabel('Względna wydajność (Quick Sort = 1.0)', fontsize=12, fontweight='bold')
ax.set_title('Względna wydajność algorytmów (Quick Sort jako punkt odniesienia)', 
             fontsize=14, fontweight='bold', pad=20)
ax.legend(fontsize=11, loc='upper left', framealpha=0.9)
ax.grid(True, alpha=0.3, linestyle='--')
ax.set_xlim(left=0)

plt.tight_layout()
plt.savefig('comparison_relative.png', dpi=300, bbox_inches='tight')
print("✓ Wykres 5 zapisany: comparison_relative.png")

# ====================================
# WYKRES 6: Złożoność teoretyczna vs rzeczywista
# ====================================
fig, ax = plt.subplots(figsize=(12, 7))

# Dla n od najmniejszego do największego
n_values = df['Size'].values
n_max = n_values[-1]

# Funkcje teoretyczne (znormalizowane)
def normalize(values):
    return values / values[-1] * df_ms['QuickSort'].iloc[-1]

theoretical = {
    'O(n log n)': normalize(n_values * np.log2(n_values)),
    'O(n + k)': normalize(n_values + 10000),  # k=10000 z zakresu danych
    'O(n²)': normalize(n_values ** 2)
}

# Linie teoretyczne
ax.plot(n_values, theoretical['O(n log n)'], '--', linewidth=2, 
        color='gray', label='Teoretyczne O(n log n)', alpha=0.6)

# Algorytmy rzeczywiste
for algorithm in ['QuickSort', 'MergeSort', 'HeapSort']:
    ax.plot(df['Size'], df_ms[algorithm], marker='o', linewidth=2.5,
            label=f'{algorithm} (rzeczywiste)', color=colors[algorithm], markersize=8)

ax.set_xlabel('Rozmiar tablicy (n)', fontsize=12, fontweight='bold')
ax.set_ylabel('Czas wykonania (ms)', fontsize=12, fontweight='bold')
ax.set_title('Złożoność teoretyczna vs rzeczywista wydajność', 
             fontsize=14, fontweight='bold', pad=20)
ax.legend(fontsize=11, loc='upper left', framealpha=0.9)
ax.grid(True, alpha=0.3, linestyle='--')
ax.set_xlim(left=0)
ax.set_ylim(bottom=0)

plt.tight_layout()
plt.savefig('comparison_theoretical.png', dpi=300, bbox_inches='tight')
print("✓ Wykres 6 zapisany: comparison_theoretical.png")

# ====================================
# WYKRES 7: Wykres pudełkowy (speedup dla różnych n)
# ====================================
fig, ax = plt.subplots(figsize=(12, 7))

# Przygotowanie danych - czas w ms dla każdego algorytmu
data_to_plot = [df_ms[col].values for col in df.columns[1:]]

box = ax.boxplot(data_to_plot, labels=df.columns[1:], patch_artist=True,
                 medianprops=dict(color='red', linewidth=2),
                 boxprops=dict(facecolor='lightblue', alpha=0.7),
                 whiskerprops=dict(linewidth=1.5),
                 capprops=dict(linewidth=1.5))

# Kolorowanie pudełek
for patch, algorithm in zip(box['boxes'], df.columns[1:]):
    patch.set_facecolor(colors[algorithm])
    patch.set_alpha(0.7)

ax.set_ylabel('Czas wykonania (ms)', fontsize=12, fontweight='bold')
ax.set_xlabel('Algorytm', fontsize=12, fontweight='bold')
ax.set_title('Rozkład czasu wykonania algorytmów (wszystkie rozmiary)', 
             fontsize=14, fontweight='bold', pad=20)
ax.grid(True, alpha=0.3, axis='y', linestyle='--')
plt.xticks(rotation=45, ha='right')

plt.tight_layout()
plt.savefig('comparison_boxplot.png', dpi=300, bbox_inches='tight')
print("✓ Wykres 7 zapisany: comparison_boxplot.png")

# ====================================
# STATYSTYKI
# ====================================
print("\n" + "="*60)
print("STATYSTYKI WYDAJNOŚCI")
print("="*60)

# Średni czas dla każdego algorytmu
print("\nŚredni czas wykonania (ms):")
for col in df.columns[1:]:
    avg_time = df_ms[col].mean()
    print(f"  {col:15s}: {avg_time:8.2f} ms")

# Najszybszy algorytm dla każdego rozmiaru
print("\nNajszybszy algorytm dla każdego rozmiaru:")
for idx, row in df_ms.iterrows():
    size = int(row['Size'])
    times = row[1:]
    fastest = times.idxmin()
    fastest_time = times.min()
    print(f"  n = {size:6,}: {fastest:15s} ({fastest_time:.2f} ms)")

# Speedup względem najwolniejszego
print("\nSpeedup względem najwolniejszego (dla n=50000):")
last_row = df_ms.iloc[-1]
max_time = last_row[1:].max()
for col in df.columns[1:]:
    speedup = max_time / last_row[col]
    print(f"  {col:15s}: {speedup:.2f}x")

print("\n" + "="*60)
print("✓ Wszystkie wykresy zostały wygenerowane!")
print("="*60)
