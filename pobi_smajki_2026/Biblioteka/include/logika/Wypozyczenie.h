#pragma once

#include <string>

/**
 * Klasa reprezentująca pojedyncze wypożyczenie egzemplarza przez czytelnika.
 */
class Wypozyczenie {
    std::string idWypozyczenia;
    std::string idCzytelnika;
    std::string kodKreskowy;
    std::string dataWypozyczenia;

public:
    /**
     * Konstruktor wypożyczenia.
     * @param idWyp Identyfikator wypożyczenia.
     * @param idCzyt Identyfikator czytelnika.
     * @param kod Kod kreskowy egzemplarza.
     * @param data Data wypożyczenia w formacie tekstowym.
     */
    Wypozyczenie(const std::string& idWyp, const std::string& idCzyt,
                 const std::string& kod, const std::string& data);

    /** @return Identyfikator wypożyczenia. */
    const std::string& pobierzIdWypozyczenia() const { return idWypozyczenia; }

    /** @return Identyfikator czytelnika. */
    const std::string& pobierzIdCzytelnika() const { return idCzytelnika; }

    /** @return Kod kreskowy wypożyczonego egzemplarza. */
    const std::string& pobierzKodKreskowy() const { return kodKreskowy; }

    /** @return Data wypożyczenia. */
    const std::string& pobierzDate() const { return dataWypozyczenia; }
};