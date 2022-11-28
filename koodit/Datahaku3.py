import requests
import pandas as pd

r = requests.get('http://172.20.241.9/luedataa_kannasta_groupid_csv.php?groupid=59')

data = r.text

print(data)

with open('data.csv', 'w') as f:
    f.write(data) 

df = pd.read_csv('data.csv', delimiter=';', header=None)
print(df)
df.to_csv('data.csv')