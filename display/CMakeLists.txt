# Create a library from the source files in this directory.

project (VRDisplay)

set (${PROJECT_NAME}_source_files 
	VRDisplayDevice.cpp
	VRCallbackDisplayAction.cpp
	VRCallbackDisplayFrameAction.cpp
	VRCallbackRenderer.cpp
	concrete/BaseDisplayDevice.cpp
	concrete/BaseDisplayFactory.cpp
	concrete/CommandLineDisplay.cpp
	concrete/CompositeDisplay.cpp
	concrete/CompositeDisplayFactory.cpp
	concrete/DataIndexWrapperDisplay.cpp
	display-graph/VRDisplayGraphNode.cpp
)

add_library (${PROJECT_NAME} ${${PROJECT_NAME}_source_files})

install(DIRECTORY ${PROJECT_SOURCE_DIR}  DESTINATION "include" FILES_MATCHING PATTERN "*.h")

install( TARGETS ${PROJECT_NAME}
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib
         RUNTIME DESTINATION bin)