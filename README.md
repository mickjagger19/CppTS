# CppTS

C++ technology stack

# Compiling

1. Windows

	Use Visual Studio 2019:

	```
	<cmake-directory>\cmake ../CppTS -G "Visual Studio 16" -A x64
	MSBuild ALL_BUILD.vcxproj /t:build /p:Configuration=Debug
	```
	
	```
	<cmake-directory>\cmake ../CppTS -G "Visual Studio 16" -A x64
	MSBuild ALL_BUILD.vcxproj /t:build /p:Configuration=Release
	```

1. Linux

	Use Ubuntu 19.04:

	```
	<cmake-directory>/cmake ../CppTS -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"
	make
	```

	```
	<cmake-directory>/cmake ../CppTS -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles"
	make
	```
