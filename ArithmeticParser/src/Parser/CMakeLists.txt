target_include_directories(ArithmeticParserObjectLib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(ArithmeticParserObjectLib PRIVATE
	"ErrorData.cpp"
	"LexicalParser.cpp"
	"Node.cpp"
	"SyntacticParser.cpp"
	"Token.cpp"
)