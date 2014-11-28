#include "space_avatarselect.h"
#include "space_world.h"
#include "OgreApplication.h"
#include "common/common.hpp"
#include "common/stringconv.hpp"
#include "pyscript/pythread_lock.hpp"
#include "../../kbengine_dll/kbengine_dll.h"

std::vector<Ogre::String> g_avatars;
KBEngine::DBID g_selAvatarDBID = 0;

//-------------------------------------------------------------------------------------
SpaceAvatarSelect::SpaceAvatarSelect(Ogre::Root *pOgreRoot, Ogre::RenderWindow* pRenderWin, 
		OIS::InputManager* pInputMgr, OgreBites::SdkTrayManager* pTrayMgr)
:   Space(pOgreRoot, pRenderWin, pInputMgr, pTrayMgr)
{
}

//-------------------------------------------------------------------------------------
SpaceAvatarSelect::~SpaceAvatarSelect(void)
{
	mTrayMgr->destroyWidget("start");
	mTrayMgr->destroyWidget("create");

	for(KBEngine::uint32 i=0; i<g_avatars.size(); i++)
	{
		mTrayMgr->destroyWidget(g_avatars[i]);
	}
	
	g_avatars.clear();
}

//-------------------------------------------------------------------------------------
void SpaceAvatarSelect::setupResources(void)
{
	// ogre²»ÏÔÊ¾ÎÄ×Öbug
	// http://www.ogre3d.org/forums/viewtopic.php?f=4&t=59197
	Ogre::ResourceManager::ResourceMapIterator iter = Ogre::FontManager::getSingleton().getResourceIterator();
	while (iter.hasMoreElements()) { 
		iter.getNext()->load(); 
	}
}

//-------------------------------------------------------------------------------------
void SpaceAvatarSelect::createScene(void)
{
	mTrayMgr->createButton(OgreBites::TL_BOTTOMRIGHT, "start", "start", 120);
	mTrayMgr->createButton(OgreBites::TL_BOTTOMLEFT, "create", "create avatar", 120);

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
bool SpaceAvatarSelect::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	mTrayMgr->frameRenderingQueued(evt);
    return true;
}

//-------------------------------------------------------------------------------------
bool SpaceAvatarSelect::keyPressed( const OIS::KeyEvent &arg )
{
    return true;
}

//-------------------------------------------------------------------------------------
void SpaceAvatarSelect::buttonHit(OgreBites::Button* button)
{
	if(button->getCaption().find("start") != Ogre::UTFString::npos)
	{
		if(g_selAvatarDBID == 0)
		{
			MessageBox( NULL, "SpaceAvatarSelect::no selected avatar!", "warning!", MB_OK);
			return;
		}

		kbe_lock();
		kbe_callEntityMethod(kbe_playerID(), "selectAvatarGame", KBEngine::StringConv::val2str(g_selAvatarDBID).c_str());
		kbe_unlock();

		OgreApplication::getSingleton().changeSpace(new SpaceWorld(mRoot, mWindow, mInputManager, mTrayMgr));
	}
	else if(button->getCaption() == "create avatar")
	{
		kbe_lock();
		kbe_callEntityMethod(kbe_playerID(), "reqCreateAvatar", "[1, \"kbengine\"]");
		kbe_unlock();
	}
	else
	{
		for(KBEngine::uint32 i=0; i<g_avatars.size(); i++)
		{
			if(button->getCaption() == g_avatars[i])
			{
				Ogre::String dbid = Ogre::StringUtil::split(button->getCaption(), "_")[1];
				g_selAvatarDBID = KBEngine::StringConv::str2value<KBEngine::DBID>(dbid.c_str());
				((OgreBites::Button*)mTrayMgr->getWidget("start"))->setCaption(Ogre::String("start[") + dbid + Ogre::String("]"));
			}
		}
	}
}

//-------------------------------------------------------------------------------------
void SpaceAvatarSelect::kbengine_onEvent(const KBEngine::EventData* lpEventData)
{
	switch(lpEventData->id)
	{
		case CLIENT_EVENT_SCRIPT:
			{
				const KBEngine::EventData_Script* peventdata = static_cast<const KBEngine::EventData_Script*>(lpEventData);
				if(peventdata->name == "update_avatars")
				{
					for(KBEngine::uint32 i=0; i<g_avatars.size(); i++)
					{
						mTrayMgr->destroyWidget(g_avatars[i]);
					}
						
					g_avatars.clear();

					Json::Reader reader;
					Json::Value root;

					if (reader.parse(peventdata->datas.c_str(), root))
					{  
						Json::Value::Members mem = root.getMemberNames();  
						for (auto iter = mem.begin(); iter != mem.end(); iter++)  
						{  
							Json::Value& val = root[*iter];
							std::string name = val[1].asString();
							KBEngine::DBID dbid = val[Json::Value::UInt(0)].asUInt();

							Ogre::String str = Ogre::String(name) + "_" + KBEngine::StringConv::val2str(dbid);
							g_avatars.push_back(str);
							mTrayMgr->createButton(OgreBites::TL_CENTER, str, str, 300);
						}
					}
				}
			}
			break;
		default:
			break;
	};
}