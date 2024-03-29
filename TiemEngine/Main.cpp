

// OpenGL headers
#include <GL/glew.h>

// SDL headers
#include <SDL_main.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>
#include <string>
#include <unordered_set> // Added by Kapom
#include "GameEngine.h"

#include "Tilemap.h"
#include "irrKlang.h"

using namespace std;
bool quit;
const GLint WIDTH = 1280, HEIGHT = 720;
float deltaTime;

SDL_Window* window;
SDL_GLContext glContext;
SDL_Event sdlEvent;

GameEngine * engine = nullptr;

//Tilemap tilemap(WIDTH, HEIGHT,1 );

//irrklang::ISoundEngine* soundEngine = irrklang::createIrrKlangDevice();

int main(int argc, char *argv[])
{
	quit = false;

	//Use OpenGL 3.1 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Initialize video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// Display error message
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}
	else
	{
		// Create window
		window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			// Display error message
			cout << "Window could not be created! SDL_Error" << SDL_GetError() << endl;
			return false;
		}
		else
		{
			// Create OpenGL context
			glContext = SDL_GL_CreateContext(window);

			if (glContext == NULL)
			{
				// Display error message
				cout << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << endl;
				return false;
			}
			else
			{
				// Initialize glew
				GLenum glewError = glewInit();
				if (glewError != GLEW_OK)
				{
					cout << "Error initializing GLEW! " << glewGetErrorString(glewError) << endl;
					return false;
				}
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					cout << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << endl;
				}

				engine = GameEngine::GetInstance();
				engine->Init(WIDTH, HEIGHT);
			}
		}
	}

    //Loading Map
    //tilemap.LoadMapFromFile("../Resource/Texture/map.txt");


    float prevTime = SDL_GetTicks();

    // Game loop
    while (engine->GetStateController()->gameStateCurr != GameState::GS_QUIT)
    {
        if (engine->GetStateController()->gameStateCurr != GS_RESTART)
        {
            engine->GetStateController()->LoadLevel();
        }
        else
        {
            engine->GetStateController()->gameStateNext =
                engine->GetStateController()->gameStateCurr = engine->GetStateController()->gameStatePrev;
        }

        // Initialize the gamestate
        engine->GetStateController()->InitLevel();

        // Add the following set
        std::unordered_set<SDL_Keycode> pressedKeys;

        while (engine->GetStateController()->gameStateCurr == engine->GetStateController()->gameStateNext)
        {
                       
            float currentTime = SDL_GetTicks();
            deltaTime = (currentTime - prevTime) / 1000.0f;
            prevTime = currentTime;
            //cout << currentTime / 1000 << endl;

            while (SDL_PollEvent(&sdlEvent) != 0)
            {
                // Esc button is pressed
                if (sdlEvent.type == SDL_QUIT)
                {
                    engine->GetStateController()->gameStateNext = GameState::GS_QUIT;
                }
                else if (sdlEvent.type == SDL_KEYDOWN)
                {
                    if (pressedKeys.find(sdlEvent.key.keysym.sym) == pressedKeys.end()) {
                        pressedKeys.insert(sdlEvent.key.keysym.sym); // Add to pressedKeys set
                        cout << sdlEvent.key.keysym.sym << endl;
                    }
                    if (pressedKeys.count(SDLK_SPACE))
                    {
                        engine->GetStateController()->HandleKeyLevel(' ');
                        cout << "JUMP" << endl;
                    }if (pressedKeys.count(SDLK_w))
                    {
                        engine->GetStateController()->HandleKeyLevel('w');
                        cout << "JUMP" << endl;
                    }
                    if (pressedKeys.count(SDLK_LSHIFT))
                    {
                        engine->GetStateController()->HandleKeyLevel('C');
                        cout << "DASH" << endl;
                    }

                }
                else if (sdlEvent.type == SDL_KEYUP)
                {
                    pressedKeys.erase(sdlEvent.key.keysym.sym); // Remove from pressedKeys set
                }
                else if (sdlEvent.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (sdlEvent.button.button == SDL_BUTTON_LEFT)
                    {
                        engine->GetStateController()->HandleMouseLevel(0, sdlEvent.button.x, sdlEvent.button.y);
                        cout << "CLICK" << endl;
                    }
                    else if (sdlEvent.button.button == SDL_BUTTON_RIGHT) {
                        engine->GetStateController()->HandleMouseLevel(1, sdlEvent.button.x, sdlEvent.button.y);
                        cout << "RCLICK" << endl;
                    }
                }
                else if (sdlEvent.type == SDL_MOUSEBUTTONUP)
                {

                    
                    if (sdlEvent.button.button == SDL_BUTTON_LEFT)
                    {
                        //engine->GetStateController()->HandleMouseLevel(0, sdlEvent.button.x, sdlEvent.button.y);
                    }
                }
                else if (sdlEvent.type == SDL_MOUSEMOTION) {
                    engine->GetStateController()->HandleMousePos(sdlEvent.button.x, sdlEvent.button.y);
                }
            }

            // Handle multiple key inputs
            if (pressedKeys.count(SDLK_LEFT) || pressedKeys.count(SDLK_a))
            {
                engine->GetStateController()->HandleKeyLevel('a');
                
                //cout << "A" << endl;
            }

            if (pressedKeys.count(SDLK_g))
            {
                //soundEngine->play2D("../Resource/Sound/bell.wav", false);
                engine->GetStateController()->HandleKeyLevel('g');
                //cout << "A" << endl;
            }
            if (pressedKeys.count(SDLK_1))
            {
                //soundEngine->play2D("../Resource/Sound/bell.wav", false);
                engine->GetStateController()->HandleKeyLevel('1');
                //cout << "A" << endl;
            }
            if (pressedKeys.count(SDLK_2))
            {
                //soundEngine->play2D("../Resource/Sound/bell.wav", false);
                engine->GetStateController()->HandleKeyLevel('2');
                //cout << "A" << endl;
            }

            if (pressedKeys.count(SDLK_RIGHT) || pressedKeys.count(SDLK_d))
            {
                engine->GetStateController()->HandleKeyLevel('d');
                //cout << "D" << endl;
            }

            if (pressedKeys.count(SDLK_DOWN) || pressedKeys.count(SDLK_s))
            {
                engine->GetStateController()->HandleKeyLevel('s');
            }

            if (pressedKeys.count(SDLK_ESCAPE))
            {
                engine->GetStateController()->HandleKeyLevel('q');
            }

            if (pressedKeys.count(SDLK_r))
            {
                engine->GetStateController()->HandleKeyLevel('r');
            }

            if (pressedKeys.count(SDLK_e))
            {
                engine->GetStateController()->HandleKeyLevel('e');
            }

            

            engine->GetStateController()->UpdateLevel(deltaTime);

            engine->GetStateController()->DrawLevel();
            SDL_GL_SwapWindow(window);

            //cout << "Next " << GameData::GetInstance()->gGameStateNext << endl;
        }
        engine->GetStateController()->Freelevel();

        if (engine->GetStateController()->gameStateNext != GS_RESTART)
        {
            engine->GetStateController()->UnloadLevel();
        }

        engine->GetStateController()->gameStatePrev = engine->GetStateController()->gameStateCurr;
        engine->GetStateController()->gameStateCurr = engine->GetStateController()->gameStateNext;
    }

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}


