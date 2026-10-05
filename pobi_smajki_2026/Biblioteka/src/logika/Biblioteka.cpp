#include "logika/Biblioteka.h"
#include <stdexcept>

Czytelnik* Biblioteka::znajdzCzytelnika(const std::string& id) {
    return znajdz(czytelnicy, [&id](const Czytelnik& c) {
        return c.pobierzId() == id;
    });
}

Egzemplarz* Biblioteka::znajdzEgzemplarz(const std::string& kodKreskowy) {
    for (auto& ksiazka : ksiazki) {
        auto& egzemplarze = ksiazka.pobierzEgzemplarze();
        Egzemplarz* egz = znajdz(egzemplarze, [&kodKreskowy](const Egzemplarz& e) {
            return e.pobierzKod() == kodKreskowy;
        });
        if (egz) return egz;
    }
    return nullptr;
}

void Biblioteka::dodajWypozyczenie(const Wypozyczenie& w) {
    wypozyczenia.push_back(w);
}

void Biblioteka::usunWypozyczeniePoKod(const std::string& kodKreskowy) {
    wypozyczenia.erase(
        std::remove_if(wypozyczenia.begin(), wypozyczenia.end(),
            [&kodKreskowy](const Wypozyczenie& w) {
                return w.pobierzKodKreskowy() == kodKreskowy;
            }),
        wypozyczenia.end()
    );
}

void Biblioteka::dodajKsiazke(const Ksiazka& k) {
    auto it = std::find_if(ksiazki.begin(), ksiazki.end(),
        [&k](const Ksiazka& istniejaca) {
            return istniejaca.pobierzIsbn() == k.pobierzIsbn();
        });
    if (it != ksiazki.end()) {
        throw std::invalid_argument("Ksiazka o podanym ISBN juz istnieje.");
    }
    ksiazki.push_back(k);
}

void Biblioteka::dodajCzytelnika(const Czytelnik& c) {
    auto it = std::find_if(czytelnicy.begin(), czytelnicy.end(),
        [&c](const Czytelnik& istniejacy) {
            return istniejacy.pobierzId() == c.pobierzId();
        });
    if (it != czytelnicy.end()) {
        throw std::invalid_argument("Czytelnik o podanym ID juz istnieje.");
    }
    czytelnicy.push_back(c);
}

void Biblioteka::dodajPracownika(const Pracownik& p) {
    auto it = std::find_if(pracownicy.begin(), pracownicy.end(),
        [&p](const Pracownik& istniejacy) {
            return istniejacy.pobierzId() == p.pobierzId();
        });
    if (it != pracownicy.end()) {
        throw std::invalid_argument("Pracownik o podanym ID juz istnieje.");
    }
    pracownicy.push_back(p);
}

void Biblioteka::dodajEgzemplarzDoKsiazki(const std::string& isbn, const Egzemplarz& egzemplarz) {
    if (znajdzEgzemplarz(egzemplarz.pobierzKod()) != nullptr) {
        throw std::invalid_argument("Egzemplarz o podanym kodzie kreskowym juz istnieje.");
    }
    auto it = std::find_if(ksiazki.begin(), ksiazki.end(),
        [&isbn](const Ksiazka& k) { return k.pobierzIsbn() == isbn; });
    if (it == ksiazki.end()) {
        throw std::invalid_argument("Ksiazka o podanym ISBN nie istnieje.");
    }
    it->dodajEgzemplarz(egzemplarz);
}

void Biblioteka::dodajAutoraDoKsiazki(const std::string& isbn, const Autor& autor) {
    auto it = std::find_if(ksiazki.begin(), ksiazki.end(),
        [&isbn](const Ksiazka& k) { return k.pobierzIsbn() == isbn; });
    if (it == ksiazki.end()) {
        throw std::invalid_argument("Ksiazka o podanym ISBN nie istnieje.");
    }
    it->dodajAutora(autor);
}