#pragma once

#include "IRepozytoriumBiblioteki.h"
#include "logika/Biblioteka.h"

/**
 * Implementacja repozytorium przechowująca dane w pamięci.
 * Zapis jest operacją pustą – dane istnieją tylko w trakcie działania programu.
 */
class RepozytoriumBibliotekiWPamieci : public IRepozytoriumBiblioteki {
    Biblioteka biblioteka;

public:
    /**
     * Zwraca referencję do obiektu biblioteki przechowywanego w pamięci.
     */
    Biblioteka& pobierzBiblioteke() override;

    /**
     * Operacja zapisu – w tej implementacji nic nie robi.
     */
    void zapisz() override;
};