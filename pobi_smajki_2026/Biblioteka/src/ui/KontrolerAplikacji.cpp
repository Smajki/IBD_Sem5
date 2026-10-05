/**
 * @file KontrolerAplikacji.cpp
 * @brief Implementacja głównego kontrolera łączącego UI z logiką biznesową.
 */

#include "ui/KontrolerAplikacji.h"
#include "dane/RepozytoriumBibliotekiWPliku.h"
#include "logika/PolitykaKary.h"
#include "logika/SerwisBiblioteki.h"
#include "logika/Biblioteka.h"
#include <iostream>
#include <fmt/core.h>
#include <fmt/color.h>
#include <sstream>

KontrolerAplikacji::KontrolerAplikacji()
    : ui(std::make_unique<KonsolaUI>())
    , repo(std::make_unique<RepozytoriumBibliotekiWPliku>("biblioteka.dat"))
    , polityka(std::make_unique<PolitykaKary>(1.0))
    , serwis(std::make_unique<SerwisBiblioteki>(*repo, *polityka))
{
}

void KontrolerAplikacji::uruchom() {
    bool dziala = true;
    while (dziala) {
        ui->pokazMenu();
        std::string komenda = ui->czytajKomende();

        if (komenda == "1") {
            // ----- Wypożyczenie egzemplarza -----
            std::string idCzyt = ui->czytajLinie("Podaj ID czytelnika: ");
            std::string kod = ui->czytajLinie("Podaj kod kreskowy: ");
            try {
                serwis->wypozyczEgzemplarz(idCzyt, kod);
                repo->zapisz();   // automatyczny zapis zgodnie ze scenariuszem
                ui->wypisz("Wypozyczono pomyslnie.");
            } catch (const std::exception& e) {
                ui->wypisz(std::string("Blad: ") + e.what());
            }
        }
        else if (komenda == "2") {
            // ----- Zwrot egzemplarza -----
            std::string kod = ui->czytajLinie("Podaj kod kreskowy: ");
            try {
                serwis->zwrocEgzemplarz(kod);
                repo->zapisz();   // automatyczny zapis zgodnie ze scenariuszem
                ui->wypisz("Zwrocono pomyslnie.");
            } catch (const std::exception& e) {
                ui->wypisz(std::string("Blad: ") + e.what());
            }
        }
        else if (komenda == "3") {
            // ----- Wyświetlenie czytelników -----
            const auto& czytelnicy = repo->pobierzBiblioteke().pobierzCzytelnikow();
            if (czytelnicy.empty()) {
                ui->wypisz("Brak czytelnikow.");
            } else {
                for (const auto& c : czytelnicy) {
                    ui->wypisz("ID: " + c.pobierzId() + " - " + c.pobierzImieINazwisko());
                }
            }
        }
        else if (komenda == "4") {
            const auto& ksiazki = repo->pobierzBiblioteke().pobierzKsiazki();
            if (ksiazki.empty()) {
                ui->wypisz("Brak ksiazek.");
            } else {
                for (const auto& k : ksiazki) {
                    fmt::print(fmt::emphasis::bold, "ISBN: {} - {}\n", k.pobierzIsbn(), k.pobierzTytul());

                    const auto& autorzy = k.pobierzAutorow();
                    if (!autorzy.empty()) {
                        fmt::print("  Autorzy: ");
                        for (size_t i = 0; i < autorzy.size(); ++i) {
                            if (i > 0) fmt::print(", ");
                            fmt::print("{}", autorzy[i].pobierzImieINazwisko());
                        }
                        fmt::print("\n");
                    }

                    const auto& egz = k.pobierzEgzemplarze();
                    fmt::print("  Liczba egzemplarzy: {}\n", egz.size());
                    for (const auto& e : egz) {
                        std::string kod = e.pobierzKod();
                        bool dostepny = e.czyDostepny();
                        fmt::color kolor = dostepny ? fmt::color::green : fmt::color::red;
                        fmt::print(fg(kolor), "    {} [{}]\n",
                                   kod, dostepny ? "Dostepny" : "Wypozyczony");
                    }
                }
            }
        }
        else if (komenda == "5") {
            // ----- Dodawanie czytelnika -----
            std::string id = ui->czytajLinie("ID czytelnika: ");
            std::string imie = ui->czytajLinie("Imie i nazwisko: ");
            try {
                repo->pobierzBiblioteke().dodajCzytelnika(Czytelnik(id, imie));
                repo->zapisz();
                ui->wypisz("Dodano czytelnika.");
            } catch (const std::exception& e) {
                ui->wypisz(std::string("Blad: ") + e.what());
            }
        }
        else if (komenda == "6") {
            // ----- Dodawanie książki -----
            std::string isbn = ui->czytajLinie("ISBN: ");
            std::string tytul = ui->czytajLinie("Tytul: ");
            std::string autorImie = ui->czytajLinie("Imie i nazwisko autora: ");
            try {
                Ksiazka k(isbn, tytul);
                k.dodajAutora(Autor(autorImie));

                // Opcjonalne dodanie egzemplarza od razu
                std::string odpowiedz = ui->czytajLinie("Czy chcesz od razu dodac egzemplarz? (t/n): ");
                if (odpowiedz == "t" || odpowiedz == "T") {
                    std::string kod = ui->czytajLinie("Kod kreskowy egzemplarza: ");
                    // Dodamy egzemplarz do książki po wstawieniu do biblioteki,
                    repo->pobierzBiblioteke().dodajKsiazke(k);
                    repo->pobierzBiblioteke().dodajEgzemplarzDoKsiazki(isbn, Egzemplarz(kod));
                } else {
                    repo->pobierzBiblioteke().dodajKsiazke(k);
                }
                repo->zapisz();
                ui->wypisz("Dodano ksiazke (z autorem).");
            } catch (const std::exception& e) {
                ui->wypisz(std::string("Blad: ") + e.what());
            }
        }
        else if (komenda == "7") {
            // ----- Dodawanie egzemplarza do istniejącej książki -----
            std::string isbn = ui->czytajLinie("Podaj ISBN ksiazki: ");
            std::string kod  = ui->czytajLinie("Kod kreskowy egzemplarza: ");
            try {
                repo->pobierzBiblioteke().dodajEgzemplarzDoKsiazki(isbn, Egzemplarz(kod));
                repo->zapisz();
                ui->wypisz("Dodano egzemplarz.");
            } catch (const std::exception& e) {
                ui->wypisz(std::string("Blad: ") + e.what());
            }
        }
        else if (komenda == "8") {
            // ----- Zapis i zakończenie -----
            repo->zapisz();
            ui->wypisz("Stan zapisano. Do widzenia.");
            dziala = false;
        }
        else {
            ui->wypisz("Nieznana komenda.");
        }
    }
}