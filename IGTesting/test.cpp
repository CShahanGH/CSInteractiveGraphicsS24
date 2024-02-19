#include "pch.h"
#include "..\CSInteractiveGraphicsS24\Texture.h"
#include <Windows.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

namespace igtesting
{
	bool SetUpGraphics()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(100, 100, "Testing", NULL, NULL);
		if (window == nullptr)
		{
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent(window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			glfwTerminate();
			return false;
		}
		return true;
	}

	TEST(Atexture, ShouldInitializeItsTextureID)
	{
		EXPECT_TRUE(SetUpGraphics());
		Texture sut;
		EXPECT_TRUE(sut.GetTextureID() != 0);
		glfwTerminate();
	}
	TEST(ATexture, CanSetTheTextureData)
	{
		Texture sut;
		unsigned char data[] = { 255, 255, 255, 255 };
		sut.setTextureData(4, data);
		EXPECT_TRUE(sut.GetTextureData() != nullptr);
		EXPECT_TRUE(sut.IsLoadedFromFile() == false);
	}

	TEST(ATexture, HasNullTextureDataWhenCreated)
	{
		Texture sut;
		EXPECT_TRUE(sut.GetTextureData() == nullptr);
	}

	
}