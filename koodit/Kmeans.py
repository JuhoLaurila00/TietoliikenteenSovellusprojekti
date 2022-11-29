import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

'''
def DistanceCalc(Arr1, Arr2):
    Value1 = pow(Arr1[0]-Arr2[0],2)
    Value2 = pow(Arr1[1]-Arr2[1],2)
    Value3 = pow(Arr1[2]-Arr2[2],2)
    dist = np.sqrt(Value1+Value2+Value3)
    return dist
'''

df = pd.read_csv('data.csv', usecols=['5','6','7'])
print(df)
nData=df.to_numpy()

'''
data = np.loadtxt('putty.log')

nData = np.zeros((int(data.shape[0] / 3), 3),dtype=int)
nData[:,0] = data[0:len(data):3]
nData[:,1] = data[1:len(data):3]
nData[:,2] = data[2:len(data):3]
'''

numberOfRows = nData.shape[0]


CenterPoints = np.random.randint(np.min(nData),np.max(nData),size=(4,3))
                                           

numberOfLoops = 100
AllCenterPoints = np.zeros((numberOfLoops,12))

for k in range(numberOfLoops):
    centerPointCumulativeSum = np.zeros((4,3),dtype=int)                             
    Counts = np.zeros((1,4),dtype=int)                                                
    Distances = np.zeros((1,4),dtype=int)   
    for i in range(numberOfRows):
        for j in range(4):
            Distances[0][j] = np.linalg.norm(nData[i]-CenterPoints[j])
        Cluster = np.argmin(Distances)
        centerPointCumulativeSum[Cluster] += nData[i]
        Counts[0][Cluster] += 1

    for i in range(4):
        if Counts[0][i] == 0:
            CenterPoints[i] = np.random.randint(np.min(nData),np.max(nData),size=(1,3))
        else:
            CenterPoints[i] = centerPointCumulativeSum[i]/Counts[0][i]
    
    AllCenterPoints[k] = CenterPoints.reshape(1,12)

    

print(centerPointCumulativeSum)
print(Counts)
print(CenterPoints)

AllCenterPoints = AllCenterPoints.reshape(numberOfLoops*4,3)

fig = plt.figure()
ax = fig.add_subplot(projection='3d')

ax.scatter(nData[:,0],nData[:,1],nData[:,2],marker='x')
ax.scatter(CenterPoints[:,0],CenterPoints[:,1], CenterPoints[:,2], color='red',marker='X', s=100)
ax.scatter(AllCenterPoints[:,0],AllCenterPoints[:,1],AllCenterPoints[:,2], color='green',marker='^')

plt.show()




