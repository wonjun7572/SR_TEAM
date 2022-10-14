#pragma once
#include "Base.h"
#include "Engine_Include.h"
#include "ImGuiFileBrowser.h"
#include "ImGuiFileDialog.h"
#include "ImGuiFileDialogConfig.h"
#include "Scene.h"

BEGIN(Engine)

class CCamera;
class CTransform;

END
// TexturePath �� ���� Struct
struct TexturePath
{
	PDIRECT3DTEXTURE9 pTexture;
	_tchar*	wszFilePathName;
};

struct ObjectElement
{
	_int	iId;
	wstring strName;
	_vec3	vPos;
};

class CImGuiMgr : public CBase
{
	DECLARE_SINGLETON(CImGuiMgr)

private:
	explicit CImGuiMgr();
	virtual ~CImGuiMgr();

public:
	// ����
	static void TransformEdit(CCamera* pCamera, CTransform* pTransform, _bool& Window); // Gizmo
	static void LoggerWindow();
	static void LogOut(const char* fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		log.appendfv(fmt, args);
		va_end(args);
	}
	// ���� 

public:
	// Map_Tool ��� ����
	// â����
	void  WindowLayOut(); // ��ó�� ��ư
	void  CreateWall(LPDIRECT3DDEVICE9 pGrahicDev, CScene* pScene, CCamera *pCam);// ������Ʈ ����
	void  Save_Transform(CScene* pScene, wstring strDirectory = L"../../Data/Map.dat");											// ť�� ������Ʈ ����
	void  Load_Transform(LPDIRECT3DDEVICE9 pGrahicDev, CScene *pScene, wstring strDirectory = L"../../Data/Map.dat");				// ť�� ������Ʈ �ε�
	void  SwitchCamera(LPDIRECT3DDEVICE9 pGrahicDev, CScene* pScene, CLayer* pLayer, CCamera* pCam);

	void  CreateObject(LPDIRECT3DDEVICE9 pGrahicDev, CScene* pScene, CCamera *pCam);
	void  Save_ObjectTransform(CScene* pScene, wstring strDirectory = L"../../Data/ObjectTransform.dat");
	void  Load_ObjectTransform(LPDIRECT3DDEVICE9 pGrahicDev, CScene* pScene, wstring strDirectory = L"../../Data/ObjectTransform.dat");


private:
	// Map_Tool ����
	wstring	m_CurrentSelectGameObjectObjKey = L"";
	_bool	m_bCubeCreateCheck = false;
	_bool	m_bCubeSelectCheck = false;

	_bool	m_bCameraCreateCheck = false;
	_bool	m_bCameraSelectCheck = false;

	_bool	m_bObjectCreateCheck = false;
	_bool	m_bObjectSelectCheck = false;

	_int	m_iIndex = 0;

	static _int m_iWidth;
	static _int m_iDepth;
	static _int m_iInterval;

	_int	m_iGunIndex = 0;
	_int	m_iShopIndex = 0;
	_int	m_iLavaIndex = 0;
	_int	m_iItemIndex = 0;
	_int	m_iThroneIndex = 0;
	_int	m_iSlimeIndex = 0;
	_int	m_iFireManIndex = 0;
	_int	m_iZombieIndex = 0;
	_int	m_iIllusionerIndex = 0;

	list<_tchar* > NameList;
	list<char*> CamList;

	CTransform* m_pSelectedTransform = nullptr;
	// ~Map_Tool ����

public:
	//  windowâ ������ �ʿ��� �Һ���
	static  _bool Show_Terrain_Window;
	static	_bool Show_Player_Window;
	static  _bool Show_Main_Menu_Window;
	static  _bool Show_Cube_Tool;
	static  _bool Show_Monster_Window;
	static  _bool Show_Camera_Tool;
	static  _bool Show_Object_Tool;
	static ImVec4 clear_color;
	// ~ windowâ ������ �ʿ��� �Һ���

	// File ����
	static ImGuiFileDialog fileDialog;
	static imgui_addons::ImGuiFileBrowser file_dialog;
	// ~File ����

private:
	// ����
	static ImGuiTextBuffer log;
	virtual void Free() override;
	// ~����
};


