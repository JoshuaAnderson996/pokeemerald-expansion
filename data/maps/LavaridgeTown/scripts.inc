LavaridgeTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LavaridgeTown_OnFrame
	.byte 0

LavaridgeTown_OnTransition:
	setflag FLAG_VISITED_LAVARIDGE_TOWN
	call_if_set FLAG_WHITEOUT_TO_LAVARIDGE, LavaridgeTown_EventScript_ClearLavaridgeWhiteOut
	call_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, LavaridgeTown_EventScript_ShowMtChimneyTrainers
	call Common_EventScript_SetupRivalGfxId
	call Common_EventScript_SetupRivalOnBikeGfxId
	call_if_eq VAR_LAVARIDGE_TOWN_STATE, 1, LavaridgeTown_EventScript_CheckSetRivalPos
	call_if_eq VAR_LAVARIDGE_TOWN_STATE, 1, LavaridgeTown_EventScript_HideMapNamePopup
	end

LavaridgeTown_EventScript_ClearLavaridgeWhiteOut::
	clearflag FLAG_WHITEOUT_TO_LAVARIDGE
	return

LavaridgeTown_EventScript_CheckSetRivalPos::
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8004, 9, LavaridgeTown_EventScript_SetRivalPos
	return

LavaridgeTown_EventScript_SetRivalPos::
	setobjectxyperm LOCALID_LAVARIDGE_RIVAL, 11, 9
	setobjectxyperm LOCALID_LAVARIDGE_RIVAL_ON_BIKE, 9, 8
	setobjectmovementtype LOCALID_LAVARIDGE_RIVAL_ON_BIKE, MOVEMENT_TYPE_FACE_UP
	clearflag FLAG_HIDE_LAVARIDGE_TOWN_RIVAL
	return

LavaridgeTown_EventScript_ShowMtChimneyTrainers::
	clearflag FLAG_HIDE_MT_CHIMNEY_TRAINERS
	return

LavaridgeTown_EventScript_HideMapNamePopup::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

LavaridgeTown_OnFrame:
	map_script_2 VAR_LAVARIDGE_TOWN_STATE, 1, LavaridgeTown_EventScript_RivalGiveGoGoggles
	.2byte 0

LavaridgeTown_EventScript_RivalGiveGoGoggles::
	lockall
	getplayerxy VAR_0x8008, VAR_0x8009
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalNoticePlayer
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExitHerbShop
	delay 20
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LavaridgeTown_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, LavaridgeTown_EventScript_PlayBrendanMusic
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalApproachPlayer1
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalApproachPlayer2
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LavaridgeTown_EventScript_MayGiveGoGoggles
	goto_if_eq VAR_RESULT, FEMALE, LavaridgeTown_EventScript_BrendanGiveGoGoggles
	end

LavaridgeTown_EventScript_MayGiveGoGoggles::
	msgbox LavaridgeTown_Text_MayNiceBadgesTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox LavaridgeTown_Text_MayExplainGoGogglesChallengeDad, MSGBOX_DEFAULT
	goto LavaridgeTown_EventScript_RivalExit
	end

LavaridgeTown_EventScript_BrendanGiveGoGoggles::
	msgbox LavaridgeTown_Text_BrendanNiceBadgesTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox LavaridgeTown_Text_BrendanExplainGoGogglesChallengeDad, MSGBOX_DEFAULT
	goto LavaridgeTown_EventScript_RivalExit
	end

LavaridgeTown_EventScript_RivalExit::
	closemessage
	removeobject LOCALID_LAVARIDGE_RIVAL
	addobject LOCALID_LAVARIDGE_RIVAL_ON_BIKE
	delay 30
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExit1
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExit2
	removeobject LOCALID_LAVARIDGE_RIVAL_ON_BIKE
	setvar VAR_LAVARIDGE_TOWN_STATE, 2
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LavaridgeTown_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	return

LavaridgeTown_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	return

LavaridgeTown_EventScript_RivalNoticePlayer::
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_Delay48
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExitHerbShop::
	opendoor 12, 15
	waitdooranim
	addobject LOCALID_LAVARIDGE_RIVAL
	applymovement LOCALID_LAVARIDGE_RIVAL, LavaridgeTown_Movement_RivalExitHerbShop
	waitmovement 0
	closedoor 12, 15
	waitdooranim
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalApproachPlayer1::
	applymovement LOCALID_LAVARIDGE_RIVAL, LavaridgeTown_Movement_RivalApproachPlayer1
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalApproachPlayer2::
	applymovement LOCALID_LAVARIDGE_RIVAL, LavaridgeTown_Movement_RivalApproachPlayer2
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExit1::
	applymovement LOCALID_PLAYER, LavaridgeTown_Movement_PlayerWatchRivalExit
	applymovement LOCALID_LAVARIDGE_RIVAL_ON_BIKE, LavaridgeTown_Movement_RivalExit1
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExit2::
	applymovement LOCALID_LAVARIDGE_RIVAL_ON_BIKE, LavaridgeTown_Movement_RivalExit2
	waitmovement 0
	return

LavaridgeTown_Movement_RivalExit2:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

LavaridgeTown_Movement_PlayerWatchRivalExit:
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

LavaridgeTown_Movement_RivalExit1:
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

LavaridgeTown_Movement_RivalApproachPlayer2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LavaridgeTown_Movement_RivalApproachPlayer1:
	walk_left
	walk_left
	walk_up
	step_end

LavaridgeTown_Movement_RivalExitHerbShop:
	walk_down
	step_end

LavaridgeTown_EventScript_HotSpringsTrigger::
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_SOUTH, LavaridgeTown_EventScript_EnteredHotSprings
	end

LavaridgeTown_EventScript_EnteredHotSprings::
	incrementgamestat GAME_STAT_ENTERED_HOT_SPRINGS
	end

LavaridgeTown_EventScript_ExpertM::
	msgbox LavaridgeTown_Text_HotSpringsNeverRunDry, MSGBOX_NPC
	end

LavaridgeTown_EventScript_OldMan::
	msgbox LavaridgeTown_Text_PokemonNippedBackside, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_Twin::
	msgbox LavaridgeTown_Text_BatheInHotSpringsEveryDay, MSGBOX_NPC
	end

LavaridgeTown_EventScript_HotSpringsOldWoman1::
	msgbox LavaridgeTown_Text_IfPokemonInHotSprings, MSGBOX_NPC
	end

LavaridgeTown_EventScript_HotSpringsOldWoman2::
	msgbox LavaridgeTown_Text_HotSpringsClaims, MSGBOX_NPC
	end

LavaridgeTown_EventScript_ExpertF::
	msgbox LavaridgeTown_Text_OhYouLikeHotSprings, MSGBOX_NPC
	end

LavaridgeTown_EventScript_EggWoman::
	lock
	faceplayer
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, LavaridgeTown_EventScript_NoRoomForEgg
	msgbox LavaridgeTown_Text_HaveEggWillYouTakeIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LavaridgeTown_EventScript_DeclineEgg
	random 36
	switch VAR_RESULT
	@ --- Baby Pokémon ---
	case 0,  LavaridgeTown_EventScript_GiveEgg_Wynaut
	case 1,  LavaridgeTown_EventScript_GiveEgg_Azurill
	case 2,  LavaridgeTown_EventScript_GiveEgg_Pichu
	case 3,  LavaridgeTown_EventScript_GiveEgg_Cleffa
	case 4,  LavaridgeTown_EventScript_GiveEgg_Igglybuff
	case 5,  LavaridgeTown_EventScript_GiveEgg_Togepi
	case 6,  LavaridgeTown_EventScript_GiveEgg_Tyrogue
	case 7,  LavaridgeTown_EventScript_GiveEgg_Smoochum
	case 8,  LavaridgeTown_EventScript_GiveEgg_Elekid
	case 9,  LavaridgeTown_EventScript_GiveEgg_Magby
	case 10, LavaridgeTown_EventScript_GiveEgg_Munchlax
	case 11, LavaridgeTown_EventScript_GiveEgg_Bonsly
	case 12, LavaridgeTown_EventScript_GiveEgg_MimeJr
	case 13, LavaridgeTown_EventScript_GiveEgg_Happiny
	case 14, LavaridgeTown_EventScript_GiveEgg_Budew
	case 15, LavaridgeTown_EventScript_GiveEgg_Chingling
	case 16, LavaridgeTown_EventScript_GiveEgg_Mantyke
	case 17, LavaridgeTown_EventScript_GiveEgg_Riolu
	@ --- Starters ---
	case 18, LavaridgeTown_EventScript_GiveEgg_Bulbasaur
	case 19, LavaridgeTown_EventScript_GiveEgg_Charmander
	case 20, LavaridgeTown_EventScript_GiveEgg_Squirtle
	case 21, LavaridgeTown_EventScript_GiveEgg_Chikorita
	case 22, LavaridgeTown_EventScript_GiveEgg_Cyndaquil
	case 23, LavaridgeTown_EventScript_GiveEgg_Totodile
	case 24, LavaridgeTown_EventScript_GiveEgg_Treecko
	case 25, LavaridgeTown_EventScript_GiveEgg_Torchic
	case 26, LavaridgeTown_EventScript_GiveEgg_Mudkip
	case 27, LavaridgeTown_EventScript_GiveEgg_Turtwig
	case 28, LavaridgeTown_EventScript_GiveEgg_Chimchar
	case 29, LavaridgeTown_EventScript_GiveEgg_Piplup
	@ --- Rare / Interesting ---
	case 30, LavaridgeTown_EventScript_GiveEgg_Eevee
	case 31, LavaridgeTown_EventScript_GiveEgg_Dratini
	case 32, LavaridgeTown_EventScript_GiveEgg_Larvitar
	case 33, LavaridgeTown_EventScript_GiveEgg_Bagon
	case 34, LavaridgeTown_EventScript_GiveEgg_Gible
	case 35, LavaridgeTown_EventScript_GiveEgg_Phione

@ --- Baby Pokémon ---
LavaridgeTown_EventScript_GiveEgg_Wynaut::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Baby
	waitfanfare
	giveegg SPECIES_WYNAUT
	release
	end

LavaridgeTown_EventScript_GiveEgg_Azurill::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Baby
	waitfanfare
	giveegg SPECIES_AZURILL
	release
	end

LavaridgeTown_EventScript_GiveEgg_Pichu::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Baby
	waitfanfare
	giveegg SPECIES_PICHU
	release
	end

LavaridgeTown_EventScript_GiveEgg_Cleffa::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Baby
	waitfanfare
	giveegg SPECIES_CLEFFA
	release
	end

LavaridgeTown_EventScript_GiveEgg_Igglybuff::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Baby
	waitfanfare
	giveegg SPECIES_IGGLYBUFF
	release
	end

LavaridgeTown_EventScript_GiveEgg_Togepi::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Togepi
	waitfanfare
	giveegg SPECIES_TOGEPI
	release
	end

LavaridgeTown_EventScript_GiveEgg_Tyrogue::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Tyrogue
	waitfanfare
	giveegg SPECIES_TYROGUE
	release
	end

LavaridgeTown_EventScript_GiveEgg_Smoochum::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Baby
	waitfanfare
	giveegg SPECIES_SMOOCHUM
	release
	end

LavaridgeTown_EventScript_GiveEgg_Elekid::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Elekid
	waitfanfare
	giveegg SPECIES_ELEKID
	release
	end

LavaridgeTown_EventScript_GiveEgg_Magby::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Magby
	waitfanfare
	giveegg SPECIES_MAGBY
	release
	end

LavaridgeTown_EventScript_GiveEgg_Munchlax::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Munchlax
	waitfanfare
	giveegg SPECIES_MUNCHLAX
	release
	end

LavaridgeTown_EventScript_GiveEgg_Bonsly::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Baby
	waitfanfare
	giveegg SPECIES_BONSLY
	release
	end

LavaridgeTown_EventScript_GiveEgg_MimeJr::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Baby
	waitfanfare
	giveegg SPECIES_MIME_JR
	release
	end

LavaridgeTown_EventScript_GiveEgg_Happiny::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Baby
	waitfanfare
	giveegg SPECIES_HAPPINY
	release
	end

LavaridgeTown_EventScript_GiveEgg_Budew::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Baby
	waitfanfare
	giveegg SPECIES_BUDEW
	release
	end

LavaridgeTown_EventScript_GiveEgg_Chingling::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Baby
	waitfanfare
	giveegg SPECIES_CHINGLING
	release
	end

LavaridgeTown_EventScript_GiveEgg_Mantyke::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Baby
	waitfanfare
	giveegg SPECIES_MANTYKE
	release
	end

LavaridgeTown_EventScript_GiveEgg_Riolu::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Riolu
	waitfanfare
	giveegg SPECIES_RIOLU
	release
	end

@ --- Starters ---
LavaridgeTown_EventScript_GiveEgg_Bulbasaur::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Starter
	waitfanfare
	giveegg SPECIES_BULBASAUR
	release
	end

LavaridgeTown_EventScript_GiveEgg_Charmander::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Starter
	waitfanfare
	giveegg SPECIES_CHARMANDER
	release
	end

LavaridgeTown_EventScript_GiveEgg_Squirtle::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Starter
	waitfanfare
	giveegg SPECIES_SQUIRTLE
	release
	end

LavaridgeTown_EventScript_GiveEgg_Chikorita::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Starter
	waitfanfare
	giveegg SPECIES_CHIKORITA
	release
	end

LavaridgeTown_EventScript_GiveEgg_Cyndaquil::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Starter
	waitfanfare
	giveegg SPECIES_CYNDAQUIL
	release
	end

LavaridgeTown_EventScript_GiveEgg_Totodile::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Starter
	waitfanfare
	giveegg SPECIES_TOTODILE
	release
	end

LavaridgeTown_EventScript_GiveEgg_Treecko::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Starter
	waitfanfare
	giveegg SPECIES_TREECKO
	release
	end

LavaridgeTown_EventScript_GiveEgg_Torchic::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_StarterFire
	waitfanfare
	giveegg SPECIES_TORCHIC
	release
	end

LavaridgeTown_EventScript_GiveEgg_Mudkip::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Starter
	waitfanfare
	giveegg SPECIES_MUDKIP
	release
	end

LavaridgeTown_EventScript_GiveEgg_Turtwig::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Starter
	waitfanfare
	giveegg SPECIES_TURTWIG
	release
	end

LavaridgeTown_EventScript_GiveEgg_Chimchar::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Starter
	waitfanfare
	giveegg SPECIES_CHIMCHAR
	release
	end

LavaridgeTown_EventScript_GiveEgg_Piplup::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Starter
	waitfanfare
	giveegg SPECIES_PIPLUP
	release
	end

@ --- Rare / Interesting ---
LavaridgeTown_EventScript_GiveEgg_Eevee::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Eevee
	waitfanfare
	giveegg SPECIES_EEVEE
	release
	end

LavaridgeTown_EventScript_GiveEgg_Dratini::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Dratini
	waitfanfare
	giveegg SPECIES_DRATINI
	release
	end

LavaridgeTown_EventScript_GiveEgg_Larvitar::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Larvitar
	waitfanfare
	giveegg SPECIES_LARVITAR
	release
	end

LavaridgeTown_EventScript_GiveEgg_Bagon::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Bagon
	waitfanfare
	giveegg SPECIES_BAGON
	release
	end

LavaridgeTown_EventScript_GiveEgg_Gible::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Gible
	waitfanfare
	giveegg SPECIES_GIBLE
	release
	end

LavaridgeTown_EventScript_GiveEgg_Phione::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_EggGift_Phione
	waitfanfare
	giveegg SPECIES_PHIONE
	release
	end

LavaridgeTown_EventScript_NoRoomForEgg::
	msgbox LavaridgeTown_Text_NoRoomForThisEgg, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_DeclineEgg::
	msgbox LavaridgeTown_Text_AsYouWishThen, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_TownSign::
	msgbox LavaridgeTown_Text_TownSign, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_GymSign::
	msgbox LavaridgeTown_Text_GymSign, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_HerbShopSign::
	msgbox LavaridgeTown_Text_HerbShopSign, MSGBOX_SIGN
	end

LavaridgeTown_Text_MayNiceBadgesTakeThis:
	.string "MAY: {PLAYER}{KUN}! Long time no see!\p"
	.string "Oh? While I visited the hot springs,\n"
	.string "you got the LAVARIDGE GYM BADGE.\p"
	.string "You must have collected\n"
	.string "good POKéMON…\l"
	.string "No, I believe you raised some.\p"
	.string "I guess it would be okay for you to\n"
	.string "have this.$"

LavaridgeTown_Text_MayExplainGoGogglesChallengeDad:
	.string "MAY: With those GO-GOGGLES, you'll\n"
	.string "have no trouble getting through the\l"
	.string "desert near ROUTE 111.\p"
	.string "But, wow, {PLAYER}{KUN}…\n"
	.string "Challenging GYMS…\p"
	.string "You're trying hard because you don't\n"
	.string "want to lose to me, I bet!\p"
	.string "{PLAYER}{KUN}, I think I should challenge\n"
	.string "your dad in PETALBURG GYM.\p"
	.string "See you again!$"

LavaridgeTown_Text_BrendanNiceBadgesTakeThis:
	.string "BRENDAN: {PLAYER}, hey, it's been a while.\n"
	.string "How's it going?\p"
	.string "Hmm…\n"
	.string "That's a decent collection of BADGES.\p"
	.string "All right, then.\n"
	.string "You may as well have this.$"

LavaridgeTown_Text_BrendanExplainGoGogglesChallengeDad:
	.string "BRENDAN: Keep those with you if you're\n"
	.string "planning on going into that desert near\l"
	.string "ROUTE 111.\p"
	.string "There should be some POKéMON that\n"
	.string "are exclusively desert-dwellers.\l"
	.string "You might look around for those.\p"
	.string "As for me…\n"
	.string "I'm considering challenging NORMAN,\l"
	.string "the GYM LEADER of PETALBURG.\p"
	.string "Unlike you, {PLAYER}, your dad looks like\n"
	.string "he really is tough.\p"
	.string "See you around!$"

LavaridgeTown_Text_HaveEggWillYouTakeIt:
	.string "Oh, hello there!\p"
	.string "I keep finding strange EGGs\n"
	.string "washed up near our hot springs…\p"
	.string "I can't keep them all myself.\n"
	.string "Would you take one off my hands?$"

LavaridgeTown_Text_NoRoomForThisEgg:
	.string "Oh? You've too many POKéMON.\n"
	.string "There's no room for this EGG…$"

LavaridgeTown_Text_AsYouWishThen:
	.string "As you wish, then…\p"
	.string "If you have a change of heart about\n"
	.string "hatching this EGG, I will be here.$"

LavaridgeTown_Text_EverySoOftenEggFoundAtDayCare:
	.string "Every so often, an EGG will be found at\n"
	.string "the POKéMON DAY CARE.\p"
	.string "Or at least that's how the rumor goes.$"

LavaridgeTown_Text_HotSpringsNeverRunDry:
	.string "We draw as much hot water as we need,\n"
	.string "and yet the hot springs never run dry.\p"
	.string "Isn't it magical?\p"
	.string "These hot springs appear near active\n"
	.string "volcanoes. Veins of water under the\l"
	.string "ground are heated by magma to well up\l"
	.string "as hot springs.$"

LavaridgeTown_Text_PokemonNippedBackside:
	.string "Being buried in this hot sand is…\n"
	.string "Sigh…\p"
	.string "So warm and heavenly…\p"
	.string "Eh? Gyaah! Ouch!\p"
	.string "A POKéMON nipped my backside!$"

LavaridgeTown_Text_OhYouLikeHotSprings:
	.string "Oh, you like hot springs, do you?\p"
	.string "That's surprising for one as young\n"
	.string "as you.$"

LavaridgeTown_Text_BatheInHotSpringsEveryDay:
	.string "I bathe in the hot springs every day.\p"
	.string "I want to become a beautiful and strong\n"
	.string "GYM LEADER like FLANNERY.$"

LavaridgeTown_Text_IfPokemonInHotSprings:
	.string "If people put POKéMON in hot springs,\n"
	.string "it might be seriously strange.\p"
	.string "Why, it might be an electric bath, or\n"
	.string "a bubble bath, or even a lava bath…$"

LavaridgeTown_Text_HotSpringsClaims:
	.string "They're claiming that these hot springs\n"
	.string "are good for calming nervous tension,\l"
	.string "relieving aching muscles, solving\l"
	.string "romantic problems, and attracting\l"
	.string "money…$"

LavaridgeTown_Text_TownSign:
	.string "LAVARIDGE TOWN\p"
	.string "“POKéMON CENTER HOT SPRINGS\n"
	.string "An excellent place for relaxing!”$"

LavaridgeTown_Text_GymSign:
	.string "LAVARIDGE TOWN POKéMON GYM\n"
	.string "LEADER: FLANNERY\l"
	.string "“One with a fiery passion that burns!”$"

LavaridgeTown_Text_HerbShopSign:
	.string "POKéMON HERB SHOP\n"
	.string "“Bitter taste--better cure!”$"

LavaridgeTown_Text_EggGift_Baby:
    .string "{PLAYER} received the EGG.\p"
    .string "What a cute little EGG!\n"
    .string "I wonder what tiny POKéMON\l"
    .string "is sleeping inside…$"

LavaridgeTown_Text_EggGift_Togepi:
    .string "{PLAYER} received the EGG.\p"
    .string "That EGG has a very peculiar\n"
    .string "pattern on it… I have a feeling\l"
    .string "something special is inside!$"

LavaridgeTown_Text_EggGift_Tyrogue:
    .string "{PLAYER} received the EGG.\p"
    .string "That EGG feels restless…\n"
    .string "Whatever is inside seems eager\l"
    .string "to fight already!$"

LavaridgeTown_Text_EggGift_Elekid:
    .string "{PLAYER} received the EGG.\p"
    .string "Careful with that one!\n"
    .string "It gives off little sparks\l"
    .string "every now and then…$"

LavaridgeTown_Text_EggGift_Magby:
    .string "{PLAYER} received the EGG.\p"
    .string "That EGG is unusually warm!\n"
    .string "It must love the heat of\l"
    .string "the hot springs here.$"

LavaridgeTown_Text_EggGift_Munchlax:
    .string "{PLAYER} received the EGG.\p"
    .string "That EGG wobbles a lot…\n"
    .string "I think whatever is inside\l"
    .string "might already be hungry!$"

LavaridgeTown_Text_EggGift_Riolu:
    .string "{PLAYER} received the EGG.\p"
    .string "That EGG has a strong aura\n"
    .string "around it… Raise it with\l"
    .string "plenty of love and care!$"

LavaridgeTown_Text_EggGift_Starter:
    .string "{PLAYER} received the EGG.\p"
    .string "That EGG… I am not sure where\n"
    .string "it came from, but it feels\l"
    .string "like it holds great potential!\p"
    .string "Treasure it well, TRAINER!$"

LavaridgeTown_Text_EggGift_StarterFire:
    .string "{PLAYER} received the EGG.\p"
    .string "That EGG feels warm to the\n"
    .string "touch… just like our hot\l"
    .string "springs! It must feel right\l"
    .string "at home here in LAVARIDGE!$"

LavaridgeTown_Text_EggGift_Eevee:
    .string "{PLAYER} received the EGG.\p"
    .string "Oh my… that is a very rare\n"
    .string "EGG indeed! The POKéMON\l"
    .string "inside could grow into\l"
    .string "all sorts of things…$"

LavaridgeTown_Text_EggGift_Dratini:
    .string "{PLAYER} received the EGG.\p"
    .string "I found that EGG near the\n"
    .string "water. Something powerful\l"
    .string "is coiled up inside…\p"
    .string "Handle it gently!$"

LavaridgeTown_Text_EggGift_Larvitar:
    .string "{PLAYER} received the EGG.\p"
    .string "That EGG is surprisingly\n"
    .string "heavy… Whatever is inside\l"
    .string "must be incredibly tough!$"

LavaridgeTown_Text_EggGift_Bagon:
    .string "{PLAYER} received the EGG.\p"
    .string "That EGG keeps rolling\n"
    .string "around on its own…\l"
    .string "Something very determined\l"
    .string "is waiting inside!$"

LavaridgeTown_Text_EggGift_Gible:
    .string "{PLAYER} received the EGG.\p"
    .string "I am not sure how I ended\n"
    .string "up with that EGG, but it\l"
    .string "feels ferocious!\p"
    .string "Be careful raising it…$"

LavaridgeTown_Text_EggGift_Phione:
    .string "{PLAYER} received the EGG.\p"
    .string "This EGG is… strange.\n"
    .string "It appeared floating in the\l"
    .string "hot springs one morning…\p"
    .string "I have never seen anything\n"
    .string "quite like it. Something\l"
    .string "mysterious is inside…$"

