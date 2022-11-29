import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('putty.log')

datahyi = np.zeros((40,3),dtype=int)

datahyi[:,0] = data[0:-1:3]
datahyi[:,1] = data[1:-1:3]
datahyi[:,2] = data[2:len(data):3]

NumberOfRows = datahyi.shape[0]

#print(NumberOfRows)
#print(datahyi)

randomCenterPoints = np.random.randint(np.min(datahyi),np.max(datahyi),size=(4,3))  # 4 random X,Y,Z points in the data range
centerPointCumulativeSum = np.zeros((4,3),dtype=int)                                # Cumulative sum of the center points
Counts = np.zeros((1,4),dtype=int)                                                  # Number of points in each cluster
Distances = np.zeros((1,4),dtype=int)                                               # Distance of each point to the center points

#print(randomCenterPoints)

plt.show()



for k in range(100):
    for i in range(NumberOfRows):
        for j in range(4):
            Distances[0][j] = np.linalg.norm(datahyi[i]-randomCenterPoints[j])
        Cluster = np.argmin(Distances)
        centerPointCumulativeSum[Cluster] += datahyi[i]
        Counts[0][Cluster] += 1

    print(centerPointCumulativeSum)
    print(Counts)

    for i in range(4):
        if Counts[0][i] == 0:
            randomCenterPoints[i] = np.random.randint(np.min(datahyi),np.max(datahyi),size=(1,3))
        else:
            randomCenterPoints[i] = centerPointCumulativeSum[i]/Counts[0][i]


fig = plt.figure()
ax = fig.add_subplot(projection='3d')

ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')

ax.scatter(datahyi[:,0],datahyi[:,1],datahyi[:,2])
ax.scatter(randomCenterPoints[:,0],randomCenterPoints[:,1],randomCenterPoints[:,2],color='red')

plt.show()