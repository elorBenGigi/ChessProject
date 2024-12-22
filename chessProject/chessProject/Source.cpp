/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project,
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include "board.h"

#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::string;


void main()
{
	srand(time_t(NULL));
	char* message = nullptr;
	Pipe p;
	King* otherKing = nullptr;
	Board board = Board();
	bool isConnect = false;
	string ans;

	system("start chessGraphics.exe");
	Sleep(MODERATE_SLEEP);
	isConnect = p.connect();


	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(MODERATE_SLEEP);
			isConnect = p.connect();
		}
		else
		{
			p.close();
			return;
		}
	}


	char msgToGraphics[BUFFER_SIZE];
	// msgToGraphics should contain the board string accord the protocol

	message = board.initialBoardString();
	strcpy_s(msgToGraphics, message);

	p.sendMessageToGraphics(msgToGraphics);
	delete message;
	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		// should handle the string the sent from graphics
		// according the protocol. Ex: e2e4           (move e2 to e4)

		char resultCode = board.makeMove(msgFromGraphics);

		strcpy_s(msgToGraphics, &resultCode); // msgToGraphics should contain the result of the operation
		msgToGraphics[1] = '\0';
		

		/*
		
			I JUST CANT GET THE CHECKMATE TO WORK ):
		
		*/


		if (resultCode == CHECKMATE) 
		{
			resultCode = VALID_MOVE_CHECK;
			strcpy_s(msgToGraphics, &resultCode); // msgToGraphics should contain the result of the operation
			msgToGraphics[1] = '\0';
			p.sendMessageToGraphics(msgToGraphics);
			board.printBoard();
			msgFromGraphics = p.getMessageFromGraphics();

			resultCode = CHECKMATE;
			strcpy_s(msgToGraphics, &resultCode); // msgToGraphics should contain the result of the operation
			msgToGraphics[1] = '\0';
			p.sendMessageToGraphics(msgToGraphics);
			std::cout << "CHECKMATE\n";
			msgFromGraphics = p.getMessageFromGraphics();
		}
		else
		{
			p.sendMessageToGraphics(msgToGraphics);
			board.printBoard();

			// get message from graphics
			msgFromGraphics = p.getMessageFromGraphics();
		}
	}

	p.close();
}