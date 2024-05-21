#include <iostream>
#include <conio.h>
#include <vector>
#include <array>
#include <fstream>

using namespace std;

struct Slowo
{
    uint8_t p;  //pozycja slowa w slowniku
    uint8_t k;  //dlugosc slowa
    char s;  //symbol po slowie

    Slowo(uint8_t p, uint8_t k, char s)
    {
        this->p = p;
        this->k = k;
        this->s = s;
    }

    Slowo() = default;
};

ostream& operator<<(ostream& o, const Slowo& s)
{
    o << "(" << ((unsigned int)s.p) << "," << ((unsigned int)s.k) << "," << s.s << ")";
    return o;
}

struct Slowo najdluzsze_slowo(const char* bufor, const char* slownik, int bufor_size, int slownik_size)
{
    Slowo slowo;
    slowo.p = 0;
    slowo.k = 0;
    slowo.s = bufor[0];
    for (int i = 0; i < slownik_size; i++)
    {
        if (slownik[i] == bufor[0])
        {
            int pozycja = i;
            int dlugosc = 1;
            char symbol = bufor[1];

            for (int j = i + 1; j < slownik_size && j - i + 1 < bufor_size; j++)
            {
                if (slownik[j] == bufor[dlugosc])
                {
                    dlugosc++;
                    symbol = bufor[dlugosc];
                }
                else break;
            }
            if (dlugosc > slowo.k)
            {
                slowo.p = pozycja;
                slowo.k = dlugosc;
                slowo.s = symbol;
            }
        }
    }
    return slowo;
}

void koder(const char* dane, int rozmiar, int slownik_size, int bufor_size, vector<Slowo>& wynik)
{
    vector<char> okno;
    okno.resize(slownik_size + rozmiar);
    char* slownik = okno.data();
    char* wejscie = slownik + slownik_size;

    for (int i = 0; i < rozmiar; i++)
    {
        wejscie[i] = dane[i];
    }

    for (int i = 0; i < slownik_size; i++)
    {
        slownik[i] = wejscie[0];
    }
    wynik.push_back({ 0,0,wejscie[0] });
    slownik++;
    wejscie++;
    rozmiar--;
    while (rozmiar > 1)
    {
        Slowo slowo = najdluzsze_slowo(wejscie, slownik, min(bufor_size, rozmiar), slownik_size);
        wynik.push_back(slowo);
        slownik += slowo.k + 1;
        wejscie += slowo.k + 1;
        rozmiar -= slowo.k + 1;
    }
    if (rozmiar == 1)
    {
        wynik.push_back({ 0,0,wejscie[0] });
    }
}

void dekoder(const vector<Slowo>& slowa, int slownik_size, int bufor_size, vector<char>& wynik)
{
    int wyjscie_size = 0;
    for (int i = 0; i < slowa.size(); i++)
    {
        wyjscie_size += slowa[i].k + 1;
    }
    vector<char> okno;
    okno.resize(slownik_size + wyjscie_size);
    char* slownik = okno.data();
    char* wyjscie = slownik + slownik_size;
    for (int i = 0; i < slownik_size; i++)
    {
        slownik[i] = slowa[0].s;
    }
    for (int i = 0; i < slowa.size(); i++)
    {
        const Slowo& s = slowa[i];
        for (int j = 0; j < s.k; j++)
        {
            wyjscie[j] = slownik[s.p + j];
        }
        wyjscie[s.k] = s.s;
        slownik += s.k + 1;
        wyjscie += s.k + 1;
    }
    wynik.resize(wyjscie_size);
    for (int i = 0; i < wyjscie_size; i++)
    {
        wynik[i] = okno[slownik_size + i];
    }
}

void czytaj_plik(const char* sciezka, vector<char>& wynik)
{
    wynik.clear();
    ifstream plik{ sciezka, ios::binary };
    if (plik.is_open())
    {
        char bufor[4096];
        while (1)
        {
            plik.read(bufor, 4096);
            int ile_wczytanych = plik.gcount();
            if (ile_wczytanych == 0)
                break;
            wynik.resize(wynik.size() + ile_wczytanych);
            memcpy(wynik.data() + wynik.size() - ile_wczytanych, bufor, sizeof(char) * ile_wczytanych);
        }
        plik.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku do odczytu!" << endl;
    }
}

void zapisz_skompresowany(const char* sciezka, const vector<Slowo>& slowa)
{
    ofstream plik{ sciezka, ios::binary };
    if (plik.is_open())
    {
        plik.write(reinterpret_cast<const char*> (slowa.data()), sizeof(Slowo) * slowa.size());
        plik.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku do zapisu!" << endl;
    }
}

void zapisz_zdekompresowany(const char* sciezka, const vector<char>& dane)
{
    ofstream plik{ sciezka, ios::binary };
    if (plik.is_open())
    {
        plik.write(dane.data(), sizeof(char) * dane.size());
        plik.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku do zapisu!" << endl;
    }
}

void wczytaj_skompresowany(const char* sciezka, vector<Slowo>& slowa)
{
    ifstream plik{ sciezka, ios::binary };
    if (plik.is_open())
    {
        plik.seekg(0, ifstream::end);
        int size = plik.tellg();
        plik.seekg(0);
        if (size % sizeof(Slowo) == 0)
        {
            int n = size / sizeof(Slowo);
            slowa.resize(n);
            plik.read(reinterpret_cast<char*>(slowa.data()), size);
            plik.close();
        }
        else
        {
            cout << "Nieprawidlowy rozmiar pliku!" << endl;
        }
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku do odczytu!" << endl;
    }
}

void testuj()
{
    //czesc odpowiedzialna za testowanie programu pod katem poprawnosci

    vector<Slowo> wynik;
    koder("aabaaabaab", 10, 5, 3, wynik);
    cout << endl << "Po wykonaniu kompresji..." << endl;
    for (int i = 0; i < wynik.size(); i++)
    {
        cout << wynik[i] << endl;
    }
    vector<char> zdekompresowane;
    dekoder(wynik, 5, 3, zdekompresowane);
    cout << endl << "Po dekompresji..." << endl;
    for (int i = 0; i < zdekompresowane.size(); i++)
    {
        cout << zdekompresowane[i] << endl;
    }
}

int main()
{
    //testuj();

  //g³owna czesc programu

    vector<Slowo> wynik;
    vector<Slowo> wczytane_slowa;
    vector<char> zdekompresowany;
    vector<char> zawartosc;

    czytaj_plik("D:\\LZ77\\Photo.jpg", zawartosc);
    koder(zawartosc.data(), zawartosc.size(), 512, 64, wynik);
    zapisz_skompresowany("D:\\LZ77\\Photo_skompresowane.bin", wynik);
    wczytaj_skompresowany("D:\\LZ77\\Photo_skompresowane.bin", wczytane_slowa);
    dekoder(wczytane_slowa, 512, 64, zdekompresowany);
    zapisz_zdekompresowany("D:\\LZ77\\Photo_zdekompresowane.jpg", zdekompresowany);
}

