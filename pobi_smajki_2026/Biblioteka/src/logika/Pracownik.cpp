#include "logika/Pracownik.h"

Pracownik::Pracownik(const std::string& id, const std::string& imieINazwisko,
                     const std::string& stanowisko, double wyplata, StopienPracownika stopien)
                    : Czlowiek(id, imieINazwisko)
                    , stanowisko(stanowisko)
                    , wyplata(wyplata)
                    , stopien(stopien) {
}

std::string Pracownik::rola() const {
    return "Pracownik";
}