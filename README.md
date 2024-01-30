# Progetto Informatica (Sviluppo di un gioco platform)
In questo file READ.ME riporto tutte le idee che ci siamo detti e ci diremo riguardo al gioco.
## Requisiti base del gioco
Parto scrivendo un breve riassunto dei rquisiti di base richiesti nella consegna del progetto:
1. Sviluppare un gioco **platform** in **grafica ASCII**
2. Il gioco deve presentare più **livelli** 
3. Il gioco deve essere accompagnato da un **punteggio** 
4. Il protagonista deve essere **controllato da tastiera**
### 1. Platform in grafica ASCII
La mappa deve avere una grafica ASCCI e per visualizzarla è possibile usare solamente le librerie **curses/ncurses.h**.
### 2. Gioco a più livelli
Ogni livello è composto da uno schema che viene scelto in modo ***random da un insieme di livelli predefiniti (o generati in modo casuale)***. Ogni volta che viene avviata una nuova partita, bisogna partire da una nuova schermata casuale.
Man mano che la partita avanza anche la **difficoltà deve aumentare** (es. più nemici, meno potenziamenti, ecc...).
Il gioco deve essere infinito, senza alcun tipo di traguardo, e deve essere possibile tornare indietro di schema in qualsiasi momento e trovare esattamente tutto come lo si ha lasciato.
### 3. Punteggio
All'interno del gioco devono essere presenti **diversi tipi di nemici e una valuta**, quest'ultima può essere utilizzata per acquistare potenziamenti (es. vita, poteri, armi, ecc...) all'interno di un ***livello market*** (in cui acquistare vita aggiutiva, poteri, armi ecc...).
### 4. Protagonista e giocatore
Il giocatore umano controlla il protagonista (non lo avreste mai detto vero?). Nel percorso il protagonista potrà incontrare dei **nemici** e **toccandoli o venendo colpito perderà vita**. Questi nemici (a differenza del protagonista) **vengono controllati dal computer** (si possono muovere e sparare/colpire) e possono venire uccisi dal protagonista. Se la vita scende a 0, si finalizza il ***Game Over*** (sconfitta, partita persa). Se il protagonista muore, **mantiene i bonus, i poteri, le armi, ecc...** che ha acquistato e alla prossima partita **comincerà da uno schema random** con una difficoltà impostata in modo proporzionato ai potenziamenti che ha acquisito.
### Impostazioni base del progetto
- Il progetto deve essere realizzato usando le classi e deve perciò essere realizzato in più file 
- Ogni classe deve presentare due file del tipo: **NomeClasse.cpp** e **NomeClasse.hpp**
- **Le stanze e gli elementi in una stanza** devono essere gestiti tramite **strutture dati dinamiche**

# Idee da implementare nel gioco
(Idee discusse in data 02/03/2023)
### Stato di partenza del gioco
- Il personaggio parte con **5 vite**
- **Arma base** (es. spada) - infligge 1 danno 
- Valuta iniziale pari a 0 (es. 0$)
- Potenza base del salto del personaggio pari a 3
### Armi per il personaggio
- Spada (base)
- Pistola (distanza base percorsa dal proiettile = 3)
### Nemici
- Nemico base (leggero - senz'arma)
- Nemico base con arma (leggero - il proiettile si muove dritto in una direzione)
- Nemico volante (senz'arma)
- Nemico volante con arma
- Nemico pesante (con armatura - senz'arma)
- Nemico pesante con arma (con armatura)
- [Nemico Veloce]
### Ostacoli
- Trappole per terra
- Pedane da teletrasporto
## Potenziamenti
### Movimento
- Movimento+ (aumenta la velocità di movimento del personaggio)
- Salto+ (aumenta la velocità di salto del personaggio)
### Potenziamenti Armi
- Spada+ (Aumenta la velocità d'attacco della spada)
- Pistola+ (Aumenta il danno della pistola)
### Vita
- Capacità+ (Aumenta la quantità di vita totale)
- Armatura (Attiva armatura che assorbe 3 di danno)
- Armatura+ (Aumenta la robustezza dell'armatura | es. Armatura Lv. 2 = 5, Lv. 3 = 6 ecc...)
### Potenziamenti generali
- Moltiplicatore di valuta (I "soldi" guadagnati sconfiggendo nemici aumenta)
- [Visore per trappole]

test livia