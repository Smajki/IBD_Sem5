#pragma once

#include "IPolitykaKary.h"

/**
 * Prosta implementacja polityki kar – stała stawka dzienna.
 */
class PolitykaKary : public IPolitykaKary {
    double stawkaDzienna;

public:
    /**
     * Konstruktor ustalający stawkę dzienną.
     * @param stawka Kara za jeden dzień zwłoki (domyślnie 0.50 zł).
     */
    explicit PolitykaKary(double stawka = 0.50);

    /**
     * Oblicza całkowitą karę.
     * @param dni Liczba dni po terminie.
     * @return Należna kara.
     */
    double obliczKare(int dni) const override;
};