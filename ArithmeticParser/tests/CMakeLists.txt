add_executable(ArithmeticParserTests "")

target_link_libraries(ArithmeticParserTests
    ArithmeticParserObjectLib
    ${CONAN_LIBS}
)

add_subdirectory("ArgumentsParsing")
add_subdirectory("LexicalParser")
add_subdirectory("SyntacticParser")

enable_testing()

add_test(NAME ArithmeticParserTests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    COMMAND ArithmeticParserTests
)