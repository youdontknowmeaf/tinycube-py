#include <raylib.h>
#include <stdio.h>
#include <filesystem>

#define XZ_WORLD_LIMIT 64
#define Y_WORLD_LIMIT 24
#define WH_BLOCK_SIZE 2
#define BLOCK_OFFSET (WH_BLOCK_SIZE / 2.0f)

namespace fs = std::filesystem;

void DrawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color);
// Fuck raylib 5.X/6.X

typedef struct {
	Color col;
	Texture2D txt;
} block;

int main(int argc, char *argv[]) {
	InitWindow(720, 480, "Minecraft: PreClassic (RubyDung)");
	SetTargetFPS(30);
	std::string icon_path = fs::path(argv[0]).parent_path() / "logo.png";
	Image icon = LoadImage(icon_path.c_str());
	SetWindowIcon(icon);
	HideCursor();
	DisableCursor();

	float xpos = 10.0f;
	float ypos = Y_WORLD_LIMIT * WH_BLOCK_SIZE;
	float zpos = 40.0f;
	
	Texture2D stone_txt = LoadTexture("stone.png");
	Texture2D grass_txt = LoadTexture("grass.png");

	block grass; grass.col = GREEN; grass.txt = grass_txt;
	block air; air.col = BLANK;
	block stone; stone.col = GRAY; stone.txt = stone_txt;

	block world[XZ_WORLD_LIMIT][Y_WORLD_LIMIT][XZ_WORLD_LIMIT];


	for (int x = 0; x < XZ_WORLD_LIMIT; x++) {
		for (int y = 0; y < Y_WORLD_LIMIT; y++) {
			for (int z = 0; z < XZ_WORLD_LIMIT; z++) {
				if (y < 13) world[x][y][z] = stone;
				else if (y < 16) world[x][y][z] = grass;
				else world[x][y][z] = air;
			}
		}
	}

	
	Camera3D camera = { 0 };
	camera.position = (Vector3){ xpos, ypos, zpos };
	camera.target = (Vector3){ 10.0f, 10.0f, 10.0f };
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	while(!WindowShouldClose()) {
		// MOVEMENT
		// Im lazy lol
		UpdateCamera(&camera, CAMERA_FIRST_PERSON);

		float feet = camera.position.y - 3.0f;
		int bx = (int)(camera.position.x / WH_BLOCK_SIZE);
		int by = (int)(feet / WH_BLOCK_SIZE);
		int bz = (int)(camera.position.z / WH_BLOCK_SIZE);

		if (world[bx][by][bz].col.a != 0) {
			float blocktopy = (by + 1) * WH_BLOCK_SIZE;
			camera.position.y = blocktopy + 3.0f;
		} else {
			camera.position.y -= 0.5;
		}

		// 2D
		BeginDrawing();
		ClearBackground(BLACK);
		DrawFPS(10, 10);
		DrawText(TextFormat("X: %f, Y: %f, Z: %f", camera.position.x, camera.position.y, camera.position.z), 10, 30, 10, RAYWHITE);
		DrawText("Minecraft 'Pre-Classic' rd-132211 - C++ - Made by SpookScoop93", 10, GetScreenHeight() - 20, 10, RAYWHITE);
		// 3D
		BeginMode3D(camera);
		
		for (int x = 0; x < XZ_WORLD_LIMIT; x++) {
			for (int y = 0; y < Y_WORLD_LIMIT; y++) {
				for (int z = 0; z < XZ_WORLD_LIMIT; z++) {	
					if(world[x][y][z].col.a != 0) {
						DrawCubeTexture(
							world[x][y][z].txt,
							(Vector3){ (float)(x * WH_BLOCK_SIZE) + BLOCK_OFFSET,
							(float)(y * WH_BLOCK_SIZE) + BLOCK_OFFSET,
							(float)(z * WH_BLOCK_SIZE) + BLOCK_OFFSET },
							(float)WH_BLOCK_SIZE, (float)WH_BLOCK_SIZE, (float) WH_BLOCK_SIZE,
							world[x][y][z].col
							 );
					}
				}
			}
		}
		//DrawCubeV((Vector3){10, 10, 10}, (Vector3){20, 20, 20}, GREEN);

		EndMode3D();
		EndDrawing();
	}

	CloseWindow();
	UnloadImage(icon);
	UnloadTexture(grass_txt);
	UnloadTexture(stone_txt);
	return 0;
}
