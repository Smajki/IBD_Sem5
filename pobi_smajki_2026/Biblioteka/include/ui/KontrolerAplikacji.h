#pragma once

#include <memory>
#include "ui/KonsolaUI.h"
#include "logika/SerwisBiblioteki.h"
#include "dane/IRepozytoriumBiblioteki.h"
#include "logika/IPolitykaKary.h"

/**
 * @brief Główny kontroler aplikacji – łączy warstwę UI z logiką biznesową.
 * Zarządza cyklem życia repozytorium, polityki kar, serwisu bibliotecznego oraz interfejsu
 * użytkownika. Odpowiada za przepływ sterowania: wyświetlanie menu, odczytywanie komend
 * i delegowanie ich do odpowiednich komponentów.
 */
class KontrolerAplikacji {
    std::unique_ptr<KonsolaUI> ui;
    std::unique_ptr<IRepozytoriumBiblioteki> repo;
    std::unique_ptr<IPolitykaKary> polityka;
    std::unique_ptr<SerwisBiblioteki> serwis;

public:
    /**
     * @brief Konstruktor inicjujący wszystkie zależności.
     * Tworzy repozytorium plikowe (biblioteka.dat), domyślną politykę kar (1 zł/dzień)
     * oraz serwis biblioteczny. Interfejs użytkownika jest inicjowany jako KonsolaUI.
     */
    KontrolerAplikacji();

    /**
     * @brief Uruchamia główną pętlę aplikacji.
     * Wyświetla menu, odczytuje komendy użytkownika i wywołuje odpowiednie metody
     * serwisu bibliotecznego lub bezpośrednio modyfikuje dane poprzez repozytorium.
     * Po każdej operacji zmieniającej stan zapisuje dane.
     */
    void uruchom();
};