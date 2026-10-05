#pragma once

#include <string>

/** Status fizycznego egzemplarza książki. */
enum class StatusEgzemplarza {
    Dostepny,
    Wypozyczony,
    Zaginiony
};

/**
 * Klasa reprezentująca pojedynczy egzemplarz książki.
 * Identyfikowany unikalnym kodem.
 */
class Egzemplarz {
    std::string kodKreskowy;
    StatusEgzemplarza status;

public:
    /**
     * Konstruktor egzemplarza – domyślnie dostępny.
     * @param kod Unikalny kod.
     */
    explicit Egzemplarz(const std::string& kod);

    /** @return Czy egzemplarz jest dostępny do wypożyczenia. */
    bool czyDostepny() const;

    /** Oznacza egzemplarz jako wypożyczony. */
    void oznaczWypozyczony();

    /** Oznacza egzemplarz jako ponownie dostępny. */
    void oznaczDostepny();

    /** Oznacza egzemplarz jako zaginiony. */
    void oznaczZaginiony();

    /** @return Kod kreskowy egzemplarza. */
    const std::string& pobierzKod() const { return kodKreskowy; }

    /** @return Aktualny status egzemplarza. */
    StatusEgzemplarza pobierzStatus() const { return status; }
};