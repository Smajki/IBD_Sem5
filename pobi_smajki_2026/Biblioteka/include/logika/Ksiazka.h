#pragma once

#include <string>
#include <vector>
#include "Egzemplarz.h"
#include "Autor.h"

/**
 * Klasa reprezentująca tytuł książki wraz z jej egzemplarzami i autorami.
 */
class Ksiazka {
    std::string isbn;
    std::string tytul;
    std::vector<Egzemplarz> egzemplarze;
    std::vector<Autor> autorzy;

public:
    /**
     * Konstruktor książki – tworzy pozycję bez egzemplarzy i autorów.
     * @param isbn Numer ISBN.
     * @param tytul Tytuł książki.
     */
    Ksiazka(const std::string& isbn, const std::string& tytul);

    /** @return ISBN książki. */
    const std::string& pobierzIsbn() const { return isbn; }

    /** @return Tytuł książki. */
    const std::string& pobierzTytul() const { return tytul; }

    /** @return Wektor egzemplarzy (stały dostęp). */
    const std::vector<Egzemplarz>& pobierzEgzemplarze() const { return egzemplarze; }

    /** @return Wektor egzemplarzy (modyfikowalny – potrzebne dla Biblioteki). */
    std::vector<Egzemplarz>& pobierzEgzemplarze() { return egzemplarze; }

    /** Dodaje nowy egzemplarz do książki. */
    void dodajEgzemplarz(const Egzemplarz& egz) { egzemplarze.push_back(egz); }

    /** @return Wektor autorów. */
    const std::vector<Autor>& pobierzAutorow() const { return autorzy; }

    /** Dodaje autora do książki. */
    void dodajAutora(const Autor& autor) { autorzy.push_back(autor); }
};