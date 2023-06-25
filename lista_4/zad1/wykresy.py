import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

dane = pd.read_csv("wyniki/wyniki.csv", sep=";")


dane_k = np.linspace(1, 16, 16, dtype=int)
dane_flow = np.array(dane[::3])
dane_time = np.array(dane[1::3])
dane_paths = np.array(dane[2::3])

sns.lineplot(data=dane, x="k", y="flow")
plt.title("Maksymalny przepływ w zależności od k\nw algorytmie Edmondsa-Karpa")
plt.savefig("./wykresy/ek_flow.png", dpi=300)
plt.clf()

sns.lineplot(data=dane, x="k", y="time")
plt.title("Czas w µs w zależności od k\nw algorytmie Edmondsa-Karpa")
plt.savefig("./wykresy/ek_time.png", dpi=300)
plt.clf()

sns.lineplot(data=dane, x="k", y="aug_paths")
plt.title("# ścieżek powiększających w zależności od k\nw algorytmie Edmondsa-Karpa")
plt.savefig("./wykresy/ek_aug.png", dpi=300)
plt.clf()