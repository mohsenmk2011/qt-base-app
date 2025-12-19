
qt_add_resources(${PROJECT_NAME} "currentappqmlfiles"
    PREFIX "/"
    FILES
    app/CurrentApp.cmake
    app/CurrentAppSettingsPane.qml
)
qt_add_resources(${PROJECT_NAME} "currentappimages"
    PREFIX "/"
    FILES
)

#find_package(Qt6 REQUIRED COMPONENTS Charts)

#target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Charts)
