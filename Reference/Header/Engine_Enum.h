#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	enum WINMODE { MODE_FULL, MODE_WIN };

	// ID_DYNAMIC : 매 프레임마다 갱신을 해야하는 컴포넌트 집단
	// ID_STATIC : 한 번 만들면 그대로 사용할 컴포넌트 집단
	enum COMPONENTID { ID_DYNAMIC, ID_STATIC, ID_END };

	enum RENDERID { RENDER_PRIORITY, RENDER_MAPSETTING, RENDER_ANIOBJ, RENDER_NONANIOBJ, RENDER_NONALPHA, RENDER_ALPHA, RENDER_UI, RENDER_EFFECT_UI, RENDER_END };

	enum INFOID { INFO_RIGHT, INFO_UP, INFO_LOOK, INFO_POS, INFO_END };

	enum ROTATIONID { ROT_X, ROT_Y, ROT_Z, ROT_END };

	enum TEXTUREID { TEX_NORMAL, TEX_CUBE, TEX_END };

	enum LOADINGID { LOADING_STAGE, LOADING_BOSS, LOADING_END };

	enum MOUSEKEYSTATE { DIM_LB, DIM_RB, DIM_MB, DIM_END };

	enum MOUSEMOVESTATE { DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };

	enum CHANNELID { SOUND_EFFECT, SOUND_REFLECT, SOUND_BGM, SOUND_PLAYER, SOUND_EARTH, SOUND_DOOR, SOUND_GET, SOUND_MB, SOUND_KRAKEN1, SOUND_KRAKEN2, SOUND_KRAKEN3, MAXCHANNEL };

	enum DIRRECTIONSTATE { DIR_PX, DIR_MX, DIR_PY, DIR_MY, DIR_PZ, DIR_MZ, DIR_END };

	enum SKILLID { SKILL_SLOW, SKILL_DOUBLEGUN, SKILL_STATICFIELD, SKILL_HYPERIONSTRIKE, SKILL_SHIELD, SKILL_GRAVITYCANON, SKILLEND };

	enum EFFECTID
	{
		BLUEBOMB_EFT, REDEFFECT_EFT, BLUEEFFECT_EFT, CASTINGEFFECT_EFT, STAREFFECT_EFT, COIN_EFT, CREATEEFFECT_EFT, EXPLOSION_EFT, LIGHTNING_EFT, REDBOMB_EFT, STUN_EFT, EFT_END
	};

	enum WALLCOLDIR { WALL_LEFT, WALL_RIGHT, WALL_FRONT, WALL_BACK, WALL_END, };

	enum ITEMID { ITEM_HP, ITEM_DEFENCE, ITEM_BULLET, ITEM_END };

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
	enum ZOMBIEWALKID { ZOMBIEWALK_START, ZOMBIEWALK_1, ZOMBIEWALK_2, ZOMBIEWALK_END };
	enum ZOMBIEIDLEID { ZOMBIEIDLE_1, ZOMBIEIDLE_2, ZOMBIESTOP_END };
	enum ZOMBIEATTACKID { ZOMBIEATTACK_1, ZOMBIEATTACK_END };
	enum ZOMBIEDEADID { ZOMBIEDEAD_1, ZOMBIEDEAD_2, ZOMBIEDEAD_END };

	enum ILLUSIONSTATEID { ILLUSION_WALK, ILLUSION_IDLE, ILLUSION_ATTACK, ILLUSION_END };
	enum ILLUSIONWALKID { ILLUSIONWALK_START, ILLUSIONWALK_1, ILLUSIONWALK_2, ILLUSIONWALK_END };
	enum ILLUSIONIDLEID { ILLUSIONIDLE_1, ILLUSIONIDLE_2, ILLUSIONIDLE_3 };
	enum ILLUSIONATTACKID { ILLUSIONATTACK_1, ILLUSIONATTACK_2 };

	enum FIREMANSTATEID { FIREMAN_WALK, FIREMAN_IDLE, FIREMAN_ATTACK, FIREMAN_END };
	enum FIREMANWALKID { FIREMANWALK_START, FIREMANWALK_1, FIREMANWALK_2, FIREMANWALK_END };
	enum FIREMANIDLEID { FIREMANIDLE_1, FIREMANIDLE_2, FIREMANIDLE_END, };
	enum FIREMANATTACKID { FIREMANATTACK_1, FIREMANATTACK_2 };

	enum THORNSTATEID { THORN_UP, THORN_DOWN, THORN_END, };
	enum MAGMASTATEID { MAGMA_UP, MAGMA_DOWN, MAGMA_END, };
	enum ITEMBOXSTATEID { ITEMBOX_UP, ITEMBOX_DOWN, ITEMBOX_END };
	enum TERRETSTATEID { TERRET_IDLE, TERRET_SHOT, TERRET_END };
	enum TERRETIDLEID { TERRETIDLE_START, TERRETIDLE_1, TERRETIDLE_END };
	enum TERRETATTACKID { TERRETATTACK_START, TERRETATTACK_1, TERRETATTACK_END };

	enum UZISUPPORTSTATEID { UZISUPPORT_IDLE, UZISUPPORT_WALK, UZISUPPORT_ATTACK, UZISUPPORT_ULTI, UZISUPPORTER_DROP };
	enum UZISUPPORTIDLEID { UZISUPPORT_IDLE_1, UZISUPPORT_IDLE_2 };
	enum UZISUPPORTWALKID { UZISUPPORT_WALK_1, UZISUPPORT_WALK_2 };
	enum UZISUPPORTATTACKID { UZISUPPORT_ATTACK_1, UZISUPPORT_ATTACK_2 };
	enum UZISUPPORTULTID { UZIULT_1, UZIULT_2, UZIULT_3, UZIULT_4, UZIULT_5, UZIULT_6, };

	enum SHOTGUNSUPPORTSTATEID { SHOTGUNSUPPORT_IDLE, SHOTGUNSUPPORT_WALK, SHOTGUNSUPPORT_ATTACK, SHOTGUNSUPPORT_ULTI, SHOTGUNSUPPORT_DROP };
	enum SHOTGUNSUPPORTIDLEID { SHOTGUNSUPPORT_IDLE_1, SHOTGUNSUPPORT_IDLE_2 };
	enum SHOTGUNSUPPORTWALKID { SHOTGUNSUPPORT_WALK_1, SHOTGUNSUPPORT_WALK_2 };
	enum SHOTGUNSUPPORTATTACKID { SHOTGUNSUPPORT_ATTACK_1, SHOTGUNSUPPORT_ATTACK_2 };

	enum SNIPERSUPPORTSTATEID { SNIPERSUPPORT_IDLE, SNIPERSUPPORT_WALK, SNIPERSUPPORT_ATTACK, SNIPERSUPPORT_ULTI, SNIPERSUPPORT_DROP };
	enum SNIPERSUPPORTIDLEID { SNIPERSUPPORT_IDLE_1, SNIPERSUPPORT_IDLE_2 };
	enum SNIPERSUPPORTWALKID { SNIPERSUPPORT_WALK_1, SNIPERSUPPORT_WALK_2 };
	enum SNIPERSUPPORTATTACKID { SNIPERSUPPORT_ATTACK_1, SNIPERSUPPORT_ATTACK_2 };

	enum SUPPORTDROPID { SPDROP_1, SPDROP_2 };

	enum ALIENSTATEID { ALIEN_IDLE, ALIEN_WALK, ALIEN_ATTACK, ALIEN_END };
	enum ALIENWALKID { ALIENWALK_START, ALIENWALK_1, ALIENWALK_2, ALIENWALK_END };
	enum ALIENIDLEID { ALIENIDLE_1, ALIENIDLE_2, ALIENIDLE_END };
	enum ALIENATTACKID { ALIENATTACK_START, ALIENATTACK_1, ALIENATTACK_2, ALIENATTACK_END };
	enum ALIENSHOTTINGID { ALIENSHOT_START, ALIENSHOT_1, ALIENSHOT_END };


	enum MOBSTATEID {MOB_IDLE, MOB_WALK, MOB_ATTACK, MOB_END};
	enum MOBWALKID {MOB_WALKSTART, MOBWALK_1, MOBWALK_2, MOBWALK_3, MOBWALK_END};
	enum MOBIDLEID {MOBIDLE_1, MOBIDLE_2, MOBIDLE_3, MOBIDLE_END};
	enum MOBATTACKID {MOBATTACK_1, MOBATTACK_2, MOBATTACK_3, MOBATTACK_END};

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
	enum MIDDLEBOSSBOMBINGID { MIDDLEBOSS_BOMBING_1, MIDDLEBOSS_BOMBING_2, MIDDLEBOSS_BOMBING_3, MIDDLEBOSS_BOMBING_4, 
		MIDDLEBOSS_BOMBING_5, MIDDLEBOSS_BOMBING_6, MIDDLEBOSS_BOMBING_7, MIDDLEBOSS_BOMBING_8,
		MIDDLEBOSS_BOMBING_9, MIDDLEBOSS_BOMBING_10, MIDDLEBOSS_BOMBING_11, MIDDLEBOSS_BOMBING_12,
		MIDDLEBOSS_BOMBING_END };
	enum MIDDLEBOSSCRASHID { MIDDLEBOSS_CRASH_1, MIDDLEBOSS_CRASH_2, MIDDLEBOSS_CRASH_3, MIDDLEBOSS_CRASH_4, MIDDLEBOSS_CRASH_END };
	// 어떤패턴사용
	enum MIDDLEBOSSDEADID { MIDDLEBOSS_DEAD_1, MIDDLEBOSS_DEAD_2, MIDDLEBOSS_DEAD_3 };
	enum MIDDLEBOSSSKILLID { MIDDLEBOSS_SKILL_NORMALATTACK, MIDDLEBOSS_SKILL_BOMBING, MIDDLEBOSS_SKILL_CRASH, MIDDLEBOSS_SKILL_LASER, MIDDLEBOSS_SKILL_END };

	//enum KRAKENSTATEID { KRAKEN_IDLE, KRAKEN_WALK, KRAKEN_ATTACK, KRAKEN_SHOT, KRAKENSTATE_END };
	//enum KRAKENWALKID { KRAKENWALK_START, KRAKENWALK_1, KRAKENWALK_2, KRAKENWALK_END };
	//enum KRAKENIDLEID { KRAKENIDLE_1, KRAKENIDLE_2, KRAKENIDLE_END };
	//enum KRAKENATTACKID { KRAKENATTACK_START, KRAKENATTACK_1, KRAKENATTACK_2, KRAKENATTACK_END };
	//enum KRAKENSHOTID { KRAKENSHOT_START, KRAKENSHOT_1, KRAKENSHOT_2, KRAKENSHOT_END };


	enum KRAKENSTATEID { KRAKEN_IDLE, KRAKEN_APPEAR, KRAKEN_ATTACK, KRAKEN_REVIVE, KRAKENSTATE_END };

	enum KRAKENIDLEID { KRAKENIDLE_1, KRAKENIDLE_2, KRAKENIDLE_3, KRAKENIDLE_4, KRAKENIDLE_END };
	enum KRAKENAPPEARID { KRAKENAPPEAR_1, KRAKENAPPEAR_2, KRAKENAPPEAR_3, KRAKENAPPEAR_4 };

	enum KRAKENSMASHID { KRAKENSMASH_1, KRAKENSMASH_2, KRAKENSMASH_3, KRAKENSMASH_4,
		KRAKENSMASH_5, KRAKENSMASH_6, KRAKENSMASH_7, KRAKENSMASH_8,
		KRAKENSMASH_9, KRAKENSMASH_10, KRAKENSMASH_11, KRAKENSMASH_12 };

	enum KRAKENINKSHOTID { KRAKENINKSHOT_1, KRAKENINKSHOT_2, KRAKENINKSHOT_3, KRAKENINKSHOT_4 };
	enum KRAKENROLLINGID { KRAKENROLLING_1, KRAKENROLLING_2, KRAKENROLLING_3, KRAKEN_ROLLING_4 };
	enum KRAKENLURKERID {KRAKENLURKER_1, KRAKENLURKER_2, KRAKENLURKER_3, KRAKENLURKER_4, KRAKENLURKER_5, KRAKENLURKER_6 };

	enum KRAKENSKILLID { KRAKEN_SKILL_SMASH, KRAKEN_SKILL_INKSHOT, KRAKEN_SKILL_ROLLING, KRAKEN_SKILL_LURKER, KRAKEN_SKILL_5, KRAKEN_SKILL_END };

	enum KRAKENLEGIDLEID { LEGIDLE_1, LEGIDLE_2, LEGIDLE_3, LEGIDLE_4, LEGIDLE_5, LEGIDLE_6, LEGIDLE_7, LEGIDLE_8 };
	enum KRAKENLEGSHAKEID { LEGSHAKE_1, LEGSHAKE_2, LEGSHAKE_3 };
	enum KRAKENLEGREVIVEID { LEGREVIVE_1, LEGREVIVE_2, LEGREVIVE_3, KEGREVIVE_4 };
	enum KRAKENLEGSWINGID { LEGSWING_1, LEGSWING_2, LEGSWING_3, LEGSWING_4, LEGSWING_5, LEGSWING_6, 
		LEGSWING_7, LEGSWING_8, LEGSWING_9, LEGSWING_10, LEGSWING_11, LEGSWING_12,
		LEGSWING_13, LEGSWING_14, LEGSWING_15, LEGSWING_16, LEGSWING_17, LEGSWING_18,
		LEGSWING_19, LEGSWING_20, LEGSWING_21, LEGSWING_22, LEGSWING_23, LEGSWING_24
	};


	enum OBJECT_ID { GUN, SHOP, LAVA, ITEMBOX, THRONE, SLIME, FIREMAN, ZOMBIE, ILLUSIONER };

	enum SCENE_ID {LOGO_SCENE, STAGE_SCENE, FINAL_SCENE, TOOL_SCENE ,SCENE_END};
	enum COLOR_ID { COLOR_BLUE, COLOR_RED, COLOR_YELLOW, COLOR_END };
	enum SUPPORTER_ID { SUPPORTER_UZI, SUPPORTER_SHOTGUN, SUPPORTER_SNIPER, SUPPORTER_END };
	enum EXPLOSIONID { EXPLOSION_1, EXPLOSION_2 };

	enum LIGHT_TYPE : int8_t
	{
		DIRECTIONAL_LIGHT,
		POINT_LIGHT,
		SPOT_LIGHT
	};

}

#endif // Engine_Enum_h__




