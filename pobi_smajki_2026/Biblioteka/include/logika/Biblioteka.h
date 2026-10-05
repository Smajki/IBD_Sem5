#pragma once

#include <vector>
#include <algorithm>
#include <stdexcept>
#include "logika/Ksiazka.h"
#include "logika/Czytelnik.h"
#include "logika/Pracownik.h"
#include "logika/Wypozyczenie.h"
#include "logika/Egzemplarz.h"

/**
 * @brief Główny agregat przechowujący cały stan biblioteki.
 * Odpowiada za spójność danych – wszystkie operacje modyfikujące kolekcje
 * przechodzą przez metody tej klasy, które dbają o unikalność identyfikatorów.
 */
class Biblioteka {
    std::vector<Ksiazka> ksiazki;
    std::vector<Czytelnik> czytelnicy;
    std::vector<Pracownik> pracownicy;
    std::vector<Wypozyczenie> wypozyczenia;

public:
    template<typename T, typename Pred>
    T* znajdz(std::vector<T>& kontener, Pred pred) {
        auto it = std::find_if(kontener.begin(), kontener.end(), pred);
        return it != kontener.end() ? &(*it) : nullptr;
    }

    template<typename T, typename Pred>
    const T* znajdz(const std::vector<T>& kontener, Pred pred) const {
        auto it = std::find_if(kontener.begin(), kontener.end(), pred);
        return it != kontener.end() ? &(*it) : nullptr;
    }

    Czytelnik* znajdzCzytelnika(const std::string& id);
    Egzemplarz* znajdzEgzemplarz(const std::string& kodKreskowy);

    void dodajWypozyczenie(const Wypozyczenie& w);
    void usunWypozyczeniePoKod(const std::string& kodKreskowy);

    std::vector<Ksiazka>& pobierzKsiazki() { return ksiazki; }
    std::vector<Czytelnik>& pobierzCzytelnikow() { return czytelnicy; }
    std::vector<Pracownik>& pobierzPracownikow() { return pracownicy; }
    std::vector<Wypozyczenie>& pobierzWypozyczenia() { return wypozyczenia; }

    const std::vector<Ksiazka>& pobierzKsiazki() const { return ksiazki; }
    const std::vector<Czytelnik>& pobierzCzytelnikow() const { return czytelnicy; }
    const std::vector<Pracownik>& pobierzPracownikow() const { return pracownicy; }
    const std::vector<Wypozyczenie>& pobierzWypozyczenia() const { return wypozyczenia; }

    /**
     * @brief Dodaje nową książkę. ISBN musi być unikalny.
     * @param k Książka do dodania.
     * @throw std::invalid_argument jeśli książka o podanym ISBN już istnieje.
     */
    void dodajKsiazke(const Ksiazka& k);

    /**
     * @brief Dodaje nowego czytelnika. ID musi być unikalne.
     * @param c Czytelnik do dodania.
     * @throw std::invalid_argument jeśli czytelnik o podanym ID już istnieje.
     */
    void dodajCzytelnika(const Czytelnik& c);

    /**
     * @brief Dodaje nowego pracownika. ID musi być unikalne.
     * @param p Pracownik do dodania.
     * @throw std::invalid_argument jeśli pracownik o podanym ID już istnieje.
     */
    void dodajPracownika(const Pracownik& p);

    /**
     * @brief Dodaje egzemplarz do książki o podanym ISBN.
     * @param isbn ISBN książki, do której dodawany jest egzemplarz.
     * @param egzemplarz Egzemplarz do dodania.
     * @throw std::invalid_argument jeśli książka nie istnieje, lub egzemplarz o podanym kodzie kreskowym już istnieje (globalnie).
     */
    void dodajEgzemplarzDoKsiazki(const std::string& isbn, const Egzemplarz& egzemplarz);

    /**
     * @brief Dodaje autora do książki o podanym ISBN.
     * @param isbn ISBN książki.
     * @param autor Autor do dodania.
     * @throw std::invalid_argument jeśli książka nie istnieje.
     */
    void dodajAutoraDoKsiazki(const std::string& isbn, const Autor& autor);
};