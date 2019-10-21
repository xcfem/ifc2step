cmake_minimum_required (VERSION 3.7.2)
project(ifc2step)

set(IFCPP_LIBRARIES libIfcPlusPlusd.a)
add_executable(ifc2step ifc2step.cc)
target_include_directories(ifc2step
    PRIVATE
    ${OPENTHREADS_INCLUDE_DIR}
    ${OSG_INCLUDE_DIR}
    ${OSGGA_INCLUDE_DIR}
    ${OSGDB_INCLUDE_DIR}
    ${OSGUTIL_INCLUDE_DIR}
    ${OSGANIMATION_INCLUDE_DIR}
    ${OSGTEXT_INCLUDE_DIR}
)
target_link_libraries(ifc2step ${IFCPP_LIBRARIES} ${OPENTHREADS_LIBRARY} )
install(
    TARGETS ifc2step
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION lib
)
