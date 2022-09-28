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
	HRESULT Ready_MapTool(LPDIRECT3DDEVICE9 pGraphicDev, CScene* pScene);		//  ������ �ʿ��� ���ҽ��� �����մϴ�.
	HRESULT Ready_PlayerTool(LPDIRECT3DDEVICE9 pGraphicDev, CScene* pScene, CLayer* pLayer);	//  �÷��̾� ��
	HRESULT Ready_MonsterTool(LPDIRECT3DDEVICE9 pGraphicDev, CScene* pScene);   //  ���� ��
	HRESULT	Ready_CameraTool(LPDIRECT3DDEVICE9 pGraphicDev, CScene* pScene, CLayer* pLayer);

public:
	// Map_Tool ��� ����
	// â����
	void  WindowLayOut(); // ��ó�� ��ư
	void  CreateObject(LPDIRECT3DDEVICE9 pGrahicDev, CScene* pScene, CCamera *pCam);// ������Ʈ ����
	void  TerrainTool(LPDIRECT3DDEVICE9 pGrahicDev, CScene* pScene);				// Terrain Tool
	void  Save_Transform(CScene* pScene, wstring strDirectory = L"../../Data/Map.dat");											// ť�� ������Ʈ ����
	void  Load_Transform(LPDIRECT3DDEVICE9 pGrahicDev, CScene *pScene, wstring strDirectory = L"../../Data/Map.dat");				// ť�� ������Ʈ �ε�

	void  SwitchCamera(LPDIRECT3DDEVICE9 pGrahicDev, CScene* pScene, CLayer* pLayer, CCamera* pCam);

private:
	// Map_Tool ����
	wstring	m_CurrentSelectGameObjectObjKey = L"";
	_bool	m_bCubeCreateCheck = false;
	_bool	m_bCubeSelectCheck = false;

	_bool	m_bCameraCreateCheck = false;
	_bool	m_bCameraSelectCheck = false;

	_int	m_iIndex = 0;

	static _int m_iWidth;
	static _int m_iDepth;
	static _int m_iInterval;

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


