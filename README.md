---
pagetitle:  Tietoliikenteen Sovellusprojekti
author: Juho Laurila
---

# Tietoliikenteen Sovellusprojekti
Vuoden 2022 tietoliikenteen sovellusprojekti
<br/>
<br/>
# Arkkitehtuurikuva
![image](https://user-images.githubusercontent.com/97531298/199923738-0a49c750-2408-4f4b-a696-a13558a3ca13.png)

# Arduinon toiminta
## Komponentit
- GY-61 Kiihtyvyysanturi
- Arduino
- RWS-371 Vastaanotin
- TWS-BS Lähetin

## Koodi
> Koodi koostuu pääohjelmasta ja kahdesta luokasta (accelerator ja messaging).
> 
> Accelerator luokkaa käytetään mittausten tekemiseen ja sen tallentamiseen Measurement nimiseen struktiin, jossa on sisällä x,y,z arvot.
>
> Messaging luokkaa käytään datan muokkamiseen lähetettävään muotoon ja datan lähettämiseen sekä varmistusviestin vastaanottamiseen. createMessage metodissa x,y,z arvoista muodostetaan jokaisesta 2 high bittiä ja 8 low bittiä jotta data saadaan siirrettyä.
>
> Pääohjelmassa määritetään mittausten määrä sekä missä asennossa mittaukset tehdään käyttäjän inputin mukaan. Asento sijoitetaan flags nimiseen muuttujaan hexadecimaalina, joka lähetetään myös tietokantaan.