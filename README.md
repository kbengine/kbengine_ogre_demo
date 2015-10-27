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

		1. Download and install Microsoft DirectX SDK 9.0, (http://www.microsoft.com/en-hk/download/details.aspx?id=6812).

		2. Download kbengine-xxx.zip, (https://github.com/kbengine/kbengine/releases/latest).
			Decompression(kbengine-xxx.zip\kbengine-xxx\*) to kbengine_ogre_demo\kbengine\*.
			Covering all the directories and files.

		3. Microsoft Visual Studio-> kbengine_ogre_demo\kbengine\kbe\src\kbengine_vs**.sln -> build.
		
		4. Microsoft Visual Studio-> kbengine_ogre_demo\kbengine\kbe\src\client\ogre\client_for_ogre_vc**.sln -> build.

		5. Copy Ogre-dlls to client.
			kbengine_ogre_demo\ogre3d\bin\debug\*.dll to kbengine_ogre_demo\kbengine\kbe\bin\client\
			kbengine_ogre_demo\ogre3d\bin\release\*.dll to kbengine_ogre_demo\kbengine\kbe\bin\client\

		6. Download demo-assets(server):
			https://github.com/kbengine/kbengine_demos_assets/releases/latest
			Unzip and Covering to kbengine/kbengine_demos_assets

![demo_configure](http://www.kbengine.org/assets/img/screenshots/demo_copy_kbengine.jpg)



##Start the servers:

	Installation(KBEngine):
			http://www.kbengine.org/docs/installation.html

	Start server:
		Windows:
			kbengine\kbengine_demos_assets\start_server_fixed.bat

		Linux:
			kbengine\kbengine_demos_assets\start_server_fixed.sh

		(More: http://www.kbengine.org/docs/startup_shutdown.html)



##Configure client:

	Change the login address:
		kbengine_ogre_demo\kbengine\kbe\bin\client\kbengine.xml

##Start the client:

	Linux:
			nonsupport.

	Windows:
			kbengine_ogre_demo\kbengine\kbe\bin\client\!start.bat.





![screenshots1](http://www.kbengine.org/assets/img/screenshots/ogre_demo1.jpg)
![screenshots2](http://www.kbengine.org/assets/img/screenshots/ogre_demo2.jpg)
![screenshots3](http://www.kbengine.org/assets/img/screenshots/ogre_demo3.jpg)