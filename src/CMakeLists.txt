add_executable(ipp main.cpp models/customer.cpp models/sales_invoice.cpp)


target_link_libraries(ipp mvcpp ${CMAKE_THREAD_LIBS_INIT} sqlite3)
