#pragma once

#include <string>

/**
 * Klasa odpowiedzialna za komunikację tekstową z użytkownikiem.
 * Udostępnia proste metody do wyświetlania komunikatów i odczytywania danych.
 */
class KonsolaUI {
public:
    /**
     * @brief Wyświetla główne menu aplikacji.
     */
    void pokazMenu() const;

    /**
     * @brief Odczytuje komendę wpisaną przez użytkownika (pojedyncze słowo).
     * @return Łańcuch znaków z wpisaną komendą.
     */
    std::string czytajKomende() const;

    /**
     * @brief Wypisuje na konsolę podany tekst.
     * @param tekst Komunikat do wyświetlenia.
     */
    void wypisz(const std::string& tekst) const;

    /**
     * @brief Wyświetla prompt i odczytuje całą linię tekstu.
     * @param prompt Tekst wyświetlany przed odczytem.
     * @return Wczytana linia (bez znaku nowej linii).
     */
    std::string czytajLinie(const std::string& prompt) const;
};