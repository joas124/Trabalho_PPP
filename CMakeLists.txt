cmake_minimum_required(VERSION 3.0.0)
project(trabalho VERSION 0.1.0)

add_compile_options(-Wall -Wextra -Werror -executable)

include(CTest)
enable_testing()

add_executable(trabalho main.c ../headers/principal.h ../headers/principal.c ../headers/auxiliar.h ../headers/auxiliar.c ../headers/alunos.h ../headers/alunos.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
