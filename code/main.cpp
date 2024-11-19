//Project by: Robert Parrish, Ryan Parker

#include "chaosGameFunctionality.h"

int main()
{
	// Create a window that can be drawn in
	//   sf::Window name(sf::VideoMode(w,h), windowName)
	//   - sf::VideoMode(w,h) creates a window with a width of w, and a height of h pixels
	//   - windowName is a string that will be the title of the window
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "ChaosGame", sf::Style::Default);

	//set Framerate for the window (frames_per_second)
	window.setFramerateLimit(120);

	// Random Number Seed
	srand(time(0));

	// Boolean to detect when mouse click is held
	bool mouseLeftClickHeld = false;


	
	//***********************************************
	//    main loop / game loop    //

	// run the program as long as the window is open
	while (window.isOpen())
	{
		//check if window is closed
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: the user has closed the window
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		
		short menuChoice = runMainMenu(window, event);

		std::cout << menuChoice << std::endl;

		if (menuChoice == 1)
		{
			runChaosTriangle(window, event);
		}
		else if (menuChoice == 2)
		{
			runChaos5orMoreVerts(window, event);
		}
		else if (menuChoice == 3)
		{
			runChaosFern(window, event);
		}
		else if (menuChoice == 0)
		{
			window.close();
		}
	}


	// end program
	//**********************************************
	return 0;
}
	
