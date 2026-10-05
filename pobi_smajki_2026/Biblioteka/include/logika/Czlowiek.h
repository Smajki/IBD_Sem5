#pragma once

#include <string>

/**
 * Abstrakcyjna klasa bazowa dla osób powiązanych z biblioteką.
 * Zawiera wspólne dane: identyfikator i imię z nazwiskiem.
 */
class Czlowiek {
protected:
    std::string id;
    std::string imieINazwisko;

public:
    /**
     * Konstruktor inicjujący pola chronione.
     * @param id Identyfikator osoby (np. numer legitymacji).
     * @param imieINazwisko Imię i nazwisko.
     */
    Czlowiek(const std::string& id, const std::string& imieINazwisko);

    virtual ~Czlowiek() = default;

    /**
     * Zwraca tekstową reprezentację roli pełnionej przez osobę.
     * Metoda wirtualna – implementowana w klasach pochodnych.
     */
    virtual std::string rola() const = 0;

    /** @return Identyfikator osoby. */
    const std::string& pobierzId() const { return id; }

    /** @return Imię i nazwisko. */
    const std::string& pobierzImieINazwisko() const { return imieINazwisko; }
};