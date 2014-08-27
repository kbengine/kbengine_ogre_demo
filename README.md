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

		1. Download and install OGRE 1.8.1 SDK for Visual C++ 2010 (32-bit), (http://www.ogre3d.org/download/sdk).
			Decompression to kbengine_ogre_demo\ogresdk\*.
			Set environment variables: OGRE_HOME = **\kbengine_ogre_demo\ogresdk

		2. Download and install Microsoft DirectX SDK 9.0, (http://www.microsoft.com/en-hk/download/details.aspx?id=6812).

		3. Download kbengine-xxx.zip, (https://github.com/kbengine/kbengine/releases/latest).
			Decompression(kbengine-xxx.zip\kbengine-xxx\*) to kbengine_ogre_demo\kbengine\*.
			Covering all the directories and files.

		4. Microsoft Visual Studio-> kbengine_ogre_demo\kbengine\kbe\src\kbengine_vs90.sln -> build.
		
		5. Microsoft Visual Studio-> kbengine_ogre_demo\kbengine\kbe\src\client\ogre\client_for_ogre_vc90.sln -> build.

		6. Copy Ogre-dlls to client.
			kbengine_ogre_demo\ogre3d\bin\debug\*.dll to kbengine_ogre_demo\kbengine\kbe\bin\client\
			kbengine_ogre_demo\ogre3d\bin\release\*.dll to kbengine_ogre_demo\kbengine\kbe\bin\client\


##Start the servers:

	Linux:
			http://www.kbengine.org/docs/startup_shutdown.html


	Windows:
			kbengine_ogre_demo\kbengine\kbe\bin\Hybrid\!(win)fixedstart.bat.
			also see: http://www.kbengine.org/docs/startup_shutdown.html


##Start the client:

	Linux:
			nonsupport.

	Windows:
			kbengine_ogre_demo\kbengine\kbe\bin\client\!start.bat.


##Installation:

	Change the login address:
		kbengine_ogre_demo\kbengine\kbe\bin\client\kbengine.xml


![screenshots1](http://www.kbengine.org/assets/img/screenshots/ogre_demo1.jpg)
![screenshots2](http://www.kbengine.org/assets/img/screenshots/ogre_demo2.jpg)
![screenshots3](http://www.kbengine.org/assets/img/screenshots/ogre_demo3.jpg)