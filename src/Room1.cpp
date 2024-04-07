
#include "Room1.hpp"

Tabs_Room1::Tabs_Room1() {
}

Tabs_Room1::~Tabs_Room1() {
}

Tabs Tabs_Room1::getDirect() {
    return direct;
}


void Tabs_Room1::roomInit(SDL_Renderer* renderer) {
    // roomBackground.loadFromFile(BG_Room1, renderer);
    
    roomBackground.importTexture(ResourceManager::getInstance().getTexture(BG_Room1, renderer));
}

void Tabs_Room1::render(SDL_Renderer* renderer, Vector2f player_pos, bool shake) {

    int addX = ceil(player_pos.x / (BACKGROUND_WIDTH * 2));
    int addY = ceil(player_pos.y / (BACKGROUND_HEIGHT * 2));
    int shakeX{0}, shakeY{0};
    if(shake)
    {
        shakeX = rand() % 10;
        shakeY = rand() % 10;
    }
	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			int posX = player_pos.x + x * (BACKGROUND_WIDTH * 2) - addX * (BACKGROUND_WIDTH * 2);
			int posY = player_pos.y + y * (BACKGROUND_HEIGHT * 2) - addY * (BACKGROUND_HEIGHT * 2);

            SDL_Rect dst;
            dst.x = -posX + shakeX; dst.y = -posY + shakeY;
            dst.w = BACKGROUND_WIDTH * 2; dst.h = BACKGROUND_HEIGHT * 2;

            roomBackground.render(renderer, &dst);
		}
	}

    if(roomBackground.getTexture() == NULL) std::cout << 1;
}

void Tabs_Room1::handleEvents() {
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_ESCAPE])
    {
        direct = Title;
        return;
    }
    
    direct = Room1;

    currentKeyStates = NULL;
}
