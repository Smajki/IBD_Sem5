#include "logika/Czytelnik.h"

Czytelnik::Czytelnik(const std::string& id, const std::string& imieINazwisko) : Czlowiek(id, imieINazwisko) {
}

std::string Czytelnik::rola() const {
    return "Czytelnik";
}