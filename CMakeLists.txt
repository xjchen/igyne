
# Module name (usually identique to the directory name)
set(qt_module_name "Igyne")
set(qt_module_title "iGyne")

# Build module sub libraries
add_subdirectory(Logic)

set(qt_module_export_directive "Q_SLICER_QTMODULES_IGYNE_EXPORT")

# Additional includes - Current_{source,binary} and Slicer_{Libs,Base} already included
set(qt_module_include_directories
  ${CMAKE_CURRENT_SOURCE_DIR}/Widgets
  ${CMAKE_CURRENT_BINARY_DIR}/Widgets
  ${CMAKE_CURRENT_SOURCE_DIR}/Logic
  ${CMAKE_CURRENT_BINARY_DIR}/Logic
  )

# Source files
set(qt_module_SRCS
  qSlicerIgyneModule.cxx
  qSlicerIgyneModule.h
  qSlicerIgyneModuleWidget.cxx
  qSlicerIgyneModuleWidget.h
<<<<<<< HEAD
  qTemplateSheetWidget.cxx
  qTemplateSheetWidget.h  
=======
>>>>>>> c46f7c7e827d4c7307c467571091d7bf54eb80ff
  )

# Headers that should run through moc
set(qt_module_MOC_SRCS
  qSlicerIgyneModule.h
  qSlicerIgyneModuleWidget.h
<<<<<<< HEAD
  qTemplateSheetWidget.h  
=======
>>>>>>> c46f7c7e827d4c7307c467571091d7bf54eb80ff
  )

# UI files
set(qt_module_UI_SRCS
  Resources/UI/qSlicerIgyneModule.ui
<<<<<<< HEAD
  Resources/UI/qTemplateSheetWidget.ui  
=======
>>>>>>> c46f7c7e827d4c7307c467571091d7bf54eb80ff
  )

# Additional Target libraries
set(qt_module_target_libraries
  vtkSlicerIgyneModuleLogic
  )

# Resources
set(qt_module_resources
  Resources/qSlicerIgyneModule.qrc
  )

slicerMacroBuildQtModule(
  NAME ${qt_module_name}
  TITLE ${qt_module_title}
  EXPORT_DIRECTIVE ${qt_module_export_directive}
  INCLUDE_DIRECTORIES ${qt_module_include_directories}
  SRCS ${qt_module_SRCS}
  MOC_SRCS ${qt_module_MOC_SRCS}
  UI_SRCS ${qt_module_UI_SRCS}
  TARGET_LIBRARIES ${qt_module_target_libraries}
  RESOURCES ${qt_module_resources}
  )


<<<<<<< HEAD
# if(BUILD_TESTING)
#   add_subdirectory(Testing)
# endif()
=======
if(BUILD_TESTING)
  add_subdirectory(Testing)
endif()
>>>>>>> c46f7c7e827d4c7307c467571091d7bf54eb80ff
