#include "ui/KonsolaUI.h"
#include <fmt/core.h>
#include <fmt/color.h>
#include <iostream>
#include <limits>

void KonsolaUI::pokazMenu() const {
    fmt::print(fmt::emphasis::bold | fg(fmt::color::steel_blue), "\n=== Biblioteka - Menu ===\n");
    fmt::print("1. Wypozycz egzemplarz\n");
    fmt::print("2. Zwroc egzemplarz\n");
    fmt::print("3. Pokaz wszystkich czytelnikow\n");
    fmt::print("4. Pokaz wszystkie ksiazki\n");
    fmt::print("5. Dodaj czytelnika\n");
    fmt::print("6. Dodaj ksiazke\n");
    fmt::print("7. Dodaj egzemplarz do istniejacej ksiazki\n");
    fmt::print("8. Zapisz i wyjdz\n");
    fmt::print("Wybierz opcje: ");
}

std::string KonsolaUI::czytajKomende() const {
    std::string komenda;
    std::cin >> komenda;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return komenda;
}

void KonsolaUI::wypisz(const std::string& tekst) const {
    fmt::print("{}\n", tekst);
}

std::string KonsolaUI::czytajLinie(const std::string& prompt) const {
    std::cout << prompt;
    std::string linia;
    std::getline(std::cin, linia);
    return linia;
}