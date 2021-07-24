# Zadanie

[[_TOC_]]

# Hradlové siete

## Základný popis

Hradlová sieť sa skladá z _logických hradiel_, ktorej vstupy a výstupy môžu byť prepojené. Hradlová sieť aj každé hradlo môžu mať ľubovoľný počet vstupov a výstupov. Hradlá v hradlovej sieti môžu mať:
- vstupy pripojené na výstup iného hradla alebo vstup hradlovej siete
- výstupy pripojené na vstupy iného hradla alebo výstup hradlovej siete

## Logika výpočtu

Hradlá počítajú v _trojstavovej logike_. Na vstupoch/výstupoch sa môže objaviť jedna z následujúcich troch hodnôt: 
- `'0'` (logická nula) 
- `'1'` (logická jedna), 
- `'?'` (nedefinovaná hodnota)

## Výpočet hradlovej siete

Celá hradlová sieť pracuje v _taktoch_ - pred prvým taktom sú definované hodnoty len na vstupoch hradlovej siete (okrem výnimiek popísaných ďalej). Doba výpočtu každého hradla je práve 1 takt.

Výsledkom hradlovej siete sú hodnoty na jej výstupoch po _ustálení_ (keď na výstupe každého hradla v nej je hodnota odpovedajúca (podľa prechodovej funkcie) hodnotám na jeho vstupoch a hodnoty na týchto vstupoch sa od predchádzajúceho taktu nezmenili). Počet taktov, po ktorých dôjde ku ustáleniu siete, je dobou výpočtu hradlovej siete. Ak sú medzi hradlami v hradlovej sieti cykly, tak môže dôjsť ku zacykleniu hradlovej siete, teda nikdy nedojde k jej ustáleniu. Pre detekciu cyklov program používa časové obmedzenie - ak sa hradlová sieť neustáli po 1.000.000 taktoch, tak za výsledok hradlovej siete sú považované hodnoty na jej výstupoch po vykonaní 1.000.000 taktov. Hradlová sieť sa môže ustáliť aj v okamihu, keď na nejakom jej výstupe je `'?'`.

## Vstupný súbor, definície hradiel a hradlovej siete

Obsahuje dva druhy blokov: definície **typov hradiel** pomocou ich prechodových funkcií a definície vlastnej **hradlovej siete**.

V každom vstupnom súbore musí byť definovaný aspoň jeden typ hradla a práve jedna hradlová sieť. Vo vstupnom súbore môžu byť definované aj typy hradiel, ktoré nie sú použité v hradlovej sieti.

Jednotlivé hradlá, ich súčasti (vstupy a výstupy) a ich inštancie v hradlovej siete a ostatné súčasti hradlovej siete sú pomenované. Meno takého prvku je ľubovoľná postupnosť znakov, ktorá nesmie:
- obsahovať biele znaky
- obsahovať znaky `'.'`, `';'`
- obsahovať postupnosť znakov `'->'`
- začínať slovom `'end'`

Mená prvkov a kľúčové slová vstupného súboru sú case sensitive. Jednotlivé bloky alebo riadky v blokoch môžu byť vo vstupnom súbore oddelené ľubovoľným počtom:
- prázdnych riadkov
- riadkov obsahujúcich iba biele znaky
- riadkov začínajúcich znakom `';'` - komentár

Každý riadok odpovedajúci jednomu z predchádzajúcich troch bodov sa ignoruje. Ak sa riadok nejakého bloku skladá z viacerých zložiek, tak sú tieto zložky oddelené práve jednou medzerou.

### Blok definície hradiel

#### Syntax

```
    gate meno_hradla
    inputs i1 i2 ... iN
    outputs o1 o2 ... oM
    definicia_prechodovej_funkcie_1
    definicia_prechodovej_funkcie_2
    .
    .
    definicia_prechodovej_funkcie_O
    end
```

#### Vstupy

Počet vstupov je obmedzený `N >= 0`.

Za kľúčovým slovom `inputs` následuje zoznam mien všetkých vstupov. Mená sú jedinečné v definícii daného hradla a nesmú byť rovnaké ako mená vstupov hradlovej siete.

#### Výstupy

Počet výstupov je obmedzený `M >= 1`.

Za kľúčovým slovom `outputs` následuje zoznam mien všetkých výstupov. Mená sú jedinečné v definícii daného hradla a nesmú byť rovnaké ako mená výstupov hradlovej siete.

V počiatočnom stave (pred prvým taktom hradlovej siete) majú všetky výstupy všetkých hradiel následujúce hodnoty:
- ak `N = 0`, hodnoty definované prechodovou funkciou
- ak `N >= 1`, nedefinovanou hodnotou `'?'` 

#### Prechodové funkcie

Každý riadok prechodovej funkcie definuje hodnotu na všetkých výstupoch hradla v závislosti na jednej kombinácii všetkých vstupoch hradla. Na riadku sú najprv hodnoty všetkých vstupov (poradie je určené poradím `inputs`) nasledované hodnotami všetkých výstupov (poradie je určené poradím `outputs`). Ak pre nejakú kombináciu nie je prechodová funkcia explicitne definovaná, tak sa použije následujúca implicitná definícia:
- pre kombináciu vstupov, kde ani jeden nemá hodnotu `'?'` je hodnota všetkých výstupov definovaná ako `'0'`
- pre kombináciu vstupov, kde aspoň jeden má hodnota `'?'` je hodnota všetkých výstupov definovaná ako `'?'`

Explicitná definícia prechodovej funkcie môže byť prázdna - potom sa na hradlo aplikuje len implicitné chovanie prechodovej funkcie.

#### Príklad

Hradlo pomenované `and`, s dvomi vstupmi `i1` a `i2` a jedným výstupom `o` a prechodovou funkciou definovanou podľa logického súčinu:

```
    gate and
    inputs i1 i2
    outputs o
    1 1 1
    0 1 0
    1 0 0
    0 0 0
    end
```

Skrátene (s použítím implicitných pravidiel):

```
    gate and
    inputs i1 i2
    outputs o
    1 1 1
    end
```

### Blok definície vlastnej hradlovej siete

#### Syntax

```
    network
    inputs i1 i2 ... iN
    outputs o1 o2 ... oM
    gate meno_instancie meno_typu_hradla
    ...
    gate meno_instancie meno_typu_hradla
    definicia_prepojenia_medzi_vnutornymi_hradlami
    end
```

#### Vstupy

Hradlová sieť musí mať aspoň jeden vstup (`N >= 1`).

Rovnaké ako pri definícii bloku hradla v časti vstupy.

#### Výstupy

Rovnaké ako pri definícii bloku hradla v časti výstupy.

#### Hradlá

Riadky začínajúce kľúčovým slovom `gate` obsahujú definíciu inštancií hradiel v hradlovej sieti. Meno inšatncie nejakého hradla môže byť rovnaké ako vlastné meno typu hradla. Každá sieť musí obsahovať aspoň jedno hradlo.

#### Definícia prepojenia

Každý riadok v definícii prepojenia definuje jedno spojenie medzi dvomi miestami v hradlovej sieti. Definícia prepojenia má jednu z následujúcich foriem:
- `ga.ix->gb.oy` definuje prepojenie vstupu `ix` na inštancii `ga` hradla na výstup `oy` na inštancii `gb` hradla
- `ga.ix->iy` definuje prepojenie vstupu `ix` na inštancii `ga` hradla na vstup `iy` hradlovej siete
- `ox->ga.oy` definuje prepojenie výstupu `ox` hradlovej siete na výstup `oy` na inštancii `ga` hradla

#### Pravidlá o prepojeniach vstupov

Jeden vstup hradlovej siete môže byť pripojený na vsutp viacerých hradiel. Každý vstup hradlovej siete musí byť pripojený aspoň na jedno hradlo. Na každý výstup hradlovej siete musí byť pripojený práve jeden výstup nejakého hradla. Ak vstup nejakého hradla zostane nezapojený, tak je na ňom konštante nedefinovaná hodnota.

#### Implicitné vstupy

Každá hradlová sieť má ku svojim explicitne definovaným vstupom ešte dva implicitne definované vstupy pomenované `'0'` a `'1'`. Na týchto vstupov sú vždy konštantné hodnota 0, resp. 1. Pravidlá pre pripojenie na tieto vstupy sú rovnaké ako pre ostatné vstupy hradlovej siete.

### Použitie

Program sa spúšťa s práve jedným parametrom na príkazovom riadku - definuje meno vstupného súboru. Ak je načítanie v poriadku, program čaká na štandardnom vstupe na príkazy. Každý príkaz je na samostatnom riadku. Príkaz je zoznam jedničiek, núl a otáznikov oddelených medzerami. Jeden príkaz definuje hodnoty na vstupe hradlovej siete. Odpoveď na každý príkaz je jeden riadok na štandardnom výstupe. Formát odpovede je počet taktov a za medzerou hodnoty na výstupoch hradlovej siete oddelené medzerami. Príkazom `end` alebo ukončením štandardného vstupu sa program ukončí.

### Chyby

1. `Argument error.`: ak program nedostal práve jeden argument na príkazovom riadku.
2. `File error.`: ak sa nedá z nejakého dôvodu vstupný súbor otvoriť alebo sa z neho nedá čítať.
3. `Syntax error.`: príkaz na vstupe je v nesprávnom formáte (čaká sa na ďalší príkaz).

Chyby vo vstupnom súbore hradlovej siete: (`N` je číslo riadku kde nastala chyba)

4. `Line N: Duplicate.`: Pri opakovaní niektorej kombinácie vstupov v definícii funkcie hradla, definícia už definovaného typu hradla alebo inštancie, mena vstupu alebo výstupu v definícii preojenia hradlovej siete.
5. `Line N: Missing keyword.`: Ak v programe chýba nejaká povinná časť, napríklad `inputs` alebo `outputs`.
6. `Line N: Binding rule.`: Ak je chyba v logike prepojovacieho pravidla, napríklad prepojenie vstupu jedného hradla na vstup iného apod. Vznikne tiež na príkaze `end`, ak neboli dodržané pravidlá pre tvorbu hradlovej siete.
7. `Line N: Syntax error.`: Pri inej chybe (napríklad neplatné meno typu hradla v definícii hradlovej siete, alebo odkaz na neexistujúci vstup alebo výstup v prepojovacom pravidle, atd).

Oznámi sa prvá chyba, na ktorú program narazí.
