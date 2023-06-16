# JasonTheEngine

To use this library   
Make sure to have these libraries:

- GLFW
- Vulkan
- GLM
- ShaderC

---

Future Libs that will be used

- STB
- Freetype

---

I personally use **vcpkg** with can directly integrate into Microsoft Visual Studio which is very handy.   
Manual linking works but that can be messy real quick...   
What I have find out is that packaging a product might require glfw3.dll and the vulkan-1.dll packaged.   
(Or whatever the dll names they are for those libs)  
I have no idea if that is true though... that's just the errors I saw when running it on a Windows 10 VM.  

---

With Vcpkg

***All commands in quotes and italicized are ran in either Command Prompt or Powershell.

1. Make sure to first be in the directory you want to download vcpkg. (i.e. C/: using "*cd /*")
2. Run "*git clone https://github.com/microsoft/vcpkg.git*" (Which assumes that you have git installed...)
3. Enter into the directory "*cd vcpkg*"
4. Run "*bootstrap-vcpkg.bat*"   Now vckpkg is set up and the next steps are the dependencies
5. GLFW: "*vcpkg install gflw3:x64-windows*"
6. Vulkan: "*vcpkg install vulkan:x64-windows*"   Note that it will prompt you to manually link Vulkan, this command only intalls a stub. To find the actuall lib download, go to https://vulkan.lunarg.com/    
Steps 7 and 8 are optional depending on how you install Vulkan because they can come with these things.
7. GLM: "*vcpkg install glm:x64-windows*"
8. ShaderC: "*vcpkg install shaderc:x64-windows*"
9. To link with MSVS run "*vcpkg integrate install*"

After all of that everything should run smooth as long as you link the JasonTheEngine.libs correctly






