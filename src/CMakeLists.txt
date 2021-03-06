add_library(mmbot_shared_deps INTERFACE)
target_sources(mmbot_shared_deps INTERFACE
        app/mmbot.application.cpp
        mm2/mm2.client.cpp
        cex/cex.cpp
        config/config.cpp
        dex/dex.cpp
        dex/dex.utils.cpp
        http/http.price.rest.cpp
        http/http.mm2.rest.cpp
        http/http.sm.rest.cpp
        http/http.server.cpp
        order_manager/order.manager.cpp
        orders/orders.cpp
        price/coinpaprika.price.platform.cpp
        price/service.price.platform.cpp
        strategy_manager/strategy.manager.cpp
        utils/antara.utils.cpp
        utils/mmbot_strong_types.cpp)
target_compile_features(mmbot_shared_deps INTERFACE cxx_std_17)
target_include_directories(mmbot_shared_deps INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(mmbot_shared_deps INTERFACE absl::numeric mmbot::bcmath mmbot::log mmbot::http mmbot::default_settings nlohmann_json::nlohmann_json strong_type Cpp-Taskflow mmbot::restinio reproc++
        $<$<AND:$<PLATFORM_ID:Linux>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
        $<$<PLATFORM_ID:Darwin>:c++fs>)
target_enable_tsan(mmbot_shared_deps)
target_enable_ubsan(mmbot_shared_deps)
target_enable_asan(mmbot_shared_deps)

add_executable(mmbot)
target_sources(mmbot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(mmbot PUBLIC mmbot_shared_deps)

add_executable(mmbot-test)
target_sources(mmbot-test PUBLIC
        mmbot.tests.cpp
        mm2/mm2.client.tests.cpp
        cex/cex.tests.cpp
        config/config.tests.cpp
        strategy_manager/strategy.manager.tests.cpp
        order_manager/order.manager.tests.cpp
        orders/orders.tests.cpp
        price/coinpaprika.price.platform.tests.cpp
        price/factory.price.plaftorm.tests.cpp
        price/service.price.platform.tests.cpp
        http/http.server.tests.cpp
        utils/antara.utils.tests.cpp
        utils/mmbot_strong_types.tests.cpp)
target_link_libraries(mmbot-test PRIVATE doctest trompeloeil PUBLIC mmbot_shared_deps)
target_enable_coverage(mmbot-test)
set_target_properties(mmbot-test mmbot
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )

if (UNIX)
    configure_file(${PROJECT_SOURCE_DIR}/assets/mmbot_config.json ${CMAKE_BINARY_DIR}/bin/assets/mmbot_config.json COPYONLY)
    configure_file(${PROJECT_SOURCE_DIR}/assets/MM2.json ${CMAKE_BINARY_DIR}/bin/assets/MM2.json COPYONLY)
else ()
    configure_file(${PROJECT_SOURCE_DIR}/assets/mmbot_config.json ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/assets/mmbot_config.json COPYONLY)
    configure_file(${PROJECT_SOURCE_DIR}/assets/MM2.json ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/assets/MM2.json COPYONLY)
endif ()
