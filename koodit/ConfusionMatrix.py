import numpy as np
from sklearn.metrics import confusion_matrix

data = np.loadtxt('Data.log')       #Data jossa heiluttelin arduinoa samalla
data2 = np.loadtxt('Data2.log')     #Data jossa pidin arduinoa annetussa asennossa koko ajan

dataTrue = data[:,0]
dataPred = data[:,1]
data2True = data2[:,0]
data2Pred = data2[:,1]

cm = confusion_matrix(dataTrue, dataPred) 
print("Heiluteltu arduino CM")
print(cm)

print("")

cm2 = confusion_matrix(data2True, data2Pred)
print("Oikea CM")
print(cm2)