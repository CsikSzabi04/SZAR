#include <iostream>
#include <stdlib.h>
#include <time.h>

int main() {
	srand(time(NULL));
	int t[10];
	int min, max;

	const char* fmtMin = "Adja meg a min erteket: ";
	const char* fmtMax = "Adja meg a max erteket: ";
	const char* fmtIntRead = "%d";
	_asm {
		CIKLUS_DO:
			mov esi, esp;

			//printf("Adja meg a min erteket: ");
			//scanf_s("%d", &min);
			push fmtMin;
			call dword ptr printf;

			lea eax, min;  //&min értékét tárolja az eax-ben
			push eax;
			push fmtIntRead;
			call dword ptr scanf;

			//printf("Adja meg a max erteket: ");
			//scanf_s("%d", &max);
			push fmtMax;
			call dword ptr printf;

			lea eax, max;  //&max értékét tárolja az eax-ben
			push eax;
			push fmtIntRead;
			call dword ptr scanf;

			mov esp, esi;

			//Do-nak While része //while(max <=min || min < 10 || min > 1000 || max < 10 || max > 1000);
			mov eax, max;
			cmp eax, min;
			jle CIKLUS_DO;
			cmp min, 1;
			jl CIKLUS_DO;
			cmp min, 1000;
			jg CIKLUS_DO;
			cmp max, 1;
			jl CIKLUS_DO;
			cmp max, 1000;
			jg CIKLUS_DO;
	}

	//for (int i = 10; i > 0; i--) t[10-i] = rand() % (max - min + 1) + min;
	_asm {
		mov ecx, 10;       // int i = 10;
		mov edi, 0;
		CIKLUS_PUSH:
			rdrand eax;    //random számot generál
			mov ebx, max;  //ebx = max;
			sub ebx, min;  // (max - min)
			inc ebx;       // (max-min+1)
			mov edx, 0;
			idiv ebx;      // edx = %(max-min+1);
			add edx, min;  // edx + min

			mov t[edi], edx;
			add edi, 4;

		loop CIKLUS_PUSH;
	}

	//for (int i = 10; i > 0; i--) printf("%d\t", t[10 - i]);
	const char* fmtIntPrint = "%d\t";
	_asm {
		mov ecx, 10;       // int i = 10;
		mov edi, 0;
		CIKLUS_PRINT:
			push ecx;
			mov esi, esp;

			push t[edi];
			push fmtIntPrint;
			call dword ptr printf;

			add edi, 4;

			mov esp, esi;
			pop ecx;
		loop CIKLUS_PRINT;
	}

	return 0;
}

/*

----ELMÉLET----

KÉRDÉS: Mi jellemző a Neumann-elvű számítógépre?
VÁLASZOK: Tárolt program | Program és adat azonos helyen | BCD aritmetika | soros ALU
JÓ VÁLASZ: Tárolt program / Program és adat azonos helyen
MAGYARÁZAT: Neumann János elvei szerint a gép belső memóriában tárolja az utasításokat, és nem tesz különbséget adat- és programmemória között (egységes tárolás).

KÉRDÉS: Melyik volt az első Neumann-elvű számítógép?
VÁLASZOK: ENIAC | COLOSSUS | IAS-gép | egyik válasz sem helyes
JÓ VÁLASZ: IAS-gép
MAGYARÁZAT: Az IAS-gép volt az első, amely már építésekor maradéktalanul implementálta a Neumann-elveket, szemben például az ENIAC-kal, amit eredetileg huzalozással programoztak.

KÉRDÉS: Egy számítógép memóriarekesze 12 bites. Hány jegyű oktális számmal adható meg a memóriarekesz tartalma?
VÁLASZOK: 6 | 18 | 4 | egyik válasz sem helyes
JÓ VÁLASZ: 4
MAGYARÁZAT: Az oktális számrendszer alapja 8 (2^3), tehát egy oktális jegy 3 bitet fed le. 12 bit / 3 = 4 jegy.

KÉRDÉS: Egy processzor ALU-ja 64 bites. Hány jegyű hexadecimális számmal adható meg az operandusok mérete?
VÁLASZOK: 3 | 4 | 6 | egyik válasz sem helyes
JÓ VÁLASZ: egyik válasz sem helyes
MAGYARÁZAT: Egy hexadecimális jegy 4 bitet képvisel. 64 bithez 64 / 4 = 16 hexadecimális jegyre lenne szükség, ami nem szerepel a válaszok között.

KÉRDÉS: Hány jegyű hexadecimális számmal adható meg egy 32 bites regiszter tartalma?
VÁLASZOK: 32 | 16 | 4 | egyik válasz sem helyes
JÓ VÁLASZ: egyik válasz sem helyes
MAGYARÁZAT: 32 bit ábrázolásához 32 / 4 = 8 hexadecimális jegy kell. Mivel a 8-as nincs a listában, a válasz: egyik sem helyes.

KÉRDÉS: Egy mikroprocesszor címsínje 32 bites, a memóriarekesz 32 bites. Mennyi bájt a memóriakapacitás?
VÁLASZOK: 16 777 216 | 33 554 432 | 65 536 | egyik válasz sem helyes
JÓ VÁLASZ: egyik válasz sem helyes
MAGYARÁZAT: 2^32 címezhető egység (ha bájtonként címezzük) 4 GB-ot jelent. A megadott értékek (pl. 16 MB, 32 MB) sokkal kisebbek.

KÉRDÉS: Mi az átvitelbit értéke a 0xBE és 0xAD számok összeadása után?
VÁLASZOK: 1 | 0
JÓ VÁLASZ: 1
MAGYARÁZAT: 0xBE (190) + 0xAD (173) = 0x16B (363). Mivel az eredmény meghaladja a 8 bites maximumot (255), az átvitelbit (Carry) 1-es lesz.

KÉRDÉS: 0x7A és 0x45 kettes komplemens kódban ábrázolt számok. Mi a túlcsordulás bit értéke a számok összeadása után?
VÁLASZOK: 1 | 0
JÓ VÁLASZ: 1
MAGYARÁZAT: 0x7A (pozitív) + 0x45 (pozitív) = 0xBF. Mivel a 0xBF legfelső bitje 1-es, az eredmény negatívnak látszik. Két azonos előjelű szám összege nem adhat ellentétes előjelet, ezért túlcsordulás történt.

KÉRDÉS: X = 0x1A és Y = 0xA5 előjel nélküli egész számok. Mi a kölcsönbit értéke az X-Y kivonás után?
VÁLASZOK: 1 | 0
JÓ VÁLASZ: 1
MAGYARÁZAT: Előjel nélküli kivonásnál akkor keletkezik kölcsönbit (Borrow), ha a kisebb számból (0x1A) vonunk ki egy nagyobbat (0xA5).

KÉRDÉS: Mi 0x80 kettes komplemens kódú szám előjelbitje?
VÁLASZOK: 1 | 0
JÓ VÁLASZ: 1
MAGYARÁZAT: A 0x80 binárisan 1000 0000. Az MSB (legfelső bit) az előjelbit, ami itt 1-es (negatív szám).

KÉRDÉS: A 0x80CC szó esetében előjel-kiterjesztést hajtunk végre duplaszó méretűre. Mi az eredmény hexadecimálisan?
VÁLASZOK: 0xFFFF80CC | 0x000080CC | 0x800080CC | egyik válasz sem helyes
JÓ VÁLASZ: 0xFFFF80CC
MAGYARÁZAT: Előjel-kiterjesztésnél az eredeti szám legfelső bitjét (ami itt 1-es, mert a 8-as hexajegy 1000 binárisan) másoljuk be az új, felsőbb helyiértékekre.

KÉRDÉS: 8 bites, előjel nélküli egész számokkal számolunk. Mennyi a 255 és 1 decimális számok összege decimálisan?
VÁLASZOK: 256 | 1 | 0 | egyik válasz sem helyes
JÓ VÁLASZ: 0
MAGYARÁZAT: 8 biten a 255 a maximum. Ha 1-et hozzáadunk, az eredmény "átfordul" (túlcsordul), és a regiszterben 0 marad.

KÉRDÉS: Melyik pszeudo-tetrád az alábbi 4 bites számok közül?
VÁLASZOK: 1011 | 1000 | 0101 | egyik válasz sem helyes
JÓ VÁLASZ: 1011
MAGYARÁZAT: A BCD kódolásnál a 9 feletti (1010-től 1111-ig terjedő) kombinációk nem érvényes számjegyek, ezeket hívjuk pszeudo-tetrádoknak. A 1011 értéke 11.

KÉRDÉS: A 0xBE8000 az IEEE-754 szabvány szerinti 32 bites szám. Mi a szám (-1)-szeresének hexadecimális alakja?
VÁLASZOK: 0xFE8000 | 0xBE8001 | 0x3E8000 | egyik válasz sem helyes
JÓ VÁLASZ: 0x3E8000
MAGYARÁZAT: Az IEEE-754 formátumnál az első bit az előjel. Ha 0xB (1011) a kezdő jegy, és az első bitet 1-ről 0-ra váltjuk (negatívból pozitívba), akkor 0011 lesz az eleje, ami hexadecimálisan 3.

KÉRDÉS: Mennyi az A = 00101100 és B = 10101111 bináris kódszavak Hamming-távolsága?
VÁLASZOK: 3 | 5 | 10000011 | egyik válasz sem helyes
JÓ VÁLASZ: 3
MAGYARÁZAT: A Hamming-távolság az eltérő bitek száma. Itt a 1., 7. és 8. helyen térnek el a bitek, összesen 3 helyen.

KÉRDÉS: Egy processzor órajelének frekvenciáját felére csökkentjük. Hogyan változik a disszipált teljesítmény?
VÁLASZOK: negyedére csökken | kétszeresére nő | felére csökken | egyik válasz sem helyes
JÓ VÁLASZ: felére csökken
MAGYARÁZAT: A processzor disszipált teljesítménye lineárisan arányos az órajellel (P ~ f).

KÉRDÉS: Egy A/D átalakító 12 bites, a bemeneti feszültség-tartomány 5 V. Mennyi a kvantálási szintek száma?
VÁLASZOK: 4096 | 8192 | 5/8192 V | egyik válasz sem helyes
JÓ VÁLASZ: 4096
MAGYARÁZAT: 12 biten 2^12 különböző értéket lehet megkülönböztetni, ami 4096 szintet jelent.

KÉRDÉS: A szinuszjel melyik jellemzőjét változtatja az FSK modem?
VÁLASZOK: amplitúdó | fázis | frekvencia | egyik válasz sem helyes
JÓ VÁLASZ: frekvencia
MAGYARÁZAT: FSK = Frequency Shift Keying (Frekvenciabillentyűzés). Az adatokat a frekvencia váltásával kódolják.

KÉRDÉS: Mennyi az adatátviteli sebesség 9600 baud és 4 elemi jel esetén?
VÁLASZOK: 9600 bit/s | 4800 bit/s | 19200 bit/s | egyik válasz sem helyes
JÓ VÁLASZ: 19200 bit/s
MAGYARÁZAT: 4 állapot esetén log2(4) = 2 bit vihető át elemenként. 9600 baud * 2 bit = 19200 bit/s.

KÉRDÉS: A 0x9D bájtot páratlan paritásbittel védjük. Mi a védőbit értéke?
VÁLASZOK: 1 | 0
JÓ VÁLASZ: 0
MAGYARÁZAT: 0x9D = 1001 1101. Ebben 5 darab 1-es van. Mivel 5 már páratlan szám, a paritásbit 0 lesz, hogy az összesített 1-esek száma páratlan maradjon.

KÉRDÉS: A soros aszinkron adatátvitelre jellemző, hogy:
VÁLASZOK: van külön órajel vezeték | nincs külön órajel vezeték
JÓ VÁLASZ: nincs külön órajel vezeték
MAGYARÁZAT: Az aszinkron átvitel lényege, hogy nincs közös órajel; a szinkronizációt a Start és Stop bitek végzik.

KÉRDÉS: A 0xB (1011) Hamming-kódolása során a paritások és a súly?
JÓ VÁLASZOK: P2=1, P1=0, P0=1, Védett szó=1010111, Súly=3 (egyik sem jó a súlynál)
MAGYARÁZAT: A Hamming-súly az 1-esek száma az adatban (1011 -> 3 db). A paritásbiteket a pozíciók XOR-olásával számítjuk.

KÉRDÉS: "Az utasítás-végrehajtás ebben az esetben pipeline-szervezésű" (ha nincs átlapolódás).
VÁLASZOK: IGAZ | HAMIS
JÓ VÁLASZ: HAMIS
MAGYARÁZAT: A pipeline lényege az időbeli átlapolás (több utasítás fut egyszerre különböző fázisokban). Ha nincs átlapolás, nincs pipeline.

KÉRDÉS: Mennyi a CPI érték (4 fázis, átlapolás nélkül)?
VÁLASZOK: 1 | 2 | 4 | egyik válasz sem helyes
JÓ VÁLASZ: 4
MAGYARÁZAT: CPI = Cycles Per Instruction. Ha egy utasítás 4 ciklusig tart és sorban követik egymást, akkor 4 ciklus kell egy utasításhoz.

KÉRDÉS: Lehetséges-e maximális IPC = 1 érték, ha minden utasítás 4 ciklusig tart?
VÁLASZOK: lehetséges, pipeline szervezéssel | nem lehetséges, ellentmondás van
JÓ VÁLASZ: lehetséges, pipeline szervezéssel
MAGYARÁZAT: Ideális pipeline esetén minden ciklusban befejeződik egy utasítás (miközben a többi még fut), így az IPC (utasítás per ciklus) elérheti az 1-et.

KÉRDÉS: 5 PFlops mennyi GFlops?
VÁLASZOK: 5000 | 5 000 000 | 500 | egyik válasz sem helyes
JÓ VÁLASZ: 5 000 000
MAGYARÁZAT: 1 Peta = 1000 Tera = 1.000.000 Giga.

KÉRDÉS: 7080 mAh és 7,6 V akkumulátor energiája?
VÁLASZOK: 54 W | 54 kWh | 54 Wh | egyik válasz sem helyes
JÓ VÁLASZ: 54 Wh
MAGYARÁZAT: Energia (Wh) = Kapacitás (Ah) * Feszültség (V). 7,08 Ah * 7,6 V = 53,8 Wh, kerekítve 54 Wh.

KÉRDÉS: Mi tárol egy bitet a DRAM-ban?
VÁLASZOK: Flip-flop | MOSFET Tranzisztor | Kondenzátor | egyik válasz sem helyes
JÓ VÁLASZ: Kondenzátor
MAGYARÁZAT: A dinamikus RAM (DRAM) apró kondenzátorok elektromos töltésének jelenlétével (1) vagy hiányával (0) tárolja az információt.

*/
