#pragma once

#include <string>
#include <stdexcept>
#include "dane/IRepozytoriumBiblioteki.h"
#include "logika/IPolitykaKary.h"

/**
 * Serwis biblioteczny – realizuje wypożyczanie i zwrot egzemplarzy.
 * Korzysta z repozytorium do odczytu/zapisu stanu oraz z polityki kar.
 */
class SerwisBiblioteki {
    IRepozytoriumBiblioteki& repo;
    IPolitykaKary& politykaKary;

public:
    /**
     * Konstruktor przyjmujący referencje do repozytorium i polityki kar.
     * @param repo Referencja do repozytorium biblioteki.
     * @param polityka Referencja do obiektu polityki kar.
     */
    SerwisBiblioteki(IRepozytoriumBiblioteki& repo, IPolitykaKary& polityka);

    /**
     * Wypożycza egzemplarz danemu czytelnikowi.
     * Zmienia status egzemplarza na wypożyczony i rejestruje wypożyczenie.
     * @param idCzytelnika Identyfikator czytelnika.
     * @param kodKreskowy Kod kreskowy egzemplarza.
     * @throw std::runtime_error gdy czytelnik nie istnieje, egzemplarz nie istnieje lub jest niedostępny.
     */
    void wypozyczEgzemplarz(const std::string& idCzytelnika, const std::string& kodKreskowy);

    /**
     * Przyjmuje zwrot egzemplarza.
     * Oznacza egzemplarz jako dostępny i usuwa rekord wypożyczenia.
     * @param kodKreskowy Kod kreskowy zwracanego egzemplarza.
     * @throw std::runtime_error gdy egzemplarz nie istnieje lub nie był wypożyczony.
     */
    void zwrocEgzemplarz(const std::string& kodKreskowy);
};