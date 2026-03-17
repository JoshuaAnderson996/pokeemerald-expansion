GraniteCave_StevensRoom_MapScripts::
	.byte 0

GraniteCave_StevensRoom_EventScript_Steven::
	lock
	faceplayer
	@ If the letter has already been delivered (re-interaction after full event), just say goodbye
	goto_if_set FLAG_DEFEATED_GRANITE_CAVE_STEVEN, GraniteCave_StevensRoom_EventScript_AlreadyDefeated
	@ Deliver the letter
	msgbox GraniteCave_StevensRoom_Text_ImStevenLetterForMe, MSGBOX_DEFAULT
	setvar VAR_0x8004, ITEM_LETTER
	call Common_EventScript_PlayerHandedOverTheItem
	setflag FLAG_DELIVERED_STEVEN_LETTER
	@ Steven thanks the player and gives TM Steel Wing for the delivery
	msgbox GraniteCave_StevensRoom_Text_ThankYouTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_STEEL_WING
	call_if_eq VAR_RESULT, FALSE, GraniteCave_StevensRoom_EventScript_BagFull
	@ Steven challenges the player to a battle
	msgbox GraniteCave_StevensRoom_Text_WantToTestYourStrength, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_STEVEN_GRANITE_CAVE, GraniteCave_StevensRoom_Text_StevenDefeat
	@ Post-battle: Steven is impressed and gives rewards
	msgbox GraniteCave_StevensRoom_Text_ImpressedHeresMegaRing, MSGBOX_DEFAULT
	giveitem ITEM_MEGA_RING
	call_if_eq VAR_RESULT, FALSE, GraniteCave_StevensRoom_EventScript_BagFull
	@ Give Beldum
	msgbox GraniteCave_StevensRoom_Text_AlsoTakeBeldum, MSGBOX_DEFAULT
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_BELDUM
	givemon SPECIES_BELDUM, 5
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, GraniteCave_StevensRoom_EventScript_BeldumToParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, GraniteCave_StevensRoom_EventScript_BeldumToPC
	goto GraniteCave_StevensRoom_EventScript_NoBeldumRoom

GraniteCave_StevensRoom_EventScript_BeldumToParty::
	bufferspeciesname STR_VAR_2, SPECIES_BELDUM
	playfanfare MUS_OBTAIN_ITEM
	message GraniteCave_StevensRoom_Text_ObtainedBeldum
	waitmessage
	waitfanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, GraniteCave_StevensRoom_EventScript_AfterBeldum
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto GraniteCave_StevensRoom_EventScript_AfterBeldum

GraniteCave_StevensRoom_EventScript_BeldumToPC::
	bufferspeciesname STR_VAR_2, SPECIES_BELDUM
	playfanfare MUS_OBTAIN_ITEM
	message GraniteCave_StevensRoom_Text_ObtainedBeldum
	waitmessage
	waitfanfare
	call Common_EventScript_TransferredToPC
	goto GraniteCave_StevensRoom_EventScript_AfterBeldum

GraniteCave_StevensRoom_EventScript_NoBeldumRoom::
	call Common_EventScript_NoMoreRoomForPokemon
	goto GraniteCave_StevensRoom_EventScript_AfterBeldum

GraniteCave_StevensRoom_EventScript_AfterBeldum::
	@ Register in PokéNav and exit
	setflag FLAG_DEFEATED_GRANITE_CAVE_STEVEN
	msgbox GraniteCave_StevensRoom_Text_CouldBecomeChampionLetsRegister, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox GraniteCave_StevensRoom_Text_RegisteredSteven, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_REGISTERED_STEVEN_POKENAV
	msgbox GraniteCave_StevensRoom_Text_IveGotToHurryAlong, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, GraniteCave_StevensRoom_EventScript_StevenExitNorth
	call_if_eq VAR_FACING, DIR_SOUTH, GraniteCave_StevensRoom_EventScript_StevenExitSouth
	call_if_eq VAR_FACING, DIR_WEST, GraniteCave_StevensRoom_EventScript_StevenExitWestEast
	call_if_eq VAR_FACING, DIR_EAST, GraniteCave_StevensRoom_EventScript_StevenExitWestEast
	playse SE_EXIT
	removeobject LOCALID_GRANITE_CAVE_STEVEN
	release
	end

GraniteCave_StevensRoom_EventScript_AlreadyDefeated::
	msgbox GraniteCave_StevensRoom_Text_AlreadyDefeated, MSGBOX_DEFAULT
	release
	end

GraniteCave_StevensRoom_EventScript_StevenExitNorth::
	applymovement LOCALID_GRANITE_CAVE_STEVEN, GraniteCave_StevensRoom_Movement_StevenExit
	waitmovement 0
	return

GraniteCave_StevensRoom_EventScript_StevenExitWestEast::
	applymovement LOCALID_PLAYER, GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit
	applymovement LOCALID_GRANITE_CAVE_STEVEN, GraniteCave_StevensRoom_Movement_StevenExit
	waitmovement 0
	return

GraniteCave_StevensRoom_EventScript_StevenExitSouth::
	applymovement LOCALID_PLAYER, GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit
	applymovement LOCALID_GRANITE_CAVE_STEVEN, GraniteCave_StevensRoom_Movement_StevenExitSouth
	waitmovement 0
	return

GraniteCave_StevensRoom_EventScript_BagFull::
	msgbox GraniteCave_StevensRoom_Text_OhBagIsFull, MSGBOX_DEFAULT
	return

GraniteCave_StevensRoom_Movement_StevenExit:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	delay_8
	step_end

GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit:
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_up
	step_end

GraniteCave_StevensRoom_Movement_StevenExitSouth:
	walk_left
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	delay_8
	step_end

GraniteCave_StevensRoom_Text_ImStevenLetterForMe:
	.string "My name is STEVEN.\p"
	.string "I'm interested in rare stones,\n"
	.string "so I travel here and there.\p"
	.string "Oh?\n"
	.string "A LETTER for me?$"

GraniteCave_StevensRoom_Text_ThankYouTakeThis:
	.string "STEVEN: Okay, thank you.\p"
	.string "You went through all this trouble to\n"
	.string "deliver that. I need to thank you.\p"
	.string "Please, take this TM.\p"
	.string "It contains my favorite move,\n"
	.string "STEEL WING.$"

GraniteCave_StevensRoom_Text_WantToTestYourStrength:
	.string "STEVEN: Still… coming all the way to\n"
	.string "GRANITE CAVE to find me…\p"
	.string "You must be a skilled Trainer.\p"
	.string "I'd like to see what you're capable of.\p"
	.string "Would you battle me?\n"
	.string "Consider it a proper thank-you.$"

GraniteCave_StevensRoom_Text_StevenDefeat:
	.string "STEVEN: …Impressive.\n"
	.string "You're stronger than I imagined.$"

GraniteCave_StevensRoom_Text_ImpressedHeresMegaRing:
	.string "STEVEN: You battled beautifully.\p"
	.string "There's something I want to give you.\p"
	.string "This is a MEGA RING.\p"
	.string "It resonates with certain POKéMON\n"
	.string "holding a Mega Stone in battle.\p"
	.string "I have a feeling you'll put it\n"
	.string "to great use.$"

GraniteCave_StevensRoom_Text_AlsoTakeBeldum:
	.string "STEVEN: One more thing.\p"
	.string "I'd like you to have this POKéMON\n"
	.string "as well.\p"
	.string "It's a BELDUM a rare Steel and\n"
	.string "Cosmic type.\p"
	.string "Devon Corp scientist have recently\n"
	.string "found this new type\n"
	.string "The wonders of space\n"
	.string "is exciting.$"

GraniteCave_StevensRoom_Text_ObtainedBeldum:
	.string "{PLAYER} received a BELDUM!$"

GraniteCave_StevensRoom_Text_CouldBecomeChampionLetsRegister:
	.string "STEVEN: Your POKéMON appear quite\n"
	.string "capable.\p"
	.string "If you keep training, you could even\n"
	.string "become the CHAMPION of the POKéMON\l"
	.string "LEAGUE one day. That's what I think.\p"
	.string "I know, since we've gotten to know each\n"
	.string "other, let's register one another in\l"
	.string "our POKéNAVS.\p"
	.string "… … … … … …$"

GraniteCave_StevensRoom_Text_RegisteredSteven:
	.string "Registered STEVEN\n"
	.string "in the POKéNAV.$"

GraniteCave_StevensRoom_Text_IveGotToHurryAlong:
	.string "Now, I've got to hurry along.$"

GraniteCave_StevensRoom_Text_OhBagIsFull:
	.string "Oh, your BAG is full…\n"
	.string "That's too bad, then.$"

GraniteCave_StevensRoom_Text_AlreadyDefeated:
	.string "STEVEN: It was good battling you.\p"
	.string "Don't forget keep that MEGA RING\n"
	.string "close. It may serve you well.$"
