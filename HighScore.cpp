#include "HighScore.h"

HighScore::HighScore(SDL_Renderer * renderer, double x, double y) : Texture(renderer, x, y) {
	//std::cout << "highscore constructor" << this << std::endl;
	this->width = HIGHSCORE_WIDTH;
	this->height = HIGHSCORE_HEIGHT;
	namefile = "highscore.txt";
	std::fstream fs;
	fs.open(namefile, std::fstream::in);
	if (!fs.is_open())
		std::cout << "Error openning the file" << this << std::endl;
	else
	{
		while (!fs.eof())
		{
			str = "";
			std::getline(fs, str);
			highScore.push_back(atoi(str.c_str()));
		}
	}
	fs.close();
	back = new Button(renderer, "Back", DISPLAY_WIDTH - 1.5 * BUTTON_WIDTH, DISPLAY_HEIGHT - 1.5 * BUTTON_HEIGHT);
}

HighScore::~HighScore() {
//	std::cout << "highscore destructor" << this << std::endl;
}

void HighScore::Render() {
	SDL_Rect dstRect;
	TTF_Font * font = TTF_OpenFont("ttf.ttf", 24);
	SDL_Color color = { 255, 0, 0 };

	for (size_t i = 0; i < highScore.size(); ++i)
	{
		str = std::to_string(i + 1) + ") " + std::to_string(highScore[i]);
		SDL_Surface * surface = TTF_RenderText_Solid(font, str.c_str(), color);
		message = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		dstRect.x = int(x);
		dstRect.y = int(y + height * i);
		dstRect.w = int(width * 6);
		dstRect.h = int(height);

		SDL_RenderCopy(renderer, message, 0, &dstRect);
	}
	back->Render();
}

void HighScore::Push_back(int score) {
	highScore.push_back(score);
	std::sort(highScore.begin(), highScore.end(), std::greater<int>());
	while (highScore.size() > 10)
		highScore.erase(highScore.begin() + highScore.size() - 1);
	std::fstream fs;
	fs.open(namefile, std::fstream::out | std::fstream::trunc);
	if (!fs.is_open())
		std::cout << "Error openning the file" << this << std::endl;
	else
	{
		for (size_t i = 0; i < highScore.size(); ++i)
		{
			str = std::to_string(highScore[i]);
			for (size_t j = 0; j < str.size(); ++j)
				fs << str[j];
			if (i != highScore.size() - 1)
				fs << "\n";
		}
	}
	fs.close();
}

void HighScore::Clean() {
	highScore.clear();
	delete back;
}

Button * HighScore::getButton() {
	return back;
}

