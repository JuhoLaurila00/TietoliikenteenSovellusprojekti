import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from sklearn.preprocessing import StandardScaler
from sklearn.cluster import KMeans

data = np.loadtxt('putty.log')

nData = np.zeros((int(data.shape[0] / 3), 3))

i = 0
tracker = 0
while i < nData.shape[0]:
    nData[i][0] = data[tracker]
    nData[i][1] = data[tracker+1]
    nData[i][2] = data[tracker+2]
    i+=1
    tracker+=3
    
print(nData)