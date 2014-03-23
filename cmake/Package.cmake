
if(WIN32)
    INSTALL(FILES vcredist_x64.exe DESTINATION ./)
    SET(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
    SET(CPACK_NSIS_EXTRA_INSTALL_COMMANDS 
            ${CPACK_NSIS_EXTRA_INSTALL_COMMANDS} 
            "ExecWait '\\\"$INSTDIR\\\\vcredist_x64.exe\\\" /quiet /norestart'")
    SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "${CPACK_PACKAGE_NAME} ${CPACK_PACKAGE_VERSION} (Win64)")
    set(CPACK_NSIS_CREATE_ICONS "CreateShortCut '\$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\${PROJECT_NAME}.lnk' '\$INSTDIR\\\\${PROJECT_NAME}.exe'")
endif() 

set(CPACK_PACKAGE_NAME                  "${META_PROJECT_NAME}")
set(CPACK_PACKAGE_VENDOR                "${META_AUTHOR_ORGANIZATION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY   "${META_AUTHOR_DOMAIN}")
set(CPACK_PACKAGE_VERSION               "${META_VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR         "${META_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR         "${META_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH         "${META_VERSION_PATCH}")
set(CPACK_RESOURCE_FILE_LICENSE         "${VOXELLANCER_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README          "${VOXELLANCER_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_WELCOME         "${VOXELLANCER_SOURCE_DIR}/README.md")
set(CPACK_PACKAGE_DESCRIPTION_FILE      "${VOXELLANCER_SOURCE_DIR}/README.md")
set(CPACK_PACKAGE_ICON                  "")
set(CPACK_PACKAGE_RELOCATABLE           OFF)

include(CPack)