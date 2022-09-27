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
	HRESULT Ready_PlayerTool(LPDIRECT3DDEVICE9 pGraphicDev, CScene* pScene);	//  �÷��̾� ��
	HRESULT Ready_MonsterTool(LPDIRECT3DDEVICE9 pGraphicDev, CScene* pScene);   //  ���� ��

public:
	// Map_Tool ��� ����
	// â����
	void  WindowLayOut(); // ��ó�� ��ư
	void  CreateObject(LPDIRECT3DDEVICE9 pGrahicDev, CScene* pScene, CCamera *pCam);// ������Ʈ ����
	void  TerrainTool(LPDIRECT3DDEVICE9 pGrahicDev, CScene* pScene);				// Terrain Tool
	void  Save_Transform(CScene* pScene, wstring strDirectory = L"../../Data/Map.dat");											// ť�� ������Ʈ ����
	void  Load_Transform(LPDIRECT3DDEVICE9 pGrahicDev, CScene *pScene, wstring strDirectory = L"../../Data/Map.dat");				// ť�� ������Ʈ �ε�

private:
	// Map_Tool ����
	wstring	m_CurrentSelectGameObjectObjKey = L"";
	_bool	m_bCubeCreateCheck = false;
	_bool	m_bCubeSelcetCheck = false;
	_int		m_iIndex = 0;

	static _int m_iWidth;
	static _int m_iDepth;
	static _int m_iInterval;

	list<_tchar* > NameList;

	CTransform* m_pSelectedTransform = nullptr;
	// ~Map_Tool ����

public:
	//  windowâ ������ �ʿ��� �Һ���
	static  bool Show_Terrain_Window;
	static	bool Show_Player_Window;
	static  bool Show_Main_Menu_Window;
	static  bool Show_Cube_Tool;
	static  bool Show_Monster_Window;
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


