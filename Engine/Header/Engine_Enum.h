#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	enum WINMODE	 { MODE_FULL, MODE_WIN };
	
// ID_DYNAMIC : �� �����Ӹ��� ������ �ؾ��ϴ� ������Ʈ ����
// ID_STATIC : �� �� ����� �״�� ����� ������Ʈ ����
	enum COMPONENTID { ID_DYNAMIC, ID_STATIC, ID_END };

	enum RENDERID { RENDER_PRIORITY, RENDER_NONALPHA, RENDER_ALPHA, RENDER_UI, RENDER_END };

	enum INFOID { INFO_RIGHT, INFO_UP, INFO_LOOK, INFO_POS, INFO_END };

	enum ROTATIONID { ROT_X, ROT_Y, ROT_Z, ROT_END};

	enum TEXTUREID { TEX_NORMAL, TEX_CUBE, TEX_END };

	enum LOADINGID { LOADING_STAGE, LOADING_BOSS, LOADING_END };
	
}

#endif // Engine_Enum_h__




