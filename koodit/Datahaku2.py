import mysql.connector

connection = mysql.connector.connect(host='172.20.241.9',
                                    database='measurements',
                                    user='dbaccess_ro',
                                    password='vsdjkvwselkvwe234wv234vsdfas')

sql_select_Query = "select * from rawdata where groupid=59"

cursor = connection.cursor()
cursor.execute(sql_select_Query)

data = cursor.fetchall()
print("Total number of rows in table: ", cursor.rowcount)
print("Column Names: ", cursor.column_names)

print(cursor)
with open('data.csv', 'w') as f:
    for (x) in data:
        f.write(f"{x}\n")