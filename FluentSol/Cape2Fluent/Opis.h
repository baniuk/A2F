/*! @page Intro Introduction

Wszystkie parametry strumieni trzymane s� w klasie C_Parameter_Container lub wyprowadzonej z niej klasie C_PortParameter_Container. Ta druga r�ni si�
jedynie tym �e jest w stanie przechowa� obiekty klasy C_Parameter_Container przez co mo�liwa jest obs�uga wielu wej�� na przyk�ad. W klasie C_Parameter_Container
przechowywane s� poszczeg�lne zwi�zki oraz skojarzone z nimi parametry fizyczne (zdefiniowane w klasie C_Parameters_Set ).
Dost�p do nich jest za pomoc� nazwy zwi�zku lub jego numeru nadawanego poczas rejestracji.
Parametry zwi�zk�w s� trzymane w C_myRunProcess::Parameters i wype�niane najpierw w funkcji C_myRunProcess::PutParams gdzie tworzone i rejestrowane s� 
komponenty i dodawane s� parametry odczytane z ASPENA (po przeliczeniu jednostek) oraz niekt�re parametry podawane w skrypcie. Nast�pnie w C_myRunProcess::CreateEnv s� wykorzystywane razem z parametrami ze skryptu (skrypt obs�ugiwany 
przez klas� C_Params oraz C_myRunProcess::copyparams) do tworzenia pliku dla Fluenta.
W klasie C_myRunProcess::ImportData zaimportowane w�a�ciowo�ci fizycze z fluenta s� trzymane w dw�ch obiektach klasy C_PortParameter_Container - SUM i SR
Finalnie mamy w C_myRunProcess::Parameters w�asciwo�ci fizyczne z ASPENA a w C_myRunProcess::SUM i C_myRunProcess:SR w�a�ciwo�ci fizyczne z Fluenta.
Odpowiedniego kopiowania do ASPENA dokonuje si� poprzez funkcj� C_myRunProcess::GetParams kt�ra zwraca warto�ci albo te policzone albo te oryginalne,
je�li nie by�y liczone. PRzelicza tak�e odpowiednio jednostki. Je�li oryginalne to domy�lnie brane jest wejscie 0 jako to wa�niejsze. Wartos� przep�ywu moilowego jest przeliczana przy uwzgl�dnieniu udzia�u molowego materia��w na wej�ciu - w aspenie podaje si�tylko przep�yw mieszaniny, 
w klasie C_myRunProcess::Parameters trzymane s� ju� poszczeg�lne sk�adniki
\n\n

Dane z pliku konfiguracyjnego przechowywane s� jako ca�e tekstowe linie a dost�p do poszczeg�lnych parametr�w w lini jest realizowany za pomoc� oznaczenia tych parametr�w odpowiednimi s�owami kluczowymi. Zarz�dza tym klasa C_Params (poprez Data_To_Read), gdzie zdefinowane s� nazwy p�l dla poszczeg�lnych rozkaz�w. Wszystkie rozkazy kt�re maj� wi�cej linijek (z instrukcj� END) trzymaja dane w klasie Data_To_Read kt�ra obs�uguje zwracanie ilo�ci linii oraz zwracanie posczeg�lnych cz�sci rozkaz�w. Informacje na temat poszczeg�lncy cz�sci (czyli spacji) s� wype�niane w klasie C_Params::Creadfile, podczas interpretacji kodu.
\n
Przyk�ady odwo�a� do posczeg�lnych p�l i klas: \n
\code
tmpsurf = copyparams->bASSIGNS.GetSubString(line,ASSIGN_SURF_NAME);	// nazwa powierzchni skojarzona z materia�em
tmpin = copyparams->bASSIGNS.GetSubString(line,ASSIGN_INPUTID);		// index wejscia w ASPENIE do kt�rego pod��czony jest dany materia� (numeracja od 1!!)

ret = Parameters.GetParameterP(tmpmat,PARAM_MOLEFLOW,paramVal1,atoi(tmpin)-1);
ret = SR.GetParameter(pszB,PARAM_TEMPERATURE,val);
\endcode

W przypadku zmiany port�w za pomoc� instrukcji ACTIVEPORTS zmiana jest dokonywana w g��wnej klasie UnitOperation.cpp zaraz po odczycie danych. Polega na skasowaniu ostatnich port�w tak aby zgadza�a si� ilo��. Tworzenie port�w jest zrealizowane p� na p� - max ilosc ustala sie w programie MAX_INPUTS, a p�niej w skrypcie mo�na zejsc w d�. NUM_OF_INPUTS wyst�puje tylko w konstruktorze i destruktorze CUnitOperation.cpp i tak�e s�u�y do okreslenia rozmiar�w tablicy ports[] oraz w funkcji removePorts

W trybie debug brany jest plik "f:\\FluentSol\\parsertest\\Matlab\\params.txt"; oraz katalog z danymi zdefiniowany w tym pliku. Dodatkowo w funkcji UnitOperation::Calculate() s� zapisywane wszystkie parametry strumieni do pliku na c:\ 

/// \todo Doda� numery stron w helpie
/// \todo Usun�� referencje do moleperkg w rozdziale B��dy numeryczne
/// \todo dodano funkcj� activeports do zmiany ilosci port�w w programie - zmiana tylko w d� i bez zabezpiecze� je�li chodzi o wyzerowanie lub porty ujemne!
/// \todo zmienic w helpie wymagania co do \\ w nazwach
/// \warning nazwa fluent.exe i nazwa procesu sa wra�liwe na wielkos� liter. narazie w C_Params.cpp na si�e sa zmniejszane litery ale to nie b�dzie dia�a� je�li b�dzie treba gdzie� du�� liter�. To samo w EXPORTS
/// \todo dodac info o u�ywaniu tylko ma�ych liter lub tak jak we fluencie
/// \todo dodac info o kolejnosci przepisywania niezainicjlizowanych parametr�w

*/

