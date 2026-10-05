#pragma once

#include <string>
#include "IRepozytoriumBiblioteki.h"
#include "logika/Biblioteka.h"

/**
 * Implementacja repozytorium zapisująca stan biblioteki w pliku tekstowym.
 * Wczytuje dane przy konstrukcji, zapisuje na żądanie.
 */
class RepozytoriumBibliotekiWPliku : public IRepozytoriumBiblioteki {
    Biblioteka biblioteka;
    std::string sciezka;

    /**
     * Wewnętrzna metoda do wczytania danych z pliku.
     * Wywoływana automatycznie w konstruktorze.
     */
    void wczytaj();

public:
    /**
     * Konstruktor przyjmujący ścieżkę do pliku z danymi.
     * @param sciezka Ścieżka do pliku.
     */
    explicit RepozytoriumBibliotekiWPliku(const std::string& sciezka);

    /**
     * Zwraca referencję do biblioteki wczytanej z pliku.
     */
    Biblioteka& pobierzBiblioteke() override;

    /**
     * Zapisuje aktualny stan biblioteki do pliku wskazanego w konstruktorze.
     */
    void zapisz() override;
};