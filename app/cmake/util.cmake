macro(create_alias INPUT)
if (${INPUT}_REL AND ${INPUT}_DEBUG)
   set(${INPUT} optimized ${${INPUT}_REL} debug ${${INPUT}_DEBUG})
endif()
endmacro(create_alias)