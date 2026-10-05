cmake_policy(SET CMP0167 NEW)

find_package(Boost REQUIRED CONFIG COMPONENTS unit_test_framework)

# Źródła testów
set(TEST_SOURCES
        test.cpp
        ../src/logika/SerwisBiblioteki.cpp
        ../src/logika/Biblioteka.cpp
        ../src/logika/Czlowiek.cpp
        ../src/logika/Czytelnik.cpp
        ../src/logika/Pracownik.cpp
        ../src/logika/Ksiazka.cpp
        ../src/logika/Egzemplarz.cpp
        ../src/logika/Wypozyczenie.cpp
        ../src/logika/PolitykaKary.cpp
        ../src/logika/Autor.cpp
        ../src/dane/RepozytoriumBibliotekiWPamieci.cpp
)

add_executable(runTests ${TEST_SOURCES})
target_link_libraries(runTests PRIVATE Boost::unit_test_framework)
target_include_directories(runTests PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_test(NAME BibliotekaTests COMMAND runTests)