ProfBirch_EventScript_UpdateLocation::
	goto_if_eq VAR_PETALBURG_GYM_STATE, 0, Common_EventScript_NopReturn
	goto_if_set FLAG_SYS_GAME_CLEAR, ProfBirch_EventScript_MoveToLab
	call_if_eq VAR_BIRCH_STATE, 0, ProfBirch_EventScript_MoveToLab
	call_if_eq VAR_BIRCH_STATE, 1, ProfBirch_EventScript_MoveToLab
	call_if_eq VAR_BIRCH_STATE, 2, ProfBirch_EventScript_MoveToRoute101
	call_if_eq VAR_BIRCH_STATE, 3, ProfBirch_EventScript_MoveToRoute101
	call_if_eq VAR_BIRCH_STATE, 4, ProfBirch_EventScript_MoveToRoute103
	call_if_eq VAR_BIRCH_STATE, 5, ProfBirch_EventScript_MoveToRoute103
	call_if_eq VAR_BIRCH_STATE, 6, ProfBirch_EventScript_MoveToLab
	call_if_eq VAR_BIRCH_STATE, 7, ProfBirch_EventScript_MoveToLab
	return

ProfBirch_EventScript_MoveToLab::
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380
	setflag FLAG_HIDE_ROUTE_101_BIRCH
	setflag FLAG_HIDE_ROUTE_103_BIRCH
	return

ProfBirch_EventScript_MoveToRoute101::
	clearflag FLAG_HIDE_ROUTE_101_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380
	setflag FLAG_HIDE_ROUTE_103_BIRCH
	return

ProfBirch_EventScript_MoveToRoute103::
	clearflag FLAG_HIDE_ROUTE_103_BIRCH
	setflag FLAG_HIDE_ROUTE_101_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380
	return

ProfBirch_EventScript_RatePokedexOrRegister::
	lock
	faceplayer
	goto_if_unset FLAG_HAS_MATCH_CALL, ProfBirch_EventScript_AskRatePokedex
	goto_if_unset FLAG_ENABLE_PROF_BIRCH_MATCH_CALL, EventScript_RegisterProfBirch

ProfBirch_EventScript_AskRatePokedex::
	msgbox gBirchDexRatingText_AreYouCurious, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ProfBirch_EventScript_DeclineRating
	call ProfBirch_EventScript_RatePokedex
	release
	end

ProfBirch_EventScript_DeclineRating::
	msgbox gBirchDexRatingText_Cancel, MSGBOX_DEFAULT
	release
	end

ProfBirch_EventScript_ShowRatingMessage::
	copyvar VAR_0x8004, VAR_0x8009
	special ShowPokedexRatingMessage
	waitmessage
	waitbuttonpress
	return

ProfBirch_EventScript_RatePokedex::
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	copyvar VAR_0x800A, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_0x8008  @ Num Hoenn seen
	buffernumberstring STR_VAR_2, VAR_0x8009  @ Num Hoenn caught
	msgbox gBirchDexRatingText_SoYouveSeenAndCaught, MSGBOX_DEFAULT
	call ProfBirch_EventScript_ShowRatingMessage
	goto_if_eq VAR_0x800A, 0, Common_EventScript_NopReturn  @ National dex not enabled
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	buffernumberstring STR_VAR_1, VAR_0x8008  @ Num National seen
	buffernumberstring STR_VAR_2, VAR_0x8009  @ Num National caught
	msgbox gBirchDexRatingText_OnANationwideBasis, MSGBOX_DEFAULT
	return

	ProfBirch_EventScript_CheckMilestoneRewards::
	@ VAR_0x8009 contains National Dex caught count
	copyvar VAR_TEMP_0, VAR_0x8009

	@ Check 1000 Pokémon milestone
	goto_if_set FLAG_RECEIVED_BIRCH_REWARD_1000, ProfBirch_CheckReward400
	goto_if_ge VAR_TEMP_0, 500, ProfBirch_GiveReward500

	@ Check 900 Pokémon milestone
	goto_if_set FLAG_RECEIVED_BIRCH_REWARD_900, ProfBirch_CheckReward400
	goto_if_ge VAR_TEMP_0, 500, ProfBirch_GiveReward500

	@ Check 800 Pokémon milestone
	goto_if_set FLAG_RECEIVED_BIRCH_REWARD_800, ProfBirch_CheckReward400
	goto_if_ge VAR_TEMP_0, 500, ProfBirch_GiveReward500

	@ Check 700 Pokémon milestone
	goto_if_set FLAG_RECEIVED_BIRCH_REWARD_700, ProfBirch_CheckReward400
	goto_if_ge VAR_TEMP_0, 500, ProfBirch_GiveReward500

	@ Check 600 Pokémon milestone
	goto_if_set FLAG_RECEIVED_BIRCH_REWARD_600, ProfBirch_CheckReward400
	goto_if_ge VAR_TEMP_0, 500, ProfBirch_GiveReward500
	
	@ Check 500 Pokémon milestone
	goto_if_set FLAG_RECEIVED_BIRCH_REWARD_500, ProfBirch_CheckReward400
	goto_if_ge VAR_TEMP_0, 500, ProfBirch_GiveReward500
	
ProfBirch_CheckReward400:
	@ Check 400 Pokémon milestone
	goto_if_set FLAG_RECEIVED_BIRCH_REWARD_400, ProfBirch_CheckReward300
	goto_if_ge VAR_TEMP_0, 400, ProfBirch_GiveReward400
	
ProfBirch_CheckReward300:
	@ Check 300 Pokémon milestone
	goto_if_set FLAG_RECEIVED_BIRCH_REWARD_300, ProfBirch_CheckReward200
	goto_if_ge VAR_TEMP_0, 300, ProfBirch_GiveReward300
	
ProfBirch_CheckReward200:
	@ Check 200 Pokémon milestone
	goto_if_set FLAG_RECEIVED_BIRCH_REWARD_200, ProfBirch_CheckReward100
	goto_if_ge VAR_TEMP_0, 200, ProfBirch_GiveReward200
	
ProfBirch_CheckReward100:
	@ Check 100 Pokémon milestone
	goto_if_set FLAG_RECEIVED_BIRCH_REWARD_100, ProfBirch_NoMoreRewards
	goto_if_ge VAR_TEMP_0, 100, ProfBirch_GiveReward100
	
ProfBirch_NoMoreRewards:
	return

@ Reward Scripts
ProfBirch_GiveReward100::
	msgbox ProfBirch_Text_Reward100Pokemon, MSGBOX_DEFAULT
	giveitem ITEM_MASTER_BALL, 2
	setflag FLAG_RECEIVED_BIRCH_REWARD_100
	return

ProfBirch_GiveReward200::
	msgbox ProfBirch_Text_Reward200Pokemon, MSGBOX_DEFAULT
	giveitem ITEM_MASTER_BALL, 5
	giveitem ITEM_RARE_CANDY, 10
	setflag FLAG_RECEIVED_BIRCH_REWARD_200
	return

ProfBirch_GiveReward300::
	msgbox ProfBirch_Text_Reward300Pokemon, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY, 25
	giveitem ITEM_ABILITY_CAPSULE, 5
	setflag FLAG_RECEIVED_BIRCH_REWARD_300
	return

ProfBirch_GiveReward400::
	msgbox ProfBirch_Text_Reward400Pokemon, MSGBOX_DEFAULT
	givemon SPECIES_CELEBI, 30
	setflag FLAG_RECEIVED_BIRCH_REWARD_400
	return

ProfBirch_GiveReward500::
	msgbox ProfBirch_Text_Reward500Pokemon, MSGBOX_DEFAULT
	giveitem ITEM_SHINY_CHARM, 1
	setflag FLAG_RECEIVED_BIRCH_REWARD_500
	return

	ProfBirch_GiveReward600::
	msgbox ProfBirch_Text_Reward500Pokemon, MSGBOX_DEFAULT
	giveitem ITEM_SHINY_CHARM, 1
	setflag FLAG_RECEIVED_BIRCH_REWARD_600
	return

ProfBirch_GiveReward700::
	msgbox ProfBirch_Text_Reward500Pokemon, MSGBOX_DEFAULT
	giveitem ITEM_SHINY_CHARM, 1
	setflag FLAG_RECEIVED_BIRCH_REWARD_700
	return

	ProfBirch_GiveReward800::
	msgbox ProfBirch_Text_Reward500Pokemon, MSGBOX_DEFAULT
	giveitem ITEM_SHINY_CHARM, 1
	setflag FLAG_RECEIVED_BIRCH_REWARD_800
	return

ProfBirch_GiveReward900::
	msgbox ProfBirch_Text_Reward500Pokemon, MSGBOX_DEFAULT
	giveitem ITEM_SHINY_CHARM, 1
	setflag FLAG_RECEIVED_BIRCH_REWARD_900
	return

	ProfBirch_GiveReward1000::
	msgbox ProfBirch_Text_Reward500Pokemon, MSGBOX_DEFAULT
	giveitem ITEM_SHINY_CHARM, 1
	setflag FLAG_RECEIVED_BIRCH_REWARD_1000
	return