.set LOCALID_NURSE, 1
.set LOCALID_GUARD_1, 3
.set LOCALID_GUARD_2, 4

EverGrandeCity_PokemonLeague_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_PokemonLeague_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

EverGrandeCity_PokemonLeague_1F_OnTransition:
	setrespawn HEAL_LOCATION_EVER_GRANDE_CITY_POKEMON_LEAGUE
	setflag FLAG_LANDMARK_POKEMON_LEAGUE
	call_if_unset FLAG_ENTERED_ELITE_FOUR, EverGrandeCity_PokemonLeague_1F_EventScript_GuardsBlockDoor
	end

EverGrandeCity_PokemonLeague_1F_EventScript_GuardsBlockDoor::
	setobjectxyperm LOCALID_GUARD_1, 9, 2
	setobjectxyperm LOCALID_GUARD_2, 10, 2
	return

EverGrandeCity_PokemonLeague_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

EverGrandeCity_PokemonLeague_1F_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart EverGrandeCity_PokemonLeague_1F_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
EverGrandeCity_PokemonLeague_1F_Pokemart:
	.2byte ITEM_POKE_BALL 
	.2byte ITEM_GREAT_BALL 
	.2byte ITEM_ULTRA_BALL 
	.2byte ITEM_MASTER_BALL 
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
	.2byte ITEM_TM01 
	.2byte ITEM_TM02 
	.2byte ITEM_TM03 
	.2byte ITEM_TM04 
	.2byte ITEM_TM05 
	.2byte ITEM_TM06 
	.2byte ITEM_TM07 
	.2byte ITEM_TM08 
	.2byte ITEM_TM09 
	.2byte ITEM_TM10 
	.2byte ITEM_TM11 
	.2byte ITEM_TM12 
	.2byte ITEM_TM13 
	.2byte ITEM_TM14 
	.2byte ITEM_TM15 
	.2byte ITEM_TM16 
	.2byte ITEM_TM17 
	.2byte ITEM_TM18 
	.2byte ITEM_TM19
	.2byte ITEM_TM20 
	.2byte ITEM_TM21 
	.2byte ITEM_TM22 
	.2byte ITEM_TM23 
	.2byte ITEM_TM24 
	.2byte ITEM_TM25 
	.2byte ITEM_TM26 
	.2byte ITEM_TM27 
	.2byte ITEM_TM28 
	.2byte ITEM_TM29 
	.2byte ITEM_TM30 
	.2byte ITEM_TM31 
	.2byte ITEM_TM32 
	.2byte ITEM_TM33 
	.2byte ITEM_TM34 
	.2byte ITEM_TM35 
	.2byte ITEM_TM36 
	.2byte ITEM_TM37 
	.2byte ITEM_TM38 
	.2byte ITEM_TM39 
	.2byte ITEM_TM40 
	.2byte ITEM_TM41 
	.2byte ITEM_TM42 
	.2byte ITEM_TM43 
	.2byte ITEM_TM44 
	.2byte ITEM_TM45 
	.2byte ITEM_TM46 
	.2byte ITEM_TM47 
	.2byte ITEM_TM48 
	.2byte ITEM_TM49 
	.2byte ITEM_TM50 
	.2byte ITEM_TM51 
	.2byte ITEM_TM52 
	.2byte ITEM_TM53 
	.2byte ITEM_TM54 
	.2byte ITEM_TM55 
	.2byte ITEM_TM56 
	.2byte ITEM_TM57 
	.2byte ITEM_TM58 
	.2byte ITEM_TM59 
	.2byte ITEM_TM60 
	.2byte ITEM_TM61 
	.2byte ITEM_TM62 
	.2byte ITEM_TM63 
	.2byte ITEM_TM64 
	.2byte ITEM_TM65 
	.2byte ITEM_TM66 
	.2byte ITEM_TM67 
	.2byte ITEM_TM68 
	.2byte ITEM_TM69 
	.2byte ITEM_TM70 
	.2byte ITEM_TM71 
	.2byte ITEM_TM72 
	.2byte ITEM_TM73 
	.2byte ITEM_TM74 
	.2byte ITEM_TM75 
	.2byte ITEM_TM76 
	.2byte ITEM_TM77 
	.2byte ITEM_TM78 
	.2byte ITEM_TM79 
	.2byte ITEM_TM80 
	.2byte ITEM_TM81 
	.2byte ITEM_TM82 
	.2byte ITEM_TM83 
	.2byte ITEM_TM84 
	.2byte ITEM_TM85 
	.2byte ITEM_TM86 
	.2byte ITEM_TM87 
	.2byte ITEM_TM88 
	.2byte ITEM_TM89 
	.2byte ITEM_TM90 
	.2byte ITEM_TM91 
	.2byte ITEM_TM92 
	.2byte ITEM_TM93 
	.2byte ITEM_TM94 
	.2byte ITEM_TM95 
	.2byte ITEM_TM96 
	.2byte ITEM_TM97 
	.2byte ITEM_TM98 
	.2byte ITEM_TM99 
	.2byte ITEM_TM100
	.2byte ITEM_MAX_REPEL
	pokemartlistend

@ The door guards only check for FLAG_BADGE06_GET because Winonas badge is the only one that can be skipped
@ Its assumed the player has the remaining badges
EverGrandeCity_PokemonLeague_1F_EventScript_DoorGuard::
	lockall
	goto_if_set FLAG_ENTERED_ELITE_FOUR, EverGrandeCity_PokemonLeague_1F_EventScript_GoForth
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_ge VAR_TEMP_0, 11, EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromRight
	call_if_le VAR_TEMP_0, 8, EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromLeft
	message EverGrandeCity_PokemonLeague_1F_Text_MustHaveAllGymBadges
	waitmessage
	delay 120
	goto_if_unset FLAG_BADGE06_GET, EverGrandeCity_PokemonLeague_1F_EventScript_NotAllBadges
	closemessage
	applymovement LOCALID_GUARD_1, EverGrandeCity_PokemonLeague_1F_Movement_LeftGuardOutOfWay
	applymovement LOCALID_GUARD_2, EverGrandeCity_PokemonLeague_1F_Movement_RightGuardOutOfWay
	waitmovement 0
	delay 10
	playfanfare MUS_OBTAIN_BADGE
	message EverGrandeCity_PokemonLeague_1F_Text_GoForth
	waitmessage
	waitfanfare
	closemessage
	copyobjectxytoperm LOCALID_GUARD_1
	copyobjectxytoperm LOCALID_GUARD_2
	setflag FLAG_ENTERED_ELITE_FOUR
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromRight::
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromRight
	waitmovement 0
	return

EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromLeft::
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromLeft
	waitmovement 0
	return

EverGrandeCity_PokemonLeague_1F_EventScript_NotAllBadges::
	playse SE_FAILURE
	msgbox EverGrandeCity_PokemonLeague_1F_Text_HaventObtainedAllBadges, MSGBOX_DEFAULT
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_EventScript_GoForth::
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox EverGrandeCity_PokemonLeague_1F_Text_GoForth, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromRight:
	walk_down
	walk_left
	walk_in_place_faster_up
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromLeft:
	walk_down
	walk_right
	walk_in_place_faster_up
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_LeftGuardOutOfWay:
	walk_left
	walk_in_place_faster_down
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_RightGuardOutOfWay:
	walk_right
	walk_in_place_faster_down
	step_end

EverGrandeCity_PokemonLeague_1F_Text_MustHaveAllGymBadges:
	.string "Beyond this point, only those TRAINERS\n"
	.string "who have collected all the GYM BADGES\l"
	.string "are permitted to enter.\p"
	.string "TRAINER, let us confirm that you have\n"
	.string "all the GYM BADGES.$"

EverGrandeCity_PokemonLeague_1F_Text_HaventObtainedAllBadges:
	.string "You haven't obtained all the BADGES.\p"
	.string "If you're bound for the POKéMON\n"
	.string "LEAGUE, you must return with them.$"

EverGrandeCity_PokemonLeague_1F_Text_GoForth:
	.string "TRAINER! Believe in yourself and your\n"
	.string "POKéMON, and go forth!$"

