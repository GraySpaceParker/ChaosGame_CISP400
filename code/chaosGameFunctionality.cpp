//Project by: Robert Parrish, Ryan Parker

#include "chaosGameFunctionality.h"

// Find a point "between" the distance starting from point1 to point2
sf::Vector2f betweenPoint(sf::Vector2f point1, sf::Vector2f point2, float between)
{
	return sf::Vector2f(  ((point1.x + point2.x) * between), 
						  ((point1.y + point2.y) * between));
}

// Function to quickly customize text for a sf::Text variable
sf::Text textSettings(const sf::Font &font, sf::String str, int charSize, const sf::Color& color, const sf::Uint32 style)
{
	sf::Text text;
	text.setFont(font);
	text.setString(str);
	text.setCharacterSize(charSize);
	text.setFillColor(color);
	text.setStyle(style);

	return text;
}

//Function that displays a menu, returning a number representing the menu option the user picked
short runMainMenu(sf::RenderWindow& window, sf::Event& event)
{
	// Boolean to detect when input is held
	bool mouseLeftClickHeld = true;
	bool keyPressHeld = true;
	
	//Condition for when to exit the menu loop
	bool menuOpen = true;

	// Choice based on menu option
	short choice = -1;

	// set font
	sf::Font font;
	if (!font.loadFromFile("LoveDays-2v7Oe.ttf"))
	{
		std::cout << "\nERROR: Failed To Load Font" << std::endl;
		window.close();
		exit(0);
	}

	
	while (menuOpen)
	{
		// check all the window's events that were triggered since the last iteration of the loop
		while (window.pollEvent(event))
		{
			// "close requested" event: the user has closed the window
			if (event.type == sf::Event::Closed) {
				menuOpen = false;
				window.close();
			}
		}

		// Vector for text position
		std::vector<sf::Vector2f> textPos;

		// Text for Menu Options
		sf::Text title = textSettings(font, "Chaos Game", 32, sf::Color::White, sf::Text::Bold | sf::Text::Underlined);
		title.setPosition(80.f, 50.f);
		
		sf::Text option1 = textSettings(font, "1) Triangle", 24, sf::Color::White);
		textPos.push_back(sf::Vector2f(20.f, 100.f));
		option1.setPosition(textPos[0]);

		sf::Text option2 = textSettings(font, "2) runChaosPentagon", 24, sf::Color::White);
		textPos.push_back(sf::Vector2f(20.f, 140.f));
		option2.setPosition(textPos[1]);

		sf::Text option3 = textSettings(font, "3) Barnsley Fern", 24, sf::Color::White);
		textPos.push_back(sf::Vector2f(20.f, 180.f));
		option3.setPosition(textPos[2]);

		sf::Text exitText = textSettings(font, "0 or Esc) Exit", 24, sf::Color::White);
		textPos.push_back(sf::Vector2f(20.f, 240.f));
		exitText.setPosition(textPos[3]);

		// Detect Mouse for selecting options / highlighting options
		sf::Vector2i mousePositionInt = sf::Mouse::getPosition(window);
		sf::Vector2f mousePosition(mousePositionInt.x, mousePositionInt.y);
		
		// Check if mouse is over an option
		float highlight_yPos = 0.f;
		bool showHighlight = false;
		if (10.f <= mousePosition.x && mousePosition.x <= 260.f)
		{
			int index = 0;
			while (index < textPos.size())
			{
				//check each option region for the mouse
				if (textPos[index].y - 3 <= mousePosition.y && mousePosition.y <= textPos[index].y + 33)
				{
					highlight_yPos = textPos[index].y - 3;
					showHighlight = true;
					
					// Detect if user clicked on an option
					if (event.type == sf::Event::MouseButtonPressed)
					{
						if (!mouseLeftClickHeld && event.mouseButton.button == sf::Mouse::Left)
						{
							choice = index + 1;
							if (choice == 4) { choice = 0; }
							menuOpen = false;
						}
					}
					else if (mouseLeftClickHeld)
					{
						mouseLeftClickHeld = false;
					}
					// End loop if mouse is in given area
					index = textPos.size();
				}
				index++;
			}
		}

		// highlight if the mouse is over an option
		sf::RectangleShape highlight(sf::Vector2f(250.f, 36.f));
		highlight.setFillColor(sf::Color(50, 200, 80));
		highlight.setPosition(10.f, highlight_yPos);
		

		// Select option if use enters the corresponding key
		// Check which key was pressed
		if (!keyPressHeld) //prevents multiple inputs from the "esc" key being pressed before this function was called
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
			{
				choice = 1;
				menuOpen = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
			{
				choice = 2;
				menuOpen = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
			{
				choice = 3;
				menuOpen = false;
			}	
			// End Menu loop and End Program
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				choice = 0;
				menuOpen = false;
			}
		}
		//Escape key is not being held down
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			keyPressHeld = false;
		}


		/*****************/
		//   draw here   //

		// clear the window with black color
		window.clear(sf::Color::Black);

		// Option Highlight
		if (showHighlight)
		{
			window.draw(highlight);
		}

		// draw text
		window.draw(title);
		window.draw(option1);
		window.draw(option2);
		window.draw(option3);
		window.draw(exitText);

		window.display();

		//               //
		/*****************/


	}
	return choice;
}


void runChaosTriangle(sf::RenderWindow& window, sf::Event& event)
{
	//Vectors to hold vertices and points
	std::vector<sf::Vector2f> vertices;
	std::vector<sf::Vector2f> points;

	// User specified points
	int userPoints = 0;
	int userPointsMax = 4;

	// Boolean to start the Chaos Game generation
	bool generateChaos = false;

	// Boolean to detect when mouse click is held
	bool mouseLeftClickHeld = true;

	// Condition for when to go back to menu
	bool endChaos = true;

	// set font for text
	sf::Font font;
	if (!font.loadFromFile("LoveDays-2v7Oe.ttf"))
	{
		std::cout << "\nERROR: Failed To Load Font" << std::endl;
		window.close();
		exit(0);
	}

	while (endChaos) 
	{
		// check all the window's events that were triggered since the last iteration of the loop
		while (window.pollEvent(event))
		{
			// "close requested" event: the user has closed the window
			if (event.type == sf::Event::Closed) {
				endChaos = false;
				window.close();
			}
		}

		// Instructional Text for user
		std::string infoStr = "";
		if (userPoints < userPointsMax - 1)
		{
			infoStr += "Create A Triangle by\nClicking Three Points\n [ ";
			infoStr += std::to_string(userPoints);
			infoStr += " ] / 3";
		}
		else if (userPoints == userPointsMax - 1)
		{
			infoStr += "Now Click Anywhere\nOn Screen to Start";
		}

		sf::Text info = textSettings(font, infoStr, 18, sf::Color::White);
		info.setPosition(10.f, 5.f);

		sf::Text exitText = textSettings(font, "\"Esc\" to exit", 18, sf::Color::White);
		exitText.setPosition(window.getSize().x - 100.f, 5.f);
		


		// Detect where the user is clicking
		// only take input on first click, take new input after mouse released
		// !!! Does not take multiple input if mouse is clicked rapidly !!!
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (!mouseLeftClickHeld && event.mouseButton.button == sf::Mouse::Left)
			{
				mouseLeftClickHeld = true;

				if (userPoints < userPointsMax) {
					if (vertices.size() < userPointsMax - 1) {
						// off set by -2 so dots are centered at mouse click
						vertices.push_back(sf::Vector2f(event.mouseButton.x - 2, event.mouseButton.y - 2));
					}
					else {
						points.push_back(sf::Vector2f(event.mouseButton.x - 2, event.mouseButton.y - 2));
					}
					userPoints++;
				}

				// after all needed userPoints obtained start Chaos Game generation
				if (userPoints == userPointsMax)
				{
					generateChaos = true;
				}
			}
		}
		//Prevent multiple inputs from a single mouse click
		else if (mouseLeftClickHeld)
		{
			mouseLeftClickHeld = false;
		}

		//Generate points for image
		if (generateChaos && points.size() < 10'000)
		{
			points.push_back(betweenPoint(points.back(), vertices[rand() % 3], 0.5));
		}


		/*****************/
		//   draw here   //

		// clear the window with black color
		window.clear(sf::Color::Black);

		// Draw Text
		window.draw(info);
		window.draw(exitText);

		// Draw points
		for (int index = 0; index < vertices.size(); index++)
		{
			if (index < userPointsMax - 1) {
				sf::CircleShape vert(2.f);
				vert.setFillColor(sf::Color(0, 255, 255));
				vert.setPosition(vertices[index]);
				window.draw(vert);
			}
		}
		for (int index = 0; index < points.size(); index++)
		{
			sf::CircleShape point(1.f);
			point.setFillColor(sf::Color(255, 255, 255));
			point.setPosition(points[index]);
			window.draw(point);
		}

		window.display();

		//               //
		/*****************/


		// Go back to main menu
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			endChaos = false;
		}
	}
}

void runChaosPentagon(sf::RenderWindow& window, sf::Event& event)
{
	bool endChaos = true;
	
	//Text and Font
	Text text;
	Font font;
	if (!font.loadFromFile("LoveDays-2v7Oe.ttf"))
	{
		throw("Font failed to load");
	}
	text.setFont(font);
	text.setCharacterSize(25);
	text.setColor(Color::Red);
	text.setString("1. Left click 5 points to outline a pentagon\n\n2. Left click one more time in the encompassed outline");

	

	//Declarations
	vector<Vector2f> vertices;
	vector<Vector2f> points;
	double randomVertex = rand() % 5;                 
	double randomPrev = randomVertex;

	while (endChaos)
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		while (window.pollEvent(event))
		{
		    if (event.type == Event::Closed)
		    {
					// Quit the game when the window is closed
					endChaos = false;
					window.close();
		    }
		    if (event.type == sf::Event::MouseButtonPressed)
		    {
			if (event.mouseButton.button == sf::Mouse::Left)
			{
			    std::cout << "the left button was pressed" << std::endl;
			    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
			    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
	
			    if(vertices.size() < 5)
			    {
				vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
			    }
			    else if(points.size() == 0)
			    {
				///fourth click
				///push back to points vector
				points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
			    }
			}
		    }
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			endChaos = false;
		}
		/*
		****************************************
		Update
		****************************************
		*/
		
		if(points.size() > 0)
		{
		    ///generate more point(s)
		    ///select random vertex
		    
		    double count = points.size() - 1;
		    while (randomVertex == randomPrev)
		    {
			randomVertex = rand() % 5;
		    }
		    randomPrev = randomVertex;    
			
		    ///calculate midpoint between random vertex and the last point in the vector
		    ///push back the newly generated coord.
		    double midpointX = (vertices.at(randomVertex).x + points.at(count).x) * 0.5;
		    double midpointY = (vertices.at(randomVertex).y + points.at(count).y) * 0.5;
		    points.push_back(Vector2f(midpointX, midpointY));
		}
	
		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		window.draw(text);
		for(int i = 0; i < vertices.size(); i++)
		{
		    RectangleShape rect(Vector2f(4,4));
		    rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
		    rect.setFillColor(Color::Blue);
		    window.draw(rect);
		}
		for(int i = 0; i < points.size(); i++)
		{
		    RectangleShape rect(Vector2f(10,10));
		    rect.setPosition(Vector2f(points[i].x, points[i].y));
		    rect.setFillColor(Color::Blue);
		    window.draw(rect);
		}
		window.display();
	}
}

void runChaosFern(sf::RenderWindow& window, sf::Event& event)
{
	//Vectors to hold points
	std::vector<sf::Vector2f> points;

	// Boolean to start the Chaos Game generation
	bool generateChaos = false;

	// Boolean to detect when mouse click is held
	bool mouseLeftClickHeld = true;

	// Condition for when to go back to menu
	bool endChaos = true;

	//Fern Generation Iterations
	int fernIterations = 10'000;

	//Variables needed for fern generation
	float x, y, xn, yn;
	x = y = xn = yn = 0.f;

	// set font for text
	sf::Font font;
	if (!font.loadFromFile("LoveDays-2v7Oe.ttf"))
	{
		std::cout << "\nERROR: Failed To Load Font" << std::endl;
		window.close();
		exit(0);
	}

	while (endChaos)
	{
		// check all the window's events that were triggered since the last iteration of the loop
		while (window.pollEvent(event))
		{
			// "close requested" event: the user has closed the window
			if (event.type == sf::Event::Closed) {
				endChaos = false;
				window.close();
			}
		}

		//// Detect where the user is clicking
		//// only take input on first click, take new input after mouse released
		//// !!! Does not take multiple input if mouse is clicked rapidly !!!
		if (event.type == sf::Event::MouseButtonPressed && !generateChaos)
		{
			if (!mouseLeftClickHeld && event.mouseButton.button == sf::Mouse::Left)
			{
				generateChaos = true;
			}
		}
		//Prevent multiple inputs from mouse (carried over from menu)
		else if (mouseLeftClickHeld)
		{
			mouseLeftClickHeld = false;
		}

		// Generate Fern
		if (generateChaos && points.size() < fernIterations)
		{
			int r = rand() % 100;
			
			if (r < 1)
			{
				xn = 0;
				yn = 0.16 * y;
			}
			else if (r < 86)
			{
				xn = 0.85 * x + 0.04 * y;
				yn = -0.04 * x + 0.85 * y + 1.6;
			}
			else if (r < 93)
			{
				xn = 0.2 * x - 0.26 * y;
				yn = 0.23 * x + 0.22 * y + 1.6;
			}
			else
			{
				xn = -0.15 * x + 0.28 * y;
				yn = 0.26 * x + 0.24 * y + 0.44;
			}

			points.push_back(sf::Vector2f((xn * (window.getSize().x / 10)) + window.getSize().x / 2, yn * (window.getSize().y / 10)));

			x = xn;
			y = yn;
		}
		
		// Instructional Text for user
		std::string infoStr = "";
		if (!points.size())
		{
			infoStr += "Click To Generate Upsidedown Fern";
			infoStr += "\nIt takes a bit to generate...";
		}

		sf::Text info = textSettings(font, infoStr, 18, sf::Color::White);
		info.setPosition(10.f, 5.f);

		sf::Text exitText = textSettings(font, "\"Esc\" to exit", 18, sf::Color::White);
		exitText.setPosition(window.getSize().x - 100.f, 5.f);



		/*****************/
		//   draw here   //

		// clear the window with black color
		window.clear(sf::Color::Black);

		// Draw Text
		window.draw(info);
		window.draw(exitText);

		for (int index = 0; index < points.size(); index++)
		{
			sf::CircleShape point(1.f);
			point.setFillColor(sf::Color(20, 255, 20));
			point.setPosition(points[index]);
			window.draw(point);
		}

		window.display();

		//               //
		/*****************/


		// Go back to main menu
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			endChaos = false;
		}
	}
}
