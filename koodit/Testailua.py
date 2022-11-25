import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from sklearn.preprocessing import StandardScaler
from sklearn.cluster import KMeans

data = np.loadtxt('putty.log')
data = data.reshape(-1,1)

scaler = StandardScaler()

def optimise_k_means(dat, max_k):
    means = []
    inertias = []

    for k in range(1, max_k):
        kmeans = KMeans(n_clusters=k)
        kmeans.fit(dat)

        means.append(k)
        inertias.append(kmeans.inertia_)
        
    fig = plt.subplots(figsize=(10,5))
    plt.plot(means, inertias, 'o-')
    plt.xlabel('number of clusters')
    plt.ylabel('intertia')
    plt.grid(True)
    plt.show()

kmeans = KMeans(n_clusters=4)
kmeans.fit(data)

print(kmeans.labels_)
optimise_k_means(data, 10)