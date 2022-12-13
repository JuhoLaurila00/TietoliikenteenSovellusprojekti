---
author: Juho Laurila
---

# **Tietoliikenteen Sovellusprojekti**
Syksyn 2022  tietoliikenteen sovellusprojekti.

## **Sisältö**
1. [Kuvaus Projektista](#kuvaus-projektista)
2. [Käytetyt Ohjelmistot](#käytetyt-ohjelmistot)
3. [Arkkitehtuuri](#arkkitehtuuri)
4. [Tehdyt Ohjelmat](#tehdyt-ohjelmat)
5. [Arduino mittaukset ja lähetys](#arduino-mittaukset-ja-lähetys)
    1. [Komponentit](#komponentit)
    2. [Arduinon ohjelma](#arduinon-ohjelma)
6. [Python](#python)
    1. [Kirjastot](#kirjastot)
    2. [TCP/socket ja datahaku](#tcpsocket-ja-datahaku)
    3. [Requests (MainDatahaku.py)](#requests-maindatahakupy)
    4. [K-means](#k-means)
    5. [Confusion Matrix](#confusion-matrix)
7. [Arduino K-means](#arduino-k-means)

</br>

## **Kuvaus Projektista**

  Projektissa käytetään arduinoa xyz kiihtyvysdatan mittaamiseen ja lähettämiisen opettajan vastaanottavaan laitteeseen 433MHz radiolähettimellä. Laite laittaa datan MySQL tietokantaan, josta se sitten haetaan omalla tietokoneella pythonilla ja käsitellään se K-means algoritmilla. Tarkkuus tarkistetaan tämän jälkeen arduinolla, kun K-means koodi tallentaa CenterPoints.h nimisen tiedoston, jota tullaan käyttämään arduino koodissa.

</br>

## **Käytetyt Ohjelmistot**

- Visual Studio Code (Python koodille)
- Arduino IDE (Arduino koodille)
- Wireshark (Data liikenteen seuraamiseen)

</br>


## **Arkkitehtuuri**

![image](https://user-images.githubusercontent.com/97531298/199923738-0a49c750-2408-4f4b-a696-a13558a3ca13.png)

</br>

## **Tehdyt Ohjelmat**
Lista tehdyistä ohjelmista, joita projekti käyttää:

- Transmitter.ino
    - accelerator luokka
    - messaging luokka
- MainDatahaku.py
- Kmeans.py
- ArduinoKmeans.ino
- ConfusionMatrix.py

Lista tehdyistä ohjelmista, joita käytin testailuun:
- RequestsDatahaku.py
- ConnectorDatahaku.py
- TCPSocketDatahaku.py

Tiedostot joita ohjelmat tekevät:
- RequestsDatahaku.py, ConnectorDatahaku.py, TCPSocketDatahaku.py
    - -> data.csv
- MainDatahaku.py
    - -> xyz_data.csv

Kuvaukset ohjelmista alempana

</br>

## **Arduino mittaukset ja lähetys**
### **Komponentit**
- GY-61 Kiihtyvyysanturi
- Arduino
- RWS-371 Vastaanotin
- TWS-BS Lähetin

### **Arduinon ohjelma**
 Koodi koostuu pääohjelmasta ja kahdesta luokasta (accelerator ja messaging).
 
 Accelerator luokkaa käytetään mittausten tekemiseen ja sen tallentamiseen Measurement nimiseen struktiin, jossa on sisällä x,y,z arvot.

 Messaging luokkaa käytään datan muokkamiseen lähetettävään muotoon ja datan lähettämiseen sekä varmistusviestin vastaanottamiseen. createMessage metodissa x,y,z arvoista muodostetaan jokaisesta 2 high bittiä ja 8 low bittiä jotta data saadaan siirrettyä.

 Pääohjelmassa määritetään mittausten määrä sekä missä asennossa mittaukset tehdään käyttäjän inputin mukaan. Asento sijoitetaan flags nimiseen muuttujaan hexadecimaalina, joka lähetetään myös tietokantaan.

</br>

## **Python**
Ohjelmat joiden nimen edessä on [T] ovat testi ohjelmia. [P] merkitsee ohjelmat, joita projekti käyttää toimiakseen.


### **Kirjastot**
Lista projektissa käytetyistä kirjastoista (ei sisällä socket tai mysql connector kirjastoja, koska niitä käytin vain testi ohjelmissa):
- Numpy
- Matplotlib
- sklearn
- Pandas
- Requests

</br>

### **TCP/socket ja datahaku**
 Tiedon sain haettua monella eri tapaa, jotka ovat:
 - requests (RequestsDatahaku.py ja MainDatahaku.py)
 - mysql.connector (ConnectorDatahaku.py)
 - TCP-socket (TCPSocketDatahaku.py)

 Käytin requestia lopullisen tiedon hakemiseen, joka syötetään k-means:ille. Tein näin, koska requests:illa tiedon sai helpoiten ja muiden ratkaisujen kanssa oli ongelmia esim: 
 - TCP-socketilla ei saanut kaikkea tietoa tietokannasta (Vain 300 riviä tietoa)
 - mysql.connector:illa sain kaiken tiedon tietokannasta, mutta sen oli turhan sotkuinen, enkä saanut tietoa helposti formatoitua pandaksella.

</br>

 ### **Requests (MainDatahaku.py)**

 Ohjelma hakee data r nimiseen muuttujaan requests.get komennolla, jonka jälkeen se muutetaan tekstiksi data nimiseen muuttujaan.
   
Ohjelma luo ja tallentaa datan xyz_data.csv tiedostoon seuraavalla koodilla:
<pre>
with open('xyz_data.csv', 'w') as f:

f.write(data)
</pre> 
  
Heti sen jälkeen ohjelma formatoi saadun datan selvemmäksi K-means ohjelmalle tällä koodilla:
<pre>
df = pd.read_csv('xyz_data.csv', delimiter=';', header=None)
print(df)
df.to_csv('xyz_data.csv')
</pre>

Data on nyt valmis K-means algoritmille.

</br>

### **K-means**

Ensimmäisenä ohjelma käyttää pandasta xyz_data.csv tuomiseen ohjelmaan. Dataframe johon data laitettiin pandaksella muutetaan numpy arrayksi. 
<pre>
df = pd.read_csv('xyz_data.csv', usecols=['5','6','7'])
print(df)
nData=df.to_numpy()
</pre>

Sen jälkeen arvotaan 4 keskipistettä satunnaisesti datan isoimman ja pienimmän arvon mukaan np.random.randint functiolla. 
<pre>
CenterPoints = np.random.randint(np.min(nData),np.max(nData),size=(4,3))
</pre>

Ohjelma aloittaa sitten uusien keskipisteidän löytämisen for looppien sisällä laskemalla jokaisen arvotun keskipisteen etäisyyden jokaiseen xyz datapisteeseen. Sitten katsotaan mikä neljästä keskipisteestä oli lähimpänä kyseiseen xyz datapisteseen. Ohjelma antaa sitten sille keskipisteelle "pisteen" Counts muuttujaan, joka oli lähimpänä sitä xyz datapistettä ja lisää centerPointCumulativeSum arrayhin datapisteen arvot siihen kohtaan mikä keskipiste oli lähimpänä datapistettä (esim keskipiste 2 oli lähimpänä datapistettä niin centerPointCumulativeSum arrayn kohtaan 2 lisätään datapisteen xyz arvot).
<pre>
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
</pre>

Sitten mennään uuten for looppin, jossa "arvotaan" uudet keksipisteet. Jos edellien arvottu keskipiste ei saanut yhtään pistettä (ei ollut lähimpänä yhtäkään datapistettä), sille arvotaan satunnaisesti uusi xyz arvo. Jos keksipiste sai enemmän pisteitä kuin 0, niin uusi keskipisteen paikka määritetään jakamalla CenterPointCumulativeSum pisteiden määrällä.
<pre>
for i in range(4):
        if Counts[0][i] == 0:
            CenterPoints[i] = np.random.randint(np.min(nData),np.max(nData),size=(1,3))
        else:
            CenterPoints[i] = centerPointCumulativeSum[i]/Counts[0][i]

AllCenterPoints[k] = CenterPoints.reshape(1,12)
</pre>

Ohjelma myös tallentaa kaikkien looppien varrella olleiden keskipisteiden paikat AllCenterPoints arrayhin. Sitten kun kaikki loopit on tehty ohjelma käyttää matplotlibiä datapisteiden, keskipisteiden ja varrella olleiden keskipisteiden plottaamiseen. Ja tallentaa myös lopulliset keskipisteet CenterPoints.h tiedostoon arduinoa varten.

</br>

![kmeans1](https://user-images.githubusercontent.com/97531298/206868055-11be2b60-5968-4c7b-aca1-247cfa457db9.png)
 
Kuva datasta plotattuna matplotlibillä ennen k-means algoritmin määrittämiä keskipisteitä. Jokainen sininen pallo on xyz datapiste, joita on yli 400 omassa datassani. Osa palloista on niin lähellä toisiaan että kuva näyttää ne päällekkäin. 

</br>

![kmeans2](https://user-images.githubusercontent.com/97531298/206868058-67e9b2d7-c56c-4480-af75-0957dac56724.png)

Kuva datasta plotattuna algoritmin jälkeen. Punaiset rastit ovat keskipisteet ja vihreät kolmiot ovat pisteitä joissa keskipiste oli jossain välissä algoritmia.

</br>

### **Confusion Matrix**

Suosittelen lukemaan Arduino K-means osan ennen kuin luet tämän.

</br>

Confusion matrix ei ollut kovin monimutkainen toteuttaa sklearnia ja numpyä käyttäen. Ensiksi koodissa importataan kirjastot ja data: 
<pre>
import numpy as np
from sklearn.metrics import confusion_matrix

data = np.loadtxt('Data.log')       #Data jossa heiluttelin arduinoa samalla
data2 = np.loadtxt('Data2.log')     #Data jossa pidin arduinoa annetussa asennossa koko ajan
</pre>

Sitten sijoitetaan Data.log tiedot kahteen numpy arrayhin. dataTrue on ArduinoKmeans ohjelmassa käyttäjän antama asento ja dataPred on algoritmin antama asento. Sama tehtiin Data2.log tiedoille.
<pre>
dataTrue = data[:,0]
dataPred = data[:,1]
data2True = data2[:,0]
data2Pred = data2[:,1]
</pre>

Sitten koodissa tehdään confusion matrixit:
<pre>
cm = confusion_matrix(dataTrue, dataPred) 
print("Heiluteltu arduino CM")
print(cm)

print("")

cm2 = confusion_matrix(data2True, data2Pred)
print("Oikea CM")
print(cm2)
</pre>
<sup>dataTrue, dataPred jne muuttujia ei olisi pakko tehdä. Tiedot pystyisi syöttämään suoraan confusion matrixiin, mutta tein muuttujat koska se teki mielestäni koodista selvemmän.</sup>

Alla kuva tuloksista

![CM](https://user-images.githubusercontent.com/97531298/206867805-340ebdb5-3f3a-413b-ac64-2d08fd3e56e5.PNG)

</br>

## **Arduino K-means**

ArduinoKmeans ohjelmassa katsotaan kuinka tarkka algoritmi on kmeansin antamilla keskipisteillä. Ensimmäiseksi otetaan ohjelmaan mukaan edellisen ohjelman tekemä CenterPoints.h tiedosto, joka sisältää kmeansin antamat keskipisteet. 
<pre>
#include "CenterPoints.h"
</pre>

Itse arduinoon oli aluksi kytketty nappi ja kiihtyvyysanturi. Nappia painamalla arduino teki yhden mittauksen ja tarkisti mikä neljästä keskipisteestä oli lähimpänä kiihtyvyysanturin arvoa. Tein funktion joka laski etäisyyden:
<pre>
int Distance(int mX,int mY,int mZ,int cX,int cY,int cZ)
{
    int Value1 = pow(mX-cX,2);
    int Value2 = pow(mY-cY,2);
    int Value3 = pow(mZ-cZ,2);
    int dist = sqrt(Value1+Value2+Value3);
    return dist;
}
</pre>

Ohjelma teki Distances nimisen arrayn johon etäisyys jokaiseen keskipisteeseen laitettiin. Sen jälkeen tarkistetaan mikä keskipisteistä oli lähimpänä for loopissa.
<pre>
    Distances[0] = Distance(X,Y,Z,kp[0][0],kp[0][1],kp[0][2]);
    Distances[1] = Distance(X,Y,Z,kp[1][0],kp[1][1],kp[1][2]);
    Distances[2] = Distance(X,Y,Z,kp[2][0],kp[2][1],kp[2][2]);
    Distances[3] = Distance(X,Y,Z,kp[3][0],kp[3][1],kp[3][2]);

    for(int a = 0; a < 4; a++){
      if (Distances[a] < minVal) {
         minVal = Distances[a];
      }
    }
</pre>
<sup>
Koodissa minVal muuttuja alustettiin arvolla, joka oli pakosta suurempi kuin yksikään mittauksen arvo. Tässä tapauksessa 400. Alustus tehtiin joka napin painalluksella heti alussa.
</sup>

</br>

Kun olin testannut, että koodi toimii muutin sitä sellaiseksi että se kysyy käyttäjältä montako mittausta tehdään ja missä asennossa. Ohjelma tulosti loopin sisällä sitten käyttäjän väittämän asennon ja algoritmin antaman asennon.
<pre>
    Serial.print(GivenPos);
    Serial.print("  ");
    if(minVal == Distances[0]){Serial.print("1");}
    if(minVal == Distances[1]){Serial.print("2");}
    if(minVal == Distances[2]){Serial.print("3");}
    if(minVal == Distances[3]){Serial.print("4");}
</pre>
<sup>GivenPos on käyttäjän antama asento.</sup></br>

Sitten kun tulokset tulivat sarjamonitorille kopioin ne sieltä Data.log ja Data2.log tiedostoihin confusion matrixia varten. Tein yhteensä 400 mittausta joka asennossa molempiin tiedostoihin. Tiedostojen ero on se, että toisessa on mittaukset, jossa heilutin arduinoa samalla. Tässä pieni pätkä Data.log:ista:
<pre>
1  3
1  3
1  3
1  1
1  1
1  1
</pre>
<sup>Kuten näkyy väitin asennoksi 1 (UP), mutta joissakin kohti algoritmi sanoo asennoksi 3 (LEFT), joka on oikea asento.</sup>
