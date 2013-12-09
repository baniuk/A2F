/*! @page Intro Introduction

Wszystkie parametry strumieni trzymane s¹ w klasie C_Parameter_Container lub wyprowadzonej z niej klasie C_PortParameter_Container. Ta druga ró¿ni siê
jedynie tym ¿e jest w stanie przechowaæ obiekty klasy C_Parameter_Container przez co mo¿liwa jest obs³uga wielu wejœæ na przyk³ad. W klasie C_Parameter_Container
przechowywane s¹ poszczególne zwi¹zki oraz skojarzone z nimi parametry fizyczne (zdefiniowane w klasie C_Parameters_Set ).
Dostêp do nich jest za pomoc¹ nazwy zwi¹zku lub jego numeru nadawanego poczas rejestracji.
Parametry zwi¹zków s¹ trzymane w C_myRunProcess::Parameters i wype³niane najpierw w funkcji C_myRunProcess::PutParams gdzie tworzone i rejestrowane s¹ 
komponenty i dodawane s¹ parametry odczytane z ASPENA (po przeliczeniu jednostek) oraz niektóre parametry podawane w skrypcie. Nastêpnie w C_myRunProcess::CreateEnv s¹ wykorzystywane razem z parametrami ze skryptu (skrypt obs³ugiwany 
przez klasê C_Params oraz C_myRunProcess::copyparams) do tworzenia pliku dla Fluenta.
W klasie C_myRunProcess::ImportData zaimportowane w³aœciowoœci fizycze z fluenta s¹ trzymane w dwóch obiektach klasy C_PortParameter_Container - SUM i SR
Finalnie mamy w C_myRunProcess::Parameters w³asciwoœci fizyczne z ASPENA a w C_myRunProcess::SUM i C_myRunProcess:SR w³aœciwoœci fizyczne z Fluenta.
Odpowiedniego kopiowania do ASPENA dokonuje siê poprzez funkcjê C_myRunProcess::GetParams która zwraca wartoœci albo te policzone albo te oryginalne,
jeœli nie by³y liczone. PRzelicza tak¿e odpowiednio jednostki. Jeœli oryginalne to domyœlnie brane jest wejscie 0 jako to wa¿niejsze. Wartosæ przep³ywu moilowego jest przeliczana przy uwzglêdnieniu udzia³u molowego materia³ów na wejœciu - w aspenie podaje siêtylko przep³yw mieszaniny, 
w klasie C_myRunProcess::Parameters trzymane s¹ ju¿ poszczególne sk³adniki
\n\n

Dane z pliku konfiguracyjnego przechowywane s¹ jako ca³e tekstowe linie a dostêp do poszczególnych parametrów w lini jest realizowany za pomoc¹ oznaczenia tych parametrów odpowiednimi s³owami kluczowymi. Zarz¹dza tym klasa C_Params (poprez Data_To_Read), gdzie zdefinowane s¹ nazwy pól dla poszczególnych rozkazów. Wszystkie rozkazy które maj¹ wiêcej linijek (z instrukcj¹ END) trzymaja dane w klasie Data_To_Read która obs³uguje zwracanie iloœci linii oraz zwracanie posczególnych czêsci rozkazów. Informacje na temat poszczególncy czêsci (czyli spacji) s¹ wype³niane w klasie C_Params::Creadfile, podczas interpretacji kodu.
\n
Przyk³ady odwo³añ do posczególnych pól i klas: \n
\code
tmpsurf = copyparams->bASSIGNS.GetSubString(line,ASSIGN_SURF_NAME);	// nazwa powierzchni skojarzona z materia³em
tmpin = copyparams->bASSIGNS.GetSubString(line,ASSIGN_INPUTID);		// index wejscia w ASPENIE do którego pod³¹czony jest dany materia³ (numeracja od 1!!)

ret = Parameters.GetParameterP(tmpmat,PARAM_MOLEFLOW,paramVal1,atoi(tmpin)-1);
ret = SR.GetParameter(pszB,PARAM_TEMPERATURE,val);
\endcode

W przypadku zmiany portów za pomoc¹ instrukcji ACTIVEPORTS zmiana jest dokonywana w g³ównej klasie UnitOperation.cpp zaraz po odczycie danych. Polega na skasowaniu ostatnich portów tak aby zgadza³a siê iloœæ. Tworzenie portów jest zrealizowane pó³ na pó³ - max ilosc ustala sie w programie MAX_INPUTS, a póŸniej w skrypcie mo¿na zejsc w dó³. NUM_OF_INPUTS wystêpuje tylko w konstruktorze i destruktorze CUnitOperation.cpp i tak¿e s³u¿y do okreslenia rozmiarów tablicy ports[] oraz w funkcji removePorts

W trybie debug brany jest plik "f:\\FluentSol\\parsertest\\Matlab\\params.txt"; oraz katalog z danymi zdefiniowany w tym pliku. Dodatkowo w funkcji UnitOperation::Calculate() s¹ zapisywane wszystkie parametry strumieni do pliku na c:\ 

/// \todo Dodaæ numery stron w helpie
/// \todo Usun¹æ referencje do moleperkg w rozdziale B³êdy numeryczne
/// \todo dodano funkcjê activeports do zmiany ilosci portów w programie - zmiana tylko w dó³ i bez zabezpieczeñ jeœli chodzi o wyzerowanie lub porty ujemne!
/// \todo zmienic w helpie wymagania co do \\ w nazwach
/// \warning nazwa fluent.exe i nazwa procesu sa wra¿liwe na wielkosæ liter. narazie w C_Params.cpp na si³e sa zmniejszane litery ale to nie bêdzie dia³aæ jeœli bêdzie treba gdzieœ du¿¹ literê. To samo w EXPORTS
/// \todo dodac info o u¿ywaniu tylko ma³ych liter lub tak jak we fluencie
/// \todo dodac info o kolejnosci przepisywania niezainicjlizowanych parametrów

*/

