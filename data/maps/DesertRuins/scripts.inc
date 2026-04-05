DesertRuins_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, DesertRuins_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, DesertRuins_OnTransition
	.byte 0

DesertRuins_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, DesertRuins_EventScript_TryRemoveRegirock
	end

DesertRuins_EventScript_TryRemoveRegirock::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

DesertRuins_EventScript_HideRegiEntrance::
	setmetatile 7, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 8, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 9, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 7, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	setmetatile 8, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	setmetatile 9, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	return

DesertRuins_OnTransition:
	setflag FLAG_LANDMARK_DESERT_RUINS
	call_if_unset FLAG_DEFEATED_REGIROCK, DesertRuins_EventScript_ShowRegirock
	call DesertRuins_EventScript_UpdateMagmaScene
	end

DesertRuins_EventScript_ShowRegirock::
	clearflag FLAG_HIDE_REGIROCK
	return

@ Hides/shows Magma NPCs on every transition based on scene state
DesertRuins_EventScript_UpdateMagmaScene::
	goto_if_set FLAG_DESERT_RUINS_MAGMA_SCENE_DONE, DesertRuins_EventScript_HideAllMagmaNPCs
	clearflag FLAG_HIDE_DESERT_RUINS_TABITHA
	clearflag FLAG_HIDE_DESERT_RUINS_COURTNEY
	clearflag FLAG_HIDE_DESERT_RUINS_MAGMA_GRUNTS
	setflag FLAG_HIDE_DESERT_RUINS_STEVEN
	setflag FLAG_HIDE_DESERT_RUINS_ROXANNE
	setflag FLAG_HIDE_DESERT_RUINS_WATTSON
	return

DesertRuins_EventScript_HideAllMagmaNPCs::
	setflag FLAG_HIDE_DESERT_RUINS_TABITHA
	setflag FLAG_HIDE_DESERT_RUINS_COURTNEY
	setflag FLAG_HIDE_DESERT_RUINS_MAGMA_GRUNTS
	setflag FLAG_HIDE_DESERT_RUINS_STEVEN
	setflag FLAG_HIDE_DESERT_RUINS_ROXANNE
	setflag FLAG_HIDE_DESERT_RUINS_WATTSON
	return

DesertRuins_EventScript_CaveEntranceMiddle::
	lockall
	goto_if_set FLAG_SYS_REGIROCK_PUZZLE_COMPLETED, DesertRuins_EventScript_BigHoleInWall
	braillemsgbox DesertRuins_Braille_UseRockSmash
	releaseall
	end

DesertRuins_EventScript_BigHoleInWall::
	msgbox gText_BigHoleInTheWall, MSGBOX_DEFAULT
	releaseall
	end

DesertRuins_EventScript_CaveEntranceSide::
	lockall
	braillemsgbox DesertRuins_Braille_UseRockSmash
	releaseall
	end

DesertRuins_EventScript_Regirock::
	lock
	faceplayer
	goto_if_set FLAG_REGIROCK_BOSS_DEFEATED, DesertRuins_EventScript_RegirockRematch
	goto DesertRuins_EventScript_RegirockBoss
	end

DesertRuins_EventScript_RegirockBoss::
	waitse
	playmoncry SPECIES_REGIROCK_BOSS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag B_FLAG_NO_CATCHING
	setflag B_SMART_WILD_AI_FLAG
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 1, 0, 0, 1, 0, 0 @ +1 Atk, +1 Def, +1 SpDef
	setwildbattle SPECIES_REGIROCK_BOSS, 50,      
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special StartRegiBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	clearflag B_FLAG_NO_CATCHING
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, DesertRuins_EventScript_RegirockBossDefeated
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, DesertRuins_EventScript_RanFromRegirock
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, DesertRuins_EventScript_RanFromRegirock
	release
	end

DesertRuins_EventScript_RegirockBossDefeated::
	setflag FLAG_REGIROCK_BOSS_DEFEATED
	setflag FLAG_HIDE_REGIROCK  @ hide it now; OnTransition will restore it on next entry
	msgbox DesertRuins_Text_RegirockWithdrewItsEnergy, MSGBOX_DEFAULT
	release
	end

DesertRuins_EventScript_RegirockRematch::
	waitse
	playmoncry SPECIES_REGIROCK, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_REGIROCK, 40
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special StartRegiBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, DesertRuins_EventScript_DefeatedRegirock
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, DesertRuins_EventScript_RanFromRegirock
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, DesertRuins_EventScript_RanFromRegirock
	@ Caught - OnResume handles sprite removal via FLAG_SYS_CTRL_OBJ_DELETE
	setflag FLAG_DEFEATED_REGIROCK
	release
	end

DesertRuins_EventScript_DefeatedRegirock::
	setflag FLAG_DEFEATED_REGIROCK
	goto Common_EventScript_RemoveStaticPokemon
	end

DesertRuins_EventScript_RanFromRegirock::
	setvar VAR_0x8004, SPECIES_REGIROCK
	goto Common_EventScript_LegendaryFlewAway
	end

@ =============================================================
@ TEAM MAGMA AMBUSH CUTSCENE
@ =============================================================

DesertRuins_EventScript_MagmaAmbushTrigger::
	goto_if_set FLAG_DESERT_RUINS_MAGMA_SCENE_DONE, DesertRuins_EventScript_AmbushDone
	goto_if_unset FLAG_BADGE03_GET, DesertRuins_EventScript_AmbushDone
	setflag FLAG_DESERT_RUINS_MAGMA_SCENE_STARTED
	lockall
	delay 30
	applymovement LOCALID_DESERT_RUINS_TABITHA, Common_Movement_FacePlayer
	applymovement LOCALID_DESERT_RUINS_COURTNEY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox DesertRuins_Text_TabithaStartled, MSGBOX_DEFAULT
	applymovement LOCALID_DESERT_RUINS_TABITHA, Common_Movement_FaceDown
	applymovement LOCALID_DESERT_RUINS_COURTNEY, Common_Movement_FaceDown
	waitmovement 0
	msgbox DesertRuins_Text_CourtneyRecognizes, MSGBOX_DEFAULT
	msgbox DesertRuins_Text_TabithaOutnumbered, MSGBOX_DEFAULT
	addobject LOCALID_DESERT_RUINS_STEVEN
	applymovement LOCALID_DESERT_RUINS_STEVEN, DesertRuins_Movement_StevenEnter
	waitmovement 0
	applymovement LOCALID_DESERT_RUINS_GRUNT_1, Common_Movement_FaceRight
	applymovement LOCALID_DESERT_RUINS_GRUNT_4, Common_Movement_FaceRight
	waitmovement 0
	addobject LOCALID_DESERT_RUINS_WATTSON
	applymovement LOCALID_DESERT_RUINS_WATTSON, DesertRuins_Movement_WatsonEnter
	waitmovement 0
	applymovement LOCALID_DESERT_RUINS_GRUNT_3, Common_Movement_FaceLeft
	applymovement LOCALID_DESERT_RUINS_GRUNT_5, Common_Movement_FaceLeft
	waitmovement 0
	addobject LOCALID_DESERT_RUINS_ROXANNE
	applymovement LOCALID_DESERT_RUINS_ROXANNE, DesertRuins_Movement_RoxanneEnter
	waitmovement 0
	applymovement LOCALID_DESERT_RUINS_GRUNT_2, Common_Movement_FaceUp
	waitmovement 0
	msgbox DesertRuins_Text_StevenArrives, MSGBOX_DEFAULT
	msgbox DesertRuins_Text_RoxanneArrives, MSGBOX_DEFAULT
	msgbox DesertRuins_Text_WatsonArrives, MSGBOX_DEFAULT
	msgbox DesertRuins_Text_TabithaChallengePlayer, MSGBOX_DEFAULT
	applymovement LOCALID_DESERT_RUINS_TABITHA, Common_Movement_FacePlayer
	waitmovement 0
	@ Battle Tabitha first
	trainerbattle_no_intro TRAINER_TABITHA_DESERT_RUINS, DesertRuins_Text_TabithaDefeat
	msgbox DesertRuins_Text_TabithaDefeated, MSGBOX_DEFAULT
	@ Then Courtney steps up
	applymovement LOCALID_DESERT_RUINS_COURTNEY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox DesertRuins_Text_CourtneyChallenge, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_COURTNEY_DESERT_RUINS, DesertRuins_Text_CourtneyDefeat
	msgbox DesertRuins_Text_AdminsDefeatedReaction, MSGBOX_DEFAULT
	msgbox DesertRuins_Text_AdminsFlee, MSGBOX_DEFAULT
	@ Admins and grunts all run to the exit simultaneously
	applymovement LOCALID_DESERT_RUINS_TABITHA, DesertRuins_Movement_TabithaFlee
	applymovement LOCALID_DESERT_RUINS_COURTNEY, DesertRuins_Movement_CourtneyFlee
	applymovement LOCALID_DESERT_RUINS_GRUNT_1, DesertRuins_Movement_Grunt1Flee
	applymovement LOCALID_DESERT_RUINS_GRUNT_2, DesertRuins_Movement_Grunt2Flee
	applymovement LOCALID_DESERT_RUINS_GRUNT_3, DesertRuins_Movement_Grunt3Flee
	applymovement LOCALID_DESERT_RUINS_GRUNT_4, DesertRuins_Movement_Grunt4Flee
	applymovement LOCALID_DESERT_RUINS_GRUNT_5, DesertRuins_Movement_Grunt5Flee
	waitmovement 0
	@ Remove everyone once they've walked off
	removeobject LOCALID_DESERT_RUINS_TABITHA
	removeobject LOCALID_DESERT_RUINS_COURTNEY
	removeobject LOCALID_DESERT_RUINS_GRUNT_1
	removeobject LOCALID_DESERT_RUINS_GRUNT_2
	removeobject LOCALID_DESERT_RUINS_GRUNT_3
	removeobject LOCALID_DESERT_RUINS_GRUNT_4
	removeobject LOCALID_DESERT_RUINS_GRUNT_5
	setflag FLAG_HIDE_DESERT_RUINS_TABITHA
	setflag FLAG_HIDE_DESERT_RUINS_COURTNEY
	setflag FLAG_HIDE_DESERT_RUINS_MAGMA_GRUNTS
	delay 20
	@ Allies face player and speak
	applymovement LOCALID_DESERT_RUINS_STEVEN, Common_Movement_FacePlayer
	applymovement LOCALID_DESERT_RUINS_ROXANNE, Common_Movement_FacePlayer
	applymovement LOCALID_DESERT_RUINS_WATTSON, Common_Movement_FacePlayer
	waitmovement 0
	msgbox DesertRuins_Text_StevenPostBattle, MSGBOX_DEFAULT
	msgbox DesertRuins_Text_RoxannePostBattle, MSGBOX_DEFAULT
	msgbox DesertRuins_Text_WattsonPostBattle, MSGBOX_DEFAULT
	msgbox DesertRuins_Text_StevenReward, MSGBOX_DEFAULT
	giveitem ITEM_HARD_STONE
	msgbox DesertRuins_Text_StevenRegirockWarning, MSGBOX_DEFAULT
	msgbox DesertRuins_Text_RoxanneRegirockWarning, MSGBOX_DEFAULT
	msgbox DesertRuins_Text_StevenFarewell, MSGBOX_DEFAULT
	@ Allies walk to the exit together
	applymovement LOCALID_DESERT_RUINS_STEVEN, DesertRuins_Movement_StevenFlee
	applymovement LOCALID_DESERT_RUINS_ROXANNE, DesertRuins_Movement_RoxanneFlee
	applymovement LOCALID_DESERT_RUINS_WATTSON, DesertRuins_Movement_WattsonFlee
	waitmovement 0
	removeobject LOCALID_DESERT_RUINS_STEVEN
	removeobject LOCALID_DESERT_RUINS_ROXANNE
	removeobject LOCALID_DESERT_RUINS_WATTSON
	setflag FLAG_DESERT_RUINS_MAGMA_SCENE_DONE
	releaseall
	end

DesertRuins_EventScript_AmbushDone::
	releaseall
	end

DesertRuins_EventScript_Tabitha::
	lock
	faceplayer
	msgbox DesertRuins_Text_TabithaIdle, MSGBOX_DEFAULT
	release
	end

DesertRuins_EventScript_Courtney::
	lock
	faceplayer
	msgbox DesertRuins_Text_CourtneyIdle, MSGBOX_DEFAULT
	release
	end

DesertRuins_Text_TabithaIdle:
	.string "TABITHA: Don't get in our way, kid.$"

DesertRuins_Text_CourtneyIdle:
	.string "COURTNEY: …Leave.$"

DesertRuins_Movement_StevenEnter:
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	face_left
	step_end

DesertRuins_Movement_RoxanneEnter:
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	face_down
	step_end

DesertRuins_Movement_WatsonEnter:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	face_right
	step_end

	DesertRuins_EventScript_MagmaGrunt::
	lock
	faceplayer
	msgbox DesertRuins_Text_GruntIdle, MSGBOX_DEFAULT
	release
	end

@ Grunt 1 is at x5 y25 - walks right 3, down 5 (past exit)
DesertRuins_Movement_Grunt1Flee:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

@ Grunt 2 is at x8 y25 - walks down 5 (past exit)
DesertRuins_Movement_Grunt2Flee:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

@ Grunt 3 is at x11 y25 - walks left 3, down 5 (past exit)
DesertRuins_Movement_Grunt3Flee:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

@ Grunt 4 is at x5 y27 - walks right 3, down 3 (past exit)
DesertRuins_Movement_Grunt4Flee:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

@ Grunt 5 is at x11 y27 - walks left 3, down 3 (past exit)
DesertRuins_Movement_Grunt5Flee:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

@ Tabitha is at x7 y26 - walks right 1, down 4 (past exit)
DesertRuins_Movement_TabithaFlee:
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

@ Courtney is at x9 y26 - walks left 1, down 4 (past exit)
DesertRuins_Movement_CourtneyFlee:
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

@ Steven - adjust steps to match his final position after entrance
DesertRuins_Movement_StevenFlee:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	step_end

@ Roxanne - adjust steps to match her final position after entrance
DesertRuins_Movement_RoxanneFlee:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

@ Wattson - adjust steps to match his final position after entrance
DesertRuins_Movement_WattsonFlee:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	step_end

DesertRuins_Text_GruntIdle:
	.string "You're not going anywhere, kid!$"

DesertRuins_Text_TabithaStartled:
	.string "Hm?! A kid?!\p"
	.string "…Wait. You're that trainer who\n"
	.string "took down TEAM AQUA?$"

DesertRuins_Text_CourtneyRecognizes:
	.string "…Confirmed. It's them.\p"
	.string "Quite the reputation for someone\n"
	.string "so small.$"

DesertRuins_Text_TabithaOutnumbered:
	.string "Heh. Doesn't matter.\n"
	.string "You're outnumbered.\p"
	.string "TEAM MAGMA takes what it wants.\n"
	.string "And today, we want REGIROCK.$"

DesertRuins_Text_StevenArrives:
	.string "STEVEN: I don't think so, TABITHA.\p"
	.string "You'll have to go through us first.$"

DesertRuins_Text_RoxanneArrives:
	.string "ROXANNE: We'll hold the grunts.\p"
	.string "{PLAYER}, the admins are yours.$"

DesertRuins_Text_WatsonArrives:
	.string "WATTSON: Wahaha!\n"
	.string "You've got nerve showing up in\l"
	.string "MY town's backyard!$"

DesertRuins_Text_TabithaChallengePlayer:
	.string "TABITHA: Fine. You want to be a hero?\p"
	.string "COURTNEY. Let's crush them together.$"

DesertRuins_Text_TabithaIntro:
	.string "TABITHA: Both of us against you.\n"
	.string "Don't expect mercy!$"

DesertRuins_Text_AdminsDefeat:
	.string "TABITHA: Impossible…!$"

DesertRuins_Text_NotEnoughMons:
	.string "TABITHA: You don't even have enough\n"
	.string "POKéMON for a double battle!\p"
	.string "Come back when you're ready to\n"
	.string "face us properly.$"

DesertRuins_Text_AdminsDefeatedReaction:
	.string "COURTNEY: …Strength confirmed.\n"
	.string "Exceeds projections.$"

DesertRuins_Text_AdminsFlee:
	.string "TABITHA: Grgh… Fall back!\p"
	.string "Don't think you've won, kid.\p"
	.string "LEADER MAXIE is NOT going to be\n"
	.string "happy that we lost REGIROCK…\p"
	.string "We'll be back.$"

	DesertRuins_Text_TabithaDefeat:
	.string "TABITHA: Ngh…!$"

DesertRuins_Text_TabithaDefeated:
	.string "TABITHA: Impossible… a kid beat me?\p"
	.string "COURTNEY. Finish this.$"

DesertRuins_Text_CourtneyChallenge:
	.string "COURTNEY: …Understood.\p"
	.string "I will not lose.$"

DesertRuins_Text_CourtneyDefeat:
	.string "COURTNEY: …Loss confirmed.$"

	DesertRuins_Text_StevenPostBattle:
	.string "STEVEN: Well done, {PLAYER}.\p"
	.string "You handled yourself well out there.\p"
	.string "TEAM MAGMA won't be back here\n"
	.string "any time soon.$"

DesertRuins_Text_RoxannePostBattle:
	.string "ROXANNE: The grunts have scattered.\p"
	.string "We've secured the ruins for now.\p"
	.string "Your battling ability is… impressive\n"
	.string "for someone your age.$"

DesertRuins_Text_WattsonPostBattle:
	.string "WATTSON: Wahaha! That's what they\n"
	.string "get for causing trouble!\p"
	.string "Nobody messes with HOENN's GYM\n"
	.string "LEADERS! Wahaha!$"

DesertRuins_Text_StevenReward:
	.string "STEVEN: Take this, {PLAYER}.\p"
	.string "A HARD STONE, found deep in these\n"
	.string "ruins.\p"
	.string "It's only right that it goes to\n"
	.string "someone who fought to protect them.$"

DesertRuins_Text_StevenRegirockWarning:
	.string "STEVEN: One more thing.\p"
	.string "Deep within these ruins sleeps\n"
	.string "REGIROCK, one of the legendary\l"
	.string "titans of HOENN.\p"
	.string "TEAM MAGMA came here for it.\p"
	.string "If you ever face REGIROCK yourself,\n"
	.string "be prepared.\p"
	.string "It is not a POKéMON to be taken\n"
	.string "lightly.$"

DesertRuins_Text_RoxanneRegirockWarning:
	.string "ROXANNE: According to my research,\n"
	.string "REGIROCK's body is composed entirely\l"
	.string "of rock.\p"
	.string "It repairs itself using rocks from\n"
	.string "its surroundings.\p"
	.string "Rock-type moves will not be very\n"
	.string "effective against it.\p"
	.string "I'd recommend WATER, GRASS or\n"
	.string "FIGHTING-type POKéMON if you plan\l"
	.string "to challenge it.$"

DesertRuins_Text_StevenFarewell:
	.string "STEVEN: Stay safe out there,\n"
	.string "{PLAYER}.\p"
	.string "HOENN is counting on trainers\n"
	.string "like you.$"

DesertRuins_Text_RegirockWithdrewItsEnergy:
	.string "The ancient giant withdrew\n"
	.string "its power into the ruins…\p"
	.string "Its presence still lingers here.\n"
	.string "Perhaps it will emerge again…$"
