cmake_minimum_required(VERSION 3.10)

# Nome del progetto
project(FinancialTransactions)

# Imposta lo standard C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Aggiungi i file sorgente
add_executable(FinancialTransactions
        main.cpp
        Account.cpp
        Transaction.cpp
)

# Aggiungi i file header
target_include_directories(FinancialTransactions
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Aggiungi Catch2 usando FetchContent
include(FetchContent)
FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.13.7
)
FetchContent_MakeAvailable(catch2)

# Abilita il testing
enable_testing()

# Aggiungi il test
add_executable(runUnitTests
        test.cpp
        Account.cpp
        Transaction.cpp
)

target_link_libraries(runUnitTests Catch2::Catch2)

add_test(NAME runUnitTests COMMAND runUnitTests)
