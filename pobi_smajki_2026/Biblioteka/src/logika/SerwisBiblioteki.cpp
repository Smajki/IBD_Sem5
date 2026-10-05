#include "logika/SerwisBiblioteki.h"
#include "logika/Biblioteka.h"
#include <stdexcept>
#include <sstream>
#include <chrono>
#include <iomanip>

SerwisBiblioteki::SerwisBiblioteki(IRepozytoriumBiblioteki& repo, IPolitykaKary& polityka) : repo(repo), politykaKary(polityka) {
}

void SerwisBiblioteki::wypozyczEgzemplarz(const std::string& idCzytelnika,
                                           const std::string& kodKreskowy) {
    Biblioteka& biblioteka = repo.pobierzBiblioteke();

    Czytelnik* czytelnik = biblioteka.znajdzCzytelnika(idCzytelnika);
    if (!czytelnik) {
        throw std::runtime_error("Czytelnik o podanym ID nie istnieje.");
    }

    Egzemplarz* egzemplarz = biblioteka.znajdzEgzemplarz(kodKreskowy);
    if (!egzemplarz) {
        throw std::runtime_error("Egzemplarz o podanym kodzie nie istnieje.");
    }

    if (!egzemplarz->czyDostepny()) {
        throw std::runtime_error("Egzemplarz jest juz wypozyczony lub zaginiony.");
    }

    static int numerWypozyczenia = 1;
    std::string idWyp = "WYP" + std::to_string(numerWypozyczenia++);

    // Data YYYY-MM-DD
    auto teraz = std::chrono::system_clock::now();
    std::time_t czas = std::chrono::system_clock::to_time_t(teraz);
    std::ostringstream ss;
    ss << std::put_time(std::localtime(&czas), "%Y-%m-%d");

    egzemplarz->oznaczWypozyczony();
    biblioteka.dodajWypozyczenie(Wypozyczenie(idWyp, idCzytelnika, kodKreskowy, ss.str()));
}

void SerwisBiblioteki::zwrocEgzemplarz(const std::string& kodKreskowy) {
    Biblioteka& biblioteka = repo.pobierzBiblioteke();

    Egzemplarz* egzemplarz = biblioteka.znajdzEgzemplarz(kodKreskowy);
    if (!egzemplarz) {
        throw std::runtime_error("Egzemplarz o podanym kodzie nie istnieje.");
    }

    if (egzemplarz->czyDostepny()) {
        throw std::runtime_error("Egzemplarz nie jest wypozyczony.");
    }

    egzemplarz->oznaczDostepny();
    biblioteka.usunWypozyczeniePoKod(kodKreskowy);
}