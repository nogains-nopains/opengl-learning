# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (Tutorials)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()



# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-1c73e35")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)



include_directories(
	external/AntTweakBar-1.16/include/
	external/glfw-3.0.3/include/GLFW/
	external/glm-0.9.4.0/
	external/glew-1.9.0/include/
	external/assimp-3.0.1270/include/
	external/bullet-2.81-rev2613/src/
	external/soil/src
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	GLFW_303
	GLEW_190
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)



#############################
# Tutorial open.gl.square
add_executable(open.gl.square 
	open.gl.square/square.cpp
	common/shader.cpp
	common/shader.hpp
	
	open.gl.square/SimpleFragmentShader.fragmentshader
	open.gl.square/SimpleVertexShader.vertexshader
)
target_link_libraries(open.gl.square
	${ALL_LIBS}
)

# Xcode and Visual working directories
set_target_properties(open.gl.square PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.square/")
create_target_launcher(open.gl.square WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.square/")
create_default_target_launcher(open.gl.square WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.square/") 


#############################
# Tutorial open.gl.texture

add_subdirectory (3rdparty/soil) 

add_executable(open.gl.texture
	open.gl.texture/gltexture.cpp
	common/shader.cpp
	common/shader.hpp
	
	open.gl.texture/TransformVertexShader.vertexshader
	open.gl.texture/TextureFragmentShader.fragmentshader
)

target_link_libraries(open.gl.texture
	${ALL_LIBS}
	SOIL
)
# Xcode and Visual working directories
set_target_properties(open.gl.texture PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.texture/")
create_target_launcher(open.gl.texture WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.texture/")


#############################
# Tutorial open.gl.texture_kitten_puppy

add_executable(open.gl.texture_kitten_puppy
	open.gl.texture_kitten_puppy/gltexture_kp.cpp
	common/shader.cpp
	common/shader.hpp
#	common/texture.cpp
#	common/texture.hpp
	
	open.gl.texture_kitten_puppy/TransformVertexShader.vertexshader
	open.gl.texture_kitten_puppy/TextureFragmentShader.fragmentshader
)

target_link_libraries(open.gl.texture_kitten_puppy
	${ALL_LIBS}
	SOIL
#	C:/Users/Chenghai/Downloads/OpenGL-tutorial_v0014_33/OpenGL-tutorial_v0014_33/build/open.gl.texture_kitten_puppy.dir/Debug/SOIL.lib
#	C:/Users/Chenghai/Downloads/OpenGL-tutorial_v0014_33/OpenGL-tutorial_v0014_33/3rdparty/soil/projects/VC9/Debug/SOIL.lib
)
# Xcode and Visual working directories
set_target_properties(open.gl.texture_kitten_puppy PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.texture_kitten_puppy/")
create_target_launcher(open.gl.texture_kitten_puppy WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.texture_kitten_puppy/")

#############################
# Tutorial open.gl.texture_reflection

add_executable(open.gl.texture_reflection
	open.gl.texture_reflection/gltexture_reflection.cpp
	common/shader.cpp
	common/shader.hpp
#	common/texture.cpp
#	common/texture.hpp
	
	open.gl.texture_reflection/TransformVertexShader.vertexshader
	open.gl.texture_reflection/TextureFragmentShader.fragmentshader
)

target_link_libraries(open.gl.texture_reflection
	${ALL_LIBS}
	SOIL
#	C:/Users/Chenghai/Downloads/OpenGL-tutorial_v0014_33/OpenGL-tutorial_v0014_33/build/open.gl.texture_reflection.dir/Debug/SOIL.lib
#	C:/Users/Chenghai/Downloads/OpenGL-tutorial_v0014_33/OpenGL-tutorial_v0014_33/3rdparty/soil/projects/VC9/Debug/SOIL.lib
)
# Xcode and Visual working directories
set_target_properties(open.gl.texture_reflection PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.texture_reflection/")
create_target_launcher(open.gl.texture_reflection WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.texture_reflection/")

#############################
# Tutorial open.gl.texture_transform1

add_executable(open.gl.texture_transform1
	open.gl.texture_transform1/gltexture_transform1.cpp
	common/shader.cpp
	common/shader.hpp
	
	open.gl.texture_transform1/TransformVertexShader.vertexshader
	open.gl.texture_transform1/TextureFragmentShader.fragmentshader
)

target_link_libraries(open.gl.texture_transform1
	${ALL_LIBS}
	SOIL
)
# Xcode and Visual working directories
set_target_properties(open.gl.texture_transform1 PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.texture_transform1/")
create_target_launcher(open.gl.texture_transform1 WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.texture_transform1/")


#############################
# Tutorial open.gl.texture_rotation

add_executable(open.gl.texture_rotation
	open.gl.texture_rotation/gltexture_rotation.cpp
	common/shader.cpp
	common/shader.hpp
	
	open.gl.texture_rotation/TransformVertexShader.vertexshader
	open.gl.texture_rotation/TextureFragmentShader.fragmentshader
)

target_link_libraries(open.gl.texture_rotation
	${ALL_LIBS}
	SOIL
)
# Xcode and Visual working directories
set_target_properties(open.gl.texture_rotation PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.texture_rotation/")
create_target_launcher(open.gl.texture_rotation WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.texture_rotation/")



#############################
# Tutorial open.gl.depthbuffer

add_executable(open.gl.depthbuffer
	open.gl.depthbuffer/gltexture_depth_buffer.cpp
	common/shader.cpp
	common/shader.hpp
	
	open.gl.depthbuffer/TransformVertexShader.vertexshader
	open.gl.depthbuffer/TextureFragmentShader.fragmentshader
)

target_link_libraries(open.gl.depthbuffer
	${ALL_LIBS}
	SOIL
)
# Xcode and Visual working directories
set_target_properties(open.gl.depthbuffer PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.depthbuffer/")
create_target_launcher(open.gl.depthbuffer WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.depthbuffer/")


#############################
# Tutorial open.gl.depthstencil

add_executable(open.gl.depthstencil
	open.gl.depthstencil/depthstencil.cpp
	common/shader.cpp
	common/shader.hpp
	
	open.gl.depthstencil/TransformVertexShader.vertexshader
	open.gl.depthstencil/TextureFragmentShader.fragmentshader
)

target_link_libraries(open.gl.depthstencil
	${ALL_LIBS}
	SOIL
)
# Xcode and Visual working directories
set_target_properties(open.gl.depthstencil PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.depthstencil/")
create_target_launcher(open.gl.depthstencil WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.depthstencil/")



#############################
# Tutorial open.gl.stencil_buffer_101

add_executable(open.gl.stencil_buffer_101
	open.gl.stencil_buffer_101/stencil_buffer_101.cpp
	common/shader.cpp
	common/shader.hpp
	
	open.gl.stencil_buffer_101/TransformVertexShader.vertexshader
	open.gl.stencil_buffer_101/TextureFragmentShader.fragmentshader
)

target_link_libraries(open.gl.stencil_buffer_101
	${ALL_LIBS}
	SOIL
)
# Xcode and Visual working directories
set_target_properties(open.gl.stencil_buffer_101 PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.stencil_buffer_101/")
create_target_launcher(open.gl.stencil_buffer_101 WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.stencil_buffer_101/")

#############################
# Tutorial 1
add_executable(tutorial01_first_window 
	tutorial01_first_window/tutorial01.cpp
)
target_link_libraries(tutorial01_first_window
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial01_first_window PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial01_first_window/")
create_target_launcher(tutorial01_first_window WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial01_first_window/")

# Tutorial 2
add_executable(tutorial02_red_triangle 
	tutorial02_red_triangle/tutorial02.cpp
	common/shader.cpp
	common/shader.hpp
	
	tutorial02_red_triangle/SimpleFragmentShader.fragmentshader
	tutorial02_red_triangle/SimpleVertexShader.vertexshader
)
target_link_libraries(tutorial02_red_triangle
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial02_red_triangle PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial02_red_triangle/")
create_target_launcher(tutorial02_red_triangle WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial02_red_triangle/")
create_default_target_launcher(tutorial02_red_triangle WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial02_red_triangle/") # tut 1 is not the default or people would complain that tut 2 doesn't work

# Tutorial 3
add_executable(tutorial03_matrices 
	tutorial03_matrices/tutorial03.cpp
	common/shader.cpp
	common/shader.hpp

	tutorial03_matrices/SimpleTransform.vertexshader
	tutorial03_matrices/SingleColor.fragmentshader
)
#set_target_properties(tutorial03_matrices PROPERTIES RUNTIME_OUTPUT_DIRECTORY /test1)
target_link_libraries(tutorial03_matrices
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial03_matrices PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial03_matrices/")
create_target_launcher(tutorial03_matrices WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial03_matrices/") # Visual

# Tutorial 4
add_executable(tutorial04_colored_cube
	tutorial04_colored_cube/tutorial04.cpp
	common/shader.cpp
	common/shader.hpp
	
	tutorial04_colored_cube/TransformVertexShader.vertexshader
	tutorial04_colored_cube/ColorFragmentShader.fragmentshader
)
target_link_libraries(tutorial04_colored_cube
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial04_colored_cube PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial04_colored_cube/")
create_target_launcher(tutorial04_colored_cube WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial04_colored_cube/")

# Tutorial 5
add_executable(tutorial05_textured_cube
	tutorial05_textured_cube/tutorial05.cpp
	common/shader.cpp
	common/shader.hpp
	common/texture.cpp
	common/texture.hpp
	
	tutorial05_textured_cube/TransformVertexShader.vertexshader
	tutorial05_textured_cube/TextureFragmentShader.fragmentshader
)
target_link_libraries(tutorial05_textured_cube
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial05_textured_cube PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial05_textured_cube/")
create_target_launcher(tutorial05_textured_cube WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial05_textured_cube/")

# Tutorial 6
add_executable(tutorial06_keyboard_and_mouse
	tutorial06_keyboard_and_mouse/tutorial06.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	
	tutorial06_keyboard_and_mouse/TransformVertexShader.vertexshader
	tutorial06_keyboard_and_mouse/TextureFragmentShader.fragmentshader
)
target_link_libraries(tutorial06_keyboard_and_mouse
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial06_keyboard_and_mouse PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial06_keyboard_and_mouse/")
create_target_launcher(tutorial06_keyboard_and_mouse WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial06_keyboard_and_mouse/")

# Tutorial 7
add_executable(tutorial07_model_loading
	tutorial07_model_loading/tutorial07.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp

	tutorial07_model_loading/TransformVertexShader.vertexshader
	tutorial07_model_loading/TextureFragmentShader.fragmentshader
)
target_link_libraries(tutorial07_model_loading
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial07_model_loading PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial07_model_loading/")
create_target_launcher(tutorial07_model_loading WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial07_model_loading/")

# Tutorial 8
add_executable(tutorial08_basic_shading
	tutorial08_basic_shading/tutorial08.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	
	tutorial08_basic_shading/StandardShading.vertexshader
	tutorial08_basic_shading/StandardShading.fragmentshader
)
target_link_libraries(tutorial08_basic_shading
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial08_basic_shading PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial08_basic_shading/")
create_target_launcher(tutorial08_basic_shading WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial08_basic_shading/")

# Tutorial 9
add_executable(tutorial09_vbo_indexing
	tutorial09_vbo_indexing/tutorial09.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
	
	tutorial09_vbo_indexing/StandardShading.vertexshader
	tutorial09_vbo_indexing/StandardShading.fragmentshader
)
target_link_libraries(tutorial09_vbo_indexing
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial09_vbo_indexing PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial09_vbo_indexing/")
create_target_launcher(tutorial09_vbo_indexing WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial09_vbo_indexing/")

# Tutorial 9 - AssImp model loading
add_executable(tutorial09_AssImp
	tutorial09_vbo_indexing/tutorial09_AssImp.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	
	tutorial09_vbo_indexing/StandardShading.vertexshader
	tutorial09_vbo_indexing/StandardShading.fragmentshader
)
target_link_libraries(tutorial09_AssImp
	${ALL_LIBS}
	assimp
)
set_target_properties(tutorial09_AssImp PROPERTIES COMPILE_DEFINITIONS "USE_ASSIMP")
# Xcode and Visual working directories
set_target_properties(tutorial09_AssImp PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial09_vbo_indexing/")
create_target_launcher(tutorial09_AssImp WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial09_vbo_indexing/")

# Tutorial 9 - several objects
add_executable(tutorial09_several_objects
	tutorial09_vbo_indexing/tutorial09_several_objects.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
	
	tutorial09_vbo_indexing/StandardShading.vertexshader
	tutorial09_vbo_indexing/StandardShading.fragmentshader
)
target_link_libraries(tutorial09_several_objects
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial09_several_objects PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial09_vbo_indexing/")
create_target_launcher(tutorial09_several_objects WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial09_vbo_indexing/")

# Tutorial 10
add_executable(tutorial10_transparency
	tutorial10_transparency/tutorial10.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
	
	tutorial10_transparency/StandardShading.vertexshader
	tutorial10_transparency/StandardTransparentShading.fragmentshader
)
target_link_libraries(tutorial10_transparency
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial10_transparency PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial10_transparency/")
create_target_launcher(tutorial10_transparency WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial10_transparency/")

# Tutorial 11
add_executable(tutorial11_2d_fonts
	tutorial11_2d_fonts/tutorial11.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
	common/text2D.hpp
	common/text2D.cpp

	tutorial11_2d_fonts/StandardShading.vertexshader
	tutorial11_2d_fonts/StandardShading.fragmentshader
	tutorial11_2d_fonts/TextVertexShader.vertexshader
	tutorial11_2d_fonts/TextVertexShader.fragmentshader

)
target_link_libraries(tutorial11_2d_fonts
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial11_2d_fonts PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial11_2d_fonts/")
create_target_launcher(tutorial11_2d_fonts WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial11_2d_fonts/")

# Tutorial 12
add_executable(tutorial12_extensions
	tutorial12_extensions/tutorial12.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp

	tutorial12_extensions/StandardShading.vertexshader
	tutorial12_extensions/StandardShading_WithSyntaxErrors.fragmentshader
)
target_link_libraries(tutorial12_extensions
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial12_extensions PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial12_extensions/")
create_target_launcher(tutorial12_extensions WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial12_extensions/")

# Tutorial 13
add_executable(tutorial13_normal_mapping
	tutorial13_normal_mapping/tutorial13.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
	common/text2D.hpp
	common/text2D.cpp
	common/tangentspace.hpp
	common/tangentspace.cpp
	
	tutorial13_normal_mapping/NormalMapping.vertexshader
	tutorial13_normal_mapping/NormalMapping.fragmentshader
)
target_link_libraries(tutorial13_normal_mapping
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial13_normal_mapping PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial13_normal_mapping/")
create_target_launcher(tutorial13_normal_mapping WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial13_normal_mapping/")


# Tutorial 14
add_executable(tutorial14_render_to_texture
	tutorial14_render_to_texture/tutorial14.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
	common/text2D.hpp
	common/text2D.cpp
	
	tutorial14_render_to_texture/StandardShadingRTT.vertexshader
	tutorial14_render_to_texture/StandardShadingRTT.fragmentshader
	tutorial14_render_to_texture/Passthrough.vertexshader
	tutorial14_render_to_texture/WobblyTexture.fragmentshader
)
target_link_libraries(tutorial14_render_to_texture
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial14_render_to_texture PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial14_render_to_texture/")
create_target_launcher(tutorial14_render_to_texture WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial14_render_to_texture/")


# Tutorial 15
add_executable(tutorial15_lightmaps
	tutorial15_lightmaps/tutorial15.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
	
	tutorial15_lightmaps/TransformVertexShader.vertexshader
	tutorial15_lightmaps/TextureFragmentShaderLOD.fragmentshader
)
target_link_libraries(tutorial15_lightmaps
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial15_lightmaps PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial15_lightmaps/")
create_target_launcher(tutorial15_lightmaps WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial15_lightmaps/")

# Tutorial 16, simple version
add_executable(tutorial16_shadowmaps_simple
	tutorial16_shadowmaps/tutorial16_SimpleVersion.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
	
	tutorial16_shadowmaps/ShadowMapping_SimpleVersion.vertexshader
	tutorial16_shadowmaps/ShadowMapping_SimpleVersion.fragmentshader
	tutorial16_shadowmaps/DepthRTT.vertexshader
	tutorial16_shadowmaps/DepthRTT.fragmentshader
)
target_link_libraries(tutorial16_shadowmaps_simple
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial16_shadowmaps_simple PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial16_shadowmaps/")
create_target_launcher(tutorial16_shadowmaps_simple WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial16_shadowmaps/")


# Tutorial 16
add_executable(tutorial16_shadowmaps
	tutorial16_shadowmaps/tutorial16.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp

	tutorial16_shadowmaps/ShadowMapping.vertexshader
	tutorial16_shadowmaps/ShadowMapping.fragmentshader
	tutorial16_shadowmaps/DepthRTT.vertexshader
	tutorial16_shadowmaps/DepthRTT.fragmentshader
	tutorial16_shadowmaps/Passthrough.vertexshader
	tutorial16_shadowmaps/SimpleTexture.fragmentshader
)
target_link_libraries(tutorial16_shadowmaps
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial16_shadowmaps PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial16_shadowmaps/")
create_target_launcher(tutorial16_shadowmaps WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial16_shadowmaps/")

# Tutorial 17
add_executable(tutorial17_rotations
	tutorial17_rotations/tutorial17.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
	common/quaternion_utils.cpp
	common/quaternion_utils.hpp
	
	tutorial17_rotations/StandardShading.vertexshader
	tutorial17_rotations/StandardShading.fragmentshader
)
target_link_libraries(tutorial17_rotations
	${ALL_LIBS}
	ANTTWEAKBAR_116_OGLCORE_GLFW
)
# Xcode and Visual working directories
set_target_properties(tutorial17_rotations PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial17_rotations/")
create_target_launcher(tutorial17_rotations WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial17_rotations/")

# User playground
add_executable(playground 
	playground/playground.cpp
	common/shader.cpp
	common/shader.hpp
)
target_link_libraries(playground
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(playground PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/playground/")
create_target_launcher(playground WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/playground/")



# Misc 5, with glReadPixels
add_executable(misc05_picking_slow_easy
	misc05_picking/misc05_picking_slow_easy.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
	
	misc05_picking/StandardShading.vertexshader
	misc05_picking/StandardShading.fragmentshader
	misc05_picking/Picking.vertexshader
	misc05_picking/Picking.fragmentshader
)
target_link_libraries(misc05_picking_slow_easy
	${ALL_LIBS}
	ANTTWEAKBAR_116_OGLCORE_GLFW
)
# Xcode and Visual working directories
set_target_properties(misc05_picking_slow_easy PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/misc05_picking/")
create_target_launcher(misc05_picking_slow_easy WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/misc05_picking/")

# Misc 5, with custom ray-box intersection
add_executable(misc05_picking_custom
	misc05_picking/misc05_picking_custom.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
	
	misc05_picking/StandardShading.vertexshader
	misc05_picking/StandardShading.fragmentshader
)
target_link_libraries(misc05_picking_custom
	${ALL_LIBS}
	ANTTWEAKBAR_116_OGLCORE_GLFW
)
# Xcode and Visual working directories
set_target_properties(misc05_picking_custom PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/misc05_picking/")
create_target_launcher(misc05_picking_custom WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/misc05_picking/")

# Misc 5, with Bullet Physics
add_executable(misc05_picking_BulletPhysics
	misc05_picking/misc05_picking_BulletPhysics.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
	
	misc05_picking/StandardShading.vertexshader
	misc05_picking/StandardShading.fragmentshader
)
target_link_libraries(misc05_picking_BulletPhysics
	${ALL_LIBS}
	ANTTWEAKBAR_116_OGLCORE_GLFW
        BulletDynamics
        BulletCollision
        LinearMath
)
# Xcode and Visual working directories
set_target_properties(misc05_picking_BulletPhysics PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/misc05_picking/")
create_target_launcher(misc05_picking_BulletPhysics WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/misc05_picking/")



add_executable(tutorial18_billboards
	tutorial18_billboards_and_particles/tutorial18_billboards.cpp
	common/shader.cpp
	common/shader.hpp
	common/texture.cpp
	common/texture.hpp
	common/controls.cpp
	common/controls.hpp
	tutorial18_billboards_and_particles/Billboard.fragmentshader
	tutorial18_billboards_and_particles/Billboard.vertexshader
)

target_link_libraries(tutorial18_billboards
	${ALL_LIBS}
)

# Xcode and Visual working directories
set_target_properties(tutorial18_billboards PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial18_billboards_and_particles/")
create_target_launcher(tutorial18_billboards WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial18_billboards_and_particles/")

add_executable(tutorial18_particles
	tutorial18_billboards_and_particles/tutorial18_particles.cpp
	common/shader.cpp
	common/shader.hpp
	common/texture.cpp
	common/texture.hpp
	common/controls.cpp
	common/controls.hpp
	tutorial18_billboards_and_particles/Particle.fragmentshader
	tutorial18_billboards_and_particles/Particle.vertexshader
)

target_link_libraries(tutorial18_particles
	${ALL_LIBS}
)

# Xcode and Visual working directories
set_target_properties(tutorial18_particles PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial18_billboards_and_particles/")
create_target_launcher(tutorial18_particles WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial18_billboards_and_particles/")











SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )


if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
add_custom_command(
   TARGET tutorial01_first_window POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial01_first_window${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial01_first_window/"
)

add_custom_command(
   TARGET open.gl.square POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/open.gl.square.exe" "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.square/open.gl.square.exe"
)

add_custom_command(
   TARGET open.gl.texture POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/open.gl.texture${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.texture/"
)


add_custom_command(
   TARGET open.gl.texture_kitten_puppy POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/open.gl.texture_kitten_puppy${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.texture_kitten_puppy/"
)


add_custom_command(
   TARGET open.gl.texture_reflection POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/open.gl.texture_reflection${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.texture_reflection/"
)

add_custom_command(
   TARGET open.gl.texture_transform1 POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/open.gl.texture_transform1${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.texture_transform1/"
)


add_custom_command(
   TARGET open.gl.texture_rotation POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/open.gl.texture_rotation.exe" "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.texture_rotation/"
)

add_custom_command(
   TARGET open.gl.depthbuffer POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/open.gl.depthbuffer${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.depthbuffer/"
)

add_custom_command(
   TARGET open.gl.depthstencil POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/open.gl.depthstencil${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.depthstencil/"
)

add_custom_command(
   TARGET open.gl.stencil_buffer_101 POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/open.gl.stencil_buffer_101${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/open.gl.stencil_buffer_101/"
)



add_custom_command(
   TARGET tutorial02_red_triangle POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial02_red_triangle${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial02_red_triangle/"
)
add_custom_command(
   TARGET tutorial03_matrices POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial03_matrices${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial03_matrices/"
)
add_custom_command(
   TARGET tutorial04_colored_cube POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial04_colored_cube${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial04_colored_cube/"
)
add_custom_command(
   TARGET tutorial05_textured_cube POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial05_textured_cube${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial05_textured_cube/"
)
add_custom_command(
   TARGET tutorial06_keyboard_and_mouse POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial06_keyboard_and_mouse${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial06_keyboard_and_mouse/"
)
add_custom_command(
   TARGET tutorial07_model_loading POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial07_model_loading${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial07_model_loading/"
)
add_custom_command(
   TARGET tutorial08_basic_shading POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial08_basic_shading${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial08_basic_shading/"
)
add_custom_command(
   TARGET tutorial09_vbo_indexing POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial09_vbo_indexing${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial09_vbo_indexing/"
)
add_custom_command(
   TARGET tutorial09_AssImp POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial09_AssImp${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial09_vbo_indexing/"
)
add_custom_command(
   TARGET tutorial09_several_objects POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial09_several_objects${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial09_vbo_indexing/"
)
add_custom_command(
   TARGET tutorial10_transparency POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial10_transparency${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial10_transparency/"
)
add_custom_command(
   TARGET tutorial11_2d_fonts POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial11_2d_fonts${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial11_2d_fonts/"
)
add_custom_command(
   TARGET tutorial12_extensions POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial12_extensions${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial12_extensions/"
)
add_custom_command(
   TARGET tutorial13_normal_mapping POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial13_normal_mapping${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial13_normal_mapping/"
)
add_custom_command(
   TARGET tutorial14_render_to_texture POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial14_render_to_texture${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial14_render_to_texture/"
)
 add_custom_command(
   TARGET tutorial15_lightmaps POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial15_lightmaps${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial15_lightmaps/"
)
add_custom_command(
   TARGET tutorial16_shadowmaps_simple POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial16_shadowmaps_simple${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial16_shadowmaps/"
)
add_custom_command(
   TARGET tutorial16_shadowmaps POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial16_shadowmaps${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial16_shadowmaps/"
)
add_custom_command(
   TARGET tutorial17_rotations POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial17_rotations${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial17_rotations/"
)
add_custom_command(
   TARGET tutorial18_billboards POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial18_billboards${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial18_billboards_and_particles/"
)
add_custom_command(
   TARGET tutorial18_particles POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial18_particles${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial18_billboards_and_particles/"
)
add_custom_command(
   TARGET playground POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/playground${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/playground/"
)
add_custom_command(
   TARGET misc05_picking_slow_easy POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/misc05_picking_slow_easy${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/misc05_picking/"
)
add_custom_command(
   TARGET misc05_picking_custom POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/misc05_picking_custom${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/misc05_picking/"
)
add_custom_command(
   TARGET misc05_picking_BulletPhysics POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/misc05_picking_BulletPhysics${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/misc05_picking/"
)

elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

