set(COMPONENT_SRCS 
    "src/main.cpp"
    "src/app/main_client.cpp" "src/app/main_server.cpp" "src/app/base_main.cpp"
    "src/app/net/wifi_ap.cpp" "src/app/net/tcp_server.cpp" "src/app/net/wifi_sta.cpp" "src/app/net/tcp_client.cpp"
    "src/app/pkg/input_pkg.cpp")

register_component()
