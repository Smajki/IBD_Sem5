#pragma once

/**
 * Interfejs strategii obliczania kary pieniężnej za przetrzymanie książki.
 */
class IPolitykaKary {
public:
    virtual ~IPolitykaKary() = default;

    /**
     * Oblicza karę na podstawie liczby dni opóźnienia.
     * @param liczbaDniPoTerminie Liczba dni po upływie terminu zwrotu.
     * @return Kwota kary.
     */
    virtual double obliczKare(int liczbaDniPoTerminie) const = 0;
};