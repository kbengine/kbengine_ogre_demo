#pragma warning(disable:4251) 
#include "space_login.h"
#include "space_avatarselect.h"
#include "OgreApplication.h"
#include "cstdkbe/cstdkbe.hpp"
#include "cstdkbe/stringconv.hpp"
#include "../../kbengine_dll/kbengine_dll.h"

Ogre::String g_accountName;

//-------------------------------------------------------------------------------------
SpaceLogin::SpaceLogin(Ogre::Root *pOgreRoot, Ogre::RenderWindow* pRenderWin, 
		OIS::InputManager* pInputMgr, OgreBites::SdkTrayManager* pTrayMgr)
:   Space(pOgreRoot, pRenderWin, pInputMgr, pTrayMgr)
{
}

//-------------------------------------------------------------------------------------
SpaceLogin::~SpaceLogin(void)
{
	mTrayMgr->destroyWidget("login");
	mTrayMgr->destroyWidget("accountName");
}

//-------------------------------------------------------------------------------------
void SpaceLogin::setupResources(void)
{
	// ogre²»ÏÔÊ¾ÎÄ×Öbug
	// http://www.ogre3d.org/forums/viewtopic.php?f=4&t=59197
	Ogre::ResourceManager::ResourceMapIterator iter = Ogre::FontManager::getSingleton().getResourceIterator();
	while (iter.hasMoreElements()) { 
		iter.getNext()->load(); 
	}
}

//-------------------------------------------------------------------------------------
void SpaceLogin::createScene(void)
{
	g_accountName = kbe_getLastAccountName();
	if(g_accountName.size() == 0)
		g_accountName = KBEngine::StringConv::val2str(KBEngine::genUUID64());

	mTrayMgr->createButton(OgreBites::TL_CENTER, "login", "fast login", 120);

	Ogre::StringVector values;
	values.push_back(g_accountName);
	mTrayMgr->createParamsPanel(OgreBites::TL_CENTER, "accountName", 300, values);

	mTrayMgr->showCursor();
	
	mTrayMgr->hideFrameStats();
	mTrayMgr->hideLogo();
	mTrayMgr->hideBackdrop();

	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

    // Create the camera
    mActiveCamera = mSceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    mActiveCamera->setPosition(Ogre::Vector3(0,0,80));
    // Look back along -Z
    mActiveCamera->lookAt(Ogre::Vector3(0,0,-300));
    mActiveCamera->setNearClipDistance(5);

    mCameraMan = new OgreBites::SdkCameraMan(mActiveCamera);   // create a default camera controller
    mCameraMan->setTopSpeed(7.0f);
	OgreApplication::getSingleton().setCurrCameraMan(mCameraMan);

    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mActiveCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    mActiveCamera->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

//-------------------------------------------------------------------------------------
bool SpaceLogin::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	mTrayMgr->frameRenderingQueued(evt);
    return true;
}

//-------------------------------------------------------------------------------------
bool SpaceLogin::keyPressed( const OIS::KeyEvent &arg )
{
    return true;
}

//-------------------------------------------------------------------------------------
void SpaceLogin::buttonHit(OgreBites::Button* button)
{
	if(button->getCaption() == "fast login")
	{
		if(!kbe_login(g_accountName.c_str(), "123456"))
		{
			MessageBox( NULL, "SpaceLogin::connect is error!", "warning!", MB_OK);
		}
	}
}

//-------------------------------------------------------------------------------------
void SpaceLogin::kbengine_onEvent(const KBEngine::EventData* lpEventData)
{
	switch(lpEventData->id)
	{
	case CLIENT_EVENT_LOGIN_SUCCESS:
		break;
	case CLIENT_EVENT_LOGIN_FAILED:
		{
			const KBEngine::EventData_LoginFailed* info = static_cast<const KBEngine::EventData_LoginFailed*>(lpEventData);
			char str[256];

			if(info->failedcode == 20)
			{
				sprintf(str, "server is starting, please wait!");
			}
			else
			{
				sprintf(str, "SpaceLogin::kbengine_onEvent(): login is failed(code=%u)!", info->failedcode);
			}

			MessageBox( NULL, str, "warning!", MB_OK);
		}
		break;
	case CLIENT_EVENT_LOGIN_GATEWAY_SUCCESS:
		OgreApplication::getSingleton().changeSpace(new SpaceAvatarSelect(mRoot, mWindow, mInputManager, mTrayMgr));
		break;
	case CLIENT_EVENT_LOGIN_GATEWAY_FAILED:
		{
			const KBEngine::EventData_LoginGatewayFailed* info = static_cast<const KBEngine::EventData_LoginGatewayFailed*>(lpEventData);
			char str[256];
			sprintf(str, "SpaceLogin::kbengine_onEvent(): loginGateway is failed(code=%u)!", info->failedcode);
			MessageBox( NULL, str, "warning!", MB_OK);
		}
		break;
	case CLIENT_EVENT_VERSION_NOT_MATCH:
		{
			const KBEngine::EventData_VersionNotMatch* info = static_cast<const KBEngine::EventData_VersionNotMatch*>(lpEventData);
			char str[256];
			sprintf(str, "SpaceLogin::kbengine_onEvent(): verInfo=%s not match(server:%s)", info->verInfo.c_str(), info->serVerInfo.c_str());
			MessageBox( NULL, str, "error!", MB_OK);
		}
		break;
	case CLIENT_EVENT_SCRIPT_VERSION_NOT_MATCH:
		{
			const KBEngine::EventData_ScriptVersionNotMatch* info = static_cast<const KBEngine::EventData_ScriptVersionNotMatch*>(lpEventData);
			char str[256];
			sprintf(str, "SpaceLogin::kbengine_onEvent(): scriptVerInfo=%s not match(server:%s)", info->verInfo.c_str(), info->serVerInfo.c_str());
			MessageBox( NULL, str, "error!", MB_OK);
		}
		break;
	case CLIENT_EVENT_LAST_ACCOUNT_INFO:
		{
			const KBEngine::EventData_LastAccountInfo* info = static_cast<const KBEngine::EventData_LastAccountInfo*>(lpEventData);
			g_accountName = info->name;
			
			if(mTrayMgr)
			{
				OgreBites::ParamsPanel* pannel = ((OgreBites::ParamsPanel*)mTrayMgr->getWidget("accountName"));
				
				if(pannel)
				{
					pannel->setParamValue(0, g_accountName);
				}
			}

		}
		break;
	default:
		break;
	};
}