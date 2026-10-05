cmake_minimum_required(VERSION 3.16)
project(Biblioteka LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Katalog z plikami nagłówkowymi
include_directories(${PROJECT_SOURCE_DIR}/include)

# Zewnętrzna biblioteka: fmt (formatowanie i kolory w konsoli)
find_package(fmt REQUIRED)

# Pliki źródłowe aplikacji głównej
set(SOURCES
        main.cpp
        src/ui/KontrolerAplikacji.cpp
        src/ui/KonsolaUI.cpp
        src/logika/SerwisBiblioteki.cpp
        src/logika/Biblioteka.cpp
        src/logika/Czlowiek.cpp
        src/logika/Czytelnik.cpp
        src/logika/Pracownik.cpp
        src/logika/Ksiazka.cpp
        src/logika/Egzemplarz.cpp
        src/logika/Wypozyczenie.cpp
        src/logika/PolitykaKary.cpp
        src/logika/Autor.cpp
        src/dane/RepozytoriumBibliotekiWPamieci.cpp
        src/dane/RepozytoriumBibliotekiWPliku.cpp
)

add_executable(Biblioteka ${SOURCES})
target_link_libraries(Biblioteka PRIVATE fmt::fmt)

option(BUILD_TESTS "testy" ON)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()