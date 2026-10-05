#include "logika/Wypozyczenie.h"

Wypozyczenie::Wypozyczenie(const std::string& idWyp, const std::string& idCzyt, const std::string& kod, const std::string& data)
    : idWypozyczenia(idWyp)
    , idCzytelnika(idCzyt)
    , kodKreskowy(kod)
    , dataWypozyczenia(data) {
}