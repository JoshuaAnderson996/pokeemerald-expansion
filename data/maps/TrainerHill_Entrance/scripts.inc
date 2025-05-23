.set LOCALID_ATTENDANT, 1
.set LOCALID_NURSE, 2
.set LOCALID_GIRL, 4
.set LOCALID_MAN, 5

TrainerHill_Entrance_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, TrainerHill_Entrance_OnResume
	map_script MAP_SCRIPT_ON_RETURN_TO_FIELD, TrainerHill_Entrance_OnReturn
	map_script MAP_SCRIPT_ON_TRANSITION, TrainerHill_Entrance_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, TrainerHill_Entrance_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrainerHill_Entrance_OnFrame
	.byte 0

TrainerHill_Entrance_OnTransition:
	setflag FLAG_LANDMARK_TRAINER_HILL
	getplayerxy VAR_TEMP_D, VAR_RESULT
	end

@ Unused
TrainerHill_Entrance_OnWarp:
	end

TrainerHill_Entrance_OnResume:
	trainerhill_resumetimer
	setvar VAR_TEMP_0, 0
	trainerhill_getusingereader
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_TryFaceAttendant  @ VAR_RESULT always FALSE here
	setobjectxy OBJ_EVENT_ID_PLAYER, 9, 6
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	end

TrainerHill_Entrance_EventScript_TryFaceAttendant::
	trainerhill_getwon
	goto_if_eq VAR_RESULT, TRUE, TrainerHill_Entrance_EventScript_PlayerDontFaceAttendant
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	end

TrainerHill_Entrance_EventScript_PlayerDontFaceAttendant::
	end

TrainerHill_Entrance_OnReturn:
	addobject LOCALID_NURSE
	addobject LOCALID_ATTENDANT
	addobject LOCALID_MAN
	addobject LOCALID_GIRL
	end

TrainerHill_Entrance_OnLoad:
	call_if_eq VAR_TEMP_D, 17, TrainerHill_Entrance_EventScript_OpenCounterDoor
	end

TrainerHill_Entrance_EventScript_OpenCounterDoor::
	setmetatile 17, 10, METATILE_TrainerHill_GreenFloorTile, FALSE
	return

TrainerHill_Entrance_OnFrame:
	map_script_2 VAR_TEMP_0, 0, TrainerHill_Entrance_EventScript_ExitChallenge
	map_script_2 VAR_TEMP_D, 17, TrainerHill_Entrance_EventScript_ExitElevator
	map_script_2 VAR_TEMP_5, 1, TrainerHill_Entrance_EventScript_EntryTrigger
	map_script_2 VAR_TEMP_1, 1, TrainerHill_EventScript_WarpToEntranceCounter
	.2byte 0

TrainerHill_Entrance_EventScript_ExitElevator::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerExitElevator
	waitmovement 0
	setmetatile 17, 10, METATILE_TrainerHill_CounterDoor, TRUE
	special DrawWholeMapView
	playse SE_CLICK
	waitse
	setvar VAR_TEMP_D, 0
	releaseall
	end

TrainerHill_Entrance_EventScript_ExitChallenge::
	setvar VAR_TEMP_0, 1
	trainerhill_getstatus
	switch VAR_RESULT
	case TRAINER_HILL_PLAYER_STATUS_LOST, TrainerHill_Entrance_EventScript_ExitChallengeLost
	case TRAINER_HILL_PLAYER_STATUS_ECARD_SCANNED, TrainerHill_Entrance_EventScript_ExitChallengeECard
	case TRAINER_HILL_PLAYER_STATUS_NORMAL, TrainerHill_Entrance_EventScript_EndExitChallenge

TrainerHill_Entrance_EventScript_ExitChallengeLost::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	msgbox TrainerHill_Entrance_Text_TooBadTremendousEffort, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_PlayerExitChallenge

TrainerHill_Entrance_EventScript_ExitChallengeECard::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	msgbox TrainerHill_Entrance_Text_MovedReceptionHereForSwitch, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_PlayerExitChallenge::
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	setvar VAR_TRAINER_HILL_IS_ACTIVE, 0
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	releaseall
TrainerHill_Entrance_EventScript_EndExitChallenge::
	end

TrainerHill_Entrance_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

TrainerHill_Entrance_EventScript_Attendant::
	lock
	faceplayer
	trainerhill_inchallenge
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_ThanksForPlaying
	msgbox TrainerHill_Entrance_Text_HopeYouGiveItYourBest, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AttendantEnd

TrainerHill_Entrance_EventScript_ThanksForPlaying::
	msgbox TrainerHill_Entrance_Text_ThankYouForPlaying, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_AttendantEnd::
	release
	end

TrainerHill_Entrance_EventScript_EntryTrigger::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_Closed
	msgbox TrainerHill_Entrance_Text_WelcomeToTrainerHill, MSGBOX_DEFAULT
	trainerhill_getsaved
	call_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_SaveGame
	trainerhill_allfloorsused
	goto_if_eq VAR_RESULT, TRUE, TrainerHill_Entrance_EventScript_AllFloorsUsed
	msgbox TrainerHill_Entrance_Text_TrainersUpToFloorX, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AskChallengeTrainers

TrainerHill_Entrance_EventScript_AllFloorsUsed::
	msgbox TrainerHill_Entrance_Text_TrainersInEveryRoom, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_AskChallengeTrainers::
	message TrainerHill_Entrance_Text_LikeToChallengeTrainers
	waitmessage
	multichoice 15, 6, MULTI_YESNOINFO, FALSE
	switch VAR_RESULT
	case 0, TrainerHill_Entrance_EventScript_ChooseChallenge
	case 1, TrainerHill_Entrance_EventScript_CancelEntry
	case 2, TrainerHill_Entrance_EventScript_Info
	case MULTI_B_PRESSED, TrainerHill_Entrance_EventScript_CancelEntry
	end

TrainerHill_Entrance_EventScript_Info::
	msgbox TrainerHill_Entrance_Text_ExplainTrainerHill, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AskChallengeTrainers
	end

TrainerHill_Entrance_EventScript_ChooseChallenge::
	multichoice 13, 2, MULTI_TAG_MATCH_TYPE, FALSE
	switch VAR_RESULT
	case 4, TrainerHill_Entrance_EventScript_CancelEntry
	case MULTI_B_PRESSED, TrainerHill_Entrance_EventScript_CancelEntry
	trainerhill_setmode VAR_RESULT
	setvar VAR_TRAINER_HILL_IS_ACTIVE, 1
	setvar VAR_TEMP_5, 0
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	msgbox TrainerHill_Entrance_Text_TimeProgessGetSetGo, MSGBOX_DEFAULT
	trainerhill_start
	releaseall
	end

TrainerHill_Entrance_EventScript_CancelEntry::
	setvar VAR_TEMP_5, 0
	msgbox TrainerHill_Entrance_Text_PleaseVisitUsAgain, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

TrainerHill_Entrance_EventScript_SaveGame::
	msgbox TrainerHill_Entrance_Text_SaveGameBeforeEnter, MSGBOX_DEFAULT
	trainerhill_setsaved
	setvar VAR_TEMP_5, 1
	call Common_EventScript_SaveGame
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_SaveFailed
	trainerhill_setsaved
	return

TrainerHill_Entrance_EventScript_SaveFailed::
	trainerhill_clearsaved
	goto TrainerHill_Entrance_EventScript_CancelEntry
	end

TrainerHill_Entrance_EventScript_Closed::
	msgbox TrainerHill_Entrance_Text_StillGettingReady, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

TrainerHill_Entrance_Movement_PlayerFaceAttendant:
	face_right
	step_end

TrainerHill_Entrance_Movement_PushPlayerBackFromCounter:
	walk_down
	step_end

@ Unused
TrainerHill_Entrance_Movement_FaceUp:
	face_up
	step_end

TrainerHill_Entrance_Movement_PlayerExitElevator:
	walk_down
	walk_down
	step_end

TrainerHill_Entrance_EventScript_Records::
	lockall
	fadescreen FADE_TO_BLACK
	special ShowTrainerHillRecords
	waitstate
	releaseall
	end

TrainerHill_Entrance_EventScript_Man::
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_ManTrainerHillClosed
	msgbox TrainerHill_Entrance_Text_WhatSortOfTrainersAreAhead, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_ManTrainerHillClosed::
	msgbox TrainerHill_Entrance_Text_CantWaitToTestTheWaters, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_Girl::
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_GirlTrainerHillClosed
	msgbox TrainerHill_Entrance_Text_FriendsTryingToReachTimeBoardTop, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_GirlTrainerHillClosed::
	msgbox TrainerHill_Entrance_Text_DoYouKnowWhenTheyOpen, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_set FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_ExpandedPokemart
	pokemart TrainerHill_Entrance_Pokemart_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
TrainerHill_Entrance_Pokemart_Basic:
	.2byte ITEM_POKE_BALL 
	.2byte ITEM_GREAT_BALL 
	.2byte ITEM_ULTRA_BALL 
	.2byte ITEM_HEAL_BALL 
	.2byte ITEM_NET_BALL 
	.2byte ITEM_NEST_BALL 
	.2byte ITEM_DIVE_BALL 
	.2byte ITEM_DUSK_BALL 
	.2byte ITEM_TIMER_BALL 
	.2byte ITEM_QUICK_BALL 
	.2byte ITEM_REPEAT_BALL 
	.2byte ITEM_LUXURY_BALL 
	.2byte ITEM_LEVEL_BALL 
	.2byte ITEM_LURE_BALL 
	.2byte ITEM_MOON_BALL 
	.2byte ITEM_FRIEND_BALL 
	.2byte ITEM_LOVE_BALL 
	.2byte ITEM_FAST_BALL 
	.2byte ITEM_HEAVY_BALL 
	.2byte ITEM_DREAM_BALL 
	.2byte ITEM_BEAST_BALL 
	.2byte ITEM_POTION 
	.2byte ITEM_SUPER_POTION 
	.2byte ITEM_HYPER_POTION 
	.2byte ITEM_MAX_POTION 
	.2byte ITEM_FULL_RESTORE 
	.2byte ITEM_REVIVE 
	.2byte ITEM_MAX_REVIVE 
	.2byte ITEM_HP_UP 
	.2byte ITEM_PROTEIN 
	.2byte ITEM_IRON 
	.2byte ITEM_CALCIUM 
	.2byte ITEM_ZINC 
	.2byte ITEM_CARBOS 
	.2byte ITEM_PP_UP 
	.2byte ITEM_PP_MAX 
	.2byte ITEM_ABILITY_CAPSULE 
	.2byte ITEM_ABILITY_PATCH 
	.2byte ITEM_LONELY_MINT 
	.2byte ITEM_ADAMANT_MINT 
	.2byte ITEM_NAUGHTY_MINT 
	.2byte ITEM_BRAVE_MINT 
	.2byte ITEM_BOLD_MINT 
	.2byte ITEM_IMPISH_MINT 
	.2byte ITEM_LAX_MINT 
	.2byte ITEM_RELAXED_MINT 
	.2byte ITEM_MODEST_MINT 
	.2byte ITEM_MILD_MINT 
	.2byte ITEM_RASH_MINT 
	.2byte ITEM_QUIET_MINT 
	.2byte ITEM_CALM_MINT 
	.2byte ITEM_GENTLE_MINT 
	.2byte ITEM_CAREFUL_MINT 
	.2byte ITEM_SASSY_MINT 
	.2byte ITEM_TIMID_MINT 
	.2byte ITEM_HASTY_MINT 
	.2byte ITEM_JOLLY_MINT 
	.2byte ITEM_NAIVE_MINT 
	.2byte ITEM_SERIOUS_MINT 
	.2byte ITEM_X_ATTACK 
	.2byte ITEM_X_DEFENSE 
	.2byte ITEM_X_DEFEND 
	.2byte ITEM_X_SP_ATK 
	.2byte ITEM_X_SPECIAL 
	.2byte ITEM_X_SP_DEF 
	.2byte ITEM_X_SPEED 
	.2byte ITEM_X_ACCURACY 
	.2byte ITEM_DIRE_HIT 
	.2byte ITEM_GUARD_SPEC 
	.2byte ITEM_HELIX_FOSSIL 
	.2byte ITEM_DOME_FOSSIL 
	.2byte ITEM_OLD_AMBER 
	.2byte ITEM_ROOT_FOSSIL 
	.2byte ITEM_CLAW_FOSSIL 
	.2byte ITEM_ARMOR_FOSSIL 
	.2byte ITEM_SKULL_FOSSIL 
	.2byte ITEM_COVER_FOSSIL 
	.2byte ITEM_PLUME_FOSSIL 
	.2byte ITEM_JAW_FOSSIL 
	.2byte ITEM_SAIL_FOSSIL 
	.2byte ITEM_FOSSILIZED_BIRD 
	.2byte ITEM_FOSSILIZED_FISH 
	.2byte ITEM_FOSSILIZED_DRAKE 
	.2byte ITEM_FOSSILIZED_DINO 
	.2byte ITEM_FIRE_STONE 
	.2byte ITEM_WATER_STONE 
	.2byte ITEM_THUNDER_STONE 
	.2byte ITEM_THUNDERSTONE
	.2byte ITEM_LEAF_STONE 
	.2byte ITEM_ICE_STONE 
	.2byte ITEM_SUN_STONE 
	.2byte ITEM_MOON_STONE 
	.2byte ITEM_SHINY_STONE 
	.2byte ITEM_DUSK_STONE 
	.2byte ITEM_DAWN_STONE 
	.2byte ITEM_SWEET_APPLE 
	.2byte ITEM_TART_APPLE 
	.2byte ITEM_CRACKED_POT 
	.2byte ITEM_CHIPPED_POT 
	.2byte ITEM_GALARICA_CUFF 
	.2byte ITEM_GALARICA_WREATH 
	.2byte ITEM_DRAGON_SCALE 
	.2byte ITEM_UPGRADE 
	.2byte ITEM_UP_GRADE
	.2byte ITEM_PROTECTOR 
	.2byte ITEM_ELECTIRIZER 
	.2byte ITEM_MAGMARIZER 
	.2byte ITEM_DUBIOUS_DISC 
	.2byte ITEM_REAPER_CLOTH 
	.2byte ITEM_PRISM_SCALE 
	.2byte ITEM_WHIPPED_DREAM 
	.2byte ITEM_SACHET 
	.2byte ITEM_OVAL_STONE 
	.2byte ITEM_STRAWBERRY_SWEET 
	.2byte ITEM_LOVE_SWEET 
	.2byte ITEM_BERRY_SWEET 
	.2byte ITEM_CLOVER_SWEET 
	.2byte ITEM_FLOWER_SWEET 
	.2byte ITEM_STAR_SWEET 
	.2byte ITEM_RIBBON_SWEET 
	.2byte ITEM_EVERSTONE 
	.2byte ITEM_VENUSAURITE 
	.2byte ITEM_VENUSAURITE_X 
	.2byte ITEM_CHARIZARDITE_X 
	.2byte ITEM_CHARIZARDITE_Y 
	.2byte ITEM_CHARIZARDITE_Z 
	.2byte ITEM_BLASTOISINITE 
	.2byte ITEM_BLASTOISINITE_X
	.2byte ITEM_BUTTERFITE
	.2byte ITEM_MACHAMPITE
	.2byte ITEM_GENGARITE_X
	.2byte ITEM_KINGLERITE
	.2byte ITEM_LAPRASITE
	.2byte ITEM_SNORLAXITE
	.2byte ITEM_GARBODORITE
	.2byte ITEM_MELMETALITE
	.2byte ITEM_RILLABITE
	.2byte ITEM_CINDERITE
	.2byte ITEM_INTELITE
	.2byte ITEM_CORVIKNITE
	.2byte ITEM_ORBITE
	.2byte ITEM_DREDNITE
	.2byte ITEM_COALOSSALITE
	.2byte ITEM_FLAPPLITE
	.2byte ITEM_APPLITE
	.2byte ITEM_SANDITE
	.2byte ITEM_TOXTRITE
	.2byte ITEM_CENTITE
	.2byte ITEM_HATTERITE
	.2byte ITEM_ALCREMITE
	.2byte ITEM_COPPERITE
	.2byte ITEM_URSHITE
	.2byte ITEM_URSHITE_R
	.2byte ITEM_GRIMMITE
	.2byte ITEM_BEEDRILLITE 
	.2byte ITEM_PIDGEOTITE 
	.2byte ITEM_ALAKAZITE 
	.2byte ITEM_SLOWBRONITE 
	.2byte ITEM_GENGARITE 
	.2byte ITEM_KANGASKHANITE 
	.2byte ITEM_PINSIRITE 
	.2byte ITEM_GYARADOSITE 
	.2byte ITEM_AERODACTYLITE 
	.2byte ITEM_MEWTWONITE_X 
	.2byte ITEM_MEWTWONITE_Y 
	.2byte ITEM_AMPHAROSITE 
	.2byte ITEM_STEELIXITE 
	.2byte ITEM_SCIZORITE 
	.2byte ITEM_HERACRONITE 
	.2byte ITEM_HOUNDOOMINITE 
	.2byte ITEM_TYRANITARITE 
	.2byte ITEM_SCEPTILITE 
	.2byte ITEM_BLAZIKENITE 
	.2byte ITEM_SWAMPERTITE 
	.2byte ITEM_GARDEVOIRITE 
	.2byte ITEM_SABLENITE 
	.2byte ITEM_MAWILITE 
	.2byte ITEM_AGGRONITE 
	.2byte ITEM_MEDICHAMITE 
	.2byte ITEM_MANECTITE 
	.2byte ITEM_SHARPEDONITE 
	.2byte ITEM_CAMERUPTITE 
	.2byte ITEM_ALTARIANITE 
	.2byte ITEM_BANETTITE 
	.2byte ITEM_ABSOLITE 
	.2byte ITEM_GLALITITE 
	.2byte ITEM_SALAMENCITE 
	.2byte ITEM_METAGROSSITE 
	.2byte ITEM_LATIASITE 
	.2byte ITEM_LATIOSITE 
	.2byte ITEM_LOPUNNITE 
	.2byte ITEM_GARCHOMPITE 
	.2byte ITEM_LUCARIONITE 
	.2byte ITEM_ABOMASITE 
	.2byte ITEM_GALLADITE 
	.2byte ITEM_AUDINITE 
	.2byte ITEM_DIANCITE 
	.2byte ITEM_NORMAL_GEM 
	.2byte ITEM_FIRE_GEM 
	.2byte ITEM_WATER_GEM 
	.2byte ITEM_ELECTRIC_GEM 
	.2byte ITEM_GRASS_GEM 
	.2byte ITEM_ICE_GEM 
	.2byte ITEM_FIGHTING_GEM 
	.2byte ITEM_POISON_GEM 
	.2byte ITEM_GROUND_GEM 
	.2byte ITEM_FLYING_GEM 
	.2byte ITEM_PSYCHIC_GEM 
	.2byte ITEM_BUG_GEM 
	.2byte ITEM_ROCK_GEM 
	.2byte ITEM_GHOST_GEM 
	.2byte ITEM_DRAGON_GEM 
	.2byte ITEM_DARK_GEM 
	.2byte ITEM_STEEL_GEM 
	.2byte ITEM_FAIRY_GEM 
	.2byte ITEM_NORMALIUM_Z 
	.2byte ITEM_FIRIUM_Z
	.2byte ITEM_WATERIUM_Z
	.2byte ITEM_ELECTRIUM_Z 
	.2byte ITEM_GRASSIUM_Z 
	.2byte ITEM_ICIUM_Z 
	.2byte ITEM_FIGHTINIUM_Z 
	.2byte ITEM_POISONIUM_Z 
	.2byte ITEM_GROUNDIUM_Z 
	.2byte ITEM_FLYINIUM_Z 
	.2byte ITEM_PSYCHIUM_Z 
	.2byte ITEM_BUGINIUM_Z 
	.2byte ITEM_ROCKIUM_Z 
	.2byte ITEM_GHOSTIUM_Z 
	.2byte ITEM_DRAGONIUM_Z 
	.2byte ITEM_DARKINIUM_Z 
	.2byte ITEM_STEELIUM_Z 
	.2byte ITEM_FAIRIUM_Z 
	.2byte ITEM_PIKANIUM_Z 
	.2byte ITEM_EEVIUM_Z 
	.2byte ITEM_SNORLIUM_Z 
	.2byte ITEM_MEWNIUM_Z 
	.2byte ITEM_DECIDIUM_Z 
	.2byte ITEM_INCINIUM_Z 
	.2byte ITEM_PRIMARIUM_Z 
	.2byte ITEM_LYCANIUM_Z 
	.2byte ITEM_MIMIKIUM_Z 
	.2byte ITEM_KOMMONIUM_Z 
	.2byte ITEM_TAPUNIUM_Z 
	.2byte ITEM_SOLGANIUM_Z 
	.2byte ITEM_LUNALIUM_Z 
	.2byte ITEM_MARSHADIUM_Z 
	.2byte ITEM_ALORAICHIUM_Z 
	.2byte ITEM_PIKASHUNIUM_Z 
	.2byte ITEM_ULTRANECROZIUM_Z 
	.2byte ITEM_SILK_SCARF 
	.2byte ITEM_CHARCOAL 
	.2byte ITEM_MYSTIC_WATER 
	.2byte ITEM_MAGNET 
	.2byte ITEM_MIRACLE_SEED 
	.2byte ITEM_NEVER_MELT_ICE 
	.2byte ITEM_NEVERMELTICE 
	.2byte ITEM_BLACK_BELT 
	.2byte ITEM_BLACKBELT 
	.2byte ITEM_POISON_BARB 
	.2byte ITEM_SOFT_SAND 
	.2byte ITEM_SHARP_BEAK 
	.2byte ITEM_TWISTED_SPOON 
	.2byte ITEM_TWISTEDSPOON 
	.2byte ITEM_SILVER_POWDER 
	.2byte ITEM_SILVERPOWDER 
	.2byte ITEM_HARD_STONE 
	.2byte ITEM_SPELL_TAG 
	.2byte ITEM_DRAGON_FANG 
	.2byte ITEM_BLACK_GLASSES 
	.2byte ITEM_BLACKGLASSES 
	.2byte ITEM_METAL_COAT 
	.2byte ITEM_CHOICE_BAND 
	.2byte ITEM_CHOICE_SPECS 
	.2byte ITEM_CHOICE_SCARF 
	.2byte ITEM_FLAME_ORB 
	.2byte ITEM_TOXIC_ORB 
	.2byte ITEM_DAMP_ROCK 
	.2byte ITEM_HEAT_ROCK 
	.2byte ITEM_SMOOTH_ROCK 
	.2byte ITEM_ICY_ROCK 
	.2byte ITEM_ELECTRIC_SEED 
	.2byte ITEM_PSYCHIC_SEED 
	.2byte ITEM_MISTY_SEED 
	.2byte ITEM_GRASSY_SEED 
	.2byte ITEM_ABSORB_BULB 
	.2byte ITEM_CELL_BATTERY 
	.2byte ITEM_LUMINOUS_MOSS 
	.2byte ITEM_SNOWBALL 
	.2byte ITEM_BRIGHT_POWDER 
	.2byte ITEM_BRIGHTPOWDER 
	.2byte ITEM_WHITE_HERB 
	.2byte ITEM_QUICK_CLAW 
	.2byte ITEM_SOOTHE_BELL 
	.2byte ITEM_MENTAL_HERB 
	.2byte ITEM_KINGS_ROCK 
	.2byte ITEM_AMULET_COIN 
	.2byte ITEM_CLEANSE_TAG 
	.2byte ITEM_SMOKE_BALL 
	.2byte ITEM_FOCUS_BAND 
	.2byte ITEM_LUCKY_EGG 
	.2byte ITEM_SCOPE_LENS 
	.2byte ITEM_LEFTOVERS 
	.2byte ITEM_SHELL_BELL 
	.2byte ITEM_WIDE_LENS 
	.2byte ITEM_MUSCLE_BAND 
	.2byte ITEM_WISE_GLASSES 
	.2byte ITEM_EXPERT_BELT 
	.2byte ITEM_LIGHT_CLAY 
	.2byte ITEM_LIFE_ORB 
	.2byte ITEM_POWER_HERB 
	.2byte ITEM_FOCUS_SASH
	.2byte ITEM_ZOOM_LENS 
	.2byte ITEM_METRONOME 
	.2byte ITEM_IRON_BALL 
	.2byte ITEM_LAGGING_TAIL 
	.2byte ITEM_DESTINY_KNOT 
	.2byte ITEM_BLACK_SLUDGE 
	.2byte ITEM_GRIP_CLAW 
	.2byte ITEM_STICKY_BARB 
	.2byte ITEM_SHED_SHELL 
	.2byte ITEM_BIG_ROOT 
	.2byte ITEM_RAZOR_CLAW 
	.2byte ITEM_RAZOR_FANG 
	.2byte ITEM_EVIOLITE 
	.2byte ITEM_FLOAT_STONE
	.2byte ITEM_ROCKY_HELMET 
	.2byte ITEM_AIR_BALLOON 
	.2byte ITEM_RED_CARD 
	.2byte ITEM_RING_TARGET 
	.2byte ITEM_BINDING_BAND 
	.2byte ITEM_EJECT_BUTTON 
	.2byte ITEM_WEAKNESS_POLICY 
	.2byte ITEM_ASSAULT_VEST 
	.2byte ITEM_SAFETY_GOGGLES 
	.2byte ITEM_ADRENALINE_ORB 
	.2byte ITEM_TERRAIN_EXTENDER 
	.2byte ITEM_PROTECTIVE_PADS 
	.2byte ITEM_THROAT_SPRAY 
	.2byte ITEM_EJECT_PACK 
	.2byte ITEM_HEAVY_DUTY_BOOTS 
	.2byte ITEM_BLUNDER_POLICY 
	.2byte ITEM_ROOM_SERVICE 
	.2byte ITEM_UTILITY_UMBRELLA 
	pokemartlistend

TrainerHill_Entrance_EventScript_ExpandedPokemart::
	pokemart TrainerHill_Entrance_Pokemart_Expanded
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
TrainerHill_Entrance_Pokemart_Expanded:
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SP_ATK
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_X_ACCURACY
	pokemartlistend

TrainerHill_Entrance_Text_StillGettingReady:
	.string "This is the TRAINER HILL where\n"
	.string "you may enjoy tag battles with many\l"
	.string "TRAINERS.\p"
	.string "Unfortunately, we're still getting\n"
	.string "things ready. Please come back later!$"

TrainerHill_Entrance_Text_WelcomeToTrainerHill:
	.string "Welcome!\p"
	.string "This is the TRAINER HILL where\n"
	.string "you may enjoy tag battles with many\l"
	.string "TRAINERS!$"

TrainerHill_Entrance_Text_SaveGameBeforeEnter:
	.string "Is this your first visit here?\p"
	.string "Before you enter, please save\n"
	.string "your game.$"

TrainerHill_Entrance_Text_TrainersUpToFloorX:
	.string "Let's see…\n"
	.string "The TRAINERS here now are…\p"
	.string "Up to floor no. {STR_VAR_1}.$"

TrainerHill_Entrance_Text_TrainersInEveryRoom:
	.string "Let's see…\n"
	.string "The TRAINERS here now are…\p"
	.string "There appear to be TRAINERS gathered\n"
	.string "in every room.$"

TrainerHill_Entrance_Text_LikeToChallengeTrainers:
	.string "Would you like to challenge the\n"
	.string "waiting TRAINERS?$"

TrainerHill_Entrance_Text_TimeProgessGetSetGo:
	.string "I will time your progress.\n"
	.string "Best of luck!\p"
	.string "On your marks…\p"
	.string "Get set…\p"
	.string "Go!$"

TrainerHill_Entrance_Text_PleaseVisitUsAgain:
	.string "Please do visit us again!$"

TrainerHill_Entrance_Text_TooBadTremendousEffort:
	.string "That was too bad.\p"
	.string "I think you put in a tremendous\n"
	.string "effort in your battling.\p"
	.string "Please come back and try again!$"

TrainerHill_Entrance_Text_HopeYouGiveItYourBest:
	.string "I hope you give it your best.$"

TrainerHill_Entrance_Text_MovedReceptionHereForSwitch:
	.string "When the TRAINERS switch places,\n"
	.string "the movement can be hectic.\p"
	.string "To avoid the stampede, we moved\n"
	.string "the reception counter here.\p"
	.string "I'm sorry for the inconvenience.$"

TrainerHill_Entrance_Text_ThankYouForPlaying:
	.string "Thank you for playing!$"

TrainerHill_Entrance_Text_ExplainTrainerHill:
	.string "Here at the TRAINER HILL, we conduct\n"
	.string "an event called the Time Attack.\p"
	.string "It is a race that measures how long\n"
	.string "you take to reach our owner on\l"
	.string "the rooftop from this counter.\p"
	.string "The fastest times are posted on\n"
	.string "the Time Board--try competing with\l"
	.string "your friends.\p"
	.string "In TRAINER battles along the way,\n"
	.string "neither Exp. Points nor money will\l"
	.string "be awarded.$"

@ Unused
TrainerHill_Entrance_Text_NeedAtLeastTwoPokemon:
	.string "Oh, I'm sorry, but you appear to have\n"
	.string "only one POKéMON with you.\p"
	.string "You will need at least two POKéMON\n"
	.string "to enter this event.$"

TrainerHill_Roof_Text_YouFinallyCameBravo:
	.string "Hm! Hm!\p"
	.string "You finally came!\n"
	.string "Yes, you have arrived!\p"
	.string "Wait! Don't say it!\n"
	.string "I know why you came all the way\l"
	.string "here by yourself!\p"
	.string "You wanted to see me, the owner\n"
	.string "of the TRAINER HILL, because…\p"
	.string "You want to form a tag team with me!\n"
	.string "Wa-hoo!\p"
	.string "…Uh?\n"
	.string "That's not it?\p"
	.string "Anyway, I watched you on your way up.\n"
	.string "Marvelous battling! Bravo, indeed!$"

TrainerHill_Roof_Text_HaveTheMostMarvelousGift:
	.string "For a marvelous someone like you,\n"
	.string "I have the most marvelous gift!$"

TrainerHill_Roof_Text_FullUpBeBackLaterForThis:
	.string "Oh, no, full up with things!\n"
	.string "You'll be back later for this!$"

TrainerHill_Roof_Text_GotHereMarvelouslyQuickly:
	.string "Oh, hold on here! Did you possibly get\n"
	.string "here marvelously quickly?\p"
	.string "How splendid! You needn't have\n"
	.string "hurried so to see me!\p"
	.string "That is so delightful. I'll have the Time\n"
	.string "Board at the reception updated!$"

TrainerHill_Roof_Text_YouWerentVeryQuick:
	.string "But, oh…\n"
	.string "You weren't very quick getting here.$"

TrainerHill_Roof_Text_ArriveZippierNextTime:
	.string "Perhaps it would please me more if you\n"
	.string "arrived zippier next time.\p"
	.string "Then, I should be pleased to form\n"
	.string "a tag team with you!\p"
	.string "Until we meet again, amigo!$"

@ Unused
TrainerHill_Roof_Text_BuiltTrainerHillToFindPartner:
	.string "I had the TRAINER HILL built for but\n"
	.string "one reason and one only!\p"
	.string "To find the most suitable partner\n"
	.string "with whom I may form a tag team!$"

TrainerHill_Entrance_Text_ChallengeTime:
	.string "{STR_VAR_1} min. {STR_VAR_2}.{STR_VAR_3} sec.$"

TrainerHill_Entrance_Text_WhatSortOfTrainersAreAhead:
	.string "Who knows what sort of TRAINERS\n"
	.string "and POKéMON combos are ahead?\p"
	.string "All I know is that I'll knock aside\n"
	.string "anyone that stands in my way!$"

TrainerHill_Entrance_Text_CantWaitToTestTheWaters:
	.string "I heard tough TRAINERS come to this\n"
	.string "TRAINER HILL from all over.\p"
	.string "I can't wait to test the waters!\p"
	.string "I'll knock aside anyone that stands\n"
	.string "in my way!$"

TrainerHill_Entrance_Text_FriendsTryingToReachTimeBoardTop:
	.string "Do you see the Time Board over there?\p"
	.string "My friends and I are trying to see who\n"
	.string "can reach the top in the least time.$"

TrainerHill_Entrance_Text_DoYouKnowWhenTheyOpen:
	.string "Do you know when they're opening\n"
	.string "this place up?\p"
	.string "I'm waiting here to be the first\n"
	.string "challenger ever!$"

TrainerHill_Elevator_Text_ReturnToReception:
	.string "Would you like to return to\n"
	.string "the reception counter?$"
