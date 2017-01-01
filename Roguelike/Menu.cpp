#include "stdafx.h"
#include "Menu.h"
#include "Game.h"

Menu *Menu::s_pInstance = nullptr;

bool Menu::run(Buffer &buffer)
{
	int menuChoice = 1;
	while (true)
	{
		buffer.clear();

		buffer.drawLine("-----------------------------------------------", 0, 1);
		buffer.drawLine("                    BENEATH", 1, 1);
		buffer.drawLine("-----------------------------------------------", 2, 1);
		if (menuChoice == 1)
		{
			buffer.drawLine("@@@@@@@@@@->START<-@@@@@@@@@@", 3, 10);
			buffer.drawLine("         QUICK START         ", 4, 10);
			buffer.drawLine("          EXIT GAME          ", 5, 10);
		}
		else if (menuChoice == 2)
		{
			buffer.drawLine("            START", 3, 10);
			buffer.drawLine("@@@@@@@->QUICK START<-@@@@@@@", 4, 10);
			buffer.drawLine("          EXIT GAME          ", 5, 10);
		}
		else if (menuChoice == 3)
		{
			buffer.drawLine("            START", 3, 10);
			buffer.drawLine("         QUICK START         ", 4, 10);
			buffer.drawLine("@@@@@@@@->EXIT GAME<-@@@@@@@@", 5, 10);
		}
		int lineNumber = 6;
		buffer.drawLine("\\_                                      .')   ", lineNumber++);
		buffer.drawLine("  \\                                    (_  )     ", lineNumber++);
		buffer.drawLine("   \\              /'\\", lineNumber++);
		buffer.drawLine("    \\_         .,'   \\", lineNumber++);
		buffer.drawLine("      \\      _/       \\_", lineNumber++);
		buffer.drawLine("       \\    /           \\                        _", lineNumber++);
		buffer.drawLine("        \\  /',.,''\\      \\_                   (`  ).", lineNumber++);
		buffer.drawLine("      _  \\/   /    ',../',.\\                (       '`. .", lineNumber++);
		buffer.drawLine("    _/m\\  \\  /    |         \\               (         ) )", lineNumber++);
		buffer.drawLine("   /MMmm\\  \\_     |          \\               ` __.:'-'", lineNumber++);
		buffer.drawLine("  |MMMMmm|   \\__   \\          \\_", lineNumber++);
		buffer.drawLine(" /MMMMMMm|      \\   \\           \\", lineNumber++);
		buffer.drawLine(" |MMMMMMmm\\      \\___            \\_", lineNumber++);
		buffer.drawLine("|MMMMMMMMmm|____.'  /\\_            \\", lineNumber++);
		buffer.drawLine("'.,___________...,,'   \\            \\", lineNumber++);
		buffer.drawLine("      \\          |      \\    |__     \\", lineNumber++);
		buffer.drawLine("      |           \\      \\_     \\     \\", lineNumber++);
		buffer.drawLine("                           \\     \\     \\_ ", lineNumber++);
		buffer.print();

		char input = _getch();
		switch (input)
		{
		case Game::MOVE_SOUTH:
			(menuChoice == 3) ? menuChoice = 3 : menuChoice++;
			break;
		case Game::MOVE_NORTH:
			(menuChoice == 1) ? menuChoice = 1 : menuChoice--;
			break;
		case Game::ACCEPT:
			if (menuChoice == 3)
				return false;
			if (menuChoice == 1 || menuChoice == 2)
			{
				if (menuChoice == 1)
					runStory(buffer);
				return true;
			}
			break;
		case Game::ESCAPE:
			return false;
			break;
		}
	}
}

void Menu::runStory(Buffer &buffer)
{
	buffer.clear();
	int lineNumber = 0;
	buffer.drawLine("----------------------------------------------------------------", lineNumber++, 1);
	buffer.drawLine("            CLASSIFIED DOCUMENT: PRIORITY CLASS 1", lineNumber++, 1);
	buffer.drawLine("----------------------------------------------------------------", lineNumber++, 1);
	buffer.drawLine("Date:                     September 17, 1944", lineNumber++, 1);
	buffer.drawLine("To:                       Herr. Max Zimmer", lineNumber++, 1);
	buffer.drawLine("                          Ahnenerbe Institute", lineNumber++, 1);
	buffer.drawLine("                          [XX] Potsdammer Platz, Berlin", lineNumber++, 1);
	buffer.drawLine("From:                     [XXXXXXXXXXXXXXX]", lineNumber++, 1);
	buffer.drawLine("Subject:                  Avenues of Victory", lineNumber++, 1);
	buffer.drawLine("   My dear Max! It seems only yesterday that both of us were", lineNumber++, 1);
	buffer.drawLine("sitting in the caf\x82 Les Deux Magots, comparing lecture notes,", lineNumber++, 1);
	buffer.drawLine("soaking in the atmosphere of Saint-Germain-des-Pr\x82s, and", lineNumber++, 1);
	buffer.drawLine("deciding what we would do with our lives. How time flies. I", lineNumber++, 1);
	buffer.drawLine("suppose you haven't seen Jenice since the war started. That's a", lineNumber++, 1);
	buffer.drawLine("shame - you two were so good together.", lineNumber++, 1);
	buffer.drawLine("   When [XXXXX] passed your name to me in connection with the", lineNumber++, 1);
	buffer.drawLine("Ahnenerbe Institute, you can imagine how surprised I was. Max,", lineNumber++, 1);
	buffer.drawLine("outside of a university?! But I see now that you've managed to", lineNumber++, 1);
	buffer.drawLine("find the only route available in this whole war through which to", lineNumber++, 1);
	buffer.drawLine("continue your archaeological pursuits. Indeed, it's with your", lineNumber++, 1);
	buffer.drawLine("expertise in mind that I am writing this letter.", lineNumber++, 1);
	buffer.drawLine("   Those surrounding the F\x81hrer have made it very clear in the", lineNumber++, 1);
	buffer.drawLine("last few months that the Reich's days are numbered. Whilst the", lineNumber++, 1);
	buffer.drawLine("mood in top HQ has been overwhelmingly positive, it's obvious", lineNumber++, 1);
	buffer.print();
	_getch();

	buffer.clear();
	lineNumber = 0;
	buffer.drawLine("----------------------------------------------------------------", lineNumber++, 1);
	buffer.drawLine("that the same is not true on the ground. Indeed, some", lineNumber++, 1);
	buffer.drawLine("trustworthy intelligence has led me to believe that the English", lineNumber++, 1);
	buffer.drawLine("might push through into Belgium before the week is out. I", lineNumber++, 1);
	buffer.drawLine("have therefore been authorised, on a highly classified basis, to", lineNumber++, 1);
	buffer.drawLine("explore other... \"avenues of victory\".", lineNumber++, 1);
	buffer.drawLine("   I have in front of me a large dossier which you will", lineNumber++, 1);
	buffer.drawLine("hopefully have in your possession by the time you read this", lineNumber++, 1);
	buffer.drawLine("letter. I have noted five key sites, ranging across the South", lineNumber++, 1);
	buffer.drawLine("Americas, which are all highly likely to render a positive", lineNumber++, 1);
	buffer.drawLine("result upon deeper archaeological examination. You are ordered", lineNumber++, 1);
	buffer.drawLine("to send a team to each site, under the utmost secrecy, to", lineNumber++, 1);
	buffer.drawLine("unearth any material remains of benefit to the Reich. It is a", lineNumber++, 1);
	buffer.drawLine("tricky thing to mix ancient literature, archaeology and science,", lineNumber++, 1);
	buffer.drawLine("but if anyone can do it - you can, Max.", lineNumber++, 1);
	buffer.drawLine("----------------------------------------------------------------", lineNumber++, 1);
	buffer.drawLine("      END OF COMMUNICATION", lineNumber++, 1);
	buffer.drawLine("----------------------------------------------------------------", lineNumber++, 1);
	buffer.print();
	_getch();

	buffer.clear();
	lineNumber = 0;
	buffer.drawLine("----------------------------------------------------------------", lineNumber++, 1);
	buffer.drawLine("            CLASSIFIED DOCUMENT: PRIORITY CLASS 1", lineNumber++, 1);
	buffer.drawLine("----------------------------------------------------------------", lineNumber++, 1);
	buffer.drawLine("Date:                     September 30, 1944", lineNumber++, 1);
	buffer.drawLine("To:                       Hauptmann Schmidt", lineNumber++, 1);
	buffer.drawLine("                          [XXXXXXXXX]", lineNumber++, 1);
	buffer.drawLine("From:                     Herr. Max Zimmer", lineNumber++, 1);
	buffer.drawLine("Subject:                  Requisition Order [XXXXX]", lineNumber++, 1);
	buffer.drawLine("   Mr. Schmidt, I really was hoping I wouldn't have to send", lineNumber++, 1);
	buffer.drawLine("ANOTHER letter. I have orders from the highest place that my", lineNumber++, 1);
	buffer.drawLine("team and I are to have all the resources we request. Your", lineNumber++, 1);
	buffer.drawLine("superiors are fully aware that I am not military, yet this has", lineNumber++, 1);
	buffer.drawLine("not inhibited the extent of their support, and neither should it", lineNumber++, 1);
	buffer.drawLine("yours. I do not want to go over your head on this, but if I have", lineNumber++, 1);
	buffer.drawLine("to, I will.", lineNumber++, 1);
	buffer.drawLine("----------------------------------------------------------------", lineNumber++, 1);
	buffer.drawLine("      END OF COMMUNICATION", lineNumber++, 1);
	buffer.drawLine("----------------------------------------------------------------", lineNumber++, 1);
	buffer.print();
	_getch();

	buffer.clear();
	lineNumber = 0;
	buffer.drawLine("----------------------------------------------------------------", lineNumber++, 1);
	buffer.drawLine("            CLASSIFIED DOCUMENT: PRIORITY CLASS 1", lineNumber++, 1);
	buffer.drawLine("----------------------------------------------------------------", lineNumber++, 1);
	buffer.drawLine("Date:                     October 22, 1944", lineNumber++, 1);
	buffer.drawLine("To:                       Herr. Max Zimmer", lineNumber++, 1);
	buffer.drawLine("                          Ahnenerbe Institute", lineNumber++, 1);
	buffer.drawLine("                          [XX] Potsdammer Platz, Berlin", lineNumber++, 1);
	buffer.drawLine("From:                     [XXXXXXXXXXXXXXX]", lineNumber++, 1);
	buffer.drawLine("Subject:                  Operation Delays", lineNumber++, 1);
	buffer.drawLine("   Max, we are old friends, and I regret having to write this", lineNumber++, 1);
	buffer.drawLine("letter. It has been over a month since I ordered you to gather", lineNumber++, 1);
	buffer.drawLine("your men. I am fed up of hearing about intransigent lieutenants", lineNumber++, 1);
	buffer.drawLine("and equipment delays. A few days ago, Athens fell to the British", lineNumber++, 1);
	buffer.drawLine("and all intelligence indicates that Aachen is soon to follow.", lineNumber++, 1);
	buffer.drawLine("The need for an alternate solution to our current predicament", lineNumber++, 1);
	buffer.drawLine("is growing every day - there is no time to wait for your", lineNumber++, 1);
	buffer.drawLine("childish approach to authority. Can you imagine the devestation", lineNumber++, 1);
	buffer.drawLine("if those barbarians in the east break through our lines in the ", lineNumber++, 1);
	buffer.drawLine("winter and lay waste our fatherland!? I am ordering you to leave", lineNumber++, 1);
	buffer.drawLine("to the Americas as soon as you receive this letter. I'm sure I", lineNumber++, 1);
	buffer.drawLine("do not need to elaborate on the consequences of failure.", lineNumber++, 1);
	buffer.drawLine("----------------------------------------------------------------", lineNumber++, 1);
	buffer.drawLine("      END OF COMMUNICATION", lineNumber++, 1);
	buffer.drawLine("----------------------------------------------------------------", lineNumber++, 1);
	buffer.print();
	_getch();

	buffer.clear();
	lineNumber = 0;
	buffer.drawLine("----------------------------------------------------------------", lineNumber++, 1);
	buffer.drawLine("           COCKPIT: ", lineNumber++, 1);
	buffer.drawLine("----------------------------------------------------------------", lineNumber++, 1);
	buffer.drawLine("Radio:     We are under heavy fire, I repeat, we are under fire!", lineNumber++, 1);
	buffer.drawLine("           The wing... the wing has taken a beating from the ", lineNumber++, 1);
	buffer.drawLine("           [STATIC]. We're... Jesus, we're going down, we're", lineNumber++, 1);
	buffer.drawLine("           going down... I can't fly around the [STATIC], we're", lineNumber++, 1);
	buffer.drawLine("           goi[SIGNAL LOST].", lineNumber++, 1);
	buffer.drawLine("Max:       What on earth was that?", lineNumber++, 1);
	buffer.drawLine("Co-Pilot:  It's number two, Sir, I think it's down...", lineNumber++, 1);
	buffer.drawLine("Max:       \"Down\"? What the hell do you mean?", lineNumber++, 1);
	buffer.drawLine("Co-Pilot:  I don't know, Sir. It looks like... it looks like", lineNumber++, 1);
	buffer.drawLine("           it's crashed into the side of the mountain.", lineNumber++, 1);
	buffer.drawLine("Max:       Oh Jesus, I can see the wreckage...[GUNSHOTS] Ah", lineNumber++, 1);
	buffer.drawLine("           my damn leg... [YELLING] Land the plane now, land the", lineNumber++, 1);
	buffer.drawLine("           plane!", lineNumber++, 1);
	buffer.drawLine("Co-Pilot:  I can't, Sir, there's no safe landing place.", lineNumber++, 1);
	buffer.drawLine("Max:       I don't care if there isn't a safe landing place,", lineNumber++, 1);
	buffer.drawLine("           either you take this thing down, or it'll be shot", lineNumber++, 1);
	buffer.drawLine("           out of the sky! [VOICES] Get back to your damn", lineNumber++, 1);
	buffer.drawLine("           seats!", lineNumber++, 1);
	buffer.drawLine("Co-Pilot:  I... I might be able to take us down by that cliff.", lineNumber++, 1);
	buffer.drawLine("           But, but it won't be a nice landing...", lineNumber++, 1);
	buffer.drawLine("Max:       Fine, fine. Land the plane. Land the [GUNSHOTS].", lineNumber++, 1);
	buffer.print();
	_getch();

	buffer.clear();
	lineNumber = 0;
	buffer.drawLine("----------------------------------------------------------------", lineNumber++, 1);
	buffer.drawLine("Co-Pilot:  Sir? Sir? Oh God, he's bleeding... he's bleeding.", lineNumber++, 1);
	buffer.drawLine("           [SHOUTING] I'm taking her down here! [GUNSHOTS]", lineNumber++, 1);
	buffer.drawLine("           Prepare for landing! Oh God, oh God, oh Go[STATIC].", lineNumber++, 1);
	buffer.print();
	_getch();

	buffer.clear();
	lineNumber = 2;
	int indent = 10;
	buffer.drawLine("              ##### | #####", lineNumber++, indent);
	buffer.drawLine("             # _ _ #|# _ _ #", lineNumber++, indent);
	buffer.drawLine("             #      |      #", lineNumber++, indent);
	buffer.drawLine("       |       ############", lineNumber++, indent);
	buffer.drawLine("                   # #", lineNumber++, indent);
	buffer.drawLine("|                  # #", lineNumber++, indent);
	buffer.drawLine("                  #   #", lineNumber++, indent);
	buffer.drawLine("       |     |    #   #      |        |", lineNumber++, indent);
	buffer.drawLine("|  |             #     #               |", lineNumber++, indent);
	buffer.drawLine("       | |   |   # .-. #         |", lineNumber++, indent);
	buffer.drawLine("                 #( O )#    |    |     |", lineNumber++, indent);
	buffer.drawLine("|  ################. .###############  |", lineNumber++, indent);
	buffer.drawLine(" ##  _ _|____|     ###     |_ __| _  ##", lineNumber++, indent);
	buffer.drawLine("#  |                                |  #", lineNumber++, indent);
	buffer.drawLine("#  |    |    |    |   |    |    |   |  #", lineNumber++, indent);
	buffer.drawLine(" ######################################", lineNumber++, indent);
	buffer.drawLine("                 #     #", lineNumber++, indent);
	buffer.drawLine("                  #####", lineNumber++, indent);
	buffer.drawLine("             OOOOOOO|OOOOOOO", lineNumber++, indent);
	buffer.print();
	_getch();

	buffer.clear();
	buffer.print();
	_getch();
}