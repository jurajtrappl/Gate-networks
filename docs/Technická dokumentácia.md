# Technická dokumentácia

Text popisuje jednotlivé časti projektu, dodáva kontext implementácii a popisuje spustenie. Aplikácia pozostáva z 5 samostatných projektov:

1. [Core](#Core)
2. [Parser](#Parser)
3. [Util](#Util)
4. [Application](#Application)
5. [ApplicationTests](#ApplicationTests)

Autorská poznámka:

> Uvedené časti kódu obsahujú len časti spomenuté v popise, hlavne kvôli stručnosti. Komentáre a niektoré pre tento text nepotrebné metódy alebo fieldy sú vynechané.

## Spustenie

### Ako to funguje?
Program sa spúšťa s práve jedným parametrom na príkazovom riadku - definuje meno vstupného súboru. Ak je načítanie v poriadku, program čaká na štandardnom vstupe na príkazy. Každý príkaz je na samostatnom riadku. Príkaz je zoznam jedničiek, núl a otáznikov oddelených medzerami a definuje hodnoty na vstupe hradlovej siete. Odpoveď na každý príkaz je jeden riadok na štandardnom výstupe. Formát odpovede je počet taktov a hodnoty na výstupoch hradlovej siete, všetko oddelené medzerami. Príkazom `end` alebo ukončením štandardného vstupu sa program ukončí.

### Pripravené skripty
V zložke `samples` sa nachádzajú pripravené príklady/ukážky programu. K dispozícii sú štyri ukážky:
- dve pre jednoduché hradlá AND a OR
- jedna pre sieť s obomi hradlami
- jedna pre sieť kde je cyklus a ukončenie programu v tomto prípade skončí po vykonaní maximálneho možného počtu taktov, 10^6 (viz. zadanie).

Ukážky je možné spúštať osobitne (v každej zložke je samostatný skript) alebo spoločne pomocou `run_all` skriptu. Okrem skriptu obsahujú definíciu siete a vstupné príkazy.

## Core

Statická knižnica obsahujúca biznis model aplikácie, ktorý zahŕňa základné entity a interface-y. Patri medzi ne *komponenty* aplikácie (`gate_networks::core::components`), spôsob *vyhodnotenia* hradla a hradlovej siete (`gate_networks::core::evaluation`) a reprezentácia *logiky výpočtu* (`gate_networks::core::logic`).

### Logika výpočtu

Aplikácia využíva troj-stavovú logiku (`gate_networks::core::logic::Tri_state`). Hodnoty sú logická 0, logická 1 a stav undefined. Pre reprezentáciu hodnotu je zvolený typ z oblasti funkcionálneho programovania `std::optional<bool>`, nakoľko sa chceme vyhnúť priradzovaniu `NULL` do `bool`.

Okrem samotnej reprezentácie hodnoty na vstupoch alebo výstupoch hradla či hradlovej siete potrebujeme zaistiť výpis na výstup. Logická 1 má výstup '1', logická 0 má výstup '0' a undefined má výstup '?'. Slúži k tomu preťažený operátor `<<`.

### Komponenty

#### Vstupy a výstupy

Každý vstup a výstup má svoj názov a hodnotu k nemu priradenú. Každé hradlo má nejakú kolekciu vstupov a výstupov, ktoré sú prepojené s inými vstupmi alebo výstupmi hradiel alebo vstupmi a výstupmi siete. Takáto kolekcia je reprezentovaná typom `gate_networks::core::components::IOInstances`.

Kolekcia obsahuje field typu:

```cpp
std::map<std::string, gate_networks::core::logic::Tri_state> instances;
```

kde kľúč je názov inštancie a hodnota je troj-stavová hodnota inštancie.

#### Prepojenie

`gate_networks::core::components::IOInstances` dedí od abstraktnej triedy `AConnectible`, ktorá uchováva prepojenia a umožňuje odosielanie hodnôt medzi dvomi koncami prepojenia (`send()`). Pre výpočet siete nás zaujíma iba jeden smer, a teda aj samotné posielanie funguje jednosmerne od začiatku po jej koniec (ak prepájame výstup hradla so vstupom iného hradla, tak posielanie bude v smere od výstupu na vstup).

Najprv definujeme prepojenie. Prepojenie si pamätá názov inštancie (vstup/výstup) odkiaľ začína a bude sa posielať hodnota, ďalej `AConnectible` objekt, kde nájdeme koniec prepojenia a názov inštancie (vstup/výstup) práve tohto prepojenia.

```cpp
typedef std::shared_ptr<AConnectible> Connectible_shared_ptr;

class Connection
{
  	std::string instance_from_;
	std::string instance_to_;
	Connectible_shared_ptr to_;  
};
```

Nakoniec samotná `AConnectible` abstraktná trieda:

```cpp
class AConnectible 
{
public:
    virtual void change_state(const std::string& instance_name, logic::Tri_state new_state) = 0;

	virtual void send() = 0;
private:
	std::vector<Connection> connections_;
};
```



#### Hradlo

Každé hradlo má názov, vstupy, výstupy a zoznam funkcií, ktoré definujú hodnoty na výstupe na základe hodnôt na vstupe.
Vstupy a výstupy budeme reprezentovať pomocou `gate_networks::core::components::IOInstances`.

Od funkcií ideálne chceme rýchle a pohodlné určenie výpočtu. Hodnoty na vstupe odpovedajú definícii funkcie a jej výsledok sú hodnoty na vstupy. Teda funkcie budú obsahovať mapu hodnôt na hodnoty:



```cpp
typedef std::vector<gate_networks::core::logic::Tri_state> Tri_state_values;

std::unordered_map<Tri_state_values, Tri_state_values> functions_;
```



Nakoľko kľúčom je v implementácii `Tri_state_values`, pre ktorý nie je implicitný hasher, musíme si naprogramovať vlastný. 
Každý kľúč bude skutočne jedinečný, pretože opakujúce sa definície funkcií nie sú povolené a hodnoty na vstupoch sa nikdy neopakujú.

```cpp
template<>
struct hash<Tri_state_values>
{
	size_t operator()(const Tri_state_values& instances) const
	{
		size_t h = 0;
		for (auto&& s : instances)
		{
			h = h << 1;
			if (s.value)
			{
				h += 1;
			}
		}
		return h;
	}
};
```

Trieda `gate_networks::core::components::SimpleGate` reprezentuje hradlo kompozíciou vyššie spomínaných súčastí.

Ďalej obsahuje funkciu `std::unique_ptr<gate_networks::core::components::SimpleGate> clone()`, ktorá dokáže vytvoriť shallow copy z hradla slúžiaca ako inštancia prototypu definovaného v bloku definície hradlovej siete.

#### Hradlová sieť

Každá hradlová sieť má vstupy, výstupy a vnútorné hradlá. 

Špecialitov vstupov sú dva osobitné implicitné vstupy predstavujúce logickú 0 a logickú 1. Tieto oddeľujeme do vlastného fieldu. Oba typy vstupov a výstupy reprezentujeme, podobne ako pri hradle, `gate_networks::core::components::IOInstances`.

Vnútorné hradlá ešte rozdeľujeme na vnútorné nekonštantné a vnútorné konštatné. Rozdiel medzi nimi je ten, že pri výpočte siete sa pri inicializácii v 0. takte rozošlú hodnoty okrem oboch vstupov siete aj z vnútorných konštantných hradiel.

Výpočet hradiel je kvôli komplexnosti oddelený od definície entity použitím návrhového vzoru Visitor.

## Parser

Statická knižnica obsahujúca logiku pre spracovanie komponent aplikácie zo vstupného súboru.

Vstupný súbor obsahuje dva typy blokov definícií, hradlá (`gate_networks::parser::gate`) a hradlová sieť (`gate_networks::parser::network`). Pri spracovaní vstupu sa teda dá rozumne prepínať medzi dvomi stratégiami spracovania (podľa bloku definície). Trieda `gate_networks::parser::ReaderContext` sa stará práve o toto prepínanie.

- ak sa narazí na blok definície hradla, zavolá sa objekt, ktorý obsahuje logiku so spracovaním hradla (`gate_networks::parser::SimpleGateParser`). 
- ak sa narazí na blok definície hradlovej siete, čítací kontext zmení stratégiu na na objekt, ktorý obsahuje logiku so spracovaním hradlovej siete (`gate_networks::parser::GateNetworkParser`). Okrem toho kontext kontroluje správnosť na "top-level" úrovni, teda napríklad či je dostatočný počet definovaných prototypov hradiel, ale sietí.

Samotné stratégie pre spracovanie jednotlivých typov sú veľmi podobné až na ich interné implementácie. Každá stratégia má súpravu vlastných typov, nazývané definície, ktoré sa starajú o kontrolu správnosti zápisu jednotlivých častí.

Napríklad, nech načítame vstupy pre hradlo:

```
...
inputs i0 i1 i2
...
```

V kóde máme definovanú logiku pre to ako by mali vyzerať vstupy (`ctor()`) a čo sa s nimi má spraviť pre ďalší postup (`assign()`):

```cpp
// gate_definitions.h

...
class SimpleGateInputsDefinition {
public:
	SimpleGateInputsDefinition(const std::vector<std::string>& tokens, int current_line_number);

	void assign(core::components::SimpleGate* gate);
private:
	std::vector<std::string> inputs_;
};
...
    
// gate_definitions.cpp

...
SimpleGateInputsDefinition::SimpleGateInputsDefinition(
    const vector<string>& tokens,
    int current_line_number)
{
	if (tokens.size() != util::ContainerExtensions<vector<string>>::count_distinct(tokens))
	{
		throw DuplicateException(current_line_number);
	}

	inputs_ = tokens;
}

void SimpleGateInputsDefinition::assign(core::components::SimpleGate* gate)
{
	for (auto&& i : inputs_)
	{
		gate->inputs().push_back(i);
	}
}
...
```



Blok definície hradlovej siete obsahuje prepojenia. Spracovanie prepojení je náročnejšie než napríklad vyššie spomínané vstupy. Definícia prepojenia má tri možnosti zápisu podľa toho čo prepája, strany prepojenia sú rozdelené "->". `gate_networks::parser::ConnectionParser` obsahuje logiku spracovania prepojenia. Každý typ prepojenia má vlastný objekt, ktorý vie ako sa má prepojiť. Výber tohto objektu je zaistený mapou s kľúčom, kde sa uvádza počet častí na pravej a ľavej strane, ktoré jednoznačne určrujú vybraný typ. 

Za zmienku stojí spomenúť aj factory prototypov hradiel, ktorá sa volá a klonuje existujúce typy počas spracovania bloku definície hradlovej siete.

## Util

Statická knižnica obsahujúca metódy, ktoré "rozširujú" existujúce typy. Medzi tieto typy patria `std::string` a kontajnery.

Pre typ string je implementovaných hneď niekoľko metód, ktoré sprehľadňujú kontrolu v kóde, napríklad korektnosti, začiatkov definícií a podobne.

Pre kontajnery sú implementované špecializácie pre `std::vector<std::string>`, ktoré pomáhajú s rozdeľovaním `std::string` podľa vybraného delimiteru alebo rátajú počet unikátnych elementov.

## Application

Entry point samotnej aplikácie. Dáva dokopy všetky knižnicové projekty a definuje finálne typy pre vyhodnotenie siete. 

`gate_networks::application::InputParser` vezme názov vstupného súboru a načíta hradlovú sieť. Následne sa zo vstupu  konzoly načítavajú príkazy pre vstupy hradlovej siete do `gate_networks::application::Command`, ktorý konvertuje zadané hodnoty do vhodných hodnôt pre vstup hradlovej siete.  `gate_networks::application::GateNetworkEvaluator` vyhodnocuje sieť. Nakoľko sa dajú príkazy písať postupne a výpočet sa po vykonaní jedného príkazu neresetuje, tak je pre rozšírenie API napríklad pre testovanie pridaná aj metóda `reset()`.

## ApplicationTests

Microsoft Unit Test Framework projekt, ktorý slúži ako kontrola správnosti načítania vstupu a výpočtu siete.

### Vstup

Existuje niekoľko exceptions, ktoré môžu nastať (viz. Zadanie). Trieda `InputTests` obsahuje testy, ktoré spracúvajú nesprávne definované vstupné súbory a testujú jednotlivé exceptions.

### Verifikácia

Výpočet hradla je definovaný tabuľkou jej funkcií. Idea verifikácie je ukázať, že pre každú permutáciu vstupu to dáva korektný výsledok, teda vracia to správnu definíciu z tabuľky.

Zo začiatku si vytvoríme jednoduché hradlá napríklad AND a OR, ktoré zapojíme do siete samotné. Ukážeme, že vydávajú korektné hodnoty pre všetky vstupy. Potom ich zapojíme do jednej siete a ukážeme, že tiež vydávajú správne výsledky. 

Trieda `SimpleGateTests` má napísané testy pre hradlá AND, OR. Trieda `ComplexGateTests` má napísaný test pre zloženú hradlovú sieť z daných hradiel.
