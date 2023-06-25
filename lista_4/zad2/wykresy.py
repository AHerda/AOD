import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

dane = pd.read_csv("wyniki/wyniki.csv", sep=";")

for k in range(3, 11):
    temp = dane[dane["k"] == k]
    sns.lineplot(data=temp, x="i", y="size")
    plt.title(f"Wielkość maksymalnego skojarzenia dla k={k}")
    plt.savefig(f"./wykresy/size_k_{k}.png", dpi=300)
    plt.clf()

    temp = dane[dane["k"] == k]
    sns.lineplot(data=temp, x="i", y="time")
    plt.title(f"Czas (µs) działania programu dla k={k}")
    plt.savefig(f"./wykresy/time_k_{k}.png", dpi=300)
    plt.clf()

for i in range(1, 11):
    if i != 10:
        temp = dane[dane["i"] == i]
        sns.lineplot(data=temp, x="k", y="size")
        plt.title(f"Wielkość maksymalnego skojarzenia dla i={i}")
        plt.savefig(f"./wykresy/size_i_{i}.png", dpi=300)
        plt.clf()

        
        temp = dane[dane["i"] == i]
        sns.lineplot(data=temp, x="k", y="time")
        plt.title(f"Czas (µs) działania programu dla i={i}")
        plt.savefig(f"./wykresy/time_i_{i}.png", dpi=300)
        plt.clf()