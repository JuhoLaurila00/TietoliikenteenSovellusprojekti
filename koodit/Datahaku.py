import requests
import csv

r = requests.get('http://172.20.241.9/luedataa_kannasta_groupid_csv.php?groupid=59')

data = r.text

print(data)

with open('data.csv', 'w') as f:
    f.write(data) 