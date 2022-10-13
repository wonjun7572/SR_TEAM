#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	enum WINMODE	 { MODE_FULL, MODE_WIN };
	
// ID_DYNAMIC : 매 프레임마다 갱신을 해야하는 컴포넌트 집단
// ID_STATIC : 한 번 만들면 그대로 사용할 컴포넌트 집단
	enum COMPONENTID { ID_DYNAMIC, ID_STATIC, ID_END };

	enum RENDERID { RENDER_PRIORITY, RENDER_MAPSETTING,  RENDER_NONALPHA, RENDER_ALPHA, RENDER_WORLDMAP, RENDER_MINIMAP, RENDER_UI, RENDER_END };

	enum INFOID { INFO_RIGHT, INFO_UP, INFO_LOOK, INFO_POS, INFO_END };

	enum ROTATIONID { ROT_X, ROT_Y, ROT_Z, ROT_END};

	enum TEXTUREID { TEX_NORMAL, TEX_CUBE, TEX_END };

	enum LOADINGID { LOADING_STAGE, LOADING_BOSS, LOADING_END };
	
	enum MOUSEKEYSTATE { DIM_LB, DIM_RB, DIM_MB, DIM_END };

	enum MOUSEMOVESTATE { DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };

	enum CHANNELID { SOUND_EFFECT, SOUND_REFLECT, SOUND_BGM, SOUND_PLAYER, MAXCHANNEL };

	enum SKILLID { SKILL_SLOW, SKILL_DOUBLEGUN, SKILLEND };

	enum WALLCOLDIR { WALL_LEFT, WALL_RIGHT, WALL_FRONT, WALL_BACK, WALL_END, };

	enum ITEMID	 { ITEM_HP, ITEM_DEFENCE, ITEM_BULLET, ITEM_END };

	enum OWNERTYPE { OWN_PLAYER, OWN_MONSTER };

	enum PLAYERSTATEID { PLAYER_WALK, PLAYER_STOP, PLAYER_END };
	enum PLAYERWALKID { PLAYERWALK_1, PLAYERWALK_2, PLAYERWALK_START, PLAYERWALK_END };
	enum PLAYERSTOPID { PLAYERSTOP_1, PLAYERSTOP_2, PLAYERSTOP_END };

	enum SLIMESTATEID { SLIME_JUMP, SLIME_END, };
	enum SLIMEJUMPID { SLIMEJUMP_START, SLIMEJUMP_1, SLIMEJUMP_2, SLIMEJUMP_END, };

	enum MONSTERSTATEID { MONSTER_WALK, MONSTER_IDLE, MONSTER_ATTACK, MONSTER_DEAD, MONSTER_END };
	enum MONSTERWALKID {MONSTERWALK_START, MONSTERWALK_1, MONSTERWALK_2, MONSTERWALK_END };
	enum MONSTERIDLEID { MONSTERIDLE_1, MONSTERIDLE_2, MONSTERSTOP_END };
	enum MONSTERATTACKID { MONSTERATTACK_1, MONSTERATTACK_END };
	enum MONSTERDEADID {MONSTERDEAD_1, MONSTERDEAD_2, MONSTERDEAD_END};

	enum ILLUSIONSTATEID {ILLUSION_WALK, ILLUSION_IDLE, ILLUSION_ATTACK, ILLUSION_END};
	enum ILLUSIONWALKID {ILLUSIONWALK_START, ILLUSIONWALK_1, ILLUSIONWALK_2, ILLUSIONWALK_END};
	enum ILLUSIONIDLEID {ILLUSIONIDLE_1, ILLUSIONIDLE_2, ILLUSIONIDLE_3};
	enum ILLUSIONATTACKID {ILLUSIONATTACK_1, ILLSUIONATTACK_END};

	enum FIREMANSTATEID { FIREMAN_WALK, FIREMAN_IDLE, FIREMAN_ATTACK, FIREMAN_END };
	enum FIREMANWALKID { FIREMANWALK_START, FIREMANWALK_1, FIREMANWALK_2, FIREMANWALK_END };
	enum FIREMANIDLEID { FIREMANIDLE_1, FIREMANIDLE_2, FIREMANIDLE_END, };
	enum FIREMANATTACKID { FIREMANATTACK_1, FIREMANATTACK_END };

	enum THORNSTATEID { THORN_UP, THORN_DOWN, THORN_END, };
	enum MAGMASTATEID { MAGMA_UP, MAGMA_DOWN, MAGMA_END, };
	enum ITEMBOXSTATEID { ITEMBOX_UP, ITEMBOX_DOWN, ITEMBOX_END };

	enum UZISUPPORTSTATEID { UZISUPPORT_IDLE, UZISUPPORT_WALK, UZISUPPORT_ATTACK, UZISUPPORT_ULTI };
	enum UZISUPPORTIDLEID { UZISUPPORT_IDLE_1, UZISUPPORT_IDLE_2 };
	enum UZISUPPORTWALKID { UZISUPPORT_WALK_1, UZISUPPORT_WALK_2 };
	enum UZISUPPORTATTACKID { UZISUPPORT_ATTACK_1, UZISUPPORT_ATTACK_2 };
	enum UZISUPPORTULTID {UZIULT_1, UZIULT_2, UZIULT_3, UZIULT_4, UZIULT_5, UZIULT_6, };


	enum MIDDLEBOSSSTATEID {MIDDLEBOSS_IDLE, MIDDLEBOSS_WALK, MIDDLEBOSS_ATTACK, MIDDLEBOSS_SHOT, MIDDLEBOSSSTATE_END};
	enum MIDDLEBOSSWALKID {MIDDLEBOSSWALK_START, MIDDLEBOSSWALK_1, MIDDLEBOSSWALK_2, MIDDLEBOSSWALK_END};
	enum MIDDLEBOSSIDLEID {MIDDLEBOSSIDLE_1, MIDDLEBOSSIDLE_2, MIDDLEBOSSIDLE_END};
	enum MIDDLEBOSSATTACKID {MIDDLEBOSSATTACK_START,MIDDLEBOSSATTACK_1, MIDDLEBOSSATTACK_END};
	enum MIDDLEBOSSSHOOTID {MIDDLEBOSSSHOT_START, MIDDLEBOSSSHOT_1, MIDDLEBOSSSHOT_END};
}

#endif // Engine_Enum_h__




