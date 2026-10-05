#pragma once

#include "Czlowiek.h"

/**
 * Klasa reprezentująca czytelnika biblioteki.
 * Dziedziczy po abstrakcyjnej klasie Czlowiek.
 */
class Czytelnik : public Czlowiek {
public:
    /**
     * Konstruktor czytelnika.
     * @param id Identyfikator czytelnika.
     * @param imieINazwisko Imię i nazwisko.
     */
    Czytelnik(const std::string& id, const std::string& imieINazwisko);

    /**
     * Implementacja metody rola – zwraca "Czytelnik".
     */
    std::string rola() const override;
};