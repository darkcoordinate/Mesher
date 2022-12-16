#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define win_w 640
#define win_h 320
 
typedef struct myData {
    SDL_Window *window;
    SDL_GLContext context;
}myData;

// Handle to a program object
GLuint programObject;
GLuint resolution;
GLuint gtime;
GLuint mouse;
GLuint mouse2[5];
float speed = 1.0;
time_t *tloc;
time_t sec;
///
// Create a shader object, load the shader source, and
// compile the shader.
//
#define TRUE 1
#define FALSE 0
float frtime;
float realTime;
float mousepos[4];
float mousepos2[5][4];
float res[2];
float aTime = 0;
char* openfile(char* filename)
{
    FILE* fs = fopen(filename,"rb");
    char* ret = (char*)malloc(800000);
    char c;
    int i;
    for(i = 0; (c = fgetc(fs))!= EOF; i++)
    {
        ret[i] = c;
    }
    ret[i] = '\0';
    return ret;
}

GLuint LoadShader(GLenum type, const char *shaderSrc)
{
	GLuint shader;
	GLint compiled;
	// Create the shader object
	shader = glCreateShader(type);
	if(shader == 0)
		return 0;
	// Load the shader source
	glShaderSource(shader, 1, &shaderSrc, NULL);
	// Compile the shader
	glCompileShader(shader);
	// Check the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if(!compiled)
	{
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

		if(infoLen > 1)
        	{
            		char* infoLog = malloc(sizeof(char) * infoLen);
            		glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            		printf("Error compiling shader:\n%s\n", infoLog);
            		free(infoLog);
        	}
        	glDeleteShader(shader);
        	return 0;
    	}
    return shader;
}
///
// Initialize the shader and program object
//
int Init()
{
	tloc = (time_t*)malloc(sizeof(time_t));
	realTime = 0;
	aTime = 0;
	mousepos[0] = 160;
	mousepos[1] = 0;
	mousepos[2] = 1.0;
	mousepos[3] = 1.0;
	res[0] = win_w;
	res[1] = win_h;
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 4;j++)
		{
			mousepos2[i][j] = 4.0;
		}
	}
	GLbyte* vShaderStr = openfile("vs.sdr");

	GLbyte* fShaderStr = openfile("frg4.sdr");
	GLuint vertexShader;
	GLuint fragmentShader;
	GLint linked;

 // Load the vertex/fragment shaders
	vertexShader = LoadShader(GL_VERTEX_SHADER, vShaderStr);
	fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fShaderStr);
	// Create the program object
	programObject = glCreateProgram();
	if(programObject == 0)
		return 0;
	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);
	// Bind vPosition to attribute 0
	glBindAttribLocation(programObject, 0, "vPosition");
	// Link the program
	glLinkProgram(programObject);
	// Check the link status
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
	if(!linked)
	{
		GLint infoLen = 0;
		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

		if(infoLen > 1)
		{
			char* infoLog = malloc(sizeof(char) * infoLen);
			glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
            printf("Error linking program:\n%s\n", infoLog);

			free(infoLog);
		}
        	glDeleteProgram(programObject);
		return FALSE;
	}
	
	
	gtime = glGetUniformLocation(programObject,"time");
	resolution = glGetUniformLocation(programObject,"resolution");
	mouse = glGetUniformLocation(programObject,"mouse");
	mouse2[0] = glGetUniformLocation(programObject,"mouse1");
	mouse2[1] = glGetUniformLocation(programObject,"mouse2");
	mouse2[2] = glGetUniformLocation(programObject,"mouse3");
	mouse2[3] = glGetUniformLocation(programObject,"mouse4");
	mouse2[4] = glGetUniformLocation(programObject,"mouse5");

	// Store the program object
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	const char* message = glGetString(GL_EXTENSIONS);
	printf("message=%s\n",message);
	//free(message);
	free(vShaderStr);
	free(fShaderStr);
	vShaderStr = NULL;
	fShaderStr = NULL;
	//free(message);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return TRUE;
}

//
// Draw a triangle using the shader pair created in Init()
//
void Draw()
{
	GLfloat vVertices[] = {-1.0f, 1.0f, 0.0f,
                -1.0f, -1.0f, 0.0f,1.0f, 1.0f, 0.0f,
                1.0f, -1.0f, 0.0f};

	// Set the viewport
	glViewport(0, 0, (int)res[0],(int)res[1] );

	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	// Use the program object
	glUseProgram(programObject);
	glUniform2fv(resolution,1,res);
	glUniform4fv(mouse,1,mousepos);
	glUniform4fv(mouse2[0],1,mousepos2[0]);
	glUniform4fv(mouse2[1],1,mousepos2[1]);
	glUniform4fv(mouse2[2],1,mousepos2[2]);
	glUniform4fv(mouse2[3],1,mousepos2[3]);
	glUniform4fv(mouse2[4],1,mousepos2[4]);

	glUniform1f(gtime,realTime/50.0);
	// Load the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
/* Our program's entry point */

void mousefn(int x, int y)
{
    mousepos[0] = (float)x/res[0];
    mousepos[1] = (float)y/res[1];
	//printf("%f %f \n",mousepos[0],mousepos[1]);
//	Draw();
}

void compute()
{
}

void reshape(int width, int height)
{
    res[0] = width;
    res[1] = height;
}
float re_scale(float s)
{
	return speed*(150.0 - fmod(s,250.0));
}

float mouse_com(float m)
{
	float k = 60.0 - 120.0*m;
	if(k < -30.0)
	{
		return -30.0;
	}
	else if(k >30.0)
	{
		return 30.0;
	}
	else 
	{
		return k;
	}
} 
void idle()
{
	float amou = mouse_com(mousepos[0]);
	aTime++;
	realTime++;
	speed += 0.0000001;
	if( aTime == 25000.0)
		aTime = 0.0;
	mousepos2[0][0] = re_scale(aTime) ;
	mousepos2[1][0] = re_scale(aTime + 50);
	mousepos2[2][0] = re_scale(aTime + 100);
	mousepos2[3][0] = re_scale(aTime + 150);
	mousepos2[4][0] = re_scale(aTime + 200);
	for(int i = 0; i < 5; i++)
	{
		if(fabs(mousepos2[i][0]+100.0) < 10.01)
		{
			mousepos2[i][1] = 5.0*((float)(rand()%11) - 5.0);

		}

		if((fabs(amou - mousepos2[i][1]) < 10)&&(fabs(mousepos2[i][0] -5.0) < 10))
		{
			mousepos[2] = 1.8;
		}
		//printf("%d  %f \n",i,mousepos2[i][0]);
	}  
}



int sdlInit(myData *data) {
	SDL_Init(SDL_INIT_VIDEO);

	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	data->window = SDL_CreateWindow("Demo", 0, 0, win_w, win_h, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	data->context = SDL_GL_CreateContext(data->window);

	return 0;
}


int loopFunc(myData *data) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return 1;
		}
		if (event.type == SDL_MOUSEMOTION){
			mousefn(event.motion.x,event.motion.y);
		}
		if(event.type == SDL_MOUSEBUTTONDOWN){
			Init();
		}
		if(event.type == SDL_KEYDOWN){
			
			switch(event.key.keysym.sym){
				case SDLK_r :
				{
					Init();
					break;
				}
				default:
				{
					break;
				}
			}
		}
	}

	Draw();
	idle();
	SDL_GL_SwapWindow(data->window);

	return 0;
}

void sdlQuit(myData *data) {
	glDeleteProgram(programObject);
	SDL_GL_DeleteContext(data->context);
	SDL_DestroyWindow(data->window);
	SDL_Quit();
	return;
}

int main() {
    myData data;

    sdlInit(&data);

    Init();

    while (!loopFunc(&data));

    sdlQuit(&data);

    return 0;
}
