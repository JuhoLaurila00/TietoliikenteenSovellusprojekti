<span style="color:red">
<font size="10">
WIP README 
</font>
</span>

# Tietoliikenteen Sovellusprojekti
Syksyn 2022  tietoliikenteen sovellusprojekti

## Sisältö
1. [Kuvaus Projektista](#kuvaus-projektista)
2. [Käytetyt Ohjelmistot](#käytetyt-ohjelmistot)
3. [Arkkitehtuuri](#arkkitehtuuri)
4. [Tehdyt Ohjelmat](#tehdyt-ohjelmat)
5. [Arduino mittaukset ja lähetys](#arduino-mittaukset-ja-lähetys)
    1. [Komponentit](#komponentit)
    2. [Arduinon ohjelma](#arduinon-ohjelma)
6. [Python](#python)
    1. [TCP/socket ja datahaku](#tcpsocket-ja-datahaku)
    2. [Requests (MainDatahaku.py)](#requests-maindatahakupy)
    3. [K-means](#k-means)
    4. [Confusion Matrix](#confusion-matrix)
7. [Arduino K-means](#arduino-k-means)

</br>

## Kuvaus Projektista

  Projektissa käytetään arduinoa xyz kiihtyvysdatan mittaamiseen ja lähettämiisen opettajan vastaanottavaan laitteeseen 433MHz radiolähettimellä. Laite laittaa datan MySQL tietokantaan, josta se sitten haetaan omalla tietokoneella pythonilla ja käsitellään se K-means algoritmilla. Tarkkuus tarkistetaan tämän jälkeen arduinolla, kun K-means koodi tallentaa CenterPoints.h nimisen tiedoston, jota tullaan käyttämään arduino koodissa.

</br>

## Käytetyt Ohjelmistot

- Visual Studio Code (Python koodille)
- Arduino IDE (Arduino koodille)
- Wireshark (Data liikenteen seuraamiseen)

</br>


## Arkkitehtuuri

![image](https://user-images.githubusercontent.com/97531298/199923738-0a49c750-2408-4f4b-a696-a13558a3ca13.png)

</br>

## Tehdyt Ohjelmat
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

## Arduino mittaukset ja lähetys
### Komponentit
- GY-61 Kiihtyvyysanturi
- Arduino
- RWS-371 Vastaanotin
- TWS-BS Lähetin

### Arduinon ohjelma
 Koodi koostuu pääohjelmasta ja kahdesta luokasta (accelerator ja messaging).
 
 Accelerator luokkaa käytetään mittausten tekemiseen ja sen tallentamiseen Measurement nimiseen struktiin, jossa on sisällä x,y,z arvot.

 Messaging luokkaa käytään datan muokkamiseen lähetettävään muotoon ja datan lähettämiseen sekä varmistusviestin vastaanottamiseen. createMessage metodissa x,y,z arvoista muodostetaan jokaisesta 2 high bittiä ja 8 low bittiä jotta data saadaan siirrettyä.

 Pääohjelmassa määritetään mittausten määrä sekä missä asennossa mittaukset tehdään käyttäjän inputin mukaan. Asento sijoitetaan flags nimiseen muuttujaan hexadecimaalina, joka lähetetään myös tietokantaan.

</br>

## Python
Ohjelmat joiden nimen edessä on [T] ovat testi ohjelmia. [P] merkitsee ohjelmat, joita projekti käyttää toimiakseen.

### TCP/socket ja datahaku
 Tiedon sain haettua monella eri tapaa, jotka ovat:
 - requests (RequestsDatahaku.py ja MainDatahaku.py)
 - mysql.connector (ConnectorDatahaku.py)
 - TCP-socket (TCPSocketDatahaku.py)

 Käytin requestia lopullisen tiedon hakemiseen, joka syötetään k-means:ille. Tein näin, koska requests:illa tiedon sai helpoiten ja muiden ratkaisujen kanssa oli ongelmia esim: 
 - TCP-socketilla ei saanut kaikkea tietoa tietokannasta (Vain 300 riviä tietoa)
 - mysql.connector:illa sain kaiken tiedon tietokannasta, mutta sen oli turhan sotkuinen, enkä saanut tietoa helposti formatoitua pandaksella.

 ### Requests (MainDatahaku.py)

 Ohjelma hakee data r nimiseen muuttujaan requests.get komennolla, jonka jälkeen se muutetaan tekstiksi data nimiseen muuttujaan.
   
Ohjelma luo ja tallentaa datan xyz_data.csv tiedostoon seuraavalla koodilla:
> with open('xyz_data.csv', 'w') as f:
>
> f.write(data) 
  
Heti sen jälkeen ohjelma formatoi saadun datan selvemmäksi K-means ohjelmalle tällä koodilla:
>df = pd.read_csv('xyz_data.csv', delimiter=';', header=None)
>
>print(df)
>
>df.to_csv('xyz_data.csv')

Data on nyt valmis K-means algoritmille.

### K-means

![KmeansNoCentres](https://user-images.githubusercontent.com/97531298/206867795-27e7f2ee-ad64-4867-9fe5-4d7fc70bac0a.png)
![Kmeans](https://user-images.githubusercontent.com/97531298/206867799-ed382f48-2448-4f95-989e-91aff4e896cc.png)


<span style="color:red">
<font size="5">
!!! PÄIVITÄ/LISÄÄ KUVA OMASTA DATASTA !!! 
</br>
!!! KUVAUS TOIMINNASTA !!!
</font>
</span>

Kuva opettajan datasta (putty.log) tehdystä scatteristä, jossa näkyy neljä clusteria. Keskipisteitä kuvassa ei näy vielä tässä vaiheessa.

### Confusion Matrix
![CM](https://user-images.githubusercontent.com/97531298/206867805-340ebdb5-3f3a-413b-ac64-2d08fd3e56e5.PNG)

<span style="color:red">
<font size="5">
!!! KUVA TULOKSESTA !!! 
</br>
!!! KUVAUS TOIMINNASTA !!!
</font>
</span>

</br>

## Arduino K-means

<span style="color:red">
<font size="5">
!!! KUVAUS TOIMINNASTA !!!
</font>
</span>
