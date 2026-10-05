#include "dane/RepozytoriumBibliotekiWPliku.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

namespace {
    vector<string> split(const string& s, char delim) {
        vector<string> tokens;
        stringstream ss(s);
        string token;
        while (getline(ss, token, delim)) {
            tokens.push_back(token);
        }
        return tokens;
    }
}

RepozytoriumBibliotekiWPliku::RepozytoriumBibliotekiWPliku(const std::string& sciezka)
    : sciezka(sciezka)
{
    wczytaj();
}

void RepozytoriumBibliotekiWPliku::wczytaj() {
    ifstream plik(sciezka);
    if (!plik.is_open()) {
        return;
    }

    string linia;
    while (getline(plik, linia)) {
        if (linia.empty()) continue;

        auto pola = split(linia, '|');
        if (pola.empty()) continue;

        try {
            const string& typ = pola[0];
            if (typ == "KSIAZKA" && pola.size() >= 3) {
                biblioteka.dodajKsiazke(Ksiazka(pola[1], pola[2]));
            }
            else if (typ == "AUTOR" && pola.size() >= 3) {
                biblioteka.dodajAutoraDoKsiazki(pola[1], Autor(pola[2]));
            }
            else if (typ == "EGZEMPLARZ" && pola.size() >= 4) {
                Egzemplarz egz(pola[2]);
                int statusInt = stoi(pola[3]);
                if (statusInt == 1) egz.oznaczWypozyczony();
                else if (statusInt == 2) egz.oznaczZaginiony();
                biblioteka.dodajEgzemplarzDoKsiazki(pola[1], egz);
            }
            else if (typ == "CZYTELNIK" && pola.size() >= 3) {
                biblioteka.dodajCzytelnika(Czytelnik(pola[1], pola[2]));
            }
            else if (typ == "PRACOWNIK" && pola.size() >= 6) {
                int stopienInt = stoi(pola[5]);
                auto stopien = static_cast<StopienPracownika>(stopienInt);
                double wyplata = stod(pola[4]);
                biblioteka.dodajPracownika(Pracownik(pola[1], pola[2], pola[3], wyplata, stopien));
            }
            else if (typ == "WYPOZYCZENIE" && pola.size() >= 5) {
                biblioteka.dodajWypozyczenie(Wypozyczenie(pola[1], pola[2], pola[3], pola[4]));
            }
        } catch (const invalid_argument& e) {
        }
    }
}

Biblioteka& RepozytoriumBibliotekiWPliku::pobierzBiblioteke() {
    return biblioteka;
}

void RepozytoriumBibliotekiWPliku::zapisz() {
    ofstream plik(sciezka);
    if (!plik.is_open()) {
        throw runtime_error("Nie mozna zapisac do pliku: " + sciezka);
    }

    // Zapis książek, autorów i egzemplarzy
    const auto& ksiazki = biblioteka.pobierzKsiazki();
    for (const auto& k : ksiazki) {
        plik << "KSIAZKA|" << k.pobierzIsbn() << "|" << k.pobierzTytul() << "\n";

        for (const auto& a : k.pobierzAutorow()) {
            plik << "AUTOR|" << k.pobierzIsbn() << "|" << a.pobierzImieINazwisko() << "\n";
        }

        for (const auto& e : k.pobierzEgzemplarze()) {
            int status = 0;
            switch (e.pobierzStatus()) {
                case StatusEgzemplarza::Dostepny:    status = 0; break;
                case StatusEgzemplarza::Wypozyczony: status = 1; break;
                case StatusEgzemplarza::Zaginiony:   status = 2; break;
            }
            plik << "EGZEMPLARZ|" << k.pobierzIsbn() << "|" << e.pobierzKod() << "|" << status << "\n";
        }
    }

    // Czytelnicy
    for (const auto& c : biblioteka.pobierzCzytelnikow()) {
        plik << "CZYTELNIK|" << c.pobierzId() << "|" << c.pobierzImieINazwisko() << "\n";
    }

    // Pracownicy
    for (const auto& p : biblioteka.pobierzPracownikow()) {
        plik << "PRACOWNIK|" << p.pobierzId() << "|" << p.pobierzImieINazwisko()
             << "|" << p.pobierzStanowisko() << "|" << p.pobierzWyplate()
             << "|" << static_cast<int>(p.pobierzStopien()) << "\n";
    }

    // Wypożyczenia
    for (const auto& w : biblioteka.pobierzWypozyczenia()) {
        plik << "WYPOZYCZENIE|" << w.pobierzIdWypozyczenia() << "|"
             << w.pobierzIdCzytelnika() << "|" << w.pobierzKodKreskowy()
             << "|" << w.pobierzDate() << "\n";
    }
}