#include "mdi.h"
#include "roboto_regular.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


static void SetDockspace( MDI *mdi );
static void SetTitlebar( MDI *mdi, const ImGuiViewport *viewport );


MDI_STATE MDI_Init( MDI *mdi )
{
	if( !glfwInit() )
	{
		mdi->state = MDI_STATE_INIT_GLFW_ERROR;
		return mdi->state;
	}

	mdi->glslVersion = "#version 130";
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );

	mdi->window = glfwCreateWindow( 2000, 1200, "Dear ImGui", NULL, NULL );
	if( mdi->window == NULL )
	{
		mdi->state = MDI_STATE_INIT_GLFW_ERROR;
		return mdi->state;
	}

	glfwMakeContextCurrent( mdi->window );
	glfwSwapInterval( 1 ); 									// Enable vsync



	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;	// Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		// Enable Docking

	ImGui::StyleColorsDark();


	ImGui_ImplGlfw_InitForOpenGL( mdi->window, true );
	ImGui_ImplOpenGL3_Init( mdi->glslVersion );

	mdi->fontConfig.FontDataOwnedByAtlas = false;
	mdi->robotoFont = io.Fonts->AddFontFromMemoryTTF( (void*)Font_RobotoRegular, sizeof(Font_RobotoRegular), 2.0f * 16.0f, &mdi->fontConfig );
	IM_ASSERT( mdi->robotoFont != nullptr );
	io.FontDefault = mdi->robotoFont;

	mdi->state = MDI_STATE_INIT_OK;
	return mdi->state;
}

MDI_STATE MDI_Deinit( MDI *mdi )
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow( mdi->window );
	glfwTerminate();

	return MDI_STATE_NONE;
}

MDI_STATE MDI_Show( MDI *mdi )
{
	if( mdi->state != MDI_STATE_INIT_OK )
	{
		return mdi->state;
	}

	mdi->state = MDI_STATE_SHOW;

	ImVec4 bgColor = ImVec4( 0.133f, 0.149f, 0.165f, 1.00f );
	int display_w;
	int display_h;

	while( !glfwWindowShouldClose( mdi->window ) )
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// ---

		SetDockspace( mdi );

#if 0
		if( ImGui::Begin( "Lib", nullptr, ImGuiWindowFlags_None ) )
		{
			coreDiagram->DrawLibrary();
			ImGui::End();
		}

		if( ImGui::Begin( "Diagram", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse ) )
		{
			coreDiagram->Update();
			ImGui::End();
		}

		if( ImGui::Begin( "Properties", nullptr, ImGuiWindowFlags_None ) )
		{
			coreDiagram->DrawProperties();
			ImGui::End();
		}

		coreDiagram->DrawTooltip();
#endif

		// ---

		ImGui::Render();

		glfwGetFramebufferSize( mdi->window, &display_w, &display_h );

		glViewport( 0, 0, display_w, display_h );
		glClearColor( bgColor.x, bgColor.y, bgColor.z, bgColor.w );
		glClear( GL_COLOR_BUFFER_BIT );

		ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );

#if 0
		if( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
#endif

		glfwSwapBuffers( mdi->window );
	}

	return MDI_STATE_SHUTDOWN;
}


static void SetDockspace( MDI *mdi )
{
	const ImGuiViewport *viewport = ImGui::GetMainViewport();

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar 				|
									ImGuiWindowFlags_NoDocking 				|
									ImGuiWindowFlags_NoTitleBar 			|
									ImGuiWindowFlags_NoCollapse 			|
									ImGuiWindowFlags_NoResize 				|
									ImGuiWindowFlags_NoMove 				|
									ImGuiWindowFlags_NoBringToFrontOnFocus 	|
									ImGuiWindowFlags_NoNavFocus;

	ImGui::SetNextWindowPos( viewport->Pos );
	ImGui::SetNextWindowSize( viewport->Size );
	ImGui::SetNextWindowViewport( viewport->ID );
	ImGui::SetNextWindowBgAlpha( 0.0f );

	ImGui::PushStyleVar( ImGuiStyleVar_WindowRounding, 0.0f );
	ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 0.0f );
	ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( 0.0f, 0.0f ) );

	ImGui::Begin( "DockSpace", nullptr, window_flags );
	
	ImGui::PopStyleVar( 3 );

#if 0
	if (ImGui::DockBuilderGetNode(ImGui::GetID("DockSpaceNode")) == nullptr || redock)
	{
		redock = false;
		ImGuiID dockspace_id = ImGui::GetID("DockSpaceNode");
		ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout
		ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace); // Add empty node
		ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

		ImGuiID dock_main_id = dockspace_id;
		ImGuiID dock_id_left_top = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, nullptr, &dock_main_id);
		ImGuiID dock_id_left_bottom = ImGui::DockBuilderSplitNode(dock_id_left_top, ImGuiDir_Down, 0.60f, nullptr, &dock_id_left_top);

		ImGui::DockBuilderDockWindow("Simulation", dock_id_left_top);
		ImGui::DockBuilderDockWindow("Library", dock_id_left_top);
		ImGui::DockBuilderDockWindow("Diagram", dock_main_id);
		ImGui::DockBuilderDockWindow("Properties", dock_id_left_bottom);
		ImGui::DockBuilderDockWindow("Explorer", dock_id_left_bottom);
		ImGui::DockBuilderFinish(dockspace_id);
	}
#endif

	ImGuiID dockspace_id = ImGui::GetID( "DockSpaceNode" );
	ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

	ImGui::DockSpace( dockspace_id, ImVec2( 0.0f, 0.0f ), dockspace_flags );

	SetTitlebar( mdi, viewport );

	ImGui::End();
}

static void SetTitlebar( MDI *mdi, const ImGuiViewport *viewport )
{
	if( ImGui::BeginMainMenuBar() )
	{
		if( ImGui::BeginMenu( "File" ) )
		{
			if( ImGui::MenuItem( "Exit" ) )
			{
				glfwSetWindowShouldClose( mdi->window, GLFW_TRUE );
			}
			ImGui::EndMenu();
		}

		if( ImGui::BeginMenu( "Edit" ) )
		{
			ImGui::EndMenu();
		}

		if( ImGui::BeginMenu( "Help" ) )
		{
			ImGui::EndMenu();
		}


		const char *titlebarText = "Hallo Welt";
		float curPos = viewport->WorkSize.x - ImGui::GetCursorPosX();
		float textSizeX = ImGui::CalcTextSize( titlebarText ).x;

		ImGui::SetCursorPosX( (curPos / 2.0f) - (textSizeX / 2.0f) );
		ImGui::Text( "%s", titlebarText );

		ImGui::EndMainMenuBar();
	}
}