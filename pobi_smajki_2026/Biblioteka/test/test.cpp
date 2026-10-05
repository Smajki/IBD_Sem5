#define BOOST_TEST_MODULE BibliotekaTests
#include <boost/test/included/unit_test.hpp>

#include "logika/SerwisBiblioteki.h"
#include "logika/Biblioteka.h"
#include "dane/RepozytoriumBibliotekiWPamieci.h"
#include "logika/PolitykaKary.h"

#include <stdexcept>



BOOST_AUTO_TEST_SUITE(DodawanieEncji)

/**
 * @brief Test dodawania unikalnego czytelnika.
 */
BOOST_AUTO_TEST_CASE(DodawanieUnikalnegoCzytelnika) {
    RepozytoriumBibliotekiWPamieci repo;
    Biblioteka& b = repo.pobierzBiblioteke();
    BOOST_CHECK_NO_THROW(b.dodajCzytelnika(Czytelnik("1", "Imię Nazwisko")));
    BOOST_CHECK_EQUAL(b.pobierzCzytelnikow().size(), 1);
}

/**
 * @brief Test próby dodania czytelnika z istniejącym ID – powinien rzucić wyjątek.
 */
BOOST_AUTO_TEST_CASE(DuplikatCzytelnika) {
    RepozytoriumBibliotekiWPamieci repo;
    Biblioteka& b = repo.pobierzBiblioteke();
    b.dodajCzytelnika(Czytelnik("1", "Imię Nazwisko"));
    BOOST_CHECK_THROW(b.dodajCzytelnika(Czytelnik("1", "Inne Imię")), std::invalid_argument);
}

/**
 * @brief Test dodawania unikalnej książki.
 */
BOOST_AUTO_TEST_CASE(DodawanieUnikalnejKsiazki) {
    RepozytoriumBibliotekiWPamieci repo;
    Biblioteka& b = repo.pobierzBiblioteke();
    BOOST_CHECK_NO_THROW(b.dodajKsiazke(Ksiazka("123-456", "Fajna Książka")));
    BOOST_CHECK_EQUAL(b.pobierzKsiazki().size(), 1);
}

/**
 * @brief Test próby dodania książki z istniejącym ISBN – powinien rzucić wyjątek.
 */
BOOST_AUTO_TEST_CASE(DuplikatKsiazki) {
    RepozytoriumBibliotekiWPamieci repo;
    Biblioteka& b = repo.pobierzBiblioteke();
    b.dodajKsiazke(Ksiazka("123-456", "Fajna Książka"));
    BOOST_CHECK_THROW(b.dodajKsiazke(Ksiazka("123-456", "Inna Książka")), std::invalid_argument);
}

/**
 * @brief Test dodawania unikalnego egzemplarza.
 */
BOOST_AUTO_TEST_CASE(DodawanieUnikalnegoEgzemplarza) {
    RepozytoriumBibliotekiWPamieci repo;
    Biblioteka& b = repo.pobierzBiblioteke();
    b.dodajKsiazke(Ksiazka("123-456", "Fajna Książka"));
    BOOST_CHECK_NO_THROW(b.dodajEgzemplarzDoKsiazki("123-456", Egzemplarz("2")));
    BOOST_CHECK_EQUAL(b.pobierzKsiazki()[0].pobierzEgzemplarze().size(), 1);
}

/**
 * @brief Test próby dodania egzemplarza z istniejącym kodem kreskowym – globalna unikalność.
 */
BOOST_AUTO_TEST_CASE(DuplikatEgzemplarza) {
    RepozytoriumBibliotekiWPamieci repo;
    Biblioteka& b = repo.pobierzBiblioteke();
    b.dodajKsiazke(Ksiazka("123-456", "Fajna Książka"));
    b.dodajKsiazke(Ksiazka("789-012", "Inna Książka"));
    b.dodajEgzemplarzDoKsiazki("123-456", Egzemplarz("2"));
    // Próba dodania tego samego kodu do innej książki
    BOOST_CHECK_THROW(b.dodajEgzemplarzDoKsiazki("789-012", Egzemplarz("2")), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()




BOOST_AUTO_TEST_SUITE(Wypozyczanie)

/**
 * @brief Test poprawnego wypożyczenia dostępnego egzemplarza.
 */
BOOST_AUTO_TEST_CASE(WypozyczenieDostepnegoEgzemplarza) {
    RepozytoriumBibliotekiWPamieci repo;
    PolitykaKary polityka(1.0);
    SerwisBiblioteki serwis(repo, polityka);

    Biblioteka& b = repo.pobierzBiblioteke();
    b.dodajCzytelnika(Czytelnik("1", "Imię Nazwisko"));
    b.dodajKsiazke(Ksiazka("123-456", "Fajna Książka"));
    b.dodajEgzemplarzDoKsiazki("123-456", Egzemplarz("2"));

    BOOST_CHECK_NO_THROW(serwis.wypozyczEgzemplarz("1", "2"));
    Egzemplarz* egz = b.znajdzEgzemplarz("2");
    BOOST_REQUIRE(egz != nullptr);
    BOOST_CHECK_EQUAL(egz->czyDostepny(), false);
}

/**
 * @brief Test wypożyczenia egzemplarza dla nieistniejącego czytelnika.
 */
BOOST_AUTO_TEST_CASE(WypozyczenieDlaBlednegoCzytelnika) {
    RepozytoriumBibliotekiWPamieci repo;
    PolitykaKary polityka(1.0);
    SerwisBiblioteki serwis(repo, polityka);

    Biblioteka& b = repo.pobierzBiblioteke();
    b.dodajKsiazke(Ksiazka("123-456", "Fajna Książka"));
    b.dodajEgzemplarzDoKsiazki("123-456", Egzemplarz("2"));

    BOOST_CHECK_THROW(serwis.wypozyczEgzemplarz("inne", "2"), std::runtime_error);
}

/**
 * @brief Test wypożyczenia nieistniejącego egzemplarza.
 */
BOOST_AUTO_TEST_CASE(WypozyczenieBlednegoEgzemplarza) {
    RepozytoriumBibliotekiWPamieci repo;
    PolitykaKary polityka(1.0);
    SerwisBiblioteki serwis(repo, polityka);

    Biblioteka& b = repo.pobierzBiblioteke();
    b.dodajCzytelnika(Czytelnik("1", "Imię Nazwisko"));

    BOOST_CHECK_THROW(serwis.wypozyczEgzemplarz("1", "BRAK"), std::runtime_error);
}

/**
 * @brief Test próby wypożyczenia już wypożyczonego egzemplarza.
 */
BOOST_AUTO_TEST_CASE(WypozyczenieJuzWypozyczonego) {
    RepozytoriumBibliotekiWPamieci repo;
    PolitykaKary polityka(1.0);
    SerwisBiblioteki serwis(repo, polityka);

    Biblioteka& b = repo.pobierzBiblioteke();
    b.dodajCzytelnika(Czytelnik("1", "Imię Nazwisko"));
    b.dodajCzytelnika(Czytelnik("C2", "Inne Imię"));
    b.dodajKsiazke(Ksiazka("123-456", "Fajna Książka"));
    b.dodajEgzemplarzDoKsiazki("123-456", Egzemplarz("2"));

    serwis.wypozyczEgzemplarz("1", "2");
    BOOST_CHECK_THROW(serwis.wypozyczEgzemplarz("C2", "2"), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()





BOOST_AUTO_TEST_SUITE(Zwrot)

/**
 * @brief Test poprawnego zwrotu wypożyczonego egzemplarza.
 */
BOOST_AUTO_TEST_CASE(ZwrotWypozyczonegoEgzemplarza) {
    RepozytoriumBibliotekiWPamieci repo;
    PolitykaKary polityka(1.0);
    SerwisBiblioteki serwis(repo, polityka);

    Biblioteka& b = repo.pobierzBiblioteke();
    b.dodajCzytelnika(Czytelnik("1", "Imię Nazwisko"));
    b.dodajKsiazke(Ksiazka("123-456", "Fajna Książka"));
    b.dodajEgzemplarzDoKsiazki("123-456", Egzemplarz("2"));

    serwis.wypozyczEgzemplarz("1", "2");
    BOOST_CHECK_NO_THROW(serwis.zwrocEgzemplarz("2"));
    Egzemplarz* egz = b.znajdzEgzemplarz("2");
    BOOST_REQUIRE(egz != nullptr);
    BOOST_CHECK(egz->czyDostepny());
}

/**
 * @brief Test próby zwrotu nieistniejącego egzemplarza.
 */
BOOST_AUTO_TEST_CASE(ZwrotNieistniejacegoEgzemplarza) {
    RepozytoriumBibliotekiWPamieci repo;
    PolitykaKary polityka(1.0);
    SerwisBiblioteki serwis(repo, polityka);

    BOOST_CHECK_THROW(serwis.zwrocEgzemplarz("BRAK"), std::runtime_error);
}

/**
 * @brief Test próby zwrotu egzemplarza, który nie jest wypożyczony.
 */
BOOST_AUTO_TEST_CASE(ZwrotDostepnegoEgzemplarza) {
    RepozytoriumBibliotekiWPamieci repo;
    PolitykaKary polityka(1.0);
    SerwisBiblioteki serwis(repo, polityka);

    Biblioteka& b = repo.pobierzBiblioteke();
    b.dodajKsiazke(Ksiazka("123-456", "Fajna Książka"));
    b.dodajEgzemplarzDoKsiazki("123-456", Egzemplarz("2"));

    BOOST_CHECK_THROW(serwis.zwrocEgzemplarz("2"), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()





BOOST_AUTO_TEST_SUITE(PolitykaKar)

/**
 * @brief Test obliczania kary za przetrzymanie książki.
 */
BOOST_AUTO_TEST_CASE(ObliczanieKary) {
    PolitykaKary polityka(2.5);
    BOOST_CHECK_CLOSE(polityka.obliczKare(5), 12.5, 0.001);
    BOOST_CHECK_EQUAL(polityka.obliczKare(0), 0.0);
}

BOOST_AUTO_TEST_SUITE_END()