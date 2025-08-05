MauvilleCity_House2_MapScripts::
	.byte 0

MauvilleCity_House2_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_COIN_CASE, MauvilleCity_House2_EventScript_ReceivedCoinCase
	msgbox MauvilleCity_House2_Text_BuyHarborMailAtSlateport, MSGBOX_DEFAULT
	checkmoney 1000
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_House2_EventScript_AskToTradeForHarborMail
	release
	end

MauvilleCity_House2_EventScript_AskToTradeForHarborMail::
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	msgbox MauvilleCity_House2_Text_TradeHarborMailForCoinCase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_House2_EventScript_AcceptTrade
	goto_if_eq VAR_RESULT, NO, MauvilleCity_House2_EventScript_DeclineTrade
	end

MauvilleCity_House2_EventScript_AcceptTrade::
	msgbox MauvilleCity_House2_Text_IllTradeYouCoinCase, MSGBOX_DEFAULT
	giveitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	removemoney 1000
	setflag FLAG_RECEIVED_COIN_CASE
	goto MauvilleCity_House2_EventScript_ReceivedCoinCase
	end

MauvilleCity_House2_EventScript_ReceivedCoinCase::
	msgbox MauvilleCity_House2_Text_UseCoinCaseAtGameCorner, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House2_EventScript_DeclineTrade::
	msgbox MauvilleCity_House2_Text_ThatsDisappointing, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House2_Text_BuyHarborMailAtSlateport:
	.string "Sigh… That no-good husband of mine\n"
	.string "lost all our money at the GAME CORNER.\p"
	.string "We can't even pay the bills now…$"

MauvilleCity_House2_Text_TradeHarborMailForCoinCase:
	.string "I'm selling his COIN CASE for 1000.\n"
	.string "Will you take it off my hands?$"

MauvilleCity_House2_Text_IllTradeYouCoinCase:
	.string "Thank you… Every bit helps.\n"
	.string "Here, take this COIN CASE.$"

MauvilleCity_House2_Text_UseCoinCaseAtGameCorner:
	.string "That COIN CASE can be used\n"
	.string "at the GAME CORNER.\p"
	.string "Just don’t end up like him…$"

MauvilleCity_House2_Text_ThatsDisappointing:
	.string "Oh… That's disappointing.\p"
	.string "You can't afford it?\n"
	.string "Hmph… Just like my husband.$"
	.string "I was hoping someone decent\n"
	.string "would take it off my hands.$"

