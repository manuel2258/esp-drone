set(COMPONENT_SRCS 
    "src/main.cpp"
    "src/app/main_client.cpp" "src/app/main_server.cpp" "src/app/base_main.cpp"
    "src/app/net/wifi_ap.cpp" "src/app/net/tcp_server.cpp" "src/app/net/wifi_sta.cpp" "src/app/net/tcp_client.cpp"
    "src/app/pkg/input_pkg.cpp" "src/app/pkg/adjust_pkg.cpp" "src/app/pkg/hello_pkg.cpp"
    "src/app/ses/session.cpp" "src/app/ses/builder.cpp" "src/app/ses/system_mutex.cpp" "src/app/ses/system_watchdog.cpp"
    "src/app/ses/pip/pipeline.cpp" "src/app/ses/pip/builder.cpp" "src/app/ses/pip/processors.cpp"
    "src/app/ses/eve/event_chain.cpp" "src/app/ses/eve/builder.cpp")

register_component()
