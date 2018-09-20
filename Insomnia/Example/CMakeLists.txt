function(add_insomnia_test target)
    add_executable(${target} ${ARGN})
    target_link_libraries(${target} PRIVATE Insomnia)
    target_compile_features(${target} PRIVATE cxx_std_17)
endfunction()

add_insomnia_test(BlackjackTest ToyText/Blackjack.cpp)