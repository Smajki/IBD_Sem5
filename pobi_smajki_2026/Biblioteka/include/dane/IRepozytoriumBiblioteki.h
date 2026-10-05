#pragma once

class Biblioteka;

/**
 * Interfejs repozytorium biblioteki – abstrakcyjna warstwa dostępu do danych.
 * Pozwala odseparować logikę biznesową od konkretnego sposobu przechowywania.
 */
class IRepozytoriumBiblioteki {
public:
    virtual ~IRepozytoriumBiblioteki() = default;

    /**
     * Zwraca referencję do zarządzanej biblioteki.
     * @return Referencja do obiektu Biblioteka.
     */
    virtual Biblioteka& pobierzBiblioteke() = 0;

    /**
     * Zapisuje aktualny stan biblioteki do docelowego nośnika.
     */
    virtual void zapisz() = 0;
};