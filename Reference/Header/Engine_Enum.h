#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	enum WINMODE	 { MODE_FULL, MODE_WIN };
	
// ID_DYNAMIC : 매 프레임마다 갱신을 해야하는 컴포넌트 집단
// ID_STATIC : 한 번 만들면 그대로 사용할 컴포넌트 집단
	enum COMPONENTID { ID_DYNAMIC, ID_STATIC, ID_END };

	enum RENDERID { RENDER_PRIORITY, RENDER_MAPSETTING, RENDER_ANIOBJ, RENDER_NONANIOBJ, RENDER_NONALPHA, RENDER_ALPHA, RENDER_UI, RENDER_END };

	enum INFOID { INFO_RIGHT, INFO_UP, INFO_LOOK, INFO_POS, INFO_END };

	enum ROTATIONID { ROT_X, ROT_Y, ROT_Z, ROT_END};

	enum TEXTUREID { TEX_NORMAL, TEX_CUBE, TEX_END };

	enum LOADINGID { LOADING_STAGE, LOADING_BOSS, LOADING_END };
	
	enum MOUSEKEYSTATE { DIM_LB, DIM_RB, DIM_MB, DIM_END };

	enum MOUSEMOVESTATE { DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };

	enum CHANNELID { SOUND_EFFECT, SOUND_REFLECT, SOUND_BGM, SOUND_PLAYER, MAXCHANNEL };

	enum DIRRECTIONSTATE {DIR_PX, DIR_MX, DIR_PY, DIR_MY, DIR_PZ, DIR_MZ, DIR_END};

	enum SKILLID { SKILL_SLOW, SKILL_DOUBLEGUN, SKILL_STATICFIELD, SKILL_HYPERIONSTRIKE, SKILL_SHIELD, SKILL_GRAVITYCANON, SKILLEND };

	enum EFFECTID
	{	BLUEBOMB_EFT, REDEFFECT_EFT, BLUEEFFECT_EFT, CASTINGEFFECT_EFT, STAREFFECT_EFT, COIN_EFT, CREATEEFFECT_EFT, EXPLOSION_EFT, LIGHTNING_EFT, REDBOMB_EFT, STUN_EFT,EFT_END	};

	enum WALLCOLDIR { WALL_LEFT, WALL_RIGHT, WALL_FRONT, WALL_BACK, WALL_END, };

	enum ITEMID	 { ITEM_HP, ITEM_DEFENCE, ITEM_BULLET, ITEM_END };

	enum OWNERTYPE { OWN_PLAYER, OWN_MONSTER };

	enum COLLISIONDIRID {
		COLLISION_FRONT, COLLISION_BACK, COLLISION_LEFT, COLLISION_RIGHT,
		COLLISION_FRONT_LEFT, COLLISION_FRONT_RIGHT, COLLISION_BACK_LEFT, COLLISION_BACK_RIGHT
	};

	enum PLAYERSTATEID { PLAYER_WALK, PLAYER_STOP, PLAYER_END };
	enum PLAYERWALKID { PLAYERWALK_1, PLAYERWALK_2, PLAYERWALK_START, PLAYERWALK_END };
	enum PLAYERSTOPID { PLAYERSTOP_1, PLAYERSTOP_2, PLAYERSTOP_END };

	enum SLIMESTATEID { SLIME_JUMP, SLIME_END, };
	enum SLIMEJUMPID { SLIMEJUMP_1, SLIMEJUMP_2, SLIMEJUMP_END, };

	enum ZOMBIESTATEID { ZOMBIE_WALK, ZOMBIE_IDLE, ZOMBIE_ATTACK, ZOMBIE_DEAD, ZOMBIE_END };
	enum ZOMBIEWALKID {ZOMBIEWALK_START, ZOMBIEWALK_1, ZOMBIEWALK_2, ZOMBIEWALK_END };
	enum ZOMBIEIDLEID { ZOMBIEIDLE_1, ZOMBIEIDLE_2, ZOMBIESTOP_END };
	enum ZOMBIEATTACKID { ZOMBIEATTACK_1, ZOMBIEATTACK_END };
	enum ZOMBIEDEADID {ZOMBIEDEAD_1, ZOMBIEDEAD_2, ZOMBIEDEAD_END};

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
	enum TERRETSTATEID {TERRET_IDLE, TERRET_SHOT, TERRET_END};
	enum TERRETIDLEID {TERRETIDLE_START, TERRETIDLE_1, TERRETIDLE_END};
	enum TERRETATTACKID {TERRETATTACK_START, TERRETATTACK_1, TERRETATTACK_END};


	enum UZISUPPORTSTATEID { UZISUPPORT_IDLE, UZISUPPORT_WALK, UZISUPPORT_ATTACK, UZISUPPORT_ULTI };
	enum UZISUPPORTIDLEID { UZISUPPORT_IDLE_1, UZISUPPORT_IDLE_2 };
	enum UZISUPPORTWALKID { UZISUPPORT_WALK_1, UZISUPPORT_WALK_2 };
	enum UZISUPPORTATTACKID { UZISUPPORT_ATTACK_1, UZISUPPORT_ATTACK_2 };
	enum UZISUPPORTULTID {UZIULT_1, UZIULT_2, UZIULT_3, UZIULT_4, UZIULT_5, UZIULT_6, };

	enum ALIENSTATEID {ALIEN_IDLE, ALIEN_WALK, ALIEN_ATTACK, ALIEN_END };
	enum ALIENWALKID {ALIENWALK_START, ALIENWALK_1, ALIENWALK_2, ALIENWALK_END};
	enum ALIENIDLEID {ALIENIDLE_1, ALIENIDLE_2, ALIENIDLE_END};
	enum ALIENATTACKID {ALIENATTACK_START, ALIENATTACK_1, ALIENATTACK_2, ALIENATTACK_END};
	enum ALIENSHOTTINGID {ALIENSHOT_START, ALIENSHOT_1, ALIENSHOT_END};




	/*enum MIDDLEBOSSSTATEID {MIDDLEBOSS_IDLE, MIDDLEBOSS_WALK, MIDDLEBOSS_ATTACK, MIDDLEBOSS_SHOT, MIDDLEBOSS_CRASH, MIDDLEBOSSSTATE_END};
	enum MIDDLEBOSSWALKID {MIDDLEBOSSWALK_START, MIDDLEBOSSWALK_1, MIDDLEBOSSWALK_2,MIDDLEBOSSWALK_END};
	enum MIDDLEBOSSIDLEID {MIDDLEBOSSIDLE_1, MIDDLEBOSSIDLE_2, MIDDLEBOSSIDLE_3, MIDDLEBOSSIDLE_4, MIDDLEBOSSIDLE_END};
	enum MIDDLEBOSSATTACKID {MIDDLEBOSSATTACK_START,MIDDLEBOSSATTACK_1, MIDDLEBOSSATTACK_2, MIDDLEBOSSATTACK_3, MIDDLEBOSSATTACK_END};
	enum MIDDLEBOSSSHOOTID {MIDDLEBOSSSHOT_START, MIDDLEBOSSSHOT_1, MIDDLEBOSSSHOT_2, MIDDLEBOSSSHOT_3, MIDDLEBOSSSHOT_END};

	enum MIDDLEBOSSPATTERNID { MIDDLEBOSS_PATTERN_IDLE, MIDDLEBOSS_PATTERN_1, MIDDLEBOSS_PATTERN_2 };*/

	// 상태값
	enum MIDDLEBOSSSTATEID { MIDDLEBOSS_IDLE, MIDDLEBOSS_MOVE, MIDDLEBOSS_ATTACK, MIDDLEBOSS_END };
	// 애니메이션값
	enum MIDDLEBOSSWALKID { MIDDLEBOSSWALK_1, MIDDLEBOSSWALK_2, MIDDLEBOSSWALK_3, MIDDLEBOSSWALK_END };
	enum MIDDLEBOSSIDLEID { MIDDLEBOSSIDLE_1, MIDDLEBOSSIDLE_2, MIDDLEBOSSIDLE_3, MIDDLEBOSSIDLE_4, MIDDLEBOSSIDLE_END };
	enum MIDDLEBOSSNORMALATTACKID { MIDDLEBOSS_NORMALATTACK_1, MIDDLEBOSS_NORMALATTACK_2, MIDDLEBOSS_NORMALATTACK_3, MIDDLEBOSS_NORMALATTACK_4, MIDDLEBOSS_NORMALATTACK_END };
	enum MIDDLEBOSSBOMBINGID { MIDDLEBOSS_BOMBING_1, MIDDLEBOSS_BOMBING_2, MIDDLEBOSS_BOMBING_3, MIDDLEBOSS_BOMBING_4, MIDDLEBOSS_BOMBING_END };
	enum MIDDLEBOSSCRASHID { MIDDLEBOSS_CRASH_1, MIDDLEBOSS_CRASH_2, MIDDLEBOSS_CRASH_3, MIDDLEBOSS_CRASH_4, MIDDLEBOSS_CRASH_END };
	// 어떤패턴사용
	enum MIDDLEBOSSSKILLID { MIDDLEBOSS_SKILL_NORMALATTACK, MIDDLEBOSS_SKILL_BOMBING, MIDDLEBOSS_SKILL_CRASH, MIDDLEBOSS_SKILL_END };



	enum KRAKENSTATEID { KRAKEN_IDLE, KRAKEN_WALK, KRAKEN_ATTACK, KRAKEN_SHOT, KRAKENSTATE_END };
	enum KRAKENWALKID { KRAKENWALK_START, KRAKENWALK_1, KRAKENWALK_2, KRAKENWALK_END };
	enum KRAKENIDLEID { KRAKENIDLE_1, KRAKENIDLE_2, KRAKENIDLE_END };
	enum KRAKENATTACKID { KRAKENATTACK_START, KRAKENATTACK_1, KRAKENATTACK_2, KRAKENATTACK_END };
	enum KRAKENSHOTID { KRAKENSHOT_START, KRAKENSHOT_1, KRAKENSHOT_2, KRAKENSHOT_END };

	enum OBJECT_ID { GUN, SHOP, LAVA, ITEMBOX, THRONE, SLIME, FIREMAN, ZOMBIE, ILLUSIONER };

	enum SCENE_ID {LOGO_SCENE, STAGE_SCENE, TOOL_SCENE ,SCENE_END};
	enum COLOR_ID { COLOR_BLUE, COLOR_RED, COLOR_YELLOW, COLOR_END };

	enum EXPLOSIONID { EXPLOSION_1, EXPLOSION_2 };
}

#endif // Engine_Enum_h__




