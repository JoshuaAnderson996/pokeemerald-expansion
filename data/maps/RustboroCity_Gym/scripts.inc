RustboroCity_Gym_MapScripts::
	.byte 0

RustboroCity_Gym_EventScript_Roxanne::
	trainerbattle_single TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxanneIntro, RustboroCity_Gym_Text_RoxanneDefeat, RustboroCity_Gym_EventScript_RoxanneDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Gym_EventScript_RoxanneRematch
	goto_if_unset FLAG_RECEIVED_TM_ROCK_TOMB, RustboroCity_Gym_EventScript_GiveRockTomb
	msgbox RustboroCity_Gym_Text_RoxannePostBattle, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_RoxanneDefeated::
	message RustboroCity_Gym_Text_ReceivedStoneBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox RustboroCity_Gym_Text_StoneBadgeInfoTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_RUSTBORO_GYM
	setflag FLAG_BADGE01_GET
	setvar VAR_RUSTBORO_CITY_STATE, 1
	addvar VAR_PETALBURG_GYM_STATE, 1
	setvar VAR_0x8008, 1
	call Common_EventScript_SetGymTrainers
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
	goto RustboroCity_Gym_EventScript_GiveRockTomb
	end

RustboroCity_Gym_EventScript_GiveRockTomb::
	giveitem ITEM_TM_ROCK_TOMB
	givemon SPECIES_GROWLITHE_HISUI, 5 
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_ROCK_TOMB
	msgbox RustboroCity_Gym_Text_ExplainRockTomb, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_RoxanneRematch::
	trainerbattle_rematch_double TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxannePreRematch, RustboroCity_Gym_Text_RoxanneRematchDefeat, RustboroCity_Gym_Text_RoxanneRematchNeedTwoMons
	msgbox RustboroCity_Gym_Text_RoxannePostRematch, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Josh::
	trainerbattle_single TRAINER_JOSH, RustboroCity_Gym_Text_JoshIntro, RustboroCity_Gym_Text_JoshDefeat
	msgbox RustboroCity_Gym_Text_JoshPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Tommy::
	trainerbattle_single TRAINER_TOMMY, RustboroCity_Gym_Text_TommyIntro, RustboroCity_Gym_Text_TommyDefeat
	msgbox RustboroCity_Gym_Text_TommyPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Marc::
	trainerbattle_single TRAINER_MARC, RustboroCity_Gym_Text_MarcIntro, RustboroCity_Gym_Text_MarcDefeat
	msgbox RustboroCity_Gym_Text_MarcPostBattle, MSGBOX_AUTOCLOSE
	end

	RustboroCity_Gym_EventScript_Dick::
	trainerbattle_single TRAINER_DICK, RustboroCity_Gym_Text_DickIntro, RustboroCity_Gym_Text_DickDefeat
	msgbox RustboroCity_Gym_Text_DickPostBattle, MSGBOX_AUTOCLOSE
	end

	RustboroCity_Gym_EventScript_Garnet::
	trainerbattle_single TRAINER_GARNET, RustboroCity_Gym_Text_GarnetIntro, RustboroCity_Gym_Text_GarnetDefeat
	msgbox RustboroCity_Gym_Text_GarnetPostBattle, MSGBOX_AUTOCLOSE
	end

	RustboroCity_Gym_EventScript_Quartz::
	trainerbattle_single TRAINER_QUARTZ, RustboroCity_Gym_Text_QuartzIntro, RustboroCity_Gym_Text_QuartzDefeat
	msgbox RustboroCity_Gym_Text_QuartzPostBattle, MSGBOX_AUTOCLOSE
	end

	RustboroCity_Gym_EventScript_Mica::
	trainerbattle_single TRAINER_MICA, RustboroCity_Gym_Text_MicaIntro, RustboroCity_Gym_Text_MicaDefeat
	msgbox RustboroCity_Gym_Text_MicaPostBattle, MSGBOX_AUTOCLOSE
	end

	RustboroCity_Gym_EventScript_Opal::
	trainerbattle_single TRAINER_OPAL, RustboroCity_Gym_Text_OpalIntro, RustboroCity_Gym_Text_OpalDefeat
	msgbox RustboroCity_Gym_Text_OpalPostBattle, MSGBOX_AUTOCLOSE
	end

	RustboroCity_Gym_EventScript_Basalt::
	trainerbattle_single TRAINER_BASALT, RustboroCity_Gym_Text_BasaltIntro, RustboroCity_Gym_Text_BasaltDefeat
	msgbox RustboroCity_Gym_Text_BasaltPostBattle, MSGBOX_AUTOCLOSE
	end

	RustboroCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_RUSTBORO_GYM, RustboroCity_Gym_EventScript_GymGuidePostVictory
	msgbox RustboroCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_EnteranceAnnouncement::
	lock
	goto_if_set FLAG_DEFEATED_RUSTBORO_GYM, RustboroCity_Gym_EventScript_EnteranceAnnouncementPostVictory
	msgbox RustboroCity_Gym_Text_EnteranceAnnouncement, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_EnteranceAnnouncementPostVictory::
	lock
	msgbox RustboroCity_Gym_Text_EnteranceAnnouncementPostVictory, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_GymGuidePostVictory::
	msgbox RustboroCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE01_GET, RustboroCity_Gym_EventScript_GymStatueCertified
	goto RustboroCity_Gym_EventScript_GymStatue
	end

RustboroCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE01_GET, RustboroCity_Gym_EventScript_GymStatueCertified
	goto RustboroCity_Gym_EventScript_GymStatue
	end

RustboroCity_Gym_EventScript_GymStatueCertified::
	msgbox RustboroCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_Gym_EventScript_GymStatue::
	msgbox RustboroCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_Gym_EventScript_RegisterRoxanne::
	lockall
	pokenavcall RustboroCity_Gym_Text_RoxanneRegisterCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox RustboroCity_Gym_Text_RegisteredRoxanne, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_ROXANNE_MATCH_CALL
	clearflag FLAG_ENABLE_ROXANNE_FIRST_CALL
	releaseall
	end

RustboroCity_Gym_Text_GymGuideAdvice:
    .string "RUSTBORO GYM OFFICIATING DESK.\n"
    .string "Now announcing today's match:\p"
    .string "CHALLENGER {PLAYER} vs. LEADER ROXANNE,\n"
    .string "specialist in ROCK-type POKEMON.\p"
    .string "Standard GYM regulations in effect.\n"
    .string "Trainers, begin when ready!$"

RustboroCity_Gym_Text_GymGuidePostVictory:
    .string "OFFICIAL RESULT {PLAYER} defeats\n"
    .string "LEADER ROXANNE!\p"
    .string "Congratulations, {PLAYER}. STONE BADGE\n"
    .string "awarded. You may request a rematch when\n"
    .string "LEADER ROXANNE is ready to accept.$"

	RustboroCity_Gym_Text_EnteranceAnnouncement:
    .string "Now entering the RUSTBORO GYM.\n"
    .string "Safety notice one challenger at a time.\p"
    .string "This GYM specializes in ROCK type POKEMON.\n"
    .string "Expect solid defense and steady pressure.\p"
    .string "Defeat the trainers to reveal the path to\n"
    .string "LEADER ROXANNE. Good luck!$"

	RustboroCity_Gym_Text_EnteranceAnnouncementPostVictory:
    .string "Congratulations, STONE BADGE holder!\n"
    .string "You have bested LEADER ROXANNE.$"

RustboroCity_Gym_Text_JoshIntro:
	.string "Don't take us GYM TRAINERS lightly!\n"
	.string "I'll show you why we're better!$"

RustboroCity_Gym_Text_JoshDefeat:
	.string "You were too good for me…$"

RustboroCity_Gym_Text_JoshPostBattle:
	.string "You haven't seen anything of the ROCK\n"
	.string "type's terrifying power!$"

RustboroCity_Gym_Text_TommyIntro:
	.string "If you can't beat me, you won't stand\n"
	.string "a chance against ROXANNE!$"

RustboroCity_Gym_Text_TommyDefeat:
	.string "Wow! You've got some potential!$"

RustboroCity_Gym_Text_TommyPostBattle:
	.string "ROXANNE is stronger than me by\n"
	.string "several times.\p"
	.string "You'd better be on your guard!$"

RustboroCity_Gym_Text_MarcIntro:
	.string "We might be in the middle of town,\n"
	.string "but so what?\p"
	.string "My ROCK POKéMON need room to\n"
	.string "rampage!$"

RustboroCity_Gym_Text_MarcDefeat:
	.string "Oh, man oh man!\n"
	.string "Our challenger is one feisty customer!$"

RustboroCity_Gym_Text_DickIntro:
    .string "Ahh, the ROCK type… steady and true.\p"
    .string "Let's see if your footing is as firm\n"
    .string "as granite, youngster!$"

RustboroCity_Gym_Text_MarcPostBattle:
	.string "Ho ho! Give me ROCK type POKéMON any day.\p"
	.string "Sturdy hides, unshakable hearts they hit like\n"
	.string "landslides and never quit, eh?$"

	RustboroCity_Gym_Text_DickDefeat:
    .string "Rock-solid resolve… You’ve got it.\p"
    .string "My praise for ROCK types still stands,\n"
    .string "but you outlasted me fair and square.$"

	RustboroCity_Gym_Text_DickPostBattle:
	.string "I have to hand it to our LEADER.\p"
	.string "It took smarts and sense for her to\n"
	.string "pick the ROCK type at her young age.$"

	RustboroCity_Gym_Text_QuartzIntro:
    .string "I'm QUARTZ, the GYM's lab tech.\n"
    .string "Today's experiment: can your tactics\n"
    .string "withstand ROCK-type pressure?\p"
    .string "Hypothesis no. Let's test it!$"

RustboroCity_Gym_Text_QuartzDefeat:
    .string "Result: hypothesis rejected!\n"
    .string "Your strategy exceeded my yield\n"
    .string "strength. Consider me convinced.$"

RustboroCity_Gym_Text_QuartzPostBattle:
    .string "In our models, ROCK types excel at\n"
    .string "endurance. Stack defense, set hazards,\n"
    .string "and wait for cracks. ROXANNE prizes\n"
    .string "methods you can replicate, not luck.$"


RustboroCity_Gym_Text_MicaIntro:
	.string "They call me MICA. Thin layers, big\n"
	.string "structured smart play over raw power!\p"
	.string "Ready to peel back your game plan?$"

RustboroCity_Gym_Text_MicaDefeat:
	.string "You kept your formation tight no\n"
	.string "cracks for me to pry open.$"

RustboroCity_Gym_Text_MicaPostBattle:
	.string "Against ROCK types, chip adds up.\n"
	.string "If you rush, you just blunt your own edge.$"

RustboroCity_Gym_Text_OpalIntro:
	.string "OPAL here! Don’t be fooled by the shimmer\n"
	.string "our defenses are the real treasure.\p"
	.string "Show me your brightest move!$"

RustboroCity_Gym_Text_OpalDefeat:
	.string "Brilliant! Your reads refracted every\n"
	.string "angle I tried.$"

RustboroCity_Gym_Text_OpalPostBattle:
	.string "Roxanne teaches balance set up, stabilize,\n"
	.string "then strike once the field is yours.$"

RustboroCity_Gym_Text_BasaltIntro:
	.string "Name’s BASALT. I’m the bedrock of this\n"
	.string "Gym’s training dense, steady, unmoving.\p"
	.string "Let’s test your foundation!$"

RustboroCity_Gym_Text_BasaltDefeat:
	.string "Heh. Your footing held firm. Respect\n"
	.string "to your groundwork.$"

RustboroCity_Gym_Text_BasaltPostBattle:
	.string "When in doubt, set STEALTH ROCK and keep\n"
	.string "switch pressure high. That’s how we wear\n"
	.string "down even the toughest visitors.$"

RustboroCity_Gym_Text_GarnetIntro:
	.string "I’m GARNET, Roxanne’s apprentice.\n"
	.string "Pressure makes gems and champions.\p"
	.string "Let’s see if you can shine under it!$"

RustboroCity_Gym_Text_GarnetDefeat:
	.string "You kept your facets flawless.\n"
	.string "No flaws for me to strike.$"

RustboroCity_Gym_Text_GarnetPostBattle:
	.string "Against ROCK types, patient setup wins.\n"
	.string "Chip damage, hazard control, then break\n"
	.string "through at the perfect moment.$"

RustboroCity_Gym_Text_RoxanneIntro:
	.string "Hello, I am ROXANNE, the RUSTBORO\n"
	.string "POKéMON GYM LEADER.\p"
	.string "I became a GYM LEADER so that I might\n"
	.string "apply what I learned at the POKéMON\l"
	.string "TRAINER'S SCHOOL in battle.\p"
	.string "Would you kindly demonstrate how you\n"
	.string "battle, and with which POKéMON?$"

RustboroCity_Gym_Text_RoxanneDefeat:
	.string "So…\n"
	.string "I lost…\p"
	.string "It seems that I still have much more\n"
	.string "to learn…\p"
	.string "I understand.\p"
	.string "The POKéMON LEAGUE's rules state\n"
	.string "that TRAINERS are to be given this\l"
	.string "if they defeat a GYM LEADER.\p"
	.string "Please accept the official POKéMON\n"
	.string "LEAGUE STONE BADGE.$"

RustboroCity_Gym_Text_ReceivedStoneBadge:
	.string "{PLAYER} received the STONE BADGE\n"
	.string "from ROXANNE.$"

RustboroCity_Gym_Text_StoneBadgeInfoTakeThis:
	.string "This is the STONE BADGE it is proof of the\n"
	.string "power of your POKéMON.\p"
	.string "Congratulations on your win\n"
	.string "Heres your reward.\p"
	.string "Please take these with you, too.$"

RustboroCity_Gym_Text_ExplainRockTomb:
	.string "That TECHNICAL MACHINE, TM39,\n"
	.string "contains ROCK TOMB.\p"
	.string "It not only inflicts damage by dropping\n"
	.string "rocks, it also lowers SPEED.\p"
	.string "Also I have gifted you \n"
	.string "a special POKéMON.$"

RustboroCity_Gym_Text_RoxannePostBattle:
	.string "Since you are so strong, you should\n"
	.string "challenge other GYM LEADERS.\p"
	.string "By battling many TRAINERS, you should\n"
	.string "learn many things.$"

RustboroCity_Gym_Text_GymStatue:
	.string "RUSTBORO CITY POKéMON GYM$"

RustboroCity_Gym_Text_GymStatueCertified:
	.string "RUSTBORO CITY POKéMON GYM\p"
	.string "ROXANNE'S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"

RustboroCity_Gym_Text_RoxanneRegisterCall:
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "ROXANNE: Oh, hello, {PLAYER}?\n"
	.string "This is ROXANNE of RUSTBORO CITY.\p"
	.string "I heard from BRAWLY that you're\n"
	.string "moving up through the ranks of\l"
	.string "TRAINERS at an incredible clip.\p"
	.string "Well, I'd rather not think that\n"
	.string "I can't beat you.\p"
	.string "I promise, I will shape up my GYM\n"
	.string "so that you may challenge us again.\p"
	.string "I hope you'll be looking forward to\n"
	.string "that occasion as much as me!\p"
	.string "… … … … … …\n"
	.string "… … … … … Click!$"

RustboroCity_Gym_Text_RegisteredRoxanne:
	.string "Registered GYM LEADER ROXANNE\n"
	.string "in the POKéNAV.$"

RustboroCity_Gym_Text_RoxannePreRematch:
	.string "ROXANNE: I'm so glad to see you again.\n"
	.string "I'm ROXANNE, the GYM LEADER here.\p"
	.string "I'm sure we've both experienced many\n"
	.string "battles since we last met.\p"
	.string "I would like to see how much better\n"
	.string "we've become. Let us battle!$"

RustboroCity_Gym_Text_RoxanneRematchDefeat:
	.string "Grr…\n"
	.string "Again, I have lost…$"

RustboroCity_Gym_Text_RoxannePostRematch:
	.string "ROXANNE: I still have much to learn\n"
	.string "when it comes to battling POKéMON.\p"
	.string "That awareness makes me love battling\n"
	.string "all that much more!$"

RustboroCity_Gym_Text_RoxanneRematchNeedTwoMons:
	.string "ROXANNE: I'm so glad to see you again.\n"
	.string "I'm ROXANNE, the GYM LEADER here.\p"
	.string "I'm sure we've both experienced many\n"
	.string "battles since we last met.\p"
	.string "I would like to see how much better\n"
	.string "we've become…\p"
	.string "Oh, no…\n"
	.string "You only have one POKéMON with you?\p"
	.string "Please return with at least one more\n"
	.string "POKéMON.$"
