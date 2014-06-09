kbengine_ogre_demo
=============

##Homepage:
http://www.kbengine.org

##Releases
	binarys		: https://sourceforge.net/projects/kbengine/files/


##Build:

	Linux:

		nonsupport.

	Windows:

		1. Download and install OGRE-1.8.1 SDK, (http://www.ogre3d.org/download/sdk).
			Decompression to kbengine_ogre_demo\ogresdk\*.
			Set environment variables: OGRE_HOME = **\kbengine_ogre_demo\ogresdk

		2. Download and install Microsoft DirectX SDK 9.0, (http://www.microsoft.com/en-hk/download/details.aspx?id=6812).

		3. Download kbengine-xxx.zip, (https://github.com/kbengine/kbengine/releases/latest).
			Decompression(kbengine-xxx.zip\kbengine-xxx\*) to kbengine_ogre_demo\kbengine\*.
			Covering all the directories and files.

		4. Microsoft Visual Studio-> kbengine_ogre_demo\kbengine\kbe\src\kbengine_vs90.sln -> build.
		
		5. Microsoft Visual Studio-> kbengine_ogre_demo\kbengine\kbe\src\client\ogre\client_for_ogre_vc90.sln -> build.
##Startup:

	Linux:

		nonsupport.

	Windows:

		kbengine\kbe\src\client\ogre\!start.bat.
