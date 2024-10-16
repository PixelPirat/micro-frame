#ifndef __MDI_HPP__
#define __MDI_HPP__


#include <imgui.h>
#include <GLFW/glfw3.h>


typedef enum
{
	MDI_STATE_NONE,
	MDI_STATE_INIT_GLFW_ERROR,
	MDI_STATE_INIT_IMGUI_ERROR,
	MDI_STATE_INIT_OK,
	MDI_STATE_SHOW,
	MDI_STATE_SHUTDOWN,
	MDI_STATE_DEINIT_ERROR,
	MDI_STATE_DEINIT_OK,
} MDI_STATE;


typedef struct {
	GLFWwindow 	*window;
	ImFont 		*robotoFont;
	ImFontConfig fontConfig;

	const char 	*glslVersion;

	MDI_STATE 	 state;
} MDI;


MDI_STATE mdi_init( MDI *mdi );
MDI_STATE mdi_deinit( MDI *mdi );
MDI_STATE mdi_show( MDI *mdi );


#endif//__MDI_HPP__