function(declare_symbols LIB_NAME LIB_SYMBOL_NAME FILE_PATH)
    configure_file(${CMAKE_SOURCE_DIR}/cmake/LibSymbols.h.in ${FILE_PATH} @ONLY)
endfunction()
