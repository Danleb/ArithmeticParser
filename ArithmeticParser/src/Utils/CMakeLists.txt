target_include_directories(ArithmeticParserObjectLib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(ArithmeticParserObjectLib PRIVATE
	"ArgumentsParsing.cpp"
	"ArithmeticParserApi.cpp"
	"Utils.cpp"
)