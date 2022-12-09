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
    2. [K-means](#k-means)
    3. [Confusion Matrix](#confusion-matrix)
7. [Arduino K-means](#arduino-k-means)

## Kuvaus Projektista
<span style="color:red">
<font size="4">
!!! LYHYT KUVAUS !!! 
</font>
</span>

## Käytetyt Ohjelmistot

<span style="color:red">
<font size="4">
!!! KAIKKI KÄYTETYT OHJELMAT !!! 
</font>
</span>

## Arkkitehtuuri

![image](https://user-images.githubusercontent.com/97531298/199923738-0a49c750-2408-4f4b-a696-a13558a3ca13.png)

<span style="color:red">
<font size="5">
!!! PÄIVITÄ KUVA !!! 
</font>
</span>

## Tehdyt Ohjelmat
> Lista tehdyistä ohjelmista, joita projekti käyttää:

> Kuvaukset ohjelmista alempana

<span style="color:red">
<font size="5">
!!! MUOKKAA OHJELMIEN NIMET JÄRKEVIKSI !!!
</font>
</span>

## Arduino mittaukset ja lähetys
### Komponentit
- GY-61 Kiihtyvyysanturi
- Arduino
- RWS-371 Vastaanotin
- TWS-BS Lähetin

### Arduinon ohjelma
> Koodi koostuu pääohjelmasta ja kahdesta luokasta (accelerator ja messaging).
> 
> Accelerator luokkaa käytetään mittausten tekemiseen ja sen tallentamiseen Measurement nimiseen struktiin, jossa on sisällä x,y,z arvot.
>
> Messaging luokkaa käytään datan muokkamiseen lähetettävään muotoon ja datan lähettämiseen sekä varmistusviestin vastaanottamiseen. createMessage metodissa x,y,z arvoista muodostetaan jokaisesta 2 high bittiä ja 8 low bittiä jotta data saadaan siirrettyä.
>
> Pääohjelmassa määritetään mittausten määrä sekä missä asennossa mittaukset tehdään käyttäjän inputin mukaan. Asento sijoitetaan flags nimiseen muuttujaan hexadecimaalina, joka lähetetään myös tietokantaan.

## Python
### TCP/socket ja datahaku
> Tiedon sain haettua monella eri tapaa, jotka ovat:
> - requests (Datahaku.py ja Datahaku3.py)
> - mysql.connector (Datahaku2.py)
> - TCP-socket (TCPSocketClient.py)

> Käytin Datahaku2.py:tä lopullisen tiedon hakemiseen, joka syötetään k-means:ille. Tein näin, koska requests:illa tiedon sai helpoiten ja muiden ratkaisujen kanssa oli ongelmia esim: 
> - TCPSocketClient.py:llä ei saanut kaikkea tietoa tietokannasta
> - Datahaku2.py:llä sain kaiken tiedon tietokannasta, mutta sen oli turhan sotkuinen

<span style="color:red">
<font size="5">
!!! TARKEMPI KUVAUS OHJELMAN TOIMINNASTA !!! 
</font>
</span>

### K-means

![puttylogscatter](https://user-images.githubusercontent.com/97531298/206319716-34ec5c5a-6d3e-44a2-ad66-80aaf8f91109.png)

<span style="color:red">
<font size="5">
!!! PÄIVITÄ/LISÄÄ KUVA OMASTA DATASTA !!! 
</br>
!!! KUVAUS TOIMINNASTA !!!
</font>
</span>

Kuva opettajan datasta (putty.log) tehdystä scatteristä, jossa näkyy neljä clusteria. Keskipisteitä kuvassa ei näy vielä tässä vaiheessa.

### Confusion Matrix

<span style="color:red">
<font size="5">
!!! KUVA TULOKSESTA !!! 
</br>
!!! KUVAUS TOIMINNASTA !!!
</font>
</span>

## Arduino K-means

<span style="color:red">
<font size="5">
!!! KUVAUS TOIMINNASTA !!!
</font>
</span>