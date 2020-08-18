#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <cstdlib>
#include <string>
#include <conio.h>

int WinMain()
{
	int const size = 4;
	int gameMode = 0;
	int max = 2;
	sf::RenderWindow window(sf::VideoMode(400, 400), "2048!");
	sf::Font font;
	if (!font.loadFromFile("TIMES.ttf"))
	{
		return(0);
	}
	sf::Text text[4][4];
	sf::Text endText;
	sf::RectangleShape rect[size][size];
	int fillTable[size][size];
	endText.setFont(font);
	endText.setCharacterSize(42);
	endText.setFillColor(sf::Color(220, 220, 220, 255));
	endText.setString("Przegrana, nacisnij \nspacje aby wyjsc");
	endText.setPosition(50.0, 50.0);

	for (int a = 0; a < size; a++)
	{
		for (int b = 0; b < size; b++)
		{
			fillTable[a][b] = 0;
			text[a][b].setFont(font);
			text[a][b].setCharacterSize(42);
			text[a][b].setFillColor(sf::Color(0, 0, 0, 255));
		}
	}
	int r1 = rand() % 4;
	int r2 = rand() % 4;//numer wiersza
	fillTable[r1][r2] = 2;//Wpisujemy dwojke 
	text[r1][r2].setString(std::to_string(fillTable[r1][r2]));//Ustawiamy text na wartoœæ która jest w tablicy liczb
	do
	{
		r1 = rand() % 4;//losujemy miejsce na 2 liczbe (rozne od wczesniejszego)
		r2 = rand() % 4;
	} while (fillTable[r1][r2]==2);
	fillTable[r1][r2] = 2;
	text[r1][r2].setString(std::to_string(fillTable[r1][r2]));
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			rect[i][j].setSize(sf::Vector2f(96, 96));
			rect[i][j].setPosition((float)i * 100, (float)j * 100);
			rect[i][j].setFillColor(sf::Color(255, 235, 205, 255));
			rect[i][j].setOutlineColor(sf::Color(210, 190, 165, 255));
			rect[i][j].setOutlineThickness(2.0);//ustawienia dla kwadratow
		}
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && gameMode != 0)
			{
				window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && gameMode == 0)
			{

				for (int i = 0; i < 3; i++)
				{
					for (int k = 3; k >= 0; k--)
					{
						if (fillTable[k][i] == 0)
						{
							continue;
						}
						else if (fillTable[k][i] == fillTable[k][i + 1])
						{
							fillTable[k][i] *= 2;
							text[k][i].setString(std::to_string(fillTable[k][i]));
							fillTable[k][i + 1] = 0;
							text[k][i + 1].setString("");
						}
						else if (i == 0 && fillTable[k][i] == fillTable[k][2] && fillTable[k][1] == 0)
						{
							fillTable[k][i] *= 2;
							text[k][i].setString(std::to_string(fillTable[k][i]));
							fillTable[k][2] = 0;
							text[k][2].setString("");
						}
						else if (i == 0 && fillTable[k][i] == fillTable[k][3] && fillTable[k][1] == 0 && fillTable[k][2] == 0)
						{
							fillTable[k][i] *= 2;
							text[k][i].setString(std::to_string(fillTable[k][i]));
							fillTable[k][3] = 0;
							text[k][3].setString("");
						}
						else if (i == 1 && fillTable[k][i] == fillTable[k][3] && fillTable[k][2] == 0)
						{
							fillTable[k][i] *= 2;
							text[k][i].setString(std::to_string(fillTable[k][i]));
							fillTable[k][3] = 0;
							text[k][3].setString("");
						}
						if (max < fillTable[k][i])
						{
							max = fillTable[k][i];
							if (max == 2048)
							{
								gameMode = 1;
								endText.setString("Zwyciestwo, nacisnij \n spacje aby wyjsc");
							}
						}
					}
				}
				for (int i = 0; i < 3; i++)
				{
					int x = 3;
					do
					{
						for (int k = 0; k <= 3; k++)
						{
							if (fillTable[k][i] == 0)
							{
								for (int l = i; l < 3; l++)
								{
									fillTable[k][l] = fillTable[k][l+1];
									text[k][l].setString(std::to_string(fillTable[k][l+1]));
								}
								fillTable[k][3] = 0;
								text[k][3].setString("");
							}
						}
						x--;
					} while (x >= 0);
				}
				bool freeField = false;
				for (int f = 0; f <= 3; f++)
				{
					for (int g = 0; g <= 3; g++)
					{
						if (fillTable[f][g] == 0)
						{
							freeField = true;
							break;
						}
					}
				}
				if (freeField)
				{
					int a = 0;
					int b = 0;
					do
					{
						a = rand() % 4;
						b = rand() % 4;
					} while (fillTable[a][b] != 0);
					fillTable[a][b] = 2;
					text[a][b].setString(std::to_string(fillTable[a][b]));
				}
				else
				{
					gameMode = 1;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && gameMode == 0)
			{
				for (int k = 3; k > 0; k--)//k - kolumny (dla kazdej kolumny od ostatniej do pierwszej)
				{
					for (int i = 3; i >= 0; i--)//dla kazdego wiersza od ostatniego do pierwszego
					{
						if (fillTable[k][i] == 0)//sprawdzamy czy pole nie zawiera liczby
						{
							continue;
						}
						else if (fillTable[k][i]==fillTable[k-1][i])//Pierwszy przypadek je¿eli dwie s¹siednie kolumny w wierszu 'i' s¹ sobie równe (np. dwie czwórki)
						{											//to pomnó¿ wartoœæ kolumny k razy dwa a kolumne k-1 wyzeruj
							fillTable[k][i] *= 2;
							text[k][i].setString(std::to_string(fillTable[k][i]));
							fillTable[k-1][i] = 0;
							text[k-1][i].setString("");
						}
						else if(k == 2 && fillTable[k][i] == fillTable[0][i] && fillTable[1][i] == 0)//jezeli numer aktualnej kolumny to 2 (przed ostatnia) i wartoœæ w drugiej kolumnie i zerowej s¹ równe
						{																			// i wartoœæ w kolumnie pierwszej jest równa zero to pomnó¿ wartoœæ w 2 kolumnbie razy dwa
							fillTable[k][i] *= 2;
							text[k][i].setString(std::to_string(fillTable[k][i]));
							fillTable[0][i] = 0;
							text[0][i].setString("");
						}
						else if (k == 3 && fillTable[k][i] == fillTable[0][i] && fillTable[1][i] == 0 && fillTable[2][i] == 0)
						{
							fillTable[k][i] *= 2;
							text[k][i].setString(std::to_string(fillTable[k][i]));
							fillTable[0][i] = 0;
							text[0][i].setString("");
						}
						else if (k == 3 && fillTable[k][i] == fillTable[1][i] && fillTable[2][i] == 0)
						{
							fillTable[k][i] *= 2;
							text[k][i].setString(std::to_string(fillTable[k][i]));
							fillTable[1][i] = 0;
							text[1][i].setString("");
						}
						if (max < fillTable[k][i])
						{
							max = fillTable[k][i];
							if (max == 2048)
							{
								gameMode = 1;
								endText.setString("Zwyciestwo, nacisnij spacje aby wyjsc");
							}
						}
					}
				}
				for (int k = 3; k > 0; k--)
				{
					int x = 3;
					do
					{
						for (int i = 3; i >= 0; i--)
						{
							if (fillTable[k][i] == 0)
							{
								for (int l = k; l > 0; l--)
								{
									fillTable[l][i] = fillTable[l - 1][i];
									text[l][i].setString(std::to_string(fillTable[l - 1][i]));
								}
								fillTable[0][i] = 0;
								text[0][i].setString("");
							}
						}
						x--;
					} while (x>=0);		
				}
				bool freeField = false;
				for (int f = 0; f <= 3; f++)
				{
					for (int g = 0; g <= 3; g++)
					{
						if (fillTable[f][g] == 0)
						{
							freeField = true;
							break;
						}
					}
				}
				if (freeField)
				{
					int a = 0;
					int b = 0;
					do
					{
						a = rand() % 4;
						b = rand() % 4;
					} while (fillTable[a][b] != 0);
					fillTable[a][b] = 2;
					text[a][b].setString(std::to_string(fillTable[a][b]));
				}
				else
				{
					gameMode = 1;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && gameMode == 0)
			{
				for (int k = 0; k < 3; k++)//k - kolumny (dla kazdej kolumny od pierwszej do ostatniej )
				{
					for (int i = 0; i <=3; i++)//dla kazdego wiersza od ostatniego do pierwszego
					{
						if (fillTable[k][i] == 0)//sprawdzamy czy pole nie zawiera liczby
						{
							continue;
						}
						else if (fillTable[k][i] == fillTable[k + 1][i])//je¿eli dwie s¹siednie kolumny w wierszu 'i' s¹ sobie równe (np. dwie czwórki)
						{											//to pomnó¿ wartoœæ kolumny k razy dwa a kolumne k+1 wyzeruj
							fillTable[k][i] *= 2;
							text[k][i].setString(std::to_string(fillTable[k][i]));
							fillTable[k + 1][i] = 0;
							text[k + 1][i].setString("");
						}
						else if (k == 0 && fillTable[k][i] == fillTable[2][i] && fillTable[1][i] == 0 )// jezeli wartosc w 0 i 2 jest rowna a w 1 jest 0 
						{																			
							fillTable[k][i] *= 2;// mnozy te same w 0
							text[k][i].setString(std::to_string(fillTable[k][i]));
							fillTable[2][i] = 0;//zeruje 2
							text[2][i].setString("");
						}
						else if (k == 0 && fillTable[k][i] == fillTable[3][i] && fillTable[1][i] == 0 && fillTable[2][i] == 0)// jezeli w 0 i 3 jest ta sama wartosc a w 1 i2 jest 0 
						{
							fillTable[k][i] *= 2;// mnozy wartosc w 0
							text[k][i].setString(std::to_string(fillTable[k][i]));
							fillTable[3][i] = 0;//zeruje 3
							text[3][i].setString("");
						}
						else if (k == 1 && fillTable[k][i] == fillTable[3][i] && fillTable[2][i] == 0)//jezeli w 1 i 3 jest ta sama wartoœæ a w 2 jest 0 
						{
							fillTable[k][i] *= 2;//mnozy wartosc w 1
							text[k][i].setString(std::to_string(fillTable[k][i]));
							fillTable[3][i] = 0;// zeruje 3
							text[3][i].setString("");
						}
						if (max < fillTable[k][i])
						{
							max = fillTable[k][i];
							if (max == 2048)
							{
								gameMode = 1;
								endText.setString("Zwyciestwo, nacisnij spacje aby wyjsc");
							}
						}
					}
				}
				for (int k = 0; k < 3; k++)
				{
					int x = 3;
					do
					{
						for (int i = 0; i <= 3; i++)
						{
							if (fillTable[k][i] == 0)
							{
								for (int l = k; l < 3; l++)
								{
									fillTable[l][i] = fillTable[l + 1][i];
									text[l][i].setString(std::to_string(fillTable[l + 1][i]));
								}
								fillTable[3][i] = 0;
								text[3][i].setString("");
							}
						}
						x--;
					} while (x >= 0);
				}
				bool freeField = false;
				for (int f = 0; f <= 3; f++)
				{
					for (int g = 0; g <= 3; g++)
					{
						if (fillTable[f][g] == 0)
						{
							freeField = true;
							break;
						}
					}
				}
				if (freeField)
				{
					int a = 0;
					int b = 0;
					do
					{
						a = rand() % 4;
						b = rand() % 4;
					} while (fillTable[a][b] != 0);
					fillTable[a][b] = 2;
					text[a][b].setString(std::to_string(fillTable[a][b]));
				}
				else
				{
					gameMode = 1;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && gameMode == 0)
			{
				for (int i = 3; i > 0; i--)
				{
					for (int k = 0; k <= 3; k++)
					{
						if (fillTable[k][i] == 0)
						{
							continue;
						}
						else if (fillTable[k][i] == fillTable[k][i - 1])
						{
							fillTable[k][i] *= 2;
							text[k][i].setString(std::to_string(fillTable[k][i]));
							fillTable[k][i - 1] = 0;
							text[k][i - 1].setString("");
						}
						else if (i == 3 && fillTable[k][i] == fillTable[k][1] && fillTable[k][2] == 0)
						{
							fillTable[k][i] *= 2;
							text[k][i].setString(std::to_string(fillTable[k][i]));
							fillTable[k][2] = 0;
							text[k][2].setString("");
						}
						else if (i == 3 && fillTable[k][i] == fillTable[k][0] && fillTable[k][1] == 0 && fillTable[k][2] == 0)
						{
							fillTable[k][i] *= 2;
							text[k][i].setString(std::to_string(fillTable[k][i]));
							fillTable[k][0] = 0;
							text[k][0].setString("");
						}
						else if (i == 2 && fillTable[k][i] == fillTable[k][0] && fillTable[k][1] == 0)
						{
							fillTable[k][i] *= 2;
							text[k][i].setString(std::to_string(fillTable[k][i]));
							fillTable[k][0] = 0;
							text[k][0].setString("");
						}
						if (max < fillTable[k][i])
						{
							max = fillTable[k][i];
							if (max == 2048)
							{
								gameMode = 1;
								endText.setString("Zwyciestwo, nacisnij spacje aby wyjsc");
							}
						}
					}
				}
				for (int i = 3; i > 0; i--)
				{
					int x = 3;
					do
					{
						for (int k = 3; k >= 0; k--)
						{
							if (fillTable[k][i] == 0)
							{
								for (int l = i; l > 0; l--)
								{
									fillTable[k][l] = fillTable[k][l-1];
									text[k][l].setString(std::to_string(fillTable[k][l-1]));
								}
								fillTable[k][0] = 0;
								text[k][0].setString("");
							}
						}
						x--;
					} while (x >= 0);
				}
				bool freeField = false;
				for (int f = 0; f <= 3; f++)
				{
					for (int g = 0; g <= 3; g++)
					{
						if (fillTable[f][g] == 0)
						{
							freeField = true;
							break;
						}
					}
				}
				if (freeField)
				{
					int a = 0;
					int b = 0;
					do
					{
						a = rand() % 4;
						b = rand() % 4;
					} while (fillTable[a][b] != 0);
					fillTable[a][b] = 2;
					text[a][b].setString(std::to_string(fillTable[a][b]));
				}
				else
				{
					gameMode = 1;
				}
			}
		}
		window.clear();
		if (gameMode == 0)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					window.draw(rect[i][j]);
					if (text[i][j].getString() == std::to_string(0))
					{
						continue;
					}
					else
					{
						int q;
						if (fillTable[i][j] < 10.0)
						{
							q = 35.0;
						}
						else if (fillTable[i][j] < 100.0)
						{
							q = 25.0;
						}
						else if (fillTable[i][j] < 1000.0)
						{
							q = 15.0;
						}
						else
						{
							q = 5.0;
						}
						text[i][j].setPosition((float)i * 100 + q, (float)j * 100 + 25);// +25  trzeba bedzie zmieniac w zaleznosci od liczby cyfr w liczbie
						window.draw(text[i][j]);
					}
				}
			}
		}
		else
		{
			window.draw(endText);
		}
		window.display();
	}
	return 0;
}

