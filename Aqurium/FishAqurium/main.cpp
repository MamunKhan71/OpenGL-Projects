#include<windows.h>
#include <GL/glut.h>
#include <cmath>
#include <ctime>

// Global variables
int windowWidth = 800;
int windowHeight = 600;
float fish1PositionX = -2.0;
float fish1PositionY = 0.0;
float fish1Direction = 1.0;  // Fish 1 direction (1.0 for forward, -1.0 for backward)
float fish2PositionX = 2.0;
float fish2PositionY = 0.0;
float fish2Direction = -1.0; // Fish 2 direction (1.0 for forward, -1.0 for backward)

// Function to handle window resizing
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / (float)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Function to handle key press events
void keyboard(unsigned char key, int x, int y) {
    if (key == 27) { // 27 is the ASCII code for the ESC key
        exit(0);    // Exit the program
    }
}

// Function to draw a fish
void drawFish(float positionX, float positionY) {
    glPushMatrix();
    glTranslatef(positionX, positionY, 0.0);  // Position of the fish

    // Draw body
    glColor3f(1.0, 1.0, 0.0);        // Yellow color
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.2, 0.0);
    glVertex3f(1.0, -0.2, 0.0);
    glEnd();

    // Draw tail
    glColor3f(0.0, 0.0, 1.0);        // Blue color
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5, 0.2, 0.0);
    glVertex3f(-0.5, -0.2, 0.0);
    glVertex3f(-1.0, 0.0, 0.0);
    glEnd();

    glPopMatrix();
}

// Function to draw water plants
void drawWaterPlants() {
    // Plant 1
    glColor3f(0.0, 1.0, 0.0);        // Green color
    glPushMatrix();
    glTranslatef(-3.0, -2.5, 0.0);  // Position of the plant
    glBegin(GL_QUADS);
    glVertex3f(0.05, 0.0, 0.0);
    glVertex3f(-0.05, 0.0, 0.0);
    glVertex3f(-0.05, 1.5, 0.0);
    glVertex3f(0.05, 1.5, 0.0);
    glEnd();
    glPopMatrix();

    // Plant 2
    glPushMatrix();
    glTranslatef(3.0, -2.5, 0.0);  // Position of the plant
    glBegin(GL_QUADS);
    glVertex3f(0.05, 0.0, 0.0);
    glVertex3f(-0.05, 0.0, 0.0);
    glVertex3f(-0.05, 1.5, 0.0);
    glVertex3f(0.05, 1.5, 0.0);
    glEnd();
    glPopMatrix();
}

// Function to draw water effect
void drawWater() {
    // Animate water movement using sine wave
    static float time = 0.0;
    const float speed = 0.1;
    const float amplitude = 0.1;
    time += speed;

    // Draw water surface
    glColor3f(0.0, 0.7, 1.0);  // Light blue color
    glBegin(GL_QUADS);
    glVertex3f(-5.0, -3.0 + amplitude * sin(time), 0.0);
    glVertex3f(5.0, -3.0 + amplitude * sin(time), 0.0);
    glVertex3f(5.0, 3.0 + amplitude * sin(time), 0.0);
    glVertex3f(-5.0, 3.0 + amplitude * sin(time), 0.0);
    glEnd();
}

// Function to handle rendering
void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set up camera position and orientation
    gluLookAt(0.0, 0.0, 10.0,  // Eye position
              0.0, 0.0, 0.0,   // Look-at position
              0.0, 1.0, 0.0);  // Up vector

    // Render water
    drawWater();

    // Render aquarium background
    glColor3f(0.0, 0.0, 1.0);  // Blue color
    glBegin(GL_QUADS);
    glVertex3f(-5.0, -3.0, 0.0);
    glVertex3f(5.0, -3.0, 0.0);
    glVertex3f(5.0, 3.0, 0.0);
    glVertex3f(-5.0, 3.0, 0.0);
    glEnd();

    // Render water plants
    drawWaterPlants();

    // Render fish
    drawFish(fish1PositionX, fish1PositionY);
    drawFish(fish2PositionX, fish2PositionY);

    glutSwapBuffers();
}

// Function to update fish positions
void update(int value) {
    // Randomize fish movement
    srand(time(0));
    const float movementRange = 0.1;

    // Fish 1 movement
    fish1PositionX += fish1Direction * ((rand() % 100) / 100.0) * movementRange;
    fish1PositionY += fish1Direction * ((rand() % 100) / 100.0) * movementRange;
    if (fish1PositionX > 2.0 || fish1PositionX < -2.0) {
        fish1Direction *= -1.0;  // Reverse fish direction
    }
    if (fish1PositionY > 2.5 || fish1PositionY < -2.5) {
        fish1Direction *= -1.0;  // Reverse fish direction
    }

    // Fish 2 movement
    fish2PositionX += fish2Direction * ((rand() % 100) / 100.0) * movementRange;
    fish2PositionY += fish2Direction * ((rand() % 100) / 100.0) * movementRange;
    if (fish2PositionX > 2.0 || fish2PositionX < -2.0) {
        fish2Direction *= -1.0;  // Reverse fish direction
    }
    if (fish2PositionY > 2.5 || fish2PositionY < -2.5) {
        fish2Direction *= -1.0;  // Reverse fish direction
    }

    glutPostRedisplay();  // Request a redisplay
    glutTimerFunc(1000, update, 0);  // Call update() after 1 second
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Interactive Aquarium");

    // Register callback functions
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    // Set up initial OpenGL parameters
    glEnable(GL_DEPTH_TEST);

    // Set random seed for fish movement
    srand(time(0));

    // Start fish movement update
    glutTimerFunc(1000, update, 0);

    // Enter GLUT event processing loop
    glutMainLoop();

    return 0;
}
