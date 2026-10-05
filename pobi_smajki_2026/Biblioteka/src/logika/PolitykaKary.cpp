#include "logika/PolitykaKary.h"

PolitykaKary::PolitykaKary(double stawka) : stawkaDzienna(stawka) {
}

double PolitykaKary::obliczKare(int dni) const {
    if (dni <= 0) return 0.0;
    return stawkaDzienna * dni;
}