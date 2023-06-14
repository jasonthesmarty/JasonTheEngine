#pragma once

#include <algorithm>
#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <shaderc/shaderc.hpp>


#define JTE_MAJOR_VERSION 0
#define JTE_MINOR_VERSION 0
#define JTE_PATCH_VERSION 1
#define JTE_LETTER_VERSION 'a'


enum JTEValidation {
	JTE_DISABLE_VALIDATION_LAYERS = 0,
	JTE_ENABLE_VALIDATION_LAYERS = 1
};

enum JTEKeys {
	JTE_KEY_UNKNOWN = -1,
	JTE_KEY_SPACE = 32,
	JTE_KEY_APOSTROPHE = 39,
	JTE_KEY_COMMA = 44,
	JTE_KEY_MINUS = 45,
	JTE_KEY_PERIOD = 46,
	JTE_KEY_SLASH = 47,

	JTE_KEY_0 = 48,
	JTE_KEY_1 = 49,
	JTE_KEY_2 = 50,
	JTE_KEY_3 = 51,
	JTE_KEY_4 = 52, 
	JTE_KEY_5 = 53,
	JTE_KEY_6 = 54,
	JTE_KEY_7 = 55,
	JTE_KEY_8 = 56,
	JTE_KEY_9 = 57,

	JTE_KEY_SEMICOLON = 59,
	JTE_KEY_EQUAL = 61,

	JTE_KEY_A = 65,
	JTE_KEY_B = 66,
	JTE_KEY_C = 67, 
	JTE_KEY_D = 68,
	JTE_KEY_E = 69,
	JTE_KEY_F = 70,
	JTE_KEY_G = 71,
	JTE_KEY_H = 72,
	JTE_KEY_I = 73,
	JTE_KEY_J = 74,
	JTE_KEY_K = 75, 
	JTE_KEY_L = 76,
	JTE_KEY_M = 77,
	JTE_KEY_N = 78,
	JTE_KEY_O = 79,
	JTE_KEY_P = 80,
	JTE_KEY_Q = 81,
	JTE_KEY_R = 82,
	JTE_KEY_S = 83,
	JTE_KEY_T = 84,
	JTE_KEY_U = 85,
	JTE_KEY_V = 86,
	JTE_KEY_W = 87,
	JTE_KEY_X = 88,
	JTE_KEY_Y = 89,
	JTE_KEY_Z = 90,

	JTE_KEY_LEFT_BRACKET = 91,
	JTE_KEY_BACKSLASH = 92,
	JTE_KEY_RIGHT_BRACKET = 92,
	JTE_KEY_GRAVE = 96,
	JTE_KEY_ESCAPE = 256,
	JTE_KEY_ENTER = 257,
	JTE_KEY_TAB = 258,
	JTE_KEY_BACKSPACE = 259,
	JTE_KEY_INSERT = 260,
	JTE_KEY_DELETE = 261,
	JTE_KEY_RIGHT = 262,
	JTE_KEY_LEFT = 263,
	JTE_KEY_DOWN = 264,
	JTE_KEY_UP = 265,
	JTE_KEY_PAGE_UP = 266,
	JTE_KEY_PAGE_DOWN = 267,
	JTE_KEY_HOME = 268,
	JTE_KEY_END = 269,
	JTE_KEY_CAPS_LOCK = 280,
	JTE_KEY_SCROLL_LOCK = 281,
	JTE_KEY_NUM_LOCK = 282,
	JTE_KEY_PRINT_SCREEN = 283,
	JTE_KEY_PAUSE = 284,

	JTE_KEY_F1 = 290,
	JTE_KEY_F2 = 291,
	JTE_KEY_F3 = 292,
	JTE_KEY_F4 = 293,
	JTE_KEY_F5 = 294,
	JTE_KEY_F6 = 295,
	JTE_KEY_F7 = 296,
	JTE_KEY_F8 = 297,
	JTE_KEY_F9 = 298,
	JTE_KEY_F10 = 299,
	JTE_KEY_F11 = 300,
	JTE_KEY_F12 = 301, 
	JTE_KEY_F13 = 302,
	JTE_KEY_F14 = 303,
	JTE_KEY_F15 = 304,
	JTE_KEY_F16 = 305,
	JTE_KEY_F17 = 306,
	JTE_KEY_F18 = 307,
	JTE_KEY_F19 = 308,
	JTE_KEY_F20 = 309,
	JTE_KEY_F21 = 310,
	JTE_KEY_F22 = 311,
	JTE_KEY_F23 = 312,
	JTE_KEY_F24 = 313,
	JTE_KEY_F25 = 314,

	JTE_KEY_KP_0 = 320,
	JTE_KEY_KP_1 = 321,
	JTE_KEY_KP_2 = 322,
	JTE_KEY_KP_3 = 323,
	JTE_KEY_KP_4 = 324,
	JTE_KEY_KP_5 = 325,
	JTE_KEY_KP_6 = 326,
	JTE_KEY_KP_7 = 327,
	JTE_KEY_KP_8 = 328,
	JTE_KEY_KP_9 = 329,

	JTE_KEY_KP_DECIMAL = 330,
	JTE_KEY_KP_DIVIDE = 331,
	JTE_KEY_KP_MULTIPLY = 332,
	JTE_KEY_KP_SUBTRACT = 333,
	JTE_KEY_KP_ADD = 334,
	JTE_KEY_KP_ENTER = 335,
	JTE_KEY_KP_EQUAL = 336,
	JTE_KEY_LEFT_SHIFT = 340,
	JTE_KEY_LEFT_CONTROL = 341,
	JTE_KEY_LEFT_ALT = 342,
	JTE_KEY_LEFT_SUPER = 343,
	JTE_KEY_RIGHT_SHIFT = 344,
	JTE_KEY_RIGHT_CONTROL = 345,
	JTE_KEY_RIGHT_ALT = 346,
	JTE_KEY_RIGHT_SUPER = 347,
	JTE_KEY_MENU = 348
};


typedef int JTEint;
typedef uint32_t JTEuint;
typedef char JTEchar;
typedef const char* JTEchars;
typedef bool JTEboolean;
typedef long JTElong;
typedef double JTEdouble;
typedef float JTEfloat;


constexpr JTEuint JTE_RED_RGBA[4] = { 255, 0, 0, 255 };
constexpr JTEuint JTE_ORANGE_RGBA[4] = { 255, 165, 0, 255 }; 
constexpr JTEuint JTE_YELLOW_RGBA[4] = { 255, 255, 0, 255 };
constexpr JTEuint JTE_GREEN_RGBA[4] = { 0, 255, 0, 255 };
constexpr JTEuint JTE_BLUE_RGBA[4] = { 0, 0, 255, 255 };
constexpr JTEuint JTE_PURPLE_RGBA[4] = { 128, 0, 128, 255 };
constexpr JTEuint JTE_PINK_RGBA[4] = { 255, 192, 203, 255 };
constexpr JTEuint JTE_BROWN_RGBA[4] = { 150, 75, 0, 255 };
constexpr JTEuint JTE_WHITE_RGBA[4] = { 255, 255, 255, 255 };
constexpr JTEuint JTE_GRAY_RGBA[4] = { 127, 127, 127, 255 };
constexpr JTEuint JTE_BLACK_RGBA[4] = { 0, 0, 0, 255 };


namespace JTEEngine {

	namespace JTEVulkan {

		class JTEVulkanInstance;
		class JTEVulkanSurface;
		class JTEVulkanLogicalDevice;
		class JTEVulkanSwapchain;
		class JTEVulkanImageViews;
		class JTEVulkanRenderPass;
		class JTEVulkanGraphicsPipeline;
		class JTEVulkanFramebuffers;
		class JTEVulkanCommandBuffers;
		class JTEVulkanSemaphoreFence;

	}

	struct JTEVulkanObjects {

		JTEVulkan::JTEVulkanInstance& instance;
		JTEVulkan::JTEVulkanSurface& surface;
		JTEVulkan::JTEVulkanLogicalDevice& device;
		JTEVulkan::JTEVulkanSwapchain& swapchain;
		JTEVulkan::JTEVulkanImageViews& imageviews;
		JTEVulkan::JTEVulkanRenderPass& renderpass;
		JTEVulkan::JTEVulkanGraphicsPipeline& graphicspipeline;
		JTEVulkan::JTEVulkanFramebuffers& framebuffers;
		JTEVulkan::JTEVulkanCommandBuffers& commandbuffers;
		JTEVulkan::JTEVulkanSemaphoreFence& semaphorefence;

	};

	/**
	* @brief This allows for the creation and manipulation of a window.
	*
	* This is the foundation of a program. Everything that will be seen and rendered will be shown on this window.
	*
	* @since Added in 0.0.1a
	*/
	class JTEWindow {
	private:

		JTEuint m_Width, m_Height;
		JTEchars m_Title;

		JTEuint m_Frames;
		JTEdouble m_CurrentTime;
		JTEdouble m_PreviousTime = glfwGetTime();

		GLFWwindow* m_Window;

		JTEboolean m_FramebufferResized = false;

		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

	public:

		/**
		* @brief An empty constructor for JTEWindow.
		*
		* This is not for constructing a window because it doesn't define the width, height, and title for the window.
		* It is for declaring variables.
		*
		* @since Added in 0.0.1a
		*/
		JTEWindow();

		/**
		* @brief Initializes the width, height, and title of the window.
		*
		* This doesn't actually do anything but initialize the variables. Constructing the window is in another function.
		*
		* @param width - Width of the window.
		* @param height - Height of the window.
		* @param title - Name of the window.
		*
		* @see create()
		*
		* @since Added in 0.0.1a
		*/
		JTEWindow(JTEuint width, JTEuint height, JTEchars title);

		/**
		* @brief Creates the window.
		*
		* This function is what creates the window. Make sure the function is used otherwise the window does not exist.
		* It should be used once, before the mainloop and Vulkan initialization.
		*
		* @see delete();
		*
		* @since Added in 0.0.1a
		*/
		void create();

		/**
		* @brief Updates the window.
		*
		* This updates the window and allows the window to be resized. This should be at the top of the mainloop.
		*
		* @param JVobjects - Vulkan objects from Vulkan initialization with JTEVulkan.
		*
		* @since Added in 0.0.1a
		*/
		void update(JTEVulkanObjects& JVobjects);

		/**
		* @brief Returns the FPS and the time between each frame.
		*
		* This allows for debugging and helps with the optimization proccess or just fun information to look at.
		*
		* @param *fps - Where the FPS is being returned.
		* @param *milliseconds - Where the milliseconds are being returned.
		*
		* @note If outputted into the character stream, this will reduce performace as with any other debugging element.
		* @note The frames and ms counts updates every 1/30 of a second.
		*
		* @since Added in 0.0.1a
		*/
		void clock(float* fps, float* milliseconds);

		/**
		* @brief Checks if the window is being closed.
		*
		* This used in the mainloop to tell when the loop should stop.
		*
		* @return true - If window is closing.
		* @return false - If window is not closing.
		*
		* @note Since the boolean values are flipped for the mainloop, negate the value in the main loop (i.e. !window.close())
		*
		* @since Added in 0.0.1a
		*/
		JTEboolean close();

		/**
		* @brief Destroys the window resources and terminates GLFW.
		*
		* This frees up resources and is good pratice to use this function.
		* It ensures that resources are properly freed on termination.
		*
		* @note Make sure not to put this in the mainloop.
		* @note For your reference, all terminate or destroying functions should be called outside of the mainloop unless instructed.
		*
		* @since Added in 0.0.1a
		*/
		void terminate();

		/**
		* @brief Returns the window.
		*
		* This function returns the window variable inside the class. But this is not used at all as parameters for public functions that would be used in
		* functions internal to the source code.
		*
		* @return GLFWwindow*
		*
		* @since Added in 0.0.1a
		*/
		GLFWwindow* getWindow();

		/**
		* @brief Returns the width and height of the window.
		*
		* @return std::array<JTEuint, 2> { width, height }
		*
		* @since Added in 0.0.1a
		*/
		std::array<JTEuint, 2> getWindowDimensions();

		/**
		* @brief Sets the new title of the window.
		*
		* @param title - New title to be set.
		*
		* @since Added in 0.0.1a
		*/
		void setTitle(std::string_view title);

		/**
		* @brief Sets the new width and height of the window.
		*
		* @param width - New width to be set.
		* @param height - New height to be set.
		*
		* @since Added in 0.0.1a
		*/
		void setDimensions(JTEuint width, JTEuint height);

		/**
		* @brief Sets the new opacity of the window.
		*
		* @param - New opacity to be set. (0-255)
		*
		* @note If opacity is set above 255, the window will close and produce an error.
		*
		* @since Added in 0.0.1a
		*/
		void setOpacity(JTEuint opacity);

		/**
		* @brief Sets the new x and y of the window.
		*
		* @param x - New x to be set.
		* @param y - New y to be set.
		*
		* @note These coordinates refer to the upper-left corner of the window.
		*
		* @since Added in 0.0.1a
		*/
		void setPosition(JTEuint x, JTEuint y);

	};

	/**
	* @brief This allows for the use of input for different events.
	*
	* If-statements are used to check if the specified button is pressed or not.
	*
	* @note This can only be used once as input checking are universal, even with multiple windows.
	*
	* @since Added in 0.0.1a
	*/
	class JTEInput {
	public:

		/**
		* @brief An empty constructor for JTEInput.
		*
		* Allows for the use of checking for input from mouse and keyboard.
		*
		* @note Controller controls are not supported.
		*
		* @since Added in 0.0.1a
		*/
		JTEInput();

		/**
		* @brief This is for internal use only.
		* @brief This sets the keyboard callback for the window.
		*
		* @since Added in 0.0.1a
		*/
		static GLFWkeyfun keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		/**
		* @brief This is for internal use only.
		* @brief This sets the mouse callback for the window.
		*
		* @since Added in 0.0.1a
		*/
		static GLFWmousebuttonfun mouseButtonCallback(GLFWwindow* window, int key, int action, int mods);

		/**
		* @brief This is for internal use only.
		* @brief This sets the mouse position callback for the window.
		*
		* @since Added in 0.0.1a
		*/
		static GLFWcursorposfun cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);

		/**
		* @brief This returns a value if the mouse button specified was pressed.
		*
		* This checks if it was pressed and outputs a boolean value. It outputs a repeated stream of values.
		* So if the button was only pressed for one second, it could output more than one press.
		* This happens because it is in the mainloop.
		*
		* @param key - The mouse button being checked for input.
		*
		* @return true - If the mouse button was pressed.
		* @return false - If the mouse button wasn't pressed.
		*
		* @note Toggle switches would have to be coded manually.
		*
		* @since Added in 0.0.1a
		*/
		JTEboolean keyDown(JTEuint key);

		/**
		* @brief This returns a value if the mouse button specified was pressed.
		*
		* This checks if it was pressed and outputs a boolean value. It outputs a repeated stream of values.
		* So if the button was only pressed for one second, it could output more than one press.
		* This happens because it is in the mainloop.@param key - The mouse button being checked for input.
		*
		* @return true - If the mouse button was pressed.
		* @return false - If the mouse button wasn't pressed.
		*
		* @note Toggle switches would have to be coded manually.
		*
		* @since Added in 0.0.1a
		*/
		JTEboolean mouseButtonDown(JTEuint mouseButton);

		/**
		* @brief Returns the x position of the mouse.
		*
		* This returns the absolute x value of the mouse.
		*
		* @return JTEdouble
		*
		* @note For geometry that changes position with mouse coordinates, this will cause problems with scaling.
		*
		* @since Added in 0.0.1a
		*/
		JTEdouble getMouseX();

		/**
		* @brief Returns the y position of the mouse.
		*
		* This returns the absolute y value of the mouse.
		*
		* @return JTEdouble
		*
		* @note For geometry that changes position with mouse coordinates, this will cause problems with scaling.
		*
		* @since Added in 0.0.1a
		*/
		JTEdouble getMouseY();

	};

	/**
	* @brief Utility functions for QOL.
	*
	* Shortens all lot of writing for functions that are written a lot.
	*/
	namespace JTEUtilities {

		/**
		* @brief Prints a value
		*
		* This outputs the data inputted into the character stream.
		*
		* @param value - Data to be outputted.
		*
		* @since Added in 0.0.1a
		*/
		template <typename T>
		void print(T value);

		/**
		* @brief Prints a value with a new line
		*
		* This outputs the data inputted into the character stream with a new line.
		*
		* @param value - Data to be outputted with a new line.
		*
		* @since Added in 0.0.1a
		*/
		template <typename T>
		void println(T value);

		/**
		* @brief Turns numbers into strings.
		*
		* This converts any number data type in to an std::string, not a c string.
		*
		* @param value - Value to be converted.
		*
		* @since Added in 0.0.1a
		*/
		template <typename T>
		std::string string(T value);

#include "../JTEEngine/Standard/JTEUtilities.ipp"

	}

	/**
	* @brief The rendering proccess.
	*
	* This starts, end, and submits all rendering commands.
	*
	* @note All rendering commands must be between the starting rendering command and ending command otherwise Vulkan errors are produced.
	*/
	class JTERenderer {
	private:

		JTEuint imageIndex;
		JTEuint currentFrame = 0;

		JTEuint m_MaxFramesInFlight;

	public:

		/**
		* @brief An empty constructor for JTERenderer.
		*
		* This starts and ends all recording of rendering commands.
		* After that it submits it to be rendered onto the window.
		*
		* @since Added in 0.0.1a
		*/
		JTERenderer(JTEuint maxFramesInFlight = 1);

		/**
		* @brief Starts the rendering process.
		*
		* This begins the rendering process and allows rendering commands to be recorded.
		*
		* @param JVobjects - Vulkan objects from Vulkan initialization with JTEVulkan.
		*
		* @since Added in 0.0.1a
		*/
		void start(JTEVulkanObjects& JVObjects);

		/**
		* @brief Ends the rendering process.
		*
		* After all commands are done recording, this will end the recording process.
		*
		* @param JVobjects - Vulkan objects from Vulkan initialization with JTEVulkan.
		*
		* @since Added in 0.0.1a
		*/
		void end(JTEVulkanObjects& JVObjects);

		/**
		* @brief Submits commands for rendering.
		*
		* After the recording is done. This will submit all the commands to be rendered onto the window.
		*
		* @param JVobjects - Vulkan objects from Vulkan initialization with JTEVulkan.
		*
		* @since Added in 0.0.1a
		*/
		void submit(JTEVulkanObjects& JVObjects);

		/**
		* @brief Returns the current frame in flight.
		* @brief For internal use only.
		*
		* @since Added in 0.0.1a
		*/
		JTEuint getCurrentFrame();

	};

	/**
	* @brief Renders quadrilaterals
	*
	* Allows for the rendering and manipulation of quadrilaterals.
	*
	* @since Added in 0.0.1a
	*/
	class JTEQuad {
	private:

		JTEfloat m_X, m_Y, m_Width, m_Height;
		JTEfloat m_HalfWidth, m_HalfHeight;
		std::array<JTEfloat, 4> m_Colors;

		JTEWindow JWindow;
		JTERenderer JRenderer;

		VkBuffer m_VertexBuffer;
		VkDeviceMemory m_VertexBufferMemory;
		VkBuffer m_IndexBuffer;
		VkDeviceMemory m_IndexBufferMemory;

		VkBuffer m_StagingBufferV;
		VkDeviceMemory m_StagingBufferMemoryV;
		VkBuffer m_StagingBufferI;
		VkDeviceMemory m_StagingBufferMemoryI;

		VkDeviceSize m_BufferSizeV;
		VkDeviceSize m_BufferSizeI;

		std::array<JTEfloat, 20> m_Vertices;
		std::array<uint16_t, 6> m_Indices;

	public:

		/**
		* @brief Sets the initial values for the quad to be rendered.
		*
		* Sets the position and color of the quad. Color is uniform through the whole quad because only one color is specified.
		*
		* @param x - X value of the quad anchored at the bottom-left.
		* @param y - Y value of the quad anchored at the bottom-left.
		* @param width - Width of the quad.
		* @param height - Height of the quad.
		* @param color - Color of the quad.
		* @param JVobjects - Vulkan objects from Vulkan initialization with JTEVulkan.
		* @param JVRender - The renderer being used.
		*
		* @since Added in 0.0.1a
		*/
		JTEQuad(JTEuint x, JTEuint y, JTEuint width, JTEuint height, std::array<JTEfloat, 4> color, JTEWindow& JWindow, JTEVulkanObjects& JVObjects, JTERenderer& JVRender);

		/**
		* @brief Renders the quad
		*
		* More specfically, it runs the render command to be recorded.
		*
		* @param JVobjects - Vulkan objects from Vulkan initialization with JTEVulkan.
		* @param JVRender - The renderer being used.
		*
		* @since Added in 0.0.1a
		*/
		void render(JTEVulkanObjects& JVObjects, JTERenderer& render);

		/**
		* @brief Updates the quad
		*
		* This updates the quad but is not always required. It is only required when the quad is updated during the mainloop. If it
		* stays static then this is not needed since the quad details are already calculated in the constructor.
		*
		* @param JVobjects - Vulkan objects from Vulkan initialization with JTEVulkan.
		*
		* @note Updating the quad does impact performace.
		* @note This should be ran before render() if used.
		*
		* @since Added in 0.0.1a
		*/
		void update(JTEVulkanObjects& JVObjects);

		/**
		* @brief Cleans up resources used by the quad.
		*
		* This doesn't necessarily erase the quad but cleans up the resources used to render the quad.
		* It should be used after the mainloop.
		*
		* @param JVobjects - Vulkan objects from Vulkan initialization with JTEVulkan.
		*
		* @since Added in 0.0.1a
		*/
		void erase(JTEVulkanObjects& JVObjects);

		/**
		* @brief Gets the bottom left x coordinate of the quad.
		* 
		* @return JTEuint
		*
		* @since Added in 0.0.1a
		*/
		JTEint getX();

		/**
		* @brief Gets the bottom left y coordinate of the quad.
		*
		* @return JTEuint
		*
		* @since Added in 0.0.1a
		*/
		JTEint getY();

		/**
		* @brief Gets the width of the quad.
		*
		* @return JTEuint
		*
		* @since Added in 0.0.1a
		*/
		JTEint getWidth();

		/**
		* @brief Gets the height of the quad.
		*
		* @return JTEuint
		*
		* @since Added in 0.0.1a
		*/
		JTEint getHeight();

		/**
		* @brief Sets the new bottom left x coordinate of the quad.
		*
		* @param x - The new x value.
		*
		* @since Added in 0.0.1a
		*/
		void setX(JTEint x);

		/**
		* @brief Sets the new bottom left y coordinate of the quad.
		*
		* @param y - The new y value.
		*
		* @since Added in 0.0.1a
		*/
		void setY(JTEint y);

		/**
		* @brief Sets the new width of the quad.
		*
		* @param width - The new width value.
		*
		* @since Added in 0.0.1a
		*/
		void setWidth(JTEint width);

		/**
		* @brief Sets the new height of the quad.
		*
		* @param height - The new height value.
		*
		* @since Added in 0.0.1a
		*/
		void setHeight(JTEint height);

	};
	
	namespace JTEVulkan {

		const std::vector<JTEchars> validationLayers = {
			"VK_LAYER_KHRONOS_validation"
		};

		const std::vector<JTEchars> deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		class JTEVulkanUtils {
		public:

			struct QueueFamilyIndices {
				std::optional<JTEuint> graphicsFamily;
				std::optional<JTEuint> presentFamily;

				bool isComplete() {
					return graphicsFamily.has_value() && presentFamily.has_value();
				}
			};

			struct SwapChainSupportDetails {
				VkSurfaceCapabilitiesKHR capabilities;
				std::vector<VkSurfaceFormatKHR> formats;
				std::vector<VkPresentModeKHR> presentModes;
			};

			// Not actually used, I just use a normal array.
			// But the static functions are used because I'm too lazy too move them.
			struct Vertex {
				glm::vec2 pos;
				glm::vec3 color;
				static VkVertexInputBindingDescription getBindingDescription() {
					VkVertexInputBindingDescription bindingDescription{};
					bindingDescription.binding = 0;
					bindingDescription.stride = sizeof(Vertex);
					bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
					return bindingDescription;
				}
				static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
					std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
					attributeDescriptions[0].binding = 0;
					attributeDescriptions[0].location = 0;
					attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
					attributeDescriptions[0].offset = offsetof(Vertex, pos);
					attributeDescriptions[1].binding = 0;
					attributeDescriptions[1].location = 1;
					attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
					attributeDescriptions[1].offset = offsetof(Vertex, color);
					return attributeDescriptions;
				}
			};

			static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
			static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
			static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
			static bool checkValidationLayerSupport();
			static std::vector<JTEchars> getRequiredExtensions(JTEboolean enableValidationLayers);
			static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
			static bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);
			static bool checkDeviceExtensionSupport(VkPhysicalDevice device);
			static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
			static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
			static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormat);
			static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
			static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);
			static VkShaderModule createShaderModule(VkDevice device, JTEchars shaderCode, JTEchars successMessage, JTEchars failureMessage, shaderc_shader_kind option);
			static void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory, VkDevice device, VkPhysicalDevice physicalDevice);
			static void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VkCommandPool commandPool, VkDevice device, VkQueue graphicsQueue);
			static JTEuint findMemoryType(JTEuint typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice physicalDevice);
		};

		/**
		* @brief Creates an instance for Vulkan.
		*
		* Verifies all Vulkan layers and extensions that are used are also available.
		*
		* @since Added in 0.0.1a
		*/
		class JTEVulkanInstance {
		private:

			VkInstance m_Instance;
			JTEchars m_ApplicationName = "Application Name";
			JTEint m_MajorVersion = 0, m_MinorVersion = 0, m_Patch = 0;

			JTEboolean m_EnableValidationLayers;

		public:

			JTEVulkanInstance();
			JTEVulkanInstance(JTEchars applicationName, JTEint majorVersion, JTEint minorVersion, JTEint patch, JTEboolean enableValidationLayers = JTE_DISABLE_VALIDATION_LAYERS);
			void createVulkanInstance();
			void terminateVulkanInstance();

			VkInstance getVulkanInstance();

		};

		/**
		* @brief Creates validation layers for Vulkan.
		*
		* Creates a debug message systeam. Can be turned off and on.
		*
		* @since Added in 0.0.1a
		*/
		class JTEVulkanValidationLayers {
		private:

			VkDebugUtilsMessengerEXT m_DebugMessenger;

			JTEboolean m_EnableValidationLayers;

			JTEVulkanInstance m_JVinstance;

		public:

			JTEVulkanValidationLayers();
			JTEVulkanValidationLayers(const JTEVulkanInstance& JVinstance, JTEboolean enableValidationLayers = JTE_DISABLE_VALIDATION_LAYERS);
			void createVulkanValidationLayers();
			void terminateVulkanValidationLayers();

		};

		/**
		* @brief Creates a surface for Vulkan.
		*
		* Creates the place where graphics can be rendered.
		*
		* @since Added in 0.0.1a
		*/
		class JTEVulkanSurface {
		private:

			VkSurfaceKHR m_Surface;

			JTEVulkanInstance m_JVinstance;
			JTEWindow m_JVwindow;

		public:

			JTEVulkanSurface();
			JTEVulkanSurface(const JTEVulkanInstance& JVinstance, const JTEWindow& Jwindow);
			void createVulkanSurface();
			void terminateVulkanSurface();

			VkSurfaceKHR getVulkanSurface();

		};

		/**
		* @brief Picks a device and creates a logical device for Vulkan.
		*
		* Picks a GPU for rendering and managing resources for graphics. It is an intermediary for the GPU and the program.
		*
		* @since Added in 0.0.1a
		*/
		class JTEVulkanLogicalDevice {
		private:

			VkPhysicalDevice m_PhysicalDevice;
			VkDevice m_LogicalDevice;
			VkQueue m_GraphicsQueue;
			VkQueue m_PresentQueue;

			JTEVulkanInstance m_JVinstance;
			JTEVulkanSurface m_JVsurface;

			JTEboolean m_EnableValidationLayers;

		public:

			JTEVulkanLogicalDevice();
			JTEVulkanLogicalDevice(const JTEVulkanInstance& JVinstance, const JTEVulkanSurface& JVsurface, JTEboolean enableValidationLayers = JTE_DISABLE_VALIDATION_LAYERS);
			void createVulkanLogicalDevice();
			void terminateVulkanLogicalDevice();

			VkPhysicalDevice getVulkanPhysicalDevice();
			VkDevice getVulkanLogicalDevice();
			VkQueue getVulkanGraphicsQueue();
			VkQueue getVulkanPresentQueue();

		};

		/**
		* @brief Creates a swapchain for Vulkan.
		*
		* Used to present images onto the window.
		*
		* @since Added in 0.0.1a
		*/
		class JTEVulkanSwapchain {
		private:

			VkSwapchainKHR m_Swapchain;
			std::vector<VkImage> m_SwapChainImages;
			VkExtent2D m_SwapChainExtent;
			VkFormat m_SwapChainImageFormat;

			JTEVulkanLogicalDevice m_JVdevice;
			JTEVulkanSurface m_JVsurface;
			JTEWindow m_JVwindow;

		public:

			JTEVulkanSwapchain();
			JTEVulkanSwapchain(const JTEVulkanLogicalDevice& JVdevice, const JTEVulkanSurface& JVsurface, const JTEWindow& Jwindow);
			void createVulkanSwapchain();
			void terminateVulkanSwapchain();

			VkSwapchainKHR getVulkanSwapchain();
			std::vector<VkImage> getVulkanSwapChainImages();
			VkExtent2D getVulkanSwapChainExtent();
			VkFormat getVulkanSwapChainImageFormat();

		};

		/**
		* @brief Creates image views for Vulkan.
		*
		* It is used to interpret image data in images loaded into Vulkan.
		*
		* @since Added in 0.0.1a
		*/
		class JTEVulkanImageViews {
		private:

			std::vector<VkImageView> m_SwapChainImageViews;

			JTEVulkanSwapchain m_JVswapchain;
			JTEVulkanLogicalDevice m_JVdevice;

		public:

			JTEVulkanImageViews();
			JTEVulkanImageViews(const JTEVulkanLogicalDevice& JVdevice, const JTEVulkanSwapchain& JVswapchain);
			void creatVulkanImageViews();
			void terminateVulkanImageViews();

			std::vector<VkImageView> getVulkanSwapChainImageViews();
			void updateSwapchain(const JTEVulkanSwapchain& swpchain);

		};

		/**
		* @brief Creates a renderpass for Vulkan.
		*
		* Defines the rendering operations that happen on images being rendered.
		*
		* @since Added in 0.0.1a
		*/
		class JTEVulkanRenderPass {
		private:

			VkRenderPass m_RenderPass;

			JTEVulkanLogicalDevice m_JVdevice;
			JTEVulkanSwapchain m_JVswapchain;

		public:

			JTEVulkanRenderPass();
			JTEVulkanRenderPass(const JTEVulkanLogicalDevice& JVdevice, const JTEVulkanSwapchain& JVswapchain);
			void createVulkanRenderPass();
			void terminateVulkanRenderPass();

			VkRenderPass getVulkanRenderPass();

		};

		/**
		* @brief Creates a graphics pipeline for Vulkan.
		*
		* Used to transform vertex data and rasterize it with post processing.
		*
		* @since Added in 0.0.1a
		*/
		class JTEVulkanGraphicsPipeline {
		private:

			VkPipelineLayout m_PipelineLayout;
			VkPipeline m_GraphicsPipeline;

			JTEVulkanLogicalDevice m_JVdevice;
			JTEVulkanRenderPass m_JVrenderpass;

		public:

			JTEVulkanGraphicsPipeline();
			JTEVulkanGraphicsPipeline(const JTEVulkanLogicalDevice& JVdevice, const JTEVulkanRenderPass& JVrenderpass);
			void createVulkanGraphicsPipeline();
			void terminateVulkanGraphicsPipeline();

			VkPipelineLayout getVulkanPipelineLayout();
			VkPipeline getVulkanGraphicsPipeline();

		};

		/**
		* @brief Creates framebuffers for Vulkan.
		*
		* Defines targets to be rendered onto the window.
		*
		* @since Added in 0.0.1a
		*/
		class JTEVulkanFramebuffers {
		private:

			std::vector<VkFramebuffer> m_SwapChainFramebuffers;

			JTEVulkanLogicalDevice m_JVdevice;
			JTEVulkanSwapchain m_JVswapchain;
			JTEVulkanRenderPass m_JVrenderpass;
			JTEVulkanImageViews m_JVimageviews;

		public:

			JTEVulkanFramebuffers();
			JTEVulkanFramebuffers(const JTEVulkanLogicalDevice& JVdevice, const JTEVulkanSwapchain& JVswapchain, const JTEVulkanRenderPass& JVrenderpass, const JTEVulkanImageViews& JVimageviews);
			void createVulkanFramebuffers();
			void terminateVulkanFramebuffers();

			std::vector<VkFramebuffer> getVulkanSwapChainFramebuffers();
			void updateSwapchainAndImageViews(const JTEVulkanSwapchain& JVswapchain, const JTEVulkanImageViews& JVimageviews);

		};

		/**
		* @brief Creates command buffers for Vulkan.
		*
		* Holds the commands being recorded to be executed.
		*
		* @since Added in 0.0.1a
		*/
		class JTEVulkanCommandBuffers {
		private:

			VkCommandPool m_CommandPool;
			std::vector<VkCommandBuffer> m_CommandBuffers;

			JTEVulkanLogicalDevice m_JVdevice;
			JTEVulkanSurface m_JVsurface;

			JTEuint m_MaxFramesInFlight;

		public:

			JTEVulkanCommandBuffers();
			JTEVulkanCommandBuffers(const JTEVulkanLogicalDevice& JVdevice, const JTEVulkanSurface& JVsurface, JTEuint maxFramesInFlight = 1);
			void createVulkanCommandBuffers();
			void terminateVulkanCommandBuffers();

			VkCommandPool getVulkanCommandPool();
			std::vector<VkCommandBuffer> getVulkanCommandBuffers();

		};

		/**
		* @brief Creates semaphores and a fence for Vulkan.
		*
		* Used to synchronize rendering.
		*
		* @since Added in 0.0.1a
		*/
		class JTEVulkanSemaphoreFence {
		private:

			std::vector<VkSemaphore> m_ImageAvailableSemaphores;
			std::vector<VkSemaphore> m_RenderFinishedSemaphores;
			std::vector<VkFence> m_InFlightFences;

			JTEVulkanLogicalDevice m_JVdevice;

			JTEuint m_MaxFramesInFlight;

		public:

			JTEVulkanSemaphoreFence();
			JTEVulkanSemaphoreFence(const JTEVulkanLogicalDevice& JVdevice, JTEuint maxFramesInFlight = 1);
			void createVulkanSemaphoreFence();
			void terminateVulkanSemaphoreFence();

			std::vector<VkSemaphore> getVulkanRenderFinishedSemaphore();
			std::vector<VkSemaphore> getVulkanImageAvailableSemaphore();
			std::vector<VkFence> getVulkanInFlightFence();

		};

	};

}