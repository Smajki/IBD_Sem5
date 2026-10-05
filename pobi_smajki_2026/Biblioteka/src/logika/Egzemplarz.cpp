#include "logika/Egzemplarz.h"

Egzemplarz::Egzemplarz(const std::string& kod) : kodKreskowy(kod), status(StatusEgzemplarza::Dostepny) {
}

bool Egzemplarz::czyDostepny() const {
    return status == StatusEgzemplarza::Dostepny;
}

void Egzemplarz::oznaczWypozyczony() {
    status = StatusEgzemplarza::Wypozyczony;
}

void Egzemplarz::oznaczDostepny() {
    status = StatusEgzemplarza::Dostepny;
}

void Egzemplarz::oznaczZaginiony() {
    status = StatusEgzemplarza::Zaginiony;
}