#ifndef __MDI_H__
#define __MDI_H__


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


MDI_STATE MDI_Init( MDI *mdi );
MDI_STATE MDI_Deinit( MDI *mdi );
MDI_STATE MDI_Show( MDI *mdi );


#endif//__MDI_H__