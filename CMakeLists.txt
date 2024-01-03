idf_component_register(SRC_DIRS "${COMPONENT_DIR}"
                       INCLUDE_DIRS "${COMPONENT_DIR}")
target_compile_options(${COMPONENT_LIB} PRIVATE -Wall -Wextra -Wpedantic -std=c11)
