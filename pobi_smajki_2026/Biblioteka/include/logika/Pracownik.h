#pragma once

#include "Czlowiek.h"
#include <string>

/** Stopień służbowy pracownika biblioteki. */
enum class StopienPracownika {
    Mlodszy,
    Starszy,
    Kierownik
};

/**
 * Klasa reprezentująca pracownika biblioteki.
 * Dziedziczy po Czlowiek i dodaje informacje o stanowisku, wypłacie i stopniu.
 */
class Pracownik : public Czlowiek {
    std::string stanowisko;
    double wyplata;
    StopienPracownika stopien;

public:
    /**
     * Konstruktor pracownika.
     * @param id Identyfikator pracownika.
     * @param imieINazwisko Imię i nazwisko.
     * @param stanowisko Nazwa stanowiska.
     * @param wyplata Wysokość miesięcznej wypłaty.
     * @param stopien Stopień pracownika (enum).
     */
    Pracownik(const std::string& id, const std::string& imieINazwisko,
              const std::string& stanowisko, double wyplata, StopienPracownika stopien);

    /**
     * Implementacja metody rola – zwraca "Pracownik".
     */
    std::string rola() const override;

    /** @return Stanowisko pracownika. */
    const std::string& pobierzStanowisko() const { return stanowisko; }

    /** @return Wypłata. */
    double pobierzWyplate() const { return wyplata; }

    /** @return Stopień pracownika. */
    StopienPracownika pobierzStopien() const { return stopien; }
};