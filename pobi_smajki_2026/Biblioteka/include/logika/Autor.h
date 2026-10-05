#pragma once

#include <string>

/**
 * Prosta klasa przechowująca dane autora książki.
 */
class Autor {
    std::string imieINazwisko;

public:
    /**
     * Konstruktor autora.
     * @param imieINazwisko Imię i nazwisko autora.
     */
    explicit Autor(const std::string& imieINazwisko);

    /** @return Imię i nazwisko autora. */
    const std::string& pobierzImieINazwisko() const { return imieINazwisko; }

    /** Ustawia nowe imię i nazwisko autora. */
    void ustawImieINazwisko(const std::string& nowe) { imieINazwisko = nowe; }
};