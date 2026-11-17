#include <array>
#include <raylib.h>

constexpr int window_width{1920};
constexpr int window_height{1080};
float dt;
bool ismouseon{false};
bool editmode{true};
bool showcolors{true};
int active_color_idx{0};

void drawVector(const Vector3& vec, float ystartpos, int num, int xpos){
    DrawText(TextFormat("V%i", num), 25, ystartpos, 25, WHITE);
    DrawText(TextFormat("r: %f", vec.x), 25, ystartpos+25, 15, RED);
    DrawText(TextFormat("g: %f", vec.y), 25, ystartpos+50, 15, GREEN);
    DrawText(TextFormat("b: %f", vec.z), 25, ystartpos+75, 15, BLUE);
}



int main(){
    InitWindow(window_width, window_height, "t");
    SetTargetFPS(60);

    Shader shader = LoadShader(0, "shader.fs");
    int timeLoc = GetShaderLocation(shader, "dt");
    int resLoc = GetShaderLocation(shader, "iRes");
    int mouseLoc = GetShaderLocation(shader, "mousepos");
    int cntLoc = GetShaderLocation(shader, "cnt");
    int neonLoc = GetShaderLocation(shader, "neon");

    int avecLoc = GetShaderLocation(shader, "a");
    int bvecLoc = GetShaderLocation(shader, "b");
    int cvecLoc = GetShaderLocation(shader, "c");
    int dvecLoc = GetShaderLocation(shader, "d");


    Image blankimg = GenImageColor(window_width, window_height, WHITE);
    Texture2D blanktxtr = LoadTextureFromImage(blankimg);
    UnloadImage(blankimg);
    
    float resolution[2] = {window_width,window_height};
    SetShaderValue(shader, resLoc, resolution, SHADER_UNIFORM_VEC2);

    float cnt = 9.2972;
    float neon = 0.01;
    Vector3 a = {0.2,0.76,1};
    Vector3 b = {0.12,0.46,0.09};
    Vector3 c = {0.79,1,1};
    Vector3 d = {0.687,0.27,0.485};
    
    std::array<Vector3*, 4> colors{&a,&b,&c,&d};

    while(!WindowShouldClose()){

        SetShaderValue(shader, cntLoc, &cnt, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, neonLoc, &neon, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, avecLoc, &a, SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, bvecLoc, &b, SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, cvecLoc, &c, SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, dvecLoc, &d, SHADER_UNIFORM_VEC3);

        if(IsKeyPressed(KEY_E))editmode=!editmode;

        if(editmode){
            if(IsKeyPressed(KEY_R) && IsKeyDown(KEY_LEFT_SHIFT)){ //reset
                cnt = 9.2972;
                neon = 0.01;

                a = {0.2,0.76,1};
                b = {0.12,0.46,0.09};
                c = {0.79,1,1};
                d = {0.687,0.27,0.485};
            }

            if(IsKeyPressed(KEY_S))showcolors=!showcolors;

            if(IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_LEFT_SHIFT))cnt+=1;
            if(IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_LEFT_SHIFT)) cnt-=1;


            if(IsKeyDown(KEY_M)) neon+=0.0001;
            if(IsKeyDown(KEY_N))neon-=0.0001;

            if(IsKeyPressed(KEY_L))ismouseon = !ismouseon;
            if(ismouseon){
                Vector2 mousepos = GetMousePosition();
                Vector2 normalizedMouse = {
                    (mousepos.x / window_width) * 2.0f - 1.0f,
                    -((mousepos.y / window_height) * 2.0f - 1.0f)
                };
                SetShaderValue(shader, mouseLoc, &normalizedMouse, SHADER_UNIFORM_VEC2);
            }

            if(showcolors){

                if(IsKeyPressed(KEY_ONE)) active_color_idx = 0;
                if(IsKeyPressed(KEY_TWO)) active_color_idx = 1;
                if(IsKeyPressed(KEY_THREE)) active_color_idx = 2;
                if(IsKeyPressed(KEY_FOUR)) active_color_idx = 3;

                Vector3* target = colors[active_color_idx];

                if(IsKeyDown(KEY_R) && IsKeyDown(KEY_RIGHT)&& target->x < 1.0f)target->x += 0.01;
                if(IsKeyDown(KEY_R) && IsKeyDown(KEY_LEFT)&& target->x > 0.0f)target->x -= 0.01;
                if(IsKeyDown(KEY_G) && IsKeyDown(KEY_RIGHT)&& target->y < 1.0f)target->y += 0.01;
                if(IsKeyDown(KEY_G) && IsKeyDown(KEY_LEFT)&& target->y > 0.0f)target->y -= 0.01;
                if(IsKeyDown(KEY_B) && IsKeyDown(KEY_RIGHT)&& target->z < 1.0f)target->z += 0.01;
                if(IsKeyDown(KEY_B) && IsKeyDown(KEY_LEFT)&& target->z > 0.0f)target->z -= 0.01;

            }

            
            
        }

        dt = GetTime();
        SetShaderValue(shader, timeLoc, &dt, SHADER_UNIFORM_FLOAT);
        
        
        BeginDrawing();
        ClearBackground(BLACK);

        BeginShaderMode(shader);
        DrawTexture(blanktxtr, 0, 0, WHITE);
        EndShaderMode();
        
        if(editmode){
            DrawText(TextFormat("CNT: %f", cnt), 25, 25, 20, WHITE);
            DrawText(TextFormat("NEON: %f", neon), 25, 55, 20, WHITE);
            
            if(ismouseon){
                DrawText("Mouse mode on", 10, 10, 10, RED);
            }
            if(showcolors){
                drawVector(a, 85,1,25);
                drawVector(b, 190,2,25);
                drawVector(c, 295,3,25);
                drawVector(d, 400,4,25);
                DrawText(TextFormat("Editing Color: %i", active_color_idx+1), 25, 550, 20, WHITE);
            }

        }

        EndDrawing();
    }
    UnloadTexture(blanktxtr);
    UnloadShader(shader);
    CloseWindow();
    return 0;

}
