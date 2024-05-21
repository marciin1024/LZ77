Zadanie:
Zadanie polega na napisaniu programu, który umożliwia kompresję i dekompresję różnych rodzajów plików przy użyciu metody słownikowej LZ77. W programie ma zostać zawarta funkcja która wyszukuje najdłuższą sekwencję z bufora w słowniku. W funkcji tej mamy możliwość ustawienia wielkości bufora i słownika. Następnym krokiem jest implementacja kodera zawierającego funkcję utworzoną wcześniej. Za pomocą operacji plikowych program pobiera dane z pliku i zapisuje w postaci .bin. Trzecim etapem jest implementacja dekodera, który ma za zadanie przywrócić skompresowany plik do pierwotnej postaci.


Założenia:
- Pliki po kompresji są zapisywane w formacie .bin a po dekompresji w takim samym formacie jak przed dekompresją. 
- Program ma działać na różnego rodzaju danych np. pliki tekstowe, graficzne, dźwiękowe.
- Długości bufora i słownika w koderze i dekoderze są takie same.


Algorytm:
1.	Użytkownik podaje ścieżkę do pliku który ma zostać skompresowany. 
2.	Przy pomocy funkcji czytaj_plik() program otwiera plik lub wyświetla informację o błędzie podczas jego otwierania.
3.	Funkcja koder() kompresuje odczytany plik.
4.	Funkcja zapisz_skompresowany() zapisuje plik w miejscu ścieżki podanej przez użytkownika.
5.	Funkcja wczytaj_skompresowany() wczytuje plik z miejsca ścieżki podanej przez użytkownika w celu umożliwienia dekompresji.
6.	Funkcja dekoder() dekompresuje odczytany plik.
7.	Funkcja zapisz_zdekompresowany() zapisuje plik w miejscu ścieżki podanej przez użytkownika po wcześniejszej dekompresji pliku.


Implementacja:
W programie zawarto również część testową odpowiedzialną za sprawdzenie poprawności zastosowania algorytmu w programie. Umożliwia ona sprawdzenie krok po kroku jakie wartości są zwracane przez funkcję najdluzsze_slowo() i ustalenie czy są to poprawne wartości. 


Testowanie poprawności działania programu:
Do testowania poprawności działania programu wykonano funkcję testuj(), w której po wprowadzeniu krótkiego ciągu znaków oraz rozmiaru bufora i słownika następuje kodowanie. Następnie wyświetlane jest każde znalezione słowo w słowniku. Kolejnym krokiem jest dekodowanie wcześniejszego przykładu . Po zdekodowaniu otrzymujemy taką samą sekwencję znaków. Umożliwia to potwierdzenie prawidłowego działania programu.
