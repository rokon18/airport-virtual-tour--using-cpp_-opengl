#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include<GL/gl.h>
#include <mmsystem.h>
#include <windows.h>
#include<ctime>
using namespace std;
void keyboard(unsigned char key, int x, int y);
float _move= 0.0;
float movesun= 300.0;
float movemoon= 300.0;
float carMove = 0.0;
float pickupMove = 0.0;
float busMove = 0.0;
float savebusMove = 0.0;
float savecarMove = 0.0;
bool paused = false;
bool carpaused = false;
float planeMovex = 40.0;
float planeMovey = 300.0;
float landingMovex = -350.0;
float landingMovey = 900.0;
float planescale = 0.5;
float landingscale = 0.1;
float manMovex = 0.0;
float manMovey = 0.0;
//float maninitialX = 850, maninitialY = 350;

 bool isDay = true;
 bool isNight = false;


void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1200, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
     cout << "   Press(two times) 1, 2, 3, 4 to change scenery. and number 4 scenery not working  " << endl;
      cout <<"**********************************" << endl;
    cout << "***** For case 1:outside view *****" << endl;
    cout << "***********************************" << endl;
    cout << "1. Press 'd' for Day mode or 'n' for Night mode." << endl;
    cout << "2. In Day mode, press //'S' to stop the bus.// and continuous pressing *a* to speed up car and *p* for speed up take off plane" << endl;
    cout << "   In Night mode, press 'S' to stop the car.//and continuous pressing *b* to speed up bus and *p* for speed up landing plane" << endl;
    cout << "3. Press the left mouse button to make an announcement." << endl;
    cout << "   Press the right mouse button to play the engine sound." << endl;
    cout << "for configure sound playing setting :settings>>compiler>>linker settings>>add:-lwinmm" << endl;

    cout <<"***********************************" << endl;
    cout <<"**For case 2:passenger launge view**" << endl;
    cout << "***********************************" << endl;
    std::cout << "  - 'F' or 'f' : Toggle Fullscreen\n";
    std::cout << "  - 'D' or 'd' : Switch to Day mode\n";
    std::cout << "  - 'N' or 'n' : Switch to Night mode\n";
    std::cout << "  - 'S' or 's' : Toggle visibility\n";
    std::cout << "  - 'Esc'      : Exit the program\n";

    std::cout << "\nMouse Controls:\n";
    std::cout << "  - Left Click : Toggle stop/move state\n";
     cout <<"**********************************" << endl;
    cout << "***** For case 3:runway*****" << endl;
    cout << "***********************************" << endl;

    std::cout << "----------------------------------------\n";
    std::cout << " [D / d]  - Switch to Day mode\n";
    std::cout << " [N / n]  - Switch to Night mode\n";
    std::cout << " [R / r]  - Toggle Rain On/Off\n";
    std::cout << " [M / m]  - Toggle Moon Visibility\n";
    std::cout << " [F / f]  - Toggle Fullscreen\n";
    std::cout << " [Esc]    - Exit the Program\n";
    std::cout << "----------------------------------------\n\n";

    std::cout << " Mouse Controls:\n";
    std::cout << "----------------------------------------\n";
    std::cout << " [Left Click] - Toggle Stop/Resume\n";
    std::cout << "========================================\n\n";

     cout <<"**********************************" << endl;
    cout << "***** For case 4:takeoff and landing****" << endl;
    cout << "***********************************" << endl;
    cout<<"Press D for Day view"<<endl;
    cout<<"Press N for Night view"<<endl;
    cout<<"Press R for Rainy view"<<endl;
    cout<<"Press L for Landing view"<<endl;
    cout<<"Press T for Take Off view"<<endl;


}


void drawCircle(float x, float y, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * M_PI * i / segments;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}




// Function  clouds
void drawCloud(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x, y, 30, 100);     // Main cloud circle
    drawCircle(x - 30, y, 25, 100); // Left
    drawCircle(x + 30, y, 25, 100); // Right
    drawCircle(x, y + 15, 23, 100); // Top

}


void drawTree(float x, float y) {
    // Trunk
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_QUADS);
    glVertex2f(x - 15, y);
    glVertex2f(x + 15, y);
    glVertex2f(x + 15, y + 80);
    glVertex2f(x - 15, y + 80);
    glEnd();

    // Canopy
    glColor3f(0.0f, 0.8f, 0.0f);
    drawCircle(x, y + 50, 30, 100);  // Main canopy
    drawCircle(x - 20, y + 35, 15, 100); // Left canopy
    drawCircle(x + 20, y + 35, 15, 100); // Right canopy
}



void drawCar(float x, float y,float r,float g,float b) {
    // Car Body
    glPushMatrix();
    glTranslatef(carMove, 0.0f, 0.0f);

    glColor3f(0.0f,1.0f, 0.0f); // Green color for the body
    glBegin(GL_QUADS);
    glVertex2f(x, y);       // Bottom-left
    glVertex2f(x + 140, y); // Bottom-right
    glVertex2f(x + 140, y + 40); // Top-right
    glVertex2f(x, y + 40);  // Top-left
    glEnd();

    // Car Roof
    glColor3ub(128, 128, 128); // Gray color for the roof
    glBegin(GL_QUADS);
    glVertex2f(x + 30, y + 40);  // Bottom-left
    glVertex2f(x + 110, y + 40); // Bottom-right
    glVertex2f(x + 90, y + 70);  // Top-right
    glVertex2f(x + 50, y + 70);  // Top-left
    glEnd();

    // Car Windows
    glColor3ub(173, 216, 230); // Light blue for windows
    // Front window
    glBegin(GL_QUADS);
    glVertex2f(x + 35, y + 45);
    glVertex2f(x + 65, y + 45);
    glVertex2f(x + 65, y + 65);
    glVertex2f(x + 45, y + 65);
    glEnd();
    // Rear window
    glBegin(GL_QUADS);
    glVertex2f(x + 75, y + 45);
    glVertex2f(x + 105, y + 45);
    glVertex2f(x + 95, y + 65);
    glVertex2f(x + 85, y + 65);
    glEnd();

    // Car Headlight
    glColor3f(r,g,b); // Light gray for glass headlight
    glBegin(GL_QUADS);
    glVertex2f(x + 135, y + 10);
    glVertex2f(x + 140, y + 10);
    glVertex2f(x + 140, y + 30);
    glVertex2f(x + 135, y + 30);
    glEnd();

    // Car Rear Light
    glColor3ub(255, 0, 0); // Red for the rear light
    glBegin(GL_QUADS);
    glVertex2f(x, y + 10);
    glVertex2f(x + 5, y + 10);
    glVertex2f(x + 5, y + 30);
    glVertex2f(x, y + 30);
    glEnd();

    // Car Wheels
    glColor3ub(0, 0, 0); // Black for wheel outline

    drawCircle(x + 30, y, 15, 100); // Front wheel
    drawCircle(x + 110, y, 15, 100); // Rear wheel
    glColor3ub(255, 255, 255); // White for inner wheel
    drawCircle(x + 30, y, 8, 100); // Front wheel inner
    drawCircle(x + 110, y, 8, 100); // Rear wheel inner
    glPopMatrix();
}


void drawLamp(float x, float y,float r,float g,float b) {
    // Lamp Pole
    glColor3f(0.0f, 0.0f, 0.0f); // Black color
    glBegin(GL_QUADS);
    glVertex2f(x - 3, y);
    glVertex2f(x + 3, y);
    glVertex2f(x + 3, y + 100);
    glVertex2f(x - 3, y + 100);
    glEnd();

    // Lamp Arms
    glBegin(GL_LINES);
    glVertex2f(x, y + 100);     // Top of the pole
    glVertex2f(x - 40, y + 130); // Left arm
    glVertex2f(x, y + 100);     // Top of the pole
    glVertex2f(x + 40, y + 130); // Right arm
    glVertex2f(x , y + 100); // center arm  pole
    glVertex2f(x , y + 130); // center arm
    glEnd();

    // Lamp Lights
    glColor3f(r,g,b); // yellow(top light)
    drawCircle(x, y + 140, 15, 100);

    glColor3f(r,g,b); // Beige (left light)
    drawCircle(x - 40, y + 130, 15, 100);

    glColor3f(r,g,b); // Beige (right light)
    drawCircle(x + 40, y + 130, 15, 100);
}






// Function to draw the road with dotted lines
void drawRoad() {
    // Road base
    glBegin(GL_QUADS);
    glColor3ub(56, 55, 53); // Dark gray for road
    glVertex2f(0, 0);       // Bottom-left
    glVertex2f(1200, 0);    // Bottom-right
    glVertex2f(1200, 365);   // Top-right
    glVertex2f(0, 365);      // Top-left
for (int x = 0; x < 1200; x += 15) {
    if ((x / 10) % 2 == 0) {
        glColor3ub(0, 0, 0); // Black
    } else {
        glColor3ub(255, 255, 255); // White
    }

    glBegin(GL_QUADS);
    glVertex2f(x, 365);
    glVertex2f(x + 15, 365);
    glVertex2f(x + 15, 380);
    glVertex2f(x, 380);
    glEnd();
}
    // White dotted lines in the middle of the road
    glColor3ub(255, 255, 255); // White for dotted lines

for (int i = 0; i <= 1200; i += 50) {
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(i, 160);     // Start of the line segment
    glVertex2f(i + 20, 160); // End of the line segment
    glEnd();
}glBegin(GL_QUADS);
 glColor3ub(56, 55, 53);
   glVertex2f(0,380);
   glVertex2f(1200,380);
   glVertex2f(1200,400);
   glVertex2f(0,400);
    glEnd();

}


void pickup(float r,float g,float b) {
    glPushMatrix();
    glTranslatef(pickupMove, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(15,50);
    glVertex2f(95,50);
    glVertex2f(95,65);
    glVertex2f(15,65);

    glBegin(GL_QUADS);
    glVertex2f(110,50);
    glVertex2f(195,50);
    glVertex2f(195,90);
    glVertex2f(110,90);
    glBegin(GL_QUADS);
    glVertex2f(115,90);
    glVertex2f(170,90);
    glVertex2f(165,130);
    glVertex2f(115,130);
     glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(120,90);
    glVertex2f(165,90);
    glVertex2f(160,125);
    glVertex2f(120,125);
      glColor3ub(r,g,b);
    glBegin(GL_QUADS);//headlight
    glVertex2f(185,65);
    glVertex2f(195,65);
    glVertex2f(195,75);
    glVertex2f(185,75);
    //small part
     glColor3ub(255,255,255);
    glBegin(GL_QUADS);
    glVertex2f(95,60);
    glVertex2f(110,60);
    glVertex2f(110,65);
    glVertex2f(95,65);
     glBegin(GL_QUADS);
    glVertex2f(95,50);
    glVertex2f(100,50);
    glVertex2f(100,90);
    glVertex2f(95,90);
    glColor3ub(0,255,255);
    glBegin(GL_QUADS);
    glVertex2f(40,65);
    glVertex2f(60,65);
    glVertex2f(60,80);
    glVertex2f(40,80);
    glEnd();

    glColor3ub(0, 0, 0); // Black for wheel

    drawCircle(80, 50, 15, 100); // back Front wheel
    drawCircle(30, 50, 15, 100); // back Rear wheel
    glColor3ub(255, 255, 255); // back White for inner wheel
    drawCircle(80, 50, 8, 100); // back Front wheel inner
    drawCircle(30, 50, 8, 100); // back Rear wheel inne
   glColor3ub(0, 0, 0); // Black for wheel
    drawCircle(180, 50, 15, 100); // middle Front wheel
    drawCircle(125, 50, 15, 100); // middle Rear wheel
    glColor3ub(255, 255, 255); // middle White for inner wheel
    drawCircle(180, 50, 8, 100); // middle Front wheel inner
    drawCircle(125, 50, 8, 100); // middle Rear wheel inner
    glPopMatrix();



}
void bus(float r, float g, float b) {
    glPushMatrix();
    glTranslatef(busMove, 0.0f, 0.0f);
    // Bus body
    glColor3ub(143, 48, 24);
    glBegin(GL_QUADS);
    glVertex2f(10, 150);
    glVertex2f(210, 150);
    glVertex2f(210, 210);
    glVertex2f(10, 210);
    glEnd();

    // Bus Roof
    glBegin(GL_QUADS);
    glVertex2f(10, 210);
    glVertex2f(210, 210);
    glVertex2f(207, 240);
    glVertex2f(14, 240);
    glEnd();

    // Windows
    glColor3ub(0, 255, 255);
    glBegin(GL_QUADS);
    glVertex2f(20, 190);
    glVertex2f(60, 190);
    glVertex2f(60, 210);
    glVertex2f(20, 210);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(70, 190);
    glVertex2f(110, 190);
    glVertex2f(110, 210);
    glVertex2f(70, 210);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(120, 190);
    glVertex2f(160, 190);
    glVertex2f(160, 210);
    glVertex2f(120, 210);
    glEnd();

    // Bus Headlight
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(200, 170);
    glVertex2f(210, 170);
    glVertex2f(210, 180);
    glVertex2f(200, 180);
    glEnd();

    // Bus Door
    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
    glVertex2f(165, 150);
    glVertex2f(190, 150);
    glVertex2f(190, 220);
    glVertex2f(165, 220);
    glEnd();

    // Wheels
    glColor3ub(0.1, 0.1, 0.1);
    drawCircle(50, 150, 15, 100);
    drawCircle(160, 150, 15, 100);

    glColor3ub(255, 255, 255);
    drawCircle(50, 150, 8, 100);
    drawCircle(160, 150, 8, 100);

    glPopMatrix();
}
void drawMan(float x, float y) {
    // Draw Head
    glColor3ub(255, 224, 189); // Skin color
    drawCircle(x, y-3, 6.0f, 50);  //head

    // Draw Body
    glColor3ub(0, 0, 255);
    glBegin(GL_QUADS);
    glVertex2f(x - 6, y - 10);  // Bottom left of body
    glVertex2f(x + 6, y - 10);  // Bottom right of body
    glVertex2f(x + 6, y - 30);  // Top right of body
    glVertex2f(x - 6, y - 30);  // Top left of body
    glEnd();

    // Draw Arms
    glColor3ub(255, 224, 189); // Skin color
    glLineWidth(4);
    glBegin(GL_LINES);
    // Left arm
    glVertex2f(x - 6, y - 10);
    glVertex2f(x - 12, y -30);
    // Right arm
    glVertex2f(x + 6, y - 10);
    glVertex2f(x + 12, y - 30);
    glEnd();

    // Draw Legs
    glColor3ub(0, 0, 255);
    glLineWidth(4);
    glBegin(GL_LINES);
    // Left leg
    glVertex2f(x - 4, y - 30);
    glVertex2f(x - 6, y - 50);
    // Right leg
    glVertex2f(x + 4, y - 30);
    glVertex2f(x + 6, y - 50);
    glEnd();
}



void bigplane(){
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);//body
    glVertex2f(760,340);
    glVertex2f(1055,340);
    glVertex2f(1055,420);
    glVertex2f(760,420);
    glEnd();

glBegin(GL_POLYGON);//head
glVertex2f(1055, 420);
glVertex2f(1110, 400);
glVertex2f(1115, 395);
glVertex2f(1120, 390);
glVertex2f(1125, 385);
glVertex2f(1126, 380);
glVertex2f(1126, 380);
glVertex2f(1125, 365);
glVertex2f(1123, 362);
glVertex2f(1120, 360);
glVertex2f(1115, 358);
glVertex2f(1110, 355);
glVertex2f(1100, 349);
glVertex2f(1085, 345);
glVertex2f(1075, 341);
glVertex2f(1060, 341);
glVertex2f(1055, 340);
glEnd();

    // Back Side
    glBegin(GL_POLYGON);
    glVertex2f(670,420);
    //glVertex2f(690,395);
    glVertex2f(710,380);
    glVertex2f(720,360);
    glVertex2f(760,340);
    glVertex2f(760,420);
    glEnd();

     glColor3f(.5f,.5f,.5f);
    glBegin(GL_POLYGON);//up wings
    glVertex2f(690,420);
    glVertex2f(670,480);
    glVertex2f(695,480);
    glVertex2f(720,440);
    glVertex2f(740,420);
    glEnd();
    glBegin(GL_QUADS);//up small wings
    glVertex2f(720,405);
    glVertex2f(700,395);
    glVertex2f(630,415);
    glVertex2f(620,420);
    glColor3f(.8f,.8f,.8f);
    glBegin(GL_QUADS);// wings
    glVertex2f(950,380);
    glVertex2f(880,380);
    glVertex2f(730,340);
    glVertex2f(750,330);
     glColor3f(.6f,.6f,.6f);
     glBegin(GL_QUADS);//engine
    glVertex2f(935,360);
    glVertex2f(900,360);
    glVertex2f(900,330);
    glVertex2f(935,330);
    glColor3f(.5f,.5f,0.5f);
    for (int i = 0; i < 8; ++i) {
        int offset = i * 25;

        glBegin(GL_QUADS);
        glVertex2f(750 + offset, 380);
        glVertex2f(750 + offset, 400);
        glVertex2f(760 + offset, 400);
        glVertex2f(760 + offset, 380);

    } glVertex2f(975 , 375);
        glVertex2f(975 , 405);
        glVertex2f(990 , 405);
        glVertex2f(990, 375);
//pilot window
        glVertex2f(1100 , 385);
        glVertex2f(1100 , 395);
        glVertex2f(1108, 395);
        glVertex2f(1108, 385);

        glVertex2f(1090 , 385);
        glVertex2f(1090 , 395);
        glVertex2f(1098, 395);
        glVertex2f(1098, 385);
        glEnd();
    glBegin(GL_TRIANGLES);
     glVertex2f(1110, 385);
     glVertex2f(1110, 395);
     glVertex2f(1120, 385);


        glEnd();
        glColor3ub(94, 131, 191);
    glBegin(GL_POLYGON);
     glVertex2f(1000, 380);
     glVertex2f(1000, 350);
     glVertex2f(950, 350);
     glVertex2f(900, 300);
     glVertex2f(860, 300);
     glVertex2f(970, 380);

    glEnd();
     glColor3ub(0, 0, 0);
    drawCircle(1020, 330, 11, 100);
    drawCircle(1020, 330, 11, 100);
    glColor3ub(255, 255, 255);
    drawCircle(1020, 330, 6, 100);
    drawCircle(1020, 330, 6, 100);

    glColor3ub(0, 0, 0);
    drawCircle(850, 330, 11, 100);
    drawCircle(850, 330, 11, 100);
    glColor3ub(255, 255, 255);
    drawCircle(850, 330, 6, 100);
    drawCircle(850, 330, 6, 100);
}

void smallplane(){
    glPushMatrix();
    glTranslatef(-400,0.0f, 0.0f);
    glScalef(0.8,0.8f, 0.0f);
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);//body
    glVertex2f(760,340);
    glVertex2f(1055,340);
    glVertex2f(1055,420);
    glVertex2f(760,420);
    glEnd();

glBegin(GL_POLYGON);//head
glVertex2f(1055, 420);
glVertex2f(1110, 400);
glVertex2f(1115, 395);
glVertex2f(1120, 390);
glVertex2f(1125, 385);
glVertex2f(1126, 380);
glVertex2f(1126, 380);
glVertex2f(1125, 365);
glVertex2f(1123, 362);
glVertex2f(1120, 360);
glVertex2f(1115, 358);
glVertex2f(1110, 355);
glVertex2f(1100, 349);
glVertex2f(1085, 345);
glVertex2f(1075, 341);
glVertex2f(1060, 341);
glVertex2f(1055, 340);
glEnd();

    // Back Side
    glBegin(GL_POLYGON);
    glVertex2f(670,420);
    //glVertex2f(690,395);
    glVertex2f(710,380);
    glVertex2f(720,360);
    glVertex2f(760,340);
    glVertex2f(760,420);
    glEnd();

     glColor3f(.5f,.5f,.5f);
    glBegin(GL_POLYGON);//up wings
    glVertex2f(690,420);
    glVertex2f(670,480);
    glVertex2f(695,480);
    glVertex2f(720,440);
    glVertex2f(740,420);
    glEnd();
    glBegin(GL_QUADS);//up small wings
    glVertex2f(720,405);
    glVertex2f(700,395);
    glVertex2f(630,415);
    glVertex2f(620,420);
    glColor3f(.8f,.8f,.8f);
    glBegin(GL_QUADS);// wings
    glVertex2f(950,380);
    glVertex2f(880,380);
    glVertex2f(730,340);
    glVertex2f(750,330);
     glColor3f(.6f,.6f,.6f);
     glBegin(GL_QUADS);//engine
    glVertex2f(935,360);
    glVertex2f(900,360);
    glVertex2f(900,330);
    glVertex2f(935,330);
    glColor3f(.5f,.5f,0.5f);
    for (int i = 0; i < 8; ++i) {
        int offset = i * 25;

        glBegin(GL_QUADS);
        glVertex2f(750 + offset, 380);
        glVertex2f(750 + offset, 400);
        glVertex2f(760 + offset, 400);
        glVertex2f(760 + offset, 380);

    } glVertex2f(975 , 375);
        glVertex2f(975 , 405);
        glVertex2f(990 , 405);
        glVertex2f(990, 375);
//pilot window
        glVertex2f(1100 , 385);
        glVertex2f(1100 , 395);
        glVertex2f(1108, 395);
        glVertex2f(1108, 385);

        glVertex2f(1090 , 385);
        glVertex2f(1090 , 395);
        glVertex2f(1098, 395);
        glVertex2f(1098, 385);
        glEnd();
    glBegin(GL_TRIANGLES);
     glVertex2f(1110, 385);
     glVertex2f(1110, 395);
     glVertex2f(1120, 385);


        glEnd();
        glColor3ub(94, 131, 191);
    glBegin(GL_POLYGON);
     glVertex2f(1000, 380);
     glVertex2f(1000, 350);
     glVertex2f(950, 350);
     glVertex2f(900, 300);
     glVertex2f(860, 300);
     glVertex2f(970, 380);

    glEnd();
      glColor3ub(0, 0, 0);
    drawCircle(1020, 330, 11, 100);
    drawCircle(1020, 330, 11, 100);
    glColor3ub(255, 255, 255);
    drawCircle(1020, 330, 6, 100);
    drawCircle(1020, 330, 6, 100);

    glColor3ub(0, 0, 0);
    drawCircle(850, 330, 11, 100);
    drawCircle(850, 330, 11, 100);
    glColor3ub(255, 255, 255);
    drawCircle(850, 330, 6, 100);
    drawCircle(850, 330, 6, 100);
 glPopMatrix();
 glEnd();
}
void flyingplane(){
    glPushMatrix();
    glTranslatef(planeMovex,planeMovey, 0.0f);
    glScalef(planescale,planescale, 0.0f);
   glRotatef(10,0,0,1);
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);//body
    glVertex2f(760,340);
    glVertex2f(1055,340);
    glVertex2f(1055,420);
    glVertex2f(760,420);
    glEnd();

glBegin(GL_POLYGON);//head
glVertex2f(1055, 420);
glVertex2f(1110, 400);
glVertex2f(1115, 395);
glVertex2f(1120, 390);
glVertex2f(1125, 385);
glVertex2f(1126, 380);
glVertex2f(1126, 380);
glVertex2f(1125, 365);
glVertex2f(1123, 362);
glVertex2f(1120, 360);
glVertex2f(1115, 358);
glVertex2f(1110, 355);
glVertex2f(1100, 349);
glVertex2f(1085, 345);
glVertex2f(1075, 341);
glVertex2f(1060, 341);
glVertex2f(1055, 340);
glEnd();

    // Back Side
    glBegin(GL_POLYGON);
    glVertex2f(670,420);
    //glVertex2f(690,395);
    glVertex2f(710,380);
    glVertex2f(720,360);
    glVertex2f(760,340);
    glVertex2f(760,420);
    glEnd();

     glColor3f(.5f,.5f,.5f);
    glBegin(GL_POLYGON);//up wings
    glVertex2f(690,420);
    glVertex2f(670,480);
    glVertex2f(695,480);
    glVertex2f(720,440);
    glVertex2f(740,420);
    glEnd();
    glBegin(GL_QUADS);//up small wings
    glVertex2f(720,405);
    glVertex2f(700,395);
    glVertex2f(630,415);
    glVertex2f(620,420);
    glColor3f(.8f,.8f,.8f);
    glBegin(GL_QUADS);// wings
    glVertex2f(950,380);
    glVertex2f(880,380);
    glVertex2f(730,340);
    glVertex2f(750,330);
     glColor3f(.6f,.6f,.6f);
     glBegin(GL_QUADS);//engine
    glVertex2f(935,360);
    glVertex2f(900,360);
    glVertex2f(900,330);
    glVertex2f(935,330);
    glColor3f(.5f,.5f,0.5f);
    for (int i = 0; i < 8; ++i) {
        int offset = i * 25;

        glBegin(GL_QUADS);
        glVertex2f(750 + offset, 380);
        glVertex2f(750 + offset, 400);
        glVertex2f(760 + offset, 400);
        glVertex2f(760 + offset, 380);

    } glVertex2f(975 , 375);
        glVertex2f(975 , 405);
        glVertex2f(990 , 405);
        glVertex2f(990, 375);
//pilot window
        glVertex2f(1100 , 385);
        glVertex2f(1100 , 395);
        glVertex2f(1108, 395);
        glVertex2f(1108, 385);

        glVertex2f(1090 , 385);
        glVertex2f(1090 , 395);
        glVertex2f(1098, 395);
        glVertex2f(1098, 385);
        glEnd();
    glBegin(GL_TRIANGLES);
     glVertex2f(1110, 385);
     glVertex2f(1110, 395);
     glVertex2f(1120, 385);


        glEnd();

      glColor3ub(0, 0, 0);
    drawCircle(1020, 330, 11, 100);
    drawCircle(1020, 330, 11, 100);
    glColor3ub(255, 255, 255);
    drawCircle(1020, 330, 6, 100);
    drawCircle(1020, 330, 6, 100);

    glColor3ub(0, 0, 0);
    drawCircle(850, 330, 11, 100);
    drawCircle(850, 330, 11, 100);
    glColor3ub(255, 255, 255);
    drawCircle(850, 330, 6, 100);
    drawCircle(850, 330, 6, 100);
 glPopMatrix();
 glEnd();
}
void landingplane(){
    glPushMatrix();
    glTranslatef(landingMovex,landingMovey, 0.0f);
    glScalef(landingscale,landingscale, 0.0f);
   glRotatef(-6,0,0,1);
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);//body
    glVertex2f(760,340);
    glVertex2f(1055,340);
    glVertex2f(1055,420);
    glVertex2f(760,420);
    glEnd();

glBegin(GL_POLYGON);//head
glVertex2f(1055, 420);
glVertex2f(1110, 400);
glVertex2f(1115, 395);
glVertex2f(1120, 390);
glVertex2f(1125, 385);
glVertex2f(1126, 380);
glVertex2f(1126, 380);
glVertex2f(1125, 365);
glVertex2f(1123, 362);
glVertex2f(1120, 360);
glVertex2f(1115, 358);
glVertex2f(1110, 355);
glVertex2f(1100, 349);
glVertex2f(1085, 345);
glVertex2f(1075, 341);
glVertex2f(1060, 341);
glVertex2f(1055, 340);
glEnd();

    // Back Side
    glBegin(GL_POLYGON);
    glVertex2f(670,420);
    //glVertex2f(690,395);
    glVertex2f(710,380);
    glVertex2f(720,360);
    glVertex2f(760,340);
    glVertex2f(760,420);
    glEnd();

     glColor3f(.5f,.5f,.5f);
    glBegin(GL_POLYGON);//up wings
    glVertex2f(690,420);
    glVertex2f(670,480);
    glVertex2f(695,480);
    glVertex2f(720,440);
    glVertex2f(740,420);
    glEnd();
    glBegin(GL_QUADS);//up small wings
    glVertex2f(720,405);
    glVertex2f(700,395);
    glVertex2f(630,415);
    glVertex2f(620,420);
    glColor3f(.8f,.8f,.8f);
    glBegin(GL_QUADS);// wings
    glVertex2f(950,380);
    glVertex2f(880,380);
    glVertex2f(730,340);
    glVertex2f(750,330);
     glColor3f(.6f,.6f,.6f);
     glBegin(GL_QUADS);//engine
    glVertex2f(935,360);
    glVertex2f(900,360);
    glVertex2f(900,330);
    glVertex2f(935,330);
    glColor3f(.5f,.5f,0.5f);
    for (int i = 0; i < 8; ++i) {
        int offset = i * 25;

        glBegin(GL_QUADS);
        glVertex2f(750 + offset, 380);
        glVertex2f(750 + offset, 400);
        glVertex2f(760 + offset, 400);
        glVertex2f(760 + offset, 380);

    } glVertex2f(975 , 375);
        glVertex2f(975 , 405);
        glVertex2f(990 , 405);
        glVertex2f(990, 375);
//pilot window
        glVertex2f(1100 , 385);
        glVertex2f(1100 , 395);
        glVertex2f(1108, 395);
        glVertex2f(1108, 385);

        glVertex2f(1090 , 385);
        glVertex2f(1090 , 395);
        glVertex2f(1098, 395);
        glVertex2f(1098, 385);
        glEnd();
    glBegin(GL_TRIANGLES);
     glVertex2f(1110, 385);
     glVertex2f(1110, 395);
     glVertex2f(1120, 385);


        glEnd();

      glColor3ub(0, 0, 0);
    drawCircle(1020, 330, 11, 100);
    drawCircle(1020, 330, 11, 100);
    glColor3ub(255, 255, 255);
    drawCircle(1020, 330, 6, 100);
    drawCircle(1020, 330, 6, 100);

    glColor3ub(0, 0, 0);
    drawCircle(850, 330, 11, 100);
    drawCircle(850, 330, 11, 100);
    glColor3ub(255, 255, 255);
    drawCircle(850, 330, 6, 100);
    drawCircle(850, 330, 6, 100);
 glPopMatrix();
glEnd();
}
void drawBuilding(){
   glBegin(GL_QUADS);
   //glColor3f(r,g,b);LOWER BIG Q
  glColor3f(0.800, 1.000, 0.984);
   glVertex2f(40,400);
   glColor3f(0.204, 0.620, 0.624);
   glVertex2f(600,400);
    glColor3f(0.169, 0.494, 0.514);
  glVertex2f(600,490);
  glColor3f(0.169, 0.494, 0.514);
  glVertex2f(40,490);
  glColor3ub(34, 39, 51);//~SMALL part
   glVertex2f(40,490);
   glVertex2f(600,490);
   glVertex2f(600,500);
   glVertex2f(40,500);

   glColor3ub(70, 70, 71);
   glVertex2f(240,400);
   glVertex2f(360,400);
   glVertex2f(360,490);
   glVertex2f(240,490);
   glColor3ub(0,255,255);//door window
  for (int i = 0; i < 5; i++) {
        float offset = i * 20.0f;
        glVertex2f(250 + offset, 425);
        glVertex2f(260 + offset, 425);
        glVertex2f(260 + offset, 455);
        glVertex2f(250 + offset, 455);
    }

    glColor3ub(34, 39, 51);//~pillar
   glVertex2f(90,400);
   glVertex2f(100,400);
   glVertex2f(100,490);
   glVertex2f(90,490);
    glVertex2f(140,400);
   glVertex2f(145,400);
   glVertex2f(145,490);
   glVertex2f(140,490);
    glVertex2f(400,400);
   glVertex2f(405,400);
   glVertex2f(405,490);
   glVertex2f(400,490);
    glVertex2f(500,400);
   glVertex2f(510,400);
   glVertex2f(510,490);
   glVertex2f(500,490);
glColor3f(0.9f, 0.7f, 0.5f);
  // glColor3f(1.0f, 0.9f, 0.7f);//~2nd ground
   glVertex2f(40,500);
   glVertex2f(600,500);
   glVertex2f(604,508);
   glVertex2f(36,508);
  glColor3f(1.0f, 0.9f, 0.7f);//~2nd ground
   glVertex2f(36,508);
   glVertex2f(604,508);
   glVertex2f(600,525);
   glVertex2f(40,525);
   glEnd();
   glColor3f(0,0,0);
   glBegin(GL_LINES);
   glVertex2f(60,500);
   glVertex2f(60,525);
   glVertex2f(130,500);
   glVertex2f(132,525);
    glVertex2f(200,500);
   glVertex2f(202,525);
   glVertex2f(400,500);
   glVertex2f(402,525);
   glVertex2f(500,500);
   glVertex2f(502,525);
   glEnd();

   glBegin(GL_QUADS);
   glColor3f(0.800, 1.000, 0.984);//2ndfloor
   glVertex2f(140,525);
   glColor3f(0.204, 0.620, 0.624);
   glVertex2f(500,525);
    glColor3f(0.169, 0.494, 0.514);
  glVertex2f(570,625);
  glColor3f(0.169, 0.494, 0.514);
  glVertex2f(60,625);
glEnd();
 glColor3f(0,0,0);
glBegin(GL_LINES);
   glVertex2f(60,625);
   glVertex2f(570,625);
   glVertex2f(102,570);
   glVertex2f(530,570);
   glVertex2f(138,524);
   glVertex2f(500,524);
   //glVertex2f(80,625);
   //glVertex2f(80,600);
   glVertex2f(102,625);
   glVertex2f(102,570);
   for (int i = 0; i < 10; i++){
         float offset = i * 38.0f;
   glVertex2f(140+offset,625);
   glVertex2f(140+offset,526);

   }
    glVertex2f(530,625);
   glVertex2f(530,568);
glEnd();
glBegin(GL_QUADS);
   glColor3f(0.5,.5,.5);//top
  glVertex2f(50,625);
  glVertex2f(580,625);
  glVertex2f(585,633);
  glVertex2f(45,633);
  glColor3f(0.9f, 0.7f, 0.5f);
  glVertex2f(42,633);
  glVertex2f(587,633);
  glVertex2f(585,638);
  glVertex2f(45,638);
  glEnd();


 }


void nightBuilding(){
   glBegin(GL_QUADS);
   //glColor3f(r,g,b);LOWER BIG Q
 glColor3ub(255, 240, 00);
   glVertex2f(40,400);
   glColor3ub(240, 205, 110);
   glVertex2f(600,400);
   glColor3ub(247, 230, 0);
  glVertex2f(600,490);
   glColor3ub(181, 154, 80);
  glVertex2f(40,490);
  glColor3ub(34, 39, 51);//~SMALL part
   glVertex2f(40,490);
   glVertex2f(600,490);
   glVertex2f(600,500);
   glVertex2f(40,500);

   glColor3ub(70, 70, 71);
   glVertex2f(240,400);
   glVertex2f(360,400);
   glVertex2f(360,490);
   glVertex2f(240,490);
   glColor3ub(245, 200, 78);//door window
  for (int i = 0; i < 5; i++) {
        float offset = i * 20.0f;
        glVertex2f(250 + offset, 425);
        glVertex2f(260 + offset, 425);
        glVertex2f(260 + offset, 455);
        glVertex2f(250 + offset, 455);
    }

    glColor3ub(34, 39, 51);//~pillar
   glVertex2f(90,400);
   glVertex2f(100,400);
   glVertex2f(100,490);
   glVertex2f(90,490);
    glVertex2f(140,400);
   glVertex2f(145,400);
   glVertex2f(145,490);
   glVertex2f(140,490);
    glVertex2f(400,400);
   glVertex2f(405,400);
   glVertex2f(405,490);
   glVertex2f(400,490);
    glVertex2f(500,400);
   glVertex2f(510,400);
   glVertex2f(510,490);
   glVertex2f(500,490);
glColor3f(0.9f, 0.7f, 0.5f);
  // glColor3f(1.0f, 0.9f, 0.7f);//~2nd ground
   glVertex2f(40,500);
   glVertex2f(600,500);
   glVertex2f(604,508);
   glVertex2f(36,508);
  glColor3f(1.0f, 0.9f, 0.7f);//~2nd ground
   glVertex2f(36,508);
   glVertex2f(604,508);
   glVertex2f(600,525);
   glVertex2f(40,525);
   glEnd();
   glColor3f(0,0,0);
   glBegin(GL_LINES);
   glVertex2f(60,500);
   glVertex2f(60,525);
   glVertex2f(130,500);
   glVertex2f(132,525);
    glVertex2f(200,500);
   glVertex2f(202,525);
   glVertex2f(400,500);
   glVertex2f(402,525);
   glVertex2f(500,500);
   glVertex2f(502,525);
   glEnd();

   glBegin(GL_QUADS);
   glColor3ub(255, 240, 00);//2ndfloor
   glVertex2f(140,525);
   glColor3ub(240, 205, 110);
   glVertex2f(500,525);
    glColor3ub(247, 230, 0);
  glVertex2f(570,625);
 glColor3ub(181, 154, 80);
  glVertex2f(60,625);
glEnd();
 glColor3f(0,0,0);
glBegin(GL_LINES);
   glVertex2f(60,625);
   glVertex2f(570,625);
   glVertex2f(102,570);
   glVertex2f(530,570);
   glVertex2f(138,524);
   glVertex2f(500,524);
   //glVertex2f(80,625);
   //glVertex2f(80,600);
   glVertex2f(102,625);
   glVertex2f(102,570);
   for (int i = 0; i < 10; i++){
         float offset = i * 38.0f;
   glVertex2f(140+offset,625);
   glVertex2f(140+offset,526);

   }
    glVertex2f(530,625);
   glVertex2f(530,568);
glEnd();
glBegin(GL_QUADS);
   glColor3f(0.5,.5,.5);//top
  glVertex2f(50,625);
  glVertex2f(580,625);
  glVertex2f(585,633);
  glVertex2f(45,633);
  glColor3f(0.9f, 0.7f, 0.5f);
  glVertex2f(42,633);
  glVertex2f(587,633);
  glVertex2f(585,638);
  glVertex2f(45,638);
  glEnd();


 }
void Sprint(float x, float y, char *st) {
    int l = strlen(st); // Get text length
    if(isDay){
    glColor3f(.0f, .0f, .0f); // Text color
    }else glColor3f(1.0f, .0f, .0f);

    glRasterPos2f(x, y);
    for (int i = 0; i < l; i++) {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]);
    }

    // Draw multiple times with small offsets to simulate bold effect
    glRasterPos2f(x + 0.5, y);
    for (int i = 0; i < l; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]);
    }

    glRasterPos2f(x - 0.5, y);
    for (int i = 0; i < l; i++) {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]);
    }
}


void day() {

    // Sky
    glColor3f(0.53f, 0.81f, 0.99f);
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2f(1200, 0);
    glVertex2f(1200, 1020);
    glVertex2f(0,1020);
    glEnd();
    glPushMatrix();
	glTranslatef(0.0f,movesun, 0.0f); //moving along x-axis
	//glTranslatef(0.0f, _move, 0.0f); //will move along y-axis
	//glTranslatef(_move, _move, 0.0f); //will move diagonally along x&y-axis

    // Sun
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(350, 200, 40, 100);

glPopMatrix();
glPushMatrix();
	glTranslatef(_move,0.0f, 0.0f);
// Clouds
   drawCloud(150, 900);
    drawCloud(250, 930);
    drawCloud(420, 950);
    drawCloud(520, 970);
glPopMatrix();




drawRoad();

 // Car

    drawCar(200, 50,1,1,1);


    // Tree
    //drawTree(400, 200);

    pickup(198, 203, 204);
    bus(.7,.8,.8);
    drawLamp(900, 395,1,1,1);
    bigplane();
    smallplane();

    flyingplane();
    drawBuilding();
     drawLamp(300, 395,1,1,1);
    drawLamp(610, 395,1,1,1);

    bus(1,1,1);
    drawMan(300,300);
    drawMan(280,300);
   // glPushMatrix();
	//glTranslatef(manMovex,manMovey, 0.0f);
    drawMan(850,350);
    drawMan(864,350);
    drawMan(836,350);
   // glPopMatrix();
    //glFlush();
    glPushMatrix();
    Sprint(100,640,"HAZRAT SHAHJALAL INTERNATIONAL AIRPORT");
    glPopMatrix();
    glutSwapBuffers();

}

void night() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2f(1200, 0);
    glVertex2f(1200, 1020);
    glVertex2f(0, 1020);
    glEnd();

    glPushMatrix();
    glTranslatef(0.0f,movemoon, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(350, 200, 20, 100); // Moon
    glPopMatrix();

    drawRoad();
    drawCar(200, 50,1,1,0);
    //drawCar(400, 50,1,1,0);
    // light yellow

    pickup(255, 255, 0);
     bus(1,1,0);
      drawLamp(900, 395,1.0, 0.9, 0.7);
     bigplane();
    smallplane();
    flyingplane();

    landingplane();
    nightBuilding();
    drawLamp(300, 395,1.0f, 0.9f, 0.7f);
    drawLamp(610, 395,1.0, 0.9, 0.7);
     drawMan(850,350);
    drawMan(864,350);
    drawMan(836,350);
    glPushMatrix();
    Sprint(100,640,"HAZRAT SHAHJALAL INTERNATIONAL AIRPORT");
    glPopMatrix();

    glutSwapBuffers();
}



void display_r() {

  if (isDay) {
        day();
    } if(isNight) {
        night();
    }
}
void update_r(int value) {
    _move += 0.5f;
    if(!carpaused){
    carMove += 2.0f;}
    pickupMove += 1.0f;
    planeMovex+=1.4f;
    planeMovey+=.9f;
    if(!isDay){
    landingMovex+=0.8f;
    landingMovey-=0.9f;}


if(paused){
     manMovex+=1.0;
    manMovey+=.5;
    }
    if(!paused){
    busMove+=1.5f;
    }
    if(isDay){
        movesun+=0.5;
        }else movesun-=3.5;
    if(!isDay){
        movemoon+=0.5;
        }else movemoon-=3.5;
    if (_move > 1200) {
        _move = -480;
    }
    if (movesun >= 750) {
        movesun = 750;
     }else {
    if (movesun <= 450) {
        movesun = 450;
    }}
    if (movemoon >= 750) {
        movemoon = 750;
     }else {
    if (movemoon <= 450) {
        movemoon = 450;
    }}

    if (carMove > 1200) {
        carMove = -300;
    }
    if (pickupMove > 1200) {
        pickupMove = -300;
    }
    if (busMove > 1250) {
        busMove = -350;
    }
    if (planescale >0.3) {
        planescale-=.0005f;
    }else if(planeMovey>1000){
    planescale=0.5;
    }

    if (planeMovey > 1000) {
        planeMovex = 40;
        planeMovey = 300;
    }
     if (landingMovey<470) {
        landingMovex=-400;
        landingMovey=900;

    } if (landingscale <0.4) {
        landingscale+=.005f;
    }
    //if (manMovey>370) {
       // manMovey = maninitialY ;
       // manMovex=maninitialX;
       // }


    glutPostRedisplay();
    glutTimerFunc(10, update_r, 0);
}

void keyboard_r(unsigned char key, int x, int y) {
    switch (key) {
        case 'd': // Switch to day
            isDay = true;
            isNight = false;
            break;
        case 'n': // Switch to night
            isDay = false;
            isNight = true;
            break;
        case's':
            if(isDay){
             paused = !paused;         // Toggle state
            if (paused) {
                savebusMove = busMove;

            } else {
                busMove = savebusMove;}}
            if(!isDay){
             carpaused = !carpaused;         // Toggle state
            if (carpaused) {
                savecarMove = carMove;

            } else {
                carMove = savecarMove;}}
                break;
                case 'a':
                if(isDay)
             carMove+=2.5;
            glutPostRedisplay();

            break;
             case 'b':
                if(!isDay)
             busMove+=2.5;
            glutPostRedisplay();

            break;
            case 'p':
                if(isDay)
              planeMovex+=2.4f;
            planeMovey+=2.9f;
            glutPostRedisplay();


            break;
            case 'q':
                if(!isDay)
              landingMovex+=2.4f;
                landingMovey-=2.9f;
            glutPostRedisplay();

            break;
        case 27:     // ESC key
            exit(0);
            break;
        default:
              glutKeyboardFunc(keyboard);
    }
    glutPostRedisplay();
}
void mouse_r(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
             PlaySound(TEXT("airline-pre-boarding.wav"), NULL, SND_FILENAME | SND_ASYNC);

            }
        else if (button == GLUT_RIGHT_BUTTON) {

            PlaySound(TEXT("big-plane-sound-effect-247601.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }
    }
}

///////all shariar



bool isDay1 = true;
bool isVisible = false;

float planex1 = 1200.0f;
float planey1 = 380.0f;
float targetx1 = 0.0f;
float targety1 = 1000.0f;
float planSpeed1 = 5.0f;
bool isPlaneMoving1 = true;
bool isStopped1 = false;
bool restartPlane1 = false;
float textIntensity1 = 1.0f;
bool isFading1 = true;

float movex1 = 0.0f;
float movey1 = 0.0f;

struct Point {
    float x, y;
};

Point points[] = {
    {0, 338},      // Starting point
    {655, 335},    // Intermediate point
    {1000,700},
    {1200,720}// Ending point
};



bool isFullscreen1 = false; // Track fullscreen state

const int numPoints = sizeof(points) / sizeof(points[0]);

// Global variables for animation
float currentTime = 0.0f; // Current time in seconds
const float totalTime = 10.0f; // Total animation time in seconds

// Function to perform linear interpolation between two points
Point lerp(const Point& p1, const Point& p2, float t) {
    return {p1.x + t * (p2.x - p1.x), p1.y + t * (p2.y - p1.y)};
}

// Function to calculate the current position based on time
Point getCurrentPosition(float time) {
    float segmentTime = totalTime / (numPoints - 1); // Time for each segment
    int segmentIndex = static_cast<int>(time / segmentTime);

    if (segmentIndex >= numPoints - 1) {
        return points[numPoints - 1]; // Stay at the last point after animation ends
    }

    float t = fmod(time, segmentTime) / segmentTime; // Normalized time within the segment
    return lerp(points[segmentIndex], points[segmentIndex + 1], t);
}



float cloud_positions1 [10][2] =
{
    {100, 800}, {300, 850}, {500, 750}, {700, 800}, {900, 700},
    {1100, 850}, {200, 900}, {600, 650}, {800, 950}, {1000, 700}
};

void drawCircle1 (float cx, float cy, float r)
{
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; i++)
    {
        float angle = 2 * M_PI * i / 100;
        float x = r * cos(angle);
        float y = r * sin(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawCloud11 (float x, float y)
{
    if(!isDay) return;
    glColor3f(0.68f, 0.84f, 0.90f);
    drawCircle1(x, y, 40);
    drawCircle1(x + 50, y + 20, 50);
    drawCircle1(x + 100, y, 40);
}

void drawCloud21 (float x, float y)
{
    if(!isDay) return;
    glColor3f(0.68f, 0.84f, 0.90f);
    drawCircle1(x, y, 30);
    drawCircle1(x + 40, y + 15, 35);
    drawCircle1(x + 80, y, 30);
    drawCircle1(x + 20, y - 15, 25);
}

void drawCloud31 (float x, float y)
{
    if(!isDay) return;
    glColor3f(0.68f, 0.84f, 0.90f);
    drawCircle1(x, y, 50);
    drawCircle1(x + 60, y + 30, 60);
    drawCircle1(x + 120, y, 50);
    drawCircle1(x + 40, y - 20, 40);
}


void updateCloudPositions1 ()
{
    for (int i = 0; i < 10; i++)
    {
        cloud_positions1[i][0] += (i % 3 + 1) * 0.2f;
        if (cloud_positions1[i][0] > 1200)
        {
            cloud_positions1[i][0] = -200;
        }
    }
    glutPostRedisplay();
}


void sky1 ()
{


    if(isDay)
    {
        glBegin(GL_QUADS);

        glColor3f(0.31f, 0.85f, 0.91f);
        glVertex2f(0, 1000);
        glVertex2f(1200, 1000);

        glColor3f(0.85f, 0.95f, 0.75f);
        glVertex2f(1200,380);
        glVertex2f(0, 380);

        glEnd();
    }
    else
    {
        glBegin(GL_QUADS);

        glColor3f(0.2f, 0.08f, 0.31f);
        glVertex2f(0, 1000);
        glVertex2f(1200, 1000);

        glColor3f(0.3f, 0.9f, 0.5f);
        glVertex2f(1200,380);
        glVertex2f(0, 380);

        glEnd();
    }



}

void handleKeypress1 (unsigned char key, int x, int y)
{
    if (key == 'f' || key == 'F')
    {
        if (isFullscreen1)
        {
            glutReshapeWindow(1200, 1000);
            glutPositionWindow(100, 100);
        }
        else
        {
            glutFullScreen();
        }
        isFullscreen1 = !isFullscreen1;
    }
    else if (key == 27)
    {
        exit(0);
    }
    else if (key == 'd' || key == 'D')
    {
        isDay1 = true;
    }
    else if (key == 'n' || key == 'N')
    {
        isDay1 = false;
    }
    else if(key == 's' || key == 'S')
    {
        isVisible = !isVisible;

    }
      glutKeyboardFunc(keyboard);

    glutPostRedisplay();
}

void mouseClick1 (int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        isStopped1 = !isStopped1; // Toggle stop/move state
    }
}


void tiels1 ()
{
    if(isDay)
    {
        glBegin(GL_QUADS);
        glColor3f(0.82f, 0.92f, 0.79f);
        glVertex2f(0, 380);
        glVertex2f(1200, 380);

        glColor3f(0.48f, 0.60f, 0.59f);
        glVertex2f(1200, 0);
        glVertex2f(0, 0);
        glEnd();
    }
    else
    {
        glBegin(GL_QUADS);
        glColor3f(0.73f, 0.8f, 0.86f);
        glVertex2f(0, 380);
        glVertex2f(1200, 380);

        glColor3f(0.60f, 0.63f, 0.69f);
        glVertex2f(1200, 0);
        glVertex2f(0, 0);
        glEnd();

    }

}

void wall11 ()
{
    glBegin(GL_QUADS);
    glColor3f(0.85f, 0.86f, 0.74f);
    glVertex2f(78,1000);
    glVertex2f(228,1000);
    glColor3f(0.44f, 0.49f, 0.45f);
    glVertex2f(228,360);
    glVertex2f(78,360);
    glEnd();
}

void long_wall11 ()
{
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(378,1000);
    glVertex2f(385,1000);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(385,400);
    glVertex2f(378,400);
    glEnd();
}

void long_wall21 ()
{
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(535,1000);
    glVertex2f(542,1000);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(542,400);
    glVertex2f(535,400);
    glEnd();
}

void long_wall31 ()
{
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(692,1000);
    glVertex2f(699,1000);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(699,400);
    glVertex2f(692,400);
    glEnd();
}

void wall21 ()
{
    glBegin(GL_QUADS);
    glColor3f(0.85f, 0.86f, 0.74f);
    glVertex2f(858,1000);
    glVertex2f(1008,1000);
    glColor3f(0.44f, 0.49f, 0.45f);
    glVertex2f(1008,360);
    glVertex2f(858,360);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(1171,1000);
    glVertex2f(1178,1000);

    glVertex2f(1178,400);
    glVertex2f(1171,400);
    glEnd();

}



void top_wall1 ()
{
    glBegin(GL_QUADS);
    glColor3f(0.39f, 0.27f, 0.12f);
    glVertex2f(0,900);
    glVertex2f(1200,900);
    glColor3f(0.39f, 0.27f, 0.12f);
    glVertex2f(1200,870);
    glVertex2f(0,870);
    glEnd();
}

void renderBitmapString1 (float x, float y, void *font, const char *string)
{
    const char *c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}



void updateTextColorIntensity1 (int value)
{

    if (isFading1)
    {
        textIntensity1 -= 0.05f;
        if (textIntensity1 <= 0.5f)
        {
            textIntensity1 = 0.5f;
            isFading1 = false;
        }
    }
    else
    {
        textIntensity1 += 0.05f;
        if (textIntensity1 >= 1.0f)
        {
            textIntensity1 = 1.0f;
            isFading1 = true;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(100, updateTextColorIntensity1, 0);
}
void renderRealTimeClock1 (float x, float y, void *font)
{
    time_t now = time(0);
    struct tm *timeinfo = localtime(&now);

    char buffer[9];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);

    glColor3f(0.0f, 0.0f, 0.0f);
    renderBitmapString1(x, y, font, buffer);
}

void tv1()
{
    // TV Frame
    glBegin(GL_QUADS);
    glColor3f(0.37f, 0.43f, 0.39f); // Dark grey border
    glVertex2f(40, 970);
    glVertex2f(270, 970);
    glVertex2f(270, 780);
    glVertex2f(40, 780);
    glEnd();

    // Inner Display Area
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f); // Black background
    glVertex2f(52, 960);
    glVertex2f(258, 960);
    glVertex2f(258, 790);
    glVertex2f(52, 790);
    glEnd();

    // Header (yellow bar)
    glBegin(GL_QUADS);
    glColor3f(0.96f, 0.64f, 0.0f); // Yellow
    glVertex2f(52, 960);
    glVertex2f(258, 960);
    glVertex2f(258, 933);
    glVertex2f(52, 933);
    glEnd();

    // Text with dynamic intensity
    glColor3f(0.0f * textIntensity1, 0.0f * textIntensity1, 0.0f * textIntensity1);
    renderBitmapString1(60, 940, GLUT_BITMAP_HELVETICA_12, "DEPARTURES");


    renderRealTimeClock1(198, 940, GLUT_BITMAP_HELVETICA_18);

    // Column Titles
    glColor3f(1.0f * textIntensity1, 1.0f * textIntensity1, 1.0f * textIntensity1);
    renderBitmapString1(60, 918, GLUT_BITMAP_HELVETICA_12, "TIME");
    renderBitmapString1(110, 918, GLUT_BITMAP_HELVETICA_12, "TO");
    renderBitmapString1(160, 918, GLUT_BITMAP_HELVETICA_12, "GATE");
    renderBitmapString1(205, 918, GLUT_BITMAP_HELVETICA_12, "INFO");

    // Flight Rows
    glColor3f(1.0f * textIntensity1, 1.0f * textIntensity1, 1.0f * textIntensity1);
    renderBitmapString1(60, 890, GLUT_BITMAP_HELVETICA_12, "08:52");
    glColor3f(1.0f * textIntensity1, 0.65f * textIntensity1, 0.0f * textIntensity1);
    renderBitmapString1(110, 890, GLUT_BITMAP_HELVETICA_12, "TORONTO");
    glColor3f(1.0f * textIntensity1, 1.0f * textIntensity1, 1.0f * textIntensity1);
    renderBitmapString1(160, 890, GLUT_BITMAP_HELVETICA_12, "C12");
    glColor3f(0.0f * textIntensity1, 1.0f * textIntensity1, 0.0f * textIntensity1);
    renderBitmapString1(205, 890, GLUT_BITMAP_HELVETICA_12, "BOARDING");

    glColor3f(1.0f * textIntensity1, 1.0f * textIntensity1, 1.0f * textIntensity1);
    renderBitmapString1(60, 862, GLUT_BITMAP_HELVETICA_12, "09:05");
    glColor3f(1.0f * textIntensity1, 0.65f * textIntensity1, 0.0f * textIntensity1);
    renderBitmapString1(110, 862, GLUT_BITMAP_HELVETICA_12, "LONDON");
    glColor3f(1.0f * textIntensity1, 1.0f * textIntensity1, 1.0f * textIntensity1);
    renderBitmapString1(160, 862, GLUT_BITMAP_HELVETICA_12, "A10");
    glColor3f(0.0f * textIntensity1, 1.0f * textIntensity1, 0.0f * textIntensity1);
    renderBitmapString1(205, 862, GLUT_BITMAP_HELVETICA_12, "GATE ON");


    glColor3f(1.0f * textIntensity1, 1.0f * textIntensity1, 1.0f * textIntensity1);
    renderBitmapString1(60, 832, GLUT_BITMAP_HELVETICA_12, "10:20");
    glColor3f(1.0f * textIntensity1, 0.65f * textIntensity1, 0.0f * textIntensity1);
    renderBitmapString1(110, 832, GLUT_BITMAP_HELVETICA_12, "ITALY");
    glColor3f(1.0f * textIntensity1, 1.0f * textIntensity1, 1.0f * textIntensity1);
    renderBitmapString1(160, 832, GLUT_BITMAP_HELVETICA_12, "B09");
    glColor3f(1.0f * textIntensity1, 0.0f * textIntensity1, 0.0f * textIntensity1);
    renderBitmapString1(205, 832, GLUT_BITMAP_HELVETICA_12, "DELAYED");


    glColor3f(1.0f * textIntensity1, 1.0f * textIntensity1, 1.0f * textIntensity1);
    renderBitmapString1(60, 802, GLUT_BITMAP_HELVETICA_12, "10:20");
    glColor3f(1.0f * textIntensity1, 0.65f * textIntensity1, 0.0f * textIntensity1);
    renderBitmapString1(110, 802, GLUT_BITMAP_HELVETICA_12, "USA");
    glColor3f(1.0f * textIntensity1, 1.0f * textIntensity1, 1.0f * textIntensity1);
    renderBitmapString1(160, 802, GLUT_BITMAP_HELVETICA_12, "B09");
    glColor3f(1.0f * textIntensity1, 0.0f * textIntensity1, 0.0f * textIntensity1);
    renderBitmapString1(205, 802, GLUT_BITMAP_HELVETICA_12,"CANCEL");

    glBegin(GL_LINES);
    glColor3f(0.3f, 0.3f, 0.3f);

    glVertex2f(52, 910);
    glVertex2f(258, 910);
    glVertex2f(52, 880);
    glVertex2f(258, 880);
    glVertex2f(52, 850);
    glVertex2f(258, 850);
    glVertex2f(52, 820);
    glVertex2f(258, 820);
    glEnd();
}



void tv2()
{

    glBegin(GL_QUADS);
    glColor3f(0.149f, 0.031f, 0.0f);

    glVertex2f(820, 970);
    glVertex2f(1050, 970);
    glVertex2f(1050, 780);
    glVertex2f(820, 780);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.235f, 0.157f, 0.294f);

    glVertex2f(832, 960);
    glVertex2f(1038, 960);
    glVertex2f(1038, 790);
    glVertex2f(832, 790);
    glEnd();

    // Header (yellow bar)
    glBegin(GL_QUADS);
    glColor3f(0.96f, 0.64f, 0.0f); // Yellow
    glVertex2f(832, 960);
    glVertex2f(1038, 960);
    glVertex2f(1038, 933);
    glVertex2f(832, 933);
    glEnd();

    // Header Text
    glColor3f(0.0f, 0.0f, 0.0f); // Black text
    renderBitmapString1(840, 940, GLUT_BITMAP_HELVETICA_12, "ARAIVAL");


    renderRealTimeClock1(978, 940, GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0f * textIntensity1, 1.0f * textIntensity1, 1.0f * textIntensity1);
    renderBitmapString1(840, 918, GLUT_BITMAP_HELVETICA_12, "TIME");
    renderBitmapString1(890, 918, GLUT_BITMAP_HELVETICA_12, "TO");
    renderBitmapString1(940, 918, GLUT_BITMAP_HELVETICA_12, "GATE");
    renderBitmapString1(987, 918, GLUT_BITMAP_HELVETICA_12, "INFO");


    glColor3f(1.0f * textIntensity1, 1.0f * textIntensity1, 1.0f * textIntensity1);
    renderBitmapString1(840, 890, GLUT_BITMAP_HELVETICA_12, "08:52");
    glColor3f(1.0f * textIntensity1, 0.65f * textIntensity1, 0.0f * textIntensity1);
    renderBitmapString1(890, 890, GLUT_BITMAP_HELVETICA_12, "KENYA");
    glColor3f(1.0f * textIntensity1, 1.0f * textIntensity1, 1.0f * textIntensity1);
    renderBitmapString1(940, 890, GLUT_BITMAP_HELVETICA_12, "C12");
    glColor3f(0.0f * textIntensity1, 1.0f * textIntensity1, 0.0f * textIntensity1);
    renderBitmapString1(987, 890, GLUT_BITMAP_HELVETICA_12, "BOARDING");


    glColor3f(1.0f * textIntensity1, 1.0f * textIntensity1, 1.0f * textIntensity1);
    renderBitmapString1(840, 862, GLUT_BITMAP_HELVETICA_12, "09:05");
    glColor3f(1.0f * textIntensity1, 0.65f * textIntensity1, 0.0f * textIntensity1);
    renderBitmapString1(890, 862, GLUT_BITMAP_HELVETICA_12, "INDIA");
    glColor3f(1.0f * textIntensity1, 1.0f * textIntensity1, 1.0f * textIntensity1);
    renderBitmapString1(940, 862, GLUT_BITMAP_HELVETICA_12, "A10");
    glColor3f(0.0f * textIntensity1, 1.0f * textIntensity1, 0.0f * textIntensity1);
    renderBitmapString1(987, 862, GLUT_BITMAP_HELVETICA_12, "GATE ON");


    glColor3f(1.0f * textIntensity1, 1.0f * textIntensity1, 1.0f * textIntensity1);
    renderBitmapString1(840, 832, GLUT_BITMAP_HELVETICA_12, "10:20");
    glColor3f(1.0f * textIntensity1, 0.65f * textIntensity1, 0.0f * textIntensity1);
    renderBitmapString1(890, 832, GLUT_BITMAP_HELVETICA_12, "JAPAN");
    glColor3f(1.0f * textIntensity1, 1.0f * textIntensity1, 1.0f * textIntensity1);
    renderBitmapString1(940, 832, GLUT_BITMAP_HELVETICA_12, "B09");
    glColor3f(1.0f * textIntensity1, 0.0f * textIntensity1, 0.0f * textIntensity1);
    renderBitmapString1(987, 832, GLUT_BITMAP_HELVETICA_12, "DELAYED");


    glColor3f(1.0f * textIntensity1, 1.0f * textIntensity1, 1.0f * textIntensity1);
    renderBitmapString1(840, 802, GLUT_BITMAP_HELVETICA_12, "11:30");
    glColor3f(1.0f * textIntensity1, 0.65f * textIntensity1, 0.0f * textIntensity1);
    renderBitmapString1(890, 802, GLUT_BITMAP_HELVETICA_12, "CHAINA");
    glColor3f(1.0f * textIntensity1, 1.0f * textIntensity1, 1.0f * textIntensity1);
    renderBitmapString1(940, 802, GLUT_BITMAP_HELVETICA_12, "D05");
    glColor3f(1.0f * textIntensity1, 0.0f * textIntensity1, 0.0f * textIntensity1);
    renderBitmapString1(987, 802, GLUT_BITMAP_HELVETICA_12, "CANCELE");

    glBegin(GL_LINES);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex2f(832, 910);
    glVertex2f(1038, 910);
    glVertex2f(832, 880);
    glVertex2f(1038, 880);
    glVertex2f(832, 850);
    glVertex2f(1038, 850);
    glVertex2f(832, 820);
    glVertex2f(1038, 820);
    glEnd();
}




void drawPartialHollowArc1 (float cx, float cy, float outerRadius, float innerRadius, float startAngle, float endAngle)
{
    int numSegments = 100;
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= numSegments; i++)
    {
        float angle = startAngle + (endAngle - startAngle) * i / numSegments;
        float xOuter = outerRadius * cos(angle);
        float yOuter = outerRadius * sin(angle);
        float xInner = innerRadius * cos(angle);
        float yInner = innerRadius * sin(angle);

        glVertex2f(cx + xOuter, cy + yOuter);
        glVertex2f(cx + xInner, cy + yInner);
    }
    glEnd();
}

void lift_part1()
{
    glPushMatrix();
    glTranslatef(movex1,movey1,0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.32f, 0.33f, 0.35f);
    glVertex2f(0,540);
    glVertex2f(0,540);
    glVertex2f(0,510);
    glVertex2f(0,510);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(movex1,movey1,0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0,510);
    glVertex2f(25,510);
    glVertex2f(25,480);
    glVertex2f(0,480);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(movex1,movey1,0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0,480);
    glVertex2f(45,480);
    glVertex2f(45,450);
    glVertex2f(0,450);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(movex1,movey1,0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0,450);
    glVertex2f(65,450);
    glVertex2f(65,420);
    glVertex2f(0,420);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(movex1,movey1,0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0,420);
    glVertex2f(85,420);
    glVertex2f(85,390);
    glVertex2f(0,390);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(movex1,movey1,0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0,390);
    glVertex2f(105,390);
    glVertex2f(105,370);
    glVertex2f(0,370);
    glEnd();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(movex1,movey1,0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0,370);
    glVertex2f(109,370);
    glVertex2f(109,395);
    glVertex2f(0,395);
    glEnd();

    glPopMatrix();



    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(0,700);
    glVertex2f(0,715);
    glVertex2f(110,562);
    glVertex2f(110,547);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(110,548);
    glVertex2f(110,562);
    glVertex2f(180,558);
    glVertex2f(180,548);
    glEnd();









    glBegin(GL_POLYGON);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(0,358);
    glVertex2f(200,358);
    glVertex2f(200,375);
    glVertex2f(90,375);
    glVertex2f(0,510);
    glEnd();

}



void liftmovement1 (int value)
{

    movex1 -= 0.10;
    movey1 += 0.10;

    if(movex1 <-4 && movey1>=4)
    {
        movex1 =  5;
        movey1 = -5;
    }
    glutPostRedisplay();

    glutTimerFunc(20,liftmovement1,0);
}
void black_wall1 ()
{
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(228,400);
    glVertex2f(1200,400);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(1200,380);
    glVertex2f(228,380);
    glEnd();
}

void plan1 ()
{
    if (!isPlaneMoving1) return;

    glPushMatrix();
    glTranslatef(planex1 - 360, planey1 - 720, 0.0f); // Offset based on plan structure


    // plan body
    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex2f(601.7013684734217,822.7771865940432);
    glVertex2f(616.5624037600165,822.8872683369069);
    glVertex2f(625.3689431891098,827.0703745657262);
    glVertex2f(632.9645834467028,833.1248704232279);
    glVertex2f(641.3307959043415,840.5003471950936);
    glVertex2f(650.2474170762983,848.6463961670048);
    glVertex2f(661.8060000769833,859.5444887105078);
    glVertex2f(670.9427847346676,868.6812733681921);
    glVertex2f(673.8049100491229,871.8736430112384);
    glVertex2f(676.0065449063962,874.1853605113755);
    glVertex2f(677.8779345350786,875.7265049114668);
    glVertex2f(680.8501415923976,876.9374040829671);
    glVertex2f(683.6021851639891,877.7079762830127);
    glVertex2f(687.1248009356265,877.2676493115581);
    glVertex2f(691.0877436787184,876.7172405972398);
    glVertex2f(695.9313403647197,875.7265049114668);
    glVertex2f(699.0136291649025,875.7265049114668);
    glVertex2f(701.2152640221757,874.1853605113755);
    glVertex2f(700,870);
    glVertex2f(698.3531387077204,863.2872679678725);
    glVertex2f(677.9880162779422,810.8883583647672);
    glVertex2f(678.4335824768156,809.0619753795652);
    glVertex2f(682.2606173090358,807.6123409734212);
    glVertex2f(687.0734035374338,806.3946480722602);
    glVertex2f(692.5820142807811,804.249189151167);
    glVertex2f(696.7569613704758,800.9440227051587);
    glVertex2f(698.4965226578486,797.7548270116419);
    glVertex2f(697.9746542716368,794.3916751893878);
    glVertex2f(671.0114543173582,789.752845089727);
    glVertex2f(649.5826595925173,786.4208318745342);
    glVertex2f(627.0691748781237,784.039597914358);
    glVertex2f(603.5815489982034,783.173694656112);
    glVertex2f(583.2328224294246,782.9572188415506);
    glVertex2f(566.4177682991556,783.4595735040637);
    glVertex2f(553.1805927650474,784.1132611847603);
    glVertex2f(536.5405324795405,785.7569049882529);
    glVertex2f(519.9350176210129,787.6468406859151);
    glVertex2f(506.4259416134842,789.2222282255444);
    glVertex2f(490.827605780575,791.2679116134669);
    glVertex2f(471.6799013933147,793.4260276476035);
    glVertex2f(319.7491964930285,818.3090803410508);
    glVertex2f(312.4413919713593,819.6495133743365);
    glVertex2f(306.3156307666736,820.8084411698176);
    glVertex2f(300.1898695619879,822.4640523062192);
    glVertex2f(295,825);
    glVertex2f(290.4217638572188,828.0103496131644);
    glVertex2f(287.0277610275957,832.3149385678084);
    glVertex2f(286.1999554593049,837.7784553179337);
    glVertex2f(288.6005916071771,842.5797276134982);
    glVertex2f(294.1468889141223,845.1459248749206);
    glVertex2f(298.3686973119462,846.8843165681423);
    glVertex2f(301.5143584711091,847.2154387954225);
    glVertex2f(304.8255807439122,847.712122136343);
    glVertex2f(307.0606557780543,849.4505138295647);
    glVertex2f(309.2957308121964,851.7683694205269);
    glVertex2f(312.110269744079,854.0862250114891);
    glVertex2f(316.0009559146226,856.072958375171);
    glVertex2f(323.6084683806805,858.2562240694856);
    glVertex2f(332.3583891523874,858.6494789356298);
    glVertex2f(339.7319178925899,858.4528515025577);
    glVertex2f(349.8582306958014,857.9612820198775);
    glVertex2f(359.4929749163326,856.7815183214451);
    glVertex2f(370.5041111683683,855.8966948726207);
    glVertex2f(382.0068160030842,854.3236754080442);
    glVertex2f(407.7139011876407,850.8951477649068);
    glVertex2f(426.2403088599048,848.9269556324431);
    glVertex2f(447.302250245076,845.2237571471381);
    glVertex2f(472.9931897368784,843.1407079991542);
    glVertex2f(500,840);
    glVertex2f(518.1259212765311,836.428660744539);
    glVertex2f(542.6596112416756,832.9569121645657);
    glVertex2f(559.3240044255474,830.6424131112501);
    glVertex2f(572.0537492187829,828.559363963266);
    glVertex2f(583.3947945800289,826.7077647206136);
    glVertex2f(591.7269911719648,825.0876153832927);
    glEnd();


//plan pakha

    glBegin(GL_POLYGON);
    glColor3f(0.671, 0.671, 0.671);
    glVertex2f(396.9036705680077,809.4761894569062);
    glVertex2f(403.6439874186744,809.8994102235503);
    glVertex2f(410,810);
    glVertex2f(416.3890938123589,808.7482393234756);
    glVertex2f(423.8717046628445,806.7748034947759);
    glVertex2f(428.7230677417309,805.0480471446638);
    glVertex2f(432.7521658919924,802.4167993730644);
    glVertex2f(435,800);
    glVertex2f(435.0545076921418,797.400983308453);
    glVertex2f(434.6433752278294,794.2763765796788);
    glVertex2f(434.1500162706545,791.6451288080793);
    glVertex2f(433.0810718634423,788.2738426007176);
    glVertex2f(432.176580441955,786.629312743468);
    glVertex2f(431.0254095418803,785.4781418433931);
    glVertex2f(428.8052042345933,784.7381034076308);
    glVertex2f(424.3650636200194,784.1625179575934);
    glVertex2f(418.6914356125083,784.2447444504559);
    glVertex2f(413.1822605907221,784.5736504219059);
    glVertex2f(406.3574616831363,785.3959153505307);
    glVertex2f(400.9305131542126,786.5470862506054);
    glVertex2f(396.6547355253636,788.0271631221301);
    glVertex2f(393.6123552894518,789.7539194722422);
    glVertex2f(392.7078638679645,793.6185646367788);
    glVertex2f(392.954543346552,798.6343807013902);
    glVertex2f(394.0234877537642,804.7191411732139);
    glEnd();

//pakha picone side

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(435.9567675257559,799.52762557011);
    glVertex2f(439.0196231814829,798.5331919156531);
    glVertex2f(442.4802522989928,797.0216527608787);
    glVertex2f(446.0602134550374,795.6204456446391);
    glVertex2f(449.1230691107645,794.3565705669344);
    glVertex2f(450.8732723426085,793.6803556819036);
    glVertex2f(451.9870380356002,792.5268126427337);
    glVertex2f(452.4271709945014,790.77567234407);
    glVertex2f(451.6347863890862,789.6175717669247);
    glVertex2f(450.6290674668284,788.6728055066219);
    glVertex2f(448.7090586152455,788.4594711897793);
    glVertex2f(447.002384080505,788.2766132039143);
    glVertex2f(445.5090438626071,788.0328025560942);
    glVertex2f(443.1318900463616,787.8804209012067);
    glVertex2f(440.9071178850035,787.7280392463191);
    glVertex2f(438.1642480970278,787.6975620153416);
    glVertex2f(436.4575735622874,787.7585155772066);
    glVertex2f(435.2689966541646,787.7585155772966);
    glVertex2f(434.0499434150643,786.8442256479714);
    glVertex2f(432.5261268661889,786.3261280213537);
    glVertex2f(433.6657998943709,790.252677886258);
    glVertex2f(434.4647565627031,793.4485045595866);
    glVertex2f(434.8255757032402,796.2061937051201);
    glVertex2f(435.2637132310352,799.1185196251696);
    glEnd();

//plan window
    if(isDay)
    {
        glBegin(GL_POLYGON);
        glColor3f(0,0,0);
        glVertex2f(308.6783405097053,848.2569399231455);
        glVertex2f(309.2960904711659,847.3179599817253);
        glVertex2f(310.7539803802131,846.7990500140983);
        glVertex2f(312,846);
        glVertex2f(313.5462102060155,846.378980040305);
        glVertex2f(314.386350153602,848.2322209246871);
        glVertex2f(314.8805501227705,849.6406998368175);
        glVertex2f(314.5840301412604,850.9750397535727);
        glVertex2f(313.2744002229728,851.4692397227412);
        glVertex2f(311.7670903170087,851.691629708867);
        glVertex2f(310.8281103755884,851.0985897458647);
        glVertex2f(310.0373904249188,850.3325797936535);
        glVertex2f(309.3455104680828,849.5912798399006);
        glEnd();

    }
    else
    {
        glBegin(GL_POLYGON);
        glColor3f(1.000, 0.992, 0.2);
        glVertex2f(308.6783405097053,848.2569399231455);
        glVertex2f(309.2960904711659,847.3179599817253);
        glVertex2f(310.7539803802131,846.7990500140983);
        glVertex2f(312,846);
        glVertex2f(313.5462102060155,846.378980040305);
        glVertex2f(314.386350153602,848.2322209246871);
        glVertex2f(314.8805501227705,849.6406998368175);
        glVertex2f(314.5840301412604,850.9750397535727);
        glVertex2f(313.2744002229728,851.4692397227412);
        glVertex2f(311.7670903170087,851.691629708867);
        glVertex2f(310.8281103755884,851.0985897458647);
        glVertex2f(310.0373904249188,850.3325797936535);
        glVertex2f(309.3455104680828,849.5912798399006);
        glEnd();

    }

//plan window2
    if(isDay)
    {
        glBegin(GL_POLYGON);
        glColor3f(0,0,0);

        glVertex2f(315.6712700734402,846.3542700418466);
        glVertex2f(316.3137300333593,845.4400000988848);
        glVertex2f(318.1175599208245,845.2917401081341);
        glVertex2f(319.9460998067481,845.2670301096757);
        glVertex2f(322.886589623301,848.2075199262287);
        glVertex2f(323.1288332291762,848.9642452259202);
        glVertex2f(322.6765300989596,849.5431932325974);
        glVertex2f(322.0794899670737,849.8145751107273);
        glVertex2f(321.3377128335185,849.9593121123967);
        glVertex2f(320.5778435747546,850.0859569888573);
        glVertex2f(319.9446191924514,850.1764176149006);
        glVertex2f(319.1304735580616,850.2487861157352);
        glVertex2f(318.3886964245064,850.3754309921959);
        glVertex2f(317.7554720422032,850.4477994930306);
        glVertex2f(317.2488925363606,850.4477994930306);
        glVertex2f(316.8870500321873,850.1402333644833);
        glVertex2f(316.5975760288487,849.5793774830147);
        glVertex2f(316.3081020255101,848.9099688502941);
        glVertex2f(316.0909965230061,848.4395735948689);
        glVertex2f(316,848);
        glVertex2f(315.8015225196675,847.4806909588098);
        glVertex2f(315.6567855179982,847.1912169554711);
        glEnd();

    }
    else
    {
        glBegin(GL_POLYGON);
        glColor3f(1.000, 0.992, 0.2);

        glVertex2f(315.6712700734402,846.3542700418466);
        glVertex2f(316.3137300333593,845.4400000988848);
        glVertex2f(318.1175599208245,845.2917401081341);
        glVertex2f(319.9460998067481,845.2670301096757);
        glVertex2f(322.886589623301,848.2075199262287);
        glVertex2f(323.1288332291762,848.9642452259202);
        glVertex2f(322.6765300989596,849.5431932325974);
        glVertex2f(322.0794899670737,849.8145751107273);
        glVertex2f(321.3377128335185,849.9593121123967);
        glVertex2f(320.5778435747546,850.0859569888573);
        glVertex2f(319.9446191924514,850.1764176149006);
        glVertex2f(319.1304735580616,850.2487861157352);
        glVertex2f(318.3886964245064,850.3754309921959);
        glVertex2f(317.7554720422032,850.4477994930306);
        glVertex2f(317.2488925363606,850.4477994930306);
        glVertex2f(316.8870500321873,850.1402333644833);
        glVertex2f(316.5975760288487,849.5793774830147);
        glVertex2f(316.3081020255101,848.9099688502941);
        glVertex2f(316.0909965230061,848.4395735948689);
        glVertex2f(316,848);
        glVertex2f(315.8015225196675,847.4806909588098);
        glVertex2f(315.6567855179982,847.1912169554711);
        glEnd();

    }

//plan design 1

    glBegin(GL_POLYGON);
    glColor3f(1,1,0);
    glVertex2f(407.1423639682738,825.3805972762892);
    glVertex2f(402.1055975488507,827.9829265929911);
    glVertex2f(397.0688311294275,829.4100104118277);
    glVertex2f(392.7875796729178,830.3334175887219);
    glVertex2f(387.8347593604851,831.7605014075584);
    glVertex2f(384.2250767598085,832.5999624774623);
    glVertex2f(380.6153941593119,833.3554774403758);
    glVertex2f(373.6478672791099,834.7825612592123);
    glVertex2f(370,835);
    glVertex2f(365.3372026870616,835.789914543097);
    glVertex2f(360.3004362676385,836.1256989710585);
    glVertex2f(354.9042136279606,836.2550362998896);
    glVertex2f(349.6176464024862,836.3245963949616);
    glVertex2f(342.383396514995,835.9767959196015);
    glVertex2f(335.2187067225758,835.8376757294575);
    glVertex2f(330,835);
    glVertex2f(325.7445082308466,835.0310744947442);
    glVertex2f(319.5300129313596,834.3248716198025);
    glVertex2f(314.4453522317793,834.1130107573199);
    glVertex2f(307.3833234823622,833.1949470198957);
    glVertex2f(303.9229293951478,832.6299847199424);
    glVertex2f(299.6150918580034,831.8531615575065);
    glVertex2f(294.8835325958939,830.9350978200823);
    glVertex2f(292.6179146963481,830.228782596669);
    glVertex2f(290.8073289847237,829.9077709529598);
    glVertex2f(289.4095075299198,829.3004080703579);
    glVertex2f(291.7132579522276,826.9966576480501);
    glVertex2f(293.2623315120553,826.1625411158353);
    glVertex2f(296.7576769803844,824.4545882165381);
    glVertex2f(298.5450695494163,823.4615923448538);
    glVertex2f(302.7553720453581,821.991958454761);
    glVertex2f(305.1385621374006,821.3564410968829);
    glVertex2f(307.5217522294432,820.6414840692702);
    glVertex2f(308.8722266149339,822.1508377942304);
    glVertex2f(310.8979381931702,823.2629931705169);
    glVertex2f(312.6853307622021,823.8587906935276);
    glVertex2f(315.5848787075205,824.6134675560077);
    glVertex2f(318.2461076436347,825.0901055744162);
    glVertex2f(320.390978726473,825.5667435928247);
    glVertex2f(323.2494035104907,826.0984452767516);
    glVertex2f(327.8401696949939,826.6034295570469);
    glVertex2f(333.1195508071726,827.6593057794826);
    glVertex2f(337.4807786824507,828.3479207071581);
    glVertex2f(342.3469908380241,828.3479207071581);
    glVertex2f(346.8918493606823,828.5774590163833);
    glVertex2f(350.8858159412001,828.7151820019184);
    glVertex2f(354.9256901835629,828.6692743400733);
    glVertex2f(359.2410103969959,828.5774590163833);
    glVertex2f(363.1890693156687,828.4397360308482);
    glVertex2f(366.8097893523812,828.3796207611747);
    glVertex2f(370.4428452190587,828.1814540775378);
    glVertex2f(375.5951789936195,827.9172318326886);
    glVertex2f(378.6997903705985,827.7190651490516);
    glVertex2f(383.7860685839469,827.2566762205654);
    glVertex2f(388.8062912360831,826.7942872920792);
    glVertex2f(393.0338471536715,826.1997872411683);
    glVertex2f(396.5347918979243,826.0676761187436);
    glVertex2f(400,825);
    glVertex2f(402.7440146518823,825.4731760678328);
    glVertex2f(405,825);
    glEnd();


//plan design 2

    glBegin(GL_POLYGON);
    glColor3f(1,0,0);
    glVertex2f(677.5502946448202,808.9840128712718);
    glVertex2f(680.3668794105798,808.2257015881827);
    glVertex2f(684.2667660093239,806.9799044802506);
    glVertex2f(688.9791289828064,805.4632819140724);
    glVertex2f(693.6914919562888,803.1341829731558);
    glVertex2f(697.4830483717345,799.6134520159563);
    glVertex2f(698.4580200214206,796.5802068835999);
    glVertex2f(696.39974653875,793.7094570261911);
    glVertex2f(694.2873079644303,793.0594759264004);
    glVertex2f(691.2540628320738,792.4636599182589);
    glVertex2f(688.7624686162095,792.0303391850651);
    glVertex2f(685.6296410005061,791.7896197030336);
    glVertex2f(682.4524799786475,791.4366018117161);
    glVertex2f(679.8048457937653,791.0835839203984);
    glVertex2f(676.4511758262478,790.554057083422);
    glVertex2f(667.4492195976482,789.2302399909809);
    glVertex2f(661.359660972419,788.3476952626868);
    glVertex2f(655.7113747113368,788.171186317028);
    glVertex2f(645.4738558631254,788.2594407898574);
    glVertex2f(638.7665159280905,789.5832578822985);
    glVertex2f(632.3239394115436,791.0835839203984);
    glVertex2f(625.6165994765087,792.7604189041572);
    glVertex2f(619.3980736937012,793.9869604308165);
    glVertex2f(612.80396446208,795.6825885189476);
    glVertex2f(605.6446458677483,796.6246041234649);
    glVertex2f(598.67373039432,797.5666197279822);
    glVertex2f(590,800);
    glVertex2f(568.6824424536608,803.1523659965385);
    glVertex2f(553.2150142656674,805.6471124784729);
    glVertex2f(542.7370790415428,807.8092260961494);
    glVertex2f(530,810);
    glVertex2f(517.7896142221986,812.2997697636313);
    glVertex2f(500.3263888486576,814.7945162455657);
    glVertex2f(487.1873907104697,816.1250477025973);
    glVertex2f(472.7178611152501,817.9545284560159);
    glVertex2f(460,820);
    glVertex2f(449.7661934814535,821.280857098595);
    glVertex2f(440.8390864542306,822.186405181423);
    glVertex2f(432.9252236096611,823.5466003578333);
    glVertex2f(425.7532854067699,824.2885249995117);
    glVertex2f(418.0867307760932,825.1541037481364);
    glVertex2f(410.4201761454165,825.5250660689757);
    glVertex2f(404.5434183983594,827.5006502071003);
    glVertex2f(399.5823024435303,828.7409291958076);
    glVertex2f(395,830);
    glVertex2f(389.8789432965852,831.002614410509);
    glVertex2f(385.9392335677503,832.0969782240742);
    glVertex2f(382.4372693643416,832.6076813370713);
    glVertex2f(377.0384078840864,833.9209179133496);
    glVertex2f(371.6395464038312,834.7964089642018);
    glVertex2f(367.4080063247122,835.0152817269148);
    glVertex2f(362.8846358953093,835.890772777767);
    glVertex2f(381.2699479632053,836.5473910659061);
    glVertex2f(388.7116218954489, 835.963730365338);
    glVertex2f(394.4023137259882, 836.1096455404801);
    glVertex2f(402.573563533942, 835.5989424274829);
    glVertex2f(410, 835);
    glVertex2f(418.6925928313256, 834.4932842639238);
    glVertex2f(427.9100360256717, 834.4932842639238);
    glVertex2f(435.8866695592404, 834.4932842639238);
    glVertex2f(445.8131468454594, 833.7842501720511);
    glVertex2f(456.9804337924556, 833.0752160801783);
    glVertex2f(468.1477207394518, 832.1889234653373);
    glVertex2f(478.2514565486389, 831.1253723275281);
    glVertex2f(492.4321383860944, 829.7073041437826);
    glVertex2f(505.9037861316772, 828.289235960037);
    glVertex2f(518.1346242164826, 826.8711677762915);
    glVertex2f(529.8336867323834, 826.3393922073869);
    glVertex2f(538.1648373118886, 825.2758410695777);
    glVertex2f(544.7234026617117, 824.7440655006732);
    glVertex2f(553.0545532412169, 824.3895484547368);
    glVertex2f(560.8539282518175, 825.984751614505);
    glVertex2f(568.1215276935134, 828.289235960037);
    glVertex2f(575.2789187537646, 827.6697126687336);
    glVertex2f(579.685883879813, 827.0086972236011);
    glVertex2f(588.0585069299298, 825.3561586107699);
    glVertex2f(596.1009052754382, 823.813789238794);
    glVertex2f(605.9059677115703, 821.5002351808303);
    glVertex2f(613.507645330594, 820.618881253987);
    glVertex2f(620, 820);
    glVertex2f(628.7110005686413, 818.7460041594445);
    glVertex2f(637.8550475596479, 817.4239732691799);
    glVertex2f(646.7787560689295, 815.7714346563487);
    glVertex2f(653.3276300491149, 814.8267502010219);
    glVertex2f(658.2499414332626, 813.688396550488);
    glVertex2f(663.8315296426773, 812.912246334215);
    glVertex2f(669.5750412430981, 811.8256360314327);
    glVertex2f(675,810);
    glEnd();

//plan ar wheel

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(467.323604476862, 793.8868000927973);
    glVertex2f(467.1486076052906, 791.728505343418);
    glVertex2f(467.9069273820996, 790.3868626613713);
    glVertex2f(468.6069148683848, 789.3368814319434);
    glVertex2f(469.656890978127, 788.2285679119918);
    glVertex2f(470.823541908288, 786.945257520469);
    glVertex2f(471.6985262661445, 786.0702731626125);
    glVertex2f(471.9901877187634, 784.5536336089945);
    glVertex2f(471.2318679419544, 783.6786492511379);
    glVertex2f(473.7401564344764, 783.6786492511379);
    glVertex2f(475.6651220217607, 783.5619846700904);
    glVertex2f(477.0650969943311, 783.0369940553766);
    glVertex2f(477.8817490616639, 785.7202794149699);
    glVertex2f(478.2900750953302, 788.52022936464107);
    glVertex2f(478.9900625816154, 791.1451824381803);
    glVertex2f(477.8817490616639, 793.0701480254646);
    glVertex2f(474.5568085018091, 793.5368063496547);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(471.2318679419544, 783.6786492511379);
    glVertex2f(473.7401564344764, 783.6786492511379);
    glVertex2f(475.6651220217607, 783.5619846700904);
    glVertex2f(477.0650969943311, 783.0369940553766);
    glVertex2f(477.8817490616639, 785.7202794149699);
    glVertex2f(478.2900750953302, 788.52022936464107);
    glVertex2f(478.9900625816154, 791.1451824381803);
    glVertex2f(477.8817490616639, 793.0701480254646);
    glVertex2f(474.5568085018091, 793.5368063496547);
    glVertex2f(470.7795624232518, 782.9435456180261);
    glVertex2f(468.9685742727974, 781.8569527277534);
    glVertex2f(467.2662454113702, 779.7562064732263);
    glVertex2f(466.6505094402157, 777.2570428255991);
    glVertex2f(466.7591687292473, 774.757879177972);
    glVertex2f(467.8095418565065, 772.7295724494629);
    glVertex2f(469.5480940840927, 771.099683114054);
    glVertex2f(471.2328588683881, 770.3752878538721);
    glVertex2f(474, 770);
    glVertex2f(476.6833837937332, 771.1721226400721);
    glVertex2f(478.4943719441876, 772.9468910275175);
    glVertex2f(479.363462564057, 774.6854396519537);
    glVertex2f(479.5809648344603, 777.0397242475445);
    glVertex2f(479.1825474413603, 778.850712397999);
    glVertex2f(478.394928921513, 780.9514586525262);
    glVertex2f(477.2266802388695, 782.0380515427988);
    glVertex2f(476.5022849786877, 783.341963011126);
    glVertex2f(474.6912968282333, 783.6679408782079);
    glVertex2f(472.916528440788, 783.5230618261716);
    glVertex2f(471.685056498479, 783.0522040970534);
    glVertex2f(470.2665402309385, 782.593066506865);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex2f(470.6497536105954, 777.6078820251779);
    glVertex2f(471.6109943548288, 778.7250883066673);
    glVertex2f(473, 779);
    glVertex2f(474.1820970005985, 778.8400948356441);
    glVertex2f(475, 778);
    glVertex2f(475.4635983234833, 776.7535478099213);
    glVertex2f(475.1678672489715, 775.4063284704783);
    glVertex2f(474.3956805544127, 774.5519942552218);
    glVertex2f(473.7549298929702, 774.1905451641517);
    glVertex2f(472.7691596445973, 774.0426796268957);
    glVertex2f(471.4876583217124, 774.5519942552218);
    glVertex2f(470.8140486519909, 775.324180947806);
    glVertex2f(470.4854585691999, 776.6878297933631);
    glEnd();

//biman ar shamne wheel

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);

    glVertex2f(338.0860123426534, 814.9553895636764);
    glVertex2f(340.5028104776905, 814.8873107429711);
    glVertex2f(342.4770962781433, 814.5469166394447);
    glVertex2f(343.8727121026013, 813.491694918513);
    glVertex2f(344, 812);
    glVertex2f(343.3961603576644, 810.802581006548);
    glVertex2f(342.5792145092012, 810.0196750625443);
    glVertex2f(342.2047800995322, 808.9984927519652);
    glVertex2f(342.409017457438, 807.704995158565);
    glVertex2f(343.532317999075, 807.3305616446861);
    glVertex2f(344, 806);
    glVertex2f(343.4982785887223, 805.4924334856438);
    glVertex2f(342.3409386367327, 805.5264728959963);
    glVertex2f(341.5920716089748, 805.6285911270543);
    glVertex2f(341.1155198640379, 805.1520393821174);
    glVertex2f(340.8772439915695, 804.1308570715383);
    glVertex2f(341.5580321986221, 803.2117929920172);
    glVertex2f(342.3749780470854, 801.8161771657592);
    glVertex2f(342.7153721506117, 800.7269160362748);
    glVertex2f(342.783450971317, 799.1270637497009);
    glVertex2f(342.3749780470854, 798.0378026184167);
    glVertex2f(341.5580321986221, 797.254896180306);
    glVertex2f(340.638968119101, 796.3017926904323);
    glVertex2f(339.6518252188746, 795.9954379972586);
    glVertex2f(337.745618239127, 796.0635168179638);
    glVertex2f(336.3159630043164, 796.9825808974849);
    glVertex2f(335.0905442316215, 798.5824331840588);
    glVertex2f(334.9884260005636, 801.2375071915643);
    glVertex2f(336.2819235939637, 803.3139112230751);
    glVertex2f(337.6775394184218, 803.688344736954);
    glVertex2f(338.3923670358271, 805.0499211510595);
    glVertex2f(338, 806);
    glVertex2f(336.9627180180164, 806.5816946169281);
    glVertex2f(336.0776871318479, 806.6497734376334);
    glVertex2f(335.6692142076163, 807.8411527997756);
    glVertex2f(337.1329088527796, 808.3177045449124);
    glVertex2f(338.0489684000722, 808.6151148966998);
    glVertex2f(338.3100914456186, 809.7640562971037);
    glVertex2f(338.2056422274001, 810.6344664489249);
    glVertex2f(337.5963551211252, 811.870448864511);
    glVertex2f(337.3178238725425, 813.1586558892063);
    glVertex2f(337.4919059029067, 814.3250054926467);
    glEnd();

//plan wheel white

    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex2f(336.8122129534775, 800.5255726779957);
    glVertex2f(337.4929874201864, 801.6223759854711);
    glVertex2f(338.5141491202496, 801.9627632188254);
    glVertex2f(339.667683633284, 801.6791071910301);
    glVertex2f(340.6510245296412, 800.5444830798488);
    glVertex2f(340.5942933240822, 799.3720381649613);
    glVertex2f(339.9324292592264, 798.313055661192);
    glVertex2f(338.778894746192, 797.9348476241315);
    glVertex2f(337.6064498313045, 798.275234857486);
    glVertex2f(336.7933025516245, 799.3153069594023);
    glEnd();

//plan ar picone design

    glBegin(GL_QUADS);
    glColor3f(1,1,0);
    glVertex2f(640.3649788405372,840.7855787308916);
    glVertex2f(686.9455544805999,834.38813147375);
    glVertex2f(686.2316219576372,831.3539182511589);
    glVertex2f(637.7734519615494,838.2255187846741);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(1,0,0);
    glVertex2f(635.6598021060104,835.8485659284743);
    glVertex2f(684.8617517680204,828.3083290607669);
    glVertex2f(682.7291595226083,823.5861605173542);
    glVertex2f(630.5568135187741,831.5833814376499);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.710, 0.188, 0.176);
    glVertex2f(630.8594615936017, 826.9349535027229);
    glVertex2f(641.6609028365986, 826.2425534230437);
    glVertex2f(659.820141577471, 823.9399205999241);
    glVertex2f(681.6420157165726, 820.1990278903638);
    glVertex2f(676.7933652847228, 809.9534956313147);
    glVertex2f(672.7821916359841, 811.1896445946402);
    glVertex2f(660.943810409088, 813.3987205173624);
    glVertex2f(655.902585867491, 814.2483651030249);
    glVertex2f(650, 815);
    glVertex2f(642.3082724968925, 816.6840129152571);
    glVertex2f(633.5852547507585, 818.1000872246943);
    glVertex2f(626.1083823969294, 819.2329466722442);
    glVertex2f(623.2762337780543, 819.3462326169994);
    glVertex2f(621.1052229921038, 819.456087486666);
    glVertex2f(620.9433013020465, 820.8433741479075);
    glEnd();


//plan ar lag

    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex2f(638.0241243163877, 805.5777660223786);
    glVertex2f(650.8906284061493, 805.5777660223786);
    glVertex2f(662.7619332845481, 805.2934233905606);
    glVertex2f(675, 805);
    glVertex2f(684.3719733027114, 804.2271385212433);
    glVertex2f(691.0540251504328, 803.3741106257895);
    glVertex2f(699.5132184470164, 802.5210827303357);
    glVertex2f(703.0675013447407, 802.1656544405632);
    glVertex2f(704.8446427936027, 801.3126265451094);
    glVertex2f(705, 800);
    glVertex2f(705.0578997674662, 798.6824572007934);
    glVertex2f(703.6361866083765, 798.2559432530664);
    glVertex2f(700.8638459481516, 797.9716006212485);
    glVertex2f(695.1769933117929, 797.4740010155671);
    glVertex2f(688.8503697538438, 796.905317519312);
    glVertex2f(683.0213458015761, 796.1233735144318);
    glVertex2f(678.5429493504436, 796.2655448303408);
    glVertex2f(674.9175807947675, 796.905317519312);
    glVertex2f(666.5294731561359, 797.8294290353395);
    glEnd();




// plan wind design

    glBegin(GL_POLYGON);
    glColor3f(0.671, 0.671, 0.671);
    glVertex2f(441.4216157849391, 809.3729542745134);
    glVertex2f(441.4809973398804, 802.8409832309706);
    glVertex2f(442.609246883765, 799.8719054839056);
    glVertex2f(448.3692577130708, 797.6747879510776);
    glVertex2f(453.357038231897, 796.7246830720169);
    glVertex2f(459.117319574454, 795.7151966380147);
    glVertex2f(462.8583571187471, 794.9432364237779);
    glVertex2f(470.874867035822, 795.2995257534257);
    glVertex2f(474.1408525575934, 796.8434461818995);
    glVertex2f(477.4068380793646, 798.3279850554319);
    glVertex2f(474.2596156674759, 799.9906685937882);
    glVertex2f(469.9814437117026, 800.9407734728491);
    glVertex2f(465.1148562065163, 802.0096414617924);
    glVertex2f(460.1861871463887, 803.2566541155596);
    glVertex2f(455, 805);
    glVertex2f(450.4476121360161, 806.8789289669788);
    glVertex2f(444.9251275264756, 808.7197571701591);
    glEnd();



    glBegin(GL_POLYGON);
    glColor3f(1,0,0);
    glVertex2f(506.1250070054209, 799.8630725585685);
    glVertex2f(510.3203529302554, 803.8520899952966);
    glVertex2f(514.3781465296854, 808.6664213844512);
    glVertex2f(517.5418500139868, 811.7613487060505);
    glVertex2f(521.1182104745014, 815.1313806784586);
    glVertex2f(521.5996436134169, 809.2854068648771);
    glVertex2f(521.0494343117992, 804.47107455496165);
    glVertex2f(520.292896522075, 800.9634911618039);
    glVertex2f(519.8802395458619, 797.5246830266935);
    glVertex2f(519.0549255934353, 795.3238458202228);
    glVertex2f(518.2983878037111, 794.360979542392);
    glVertex2f(514.7220273431965, 794.2922033796987);
    glVertex2f(511.2832192080862, 794.6360841932008);
    glVertex2f(508.1195157237848, 794.9799650067118);
    glVertex2f(505, 795);
    glVertex2f(500.7604663146489, 796.4242644234582);
    glVertex2f(503.8274323375493, 798.2627341295972);
    glEnd();



//plan window
    if (isDay)
    {
        glBegin(GL_QUADS);
        glColor3f(0,0,0);
        glVertex2f(589.8033906326415,810.6707898109263);
        glVertex2f(592.5921566325294,810.22259527523);
        glVertex2f(592.5921566325294,806.2386438468186);
        glVertex2f(589.3551960969452,806.5374402039494);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(0,0,0);
        glVertex2f(584.0618460145364,811.6837635074519);
        glVertex2f(586.4398635338207,811.392577688764);
        glVertex2f(586.3913325640393,807.1218523480085);
        glVertex2f(583.7585944265667,807.4338241309542);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(0,0,0);
        glVertex2f(578.3093671158161,812.3278154723203);
        glVertex2f(580.6478339415123,812.0280120331284);
        glVertex2f(580.1381680948863,807.620901477008);
        glVertex2f(577.6198192056751,808.1905280114731);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(0,0,0);
        glVertex2f(572.0462336798289,813.5247139542698);
        glVertex2f(574.8203045596122,813.225967859524);
        glVertex2f(574.6069144919364,808.6594204112653);
        glVertex2f(571.6621315580127,808.7447764383355);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(0,0,0);
        glVertex2f(566,814);
        glVertex2f(568.5046634593994,813.7112862802352);
        glVertex2f(568.2838595102392,810.0312204609);
        glVertex2f(565.6342121203179,810.2520244100601);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(0,0,0);
        glVertex2f(560.3349173404754,814.9257080006158);
        glVertex2f(562.8373620976232,814.7785053678424);
        glVertex2f(562.395754199303,810.8040342829604);
        glVertex2f(559.9669107585419,810.9880375739272);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0,0,0);
        glVertex2f(554.2944453146142,815.9242985774034);
        glVertex2f(556.9281298652776,815.7693759567762);
        glVertex2f(556.6182846240231,811.7413878204674);
        glVertex2f(554,812);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(0,0,0);
        glVertex2f(548.4073857307784,816.7376423356966);
        glVertex2f(550.57630241956,816.4665277495989);
        glVertex2f(550.3439184886191,812.2061556823492);
        glVertex2f(547.9813485240534,812.7096541993877);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(0,0,0);
        glVertex2f(541.8231743541199,817.705908714617);
        glVertex2f(544.6892428357243,817.5509860939896);
        glVertex2f(544.5730508702537,813.1744220612695);
        glVertex2f(541.5907904231791,813.484267302524);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(0,0,0);
        glVertex2f(535.437931660551,818.1921337221296);
        glVertex2f(538.4253162382882,817.9120664179668);
        glVertex2f(535.5935246073082,814.1778356957952);
        glVertex2f(538.4564348276397,813.8977683916323);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0,0,0);
        glVertex2f(530.1166528814567,819.1256914026725);
        glVertex2f(532.9484445124367,818.8767426878611);
        glVertex2f(532.9484445124367,814.1778356957952);
        glVertex2f(529.6809926305367,814.3645472319038);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0,0,0);
        glVertex2f(511.6332298370522, 821.627082548115);
        glVertex2f(514.5893818702485, 821.285988175054);
        glVertex2f(514.5325320080716, 817.2497047604974);
        glVertex2f(511.1215882774606, 817.761346320089);
        glVertex2f(505.4935311219523, 822.6503656672984);
        glEnd();
    }
    else
    {
        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glVertex2f(589.8033906326415,810.6707898109263);
        glVertex2f(592.5921566325294,810.22259527523);
        glVertex2f(592.5921566325294,806.2386438468186);
        glVertex2f(589.3551960969452,806.5374402039494);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glVertex2f(584.0618460145364,811.6837635074519);
        glVertex2f(586.4398635338207,811.392577688764);
        glVertex2f(586.3913325640393,807.1218523480085);
        glVertex2f(583.7585944265667,807.4338241309542);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glVertex2f(578.3093671158161,812.3278154723203);
        glVertex2f(580.6478339415123,812.0280120331284);
        glVertex2f(580.1381680948863,807.620901477008);
        glVertex2f(577.6198192056751,808.1905280114731);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glVertex2f(572.0462336798289,813.5247139542698);
        glVertex2f(574.8203045596122,813.225967859524);
        glVertex2f(574.6069144919364,808.6594204112653);
        glVertex2f(571.6621315580127,808.7447764383355);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glVertex2f(566,814);
        glVertex2f(568.5046634593994,813.7112862802352);
        glVertex2f(568.2838595102392,810.0312204609);
        glVertex2f(565.6342121203179,810.2520244100601);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glVertex2f(560.3349173404754,814.9257080006158);
        glVertex2f(562.8373620976232,814.7785053678424);
        glVertex2f(562.395754199303,810.8040342829604);
        glVertex2f(559.9669107585419,810.9880375739272);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glVertex2f(554.2944453146142,815.9242985774034);
        glVertex2f(556.9281298652776,815.7693759567762);
        glVertex2f(556.6182846240231,811.7413878204674);
        glVertex2f(554,812);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glVertex2f(548.4073857307784,816.7376423356966);
        glVertex2f(550.57630241956,816.4665277495989);
        glVertex2f(550.3439184886191,812.2061556823492);
        glVertex2f(547.9813485240534,812.7096541993877);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glVertex2f(541.8231743541199,817.705908714617);
        glVertex2f(544.6892428357243,817.5509860939896);
        glVertex2f(544.5730508702537,813.1744220612695);
        glVertex2f(541.5907904231791,813.484267302524);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glVertex2f(535.437931660551,818.1921337221296);
        glVertex2f(538.4253162382882,817.9120664179668);
        glVertex2f(535.5935246073082,814.1778356957952);
        glVertex2f(538.4564348276397,813.8977683916323);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glVertex2f(530.1166528814567,819.1256914026725);
        glVertex2f(532.9484445124367,818.8767426878611);
        glVertex2f(532.9484445124367,814.1778356957952);
        glVertex2f(529.6809926305367,814.3645472319038);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glVertex2f(511.6332298370522, 821.627082548115);
        glVertex2f(514.5893818702485, 821.285988175054);
        glVertex2f(514.5325320080716, 817.2497047604974);
        glVertex2f(511.1215882774606, 817.761346320089);
        glVertex2f(505.4935311219523, 822.6503656672984);
        glEnd();
    }

































    glPopMatrix();
}

void restartPlaneMovement1 (int value)
{
    if (restartPlane1)
    {
        // Reset plane position to start again
        planex1 = 1200.0f;
        planey1 = 380.0f;
        isPlaneMoving1 = true;
        restartPlane1 = false; // Disable restart until it reaches target again
        // Restart movement
    }
}
void movePlane1 (int value)
{
    if (isPlaneMoving1 && !isStopped1)
    {
        // Calculate the direction vector to the target
        float dx = targetx1 - planex1;
        float dy = targety1 - planey1;
        float distance = sqrt(dx * dx + dy * dy);

        // Normalize the direction vector and scale by speed
        if (distance > planSpeed1)
        {
            planex1 += (dx / distance) * planSpeed1;
            planey1 += (dy / distance) * planSpeed1;
        }
        else
        {
            // Stop movement when target is reached
            planex1 = targetx1;
            planey1 = targety1;
            isPlaneMoving1 = false;
            restartPlane1 = true; // Enable restart after delay
            glutTimerFunc(15000, restartPlaneMovement1, 0); // Restart after 1 minute
        }

        glutPostRedisplay();
    }

    glutTimerFunc(30, movePlane1, 0); // Schedule next update
}







void people1 ()
{



    glBegin(GL_POLYGON);
    glColor3f(0,0,1);
    glVertex2f(395.1765581971542, 337.3743869844129);
    glVertex2f(395.9529433156438, 336.7205889898953);
    glVertex2f(396.9745026820776, 336.4754147419511);
    glVertex2f(398.01649323584, 336.4754147419511);
    glVertex2f(399.0871949769311, 336.4958459292798);
    glVertex2f(399.8757312827494, 336.4958459292798);
    glVertex2f(401.3264355830854, 335.3721306220227);
    glVertex2f(402.6339415721205, 334.4322960090835);
    glVertex2f(403.9415375611558, 333.390305455321);
    glVertex2f(404.7587850543027, 332.2257277775865);
    glVertex2f(404.615766743002, 331.1020124745093);
    glVertex2f(403.798519249855, 330.6116639786211);
    glVertex2f(402.0120059522603, 330.6729575406071);
    glVertex2f(399.8348690808921, 331.3880490971108);
    glVertex2f(398.8746031036444, 332.2870213395726);
    glVertex2f(397.6895942385812, 333.0634064580622);
    glVertex2f(396.4637229988608, 333.6559108905938);
    glVertex2f(395.5443195690704, 334.2892776977828);
    glVertex2f(394.4818978279793, 334.7387638190137);
    glVertex2f(393.7055127094896, 335.7398919981188);
    glVertex2f(393.7872374588043, 336.7410201772239);
    glVertex2f(394.6044849519513, 337.2926622350982);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex2f(396.9761539095137, 341.9944617668617);
    glVertex2f(397.9954668722228, 341.2531432485278);
    glVertex2f(399.0147798349319, 340.8593177856629);
    glVertex2f(399.9645941865471, 340.5349909338918);
    glVertex2f(400.8680761307665, 340.3728275080063);
    glVertex2f(400.4047520568079, 339.4693455637869);
    glVertex2f(400.010926593943, 338.9828552861303);
    glVertex2f(399.9645941865471, 338.2647029714943);
    glVertex2f(400.0572590013388, 337.5928830642541);
    glVertex2f(400.1047145564056, 337.1558207380537);
    glVertex2f(399.5315950997032, 336.4945290572432);
    glVertex2f(398.6608943866361, 336.4504429451891);
    glVertex2f(397.6028276973393, 336.4504429451891);
    glVertex2f(396.5227179520156, 336.6267873934053);
    glVertex2f(395.6630387666962, 337.056629859321);
    glVertex2f(395.0237901421785, 337.7620047787966);
    glVertex2f(394.990725558138, 338.8641575801474);
    glVertex2f(395.2001345903946, 339.4593200928769);
    glVertex2f(395.5307804307999, 340.0103964935523);
    glVertex2f(395.8504047431916, 340.3851284460116);
    glVertex2f(396.0818568314753, 340.8480326225789);
    glVertex2f(396.3133089197589, 341.2227645750382);
    glVertex2f(396.6219117041371, 341.6305611115379);
    glVertex2f(396.8181802151104, 341.851026501355);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.604, 0.498, 0.408);
    glVertex2f(396.8342987615646, 342.5936263615296 );
    glVertex2f(396.6620684367644, 343.6516126425555 );
    glVertex2f(396.7358814330971, 344.586577262997);
    glVertex2f(396.9696225882074, 345.4969375513216);
    glVertex2f(397.3878962341944, 346.185858805943);
    glVertex2f(397.0184105193708, 348.338968062309);
    glVertex2f(397.1728139270687, 350.8094231293964);
    glVertex2f(398.2536377809535, 353.17694204743);
    glVertex2f(400, 355);
    glVertex2f(400.3282972933164, 356.4766043528841);
    glVertex2f(400.9994038706644, 357.7549025954519);
    glVertex2f(401.3825600064484, 359.7274958882496);
    glVertex2f(400.9949984719712, 361.6354911349067);
    glVertex2f(400.667061788952, 362.9472378669835);
    glVertex2f(400.8799287433822, 365.4176709097542);
    glVertex2f(402, 368);
    glVertex2f(403.5393888237251, 369.243560849897);
    glVertex2f(405.4523337937964, 371.2964774031444);
    glVertex2f(406.8520496255558, 373.5360227339596);

    glVertex2f(407.7385363190035, 376.3354543974788);
    glVertex2f(408.4389342348832, 379.2282004497819);
    glVertex2f(408.6659785580789, 383.0585424967098);
    glVertex2f(409.9970336583379, 386.4812556116618);
    glVertex2f(412.2788424016391, 389.1433658121801);
    glVertex2f(414.1803496877234, 391.9005513770026);
    glVertex2f(413.5148221375939, 397.2247717780392);
    glVertex2f(412.4689931302476, 403.119444364901);
    glVertex2f(411.8985409444222, 408.5387401302418);
    glVertex2f(412.7542192231602, 415.003864902929);
    glVertex2f(414.1803496877234, 420.4231606682698);
    glVertex2f(415.127979610113, 423.6936859184129);
    glVertex2f(415.8440005913179, 425.43880123409);
    glVertex2f(419.1974383139764, 425.3110494915887);
    glVertex2f(422.693249184201, 425.0623088226222);
    glVertex2f(426.2924574863237, 425.1713757444682);
    glVertex2f(430, 425);
    glVertex2f(432.727405662846, 425.1713757444682);
    glVertex2f(435, 425);
    glVertex2f(437.2536827700608, 425.2804426627143);
    glVertex2f(439.3259542167374, 425.6076434174528);
    glVertex2f(440, 425);
    glVertex2f(440.961579904296, 422.3901693291913);
    glVertex2f(440.8528910721835, 419.8270967504068);
    glVertex2f(440.525690317445, 416.0097546117916);
    glVertex2f(440.3620899400758, 413.0104143600225);
    glVertex2f(440, 410);
    glVertex2f(440.2530230218297, 407.2844011520997);
    glVertex2f(440, 405);
    glVertex2f(439.2168872984913, 402.3218563718999);
    glVertex2f(437.7990173612915, 400.4131853025923);
    glVertex2f(436.5447478014609, 398.8862484471462);
    glVertex2f(434.6360767321534, 396.432247866078);
    glVertex2f(433.4363406314459, 394.4690382581771);
    glVertex2f(432.6183387445998, 392.7239675662387);
    glVertex2f(432.2911379898614, 389.3974265597312);
    glVertex2f(432.1326271165488, 387.334460710302);
    glVertex2f(432, 384);
    glVertex2f(432.1326271165488, 382.6787385847593);
    glVertex2f(432.2796463003257, 380.7184828010663);
    glVertex2f(431.6425631706255, 379.1502781741119);
    glVertex2f(430.4174033058175, 377.876119147115);
    glVertex2f(428.8491986788632, 377.1410159958266);
    glVertex2f(427.4770196302782, 375.6218177634646);
    glVertex2f(426.49848719967, 373.8388505237903);
    glVertex2f(426, 372);
    glVertex2f(425.5099282664313, 370.2376715527063);
    glVertex2f(424.7685900665023, 368.295893624159);
    glVertex2f(424.0623955427604, 366.6717982578094);
    glVertex2f(422.9679195809605, 364.7652917437061);
    glVertex2f(421.8210118005817, 363.012895084977);
    glVertex2f(421.1576347589511, 361.3289379792994);
    glVertex2f(420.3411707077133, 359.0836618383954);
    glVertex2f(419.0144166244519, 358.0120527711457);
    glVertex2f(416.8711984899528, 356.6342696846819);
    glVertex2f(415, 355);
    glVertex2f(412.4827042145499, 354.4400225469802);
    glVertex2f(411.0028631261814, 353.4704714861354);
    glVertex2f(409.6250800352177, 353.0112104573411);
    glVertex2f(408.2983259519563, 350.4597602971959);
    glVertex2f(407.4987725278411, 349.4026186940247);
    glVertex2f(407.3918712993615, 348.0841702094431);
    glVertex2f(407.2137025852289, 346.801355467688);
    glVertex2f(406.3941265002188, 345.8392444113717);
    glVertex2f(405.325114215423, 345.1622032976677);
    glVertex2f(404.5768056160659, 344.8771333550554);
    glVertex2f(403.436525845617, 344.5564296696167);
    glVertex2f(403.2853159772933, 343.8543145973274);
    glVertex2f(403.2053460084699, 343.1185908841523);
    glVertex2f(402.9654361019998, 342.4308491522713);
    glVertex2f(402.6775442142358, 341.7431074230903);
    glVertex2f(402.3736663058672, 341.4040464056989);
    glVertex2f(402.2226497200432, 341.1997298484075);
    glVertex2f(402, 341);
    glVertex2f(401.6896500053701, 340.7999800624027);
    glVertex2f(401.458634623452, 340.6134301622671);
    glVertex2f(401.2543669050538, 340.4624135764431);
    glVertex2f(400.5253939616673, 340.3735802906642);
    glVertex2f(399.5843011324116, 340.6400801480007);
    glVertex2f(398.7315015889347, 340.9243466624931);
    glVertex2f(397.7010354739001, 341.4129297342768);
    glVertex2f(397.3101690164732, 341.6971962487691);
    glVertex2f(396.8837692447348, 342.3900958778442);

    glEnd();


//manus body

    glBegin(GL_POLYGON);
    glColor3f(0.110, 0.137, 0.380);
    glVertex2f(415.0604473655696, 425.7902488058568);
    glVertex2f(413.4179374228254, 426.6839674961736);
    glVertex2f(411.7029638061366, 427.4086042356198);
    glVertex2f(410.157020953185, 428.954495946438);
    glVertex2f(409.5773627037617, 430.5486967732194);
    glVertex2f(409.456589913854, 432.6984524335762);
    glVertex2f(409.7947537255955, 434.8482080939328);
    glVertex2f(410.5199304650415, 436.9013455223634);
    glVertex2f(410.8350415002152, 438.6743474545399);
    glVertex2f(410.6459858016873, 440.3758487412916);
    glVertex2f(409.8897630075755, 442.2664057265712);
    glVertex2f(409.2469736325805, 444.4972629692012);
    glVertex2f(408.6419953972911, 446.87936477706535);
    glVertex2f(408.8738479203422, 450.0978890993234);
    glVertex2f(409.6348547758673, 452.8882475605824);
    glVertex2f(410.7002643736024, 455.323469498263);
    glVertex2f(410.8603099710947, 458.5737007498742);
    glVertex2f(410.6190835259613, 461.6493379253242);
    glVertex2f(410.920616582378, 464.7852817120576);
    glVertex2f(411.5155601763254, 467.7137526351182);
    glVertex2f(412.7451001803381, 470.3332074262759);
    glVertex2f(414.1350149674827, 472.6319126511693);
    glVertex2f(415.6853045377595, 474.2356604824903);
    glVertex2f(417.3425106301244, 475.6790335306793);
    glVertex2f(419.0531749835332, 476.908753354692);
    glVertex2f(420.2654472797895, 478.341824112983);
    glVertex2f(420.8898172569637, 480.145596025976);
    glVertex2f(421.6058348000606, 481.8514043525826);
    glVertex2f(422.8516959652897, 483.5104780818913);
    glVertex2f(424.0339921073532, 484.3059200534671);
    glVertex2f(425.5337290264235, 484.5181469759771);
    glVertex2f(427.1890990220012, 484.3625138994698);
    glVertex2f(428.0238582505403, 483.8107239009438);
    glVertex2f(429.1859142608082, 483.0271921690837);
    glVertex2f(430.4413098937462, 482.1682372623366);
    glVertex2f(432.3133911007589, 480.8467681750334);
    glVertex2f(434, 480);
    glVertex2f(435.5509903646515, 478.9086135136553);
    glVertex2f(437.3790226020875, 477.5651199415636);
    glVertex2f(438.788596285441, 476.507944671721);
    glVertex2f(440.0865145472424, 475.781414278352);
    glVertex2f(441.030902598276, 474.8215444559899);
    glVertex2f(441.5572828234423, 473.5520392070592);
    glVertex2f(441.7430640793834, 472.4683152140697);
    glVertex2f(441.6966187653981, 471.415554763737);
    glVertex2f(441.4024651101581, 470.5795391120022);
    glVertex2f(440.8606031136634, 469.6815963749538);
    glVertex2f(440.2413326025626, 468.6597994672779);
    glVertex2f(440.117478089892, 468.2108280987537);
    glVertex2f(440.480608872855, 467.292890705607);
    glVertex2f(441.0419006949477, 465.546649646272);
    glVertex2f(441.6031925170404, 463.925139938004);
    glVertex2f(442, 462);
    glVertex2f(442.3827644921692, 460.3702917314163);
    glVertex2f(442.4139473711743, 458.2186730800607);
    glVertex2f(442.4139473711743, 456.9401750408493);
    glVertex2f(442.4139473711743, 455.4433968486019);
    glVertex2f(442.6631404032156, 453.7907042612386);
    glVertex2f(442.7498833818537, 452.7505204712188);
    glVertex2f(442.8552586011407, 451.7495033879925);
    glVertex2f(443.3030820331103, 450.5377458661923);
    glVertex2f(443.9879884584755, 449.536728782966);
    glVertex2f(444.9099778772364, 449.0625627961746);
    glVertex2f(445.8583098508191, 448.6410819190267);
    glVertex2f(446.8593269340452, 448.3249712611658);
    glVertex2f(448.1764546751322, 448.2722861515223);
    glVertex2f(449.2564994228235, 448.1932584870571);
    glVertex2f(450.4682569446236, 447.7454350550875);
    glVertex2f(451.4165881928062, 447.5083520616918);
    glVertex2f(452.154180453215, 447.1922414038308);
    glVertex2f(453.0470400852315, 447.1778532054011);
    glVertex2f(453.8809753322099, 447.3817040355513);
    glVertex2f(454.4739959522834, 447.307576460422);
    glVertex2f(455.0855484667342, 447.233448888533);
    glVertex2f(455.8205785149571, 446.4818029618548);
    glVertex2f(456.2679384756346, 445.6243630372227);
    glVertex2f(456.6034584461428, 444.3568431486361);
    glVertex2f(456.6034584461428, 443.1638832534958);
    glVertex2f(456.6034584461428, 442.2691633321406);
    glVertex2f(456.0343116784564, 441.2866411955257);
    glVertex2f(455.3213300689058, 440.573659585975);
    glVertex2f(454.510141279226, 439.6467834935591);
    glVertex2f(453.9666650107597, 438.5416619987555);
    glVertex2f(452.8971925964338, 437.6504349868172);
    glVertex2f(452.0059655844956, 436.6522607334462);
    glVertex2f(450.8785475215047, 435.6571135025509);
    glVertex2f(450, 435);
    glVertex2f(448.5733095624757, 434.1395316659179);
    glVertex2f(446.8987365013637, 433.7208884006398);
    glVertex2f(445.2241634402517, 433.7208884006398);
    glVertex2f(444.0728944607373, 433.1452539108825);
    glVertex2f(443.9158603630489, 432.2768374379703);
    glVertex2f(443.8614289493593, 430.9704835094212);
    glVertex2f(443.7707092654535, 430.0814370885252);
    glVertex2f(443.4804090535326, 428.7025079390234);
    glVertex2f(443.2263957896481, 427.7408862971747);
    glVertex2f(442.5913626299368, 426.7611208507629);
    glVertex2f(442, 426);
    glVertex2f(441.5121256634793, 425.4778305598111);
    glVertex2f(440.8546832188778, 425.1229108065086);
    glVertex2f(440.4147248892826, 424.8953001516895);
    glVertex2f(439.6507203974675, 425.2694494969437);
    glVertex2f(438.6809683801764, 425.6665059449684);
    glVertex2f(438.093019409063, 425.5137919264973);
    glVertex2f(436.506295140975, 425.4330005237934);
    glVertex2f(434.1096441731407, 425.2332796098071);
    glVertex2f(432.0942785865529, 425.2332796098071);
    glVertex2f(428.8079617291438, 425.1969667163551);
    glVertex2f(424.2738669794573, 425.211063808292);
    glVertex2f(421.0445586857945, 425.247970188791);
    glVertex2f(417.6860780603852, 425.4140489010365);
    glVertex2f(416.802786005634, 425.3277015766689);
    glVertex2f(415.4630904583639, 425.5063276496382);
    glEnd();



//manuser bam pa

    glBegin(GL_POLYGON);
    glColor3f(0.518, 0.404, 0.349);
    glVertex2f(429.5454843109036, 377.0442716530293 );
    glVertex2f(429.6656883200539, 375.2011435127243 );
    glVertex2f(430.1264703551301, 373.4381513785196);
    glVertex2f(430.7274904008817, 371.4748192290643);
    glVertex2f(431.5288504618837, 369.9522351131602);
    glVertex2f(432.530505381363, 368.2693789850556);
    glVertex2f(433.3902126037135, 366.6869286457653);
    glVertex2f(434.027536664767, 365.7380580354233);
    glVertex2f(434.7795594338321, 364.0939788728199);
    glVertex2f(435.3360169965592, 362.3487256079025);
    glVertex2f(435.1842558430882, 360.5781788174065);
    glVertex2f(434.9566141128816, 358.6305773478609);
    glVertex2f(434.8750425600848, 357.4170665489961);
    glVertex2f(435.0699206123984, 355.6631604781735);
    glVertex2f(435.6155791588765, 353.6754079445746);
    glVertex2f(436.6289450309072, 352.5451152411556);
    glVertex2f(437.3305060192361, 351.1030176540348);
    glVertex2f(438.2659206703414, 349.8168225087649);
    glVertex2f(439.1233841005212, 348.7644810262714);
    glVertex2f(439.6300670365365, 347.7121395437778);
    glVertex2f(440.6824085190299, 346.0751639043434);
    glVertex2f(440.6824085190299, 344.9058955904617);
    glVertex2f(441.1890914550452, 343.8925297184309);
    glVertex2f(441.9680630664296, 342.8401882359373);
    glVertex2f(442.4752866006315, 341.4370662529793);
    glVertex2f(443.2547988095694, 340.1898467244721);
    glVertex2f(443.722506135122, 339.0205784105904);
    glVertex2f(444.5020183443763, 338.6697979164259);
    glVertex2f(445.7882134896461, 338.513895744575);
    glVertex2f(447.0744086349158, 338.6697979164259);
    glVertex2f(448.7503598848127, 339.5272613466058);
    glVertex2f(449.257042820828, 341.0083345441893);
    glVertex2f(449.1011403789772, 343.3858467824155);
    glVertex2f(449.2960184312908, 345.256678046262);
    glVertex2f(450.0365550300824, 348.257798090256);
    glVertex2f(450.5432379660978, 351.2978957063484);
    glVertex2f(450.7770916288741, 353.7143835550373);
    glVertex2f(449.7637257568434, 356.3257494560398);
    glVertex2f(448.5554818324991, 358.9371153570423);
    glVertex2f(447.3862135186175, 361.7823349208211);
    glVertex2f(446.5677256989005, 363.9649691067337);
    glVertex2f(446.6398100213703, 366.9581293844358);
    glVertex2f(446.3766489808304, 369.1511386599885);
    glVertex2f(446.5520896503482, 371.1687071934971);
    glVertex2f(446.5520896503482, 373.6248775821162);
    glVertex2f(446, 376);
    glVertex2f(445.148563719946, 377.8793155766885);
    glVertex2f(444.7924617087672, 379.6300564501809);
    glVertex2f(444.451982012286, 380.9676552577857);
    glVertex2f(444.3060621423655, 382.8889335450727);
    glVertex2f(444.3547020990056, 384.5426920708387);
    glVertex2f(444.9870215353278, 386.0018977004393);
    glVertex2f(445.0401707028609, 387.4148826092554);
    glVertex2f(445.3526734447718, 389.0121188456894);
    glVertex2f(445.2137833372558, 390.9565803509134);
    glVertex2f(445.3526734447718, 392.8663193292584);
    glVertex2f(445.4568410254088, 395.6093989526995);
    glVertex2f(445.4568410254088, 398.4219236298985);
    glVertex2f(445.1443382834978, 401.0955819955815);
    glVertex2f(444.6235003803129, 403.3872449735956);
    glVertex2f(444.2762751115229, 405.4358740594566);
    glVertex2f(443.998494896491, 406.8247751346166);
    glVertex2f(443.8128984123392, 408.8676742244025);
    glVertex2f(443.5880231532817, 410.6104574820991);
    glVertex2f(443.4755855237528, 412.6624442209999);
    glVertex2f(443.2493547250299, 413.8401851335254);
    glVertex2f(443.2235030568602, 415.1899952327278);
    glVertex2f(443.1825997205208, 416.9283870271551);
    glVertex2f(443.2235030568602, 418.155487117339);
    glVertex2f(442.9576313706538, 419.5871038892203);
    glVertex2f(442.7531146889564, 420.9573656565924);
    glVertex2f(442.405436330071, 422.3889824284736);
    glVertex2f(442, 424);
    glVertex2f(441.7514528351222, 424.5539836195797);
    glVertex2f(441.4776233111285, 425.0833873659675);
    glVertex2f(441.2950702951328, 425.0377491119685);
    glVertex2f(441.2037937871348, 424.7821748895744);
    glVertex2f(441.1672831839357, 424.325792349585);
    glVertex2f(441.1216449299367, 423.9241757143942);
    glVertex2f(441.066879025138, 423.4404102220053);
    glVertex2f(441, 423);
    glVertex2f(441, 422);
    glVertex2f(440.970288385878, 421.3444966738541);
    glVertex2f(441.0352426248703, 420.6693864495303);
    glVertex2f(440.7804840496538, 419.2682142858395);
    glVertex2f(440.6239152323632, 417.8952185008967);
    glVertex2f(440.3341260505239, 414.9780074010081);
    glVertex2f(440.5727479691216, 411.8902576192699);
    glVertex2f(440.2276509446956, 409.0598265474745);
    glVertex2f(439.6856126310262, 404.0220586910169);
    glVertex2f(438.8247282504924, 401.7582516162796);
    glVertex2f(437.4218055562893, 400.1002520685847);
    glVertex2f(436, 398);
    glVertex2f(432.5370838119274, 391.6922812853709);
    glVertex2f(431.9490072102406, 386.3898562116274);
    glVertex2f(432.441092330739, 381.8105296186749);
    glVertex2f(431.1422827376752, 378.3589021538375);
    glVertex2f(430.1267320597475, 377.3238124476809);
    glVertex2f(429.8527526328679, 377.2159777235342);
    glEnd();

//manus ar hudi

    glBegin(GL_POLYGON);
    glColor3f(0.671, 0.671, 0.671);
    glVertex2f(427.6710580430315, 485.756692365297);
    glVertex2f(427.7138157585665, 488.0656090041882);
    glVertex2f(427.6283003274965, 491.0158913761046);
    glVertex2f(428.4834546381968, 493.8379006014159);
    glVertex2f(429.4668820955021, 496.403363533172);
    glVertex2f(430.7923712770875, 498.2847030170581);
    glVertex2f(432.6737107606281, 500.3798310782741);
    glVertex2f(434.9398696839839, 501.9618665530699);
    glVertex2f(437.9756674869699, 502.8597785793053);
    glVertex2f(440.9687075744209, 503.2018403035855);
    glVertex2f(443.1493510667067, 502.7742631482353);
    glVertex2f(445.1589636968524, 502.0473819841399);
    glVertex2f(446.6127260250428, 501.2349853889745);
    glVertex2f(448.4513077930484, 500.0805270695299);
    glVertex2f(450.3326472765891, 499.0115841811535);
    glVertex2f(452.3850176222698, 497.7716104306379);
    glVertex2f(453.8815376659953, 496.7026675422623);
    glVertex2f(453.0900182385049, 495.037541873019);
    glVertex2f(452.7746922828331, 493.9204191368162);
    glVertex2f(452.2701852406771, 492.8032964006134);
    glVertex2f(451.3692798082557, 491.037521753067);
    glVertex2f(450.7206278969122, 489.8483265822705);
    glVertex2f(449.6035051607096, 488.2266968039116);
    glVertex2f(448.2701651207259, 486.1365962006935);
    glVertex2f(447.1170061672265, 484.2987491185534);
    glVertex2f(445.8917747791333, 482.3527933845227);
    glVertex2f(444.702579608337, 480.983471272419);
    glVertex2f(443.7296017413218, 479.9383668256328);
    glVertex2f(442.8286963089004, 478.6410630029457);
    glVertex2f(441.3872476170261, 477.3797953975554);
    glVertex2f(440.792670074976, 476.8059868830096);
    glVertex2f(439.5409195700929, 476.1923836943413);
    glVertex2f(438.0928160448358, 477.0268840390932);
    glVertex2f(436.4729036267517, 478.1804580256267);
    glVertex2f(434.6566381882938, 479.5058409131503);
    glVertex2f(433.3557994283171, 480.3894295048327);
    glVertex2f(431.3368381302853, 481.5350759826821);
    glVertex2f(429.8998960830564, 482.583466558898);
    glVertex2f(428.7666176627167, 483.3249635234644);
    glEnd();


//tupi

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(452.7799864084729, 493.9363003553277);
    glVertex2f(453.4772029450664, 493.3419518323299);
    glVertex2f(454, 492);
    glVertex2f(454.4651165013628, 491.0102387420852);
    glVertex2f(454.4861151126144, 489.6429881312795);
    glVertex2f(454.4861151126144, 488.5912568921982);
    glVertex2f(454.4651165013628, 487.413317904427);
    glVertex2f(454.4651165013628, 486.8033137857598);
    glVertex2f(454.4651165013628, 486.0881365431845);
    glVertex2f(455.1282146301255, 485.1893771978821);
    glVertex2f(455.8870151015609, 484.3016715076342);
    glVertex2f(457.0200588525209, 483.2409496982247);
    glVertex2f(457.9602440926792, 482.3730863996169);
    glVertex2f(458.7075708220359, 481.6016523564099);
    glVertex2f(459.3102536682912, 481.0953987655554);
    glVertex2f(460, 480);
    glVertex2f(460.0571200897542, 479.4403766018189);
    glVertex2f(459.7604960504841, 479.1013776997959);
    glVertex2f(459.2096228346967, 478.8047536605257);
    glVertex2f(458.5033751221488, 479.0307529285411);
    glVertex2f(457.5711281415855, 479.5816261443285);
    glVertex2f(456.4270068472579, 480.1042494516141);
    glVertex2f(455.1557609646716, 481.0506213864284);
    glVertex2f(454.0540145330968, 481.7992439617293);
    glVertex2f(452.9522681015221, 482.5761164455321);
    glVertex2f(451.4832728594224, 483.6637379223856);
    glVertex2f(450.5086510161062, 484.4123604981569);
    glVertex2f(449.6470288067978, 485.0056085766972);
    glVertex2f(448.9266561399988, 485.5282318839827);
    glVertex2f(448.3757829242115, 485.8389808775038);
    glVertex2f(448.4887825582192, 486.841852629322);
    glVertex2f(448.9213253538131, 487.8576751543631);
    glVertex2f(450.1062265872697, 489.258012975721);
    glVertex2f(451.1187785504052, 490.8307000674013);
    glVertex2f(452, 492);
    glVertex2f(451.6760870112561,491.6884846309964);
    glEnd();



//muk

    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex2f(448.4830813525535, 485.5724839931337);
    glVertex2f(449.3540373527321, 485.0867585314957);
    glVertex2f(449.9737560451668, 484.7182771468047);
    glVertex2f(450.5599764299023, 484.1153076082196);
    glVertex2f(450.4427323529552, 483.2945990695897);
    glVertex2f(450, 482);
    glVertex2f(449.5424818017543, 480.927763085593);
    glVertex2f(449.0295526886226, 479.9275513149861);
    glVertex2f(448.0549873736724, 478.8504001774095);
    glVertex2f(447.0034826917525, 477.7732490398328);
    glVertex2f(446.1315031994286, 477.1577341040748);
    glVertex2f(445.3108166184179, 476.9012694575089);
    glVertex2f(444.3362513034678, 476.6191585352864);
    glVertex2f(443.1565143432649, 476.6191585352864);
    glVertex2f(442.2588883952844, 476.7986387248826);
    glVertex2f(441.7349376648458, 477.2582003849078);
    glVertex2f(442, 478);
    glVertex2f(443.366984842992, 479.5261100999944);
    glVertex2f(444.2359969768101, 480.7342489201806);
    glVertex2f(445.253770359143, 481.7728243971828);
    glVertex2f(446.5462975276925, 483.4260669932273);
    glVertex2f(447.7544363478787, 485.1217004250677);
    glEnd();

//angul

    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex2f(464, 448);
    glVertex2f(463.5681527214005, 447.1507134596121);
    glVertex2f(462.4923449708329, 446.6273475269035);
    glVertex2f(461.2420819093623, 446.1621333644958);
    glVertex2f(460, 446);
    glVertex2f(459.1486181785279, 446.0167539387434);
    glVertex2f(458, 446);
    glVertex2f(457.1714579882954, 446.0749057090443);
    glVertex2f(456.1141239314809, 446.239412243099);
    glVertex2f(455.7815974439277, 447.0337810744762);
    glVertex2f(456.7422295190813, 447.7357814370885);
    glVertex2f(457.3703351066818, 447.920518374618);
    glVertex2f(458.2201250193177, 448.3084659434301);
    glVertex2f(459.1622834007183, 448.5855713497244);
    glVertex2f(459.8088268280717, 448.770308287254);
    glVertex2f(459.6425994382951, 448.4193081059478);
    glVertex2f(459.1523360132124, 448.1976237890124);
    glVertex2f(458.9405990756829, 447.7173077433355);
    glVertex2f(459.5502309695304, 447.3847812557823);
    glVertex2f(460.4554419634251, 447.4217286432883);
    glVertex2f(461.3052318760601, 447.5510444995589);
    glVertex2f(462.0811270136851, 447.8281499058533);
    glVertex2f(463, 448);
    glEnd();

//mobile
    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(460.4716775532771, 448.8346135487304);
    glVertex2f(461.6300808960011, 449.2266885262678);
    glVertex2f(463.0201649072699, 449.7791578127977);
    glVertex2f(464.0538171207775, 450.2425191498874);
    glVertex2f(464.9805397949567, 450.6524157173128);
    glVertex2f(465.5864738511507, 450.991025925186);
    glVertex2f(466.3706238062255, 451.4543872622757);
    glVertex2f(467.101308991636, 451.7038895207085);
    glVertex2f(467.7250646377182, 451.828640649925);
    glVertex2f(468.2418907444719, 451.7395327004846);
    glVertex2f(468.4557498231287, 451.2405281836189);
    glVertex2f(468.4557498231287, 450.9197395656337);
    glVertex2f(467.9567453062629, 450.705880486977);
    glVertex2f(467.136921741421, 450.3316270993277);
    glVertex2f(465.4617227219343, 449.6365850936932);
    glVertex2f(464.2142114297701, 449.1197589869394);
    glVertex2f(463.0558080870461, 448.6563976498497);
    glVertex2f(461.6479024858892, 448.2108579026482);
    glVertex2f(460.8102877611503, 448.1217499532079);
    glEnd();


//juta

    glBegin(GL_POLYGON);
    glColor3f(0,0,1);

    glVertex2f(445.9023141021365, 333.6566029641134);
    glVertex2f(445.5478110294079, 332.5424504498234);
    glVertex2f(446.2821388229172, 331.1750814550131);
    glVertex2f(447.4469346333111, 330.8205783822845);
    glVertex2f(449.4220231813703, 331.3016896952733);
    glVertex2f(451.477550255336, 331.5042628796896);
    glVertex2f(453.498085177489, 331.4536195835856);
    glVertex2f(455.3219671774959, 332.1879473770948);
    glVertex2f(456.9678743008786, 333.3020998913847);
    glVertex2f(457.4996289099715, 334.4415740537267);
    glVertex2f(457.0691608930868, 335.3784750316523);
    glVertex2f(455.1193939930796, 335.884907926932);
    glVertex2f(452.6885157800836, 336.03683788010055);
    glVertex2f(450.6627839359203, 336.8089430485371);
    glVertex2f(449.8271695502029, 335.3278317355482);
    glVertex2f(448.6876953878611, 334.4668957017788);
    glVertex2f(447.4469346333111, 334.11239262290501);

    glEnd();

//pa


    glBegin(GL_POLYGON);
    glColor3f(1,1,1);

    glVertex2f(449.4220231813703, 331.3016896952733);
    glVertex2f(451.477550255336, 331.5042628796896);
    glVertex2f(453.498085177489, 331.4536195835856);
    glVertex2f(455.3219671774959, 332.1879473770948);
    glVertex2f(456.9678743008786, 333.3020998913847);
    glVertex2f(457.4996289099715, 334.4415740537267);
    glVertex2f(457.0691608930868, 335.3784750316523);
    glVertex2f(455.1193939930796, 335.884907926932);
    glVertex2f(452.6885157800836, 336.03683788010055);
    glVertex2f(450.6627839359203, 336.8089430485371);
    glVertex2f(449.8271695502029, 335.3278317355482);
    glVertex2f(448.6876953878611, 334.4668957017788);
    glVertex2f(447.4469346333111, 334.11239262290501);
    glVertex2f(445.77163189693, 333.9964666546567);
    glVertex2f(445.4970368657567, 334.50620826534);
    glVertex2f(445.1710960958674, 335.1943054462174);
    glVertex2f(444.84515153259781, 336.5704998079723);
    glVertex2f(444.5373223766382, 337.9648019902767);
    glVertex2f(445.2978508397133, 338.4356053245613);
    glVertex2f(446.4205357137764, 338.5623600684071);
    glVertex2f(447.83294571663, 338.9788399410435);
    glVertex2f(448.4074831403754, 339.5091107353347);
    glVertex2f(449.0935759087721, 339.3869492900284);
    glVertex2f(449.4060819316444, 338.8869396534328);
    glVertex2f(449.4529578350752, 338.3400541134063);
    glVertex2f(449.6560867499422, 337.8556697779543);
    glVertex2f(449.7654638579475, 337.3244095390714);
    glVertex2f(449.8592156648091, 336.7931493001885);
    glVertex2f(449.9685927728144, 336.449392675029);
    glVertex2f(450, 336);
    glVertex2f(449.5779602442241, 335.121240778218);
    glVertex2f(448.1873084424425, 334.386852924072);
    glVertex2f(446.7497807372301, 333.8868432874763);


    glEnd();


// hand color

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(424.1826989821821, 453.2764711273802);
    glVertex2f(421.7243060631408, 456.6198854972764);
    glVertex2f(420, 460);
    glVertex2f(419.1184095689571, 463.7492249624962);
    glVertex2f(419.6592560111462, 467.5351500578198);
    glVertex2f(421.47846677712367, 470.2885501271461);
    glVertex2f(423.8876918318971, 471.7144180201901);
    glVertex2f(426.5919240428426, 472.2060966039983);
    glVertex2f(429.6894991208346, 472.2552644623792);
    glVertex2f(432.0987241814951, 469.6493679681954);
    glVertex2f(433.7212635080623, 466.7484643237266);
    glVertex2f(435.3438028346295, 462.7166999364989);
    glVertex2f(435.9829849935803, 460.6024820261233);
    glVertex2f(437.2613493114818, 457.7507462400354);
    glVertex2f(438.490547710024, 455.7348604464215);
    glVertex2f(439.8672458056655, 453.374806844418);
    glVertex2f(441.3422815570903, 451.555960840512);
    glVertex2f(442.276470866326, 450.0805603326264);
    glVertex2f(443.35908440472, 449.9446026442857);
    glVertex2f(444.3612624625192, 449.1270363339759);
    glVertex2f(445.3370674135341, 448.7050666254289);
    glVertex2f(446.2601261509806, 448.4149624508029);
    glVertex2f(447.7291081988599, 448.2830969168827);
    glVertex2f(450, 448);
    glVertex2f(450.9109124810756, 447.5837111622242);
    glVertex2f(451.7575322603644, 447.2594737999434);
    glVertex2f(452.6581916000334, 447.1874210527698);
    glVertex2f(453.5832196524123, 447.169732067914);
    glVertex2f(454.7400169721363, 447.2296751386777);
    glVertex2f(456, 446);
    glVertex2f(456.33291758942, 445.229333516562);
    glVertex2f(456.617747711064, 443.9816331557097);
    glVertex2f(456.4447566877352, 441.8931827280211);
    glVertex2f(455.1256989608648, 440.2790726148771);
    glVertex2f(454.0843375975462, 439.3071353424464);
    glVertex2f(452.5828875899335, 437.2860030749487);
    glVertex2f(451.601190331413, 436.2086422773544);
    glVertex2f(449.624855185371, 434.7685220934169);
    glVertex2f(448, 434);
    glVertex2f(446.283726283827, 433.9448096668928);
    glVertex2f(444.2335503779938, 434.3728683725063);
    glVertex2f(442.4762567444225, 435.0262211337059);
    glVertex2f(440.7158873591429, 435.3421618393409);
    glVertex2f(438.8273373079206, 436.4867376279605);
    glVertex2f(435.8514402575097, 438.5469740474758);
    glVertex2f(432.9900087859607, 439.0620331523546);
    glVertex2f(430.8153067875835, 439.9204649938193);
    glVertex2f(428.3544688420514, 442.0951589921966);
    glVertex2f(427.3243506322938, 445.013872531765);
    glVertex2f(426.4086900013981, 448.1041818824495);
    glVertex2f(425.7219445282264,450.2788758808267);
    glVertex2f(424.9207414761926,452.396341089773);

    glEnd();



//lagguge

    glBegin(GL_POLYGON);
    glColor3f(0.671, 0.671, 0.671);
    glVertex2f(357.0534570057614, 346.7751393456613);
    glVertex2f(363.3192238834108, 358.7756759079393);
    glVertex2f(370, 370);
    glVertex2f(375.4259598842992, 380.2279625059938);
    glVertex2f(380.2374700635618, 388.8147678155962);
    glVertex2f(382.5235237102413, 392.8970064703811);
    glVertex2f(384.5630686205216, 396.031124714104);
    glVertex2f(387.0692836151948, 397.9598924023141);
    glVertex2f(389.896802245696, 396.223910482925);
    glVertex2f(395.6161193662595, 392.9465524129678);
    glVertex2f(399.6646205115007, 390.7616470329963);
    glVertex2f(401.9137871444125, 388.8337893447862);
    glVertex2f(401.0141280932478, 385.2993835830676);
    glVertex2f(397.4154532085889, 379.1302389807951);
    glVertex2f(392.2125621543864, 369.1053871809889);
    glVertex2f(385.4807405192646, 356.9038952164403);
    glVertex2f(381.062922946216, 348.2787026214404);
    glVertex2f(376.9606971998136, 342.3883271907087);
    glVertex2f(373.910324208899, 337.6549897910136);
    glVertex2f(364.1280935828627,342.2831419151599);

    glEnd();



//chaka
    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(368.6200904674786, 339.2879491691519);
    glVertex2f(367.3322612356337, 337.3340013691114);
    glVertex2f(367.4654849492728, 335.4688693781636);
    glVertex2f(368.6644983720249, 334.3142638599578);
    glVertex2f(370.5296303629727, 334.8915666190607);
    glVertex2f(371.7730516902712, 336.4458432781839);
    glVertex2f(372.0886900264297, 337.4292809758158);
    glVertex2f(370.9639653068753, 338.0565313001828);
    glVertex2f(369.9041285519105, 338.8135575537291);

    glEnd();


//lati

    glBegin(GL_LINES);
    glColor3f(0,0,0);
    glLineWidth(5);
    glVertex2f(411.1723462960277, 409.9745869162112);
    glVertex2f(398.8141102917914, 390.773028043179);
    glEnd();









}


void bench1 ()
{
    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(154.7531086300433,304.2504936674857);
    glVertex2f(159.2418445495244,302.7542483609921);
    glVertex2f(165.4138564388109,271.8941889145602);
    glVertex2f(160.2393414205202,272.3305937956209);
    glEnd();





    glBegin(GL_QUADS);
    glColor3f(0.30f, 0.62f, 0.87f);
    glVertex2f(156.9991154140825,304.1034559251623);
    glVertex2f(219.1629195431286,304.5779887811092);
    glVertex2f(226.339346146869,262.1203582409945);
    glVertex2f(168.5900911891872,247.7176147224712);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(180.0588611636935, 268.48434342818506);
    glVertex2f(185.8226964302216, 268.48434342818506);
    glVertex2f(191.3018978564274, 268.6257512020118);
    glVertex2f(195.6425639134346, 267.5583743008029);
    glVertex2f(198.2754269443256, 265.9928881790299);
    glVertex2f(200.3390222866628, 262.00801444145167);
    glVertex2f(200.8371315072272, 258.5924083306482);
    glVertex2f(199.9120715216793, 255.9595430766663);
    glVertex2f(198.5600607846484, 253.75363304561679);
    glVertex2f(197.0657331329555, 250.9784531020247);
    glVertex2f(195.0021378078613, 249.1994916000009);
    glVertex2f(192.5115916777975, 247.7763223938938);
    glVertex2f(190.2345209552184, 246.0685193564638);
    glVertex2f(187.3881825519947, 244.9298939951743);
    glVertex2f(185, 245);

    glEnd();

    glPopMatrix();

}

void timer(int value) {
    currentTime += 0.05f; // Increment time (adjust speed here)
    if (currentTime > totalTime) {
        currentTime = 0.0f; // Reset time to loop the animation
    }
    glutPostRedisplay(); // Request a redraw
    glutTimerFunc(50, timer, 0); // Call timer again after 50ms
}


void bench2()
{
    glBegin(GL_QUADS);
    glColor3f(0.30f, 0.62f, 0.87f);
    glVertex2f(66.5399860659356,304.7055273026064);
    glVertex2f(129.1164489060051,304.7055273026064);
    glVertex2f(139.4589476254055,244.8244152317421);
    glVertex2f(81.6191753753134,243.509874953331);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(65.7941146578029,304.3631003974246);
    glVertex2f(70.1528996735235,302.8470012615218);
    glVertex2f(82.8637695570692,236.2013553652963);
    glVertex2f(77.6153503591312,236.4929342096262);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(139.9607683460978,275.6643541401145);
    glVertex2f(172.3298126472704,271.0402049542328);
    glVertex2f(135.5468077595742,271.5656764526285);
    glVertex2f(129.030961179468,304.0398150534798);
    glVertex2f(134.1805818637455,303.0939663563676);
    glEnd();


    //briecase

    glBegin(GL_POLYGON);

    glColor3f(1,0,0);
    glVertex2f(98.1328679119075, 270.7965425624324);
    glVertex2f(172.3667087754926,270.644271453267);
    glVertex2f(179.8447019166377,268.3628498169855);
    glVertex2f(180.351684502478,253.6603548276158);
    glVertex2f(177.0562976945158,249.9847310802734);
    glVertex2f(100,250);
    glVertex2f(97.007243120384,254.7204771655915);
    glVertex2f(96.9002528983832,268.7912391656492);

    glEnd();


//line

    glBegin(GL_LINES);
    glColor3f(0,0,0);
    glLineWidth(2);
    glVertex2f(97.3512148531289,256.4326010681217);
    glVertex2f(179.7318982035264,255.8197964452093);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);

    glVertex2f(81.8222027788316, 238.7947806767805);
    glVertex2f(85.5871706550716, 236.6150624334416);
    glVertex2f(90.7392319594, 235.6242841433785);
    glVertex2f(123.236849417474, 235.0298128013407);
    glVertex2f(123.8486091601094,225.6937829273802);
    glVertex2f(88.1632013072358, 226.3109398247852);
    glVertex2f(82.0203589884424, 230.0759077100251);
    glVertex2f(78.8498597186422, 235.2279690053533);
    glVertex2f(77.6690300199874, 238.9767216867509);

    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.467, 0.478, 0.506);
    glVertex2f(94.5438372318332,250.5180762214076);
    glVertex2f(183.5866589090341,250.5180762214076);
    glVertex2f(184.1214506308191,231.3992721675948);
    glVertex2f(94.410139301387,231.8003659589335);
    glEnd();


    glBegin(GL_LINES);
    glColor3f(0,0,0);
    glLineWidth(2);
    glVertex2f(94.3673559636441,241.9199623144098);
    glVertex2f(184.4757501465016,241.7581878185698);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.302, 0.314, 0.341);
    glVertex2f(124.6306694283129,231.3504538779596);
    glVertex2f(184.897476835559,231.4590427201348);
    glVertex2f(188.1073592608796,230.0785261856902);
    glVertex2f(188.7040490611842,226.2000424837099);
    glVertex2f(123.8637574280757,226.0011458836083);
    glEnd();




//leg

    glBegin(GL_QUADS);
    glColor3f(0.467, 0.478, 0.506);
    glVertex2f(101.9139960909799,226.0474458338571);
    glVertex2f(102.2406167122089,166.9291133914122);
    glVertex2f(108.9363394474032,167.0924237020267);
    glVertex2f(108.2830982049452,226.2107561444716);
    glEnd();


//rod

    glBegin(GL_POLYGON);
    glColor3f(0.467, 0.478, 0.506);
    glVertex2f(108.9166538769798,196.2783902005841);
    glVertex2f(511.072084207151,195.6776527332123);
    glVertex2f(511.2773296220812,187.3994209976919);
    glVertex2f(108.7035784249414,187.222115495791);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.467, 0.478, 0.506);
    glVertex2f(101.7576107759218,173.86805944574);
    glVertex2f(80.0687454603265,166.3098185024268);
    glVertex2f(130.3474786919337,166.0907390547945);
    glVertex2f(130,170);
    glVertex2f(109.5349311668676,173.86805944574);
    glEnd();


}
void bench3()
{
    glBegin(GL_QUADS);
    glColor3f(0.30f, 0.62f, 0.87f);
    glVertex2f(246.1697162501264,304.2976673202491);
    glVertex2f(310.2911458176188,303.271821603052);
    glVertex2f(321.4990915525086,248.7518143841832);
    glVertex2f(257.6309367159316,243.4813656521873);
    glEnd();



    glBegin(GL_QUADS);
    glColor3f(0.30f, 0.62f, 0.87f);
    glVertex2f(263.9642042474256,237.0197079040162);
    glVertex2f(303.5580382473523,230.7170159611709);
    glVertex2f(334.9098904758657,230.8786234468849);
    glVertex2f(323.5973664758866,236.0500629897323);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(268.3971077060638,232.7824370773749);
    glVertex2f(267.8271475122579,235.7861190968594);
    glVertex2f(302.0929959007945,230.7122713638714);
    glVertex2f(302.3710149546568,226.3334712655393);
    glVertex2f(277.6968239243719,226.2639665020737);
    glVertex2f(277.6273191609063,230.7122713638714);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.467, 0.478, 0.506);
    glVertex2f(301.4574553640455,231.0375971693266);
    glVertex2f(526.1764367173276,230.9722593338487);
    glVertex2f(526.3772829442813,225.7502574330553);
    glVertex2f(301.462147397162,225.7431260023923);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(243.9247228827226,304.4980320973855);
    glVertex2f(248.830880449809,302.9337499745463);
    glVertex2f(258.7247881804792,244.4321485169203);
    glVertex2f(253.646769448419,247.4789597561564);
    glEnd();
}

void bench4()
{
    glBegin(GL_POLYGON);
    glColor3f(0.30f, 0.62f, 0.87f);
    glVertex2f(334.7215088461149,304.3538213921802);
    glVertex2f(397.4542318330305,303.6976213609364);
    glVertex2f(408.2159123454302,243.983418517746);
    glVertex2f(353.6200697459389,243.7209385052485);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(333.8175025403845, 303.8466121059258);
    glVertex2f(335, 305);
    glVertex2f(336.359059265141, 303.6287689585433);
    glVertex2f(337.9565223406527, 302.1038669268656);
    glVertex2f(338.3922086354177, 300.4337361302663);
    glVertex2f(338.755280547722, 298.110758915194);
    glVertex2f(338.755280547722, 296.5851738598418);
    glVertex2f(338.755280547722, 294.9876574457033);
    glVertex2f(336.9399209862008, 296.5851738598418);
    glVertex2f(336.0685483966707, 298.5457621862844);
    glVertex2f(335, 300);
    glVertex2f(334.3984176000712, 302.2490956917873);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(396.1883319216977,304.5196700784205);
    glVertex2f(401.3082673073417,302.8680780185354);
    glVertex2f(413.8603669624689,236.6392364171442);
    glVertex2f(409.4836480037732,236.3089180051672);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.30f, 0.62f, 0.87f);
    glVertex2f(375.3258394182908,236.4194842068583);
    glVertex2f(409.0148318541271,236.5232703900417);
    glVertex2f(417.7541522653343,236.3335363686002);
    glVertex2f(453.3423351452414,230.4541046762541);
    glVertex2f(391.9058819803256,230.5432717023163);
    glVertex2f(377.239866752489,232.1028634526724);
    glEnd();



    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(421.8680743113625,304.8820359814201);
    glVertex2f(426.7860882830874,302.3112559507458);
    glVertex2f(438.1869388539042,238.1535282287018);
    glVertex2f(434.2748822854867,237.0357977805825);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.30f, 0.62f, 0.87f);
    glVertex2f(424.4373545701604,303.8931874568941);
    glVertex2f(488.8601001480227,304.0201776983924);
    glVertex2f(500.35315766794,245.9488662968171);
    glVertex2f(436.220095545617,243.3542769278276);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.30f, 0.62f, 0.87f);
    glVertex2f(437.435585689151,237.1323921179477);
    glVertex2f(518.8984160843368,237.1181945724683);
    glVertex2f(527.1933437127111,230.9617999392572);
    glVertex2f(463.0052030864258,231.9468917551235);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(437.1309734301853,236.9149686968194);
    glVertex2f(478.7870342581588,230.0988331644757);
    glVertex2f(478.4641040552637,225.739275425392);
    glVertex2f(456.7470479105675,226.2236707297346);
    glVertex2f(456.4241177076723,231.2290888746086);
    glVertex2f(435.4641608218328,233.9914204097121);

    glEnd();



    glBegin(GL_QUADS);
    glColor3f(0.467, 0.478, 0.506);
    glVertex2f(305.4182919105238,226.4949172374516);
    glVertex2f(311.143154005742,226.7030940409141);
    glVertex2f(311.7676844161295,166.4359094385273);
    glVertex2f(305.6264687139862,166.6440862419897);
    glEnd();



    glBegin(GL_POLYGON);
    glColor3f(0.302, 0.314, 0.341);
    glVertex2f(312.4167896385724,173.8555615539393);
    glVertex2f(335.8823811770719,170.0264482903349);
    glVertex2f(335.9805635684464,166.0009702439816);
    glVertex2f(312.9077015954447,165.9027878526071);
    glVertex2f(283.1158800393041,165.7587962959098);
    glVertex2f(282.5614026381789,169.1965561828858);
    glVertex2f(304.4078122425112,173.9650618325622);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.467, 0.478, 0.506);
    glVertex2f(507.4855035911312,226.4237112768016);
    glVertex2f(514.6715198206628,226.3059077320552);
    glVertex2f(514.7893233654092,166.4617070008762);
    glVertex2f(507.721110680624,166.697314090369);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.302, 0.314, 0.341);
    glVertex2f(514.3787466029481,174.0959500932408);
    glVertex2f(537.4974294332402,169.8599181460757);
    glVertex2f(537.641023736534,165.7674805022043);
    glVertex2f(485.5162916409066,166.1264662604386);
    glVertex2f(506.8400456800269,173.8805586383002);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.349, 0.333, 0.463);
    glVertex2f(561.3709211271704,263.6843916508146);
    glVertex2f(560.9774692306335,181.7152465389562);
    glVertex2f(563.2070299776761,178.0430288379449);
    glVertex2f(604.1260272175176,177.2561250448711);
    glVertex2f(608.7162993437819,180.2725895849875);
    glVertex2f(608.4539980794239,262.8974878577407);
    glVertex2f(605.6998348036653,266.700856190931);
    glVertex2f(563.7143551175739,266.3717937101746);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.169, 0.169, 0.227);
    glVertex2f(563.7371388478766,266.6565133652881);
    glVertex2f(551.1293613137441,267.0580349428082);
    glVertex2f(547.0338412230386,264.4079925311754);
    glVertex2f(546.8956112242898,181.6199943036826);
    glVertex2f(547.5569703617651,179.3052373225192);
    glVertex2f(549.7063875585599,177.3211599100933);
    glVertex2f(561.6908483451745,177.2591418111944);
    glVertex2f(561.271598822586,266.9352503256221);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.251, 0.294, 0.471);
    glVertex2f(565,240);
    glVertex2f(565.1458369690879,184.2585296756452);
    glVertex2f(566.1936408180944,181.5913926054469);
    glVertex2f(567.7177191439222,180.5435887564404);
    glVertex2f(601.1521874167677,180.2578240703477);
    glVertex2f(603.8193244869661,181.6866475008111);
    glVertex2f(605.6291674988865,184.2585296756452);
    glVertex2f(605.3434028127938,238.8395847193475);
    glVertex2f(604.3908538591515,240.8399375219963);
    glVertex2f(602.2952461611384,243.3165648014662);
    glVertex2f(569.1465425743856,242.9355452200093);
    glVertex2f(566.7691395860627,241.9194882610084);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(569.7046188059645,236.6910318256949);
    glVertex2f(569.7939882269899,231.686344248276);
    glVertex2f(601.3413938489363,231.5969748272506);
    glVertex2f(601.0732855858603,236.5122929836442);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(565.8901142964758,261.6387221594669);
    glVertex2f(565.9618473316191,256.5456766642908);
    glVertex2f(605.1280845198776,256.2587445237175);
    glVertex2f(605.0563514847343,261.4952560891803);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(560.6478102974957, 177.5410342595916);
    glVertex2f(560.7659264006651, 174.7952263623326);
    glVertex2f(560.6330123487803, 173.0673436878308);
    glVertex2f(560, 172);
    glVertex2f(559.3481765138944, 170.9850235416364);
    glVertex2f(558.3291687827779, 170.4090626501358);
    glVertex2f(556.6898954761992, 170.497672018059);
    glVertex2f(555.2721455894284, 171.0736329095595);
    glVertex2f(554, 172);
    glVertex2f(553.6328722828498, 173.6433045793314);
    glVertex2f(553.5442629149265, 175.2382732019484);
    glVertex2f(553.6771769668113, 176.5674137207959);
    glVertex2f(554, 178);
    glVertex2f(556, 178);
    glVertex2f(558.7722156223938, 178.1628324344129);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(595.3253513666799, 177.7087085263182);
    glVertex2f(596, 176);
    glVertex2f(596.3936822572027, 174.7886040922228);
    glVertex2f(596.4292932868867, 173.3641629048592);
    glVertex2f(596, 172);
    glVertex2f(595.4321844557321, 171.2631121534978);
    glVertex2f(594.6843528323662, 170.4440584707637);
    glVertex2f(593.6160219418434, 170.159170233291);
    glVertex2f(592.298413843532, 170.2660033223433);
    glVertex2f(591.2656939826933, 170.8001687676047);
    glVertex2f(590, 172);
    glVertex2f(589.4495314688046, 173.4709959939115);
    glVertex2f(589.1646432313319, 175.1091033593796);
    glVertex2f(589.6631976469091, 176.4979335170592);
    glVertex2f(590.2685851515387, 177.9223747044228);
    glVertex2f(592.4052469352843, 178.1004298528432);


    glEnd();

    glBegin(GL_LINES);
    glLineWidth(100);
    glColor3f(0,0,0);
    glVertex2f(567.2214901640107,266.9218260515252);
    glVertex2f(566.8522876599967,280.2746499466963);
    glVertex2f(587.5276278847791,280.4592511987033);
    glVertex2f(587.8352966381241,267.1679610542012);
    glEnd();


    glBegin(GL_LINES);
    glLineWidth(100);
    glColor3f(0,0,0);
    glVertex2f(567.8368276707007,280.0285149440203);
    glVertex2f(586.9122903780892,280.2131161960273);
    glEnd();

}





void sitting_girl()
{

    glBegin(GL_POLYGON);
    glColor3f(0.106, 0.090, 0.239);
    glVertex2f(205.951450162603, 204.5375755799563);
    glVertex2f(207.3973112964861, 201.06750888586367);
    glVertex2f(208.4383313128819, 199.1589721619109);
    glVertex2f(210.4047024549629, 197.8287799187384);
    glVertex2f(212.1397358156225, 197.6552765826724);
    glVertex2f(214.7422858566121, 199.2746410526216);
    glVertex2f(217.2870014522462, 200.951839967926);
    glVertex2f(219.4847103757485, 202.1085288750326);
    glVertex2f(222.4342670888699, 203.785727790337);
    glVertex2f(224.8633137937935, 207.0244567302353);
    glVertex2f(225.9621682555446, 210.6101923422656);
    glVertex2f(227.0610227172957, 215.5839546428237);
    glVertex2f(228.9695594140214, 219.7480347084072);
    glVertex2f(233.017970588894, 222.1770814133309);
    glVertex2f(236.3723684195027, 223.6807769925694);
    glVertex2f(240.2472762583093, 225.7049825800059);
    glVertex2f(242.2136474003902, 228.3075326209956);
    glVertex2f(243.9486807610499, 232.5294471319344);
    glVertex2f(244.5357174399486, 237.2773450827541);
    glVertex2f(245.0714661508548, 241.2336432555999);
    glVertex2f(246.5962894049723, 245.1899414284458);
    glVertex2f(248, 248);
    glVertex2f(249.2074366576692, 249.698896607399);
    glVertex2f(249.7456852913452, 250.237145241075);
    glVertex2f(250.4234798670852, 250.8351992784927);
    glVertex2f(249.8551390152364, 251.8220417648927);
    glVertex2f(247.7165671474163, 253.0101372470151);
    glVertex2f(244.5361269337352, 254.5820789618231);
    glVertex2f(240.9718404873684, 256.318526204925);
    glVertex2f(237.3527188649036, 257.945330905831);
    glVertex2f(234.1411003469792, 259.4305534988237);
    glVertex2f(228.8923058105063, 261.3611445926989);
    glVertex2f(224.910461679389, 262.9297498564725);
    glVertex2f(221.4112653217404, 264.5586860919298);
    glVertex2f(218.2137238225097, 266.1272913557033);
    glVertex2f(217.7272333612999, 268.8903276721889);
    glVertex2f(218.0071610641203, 272.3427693403074);
    glVertex2f(217.9138518298468, 275.9818294769728);
    glVertex2f(217.0740687213856, 278.1279418652626);
    glVertex2f(217.6339241270264, 281.6736927676546);
    glVertex2f(218.2870887669407, 284.8462067329526);
    glVertex2f(217.7272333612999, 287.8321022297037);
    glVertex2f(216.6075225500183, 291.5644716006426);
    glVertex2f(215, 295);
    glVertex2f(213.6216270532674, 298.3760457026061);
    glVertex2f(212.5982195803155, 300.689544890079);
    glVertex2f(212.6750164425595, 303.5694368245096);
    glVertex2f(212.8286101671556, 306.0269364174711);
    glVertex2f(212.9822038917156, 307.6780689564921);
    glVertex2f(213.4045866342559, 309.3292014955131);
    glVertex2f(213.814214274061, 310.2019034993255);
    glVertex2f(213, 311);
    glVertex2f(211.9220097765864, 311.4402813364118);
    glVertex2f(211.1593157807117, 311.8025609844524);
    glVertex2f(210.1868809359714, 312.1076385828023);
    glVertex2f(209.3860522403029, 312.4508508809459);
    glVertex2f(208.9093684928812, 312.6415243799146);
    glVertex2f(208.485305386114, 311.6899019152697);
    glVertex2f(208.485305386114, 309.4565485176362);
    glVertex2f(208.3539316568415, 307.4421513354569);
    glVertex2f(208.0911841982964, 305.2963804240051);
    glVertex2f(207.609480524297, 302.6251145954631);
    glVertex2f(206.6898644193891, 300.0852224961937);
    glVertex2f(206, 298);
    glVertex2f(205.0695884250276, 296.1440168180169);
    glVertex2f(204.2813460493923, 295.0492295407456);
    glVertex2f(203.5368494168478, 294.6551083529279);
    glVertex2f(202.6610700550308, 294.7426908391096);
    glVertex2f(200.7780466021243, 296.2315931041986);
    glVertex2f(199.1577706077628, 297.8080778554693);
    glVertex2f(196.7930434808568, 300.3917611978296);
    glVertex2f(194.8662287848594, 302.5813233523723);
    glVertex2f(192.7642491164985, 304.7708855069149);
    glVertex2f(190.9688081497736, 306.4787439874582);
    glVertex2f(189.1733671830487, 308.62451489891);
    glVertex2f(187.4217174594147, 310.5951208379983);
    glVertex2f(185.5386940065081, 312.478144290905);
    glVertex2f(183.3720601557699, 312.5493703729163);
    glVertex2f(182.0208453243128, 312.303694949015);
    glVertex2f(180.3420632609873, 311.566668677311);
    glVertex2f(179.0317943335137, 310.7477505976401);
    glVertex2f(178, 310);
    glVertex2f(177.1073368462869, 309.1508603422815);
    glVertex2f(177.0254450383198, 308.3728881665941);
    glVertex2f(178.7451730056289, 307.0216733351369);
    glVertex2f(180.301173570037, 305.2609994638442);
    glVertex2f(181.9389535163457, 303.3774878806008);
    glVertex2f(183.0854388278851, 301.4530303933739);
    glVertex2f(184.4775995633258, 299.078167962328);
    glVertex2f(185.419355349474, 297.440331802986);
    glVertex2f(185.9516521067335, 295.5158743157591);
    glVertex2f(186, 294);
    glVertex2f(185.7469225868158, 292.6496610369105);
    glVertex2f(184.8461126991777, 290.9708789735848);
    glVertex2f(183.8634110035725, 289.0464214863579);
    glVertex2f(182.91777241252, 287.2803512132803);
    glVertex2f(182.16618535962, 284.3591784704859);
    glVertex2f(181.6658460657687, 282.0639713154332);
    glVertex2f(181.331997523065, 280.5199228656704);
    glVertex2f(181.6614864234799, 278.1920604558288);
    glVertex2f(183.1874155460661, 275.1400222106564);
    glVertex2f(183.9503801073591, 273.4871123278547);
    glVertex2f(184.3954427681134, 271.5161205445143);
    glVertex2f(184.6497642885444, 269.1000661004195);
    glVertex2f(184.5861839084367, 267.1926546971868);
    glVertex2f(185, 265);
    glVertex2f(184.8588323092987, 263.3289699564639);
    glVertex2f(184.0588035309467, 261.6673717245019);
    glVertex2f(183.3203154278525, 259.6365294409928);
    glVertex2f(182.5818273247583, 257.2979837811943);
    glVertex2f(182.0279612474376, 255.0209787966538);
    glVertex2f(181.7202578711484, 253.0516771884025);
    glVertex2f(181.7202578711484, 251.7593230079876);
    glVertex2f(184.1203442062045, 250.0977247760256);
    glVertex2f(185.2280763608458, 248.8669112708685);
    glVertex2f(185.5973204123929, 245.728336832718);
    glVertex2f(185.4773053180675, 243.5867648396352);
    glVertex2f(185.6752397937161, 241.9373108758965);

    glVertex2f(185, 240);
    glVertex2f(185.7412179522657, 237.5827524116263);
    glVertex2f(185, 235);
    glVertex2f(185.0154582082207, 233.6240628986534);
    glVertex2f(184.8835018911216, 232.1725434105634);
    glVertex2f(186.3350213792116, 231.3800855079687);
    glVertex2f(187.8525190258511, 230.5890676053742);
    glVertex2f(188.2483879771484, 229.3354825929328);
    glVertex2f(188.2483879771484, 227.8839631048427);
    glVertex2f(188.5782787698961, 226.8283125680499);
    glVertex2f(190, 225);
    glVertex2f(191.8112085388239, 224.189186226068);
    glVertex2f(193.9225096124094, 222.341977866806);
    glVertex2f(195.769980517966, 220.0985403959959);
    glVertex2f(198.2110899181298, 217.5917303711131);
    glVertex2f(200, 215);
    glVertex2f(201.5759760041566, 211.5873579431042);
    glVertex2f(204.0171678704899,208.0905155399781);




    glEnd();

// pa

    glBegin(GL_POLYGON);
    glColor3f(0.992, 0.761, 0.710);
    glVertex2f(285.7507619879793, 167.4388619007231);
    glVertex2f(287.7598588185749, 169.2087805372002);
    glVertex2f(289.8646269268179, 170.6916853407351);
    glVertex2f(290.7256684256446, 172.7964534489782);
    glVertex2f(290.5343258703497, 173.801001864276);
    glVertex2f(289.0035854279912, 173.5139880313337);
    glVertex2f(287.5206806244564, 173.4183167536863);
    glVertex2f(285.798597626803, 174.3271938913368);
    glVertex2f(282.5936098256148, 176.5276332772272);
    glVertex2f(277.8100459432443, 180.4023200219474);
    glVertex2f(271.8466719105596, 186.0812306010661);
    glVertex2f(265.3486656715938, 193.3396418254429);
    glVertex2f(258.8506594326281, 201.4967134871235);
    glVertex2f(254.2882295201628, 207.78733654825);
    glVertex2f(250.3479491412154, 212.4880219126083);
    glVertex2f(246.0620301325359, 218.5021340699491);
    glVertex2f(243.073189090827, 222.2613368569309);
    glVertex2f(240.434461006124, 225.4597913905244);
    glVertex2f(237.6358163837182, 224.180409577087);
    glVertex2f(232.8303350995005, 222.489906952927);
    glVertex2f(230.6915850184578, 221.1500508854827);
    glVertex2f(229.3516452086478, 219.6812707093449);
    glVertex2f(227.6188144393623, 217.1751843590074);
    glVertex2f(226.6174420836294, 214.5716162340993);
    glVertex2f(226, 212);
    glVertex2f(226, 210);
    glVertex2f(232.1314068349664, 206.0021386921651);
    glVertex2f(237.9036180798747, 200.4465322948697);
    glVertex2f(240.643551214623, 195.9523791439069);
    glVertex2f(245, 190);
    glVertex2f(249.501138344255, 185.8698065601769);
    glVertex2f(255.3433766637995, 182.2890798488198);
    glVertex2f(260.9609740339473, 179.0917315889301);
    glVertex2f(266.4593222207659, 176.8923923142027);
    glVertex2f(271.0779346976936, 175.1329208944208);
    glVertex2f(274.2303209914696, 173.3734494746388);
    glVertex2f(277.3093959760881, 171.6872893640145);
    glVertex2f(279.9261183880237, 170.426384805941);
    glVertex2f(281.9447044103926, 169.549188743912);
    glVertex2f(283.348938165084, 168.8909541714004);
    glVertex2f(284.5776427004389, 168.1888372940547);
    glEnd();


//juta



//pa 2

    glBegin(GL_POLYGON);
    glColor3f(0.992, 0.761, 0.710);
    glVertex2f(243.5029624399393, 230.4013004960312);
    glVertex2f(249.3113422592615, 229.7311028245709);
    glVertex2f(252.9974294522929, 227.5715769943101);
    glVertex2f(253.3309187426916, 221.4226076813855);
    glVertex2f(253.3809596743749, 216.5387694199829);
    glVertex2f(253.3809596743749, 213.1084544506644);
    glVertex2f(253.4725111658441, 209.6070150219116);
    glVertex2f(255.3149097999209, 206.8012624087842);
    glVertex2f(256.9692946700547, 204.7608544022858);
    glVertex2f(260.7192337090248, 200.0734306035734);
    glVertex2f(262.7596417155231, 197.2609763243459);
    glVertex2f(264.3037342609814, 195.0551298308342);
    glVertex2f(267.1224077303888, 191.9417710528834);
    glVertex2f(269.0172962530818, 189.4513461373439);
    glVertex2f(270.3166483829285, 187.5023179425739);
    glVertex2f(273.1568636533601, 184.6997801894456);
    glVertex2f(274.5968764442985, 183.2597673985074);
    glVertex2f(274.7847041996382, 186.514484910634);
    glVertex2f(273.28208215692, 191.9624533959169);
    glVertex2f(272.3429433802211, 197.7851138114499);
    glVertex2f(271.2785860999624, 207.677375592678);
    glVertex2f(269.7759640572442, 217.6948558774659);
    glVertex2f(268.9497021548937, 225.1599737636078);
    glVertex2f(268.3052481667999, 232.3410324880816);
    glVertex2f(266.4639510579605, 237.7728589591579);
    glVertex2f(263.7020053947013, 241.8237125986047);
    glVertex2f(259.4670220443705, 245.9666310934934);
    glVertex2f(254.7717414168298, 249.3730307448464);
    glVertex2f(253.140044725367, 250.0422086093703);
    glVertex2f(251.5181456705106, 250.4400329058445);
    glVertex2f(249.1924036295844, 249.3383656233005);
    glVertex2f(247.295087754092, 246.033367756686);
    glVertex2f(246.1016148646693, 242.8201675349153);
    glVertex2f(244.9693457131658, 239.331554473526);
    glVertex2f(244.5715214166915, 235.3839133777435);
    glVertex2f(244, 232);
    glVertex2f(243.3541758321791, 229.8915278470308);
    glVertex2f(246.5629632127054, 229.8597576749464);
    glEnd();



//dan hat

    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex2f(181.0172154138902, 279.8946264303543);
    glVertex2f(184.0153486102201, 278.7632554128713);
    glVertex2f(187.4660302135431, 277.7450214971366);
    glVertex2f(190.6338690624954, 276.5005133779053);
    glVertex2f(193.0097481992096, 275.3691423604223);
    glVertex2f(196.0078813955349, 274.0114971394427);
    glVertex2f(198.327119813795, 272.1447349605957);
    glVertex2f(199.7979743041073, 270.6739526378678);
    glVertex2f(200.3636598128488, 269.3728759677624);
    glVertex2f(200.3070912619746, 267.7889565432862);
    glVertex2f(198.7797403883726, 266.4877897831807);
    glVertex2f(196.9129782095258, 266.6575855258031);
    glVertex2f(194.5370990728115, 267.9020936450345);
    glVertex2f(191.5955344273559, 268.2415049502794);
    glVertex2f(188.2579899257812, 268.3546420520277);
    glVertex2f(185.8821107890669, 268.4112106029018);
    glVertex2f(184.4113284663391, 268.1283678485311);
    glVertex2f(182.2617235331215, 267.9020936450345);
    glVertex2f(180.3383928034004, 267.9020936450345);
    glVertex2f(179.0373161332951, 269.7688558238814);
    glVertex2f(175.9260458352169, 271.0699324939869);
    glVertex2f(172.9516080261235, 271.9650901198357);
    glVertex2f(170.6232701777177, 272.2884703766338);
    glVertex2f(168.5536365336692, 272.3531464279935);
    glVertex2f(167.1954394551168, 273.7113435065457);
    glVertex2f(166.8073831469599, 276.8157939718079);
    glVertex2f(167.0014113010379, 280.0495965397893);
    glVertex2f(167.3894676091957, 283.6067793645689);
    glVertex2f(167.9715520714323, 286.711229829831);
    glVertex2f(168.7476646877478, 289.8803563464528);
    glVertex2f(169.7824815095019, 292.5967505035573);
    glVertex2f(170.9466504339751, 295.4424967633809);
    glVertex2f(171.0760025366944, 298.2235669718449);
    glVertex2f(171.3993827934925, 301.1986653343878);
    glVertex2f(172.3695235638869, 303.9797355428519);
    glVertex2f(173.6630445910794, 306.5021015458774);
    glVertex2f(175.1153376305524, 308.0444160499127);
    glVertex2f(176.3107605702498, 309.3145529233412);
    glVertex2f(177.6556113774094, 308.3806287517026);
    glVertex2f(178.6642494827791, 307.5587754806606);
    glVertex2f(180.121171905354, 305.7282841042488);
    glVertex2f(181.1671662627706, 304.4955041976858);
    glVertex2f(182.5493740367958, 302.627655844084);
    glVertex2f(183.7447969764932, 300.6477366105345);
    glVertex2f(184.5299232806697, 299.1161009690471);
    glVertex2f(185.1270047505184, 298.0327489299463);
    glVertex2f(185.5752883529049, 297.1735386920387);
    glVertex2f(186, 296);
    glVertex2f(186.0235719552915, 295.3056903487614);
    glVertex2f(186, 294);
    glVertex2f(185.7994301540982, 292.9895584030975);
    glVertex2f(185.4258604854427, 291.8688493971311);
    glVertex2f(184.9775768830562, 291.2337809604168);
    glVertex2f(184.3798654132075, 290.2624998219126);
    glVertex2f(183.7447969764932, 288.8802920478873);
    glVertex2f(183.1844424735101, 287.6848691081899);
    glVertex2f(182.698801904258, 286.0038055992403);
    glVertex2f(182.2505183018714, 285.1072383944672);
    glVertex2f(181.876948633216, 283.6876736535764);
    glVertex2f(181.4286650308295, 282.0813240783579);



    glEnd();


    //finger

    glBegin(GL_POLYGON);
    glColor3f(0.992, 0.761, 0.710);
    glVertex2f(198.6449788437922, 265.565058664423);
    glVertex2f(199.2293920527366, 264.6592181905593);
    glVertex2f(200.1060118661531, 263.2566264890928);
    glVertex2f(200.3397771497309, 262.7014339405956);
    glVertex2f(200.6319873542031, 261.6787108249429);
    glVertex2f(200.8073077168864, 260.0423583898986);
    glVertex2f(201.0702936609114, 259.3118373287182);
    glVertex2f(201.7131481907502, 258.8735274220099);
    glVertex2f(202.5313266832723, 258.8735274220099);
    glVertex2f(203.2326225340055, 259.7793678958737);
    glVertex2f(203.7293737616082, 260.8313116719735);
    glVertex2f(203.9339183847388, 262.2923446943345);
    glVertex2f(204, 264);
    glVertex2f(203.4371671571361, 265.4189553621869);
    glVertex2f(202.8527539481917, 266.5877817800757);
    glVertex2f(202.0345754556696, 267.69816687707);
    glVertex2f(201.5086035676196, 268.3410214069089);
    glVertex2f(200.6612044146503, 268.1949181046728);
    glVertex2f(200, 268);
    glVertex2f(199.4339366758671, 267.4351809330451);
    glVertex2f(198.9079647878172, 267.2014156494673);
    glVertex2f(198.4988755415561, 266.8799883845479);

    glEnd();


//matha

    glBegin(GL_POLYGON);
    glColor3f(1,0,0);
    glVertex2f(174.3828127423555, 308.0238723128756);
    glVertex2f(174.4639266799921, 311.9173413194362);
    glVertex2f(175.8834205886341, 314.9185570119934);
    glVertex2f(177.7490411542777, 316.8247345464553);
    glVertex2f(179.330762938193, 318.3253423927339);
    glVertex2f(180.2635732210148, 321.2860011164727);
    glVertex2f(180.6285859403799, 325.2605840606701);
    glVertex2f(180.8950949998868, 328.7058616961263);
    glVertex2f(182.6092562425089, 331.3888896410999);
    glVertex2f(183.9507702149957, 333.4756891538572);
    glVertex2f(185.1432270794284, 336.3077742068849);
    glVertex2f(185.9630411737726, 341.0776016646157);
    glVertex2f(187.3045551462128, 344.5804437038886);
    glVertex2f(190.2761263069534, 348.0043436633317);
    glVertex2f(193.3290018745554, 349.7581232447192);
    glVertex2f(196.0571034456012, 350.9273096323109);
    glVertex2f(199.0450242138911, 351.1221740302429);
    glVertex2f(201.1235777918319, 351.9016316219706);
    glVertex2f(204.1764533594324, 351.9016316219706);
    glVertex2f(207.0994193284116, 351.3819932274855);
    glVertex2f(208.8531989097992, 351.1221740302429);
    glVertex2f(211.2565264842932, 350.4076712378258);
    glVertex2f(211.4513908822251, 348.7188464557489);
    glVertex2f(212.8803964670594, 345.9907448847017);
    glVertex2f(214.6991308477576, 343.392529122757);
    glVertex2f(216.1281364325919, 341.3789541336456);
    glVertex2f(217.9468708132901, 340.4695869432966);
    glVertex2f(220.0254243912309, 339.1055361577729);
    glVertex2f(221.3245203774439, 337.5466209743174);
    glVertex2f(221.9740683705504, 335.2082481991341);
    glVertex2f(222.4287519657249, 332.8049206246401);
    glVertex2f(222.4287519657249, 329.0375422646225);
    glVertex2f(221.8441587719291, 326.5692598908178);
    glVertex2f(221.0647011802012, 324.2308871156345);
    glVertex2f(221.3894751767545, 321.178011548034);
    glVertex2f(221.8441587719291, 318.1900907797442);
    glVertex2f(223.2082095574527, 315.7218084059396);
    glVertex2f(223.6628931526272, 312.4740684404072);
    glVertex2f(223.5329835540059, 309.2263284748748);
    glVertex2f(223.0782999588314, 306.5631817031382);
    glVertex2f(222.039023169861, 304.8094021217507);
    glVertex2f(220.9997463808906, 304.0299445300229);
    glVertex2f(218.7912832043285, 307.2776844955553);
    glVertex2f(216.7127296263878, 308.9015544783215);
    glVertex2f(215, 310);
    glVertex2f(212.4257128718849, 311.3698368521262);
    glVertex2f(210.4121140932548, 312.2142492431646);
    glVertex2f(208.5284249132459, 312.7338876376498);
    glVertex2f(206.7096905325477, 313.7731644266202);
    glVertex2f(208.6583345118672, 315.2021700114544);
    glVertex2f(209.8924756987695, 317.0209043921525);
    glVertex2f(210.3471592939441, 319.2943223680252);
    glVertex2f(211.6462552801571, 322.2822431363151);
    glVertex2f(212.4906676711955, 324.685570710809);
    glVertex2f(213.0752608649914, 327.8034010777201);
    glVertex2f(213.8547184567192, 330.0118642542822);
    glVertex2f(213.0752608649914, 331.7006890363591);
    glVertex2f(211.3864360829145, 333.5843782163678);
    glVertex2f(209.0480633077311, 335.3381577977553);
    glVertex2f(207.6190577228968, 336.8321181819003);
    glVertex2f(207.2942837263436, 339.3004005557049);
    glVertex2f(206.4498713353052, 341.508863732267);
    glVertex2f(205.0858205497815, 342.6130953205479);
    glVertex2f(203.6568149649472, 342.8729145177906);
    glVertex2f(202.8124025739088, 342.2883213239947);
    glVertex2f(202.0978997814916, 341.313999334335);
    glVertex2f(201.0586229925212, 340.014903348122);
    glVertex2f(200.5389845980361, 338.5209429639771);
    glVertex2f(199.5646626083763, 337.0919373791429);
    glVertex2f(198.0057474249207, 335.597976994998);
    glVertex2f(196.5767418400864, 335.013388012021);
    glVertex2f(195.2126910545628, 333.9091522129211);
    glVertex2f(194.6280978607677, 333.0647398218827);
    glVertex2f(193.6537758711072, 332.4801466280868);
    glVertex2f(192.8093634800688, 334.2339262094743);
    glVertex2f(191.3154030959238, 334.7535646039595);
    glVertex2f(190.6685510281773, 333.5843782163678);
    glVertex2f(190.2761263069534, 332.6100562267081);
    glVertex2f(190.3410811062641, 331.1810506418739);
    glVertex2f(190, 330);
    glVertex2f(190.6009003035067, 328.387994271516);
    glVertex2f(191.3154030959238, 327.4136722818563);
    glVertex2f(192.2897250855836, 325.7898022990901);
    glVertex2f(192.5495442828262, 323.6462939218387);
    glVertex2f(191.9649510890303, 321.4378307452766);
    glVertex2f(190.99062909993706, 318.5798195756081);
    glVertex2f(190.0812610900215, 316.566220796978);
    glVertex2f(188.9120755214298, 315.6568536066289);
    glVertex2f(187.5480247359062, 314.6175768176586);
    glVertex2f(185.664335558973, 313.8381192259308);
    glVertex2f(184.7117390246856, 313.3251871024692);
    glVertex2f(183.5856985135499, 312.9277610397155);
    glVertex2f(182.5258956795398, 312.4640972998361);
    glVertex2f(181.2011421370272, 312.1329089142079);
    glVertex2f(179.9426262716402, 311.4374133043888);
    glVertex2f(178.8165857605044, 310.9737495645093);
    glVertex2f(178.1542089892481, 310.5100858246299);
    glVertex2f(177.260003480521, 309.8477090533736);
    glVertex2f(176.6860360387718, 309.5464020615407);
    glVertex2f(175.4845148606407, 308.6768801563143);
    glVertex2f(174.9427817159959, 308.4169088646353);
    glVertex2f(174.737233138803, 308.3255539614385);
    glVertex2f(174.3603942081159, 310.9520074283483);







    glEnd();

//muk
    glBegin(GL_POLYGON);
    glColor3f(0.992, 0.761, 0.710);
    glVertex2f(191.6047929051932, 326.5921076152891);
    glVertex2f(190.3556589984196, 328.4241706785571);
    glVertex2f(189.9392810294951, 330.3811471325024);
    glVertex2f(190.0225566232801, 332.6712259615874);
    glVertex2f(190.8969503580215, 334.3367378372856);
    glVertex2f(192.0211708741177, 334.3367378372856);
    glVertex2f(192.8955646088592, 333.7121708839898);
    glVertex2f(193.2703047808912, 332.1299346019855);
    glVertex2f(194.3528875000949, 333.3374307118667);
    glVertex2f(195.6852970006534, 334.461512279629);
    glVertex2f(197.1009820494967, 335.3776827595969);
    glVertex2f(198.4750239924476, 336.5019032756932);
    glVertex2f(199.6408877054362, 338.0008639638215);
    glVertex2f(200.640194830855, 339.9578404177668);
    glVertex2f(201.6390519562739, 341.4568011058952);
    glVertex2f(203.1801004412945, 342.830484033462);
    glVertex2f(204.2626831604983, 343.1223129815933);
    glVertex2f(205.345265879702, 342.414704344216);
    glVertex2f(206.4694863957982, 341.7482656841423);
    glVertex2f(206.4694863957982, 340.1660294022291);
    glVertex2f(207.0940533491849, 338.8336199016706);
    glVertex2f(207.5104313181094, 336.9182812446177);
    glVertex2f(208.5513762404207, 335.4193205564894);
    glVertex2f(209.3424943813773, 334.586564186403);
    glVertex2f(210, 334);
    glVertex2f(211.2161952415376, 333.4207063056516);
    glVertex2f(212.4236913514186, 332.1299346019855);
    glVertex2f(213.2980850861601, 331.1306274765666);
    glVertex2f(214, 330);
    glVertex2f(213.5479118675148, 328.0910683034174);
    glVertex2f(213.0066205079129, 326.3422808339344);
    glVertex2f(212.4653291483111, 324.8849579426985);
    glVertex2f(212.0073133824941, 323.2610838638928);
    glVertex2f(211.5909354135696, 321.9286743633343);
    glVertex2f(210.6749038819357, 320.0549735031739);
    glVertex2f(210.0919747254414, 318.514375018153);
    glVertex2f(209.6339589596244, 317.015413300247);
    glVertex2f(209.134035396915, 316.1410205952832);
    glVertex2f(208.5513762404207, 314.9335244485402);
    glVertex2f(207.468793521217, 314.6004221102624);
    glVertex2f(206.4694863957982, 314.4338709226926);
    glVertex2f(205.1787146921322, 314.475508719585);
    glVertex2f(203.2633760350794, 314.8086110947247);
    glVertex2f(201.4313129718116, 315.4748158450039);
    glVertex2f(199.5576121116513, 316.1410205952832);
    glVertex2f(197.9753758297382, 317.1403277207021);
    glVertex2f(196.5596907353948, 317.8890806477662);
    glVertex2f(195.185643437944, 319.2638553622172);
    glVertex2f(194.1030607187402, 320.9710050348078);
    glVertex2f(193.3952181715686, 322.8030680980758);
    glVertex2f(192.7706512181818, 324.7184067551287);
    glVertex2f(192.2709976554724,326.0508162556872);


    glEnd();
//gola
    glBegin(GL_POLYGON);
    glColor3f(0.992, 0.761, 0.710);
    glVertex2f(190, 316);
    glVertex2f(191.0248214274143, 314.2517474999523);
    glVertex2f(192.7686997533382, 312.7917563584345);
    glVertex2f(194.1881355673693, 311.4939864548631);
    glVertex2f(196.4186775891325, 310.1962165512916);
    glVertex2f(198.4058877539761, 309.3851103615595);
    glVertex2f(200.2714319903599, 309.3445550520729);
    glVertex2f(201.28514727525, 309.952884694372);
    glVertex2f(202.1775315362303, 310.9667674315372);
    glVertex2f(202.5830846310963, 312.3862032635684);
    glVertex2f(202.8669717975025, 313.4811966197068);
    glVertex2f(202.7858611785293, 314.9411877612246);
    glVertex2f(201.8530890603374, 315.6711833319836);
    glVertex2f(200.7175403947125, 316.036181117363);
    glVertex2f(199.2981045626814, 316.4822895217157);
    glVertex2f(197.8381134211637, 317.2528404019612);
    glVertex2f(196.2970116606727, 317.7395041158005);
    glVertex2f(195.0803523760746, 319.0372740193719);
    glVertex2f(194.2692461863425, 320.1728226849969);
    glVertex2f(193.7014718535301, 322.0789222308674);
    glVertex2f(193.0931422112311, 324.0255770862246);
    glVertex2f(192, 326);
    glVertex2f(192.1198147835526, 324.6744620380103);
    glVertex2f(192.3225913309856, 323.1333602775192);
    glVertex2f(191.9575935456061, 321.511147898055);
    glVertex2f(191.6730763791999, 319.8483802091041);
    glVertex2f(190.8220448799812, 318.307278448613);

    glEnd();

//golar design

    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex2f(190, 315);
    glVertex2f(192.3950317781751, 312.891977628321);
    glVertex2f(194.9114954620767, 311.38209941798);
    glVertex2f(196.8527674468007, 310.3755139444194);
    glVertex2f(199.1535342435106, 309.8722212076391);
    glVertex2f(200.6634124538515, 309.8722212076391);
    glVertex2f(201.7465991216068, 310.6640025496082);
    glVertex2f(202.6721340844587, 312.2579749300754);
    glVertex2f(203.1994935375805, 313.6526560820863);
    glVertex2f(204.2618614931038, 314.0351085460748);
    glVertex2f(205.45171360329, 313.865129673191);
    glVertex2f(206.8965340228017, 313.3976877727607);
    glVertex2f(207.958901978325, 313.3126983363189);
    glVertex2f(208.6388174698599, 312.9302458723304);
    glVertex2f(209.0212699338483, 312.2928250990165);
    glVertex2f(208.8937857791855, 311.1454677070512);
    glVertex2f(208.8087963427436, 309.7431420057604);
    glVertex2f(208.8087963427436, 308.4683004591324);
    glVertex2f(208.4263438787552, 306.5985328574113);
    glVertex2f(208.4263438787552, 305.1112177196786);
    glVertex2f(208, 304);
    glVertex2f(207.7889231054412, 302.306566317097);
    glVertex2f(207.4064706414528, 301.0317247704689);
    glVertex2f(206.8540393045807, 299.6293990691781);
    glVertex2f(206.2591132494877, 298.3120628043292);
    glVertex2f(205.6216924761737, 296.9947265394802);
    glVertex2f(204.8567875481969, 295.847369147515);
    glVertex2f(204.1953780736254, 295.0833965022487);
    glVertex2f(203.0189509418005, 294.6912541249737);
    glVertex2f(201.2823204138684, 295.5875795587451);
    glVertex2f(199.6577305651577, 297.2681897476066);
    glVertex2f(197.9211000372256, 299.0608406146095);
    glVertex2f(196.5205915469578, 300.5733897840988);
    glVertex2f(194.8960016982471, 302.1970796328095);
    glVertex2f(192.9913101514828, 304.0466508399631);
    glVertex2f(190.7504965670543, 306.2874644243917);
    glVertex2f(188.6217236618472, 308.6403186880417);
    glVertex2f(187.1663808249934, 310.3545018078816);
    glVertex2f(185.9450013112339, 311.7448994472077);
    glVertex2f(185.7199827889403, 313.5877549867687);
    glVertex2f(187.2917502627388, 314.4007381628714);
    glVertex2f(188.6105896373053, 314.9788595325444);
    glEnd();

    //bam hat

    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex2f(232.0360252420358, 284.4538223377813);
    glVertex2f(235, 285);
    glVertex2f(236.0289913765251, 281.6894611677502);
    glVertex2f(236.8890148516458, 279.2322512388336);
    glVertex2f(237.0118753480917, 276.8364715581399);
    glVertex2f(236.4590031140855, 275.4850060972358);
    glVertex2f(235, 275);
    glVertex2f(232.6503277242649, 274.1949708845546);
    glVertex2f(229.9473968024568, 274.1949708845546);
    glVertex2f(227.1216053842029, 274.7478431185609);
    glVertex2f(223.9886627248343, 275.1778548561213);
    glVertex2f(221.1014410583575, 276.2835993241337);
    glVertex2f(218.8285218741098, 277.2664832957003);
    glVertex2f(217.8456379025432, 278.003462743753);
    glVertex2f(217.8456379025432, 280.7680074444065);
    glVertex2f(217.6613471578744, 284.1466710966668);
    glVertex2f(217.4770564132057, 287.4639045007041);
    glVertex2f(216.9241841791995, 289.9211144296207);
    glVertex2f(215.7570094629641, 292.4397546067602);
    glVertex2f(215, 295);
    glVertex2f(213.4226600304935, 298.2756281879371);
    glVertex2f(212.6240668035956, 300.7328381168536);
    glVertex2f(212.5012063071498, 303.8657807762223);
    glVertex2f(212.6240668035956, 306.7530024426993);
    glVertex2f(213.054078541156, 308.7802006340554);
    glVertex2f(213.9141020162768, 310.500247584297);
    glVertex2f(215, 310);
    glVertex2f(216.8013236827537, 308.350188896495);
    glVertex2f(218.7670916258868, 305.5858277264638);
    glVertex2f(220.179873350138, 303.4357690386619);
    glVertex2f(221.470022547695, 301.2857103508599);
    glVertex2f(222.2071855263699, 298.8899306701662);
    glVertex2f(223.497220739051, 296.2484299965809);
    glVertex2f(224.8486861999551, 292.1326033656456);
    glVertex2f(225.8315701715217, 290.1054051742894);
    glVertex2f(226.7530238948654, 288.2010674793791);
    glVertex2f(227.9201986111007, 286.0510087915771);
    glVertex2f(229.7631060577881, 284.2081013448897);
    glEnd();


    //cup

    glBegin(GL_POLYGON);
    glColor3f(1,0,0);
    glVertex2f(234.9520929586294, 290.9023452909721);
    glVertex2f(235.2492474438984, 286.6997318564532);
    glVertex2f(235.5888525699201, 283.6008350815049);
    glVertex2f(236, 280);
    glVertex2f(236.4378653849745, 277.5303934538665);
    glVertex2f(236.947273074007, 275.7050159014997);
    glVertex2f(237.0321743555125, 274.4739473196709);
    glVertex2f(237.6264833260505, 273.6673851453693);
    glVertex2f(239.0698051116428, 273.4975828523584);
    glVertex2f(240.682924960246, 273.6249345046165);
    glVertex2f(242.2960538088491, 273.5824838638638);
    glVertex2f(243.4846717499252, 273.8796383491329);
    glVertex2f(244.4610364872376, 276.0870716682741);
    glVertex2f(244.5883884094958, 279.5680242099969);
    glVertex2f(244.9279935355175, 282.1150626551598);
    glVertex2f(245.3100493022919, 284.9592555855918);
    glVertex2f(246, 288);
    glVertex2f(246, 290);
    glVertex2f(245.7770063505718, 291.4542036207574);
    glVertex2f(244.6732896910012, 291.4966542615101);
    glVertex2f(242.5083070126127, 291.4542036207574);
    glVertex2f(240.5131268972351, 291.3268516984992);
    glVertex2f(238.8151012671265, 291.3268516984992);
    glVertex2f(236.8623717925016, 291.369032339252);
    glEnd();

//juta

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);

    glVertex2f(285.0694553932308, 167.4163148439453);
    glVertex2f(284.9858758785537, 165.9397434179833);
    glVertex2f(285.8216710253247, 164.6024711831497);
    glVertex2f(286.7967653632242, 163.5437973305731);
    glVertex2f(288.2176171127348, 162.9308808896077);
    glVertex2f(290.1965665267595, 163.738816198153);
    glVertex2f(290.975741097079, 165.2711073005665);
    glVertex2f(291.5607976998188, 166.9426975941085);
    glVertex2f(292.4523125230411, 168.7257272405533);
    glVertex2f(293.3716781844892, 169.8679806078069);
    glVertex2f(294.6532397428713, 171.065953651512);
    glVertex2f(295.7397734336736, 172.5703849156998);
    glVertex2f(296.5477087422189, 174.1583956945647);
    glVertex2f(297.32778242125385, 176.0528466939123);
    glVertex2f(296.9934661538301, 177.1672582229403);
    glVertex2f(296.2133906835105, 177.5851557963258);
    glVertex2f(295.0154176390854, 177.8637541785828);
    glVertex2f(293.6224257285205, 177.0000991935861);
    glVertex2f(292.3408731701383, 176.08724532138);
    glVertex2f(291.6165173762701, 174.96633100311);
    glVertex2f(290.975741097079, 174.2976948856932);
    glVertex2f(290.9478812588533, 173.4061800624708);
    glVertex2f(290.6692828765964, 172.0131881511858);
    glVertex2f(289.8056278915997, 171.0380938132863);
    glVertex2f(289.1648516124086, 170.1744388282896);
    glVertex2f(288.3011966274119, 169.7008215784528);
    glVertex2f(287.4375416424152, 168.7814469170046);
    glVertex2f(286.3788677898386, 168.1685304760393);
    glVertex2f(285.6266521577448, 167.7506329026538);

    glEnd();


}
void bench5()
{
    glBegin(GL_QUADS);
    glColor3f(0.302, 0.314, 0.341);
    glVertex2f(778.6397113498799,231.3459308759239);
    glVertex2f(863.1231277260407,231.0955270127511);
    glVertex2f(863.2265356998372,226.3387602181199);
    glVertex2f(778.390750433746,226.0315632981035);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.302, 0.314, 0.341);
    glVertex2f(786.1779579732795,226.7395249951406);
    glVertex2f(786.3479825084224,175.6446771195477);
    glVertex2f(790.1202910705352,175.6761681853915);
    glVertex2f(789.8115496678143,226.6894036819168);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.30f, 0.62f, 0.87f);
    glVertex2f(781.6283949273258,302.6138124729679);
    glVertex2f(859.6146082655166,302.6138124729679);
    glVertex2f(860,230);
    glVertex2f(782.4742323821868,230.5484613188086);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.302, 0.314, 0.341);
    glVertex2f(789.3613457009542,195.9692053452677);
    glVertex2f(1067.6693801717975,195.8002257134079);
    glVertex2f(1067.8700742594533,187.4714210756962);
    glVertex2f(789.3237807307108,187.3416136198292);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(782.5136815481877,302.4788907337874);
    glVertex2f(778.1352817256497,298.9389078985441);
    glVertex2f(778.6256534016283,231.1395589936498);
    glVertex2f(783.1739605295317,231.0597641317567);

    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(859.4990592478276,302.6341974977761);
    glVertex2f(863.5970292243674,299.8168431389052);
    glVertex2f(863.8154690880717,231.2370157870068);
    glVertex2f(860.093208149941,231.2370157870068);

    glEnd();


    //men

    glBegin(GL_POLYGON);
    glColor3f(0.106, 0.090, 0.239);
    glVertex2f(810.3265434231039, 236.307775057284);
    glVertex2f(809.8158027628887, 227.8805541637333);
    glVertex2f(809.560432432781, 222.6454623965276);
    glVertex2f(809.7361582204759, 218.7205016605832);
    glVertex2f(810.3024169792501, 216.13180901919014);
    glVertex2f(811.7585109303836, 213.6241728316159);
    glVertex2f(812.6483461227431, 212.0062906636898);
    glVertex2f(813.699965318951, 210.3884084957636);
    glVertex2f(813.7808636402914, 208.5278440026486);
    glVertex2f(813.0528166647247, 206.0201266423631);
    glVertex2f(812.0820873639689, 203.5124092820776);
    glVertex2f(811.4349344967984, 201.0046919217921);
    glVertex2f(810.9495698464206, 197.9307158027324);
    glVertex2f(810.610551488933, 195.8712351156918);
    glVertex2f(810.7440026957547, 193.7360158065544);
    glVertex2f(811.0776307128091, 191.2004428769309);
    glVertex2f(811.8783379537396, 189.1319491711939);
    glVertex2f(812.145240367383, 187.4638090859221);
    glVertex2f(812.3454171776157, 185.7289433972395);
    glVertex2f(811.9450635571504, 183.7271752949134);
    glVertex2f(811.0776307128091, 181.9255840028199);
    glVertex2f(810, 180);
    glVertex2f(808.8756858002504, 179.2565598663851);
    glVertex2f(807.2075457149786, 179.1898342629742);
    glVertex2f(804.6052471819545, 179.3232854697959);
    glVertex2f(801.2022414080001, 180.5243463311916);
    glVertex2f(799.0002964954413, 182.4593888301068);
    glVertex2f(797.4656076169912, 185.9291202074721);
    glVertex2f(797.1319795999368, 188.9317723609613);
    glVertex2f(796.6649003760607, 191.0669916701091);
    glVertex2f(794.7715009774472, 193.9153285185659);
    glVertex2f(792.5867340845803, 197.249972723468);
    glVertex2f(790, 200);
    glVertex2f(790.5169549229169, 214.6131201351994);
    glVertex2f(790.0570039981027, 218.2927275337121);
    glVertex2f(787.7572493740323, 222.5472735882423);
    glVertex2f(785.8024579435723, 227.146782836383);
    glVertex2f(784.4226051691301, 231.7462920845238);
    glVertex2f(784.4226051691301, 238.1856050319209);
    glVertex2f(784.5375929003336, 244.5099302481145);
    glVertex2f(785.3425070187583, 249.4544026898658);
    glVertex2f(787.6422616428288, 253.708948744396);
    glVertex2f(792.2417708909696, 257.0435929492981);
    glVertex2f(796.6113046767035, 256.4686542932805);
    glVertex2f(801.9007403120656, 251.2942063891221);
    glVertex2f(805.3503722481713, 248.4195131090341);
    glVertex2f(807.3051636786312, 245.8897830225567);
    glVertex2f(808.6850164530734, 243.1300774736722);
    glVertex2f(810, 240);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.106, 0.090, 0.239);
    glVertex2f(830.0534950245229, 236.680470439692);
    glVertex2f(831.1327235391457, 232.2436421017987);
    glVertex2f(831.8522092155608, 229.4856136755407);
    glVertex2f(831.6123806567558, 226.4877566904776);
    glVertex2f(831.0128092597432, 224.0894711024271);
    glVertex2f(830.2454656392994, 221.9970650418496);
    glVertex2f(830, 220);
    glVertex2f(829.5935291897155, 218.2303211109206);
    glVertex2f(829.1589048899929, 215.9123248457335);
    glVertex2f(829.1589048899929, 214.028952880269);
    glVertex2f(829.1589048899929, 212.0731435315174);
    glVertex2f(830, 210);
    glVertex2f(830.752527322309, 207.7269005342916);
    glVertex2f(831.3320263886058, 205.3364668858175);
    glVertex2f(832.1288376047638, 204.0325939866497);
    glVertex2f(832.8532114376349, 202.5114089376207);
    glVertex2f(833.2153983540703, 200.8453491220175);
    glVertex2f(833.2878357373575, 198.4549154735433);
    glVertex2f(832.7083366710607, 196.6439808913659);
    glVertex2f(832.4910245211994, 194.7606089259014);
    glVertex2f(832.1034631628738, 193.2284325279162);
    glVertex2f(831.8436044815307, 191.214527747508);
    glVertex2f(831.9085691518666, 189.135658296764);
    glVertex2f(831.8436044815307, 186.7319654943412);
    glVertex2f(832.4932511848883, 184.45820203259);
    glVertex2f(832.8830392069028, 182.639191263189);
    glVertex2f(833.2728272289173, 181.1450038454667);
    glVertex2f(834.3122619542894, 179.780745768416);
    glVertex2f(835.8064493720117, 178.481452361701);
    glVertex2f(837.5604954710769, 178.0916643396865);
    glVertex2f(839.4444799108137, 178.0916643396865);
    glVertex2f(841.7182343725651, 177.7668409880077);
    glVertex2f(843.9919978343164, 177.961734999015);
    glVertex2f(846.200796625732, 179.26102840573);
    glVertex2f(846.8504433290894, 183.0289792852035);
    glVertex2f(846.720513988418, 186.1472834613195);
    glVertex2f(847.1103020104325, 188.9407642857567);
    glVertex2f(848.1497367358045, 191.6692804398582);
    glVertex2f(850, 195);
    glVertex2f(851.7227936042709, 197.9058887920902);
    glVertex2f(852.8921576703144, 200.6344049461917);
    glVertex2f(853.9315293956865, 204.0125678036507);
    glVertex2f(854.7761331100512, 207.325765990774);
    glVertex2f(854.3863450880367, 210.703928848233);
    glVertex2f(853.4768397033362, 213.6273390133417);
    glVertex2f(852.8286295748131, 217.290311903403);
    glVertex2f(852.3430285537225, 220.6895190510375);
    glVertex2f(853.1321302129949, 223.9673259433993);
    glVertex2f(854.2247325104488, 227.1237325804885);
    glVertex2f(855.9243360842661, 230.2801392175776);
    glVertex2f(856.7134377435384, 234.1042472586665);
    glVertex2f(857.1990387646291, 237.6855547892909);
    glVertex2f(857.745339913356, 241.2668623197534);
    glVertex2f(857.6846397857197, 245.1516704884785);
    glVertex2f(857.1990387646291, 248.732978019022);
    glVertex2f(856.4256572547381, 250.8784205293335);
    glVertex2f(855.3216205103649, 253.0076342506246);
    glVertex2f(854.2175837659918, 254.5453997160014);
    glVertex2f(852.6403884168873, 256.5957536698372);
    glVertex2f(851.2603424864209, 258.0546593677588);
    glVertex2f(849.722577021044, 258.9615466934939);
    glVertex2f(848.7368299278536, 259.5135650656804);
    glVertex2f(846.3710369041969, 259.6712846005909);
    glVertex2f(842.7434876012566, 259.3164156470424);
    glVertex2f(840.2988348101445, 258.2518087863969);
    glVertex2f(837.8936119027601, 256.9900525071133);
    glVertex2f(835.567248762831, 255.5311468091917);
    glVertex2f(834.3843522510026, 254.2693905299081);
    glVertex2f(833.0043063205361, 252.0613170411619);
    glVertex2f(832, 250);
    glVertex2f(831.3482512039765, 247.8817493660351);
    glVertex2f(830.677943180607, 245.9102551796545);
    glVertex2f(830.4413638782413, 243.3473127373597);
    glVertex2f(829.96820527351, 241.7306875045277);
    glVertex2f(829.7316259711442, 239.562043899509);
    glVertex2f(829.8499156223721, 238.5368669225911);

    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.106, 0.090, 0.239);
    glVertex2f(800.7873075814842, 256.830426815965);
    glVertex2f(801.077967813891, 253.6292131022697);
    glVertex2f(802.1496197250314, 249.7891592208851);
    glVertex2f(802.1496197250314, 247.3779625976901);
    glVertex2f(803.131959009367, 243.6272122949424);
    glVertex2f(805, 240);
    glVertex2f(806.4361914996003, 237.6438725262734);
    glVertex2f(808.2222630723373, 235.5898902176258);
    glVertex2f(808.8473881227953, 233.2679971730677);
    glVertex2f(809.4725131732533, 231.303318443057);
    glVertex2f(810, 230);
    glVertex2f(811.4083332083344, 229.054443591952);
    glVertex2f(812.7190281929579, 228.2430609824232);
    glVertex2f(815.0907619746575, 227.3692643260075);
    glVertex2f(817.275236156968, 227.0571940915734);
    glVertex2f(820.271278662647, 226.4954676695919);
    glVertex2f(824.5776971014562, 226.6202957633656);
    glVertex2f(828.0104696802321, 226.7451238571392);
    glVertex2f(830.6942736963658, 227.7437486073285);
    glVertex2f(832.0673827278762, 230.9268649985569);
    glVertex2f(832.1922108216498, 234.1099813897853);
    glVertex2f(831.4432422590079, 237.2930977810138);
    glVertex2f(830.7566877432527, 239.9144877502607);
    glVertex2f(830.0701332274975, 243.2224322352627);
    glVertex2f(830.5070315557053, 246.5303767202648);
    glVertex2f(832.129796774763, 250.1503914397011);
    glVertex2f(834.0646322282548, 252.8341954558348);
    glVertex2f(836.1242957755203, 255.1435151906476);
    glVertex2f(835.4812450427506, 256.641977234296);
    glVertex2f(830.0293420911465, 256.7819312202325);
    glVertex2f(825.9048632307606, 256.5281171365165);
    glVertex2f(821.6534773285167, 256.6550241783745);
    glVertex2f(817.2117308634857, 256.6550241783745);
    glVertex2f(813.4045196077449, 256.5915706574455);
    glVertex2f(810.3539019143748, 256.830426815965);
    glVertex2f(807.5539230852361, 256.7915382211159);
    glVertex2f(802.7317373239417, 256.830426815965);
    glVertex2f(805.0261644200415, 256.7915382211159);



    glEnd();



//body

    glBegin(GL_POLYGON);
    glColor3f(1,1,1);

    glVertex2f(821.5933398066741, 307.7940334975903);
    glVertex2f(820.0080670623944, 308.9263711720758);
    glVertex2f(818.1963267832176, 309.8322413116641);
    glVertex2f(816.6110540389379, 310.8136006295515);
    glVertex2f(815.4787163644525, 311.7194707691399);
    glVertex2f(814.3463786899967, 313.5312110483166);
    glVertex2f(814.0444219767708, 316.173332887827);
    glVertex2f(813.5159977286776, 319.1928994207439);
    glVertex2f(813.7424652635747, 321.457747697148);
    glVertex2f(812.3081708758931, 323.7977392969847);
    glVertex2f(810.4964305967163, 324.0242068318818);
    glVertex2f(809.5150712788288, 322.740898007983);
    glVertex2f(808.3072444260443, 320.4762154518274);
    glVertex2f(807.2503959298579, 318.0605617462584);
    glVertex2f(806.570933251666, 316.852734893474);
    glVertex2f(805, 315);
    glVertex2f(803.4759370149063, 313.5312110483166);
    glVertex2f(801.4377292008323, 312.6253409087283);
    glVertex2f(799.2485430301605, 311.3420248776448);
    glVertex2f(797.2103352160866, 310.5871330946544);
    glVertex2f(794.9456598671156, 308.8508819937767);
    glVertex2f(792.9074520530418, 306.1332715750116);
    glVertex2f(791.3976684870611, 303.1137044430504);
    glVertex2f(790.7182658823698, 300.0186481327902);
    glVertex2f(789.8878849210804, 296.999081000829);
    glVertex2f(790, 295);
    glVertex2f(789.4349498512862, 291.8658186764949);
    glVertex2f(789.2084823163891, 289.2991848143279);
    glVertex2f(788.4664794277487, 286.6346236703477);
    glVertex2f(787.3125439208442, 283.2369246777954);
    glVertex2f(785.8380707731327, 280.864946135825);
    glVertex2f(784.6200277380668, 277.9801073685637);
    glVertex2f(784.1712750409373, 275.2875911857864);

    glVertex2f(783.5301997593236, 272.9797201719773);
    glVertex2f(783.1455545903555, 271.6975696087501);
    glVertex2f(784.2353825690986, 269.7743437639092);
    glVertex2f(785.3252105478418, 269.005034259729);
    glVertex2f(784.9436860561262, 265.9130466455262);
    glVertex2f(785.3060463168216, 263.2315807163803);
    glVertex2f(785.8858227339343, 261.202363256486);
    glVertex2f(787.1178476202987, 259.3905619530091);
    glVertex2f(788.2049284023849, 257.9411209102275);
    glVertex2f(789.2920091844711, 256.9265121802804);
    glVertex2f(792.2636333221735, 258.1585370666447);
    glVertex2f(795, 260);
    glVertex2f(797.4602631070532, 260.163949652296);
    glVertex2f(800, 260);
    glVertex2f(803.5033425505824, 259.9862120216039);
    glVertex2f(807.7690456871912, 260.6082937290261);
    glVertex2f(811.323798301032, 260.6082937290261);
    glVertex2f(815, 260);
    glVertex2f(820.743892727771, 260.430556098334);
    glVertex2f(825, 260);
    glVertex2f(831.8524946459622, 261.0526378057562);
    glVertex2f(837.4512300127614, 261.1415066211021);
    glVertex2f(841.7169331493702, 261.1415066211021);
    glVertex2f(844.6496400557888, 261.2303754364481);
    glVertex2f(846.9601932547854, 261.0526378057562);
    glVertex2f(848.9153071923978, 260.341687282988);
    glVertex2f(850.9592899453562, 259.2752614988358);
    glVertex2f(852.9144038829686, 257.6756228226075);
    glVertex2f(854.95836635927, 256.6980658538014);
    glVertex2f(856.4691564968093, 260.07580883695);
    glVertex2f(857.8021887269996, 262.5634076666384);
    glVertex2f(859.2240897725359, 265.4072097577109);
    glVertex2f(859.4906962185739, 270.7393386784718);
    glVertex2f(858.6908768804598, 273.3165343235063);
    glVertex2f(857.5355822809615, 275.9825987838867);
    glVertex2f(856.8246317581934, 278.8264008749592);
    glVertex2f(856.0248124200792, 282.3811534887998);
    glVertex2f(855.3138618973111, 285.6692996566024);
    glVertex2f(855.136124266619, 288.690839738367);
    glVertex2f(854.514042559169, 292.4233296228996);
    glVertex2f(853.5364855903907, 297.0445080208924);
    glVertex2f(851.9368469141624, 300.599260634733);
    glVertex2f(849.803995345858, 303.9762756178816);
    glVertex2f(847.4934061468615, 306.5534712629161);
    glVertex2f(844.7384728711348, 308.8640604619125);
    glVertex2f(842.0724084107543, 311.4412561069469);
    glVertex2f(839.9395568424499, 314.1073205673274);
    glVertex2f(837.8067052741454, 317.39546673513);
    glVertex2f(835.584984890495, 320.9502193489706);
    glVertex2f(834.0724150296127, 323.260808547967);
    glVertex2f(832.8300516147684, 323.8828902553891);

    glVertex2f(831.2304129385401, 322.6387268405449);
    glVertex2f(830.78606886181, 320.5947440875865);
    glVertex2f(830.78606886181, 318.2841548885901);
    glVertex2f(830.519462415772, 315.9735656895937);
    glVertex2f(830.1639871543879, 314.1073205673274);
    glVertex2f(828.5643484781596, 312.6854195217911);
    glVertex2f(826.5203657252011, 311.0857808455629);
    glVertex2f(825, 310);
    glVertex2f(823.6765636341286, 308.3308475698364);
    glVertex2f(822.9656131113604, 306.9978153396461);
    glEnd();

//laptop

    glBegin(GL_QUADS);
    glColor3f(0.847, 0.788, 0.800);
    glVertex2f(793.0648937324075,290.4433699638735);
    glVertex2f(795.3626138147565,257.0219869478897);
    glVertex2f(847.374641133383,256.39533601634);
    glVertex2f(850,290);
    glEnd();


//GOLA

    glBegin(GL_POLYGON);
    glColor3f(0.518, 0.404, 0.349);
    glVertex2f(822.6906565853079, 315.0764044074209);
    glVertex2f(824.5083360406618, 316.1917986186607);
    glVertex2f(826.2847045993032, 317.4311255200383);
    glVertex2f(828.0197622612318, 319.2901158721047);
    glVertex2f(829.4656436461725, 320.7359972570453);
    glVertex2f(830.209239786999, 321.6861478814348);
    glVertex2f(830.5397269606997, 320.6946863603327);
    glVertex2f(830.7462814442626, 319.2074940786795);
    glVertex2f(830.5397269606997, 317.0593274496295);
    glVertex2f(830.3744833738493, 315.4895133745467);
    glVertex2f(830.3744833738493, 314.0436319896062);
    glVertex2f(829.6721981297353, 312.9695486750789);
    glVertex2f(828.5568039184955, 312.1020198441146);
    glVertex2f(827.3587879138304, 311.4823563934258);
    glVertex2f(826.0368392190276, 310.3669621821859);
    glVertex2f(824.9214450077877, 309.5820551446468);
    glVertex2f(823.8060507965479, 308.507918301195);
    glVertex2f(822.9385219655835, 307.3099558254545);
    glVertex2f(822.3601694116072, 306.9381577550412);
    glVertex2f(820.8316662332415, 308.2187955531314);
    glVertex2f(819.2205412614505, 309.0863243840958);
    glVertex2f(817.4441727028093, 309.9125423183475);
    glVertex2f(815.9569804211561, 310.9040038394496);
    glVertex2f(814.882971066288, 312.1020198441146);
    glVertex2f(814, 314);
    glVertex2f(813.6435702052512, 317.0593274496295);
    glVertex2f(813.7675028953889, 319.6206030458054);
    glVertex2f(814.469788139503, 321.2317280175963);
    glVertex2f(815.2133842803295, 320.116338063565);
    glVertex2f(816.4940220784198, 318.3812761444278);
    glVertex2f(818.0638361534981, 316.9353947594873);
    glVertex2f(819.5097175384387, 316.2331095153733);
    glVertex2f(820.7903553365289, 315.5308242712593);
    glVertex2f(821.8231277543437,315.0764044074209);
    glEnd();


//MUK

    glBegin(GL_POLYGON);
    glColor3f(0.992, 0.761, 0.710);
    glVertex2f(822.127948514947, 314.8756630631068);
    glVertex2f(820.7786572061067, 315.3427254392438);
    glVertex2f(819.273678438554, 316.3806418306593);
    glVertex2f(817.6130122122892, 317.8856205982119);
    glVertex2f(815.9004501664534, 319.7538701027598);
    glVertex2f(814.6549504967547, 321.9853903443033);
    glVertex2f(813.409450827056, 323.749842097097);
    glVertex2f(812.0601595182158, 327.0192848426686);
    glVertex2f(811.3336180442249, 329.4583883624952);
    glVertex2f(811.1779305855125, 332.6240333563126);
    glVertex2f(810.7627640289463, 334.6998661391436);
    glVertex2f(810.8146598485171, 337.0870738393994);
    glVertex2f(811.4374096833665, 339.4742815396551);
    glVertex2f(812.9942842704899, 341.8614892399109);
    glVertex2f(814.1878881206177, 342.6399265334725);
    glVertex2f(815.3814919707456, 343.7816345640296);
    glVertex2f(817.4573247535768, 344.6119676771621);
    glVertex2f(818.4952411449924, 343.9892178423127);
    glVertex2f(819.8445324538327, 342.5880307139017);
    glVertex2f(821.2457195822437, 341.4982185029155);
    glVertex2f(822.5431150715132, 340.8235728484954);
    glVertex2f(823.7886147412119, 340.3565104723584);
    glVertex2f(825, 340);
    glVertex2f(827.2137388328832, 340.4084062919291);
    glVertex2f(828.8225092395775, 340.0451355549337);
    glVertex2f(829.5490507135684, 338.9034275243766);
    glVertex2f(830.8464462028378, 337.657927854678);
    glVertex2f(832.1957375116781, 337.2946571176825);
    glVertex2f(833.2336539030937, 337.3465529372533);
    glVertex2f(834.32346611408, 335.78967835013);
    glVertex2f(834.115882357969, 334.3365954021482);
    glVertex2f(834.0639870162261, 332.8835124541665);
    glVertex2f(833.8045079183722, 331.11905458876);
    glVertex2f(833.5969246400891, 329.3545967233536);
    glVertex2f(833.2336539030937, 327.6939304970887);
    glVertex2f(832.7665915269566, 326.240847549107);
    glVertex2f(832.1957375116781, 324.7358687815545);
    glVertex2f(831.6248834963995, 323.0233067357188);
    glVertex2f(831.0021336615501, 321.7778070660202);
    glVertex2f(830, 320);
    glVertex2f(828.5630301417235, 318.6121620722028);
    glVertex2f(827.4213221111664, 317.9894122373535);
    glVertex2f(826.8342534542365, 317.1854032371849);
    glVertex2f(825.6854168571148, 316.4585882471691);
    glVertex2f(824.700697738674, 315.6145450329572);
    glVertex2f(823.2696565455041, 314.8237672435361);
    glEnd();


//chul

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(817.8011007096459, 344.8134981230877);
    glVertex2f(819.3609667798715, 343.2536320528621);
    glVertex2f(820.5538055394559, 342.4278206039192);
    glVertex2f(821.4713738160592, 341.4184954996556);
    glVertex2f(822.8477262309642, 340.9597113613539);
    glVertex2f(824.6369843703407, 340.8220761198634);
    glVertex2f(826.0133367852457, 340.8220761198634);
    glVertex2f(827.3438107863205, 340.8220761198634);
    glVertex2f(828.4448927182444, 340.179783262412);
    glVertex2f(829.2248257533573, 339.6292373602792);
    glVertex2f(830.1882724437908, 338.8951827389965);
    glVertex2f(831.5187464448657, 338.0693712900536);
    glVertex2f(833.1244909289214, 337.3811950826011);
    glVertex2f(833.7667887225438, 336.9224109442995);
    glVertex2f(834.2714512746755, 334.9496391496024);
    glVertex2f(834.4090865161661, 334.1697061144896);
    glVertex2f(835.5560468619202, 334.857823219421);
    glVertex2f(835.9689525863918, 336.6930188751487);
    glVertex2f(836.5565843345006, 339.0037856111376);
    glVertex2f(837.1793812695691, 340.373938862882);
    glVertex2f(838.0097771829937, 341.7025723297675);
    glVertex2f(838.591054322391, 343.570963149729);
    glVertex2f(838.5080147310485, 346.5603884233015);
    glVertex2f(838, 348);
    glVertex2f(836.8887426998705, 349.7574126899862);
    glVertex2f(834.9788320989938, 350.3386898293834);
    glVertex2f(834, 350);
    glVertex2f(832.9858819067747, 349.7989324856574);
    glVertex2f(831.4911692626105, 349.2176553462602);
    glVertex2f(830.6607733491858, 349.2176553462602);
    glVertex2f(829.8718972314324, 350.3802096250546);
    glVertex2f(828.1695856089119, 351.169085742808);
    glVertex2f(826.2596750080353, 351.8749222692189);
    glVertex2f(824.3497644071587, 352.2070806345888);
    glVertex2f(822.7304923759806, 352.2070806345888);
    glVertex2f(820.9036213664445, 352.1240410432463);
    glVertex2f(820.0732254530218, 351.5842836995203);
    glVertex2f(818.5785128088575, 351.169085742808);
    glVertex2f(816.9592407776795, 351.5427639038491);
    glVertex2f(815.173895638165, 351.9579618605613);
    glVertex2f(813.4300581456248, 351.9579618605613);
    glVertex2f(812.2675038668303, 351.5842836995203);
    glVertex2f(811.1879891793783, 350.8784471731094);
    glVertex2f(810.5236724486386, 349.6743730986437);
    glVertex2f(810.2745537646113, 348.470299024178);
    glVertex2f(809.9423953092414, 347.6399031107534);
    glVertex2f(809.9423953092414, 346.3943092406165);
    glVertex2f(810.0254349005838, 345.1071955748084);
    glVertex2f(810, 344);
    glVertex2f(810.1915140832688, 341.5364931470826);

    glVertex2f(810.4406328572961, 340.4984982553019);
    glVertex2f(810.3991130616249, 339.5850627505348);
    glVertex2f(810.772791222666, 338.0488303106993);
    glVertex2f(812, 340);
    glVertex2f(813.0563799845837, 341.7025723297675);
    glVertex2f(813.9698154893508, 343.1972849739318);
    glVertex2f(815.7136469075425, 344.3598392527263);
    glVertex2f(817.0838001646932, 344.7750372094386);
    glEnd();

//pa

    glBegin(GL_POLYGON);
    glColor3f(0.992, 0.761, 0.710);
    glVertex2f(802.4398138499517, 179.1467919775571);
    glVertex2f(802.5169497384039, 177.2955306547073);
    glVertex2f(802.8640612364383, 174.9814540011451);
    glVertex2f(805.2167058342267, 174.4800707262066);
    glVertex2f(807.6464863204671, 174.5572066146586);
    glVertex2f(808.1478695954057, 176.4856038259605);
    glVertex2f(807.8007580973713, 178.953952256427);
    glVertex2f(805.1010020015485, 178.7611125352968);
    glEnd();

//juta

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(802.5615342819293, 173.8144651447542);
    glVertex2f(802.5102003481645, 172.3257810655734);
    glVertex2f(801.9455270767511, 170.7857630526277);
    glVertex2f(801.0215162689835, 170.1184219136845);
    glVertex2f(799.6355000573324, 169.2970789734468);
    glVertex2f(798.1468159781515, 169.2970789734468);
    glVertex2f(797.1714712366191, 168.527069966974);
    glVertex2f(796.9661355015597, 167.3977234241471);
    glVertex2f(797.1714712366191, 166.1657090137906);
    glVertex2f(797.7361445080326, 165.4983678748475);
    glVertex2f(799.0708267859189, 165.2416982060232);
    glVertex2f(801.2268520044043, 165.087690447286);
    glVertex2f(804.152886228864, 165.2416982060232);
    glVertex2f(807.025786519472, 165.1903642722583);
    glVertex2f(809.0809438700664, 165.5497018086123);
    glVertex2f(810.1076225453636, 167.1410537553228);
    glVertex2f(809.8509528765393, 169.0917432383874);
    glVertex2f(809.5429492739502, 170.9397648539222);
    glVertex2f(809.0296099363015, 172.4284489331031);
    glVertex2f(808.8242742012421, 173.7117972772245);
    glVertex2f(807.8489294597098, 174.2764705486379);
    glVertex2f(806.2062435792343, 174.4818062836974);
    glVertex2f(804.2042201624048, 174.3278044824028);
    glEnd();


//juta 2

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(842.594591459581, 173.9862518389248);
    glVertex2f(842.6344934695147, 172.270465411776);
    glVertex2f(842.9936115589179, 170.9137970740305);
    glVertex2f(844, 170);
    glVertex2f(845.1483200953375, 169.7167367760197);
    glVertex2f(846.1857723536134, 169.3576186866165);
    glVertex2f(847.1035185820884, 168.9985005972133);
    glVertex2f(847.9015587807623, 168.3999704482079);
    glVertex2f(848.3803828999667, 166.9235960806613);
    glVertex2f(848, 166);
    glVertex2f(846.385282403282, 165.7265357826505);
    glVertex2f(844.4699859264646, 165.8063398025179);
    glVertex2f(842.7541994993157, 166.0058498521864);
    glVertex2f(840.9187070423659, 165.8063398025179);
    glVertex2f(839.2827246350844, 166.0058498521864);
    glVertex2f(837.9659583072726, 165.7265357826505);
    glVertex2f(836.5294859496595, 166.1654578919211);
    glVertex2f(835.7713477609193, 167.442322097993);
    glVertex2f(835.8511517807867, 169.158108636948);
    glVertex2f(836.0905638403889, 170.6344830044947);
    glVertex2f(836.21026987019, 172.4300734515108);
    glVertex2f(837.247722128466, 173.9463498289911);
    glVertex2f(838.4846484364105, 174.1059578687259);
    glVertex2f(840.5595889529626, 174.1059578687259);
    glEnd();

//PA

    glBegin(GL_POLYGON);
    glColor3f(0.992, 0.761, 0.710);
    glVertex2f(837.0194879343277, 178.3120381133498);
    glVertex2f(837.2047718433475, 176.3533225037116);
    glVertex2f(837.2841792329275, 175.3474955690325);
    glVertex2f(837.4694631419474, 174.4210760239334);
    glVertex2f(838.3429444273265, 174.1563847253336);
    glVertex2f(839.2428948425658, 174.1563847253336);
    glVertex2f(840.3545982966848, 174.2357921149136);
    glVertex2f(841.5721782702437, 174.2622612447735);
    glVertex2f(842.5250669452029, 174.791643841973);
    glVertex2f(843.0279804125424, 176.0886312051118);
    glVertex2f(842.9485730229625, 177.5709024772705);
    glVertex2f(841.1751413223441, 177.8602629057302);
    glVertex2f(838.978203543966, 178.1796924640499);
    glEnd();


}

void bench6()
{

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(889.8011661125682,302.6901841945054);
    glVertex2f(890,230);
    glVertex2f(886.1101405980944,230.0603272967969);
    glVertex2f(885.7529445805646,299.3563546975614);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.30f, 0.62f, 0.87f);
    glVertex2f(889.5108630515736,302.9318403297256);
    glVertex2f(966.9815983528487,302.9318403297256);
    glVertex2f(967.2520023155058,230.7339823002676);
    glVertex2f(890,230);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(966.498697544121,302.9864028923868);
    glVertex2f(971.4039807637905,298.9342124065728);
    glVertex2f(971.4039807637905,231.1133400650563);
    glVertex2f(966.498697544121,231.2199766567883);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.671, 0.671, 0.671);
    glVertex2f(889.0275559286366,243.2538229068518);
    glVertex2f(968.013000927398,242.9143439168858);
    glVertex2f(968.12616059072,236.8037220974976);
    glVertex2f(888.8012366019926,237.4826800774296);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.302, 0.314, 0.341);
    glVertex2f(885.9584239601257,231.8913216874441);
    glVertex2f(971.27663067828,231.4651290404286);
    glVertex2f(971.4439521386062,225.8185539777884);
    glVertex2f(886.1049844996365,226.1035643129982);
    glEnd();



    //

    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(997.8927324162092,301.7415992549942);
    glVertex2f(993.6937153877705,299.5464749151004);
    glVertex2f(994.0173254631268,231.045369912219);
    glVertex2f(997.8927324162092,231.6375991200048);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.30f, 0.62f, 0.87f);
    glVertex2f(997.0258445618001,302.7784076894231);
    glVertex2f(1074.6924786380823,302.5103884962939);
    glVertex2f(1075.4997653643734,230.2005631556514);
    glVertex2f(997.308279589327,231.1231765571269);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0,0,0);

    glVertex2f(1074.094596251157,301.8462342825902);
    glVertex2f(1079.0370199677134,299.9928253888816);
    glVertex2f(1079.2135351004474,230.7106357907255);
    glVertex2f(1074.3593689502584,230.7988933570925);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.302, 0.314, 0.341);

    glVertex2f(994.1011856655169,231.4420884437795);
    glVertex2f(1078.8441939806614,231.3404781220587);
    glVertex2f(1079.1490249458238,226.3615723577396);
    glVertex2f(994.1011856655169,225.8535207491356);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.302, 0.314, 0.341);

    glVertex2f(1066.7914080769172,226.0194242287767);
    glVertex2f(1070.9507263603523,225.8530514974393);
    glVertex2f(1071.49943416062,175.6685713882629);
    glVertex2f(1067.428473073871,175.7678631220861);
    glEnd();






}


void setting_man()
{

//dan pa

    glBegin(GL_POLYGON);
    glColor3f(1,0,0);

    glVertex2f(276.8284099394614, 251.6509942753968);
    glVertex2f(278.5944644507151, 246.4789774924398);
    glVertex2f(281.4958397192032, 241.4331074602865);
    glVertex2f(284.3972149876913, 237.9009984377792);
    glVertex2f(288.1816175118062, 235.1257699200949);
    glVertex2f(293.7320745471748, 234.2427426644681);
    glVertex2f(298.5256510777203, 233.4858621596451);
    glVertex2f(303.0669341066582, 233.1074219072336);
    glVertex2f(307.7343638863999, 233.7381556612528);
    glVertex2f(312.7802339185532, 236.0087971757218);
    glVertex2f(315.933902688649, 237.1441179329563);
    glVertex2f(320, 240);
    glVertex2f(324.2595882417018, 241.811547712698);
    glVertex2f(328.9270180214435, 244.082189227167);
    glVertex2f(333.9728880535968, 246.8574177448513);
    glVertex2f(340, 250);
    glVertex2f(344.6953618719223, 251.2725540229854);
    glVertex2f(348.3536176452334, 251.7771410262007);
    glVertex2f(352.6426071725637, 251.7771410262007);
    glVertex2f(356.1747161950709, 250.1372332657509);
    glVertex2f(358.3192109587361, 249.0019125085164);
    glVertex2f(359.832971968382, 246.7312709940474);
    glVertex2f(360.3375589715973, 243.7037489747555);
    glVertex2f(360, 240);
    glVertex2f(360.7159992240088, 236.3872374281333);
    glVertex2f(359.9591187191859, 233.2356868580375);
    glVertex2f(360, 230);
    glVertex2f(359.5806784667744, 226.4216441146306);
    glVertex2f(361.0812220047424, 223.9885212108379);
    glVertex2f(363.397735491803, 221.0310962200544);
    glVertex2f(366.385584384805, 218.4193812309153);
    glVertex2f(369.4396762469831, 215.7725016170276);
    glVertex2f(371.8829497367256, 213.8382434376481);
    glVertex2f(374.0208140402502, 211.7003791341234);
    glVertex2f(376.0568752817022, 210.3769333271796);
    glVertex2f(378.6019518335173, 208.9516964581632);
    glVertex2f(380.7398161370419, 207.5264535891467);
    glVertex2f(382.8191310427716, 208.6036721473274);
    glVertex2f(383.9480077409618, 210.1840995247937);
    glVertex2f(384.3431145853284, 212.4982967560837);
    glVertex2f(383.3271255569572, 215.3769323364687);
    glVertex2f(382.311136528586, 217.9733487423062);
    glVertex2f(381.0129283256673, 221.0777596623293);
    glVertex2f(380.1662708020246, 223.8999514078049);
    glVertex2f(378.8680625991058, 228.3590143656562);
    glVertex2f(376.6667530376349, 232.8180773235076);
    glVertex2f(374.8605503205306, 237.5593594559065);
    glVertex2f(372.2489682999013, 245.2862455772407);
    glVertex2f(368.1131069895571, 257.2070515876443);
    glVertex2f(365, 265);
    glVertex2f(363.2474718832699, 270.9930177221247);
    glVertex2f(360.9768421670025, 274.2367744596495);
    glVertex2f(356.1923009791533, 275.6964649915357);
    glVertex2f(351.4888537097423, 276.0208406652881);
    glVertex2f(346.0555611743882, 275.2099014809069);
    glVertex2f(338.7909717078735, 274.495758116199);
    glVertex2f(332.3257668397052, 272.9692453991389);
    glVertex2f(326.3095108371741, 271.8019121449165);
    glVertex2f(321.1912034917372, 271.0835532192411);
    glVertex2f(317.5994088633605, 270.1856045621469);
    glVertex2f(313.4688450407271, 268.5692969793774);
    glVertex2f(310.8076391429792, 268.1309147833659);
    glVertex2f(307.9637949269898, 268.1309147833659);
    glVertex2f(306.2574883973961, 269.3632472769613);
    glVertex2f(304.2667974462034, 269.3632472769613);
    glVertex2f(302.0865168806115, 268.5100940121645);
    glVertex2f(298.3895193998252, 266.9933770969701);
    glVertex2f(295, 265);
    glVertex2f(290.0770293836112, 262.8184771658482);
    glVertex2f(285.7588668403457, 260.7532689929822);
    glVertex2f(282.8317721350466,257.5824315186333);
    glVertex2f(279.7020463617296,255.6118634391374);

    glEnd();



    //bam pa
    glBegin(GL_POLYGON);
    glColor3f(0.639, 0.071, 0.114);

    glVertex2f(336.4962356931865, 230.4513883003687);
    glVertex2f(336.801216782903, 224.7620499117648);
    glVertex2f(336.801216782903, 219.3774975082646);
    glVertex2f(337.1058076633941, 212.5706105076135);
    glVertex2f(337.6137843052337, 202.8174589842925);
    glVertex2f(338.629737588913, 196.7217392822169);
    glVertex2f(340, 190);
    glVertex2f(341.271216126479, 183.2095606092826);
    glVertex2f(342.5919553952621, 178.0281988625184);
    glVertex2f(344.5222666342527, 173.5580044143296);
    glVertex2f(346.3509825448754, 171.9324791604427);
    glVertex2f(349.0940564108093, 171.627693175339);
    glVertex2f(351.3291536349037, 172.4404558022284);
    glVertex2f(352.1419162618471, 177.0122455788391);
    glVertex2f(352.5482975753188, 182.8031792958109);
    glVertex2f(352.8530835604227, 188.289327027679);
    glVertex2f(353.3610602022623, 194.5882373864905);
    glVertex2f(354.2754181575736, 200.1759804467264);
    glVertex2f(355.2913714412529, 205.4589375218586);
    glVertex2f(356.510515381668, 211.2498712388305);
    glVertex2f(357.5264686653472, 215.8216610153872);
    glVertex2f(358.4408266206586, 221.2062134188873);
    glVertex2f(359.4567799043379, 226.1843845089157);
    glVertex2f(360.0663518745454, 232.9912715095668);
    glVertex2f(360, 240);
    glVertex2f(359.6599705610737, 245.4874969898219);
    glVertex2f(357.3232780086114, 249.449717405171);
    glVertex2f(354.6817994710453, 251.5832166008975);
    glVertex2f(350.922772321432, 253.0055511980485);
    glVertex2f(346.858959186715, 252.7007652129447);
    glVertex2f(342.7951460519979, 251.7864072576333);
    glVertex2f(340, 250);
    glVertex2f(336.4962356931865, 248.2305707647559);
    glVertex2f(331.5180646031581, 245.8938782122936);
    glVertex2f(326.9462748266014, 243.3539950030954);
    glVertex2f(322.3744850500448, 240.9157071222652);
    glVertex2f(317.802695273488, 239.0869912116425);
    glVertex2f(314.6532400940823, 237.7662519428594);
    glVertex2f(313.2309054969314, 236.8518939875481);
    glVertex2f(315.9739793628654, 236.6487033380122);
    glVertex2f(319.4282205273749, 236.2423220173405);
    glVertex2f(323.0856523486202, 236.0391313606046);
    glVertex2f(327.454251468441, 235.1247734052933);
    glVertex2f(329.8925933492713, 234.4136061067178);
    glVertex2f(333.4483758421487, 233.6008434797744);
    glVertex2f(334.8707104392997, 232.5848901960951);
    glEnd();

    //
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.6f, 0.0f);
    glVertex2f(302.7330518362961, 330.09529083828501);
    glVertex2f(305.1699216978317, 329.0799283905436);
    glVertex2f(306.6929653612916, 328.1661021924678);
    glVertex2f(309.0282987859966, 327.9630297040064);
    glVertex2f(312.5280675266695, 327.3538122338625);
    glVertex2f(314.6127924112825, 327.3538122338625);
    glVertex2f(316.5419810516649, 327.3538122338625);
    glVertex2f(316.948162085875, 325.6276960860714);
    glVertex2f(317.5573434939714, 323.2923624693694);
    glVertex2f(317.9634884708941, 319.9416664099748);
    glVertex2f(318.572705936278, 317.3017240597879);
    glVertex2f(319.2915226488377, 313.1641480241838);
    glVertex2f(320.0, 310.0);
    glVertex2f(319.1688728554664, 305.5598608351633);
    glVertex2f(320.0, 300.0);
    glVertex2f(319.782121822323, 296.4837761256873);
    glVertex2f(319.5368222355803, 292.5589827378058);
    glVertex2f(319.194944195222, 289.4532526728342);
    glVertex2f(318.929932401367, 286.7927054462829);
    glVertex2f(318.929932401367, 284.7666966404269);
    glVertex2f(318.841845061982, 282.4764258164157);
    glVertex2f(318.3920894733575, 279.8668232027734);
    glVertex2f(317.9713028205672, 276.8371593026833);
    glVertex2f(317.890441761027, 274.8173833629898);
    glVertex2f(316.7931001927544, 273.1342367581287);
    glVertex2f(314.6050959598249, 272.3768207831061);
    glVertex2f(310.565457731458, 271.6194048080836);
    glVertex2f(307.6199511619259, 271.0303034944172);
    glVertex2f(305.0, 270.0);
    glVertex2f(301.8972526839779, 268.7580555691096);
    glVertex2f(299.5408474283522, 267.4956956107387);
    glVertex2f(296.3197018101524, 266.1491783218097);
    glVertex2f(293.3973629766138, 265.055133024555);
    glVertex2f(290.956779114301, 263.1195144217196);
    glVertex2f(287.7753305965759, 261.5741737115515);
    glVertex2f(285.1571123327154, 259.92056217648404);
    glVertex2f(282.9522969526186, 258.5425525639212);
    glVertex2f(281.0230834950357, 256.4755381450823);
    glVertex2f(278.4048652311732, 253.9951208424785);
    glVertex2f(275.9244479285666, 252.7549121911725);
    glVertex2f(273.7196325484718, 251.7511400675942);
    glVertex2f(272.7550258196804, 261.4363727502955);
    glVertex2f(272.7550258196804, 265.432060267173);
    glVertex2f(274.546433160074, 274.2518621470963);
    glVertex2f(276.4765517735902, 278.6614929072858);
    glVertex2f(278.2670642699172, 285.4137400088259);
    glVertex2f(278.5426661942491, 292.1659871103661);
    glVertex2f(277.8536613861495, 299.0560351731622);
    glVertex2f(277.5780594636377, 304.2924717008872);
    glVertex2f(277.5896106658209, 307.1925284518204);
    glVertex2f(276.9388387118373, 311.314084160638);
    glVertex2f(276.6134527348463, 315.2187158842786);
    glVertex2f(275.9626807808631, 318.47257565451942);
    glVertex2f(274.878606857558, 321.6179734317791);
    glVertex2f(273.9010929265833, 324.4379852323726);
    glVertex2f(276.7649405816281, 325.2623355405767);
    glVertex2f(278.753168249295, 325.4680142648181);
    glVertex2f(281.9754682624103, 327.1134440587493);
    glVertex2f(283.7580172058358, 329.0331121516691);
    glVertex2f(285.1503134140283, 327.3059144892508);
    glVertex2f(287.1244138788944, 325.5687060801686);
    glVertex2f(289.651262473923, 324.3052817826543);
    glVertex2f(292.2570750875462, 322.8049654293561);
    glVertex2f(294.7049596639802, 322.5680733735722);
    glVertex2f(297.3107722776034, 322.7260014107615);
    glVertex2f(300, 325);
    glVertex2f(300.943171132957, 327.3059144892508);
    glVertex2f(301.4687329523649, 328.7491420854211);

    glEnd();


    //jama

    glBegin(GL_POLYGON);
    glColor3f(1,1,0);

    glVertex2f(278.0735561583649, 308.7495076282405);
    glVertex2f(281.5158981008444, 314.8518410717268);
    glVertex2f(283.8629494252622, 320.015353985446);
    glVertex2f(285.9298143309137, 323.2989513938978);
    glVertex2f(286.629771225153, 325.5838003305084);
    glVertex2f(288.2382419402848, 324.297023758403);
    glVertex2f(289.9753903126271, 323.653654723504);
    glVertex2f(292.4846046282326, 324.1683461011925);
    glVertex2f(293.7070423717327, 322.5598753860608);
    glVertex2f(295, 320);
    glVertex2f(295.1780503714457, 317.2428525007407);
    glVertex2f(294.5612278841426, 315.1867775430638);
    glVertex2f(294.4584241362588, 312.6166838459676);
    glVertex2f(294.3556203883749, 309.0185526700329);
    glVertex2f(293.5331904053041, 305.4204214940983);
    glVertex2f(292.4023491785818, 301.1026640829767);
    glVertex2f(290.8602929603241, 296.6821029239713);
    glVertex2f(289.2154329941824, 293.0839717480366);
    glVertex2f(288.2901992632278, 289.45840572102);

    glVertex2f(287.5705730280409, 286.9157468750058);
    glVertex2f(285.9257130618993, 284.756868169445);
    glVertex2f(284.5892643394093, 283.1120082033035);
    glVertex2f(283.2528156169192, 281.1587369935103);
    glVertex2f(281.8135631465453, 278.691447044298);
    glVertex2f(279.9630956846361, 276.3269608429695);
    glVertex2f(278.0098244748429, 274.9905121240795);
    glVertex2f(276.2621607608175, 274.1680821374087);
    glVertex2f(273.4864595679536, 273.6540633979895);
    glVertex2f(270.1967396356704, 273.7568671458733);
    glVertex2f(267.3182346949226, 274.1680821374087);
    glVertex2f(264.4397297541749, 275.6073346077826);
    glVertex2f(262.7948697880333, 280.0278957667881);
    glVertex2f(261.7668323091948, 284.8596719173289);
    glVertex2f(261.6640285613109, 290.7194855467081);
    glVertex2f(262.2808510486141, 294.6260279662943);
    glVertex2f(263.2060847795687, 299.4578041168352);
    glVertex2f(263.6172997711041, 303.1587390406536);
    glVertex2f(263.7201035189879, 307.9905151911945);
    glVertex2f(263.2060847795687, 311.5886463671291);
    glVertex2f(264.2341222584072, 316.6260300134376);
    glVertex2f(266.5986084597357, 321.2521986682108);
    glVertex2f(269.9911321399027, 324.0278998610746);
    glVertex2f(273.4864595679536, 325.0559373399131);
    glVertex2f(274.5144970467921, 322.2802361470492);
    glVertex2f(275.234132281979, 320.5325724330239);
    glVertex2f(275.234132281979, 317.9624787359277);
    glVertex2f(275.7481420213982, 315.3923850388315);
    glVertex2f(276.1593570129336, 312.4110763501999);
    glVertex2f(276.3649645087014, 309.9437864009876);


    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0,0,0);
    glVertex2f(267.9232412314689, 296.3847858957182);
    glVertex2f(270.0, 300.0);
    glVertex2f(272.1394715641316, 303.5480308858391);
    glVertex2f(274.313028401654, 304.9692026642191);
    glVertex2f(276.6537819189858, 307.560751201265);
    glVertex2f(278.2441931733678, 308.3814388067476);

    glEnd();


//bam hat

    glBegin(GL_POLYGON);
    glColor3f(1,1,0);

    glVertex2f(324.4039237613899, 285.171125990694);
    glVertex2f(320.6559209080099, 282.672457421774);
    glVertex2f(315.5336503417238, 279.549127110624);
    glVertex2f(312.0351543452358, 277.425253427042);
    glVertex2f(308.9121786340858, 274.426851144338);
    glVertex2f(307.7877777807178, 272.677783146094);
    glVertex2f(308.2875114918558, 270.678848290958);
    glVertex2f(309.4119123478698, 267.930312865146);
    glVertex2f(312.1604477736818, 267.8053794367);
    glVertex2f(316.2832509123998, 269.804314291836);
    glVertex2f(320.0, 270.0);
    glVertex2f(323.1545894769299, 272.053116003864);
    glVertex2f(328.276860043216, 272.927650002986);
    glVertex2f(332.399663181934, 274.052050859);
    glVertex2f(335.398065464638, 274.052050859);
    glVertex2f(338.646334604234, 275.051518285668);
    glVertex2f(341.98102982074, 276.0349432844032);
    glVertex2f(342.7477384320214, 279.6764526716534);
    glVertex2f(341.8852735508306, 283.6054593526339);
    glVertex2f(341.310296963637, 288.588589777292);
    glVertex2f(339.4895377697449, 292.3259375957857);
    glVertex2f(337.2854608511461, 296.3507737080096);
    glVertex2f(334.6980662075736, 301.142452701809);
    glVertex2f(332.781477582705, 307.0836700072733);
    glVertex2f(330.3857418106194, 312.6417770139392);
    glVertex2f(328.277494314264, 316.6666131316159);
    glVertex2f(325.9775879644217, 320.9798375375701);
    glVertex2f(324.0609933959531, 323.8538204748728);
    glVertex2f(321.6652635584675, 326.7287034121756);
    glVertex2f(319.26952777373818, 327.1120211371493);
    glVertex2f(317.065450858783, 327.1120211371493);
    glVertex2f(317.6404274462435, 324.8121147873071);
    glVertex2f(318.1195746024607, 322.4163790062214);
    glVertex2f(318.5028932734434, 319.1581783494499);
    glVertex2f(319.0778691849494, 315.6124898379827);
    glVertex2f(319.5570160711121, 311.4918238444708);
    glVertex2f(319.2695277773818, 307.7544760259772);
    glVertex2f(319.2695277773818, 304.3046165012139);
    glVertex2f(320.0, 300.0);
    glVertex2f(319.7486749335989, 298.0750347303912);
    glVertex2f(320.3236515210595, 295.967459830359);
    glVertex2f(319.7486749335989, 294.242562206542);
    glVertex2f(321.3777752674372, 292.9009141832462);
    glVertex2f(322.4318998008414, 291.271813852108);
    glVertex2f(323.1985348545363, 289.3552252272395);
    glVertex2f(323.7074598055281, 287.5149736431987);


    glEnd();

//muk

    glBegin(GL_POLYGON);
    glColor3f(0.686, 0.267, 0.231);
    glVertex2f(284.7993053516947, 336.8920434825046);
    glVertex2f(283.5923757005855, 337.49550380308592);
    glVertex2f(281.7819812232917, 339.5645305671035);
    glVertex2f(280, 340);
    glVertex2f(278.7646570961486, 339.0472750023424);
    glVertex2f(279.7129589648773, 337.4092990472657);
    glVertex2f(281.3509349199541, 336.1161601353629);
    glVertex2f(282.6440738318568, 335.2540675272478);
    glVertex2f(284.1096312653466, 334.8230212234602);
    glVertex2f(285.7476072204234, 334.3919749194926);
    glVertex2f(287.3855831755001, 333.4436730505764);
    glVertex2f(288.5925128266094, 332.4091619212418);
    glVertex2f(289.4546054345445, 331.3746507917196);
    glVertex2f(290, 330);
    glVertex2f(291.9546739975565, 328.9607914895012);
    glVertex2f(292.9029758662852, 327.8400710991855);
    glVertex2f(293.2478129094592, 325.7710488401412);
    glVertex2f(295, 325);
    glVertex2f(296.8686018627868, 325.1675840145866);
    glVertex2f(299.9721352513534, 325.6848395793476);
    glVertex2f(301.1790649024626, 328.3573266663466);
    glVertex2f(302.4161020916879, 330.1579201089646);
    glVertex2f(303.1780802868705, 332.6196958146793);
    glVertex2f(303.6469899454443, 335.3159263532972);
    glVertex2f(303.5781875217279, 338.6916539299597);
    glVertex2f(303.3395270814733, 341.5555579730145);
    glVertex2f(303.0213135211338, 343.8626242854754);
    glVertex2f(302.384886400455, 345.6923522574271);
    glVertex2f(302.146226302032004, 349.1131480371059);
    glVertex2f(301.7764396139088, 351.8107377010338);
    glVertex2f(301.609200308025, 353.9848489115221);
    glVertex2f(301.107483633739, 355.6572421503592);
    glVertex2f(300.3270321582499, 356.2704530045995);
    glVertex2f(298.3337312588565, 356.2704530045995);
    glVertex2f(297.7694941740545, 355.9359734568321);
    glVertex2f(296.6477670328081, 355.2670170612972);
    glVertex2f(295.755823972095, 354.4865668831732);
    glVertex2f(294.4763558232198, 353.7061167050492);
    glVertex2f(293.4702198790175, 353.7061167050492);
    glVertex2f(290.9616300207618, 353.7618631463438);
    glVertex2f(288.3979237212114, 354.0963417944112);
    glVertex2f(286.9478862475526, 354.1520882354058);
    glVertex2f(285.4984787738937, 353.5946238224601);
    glVertex2f(284.3278035060777, 352.3124556726849);
    glVertex2f(283.1013817982271, 350.3055837860803);
    glVertex2f(282.7660931504597, 348.521697664654);
    glVertex2f(282.3766780613977, 346.3475864541658);
    glVertex2f(282.3766780613977, 345.39989695352158);
    glVertex2f(282.54391378352814, 343.5045179481426);
    glVertex2f(283.26682111221108, 341.887711506);
    glVertex2f(283.6038975071896, 340.9691967865444);
    glVertex2f(284, 340);
    glVertex2f(284.471054645193, 338.9699178294812);
    glVertex2f(284.832370119361,338.1750237863115);

    glEnd();


//chul

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);

    glVertex2f(279.4223320266592, 340.7431477334986);
    glVertex2f(280.8471983402529, 340.7431477334986);
    glVertex2f(282.1830105092471, 339.4963897091041);
    glVertex2f(283.4297678536417, 337.9824692509106);
    glVertex2f(284.4093614242374, 336.9138195151753);
    glVertex2f(284.9970290120967, 337.82685156582982);
    glVertex2f(284.3745210941721, 339.5112884479768);
    glVertex2f(283.5689226121519, 340.4635578127373);
    glVertex2f(283.7999422429508, 342.0379346324946);
    glVertex2f(282.2852938496829, 344.5626849173767);
    glVertex2f(282.430768894059, 346.5993355386432);
    glVertex2f(282.7702106642702, 348.7329695228271);
    glVertex2f(283.497585886151, 351.3030286401395);
    glVertex2f(284.8553529696953, 353.0972208541123);
    glVertex2f(287.2799370399316, 354.3095128905804);
    glVertex2f(288.8801625280694, 353.9700711203694);
    glVertex2f(290.6258360605835, 353.8730877575419);
    glVertex2f(292.2745823031802, 353.4851543057821);
    glVertex2f(294.4082142143641, 354.1155461647455);
    glVertex2f(296.5903398800067, 355.9582300601771);
    glVertex2f(298.9664322714842, 356.7340969635167);
    glVertex2f(300.227215989411, 356.5886219191405);
    glVertex2f(301.294032981503, 355.085379793992);
    glVertex2f(302.2153749292187, 352.46682899951489);
    glVertex2f(303.0397335140171, 349.1693946555956);
    glVertex2f(303.5246530286043, 347.6176608429764);
    glVertex2f(304.5502478377132, 349.2485773452622);
    glVertex2f(304.5210050042686, 351.1493615191674);
    glVertex2f(305, 355);
    glVertex2f(304.9496198140056, 358.6631658284328);
    glVertex2f(303.8387929239678, 361.0019003337756);
    glVertex2f(302.0847420449608, 362.5220777622483);
    glVertex2f(299.0488592572208, 364.1091986961081);
    glVertex2f(296.338202950918, 365.1584850082253);
    glVertex2f(293.1903440145663, 365.2459255342351);
    glVertex2f(290, 365);
    glVertex2f(287.244388245902, 365.1584850082253);
    glVertex2f(284.0965293095503, 364.2840797481276);
    glVertex2f(281.2983424772377, 362.7101502799518);
    glVertex2f(279.4621814310326, 361.5734234418248);
    glVertex2f(277.5348898588177, 359.4748508175903);
    glVertex2f(276.4892035467004, 358.075802401434);
    glVertex2f(274.5655119744855, 356.4144324072484);
    glVertex2f(272.4669393502511, 355.1028245171019);
    glVertex2f(270.980450408085, 353.0916924188772);
    glVertex2f(271.41765303381338, 351.3428818986818);
    glVertex2f(270.4558072520264, 348.8945471704083);
    glVertex2f(269.7562830439483, 346.5336529681445);
    glVertex2f(270.7181288300557, 344.9597234999687);
    glVertex2f(272.9915825063097, 342.7737103497245);
    glVertex2f(274.1283093444367, 341.811864563617);
    glVertex2f(275, 340);
    glVertex2f(276.3143224946809, 337.6147193151481);
    glVertex2f(277.7843899170717, 336.3967720217591);
    glVertex2f(279.3096631279942, 336.0917173795746);
    glVertex2f(279.1789254242008, 337.5298321213015);
    glVertex2f(278.5314012015085, 338.8013986069678);
    glVertex2f(278.3947143284678, 339.8778077321638);
    glVertex2f(278.8902042432405, 340.5270703791073);


    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);

    glVertex2f(346.060237646496, 171.2739551711264);
    glVertex2f(346, 168);
    glVertex2f(345.7991205456145, 165.7034570189901);
    glVertex2f(346.3648742641909, 164.4413910313967);
    glVertex2f(347.1917450836487, 163.8756373128204);
    glVertex2f(348.8890062393778, 163.6145202111939);
    glVertex2f(351.0649820800561, 163.5274811783119);
    glVertex2f(353.2409579207344, 163.5710006951254);
    glVertex2f(355.6780508622942, 163.5710006951254);
    glVertex2f(357.6799486357182, 164.0932348968882);
    glVertex2f(357.7234681525318, 165.7904960526172);
    glVertex2f(356.9836363667012, 166.617366872075);
    glVertex2f(355.6780508622942, 167.487572083463);
    glVertex2f(354.2854263242601, 167.7488743092277);
    glVertex2f(353.066879534802, 168.2275889941769);
    glVertex2f(352.0224114499546, 168.7933427127532);
    glVertex2f(351.4131382145646, 169.4026159481431);
    glVertex2f(350.8038649791747, 170.3600453180416);
    glVertex2f(350.6297869119205, 171.5350722720078);
    glVertex2f(350, 172);
    glVertex2f(348.9325257561914, 171.9702674401435);
    glVertex2f(347.4963817013436, 172.013786956957);


    glEnd();

//

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(381.3630178347586, 207.2240286537358);
    glVertex2f(382.6400766319944, 205.7177541756527);
    glVertex2f(383.5569393571842, 204.3097149898614);
    glVertex2f(384.3428216935754, 203.1636365828313);
    glVertex2f(385.4561530053463, 202.2467738565915);
    glVertex2f(386.7332138000988, 202.2467738565915);
    glVertex2f(388.1739980834827, 203.5238326532272);
    glVertex2f(389.6147823668666, 204.7354012551637);
    glVertex2f(391.2520372343484, 206.1106953438483);
    glVertex2f(392.6928215177323, 207.7806953086796);
    glVertex2f(393.8716450223192, 208.9276773159168);
    glVertex2f(394.5920371640112, 210.2038325152552);
    glVertex2f(393.5769391461725, 210.8914795568948);
    glVertex2f(392.6928215177323, 210.9897148489437);
    glVertex2f(391.5467431104951, 210.5640285833953);
    glVertex2f(390.5316450926565, 209.9746168331151);
    glVertex2f(389.582037269517, 209.5161854682102);
    glVertex2f(388.5014490569791, 209.0250090079657);
    glVertex2f(387.3553706497418, 209.0250090079657);
    glVertex2f(386.2092922425046, 209.0904992026649);
    glVertex2f(385.4234099061134, 209.8108193443569);
    glVertex2f(384.735762861771, 210.072852123154);
    glVertex2f(384.0808609147783, 209.6144207602591);
    glVertex2f(383.2294883836879, 208.9922639106161);
    glVertex2f(382.6400766319444, 208.370107060973);




    glEnd();



}

void settingman2()
{
    if(isDay && isVisible)
    {
        glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex2f(478.7353394153849, 230.8507980841908);
    glVertex2f(477.9487147427201, 225.4757139876486);
    glVertex2f(477.8176421306093, 219.0518329942230);
    glVertex2f(478.6042398032741, 213.1523504942348);
    glVertex2f(479.6530376001604, 208.1705618902494);
    glVertex2f(480.5707339849359, 202.2710826440396);
    glVertex2f(481.4884312697115, 195.5850024263895);
    glVertex2f(482.2750289423763, 191.5209144509552);
    glVertex2f(483.0616266150414, 187.0635276391884);
    glVertex2f(484.1104235119273, 183.654937724308);
    glVertex2f(486.863515366254, 180.77074625787807);
    glVertex2f(491.7142010143533, 180.639646465746);
    glVertex2f(496.4337870503418, 180.639646457657);
    glVertex2f(500.104576189444, 182.0817423789786);
    glVertex2f(501.153370863033, 186.5391919079453);
    glVertex2f(501.153370863033, 193.0941097626846);
    glVertex2f(501.2844726984411, 199.9118296260454);
    glVertex2f(501.02273474742195, 205.679672558992);
    glVertex2f(501.6777715347734, 212.1035535532485);
    glVertex2f(501.9399707589995, 218.3963349336662);
    glVertex2f(502.071073711058, 224.5580167028731);
    glVertex2f(502.4643692074382, 230.5885898599692);
    glVertex2f(502.8576608437706, 236.0947825688222);
    glVertex2f(501.5466719226627, 243.4363608486262);
    glVertex2f(498.6624804562252, 248.9425445554792);
    glVertex2f(496.3026874382321, 252.744433306692);
    glVertex2f(492.500798687018, 254.8420271004645);
    glVertex2f(481.7506304939393, 257.3329197305694);
    glVertex2f(475.7200483363637, 258.3817166274557);
    glVertex2f(471.3937611371806, 258.9061150758989);
    glVertex2f(468.6406689288539, 259.5616131364528);
    glVertex2f(464.3143820831978, 259.430513524342);
    glVertex2f(459.9880948835416, 261.2659080938939);
    glVertex2f(457.890501089769, 262.4458046028901);
    glVertex2f(456.0551065202179, 263.6257011118871);
    glVertex2f(455.3996084596639, 260.8726092575606);
    glVertex2f(455.2685088475531, 257.7262185669018);
    glVertex2f(455.5307080717747, 253.5310309793566);
    glVertex2f(455.6618076388855, 249.7291422281439);
    glVertex2f(456.4484053656503, 245.6650542527095);
    glVertex2f(458.1527003139906, 242.3875639499399);
    glVertex2f(460, 240);
    glVertex2f(462.4789875136467, 236.8813802412869);
    glVertex2f(466.1497766527489, 233.6038899385173);
    glVertex2f(470.476053852405, 231.8995949810771);
    glVertex2f(475.4578491126151, 231.2440969205231);



    glEnd();


// leg 2
    glBegin(GL_POLYGON);
    glColor3f(1,1,1);

    glVertex2f(525.963008616591, 233.5830305274182);
    glVertex2f(526.2432773538925, 225.5953713709015);
    glVertex2f(525.542605503029, 219.2893246683883);
    glVertex2f(527.0840835859267, 212.0023373677064);
    glVertex2f(527.3643523282607, 203.7344094688558);
    glVertex2f(527.6446210705946, 196.5875565393408);
    glVertex2f(528.0650241840955, 191.6828353484972);
    glVertex2f(528.519620220032, 188.0260710779385);
    glVertex2f(530.9410572324273, 186.8153525717409);
    glVertex2f(534.331069497806, 185.9274923338627);
    glVertex2f(537.3982255988145, 185.766063199703);
    glVertex2f(541.0303781174074, 185.766063199703);
    glVertex2f(544.258960800601, 186.8960671388207);
    glVertex2f(545.9539670927777, 189.0753604499764);
    glVertex2f(546.7611123800762, 195.2903821151238);
    glVertex2f(546.8418269471559, 200.0525415728342);
    glVertex2f(547.1646852154753, 205.1375592988639);
    glVertex2f(547.4875434837946, 209.4154313540953);
    glVertex2f(547.6489726179544, 214.4197345130451);
    glVertex2f(548.1332600204335, 219.6661813732345);
    glVertex2f(548.6623722107415, 224.5568148793009);
    glVertex2f(550, 230);
    glVertex2f(550.1749846469176, 235.8173741263883);
    glVertex2f(550.4270867196135, 241.279585701468);
    glVertex2f(550, 245);
    glVertex2f(547.6539639199576, 248.9266819065795);
    glVertex2f(544.5447050233736, 252.2040088516274);
    glVertex2f(541.6875481994856, 253.3804851908753);
    glVertex2f(538.1581191817417, 255.0611656755152);
    glVertex2f(531.4446758714641, 258.0249557901436);
    glVertex2f(526.149032204444, 258.4701412831803);
    glVertex2f(519.943603226016, 258.5894764176886);
    glVertex2f(514.8121924421621, 258.5894764176886);
    glVertex2f(510.7547978688822, 258.2314710141638);
    glVertex2f(506.8167384301106, 258.1121358796556);
    glVertex2f(502.6400087223225, 256.7994494000652);
    glVertex2f(499.1792988215838, 256.3221088620323);
    glVertex2f(495.3231739757075, 255.032013324382);
    glVertex2f(494.0847222959673, 253.690375541053);
    glVertex2f(496.1488081288676, 252.3487197496679);
    glVertex2f(498.3160982534131, 250.9038596666377);
    glVertex2f(500.2769797946684, 248.0141395005773);
    glVertex2f(501.5154312944086, 243.7827635431317);
    glVertex2f(502.1346570442788, 240.7898390854263);
    glVertex2f(502.4442699192138, 237.074845862058);
    glVertex2f(502.6506785025039, 234.90719446616605);
    glVertex2f(504.9211729186943, 234.39117300334355);
    glVertex2f(508.739731709956, 234.7007858783705);
    glVertex2f(511.7326561672655, 234.7007858783705);
    glVertex2f(515.7576235414213, 234.90719446616605);
    glVertex2f(519.6793866239319,234.9071944616605);
    glVertex2f(522.5691067899925,234.3911730034355);
    glEnd();


    //body

    glBegin(GL_POLYGON);
    glColor3f(0.251, 0.294, 0.471);
    glVertex2f(503.2132839424972, 321.5188301513631);
    glVertex2f(500.1872011075878, 317.8050017698836);
    glVertex2f(499.4994551110175, 313.9536241890901);
    glVertex2f(500, 310);
    glVertex2f(502.3879882966128, 306.8010658247592);
    glVertex2f(505.6891690801503, 304.8753770343625);
    glVertex2f(509.2654482623159, 304.8753770343625);
    glVertex2f(514.2172194376221, 306.6635166254452);
    glVertex2f(516.9680234239034, 309.4145006117263);
    glVertex2f(519.4440890115566, 313.2658781925198);
    glVertex2f(522.6077205957799, 314.5038209863463);
    glVertex2f(523.4301579166444, 309.9466947089825);
    glVertex2f(524.3958601868682, 307.2137134227014);
    glVertex2f(525.0836061834331, 302.9496882439657);
    glVertex2f(524.5334093861679, 298.5481138656916);
    glVertex2f(523.2954665925303, 295.1093838830646);
    glVertex2f(522.3326221971519, 291.6706539002132);
    glVertex2f(521.2322286026393, 288.2319231973618);
    glVertex2f(520.5444826060691, 285.2058415324527);
    glVertex2f(520.1318350081268, 282.4548575461716);
    glVertex2f(518.2037079557693, 279.9424688969263);
    glVertex2f(516.4691392606662, 277.3862239832165);
    glVertex2f(514.2781051194834, 275.0162420786018);
    glVertex2f(513.000001870746, 272.912901026635);
    glVertex2f(511.8131917106526, 270.7218668834522);
    glVertex2f(511.0828469969925, 269.1698843687811);
    glVertex2f(510.0786230155496, 267.4353156736781);
    glVertex2f(509.0743990341741, 265.8833331575007);
    glVertex2f(507.4297048689548, 263.6965333159914);
    glVertex2f(505.7811334650435, 261.3883535345116);
    glVertex2f(504.242468213929, 259.1902581489006);
    glVertex2f(501.7146573353954, 257.874102577716);
    glVertex2f(498.197750070512, 257.1026077039463);
    glVertex2f(494.1312288774032, 257.1020677039463);
    glVertex2f(488.9657051451475, 257.2119724642071);
    glVertex2f(483.3606523718489, 257.4371819847286);
    glVertex2f(478.744562440897, 257.8714010257716);
    glVertex2f(473.9087529894237, 258.8605438681183);
    glVertex2f(470, 260);
    glVertex2f(467.2265404888971, 259.6335452580852);
    glVertex2f(464.6348944321146, 259.9445433320991);
    glVertex2f(462.2505758646747, 260.3592074307842);
    glVertex2f(459.3479271737883, 261.4995337021685);
    glVertex2f(456.9560506368875, 262.4337291169109);
    glVertex2f(455.6868109489898, 265.7881482920691);
    glVertex2f(456.5934107260596, 270.5024671328319);
    glVertex2f(458.3159530324923, 275.0354660181808);
    glVertex2f(459.6758499680971, 278.480545171046);
    glVertex2f(461.2170695895118, 283.0135440563959);
    glVertex2f(461.3072956688228, 287.2745630086229);
    glVertex2f(462.7582892101345, 291.6262419385579);
    glVertex2f(465.0247886528091, 296.1592408239068);
    glVertex2f(467.2006281777767, 300.0576198685306);
    glVertex2f(469.6484475158652, 303.8653389298999);
    glVertex2f(472.4589068247817, 308.035679035209);
    glVertex2f(475.3600611114052, 311.6620970118);
    glVertex2f(478.1704854203217, 314.3818963430094);
    glVertex2f(482.3408443948429, 317.3736756073397);
    glVertex2f(486.3298834139501, 319.5495150723071);
    glVertex2f(490.2282624553504, 321.0000747156188);
    glVertex2f(494.8519213148645, 322.1786544258095);
    glVertex2f(498.3130163520223, 322.9039342476454);
    glVertex2f(501.1981975787954, 323.3572341636002);




    glEnd();

//hat

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);

    glVertex2f(487.5312289893979, 269.4923862821861);
    glVertex2f(492.5389020041038, 266.491061260686);
    glVertex2f(496.1609731418228, 265.8997027077763);
    glVertex2f(499.6352046412677, 265.7518630694888);
    glVertex2f(502.813756864164, 265.8997027077763);
    glVertex2f(505, 265);
    glVertex2f(506.8562990392136, 264.6380119104996);
    glVertex2f(508.6890218277374, 264.8601601272904);
    glVertex2f(510.8549696444472, 265.0267712898834);
    glVertex2f(512.1878562421917, 264.4714007479066);
    glVertex2f(513.2985973261456, 263.5272708265459);
    glVertex2f(513.6873567055294, 261.916696254813);
    glVertex2f(513.7984308139248, 260.0839734662894);
    glVertex2f(513.6873567055294, 258.0463951515726);
    glVertex2f(512.8543008925641, 256.5851390518351);
    glVertex2f(511.8546339170056, 256.0297685098582);
    glVertex2f(510.5217446162611, 255.7520832388698);
    glVertex2f(509.0222441529235, 256.3629908350443);
    glVertex2f(507.9115030689698, 256.3629908350443);
    glVertex2f(506.7452249308183, 255.80762029230675);
    glVertex2f(505, 255);
    glVertex2f(502.421568946762, 255.2153074871068);
    glVertex2f(500.4357300506815, 254.9914334816432);
    glVertex2f(497.6190384492651, 254.2971732254841);
    glVertex2f(495.787927841557, 254.2649601510993);
    glVertex2f(493.4402095734788, 254.2649601510993);
    glVertex2f(490.3970570778219, 254.2649601510993);
    glVertex2f(486.7451768830327, 254.2649601510993);
    glVertex2f(483.354152735874, 254.2649601510993);
    glVertex2f(480.0500631925834, 254.2649601510993);
    glVertex2f(476.572082546949, 254.52580873634413);
    glVertex2f(473.0071513883539, 255.221409464042);
    glVertex2f(470.2247664780393, 256.8734460045193);
    glVertex2f(468.3988263806449, 261.6556700691228);
    glVertex2f(467.9640787384082, 267.3073941819996);
    glVertex2f(467.9640787384082, 272.611310653487);
    glVertex2f(468.137977953029, 278.0021814172218);
    glVertex2f(468.2249723375202, 283.0452540671673);
    glVertex2f(468.7466244944342, 288.6969734346241);
    glVertex2f(469.0074370797763, 292.6965172482815);
    glVertex2f(469.5291702504603, 296.0876833342676);
    glVertex2f(470.6595141202577, 300.5221092850817);
    glVertex2f(471.8768075185385, 304.4343830652118);
    glVertex2f(473.87664466728273, 308.6953649591312);
    glVertex2f(476.4851325262475, 311.8255479832353);
    glVertex2f(480.137021270358, 313.5645355218189);
    glVertex2f(483.0932968682454, 313.5645355218189);
    glVertex2f(485.5278834874709, 312.5211442108139);
    glVertex2f(487.2668740537687, 310.2604654711832);
    glVertex2f(488.65806650588751, 306.2607781626058);
    glVertex2f(489.1797636795591, 302.174105325581);
    glVertex2f(489.3536627364538, 297.4788757894249);
    glVertex2f(489.0058646226645, 294.0878441797988);
    glVertex2f(488.5711169804278, 291.2185097412168);
    glVertex2f(488.3102686395085, 287.7405286033234);
    glVertex2f(487.6146721675707, 286.0015380343767);
    glVertex2f(487.3583235828165, 283.3061026525093);
    glVertex2f(487.1799245252703, 280.3498168852999);
    glVertex2f(487.2668740537687, 276.3501403767224);
    glVertex2f(487.092974996823, 273.5677554664077);
    glEnd();


//gola

    glBegin(GL_POLYGON);
    glColor3f(0.518, 0.404, 0.349);
    glVertex2f(502.2274870200504, 320.3815013414608);
    glVertex2f(500.2168326894073, 317.6714889827682);
    glVertex2f(500, 315);
    glVertex2f(500.1294129359011, 312.4263037723954);
    glVertex2f(501.0036104709633, 309.4540321531842);
    glVertex2f(502.1400672665441, 307.6182173295538);
    glVertex2f(503.276524062125, 306.3943407804668);
    glVertex2f(505, 305);
    glVertex2f(506.6858944488674, 304.034007435799);
    glVertex2f(508.7839685330167, 304.20884694628115);
    glVertex2f(507.1229932163985, 308.4049951111097);
    glVertex2f(505.724277160299, 311.2898469768147);
    glVertex2f(504.5878230647183, 314.2621185960259);
    glVertex2f(503.5387833226436, 317.4092297222496);

    glEnd();

//muk

    glBegin(GL_POLYGON);
    glColor3f(0.992, 0.761, 0.710);
    glVertex2f(508.4396761971595, 325.8087309372294);
    glVertex2f(508.1628330825976, 324.1998508727706);
    glVertex2f(508.4396761971595, 322.4245349395746);
    glVertex2f(508.8835051804585, 320.8156548751159);
    glVertex2f(509.105419672108, 319.9834755314303);
    glVertex2f(510.3814279990926, 320.6492190063787);
    glVertex2f(510.880735605304, 323.0347997916107);
    glVertex2f(511.8238721948144, 324.8655943477719);
    glVertex2f(512.6560515385, 326.5299530350902);
    glVertex2f(514.6532819633456, 328.8600551974099);
    glVertex2f(516.3176405707168, 330.5798925076934);
    glVertex2f(518.0374779610005, 331.412071851379);
    glVertex2f(518.6477428130366, 330.8018069993429);
    glVertex2f(520, 330);
    glVertex2f(521.0333235982688, 328.8600551974099);
    glVertex2f(522.087417433604, 327.6395254933377);
    glVertex2f(523.418904383501, 326.5854316580026);
    glVertex2f(525.0277844479599, 325.8087309372294);
    glVertex2f(526.5811858895064, 325.2539447081057);
    glVertex2f(528.578416134352, 324.9210729706314);
    glVertex2f(530, 325);
    glVertex2f(531.0194757224965, 324.8655943477719);
    glVertex2f(531.0194757224965, 323.9224577582087);
    glVertex2f(530.6866039850222, 322.1471418250128);
    glVertex2f(530.7420826079347, 320.2608686459921);
    glVertex2f(529.9653818871614, 318.6519888515333);
    glVertex2f(528.8558094289139, 316.5992795337755);
    glVertex2f(527.9126728394034, 314.3246559943682);
    glVertex2f(526.8585790040684, 312.4938614382599);
    glVertex2f(525.9709210374702, 310.8849813738011);
    glVertex2f(524.8058699563104, 309.0541681769298);
    glVertex2f(523.6408188751506, 307.7781784907082);
    glVertex2f(521.8100243190421, 305.7809480656828);
    glVertex2f(520, 305);
    glVertex2f(518.7587000588615, 303.5063245264555);
    glVertex2f(517.7046062235263, 302.8960596744194);
    glVertex2f(516.4285978965416, 302.0638803307338);
    glVertex2f(515.0971109466446, 301.7310085932596);
    glVertex2f(513.37727363636361, 302.2857948223833);
    glVertex2f(511.768393571902, 303.5618031493679);
    glVertex2f(510, 305);
    glVertex2f(508.4951548200719, 307.0014777699335);
    glVertex2f(506.9417533785253, 309.49801580009918);
    glVertex2f(506.2760099035768, 312.1609897007857);
    glVertex2f(506.2205312806644, 315.3232712067909);
    glVertex2f(505.9431381661026, 317.708851992023);
    glVertex2f(504.5561725932932, 319.3177320564818);
    glVertex2f(504.1678222329065, 321.14852666125901);
    glVertex2f(504.44521534746484, 323.201356603479);
    glVertex2f(505, 325);
    glVertex2f(506.0147475036207,326.2528099709114);
    glVertex2f(507.1944165595855,326.2159453129125);
    glEnd();

//chul

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(510.6631947494106, 341.7519970814782);
    glVertex2f(512.8338317739822, 341.7519970814782);
    glVertex2f(515.29374571293, 341.8243474941473);
    glVertex2f(517.3910760202326, 342.2584499512616);
    glVertex2f(519.0559670313208, 342.9096036409831);
    glVertex2f(520.720026460609, 342.3308003612307);
    glVertex2f(522.2393850699592, 340.8837921618497);
    glVertex2f(523.1799403995568, 339.5091343724377);
    glVertex2f(524.5545981889688, 338.496228632871);
    glVertex2f(526.363584381953, 338.496228632871);
    glVertex2f(528.0997682774525, 338.6409294528091);
    glVertex2f(530.125579765568, 338.496228632871);
    glVertex2f(531.861989595843, 337.5556733032734);
    glVertex2f(532.802544924541, 336.6874683836447);
    glVertex2f(533.670748450696, 335.0234089543566);
    glVertex2f(534.032501894915, 334.1422982951613);
    glVertex2f(534.177202714853, 330.9178599608989);
    glVertex2f(533.8878010749769, 329.5247779767088);
    glVertex2f(533.3813482051935, 327.5713167275445);
    glVertex2f(532.5854936955338, 326.1243085281635);
    glVertex2f(531.2108359061218, 325.1110472859677);
    glVertex2f(528.750921967174, 324.4602490888735);
    glVertex2f(525.8560955684119, 325.6902060683491);
    glVertex2f(523.83109408982784, 326.847812627854);
    glVertex2f(521.8776330201139, 328.4395216471713);
    glVertex2f(520, 330);
    glVertex2f(518.6218645715064, 331.5505892758422);
    glVertex2f(517.1748563712254, 331.5505892758422);
    glVertex2f(514.85964325351157, 331.5505892758422);
    glVertex2f(511.5315243945392, 332.3464437855017);
    glVertex2f(510.012165785819, 333.7211015749137);
    glVertex2f(510.130551259937, 335.8916138739852);
    glVertex2f(508.1310551259937, 338.9303310926835);
    glVertex2f(509.3173481479561,340.6740292565984);
    glEnd();


//matha
    glBegin(GL_POLYGON);
    glColor3f(0.565, 0.404, 0.467);
    glVertex2f(505.1874173787844, 316.8799963023941);
    glVertex2f(504.5303829382343, 318.7103065296406);
    glVertex2f(503.96721056062, 321.5730994494918);
    glVertex2f(504, 324);
    glVertex2f(504.952762214445, 325.7499612498194);
    glVertex2f(506.2668311025452, 326.5947198162408);
    glVertex2f(507.9563482353881, 326.8293749735801);
    glVertex2f(508.6133826759382, 325.9376853756908);
    glVertex2f(508.4256585500668, 324.3889613372514);
    glVertex2f(508.566451644474, 322.6055821414728);
    glVertex2f(508.94189986921232, 321.2445822289049);
    glVertex2f(509.1765550535525, 320.3998236624835);
    glVertex2f(510.53755496661205, 320.4936857254192);
    glVertex2f(511.362655664493, 322.0689355877303);
    glVertex2f(511.2491357335088, 323.4311747595448);
    glVertex2f(511.7788954114367, 325.5502134712562);
    glVertex2f(512.9140947212821, 327.2151724590294);
    glVertex2f(514.2006539391069, 328.8801314468027);
    glVertex2f(515.3358532489524, 329.9396508026584);
    glVertex2f(516.4710525587979, 330.6207703885656);
    glVertex2f(517.6440918456382, 330.9234902045244);
    glVertex2f(516, 332);
    glVertex2f(514.42769380310761, 331.6424497674625);
    glVertex2f(512.951934698277, 331.7181297214162);
    glVertex2f(511.1735457759191, 332.6641291462873);
    glVertex2f(509.697696676672, 333.7993284561327);
    glVertex2f(508.8652171828333, 334.7453278810039);
    glVertex2f(508, 336);
    glVertex2f(507.616497942003, 337.4698062246329);
    glVertex2f(506.5948156341244, 336.9778865236999);
    glVertex2f(506, 336);
    glVertex2f(505.194739143334, 335.0480476969627);
    glVertex2f(504.5136198284257, 333.6101285711585);
    glVertex2f(504, 332);
    glVertex2f(503.189220633606, 330.6964503425553);
    glVertex2f(502.5081010476987, 329.4098911247306);
    glVertex2f(502.1297012777503, 327.555732251983);
    glVertex2f(502.31890111627245, 326.0042931951944);
    glVertex2f(502.1675412547451, 324.7177339773696);
    glVertex2f(502.2053812317399, 323.0149350126015);
    glVertex2f(502.6216209786833, 321.3878160018231);
    glVertex2f(503.189220633606, 320.0255768300086);
    glVertex2f(503.3027405645905, 318.5119775022147);
    glVertex2f(503.5676204035545, 317.1497835784083);
    glVertex2f(504.1736000354721, 316.3550999615085);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(526.7388275486798, 313.0068526031481);
    glVertex2f(530.2349054978758, 308.5907541410059);
    glVertex2f(532.4429547289471, 304.0826536275691);
    glVertex2f(533.3629752418935, 299.1145428576592);
    glVertex2f(534.5590019087238, 294.1464320877492);
    glVertex2f(536.1230367870325, 289.9143377281962);
    glVertex2f(538.6070921656877, 284.9462269582863);
    glVertex2f(540.6311372941697, 280.806134650028);
    glVertex2f(542.1031701148838, 275.7460218288234);
    glVertex2f(543.3911988330087, 270.6859090076188);
    glVertex2f(544.1272152433659, 268.1098515713692);
    glVertex2f(544.219217294664, 264.7057756734679);
    glVertex2f(542.4711732000623, 261.1176956729774);
    glVertex2f(540.9991454949342, 258.5416382367278);
    glVertex2f(538.7910962682877, 256.3335890055667);
    glVertex2f(535, 255);
    glVertex2f(530, 255);
    glVertex2f(526.5548234460905, 255.7815766978889);
    glVertex2f(523.6107578046622, 256.9776033647191);
    glVertex2f(521.8627188300641, 259.7376649035579);
    glVertex2f(527.198378051513, 260.6576854165043);
    glVertex2f(528.3948644719832, 263.41774695553431);
    glVertex2f(528.6708706258671, 267.1898310584229);
    glVertex2f(525.7268049844438, 270.0418946485564);
    glVertex2f(523.8867639585461, 272.3419459309221);
    glVertex2f(522.5067331891265, 275.3780136236449);
    glVertex2f(521.126702419707, 278.2300772137784);
    glVertex2f(519.9306757528767, 281.4501490090904);
    glVertex2f(520.4826880606464, 286.1422536251164);
    glVertex2f(521.7707167787695, 290.2823459333748);
    glVertex2f(522.6907372917158, 294.4224382416331);
    glVertex2f(524.1627701124299, 297.9185161908289);
    glVertex2f(524.9907885740816, 301.8746043966498);
    glVertex2f(525.8224127801795,310.5101298237277);
    glEnd();

//pa ar

    glBegin(GL_POLYGON);
    glColor3f(0.992, 0.761, 0.710);
    glVertex2f(488.4070498461944, 180.8727921660476);
    glVertex2f(488.9027924764749, 177.893363843465);
    glVertex2f(489.8915463726817, 175.7656938519279);
    glVertex2f(492.2504519512764, 175.7036230493333);
    glVertex2f(494.67143399426458, 175.7036230493333);
    glVertex2f(496.7199572580875, 175.7036230493333);
    glVertex2f(496.6578807954929, 177.8762992401441);
    glVertex2f(496.5337278703037, 180.5455731717117);
    glVertex2f(493.7402870535468, 180.4214342065225);
    glVertex2f(491.0709916191791, 180.4214342065225);
    glEnd();


// muja


    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(490, 175);
    glVertex2f(490.6364639238169, 172.2273411444036);
    glVertex2f(491.1330756245736, 169.8684355654414);
    glVertex2f(491.4434579375466, 167.5095299868468);
    glVertex2f(491.4434579375466, 165.3989320586306);
    glVertex2f(491.691673787925, 164.2197474693333);
    glVertex2f(493.3057518153846, 164.1574010067387);
    glVertex2f(494.9197398428441, 164.1574010067387);
    glVertex2f(497.0303395710605, 164.5919362449008);
    glVertex2f(496.7820337206821, 168.6269063135495);
    glVertex2f(496.7820337206821, 172.1031882188468);
    glVertex2f(496.7199572580875, 174.7724761101444);
    glVertex2f(494.2989752168982, 174.9587054981982);
    glVertex2f(492.1262992060872, 175.0828584233784);
    glEnd();

//juta

    glBegin(GL_POLYGON);
    glColor3f(0.251, 0.294, 0.471);
    glVertex2f(491.5533959345802, 164.3451942164576);
    glVertex2f(492.9402879025189, 163.5484690433865);
    glVertex2f(494.5042290908178, 163.5484690433865);
    glVertex2f(496, 164);
    glVertex2f(497.012438771047, 165.0533943702986);
    glVertex2f(498.0452306781228, 164.90585267515817);
    glVertex2f(499.1370392486277, 164.1386358383254);
    glVertex2f(500, 164);
    glVertex2f(501.3796730691242, 163.7255190818468);
    glVertex2f(502.5009899793724, 163.7550274215901);
    glVertex2f(504, 164);
    glVertex2f(505.3928072742232, 163.66650240236);
    glVertex2f(505.8944490498606, 162.9287939087757);
    glVertex2f(506.3075658062678, 162.1025603959612);
    glVertex2f(506.3370741460112, 160.8337017869962);
    glVertex2f(506, 160);
    glVertex2f(505.0682155370461, 159.3582847998275);
    glVertex2f(504.1534570050014, 159.1517264216239);
    glVertex2f(500.0813061204157, 159.1517264216239);
    glVertex2f(497.45506388325353, 159.2107431011106);
    glVertex2f(495.9501385563431, 158.8566430241902);
    glVertex2f(494.1206124922539, 158.8271346844468);
    glVertex2f(492.4976628063683, 159.2402514440854);
    glVertex2f(491.1992958576598, 159.9775999344384);
    glVertex2f(490.4615873640754, 161.1582935241733);
    glVertex2f(490.4320709243232, 162.8697772292889);
    glVertex2f(490.727162417657, 163.9190941395371);
    glEnd();


//pa 2


    glBegin(GL_POLYGON);
    glColor3f(0.992, 0.761, 0.710);
    glVertex2f(532.4465149803385, 185.9065001170145);
    glVertex2f(533.4793402542589, 180.2833402923375);
    glVertex2f(536.061403490596, 179.9390652010308);
    glVertex2f(537.6680205318246, 179.8818660191463);
    glVertex2f(539.2172584427051, 179.8243068372618);
    glVertex2f(540.823875534547, 180.0538235647997);
    glVertex2f(540, 185);
    glVertex2f(537.7253997137091, 185.1031915706321);
    glVertex2f(535, 185);
    glEnd();


//muja

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(533.7742517491596, 179.1166738879288);
    glVertex2f(533.8486067314419, 177.2206218397288);
    glVertex2f(534.5549790631244, 174.8784398798347);
    glVertex2f(534.9639314656773, 173.1682753053406);
    glVertex2f(535.0754639391008, 171.6811756596936);
    glVertex2f(535.0754639391008, 169.8966560849172);
    glVertex2f(535.2613513948068, 168.9300413152466);
    glVertex2f(536.339498637901, 168.2236689835643);
    glVertex2f(537.677883189834, 168.1493140012819);
    glVertex2f(538.8675680355011, 168.0749590189996);
    glVertex2f(540.0572477520188, 168.2608464747054);
    glVertex2f(540.949507539407, 168.6326213861172);
    glVertex2f(540.9866850305483, 170.4914959434176);
    glVertex2f(540.72644259256, 172.4619029736583);
    glVertex2f(540.72644259256, 174.0605350927289);
    glVertex2f(540.8751525571247, 175.8450546675053);
    glVertex2f(540.9123300482659, 177.5552192599994);
    glVertex2f(540.8751525571247, 179.3397388347759);
    glVertex2f(539.1278104734894, 179.5999812727641);
    glVertex2f(537.826598283548, 179.4140938170582);
    glVertex2f(535.8190137619245, 179.5628037816229);
    glEnd();


//juta

    glBegin(GL_POLYGON);
    glColor3f(0.251, 0.294, 0.471);
    glVertex2f(535.0056332765491, 169.3086270783842);
    glVertex2f(536.2256972193005, 168.4234826493295);
    glVertex2f(537.6610665637138, 168.0167946684124);
    glVertex2f(538.9768217960926, 167.897180553678);
    glVertex2f(540, 168);
    glVertex2f(540.818879121423, 168.8780162750603);
    glVertex2f(541.9432517745468, 168.5670195837708);
    glVertex2f(542.9958559604498, 168.0646403132262);
    glVertex2f(544.1919970807943, 167.6579523323091);
    glVertex2f(545.2446012666974, 167.251264351392);
    glVertex2f(546.6321249662968, 167.0598817721369);
    glVertex2f(547.9718030210826, 166.9881133049163);
    glVertex2f(549.2875582534615, 166.5096568567786);
    glVertex2f(550.1009342152956, 165.6962808949444);
    glVertex2f(550.3401624393646, 165.0742875123653);
    glVertex2f(550.459776551399, 164.1173746160899);
    glVertex2f(550.1487798601095, 163.3996899438833);
    glVertex2f(549.4071723654959, 162.8494650285249);
    glVertex2f(547.4933465729448, 162.6102368044456);
    glVertex2f(544.9814502202216, 162.5863139820492);
    glVertex2f(542.6609364467535, 162.6341596268629);
    glVertex2f(540.6274965421679, 162.6102368044456);
    glVertex2f(539.2878184873822, 162.6102368044456);
    glVertex2f(537.7567578533414, 162.7059280940836);
    glVertex2f(535.9386233504179, 163.0647704301869);
    glVertex2f(534.9817104541423, 163.8542235696141);
    glVertex2f(534.5271768284114, 165.0742875123653);
    glVertex2f(534.3357942491563, 166.6292709688813);
    glVertex2f(534.407562716377, 168.1842544252606);
    glEnd();


    }

}

void flower()
{

    glBegin(GL_POLYGON);
    glColor3f(1,1,1);

    glVertex2f(866.4909146591134,380.1540708626861);
    glVertex2f(867.0190110489718,332.0972993855677);
    glVertex2f(900.2890836100528,331.5692029957093);
    glVertex2f(900,380);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.475, 0.451, 0.302);
    glVertex2f(869.8486958766781, 381.2305024243171);
    glVertex2f(866.0185573045732, 386.4717446808818);
    glVertex2f(861.3820737699199, 388.8907795685271);
    glVertex2f(855.7376590320811, 391.9145731780837);
    glVertex2f(852.1091067006133, 393.3256768625434);
    glVertex2f(849.6900718129681, 397.9621603971968);
    glVertex2f(850.8995892567907, 403.8081613756729);
    glVertex2f(853.9233828663472, 405.0176788194955);
    glVertex2f(856.9471764759037, 406.6303687445924);
    glVertex2f(855.9394252727182, 413.0811284449797);
    glVertex2f(857.5071319921453, 417.811926520491);
    glVertex2f(860, 420);
    glVertex2f(862.6243859673965, 422.0336610500733);
    glVertex2f(862.880248666159, 425.3598761339866);
    glVertex2f(861.3450724735837, 429.0698852660437);
    glVertex2f(857.8909260402892, 432.0123063018132);
    glVertex2f(854.0529855588509, 434.5709332894388);
    glVertex2f(851.7502126999878, 439.1764618671649);
    glVertex2f(851.1106545230814, 443.2702650473659);
    glVertex2f(853.2868079194928, 446.5208496871926);
    glVertex2f(854.8067932003496, 449.1137675545364);
    glVertex2f(855.522080391341, 451.796092720754);
    glVertex2f(856.0585457485485, 455.0148850802152);
    glVertex2f(854.8962040992235, 457.9654447430547);
    glVertex2f(853.6444515149885, 459.6642518216592);
    glVertex2f(851.4985899420145, 461.8995242935073);
    glVertex2f(849.3527283690404, 465.5653711473381);
    glVertex2f(847.6044299040625, 470.0486052891375);
    glVertex2f(849.9613637781177, 475.2043981386333);
    glVertex2f(853.349456222072, 478.1505654812023);
    glVertex2f(855.7063900961272, 482.1278913936705);
    glVertex2f(855.1171566276133, 487.2836842431663);
    glVertex2f(854.0859805771413, 493.1760189283043);
    glVertex2f(854.675231526228, 498.773368791854);
    glVertex2f(858.5052490715677, 502.4564460573967);
    glVertex2f(861.1567996798798, 502.4564460573967);
    glVertex2f(864.3975837567056, 502.4564460573967);
    glVertex2f(867.3437510992745, 506.4337719698648);
    glVertex2f(870, 510);
    glVertex2f(871.6379279513205, 514.574867447356);
    glVertex2f(876.5182612163389, 517.557293331534);
    glVertex2f(880.0429463521856, 517.8284229573684);
    glVertex2f(883.9743259267838, 517.1505988927825);
    glVertex2f(887.0923166238789, 513.6259137569358);
    glVertex2f(888.4479647530507, 510.3723582469234);
    glVertex2f(888.5835295659679, 505.8987194206565);
    glVertex2f(887.9057055013819, 501.4250805943895);
    glVertex2f(888.719094378885, 497.6292658327084);
    glVertex2f(889.3969184434709, 493.562231445193);
    glVertex2f(890, 490);
    glVertex2f(892.2437795147316, 489.9020714964291);
    glVertex2f(895.2262053989095, 490.7154603739322);
    glVertex2f(898.7508905347562, 491.9355436901868);
    glVertex2f(902.5467052964372, 491.6644140643525);
    glVertex2f(904.8513071160293, 490.0376363093463);
    glVertex2f(906.7492144968697, 487.4619048639199);
    glVertex2f(908.5115570647493, 484.072845409903);
    glVertex2f(907.969278131243, 480.2769697793092);
    glVertex2f(906.206955245201, 475.9388957659594);
    glVertex2f(905.1224367418636, 472.5497754430299);
    glVertex2f(903.4956589868574, 470.3807384363551);
    glVertex2f(902.41114048352, 467.6694421780114);
    glVertex2f(901.5977516060169, 465.2292755455022);
    glVertex2f(903.6312237997746, 462.111284848407);
    glVertex2f(906.206955245201, 460.3489422804837);
    glVertex2f(908.1048626260415, 456.6886923317198);
    glVertex2f(908.5115570647493, 451.2660998150325);
    glVertex2f(907.69816818729, 447.1991554275172);
    glVertex2f(905.3935663676979, 442.3188221624986);
    glVertex2f(902.5467052964372, 436.8962296458114);
    glVertex2f(901.1910571672654, 434.1849333874678);
    glVertex2f(902.9533997351887, 430.5246834387039);
    glVertex2f(904.715742303112, 427.542575545259);
    glVertex2f(903.7667886126918, 423.882007605762);
    glVertex2f(901.3266219801826, 420.899581721584);
    glVertex2f(899.6998442251764, 417.7815910244889);
    glVertex2f(900.5132331026795, 415.2058595790625);
    glVertex2f(905.1224367418636, 411.9523040690501);
    glVertex2f(906.8847793097868, 408.0209244944518);
    glVertex2f(905.2580015547808, 404.4962393586052);
    glVertex2f(907.020344122704, 401.2426838485928);
    glVertex2f(910, 400);
    glVertex2f(910.2882283370078, 397.8674350734908);
    glVertex2f(910, 395);
    glVertex2f(908.8153539861756, 393.3669856681702);

    glVertex2f(907.1788269296956, 391.2395004974459);
    glVertex2f(905, 390);
    glVertex2f(902.5965511715551, 388.6210572043776);
    glVertex2f(900.6327187037748, 386.8208774422494);
    glVertex2f(898.7507125888227, 385.0209676801212);
    glVertex2f(897.2118308461337, 383.0078424652505);
    glVertex2f(895.849051294763, 381.3972848136305);
    glVertex2f(893.6225934710266, 380.4148790414502);
    glVertex2f(890, 380);
    glVertex2f(886.4610414247378, 380.3095620995931);
    glVertex2f(883.9334348201653, 380.3095620995931);
    glVertex2f(881.51114515745, 380.4148790414502);
    glVertex2f(878.4569538435915, 380.520159833074);
    glVertex2f(875.6133964134474, 380.7308298670218);
    glVertex2f(871.6113526228742, 380.941637507362);


    glEnd();
}


void lift()
{


    glBegin(GL_POLYGON);
    glColor3f(0.75f, 0.75f, 0.75f);

glVertex2f(892.1802487480732,392.1699384668829);
glVertex2f(896.4602869457971,398.3046598836206);
glVertex2f(901.7390007229899,405.152720999979);
glVertex2f(906.4470427404862,411.8581141764133);
glVertex2f(912.0110923975272,419.5621829323165);
glVertex2f(927.075669322552,440.4036763288406);
glVertex2f(962.9409550370152,487.988353387858);
glVertex2f(997.3766056809031,534.9228698210102);
glVertex2f(1123.53194794653, 702.265731789712);
glVertex2f(1126.2665075240814,706.1659988097549);
glVertex2f(1130,710);
glVertex2f(1133.7347036176975,713.8506643553598);
glVertex2f(1138.1723273834693,718.1800533951371);
glVertex2f(1142.7181858752356,721.3188604489757);
glVertex2f(1147.2640443670018,724.4576675028143);
glVertex2f(1151.7016681327734,727.0553009266806);
glVertex2f(1157.0051697065007,729.8694038025359);
glVertex2f(1162.4169060062225,731.8176288704358);
glVertex2f(1169.5603979218552,733.4411497603522);
glVertex2f(1174.8638994955825,733.9823233903244);
glVertex2f(1200.17814023037,734.8901450944865);
glVertex2f(1200.0676648356355,696.9970847005486);
glVertex2f(1182.1706508886443,696.9970847005486);
glVertex2f(1177.3423885259524,695.1735436868659);
glVertex2f(1172.7009732347647,691.9687569381886);
glVertex2f(1168.7226172708895,688.2114207500841);
glVertex2f(1165.2968107464412,685.0066340014068);
glVertex2f(1161.7604943341078,680.6967483738753);
glVertex2f(1156.8980592671492,673.5136056613227);
glVertex2f(1153.5827626305863,669.424739809562);
glVertex2f(914.8896622851508,328.3970969800906);
glVertex2f(913.03760161587,326.3154822847332);
glVertex2f(910.8348293120162,324.1127099808793);
glVertex2f(908.2649282908533,322.5218188725403);
glVertex2f(905.5726510305875,321.0533040033044);
glVertex2f(902.7579975312186,320.0742940904804);
glVertex2f(899.3314628363348,318.3610267430385);
glVertex2f(896.883938054275,317.7491455475235);
glVertex2f(893.3350271202881,317.1372643520085);
glVertex2f(887.1391099427091,316.5309514466414);
glVertex2f(772.9372698929045,312.1637682707406);
    glVertex2f(780.8063677447687, 347.9219203919549);
glVertex2f(784.9416771361443, 352.7764140253089);
glVertex2f(790.6951510719713, 353.8551903882765);
glVertex2f(798.785973794228, 353.8551903882765);
glVertex2f(808.494961060936, 354.394758697602);
glVertex2f(816.7655798436872, 355.6531509932224);
glVertex2f(827.3735474128682, 356.7319273561899);
glVertex2f(837.4421268005653, 358.889480082125);
glVertex2f(845.8925416438112, 361.2268288685548);
glVertex2f(855.961120315084, 364.4631579574574);
glVertex2f(863.3327595117867, 367.5196099858656);
glVertex2f(870.3448058710758, 372.1943885587249);
glVertex2f(877.8962404118487, 377.7680664340574);
glVertex2f(883.469918287181, 380.6448034019709);
glVertex2f(888.5042079810296, 386.5780733982924);



glBegin(GL_POLYGON);
    glColor3f(0.75f, 0.75f, 0.75f);

glVertex2f(756.867726851927,400.2191208107331);
glVertex2f(996.7816138311279,718.4604768658689);
glVertex2f(1000.647924830189,723.0771537806378);
glVertex2f(1005.6158274164868,726.9912588486302);
glVertex2f(1010, 730);
glVertex2f(1014.949462578622, 734.2172989741546);
glVertex2f(1020.8206201806105, 737.2281490264563);
glVertex2f(1025.6379802642932, 739.937914073528);
glVertex2f(1030, 740);
glVertex2f(1035.573785436888, 742.4971366179846);
glVertex2f(1042.799825562413, 743.5509341362902);
glVertex2f(1049.8753231853218, 743.0993066284449);
glVertex2f(1056.8002783056158, 744.0025616441354);
glVertex2f(1063.1230634154495, 744.0025616441354);
glVertex2f(1068.2261777706312, 744.6361226734082);
glVertex2f(1075.3739375624402, 744.9935106629987);
glVertex2f(1081.2708393906828, 745.8869806369748);
glVertex2f(1088.0612111929013, 745.8869806369748);
glVertex2f(1088.4185991824918, 740.5261607931179);
glVertex2f(1087.882517198106, 733.7357889908991);
glVertex2f(1087.5251292085156, 725.8732532199089);
glVertex2f(1087.3464352137203, 719.2615754124853);
glVertex2f(1087.5251292085156,714.436837553014);
glVertex2f(756.6352474874403,354.4219166002694);
glVertex2f(656.6839767671206,341.4589531621386);
glVertex2f(664.5299809533573,375.5720148414302);
glVertex2f(666.6202481543955, 377.3940985389172);
glVertex2f(669.0086501348667, 378.2786918650176);
glVertex2f(672.4585641066584, 379.074825858508);
glVertex2f(675.4661814153998, 378.8094478606779);
glVertex2f(678.4737987241413, 378.6325291954578);
glVertex2f(683.1621433524734, 378.7209885280678);
glVertex2f(686.6120573242652, 378.8094478606779);
glVertex2f(690.6811866243271, 379.5171225215582);
glVertex2f(695.0, 380.0); // M1 - simplified
glVertex2f(698.819445224451, 379.7825005193884);
glVertex2f(702.2693591962426, 380.8440125107089);
glVertex2f(706.9577038245749, 381.9055245020295);
glVertex2f(713.415235105108, 382.6131991629098);
glVertex2f(719.5189290552008, 384.2939264825008);
glVertex2f(728.6359104523906, 386.2921646589535);
glVertex2f(733.5851296341236, 387.9770052314585);
glVertex2f(737.9025336011674, 389.767148339745);
glVertex2f(742.3252401039928, 391.45198891225);
glVertex2f(747.5903668930706,394.4004599141337);
glVertex2f(751.275955645425,396.8224182371095);
glVertex2f(754.6456367904348,398.5072588096145);


glEnd();

glBegin(GL_POLYGON);
glColor3f(0.4f, 0.4f, 0.4f);
glVertex2f(746.7611273828928,311.5921436631969);
glVertex2f(632.7828386151284,339.1344550877993);
glVertex2f(734.161984922703,350.561584295879);
glVertex2f(1012.1596711079992,714.2066141139976);
glVertex2f(1126.4808023912897,708.5319282566414);
glVertex2f(834.334980936206,314.4305152184223);
glEnd();


glBegin(GL_POLYGON);
glColor3f(0.4f, 0.4f, 0.4f);
glVertex2f(1012.1596711079992,714.2066141139976);
glVertex2f(1089.6997740971676,723.2054246412021);
glVertex2f(1199.5324270968495,723.5256364575276);
glVertex2f(1126.4808023912897,708.5319282566414);
glEnd();



glBegin(GL_POLYGON);
glColor3f(0.4f, 0.4f, 0.4f);
glVertex2f(0,330);
glVertex2f(632.7828386151284,339.1344550877993);
glVertex2f(746.7611273828928,311.5921436631969);
glVertex2f(0,300);
glEnd();


/*glBegin(GL_POLYGON);
glColor3f(1,1,1);


glVertex2f(764.3004594474857, 342.7736913599076);
glVertex2f(761.4968716900768, 343.7666286906566);
glVertex2f(757.2914900539633, 345.5772791173167);
glVertex2f(750, 350);
glVertex2f(745.3026608149405, 355.4164015077338);
glVertex2f(740.742864231025, 361.9303966276135);
glVertex2f(737.2687335004227, 369.7471907714691);
glVertex2f(734.2909971602909, 378.8212297045081);
glVertex2f(732.3890609299298, 387.3799427411339);
glVertex2f(732.3890609299298, 395.1065586769765);
glVertex2f(732.1513189011346, 404.7351108431804);
glVertex2f(733.5102698951379, 419.8984500331745);
glVertex2f(739.1806895055122, 431.422206015549);
glVertex2f(745.2169426391365, 440.3851273351736);
glVertex2f(752.3506963425108, 448.6163816082982);
glVertex2f(762.1894281373135, 454.9429667464502);
glVertex2f(769.0559907971916, 458.2045840098925);
glVertex2f(778.0974984109881, 461.1506871397796);
glVertex2f(787.044663035757, 463.8016988804521);
glVertex2f(797.4277923533899, 466.4527106211245);
glVertex2f(806.9049406011178, 467.8296103558998);
glVertex2f(813.0203713725191, 468.7289384105089);
glVertex2f(820, 470);
glVertex2f(828.9728745987992, 472.0877195414909);
glVertex2f(834.6798241804847, 473.7998044159967);
glVertex2f(840, 475);
glVertex2f(844.4579892420797, 476.4059948066636);
glVertex2f(851.9504948286783, 479.4360522130089);
glVertex2f(859.2226326039064, 483.9535923461055);
glVertex2f(867.4080439039467, 489.4656829949369);
glVertex2f(876.2167197765357, 497.0437350323854);
glVertex2f(882.3314835960172, 503.1935516875263);
glVertex2f(890.2379636406387, 512.0956625525823);
glVertex2f(897.3301255101569, 520.158230106511);
glVertex2f(1106.093296605097, 782.8969837688229);
glVertex2f(1110, 788);
glVertex2f(1114, 792);
glVertex2f(1118.3074075121488, 795.9343266439779);
glVertex2f(1123.734629959469, 800.2049279140006);
glVertex2f(1129.5177358459575, 803.6747914458939);
glVertex2f(1134.500103994317, 806.8777423984109);
glVertex2f(1140.8170350395583, 809.9917224911358);
glVertex2f(1147.6781124522588, 812.8591939537874);
glVertex2f(1155, 815);
glVertex2f(1163.3412978494464, 815.6153767919193);
glVertex2f(1172.7666274921226, 815.8883406320779);
glVertex2f(1182.9578721633388, 815.8996377885309);
glVertex2f(1190, 816);
glVertex2f(1196.4346129927499, 816.1336089834859);
glVertex2f(1200, 816);
glVertex2f(1199.8505924390938, 819.6431769078122);
glVertex2f(1191.9608235118596, 819.6533425945438);
glVertex2f(1186.192196010677, 819.6533425945438);
glVertex2f(1180, 820);
glVertex2f(1173.2886871264532, 819.6533425945438);
glVertex2f(1166.9887386712144, 819.5015366076648);
glVertex2f(1161.111982888057, 818.9451512851053);
glVertex2f(1155.813117882005, 818.0266813507229);
glVertex2f(1151.1501166769795, 817.2495144831686);
glVertex2f(1144.4876924621872, 816.0131819238782);
glVertex2f(1138.8490381976803, 814.1089532741103);
glVertex2f(1134.4724441159842, 811.866399057118);
glVertex2f(1130, 810);
glVertex2f(1125.5724678682602, 807.7268752023624);
glVertex2f(1121.5684777304975, 805.7230841885797);
glVertex2f(1117.3085773191153, 802.5554659339621);
glVertex2f(1112.1748511823216, 799.8247605420504);
glVertex2f(1108.1334072022926, 796.7663750503092);
glVertex2f(1105.184245379028, 793.926436895521);
glVertex2f(1102.7812246341457, 791.1957315036093);
glVertex2f(1099.285921732499, 787.9188850333152);

glVertex2f(887.7200514732154, 521.6391035767579);
glVertex2f(883.2557848401717, 516.7836103092211);
glVertex2f(875.7662597386461, 507.7551416936828);
glVertex2f(866.9607676101939, 498.2234147181117);
glVertex2f(860.8125441939906, 493.1485986416323);
glVertex2f(853.4237974350235, 487.2015585673414);
glVertex2f(846.0350506760565, 482.2456918387656);
glVertex2f(835.8334801072153, 477.7419993019972);
glVertex2f(823.0013272738389, 474.4258249742705);
glVertex2f(807.9883711105617, 471.5754783406237);
glVertex2f(800, 470);
glVertex2f(790.4301870556349, 468.5301906406256);
glVertex2f(781.5208323674843, 466.2390980065296);
glVertex2f(771.7195972105188, 463.4388736759678);
glVertex2f(764.973602232477, 461.5296298142212);
glVertex2f(756.3183633924301, 457.8384250148442);
glVertex2f(747.3980238589115, 451.8331943806709);
glVertex2f(738.649645120581, 444.285735083853);
glVertex2f(731.5363998876688, 434.12812278595);
glVertex2f(727.4035690365262, 425.1839366155659);
glVertex2f(724.31060185936, 413.534466906093);
glVertex2f(723.2503022288276, 402.8609652133325);
glVertex2f(722.736828219058, 393.8690156776785);
glVertex2f(723.0786855323547, 384.2970109053684);
glVertex2f(725.8135440387289, 371.0785281245592);
glVertex2f(729.6879269227588, 362.646047729905);
glVertex2f(736.0038892947745, 353.9066313171409);
glVertex2f(739.8813175942539, 349.2975315176365);
glVertex2f(744.7866766423505, 345.383862383232);
glVertex2f(749.8982307529478, 342.7686026061774);
glVertex2f(753.854134354815, 341.1382651680855);
glVertex2f(757.05787740846, 340.2037359156158);
glVertex2f(760.2703020462103, 339.2692066631461);
glVertex2f(763.2491140384573, 338.8019420369113);
glVertex2f(766.1111098741455, 338.6267178020732);
glVertex2f(768.5058410835991, 338.3346774106764);
glVertex2f(770.2580834319796, 336.6851258803525);
glVertex2f(770.666939979935, 340.7878166984094);
glVertex2f(769.7324107274654, 342.3648348119521);
glVertex2f(767.4544956745707, 342.3648348119521);
glEnd();*/

}

void display1 ()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw sky and clouds
    sky1();
    plan1();


    for (int i = 0; i < 10; i++)
    {
        if (i % 3 == 0)
        {
            drawCloud11(cloud_positions1[i][0], cloud_positions1[i][1]);
        }
        else if (i % 3 == 1)
        {
            drawCloud21(cloud_positions1[i][0], cloud_positions1[i][1]);
        }
        else
        {
            drawCloud31(cloud_positions1[i][0], cloud_positions1[i][1]);
        }
    }

    tiels1();
    black_wall1();
    wall11();
    long_wall11();
    long_wall21();
    long_wall31();
    wall21();
    top_wall1();
    tv1();
    lift();
    lift_part1();
    tv2();

    if (isVisible && isDay)
    {
        Point currentPosition = getCurrentPosition(currentTime);

    // Offset to align the shape's first vertex with (0, 338)
    float offsetX = -395.1765581971542; // X-coordinate of the first vertex
    float offsetY = -337.3743869844129; // Y-coordinate of the first vertex

    // Draw the "people" shape at the current position
    glPushMatrix();
    glTranslatef(currentPosition.x + offsetX, currentPosition.y + offsetY, 0);
    people1();
    glPopMatrix();
    }


    bench1();
    bench2();
    bench3();
    bench4();
    bench5();
    bench6();
    sitting_girl();
    setting_man();
    settingman2();
    //flower();

    glColor3f(0.0f, 0.0f, 0.0f);
    drawPartialHollowArc1(180,458,90,100,-M_PI/2,M_PI/2);



    glutSwapBuffers();
}



void timer1(int value)
{
    updateCloudPositions1();

    glutPostRedisplay();
    glutTimerFunc(30, timer1, 0);
}


//////mithila////////////////////////////////////////////

#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include<bits/stdc++.h>
//bool isDay = true;
bool isMoonVisible = false;
bool isRaining = false;
float rainDropsY[500];
float rainDropsX[500];

float planeScale = 0.1f; // Initial scale (small)
float planeX = 475.0f; // Initial X position
float planeY = 500.0f; // Initial Y position
float targetX = 0.0f; // Landing X position
float targetY = 0.0f; // Landing Y position
bool planeLanded = false;
bool isStopped = false;
bool newPlaneIncoming = true;
bool isFullscreen = false;
float moonX = 1000.0f; // Initial X position of the moon
float moonY = 800.0f;  // Initial Y position of the moon
float moonSpeedX = -2.0f; // Horizontal speed of the moon
float moonSpeedY = -1.0f; // Vertical speed of the moon
void updatePlane(int value);


float cloud_positions[10][2] =
{
    {100, 800}, {300, 850}, {500, 750}, {700, 800}, {900, 700},
    {1100, 850}, {200, 900}, {600, 650}, {800, 950}, {1000, 700}
};

void drawCircle(float cx, float cy, float r)
{
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; i++)
    {
        float angle = 2 * M_PI * i / 100;
        float x = r * cos(angle);
        float y = r * sin(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawCloud1(float x, float y)
{
    if (!isDay) return;
    glColor3f(0.68f, 0.84f, 0.90f);
    drawCircle(x, y, 40);
    drawCircle(x + 50, y + 20, 50);
    drawCircle(x + 100, y, 40);
}

void drawCloud2(float x, float y)
{
    if (!isDay) return;
    glColor3f(0.68f, 0.84f, 0.90f);
    drawCircle(x, y, 30);
    drawCircle(x + 40, y + 15, 35);
    drawCircle(x + 80, y, 30);
    drawCircle(x + 20, y - 15, 25);
}

void drawCloud3(float x, float y)
{
    if (!isDay) return;
    glColor3f(0.68f, 0.84f, 0.90f);
    drawCircle(x, y, 50);
    drawCircle(x + 60, y + 30, 60);
    drawCircle(x + 120, y, 50);
    drawCircle(x + 40, y - 20, 40);
}

void updateCloudPositions()
{
    for (int i = 0; i < 10; i++)
    {
        cloud_positions[i][0] += (i % 3 + 1) * 0.2f;
        if (cloud_positions[i][0] > 1200)
        {
            cloud_positions[i][0] = -200;
        }
    }
    glutPostRedisplay();
}

void drawMoon()
{
    if (isMoonVisible)
    {
        glColor3f(1.0f, 1.0f, 0.8f);
        int numSegments = 100;
        float radius = 50.0f;
        float centerX = 1000.0f;
        float centerY = 800.0f;

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(centerX, centerY);
        for (int i = 0; i <= numSegments; i++)
        {
            float angle = 2.0f * 3.1415926f * static_cast<float>(i) / static_cast<float>(numSegments);
            float x = centerX + radius * cos(angle);
            float y = centerY + radius * sin(angle);
            glVertex2f(x, y);
        }
        glEnd();
    }
}

void updateMoon(int value)
{
    if (isMoonVisible)
    {

        moonX += moonSpeedX;
        moonY += moonSpeedY;

        if (moonX < -50.0f || moonX > 1250.0f || moonY < -50.0f || moonY > 1050.0f)
        {
            moonX = 1200.0f;
            moonY = 800.0f;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, updateMoon, 0);
}

void initializeRain()
{
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < 500; i++)
    {
        rainDropsX[i] = static_cast<float>(rand() % 1200);
        rainDropsY[i] = static_cast<float>(rand() % 1000); //
    }
}


void drawRain()
{
    if (isRaining)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        glLineWidth(1.0f);
        glBegin(GL_LINES);
        for (int i = 0; i < 500; i++)
        {
            glVertex2f(rainDropsX[i], rainDropsY[i]);
            glVertex2f(rainDropsX[i], rainDropsY[i] - 20.0f);
        }
        glEnd();
    }
}

void update_Rain(int value)
{
    for (int i = 0; i < 500; i++)
    {
        rainDropsY[i] -= 15.0f;
        if (rainDropsY[i] < 0.0f)
        {

            rainDropsY[i] = 1000.0f;
            rainDropsX[i] = static_cast<float>(rand() % 1200);
        }
    }
    glutPostRedisplay();
    glutTimerFunc(30, update_Rain, 0);
}
void sky()
{

    if (isDay)
    {
        glBegin(GL_QUADS);
        glColor3f(0.31f, 0.85f, 0.91f);
        glVertex2f(0, 1000);
        glVertex2f(1200, 1000);


        glColor3f(0.85f, 0.95f, 0.75f);
        glVertex2f(1200, 430);
        glVertex2f(0, 430);

        glEnd();
    }
    else
    {
        glBegin(GL_QUADS);
        glColor3f(0.2f, 0.08f, 0.31f);
        glVertex2f(0, 1000);
        glVertex2f(1200, 1000);
        glColor3f(0.3f, 0.9f, 0.5f);
        glVertex2f(1200, 430);
        glVertex2f(0, 430);
        glEnd();
    }

}




void handleKeypress(unsigned char key, int x, int y)
{
    if (key == 'd' || key == 'D')
    {
        isDay = true; // Switch to day
    }
    else if (key == 'n' || key == 'N')
    {
        isDay = false; // Switch to night
    }
    else if (key == 'r' || key == 'R')
    {
        isRaining = !isRaining; // Toggle rain on/off
    }
    else if (key == 'f' || key == 'F')
    {
        if (isFullscreen)
        {
            glutReshapeWindow(1200, 1000);
            glutPositionWindow(100, 100);
        }
        else
        {
            glutFullScreen();
        }
        isFullscreen = !isFullscreen;
    }
    else if (key == 27)
    {
        exit(0);
    }
    else if(key == 'm' || key =='M')
    {
        isMoonVisible = !isMoonVisible;
    }
      glutKeyboardFunc(keyboard);
    glutPostRedisplay();

}

void mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        isStopped = !isStopped;  // Toggle stop/resume
    }
}



void tiles()
{
    if(isDay)
    {


        glBegin(GL_POLYGON);

        glColor3f(0.92f, 0.69f, 0.34f);

        glVertex2f(20,0);
        glVertex2f(55,0);
        glVertex2f(240,180);
        glVertex2f(8,430);
        glVertex2f(0,430);
        glVertex2f(210,180);
    }
    else
    {
        glBegin(GL_POLYGON);

        glColor3f(0.59f, 0.89f, 0.8f);

        glVertex2f(20,0);
        glVertex2f(55,0);
        glVertex2f(240,180);
        glVertex2f(8,430);
        glVertex2f(0,430);
        glVertex2f(210,180);
    }

    glEnd();
}
void renderBitmapString(float x, float y, void *font, const char *string)
{
    const char *c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void field1()
{
    if(isDay)
    {
        glBegin(GL_QUADS);
        glColor3f(0.95f, 0.85f, 0.4f);
        glVertex2f(0, 430);


        glColor3f(0.7f, 0.85f, 0.3f);
        glVertex2f(210, 180);


        glColor3f(0.5f, 0.75f, 0.2f);
        glVertex2f(20, 0);


        glColor3f(0.85f, 0.8f, 0.3f);
        glVertex2f(0, 0);


        glBegin(GL_QUADS);
        glColor3f(0.99, 0.84, 0.02);
        glVertex2f(95,200);
        glVertex2f(92,230);
        glVertex2f(185,230);
        glVertex2f(182,200);




        glBegin(GL_QUADS);
        glColor3f(0.55, 0.56, 0.16);

        glVertex2f(70,190);
        glVertex2f(144,190);
        glColor3f(0.58, 0.54, 0.17);
        glVertex2f(167,173);
        glVertex2f(82,173);

        glBegin(GL_QUADS);
        glColor3f(0.93, 0.65, 0.49);
        glVertex2f(112,200);
        glVertex2f(118,200);
        glColor3f(0.71, 0.72, 0.38);
        glVertex2f(116,173.5);
        glVertex2f(115,173.5);

        glBegin(GL_QUADS);
        glColor3f(0.93, 0.65, 0.49);
        glVertex2f(138,200);
        glVertex2f(144,200);
        glColor3f(0.71, 0.72, 0.38);
        glVertex2f(142,173.5);
        glVertex2f(141,173.5);

        glBegin(GL_QUADS);
        glColor3f(0.93, 0.65, 0.49);
        glVertex2f(164,200);
        glVertex2f(170,200);
        glColor3f(0.71, 0.72, 0.38);
        glVertex2f(168,173.5);
        glVertex2f(167,173.5);


    }

    else
    {
        glBegin(GL_QUADS);
        glColor3f(0.235f, 0.7f, 0.62f);
        glVertex2f(0, 430);
        glVertex2f(210, 180);
        glColor3f(0.5f, 0.75f, 0.2f);
        glVertex2f(20, 0);
        glVertex2f(0, 0);


        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(95,200);
        glVertex2f(92,230);
        glVertex2f(185,230);
        glVertex2f(182,200);


        glBegin(GL_QUADS);
        glColor3f(0.55, 0.56, 0.16);

        glVertex2f(70,190);
        glVertex2f(144,190);
        glColor3f(0.58, 0.54, 0.17);
        glVertex2f(167,173);
        glVertex2f(82,173);

        glBegin(GL_QUADS);
        glColor3f(0.93, 0.65, 0.49);
        glVertex2f(112,200);
        glVertex2f(118,200);
        glColor3f(0.71, 0.72, 0.38);
        glVertex2f(116,173.5);
        glVertex2f(115,173.5);

        glBegin(GL_QUADS);
        glColor3f(0.93, 0.65, 0.49);
        glVertex2f(138,200);
        glVertex2f(144,200);
        glColor3f(0.71, 0.72, 0.38);
        glVertex2f(142,173.5);
        glVertex2f(141,173.5);

        glBegin(GL_QUADS);
        glColor3f(0.93, 0.65, 0.49);
        glVertex2f(164,200);
        glVertex2f(170,200);
        glColor3f(0.71, 0.72, 0.38);
        glVertex2f(168,173.5);
        glVertex2f(167,173.5);


    }

    glEnd();



}



void tiles2()
{
    if(isDay)
    {
        glBegin(GL_TRIANGLES);

        glColor3f(0.92f, 0.69f, 0.34f);
        glVertex2f(71, 430);
        glVertex2f(482, 430);
        glVertex2f(361, 300);
        glEnd();
    }
    else
    {
        glBegin(GL_TRIANGLES);

        glColor3f(0.59f, 0.89f, 0.8f);
        glVertex2f(71, 430);
        glVertex2f(482, 430);
        glVertex2f(361, 300);
        glEnd();
    }

}

void field2()
{
    if(isDay)
    {
        glBegin(GL_TRIANGLES);


        glColor3f(0.95f, 0.85f, 0.4f);
        glVertex2f(75, 430);

        glColor3f(0.85f, 0.9f, 0.3f);
        glVertex2f(470, 430);

        glColor3f(0.9f, 0.8f, 0.2f);
        glVertex2f(345, 325);
        glEnd();



    }
    else
    {
        glBegin(GL_TRIANGLES);


        glColor3f(0.235f, 0.7f, 0.62f);
        glVertex2f(75, 430);

        glColor3f(0.85f, 0.9f, 0.3f);
        glVertex2f(470, 430);

        glColor3f(0.5f, 0.75f, 0.2f);
        glVertex2f(345, 325);
        glEnd();
    }



    /*glBegin(GL_QUADS);
    glColor3f(0.99, 0.84, 0.02);
    glVertex2f(318,370);
    glVertex2f(313,395);
    glVertex2f(370,395);
    glVertex2f(365,370);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.99, 0.84, 0.02);
    glVertex2f(338,370);
    glVertex2f(342,348);
    glVertex2f(341,348);
    glVertex2f(340,370);
    glEnd();*/
}


void field3()
{
    if(isDay)
    {
        glBegin(GL_TRIANGLES);


        glColor3f(0.95f, 0.85f, 0.4f);
        glVertex2f(603,430);

        glColor3f(0.85f, 0.9f, 0.3f);
        glVertex2f(749, 430);

        glColor3f(0.9f, 0.8f, 0.2f);
        glVertex2f(670,365);
        glEnd();
    }
    else
    {
        glBegin(GL_TRIANGLES);


        glColor3f(0.235f, 0.7f, 0.62f);
        glVertex2f(603,430);

        glColor3f(0.85f, 0.9f, 0.3f);
        glVertex2f(749, 430);

        glColor3f(0.5f, 0.75f, 0.2f);
        glVertex2f(670,365);
        glEnd();
    }



}


void field4()
{
    if(isDay)
    {
        glBegin(GL_POLYGON);


        glColor3f(0.95f, 0.85f, 0.4f);
        glVertex2f(780, 430);


        glColor3f(0.7f, 0.85f, 0.3f);
        glVertex2f(737, 303);


        glColor3f(0.5f, 0.75f, 0.2f);
        glVertex2f(902, 130);

        glColor3f(0.85f, 0.8f, 0.3f);
        glVertex2f(1200,330);


        glColor3f(0.85f, 0.8f, 0.3f);
        glVertex2f(1200,430);

        glEnd();
    }
    else
    {
        glBegin(GL_POLYGON);


        glColor3f(0.235f, 0.7f, 0.62f);
        glVertex2f(780, 430);


        glColor3f(0.85f, 0.9f, 0.3f);
        glVertex2f(737, 303);


        glColor3f(0.5f, 0.75f, 0.2f);
        glVertex2f(902, 130);

        glColor3f(0.85f, 0.9f, 0.3f);
        glVertex2f(1200,330);


        glColor3f(0.235f, 0.7f, 0.62f);
        glVertex2f(1200,430);

        glEnd();
    }





    glBegin(GL_QUADS);
    glColor3f(0.99, 0.84, 0.02);
    glVertex2f(862,280);
    glVertex2f(855,320);
    glVertex2f(960,320);
    glVertex2f(955,280);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.55, 0.56, 0.16);
    glVertex2f(832,270);
    glVertex2f(913,270);
    glColor3f(0.58, 0.54, 0.17);
    glVertex2f(936,253);
    glVertex2f(845,253);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.93, 0.65, 0.49);
    glVertex2f(881,280);
    glVertex2f(887,280);
    glColor3f(0.71, 0.72, 0.38);
    glVertex2f(885,253.5);
    glVertex2f(884,253.5);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.93, 0.65, 0.49);
    glVertex2f(907,280);
    glVertex2f(913,280);
    glColor3f(0.71, 0.72, 0.38);
    glVertex2f(911,253.5);
    glVertex2f(910,253.5);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.93, 0.65, 0.49);
    glVertex2f(933,280);
    glVertex2f(939,280);
    glColor3f(0.71, 0.72, 0.38);
    glVertex2f(937,253.5);
    glVertex2f(936,253.5);
    glEnd();





}

void field5()
{
    if(isDay)
    {
        glBegin(GL_POLYGON);


        glColor3f(0.95f, 0.85f, 0.4f);
        glVertex2f(1030, 0);


        glColor3f(0.7f, 0.85f, 0.3f);
        glVertex2f(1004,28);


        glColor3f(0.5f, 0.75f, 0.2f);
        glVertex2f(1200, 270);

        glColor3f(0.85f, 0.8f, 0.3f);
        glVertex2f(1200, 0);

        glEnd();
    }
    else
    {
        glBegin(GL_POLYGON);


        glColor3f(0.235f, 0.7f, 0.62f);
        glVertex2f(1030, 0);


        glColor3f(0.85f, 0.9f, 0.3f);
        glVertex2f(1004,28);


        glColor3f(0.5f, 0.75f, 0.2f);
        glVertex2f(1200, 270);

        glColor3f(0.235f, 0.7f, 0.62f);
        glVertex2f(1200, 0);

        glEnd();
    }
}

void big_filed()
{
    if(isDay)
    {
        glBegin(GL_POLYGON);

        glColor3f(0.92f, 0.69f, 0.34f);
        glVertex2f(1000,0);
        glVertex2f(1200,0);
        glVertex2f(1200,430);
        glVertex2f(780,430);
        glVertex2f(723,300);

        glEnd();
    }
    else
    {
        glBegin(GL_POLYGON);

        glColor3f(0.59f, 0.89f, 0.8f);
        glVertex2f(1000,0);
        glVertex2f(1200,0);
        glVertex2f(1200,430);
        glVertex2f(780,430);
        glVertex2f(723,300);

        glEnd();
    }




}

void road1()
{

    glBegin(GL_POLYGON);

    glColor3f(0.45f, 0.65f, 0.6f); // Unified blue-green color
    glVertex2f(55, 0);
    glVertex2f(482, 430);
    glVertex2f(603, 430);
    glVertex2f(1000, 0);

    glEnd();


}

void road2()
{

    glBegin(GL_POLYGON);

    glColor3f(0.45f, 0.65f, 0.6f);
    glVertex2f(8, 430);
    glVertex2f(71, 430);
    glVertex2f(361, 300);
    glVertex2f(240, 180);

    glEnd();
}

void road3()
{
    glBegin(GL_QUADS);

    glColor3f(0.45f, 0.65f, 0.6f);
    glVertex2f(723,300);
    glVertex2f(780,430);
    glVertex2f(749,430);
    glVertex2f(662,365);

    glEnd();
}

void roadstarucureline1()
{

    if(isDay)
    {
        glBegin(GL_QUADS);

        glColor3f(1.0f,0.89f,0.10f);
        glVertex2f(122,0);
        glVertex2f(484,430);
        glVertex2f(490,430);
        glVertex2f(134,0);
        glEnd();
    }
    else
    {

        glBegin(GL_QUADS);

        glColor3f(0.404, 0.776, 0.678);
        glVertex2f(122,0);
        glVertex2f(484,430);
        glVertex2f(490,430);
        glVertex2f(134,0);
        glEnd();
    }

}


void crossline1()
{
    if(isDay)
    {
        glBegin(GL_QUADS);
        glColor3f(1.0f,0.89f,0.10f);
        glVertex2f(206,45);
        glVertex2f(280,142);
        glVertex2f(310,142);
        glVertex2f(238,45);
        glEnd();
    }
    else
    {
        glBegin(GL_QUADS);
        glColor3f(0.404, 0.776, 0.678);
        glVertex2f(206,45);
        glVertex2f(280,142);
        glVertex2f(310,142);
        glVertex2f(238,45);
        glEnd();
    }








}

void crossline2()
{
    if(isDay)
    {
        glBegin(GL_QUADS);
        glColor3f(1.0f,0.89f,0.10f);
        glVertex2f(270,45);
        glVertex2f(332,142);
        glVertex2f(360,142);
        glVertex2f(300,45);
        glEnd();
    }
    else
    {
        glBegin(GL_QUADS);
        glColor3f(0.404, 0.776, 0.678);
        glVertex2f(270,45);
        glVertex2f(332,142);
        glVertex2f(360,142);
        glVertex2f(300,45);
        glEnd();
    }



}


void crossline3()
{
    if(isDay)
    {
        glBegin(GL_QUADS);
        glColor3f(1.0f,0.89f,0.10f);
        glVertex2f(334,45);
        glVertex2f(384,142);
        glVertex2f(410,142);
        glVertex2f(362,45);
        glEnd();

    }
    else
    {

        glBegin(GL_QUADS);
        glColor3f(0.404, 0.776, 0.678);
        glVertex2f(334,45);
        glVertex2f(384,142);
        glVertex2f(410,142);
        glVertex2f(362,45);
        glEnd();

    }



}


void crossline4()
{
    if(isDay)
    {
        glBegin(GL_QUADS);
        glColor3f(1.0f,0.89f,0.10f);
        glVertex2f(398,45);
        glVertex2f(436,142);
        glVertex2f(460,142);
        glVertex2f(424,45);
        glEnd();
    }
    else
    {

        glBegin(GL_QUADS);
        glColor3f(0.404, 0.776, 0.678);
        glVertex2f(398,45);
        glVertex2f(436,142);
        glVertex2f(460,142);
        glVertex2f(424,45);
        glEnd();
    }

}


void crossline5()
{
    if(isDay)
    {
        glBegin(GL_QUADS);
        glColor3f(1.0f,0.89f,0.10f);
        glVertex2f(458,45);
        glVertex2f(488,142);
        glVertex2f(510,142);
        glVertex2f(482,45);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(1.0f,0.89f,0.10f);
        glVertex2f(592,45);
        glVertex2f(565,142);
        glVertex2f(589,142);
        glVertex2f(618,45);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(1.0f,0.89f,0.10f);
        glVertex2f(653,45);
        glVertex2f(618,142);
        glVertex2f(642,142);
        glVertex2f(679,45);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(1.0f,0.89f,0.10f);
        glVertex2f(707,45);
        glVertex2f(669,142);
        glVertex2f(693,142);
        glVertex2f(734,45);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(1.0f,0.89f,0.10f);
        glVertex2f(764,45);
        glVertex2f(720,142);
        glVertex2f(744,142);
        glVertex2f(793,45);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(1.0f,0.89f,0.10f);
        glVertex2f(820,45);
        glVertex2f(771,142);
        glVertex2f(795,142);
        glVertex2f(849,45);
        glEnd();

    }
    else
    {
        glBegin(GL_QUADS);
        glColor3f(0.404, 0.776, 0.678);
        glVertex2f(458,45);
        glVertex2f(488,142);
        glVertex2f(510,142);
        glVertex2f(482,45);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.404, 0.776, 0.678);
        glVertex2f(592,45);
        glVertex2f(565,142);
        glVertex2f(589,142);
        glVertex2f(618,45);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(0.404, 0.776, 0.678);
        glVertex2f(653,45);
        glVertex2f(618,142);
        glVertex2f(642,142);
        glVertex2f(679,45);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(0.404, 0.776, 0.678);
        glVertex2f(707,45);
        glVertex2f(669,142);
        glVertex2f(693,142);
        glVertex2f(734,45);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.404, 0.776, 0.678);
        glVertex2f(764,45);
        glVertex2f(720,142);
        glVertex2f(744,142);
        glVertex2f(793,45);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.404, 0.776, 0.678);
        glVertex2f(820,45);
        glVertex2f(771,142);
        glVertex2f(795,142);
        glVertex2f(849,45);
        glEnd();

    }



}

void crossrunwayline1()
{
    if(isDay)
    {
        glBegin(GL_QUADS);
        glColor3f(1.0f,0.89f,0.10f);
        glVertex2f(522,0);
        glVertex2f(524,60);
        glVertex2f(554,60);
        glVertex2f(558,0);
        glEnd();
    }
    else
    {

        glBegin(GL_QUADS);
        glColor3f(0.404, 0.776, 0.678);
        glVertex2f(522,0);
        glVertex2f(524,60);
        glVertex2f(554,60);
        glVertex2f(558,0);
        glEnd();
    }

}

void crossrunwayline2()
{
    if(isDay)
    {
        glBegin(GL_QUADS);
        glColor3f(1.0f,0.89f,0.10f);
        glVertex2f(524,95);
        glVertex2f(526.75,185);
        glVertex2f(547.73,185);
        glVertex2f(553,95);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(1.0f,0.89f,0.10f);
        glVertex2f(527.5,210);
        glVertex2f(529.5,269);
        glVertex2f(543,269);
        glVertex2f(546.5,210);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(1.0f,0.89f,0.10f);
        glVertex2f(531,365);
        glVertex2f(532,395);
        glVertex2f(537,395);
        glVertex2f(539,365);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(1.0f,0.89f,0.10f);
        glVertex2f(530,292);
        glVertex2f(531,345);
        glVertex2f(539.5,345);
        glVertex2f(542,292);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(1.0f,0.89f,0.10f);
        glVertex2f(531.75,410);
        glVertex2f(532.5,430);
        glVertex2f(535,430);
        glVertex2f(536.5,410);
        glEnd();
    }
    else
    {
        glBegin(GL_QUADS);
        glColor3f(0.404, 0.776, 0.678);
        glVertex2f(524,95);
        glVertex2f(526.75,185);
        glVertex2f(547.73,185);
        glVertex2f(553,95);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(0.404, 0.776, 0.678);
        glVertex2f(527.5,210);
        glVertex2f(529.5,269);
        glVertex2f(543,269);
        glVertex2f(546.5,210);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(0.404, 0.776, 0.678);
        glVertex2f(531,365);
        glVertex2f(532,395);
        glVertex2f(537,395);
        glVertex2f(539,365);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(0.404, 0.776, 0.678);
        glVertex2f(530,292);
        glVertex2f(531,345);
        glVertex2f(539.5,345);
        glVertex2f(542,292);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(0.404, 0.776, 0.678);
        glVertex2f(531.75,410);
        glVertex2f(532.5,430);
        glVertex2f(535,430);
        glVertex2f(536.5,410);
        glEnd();
    }

}

void line2()
{
    if(isDay)
    {
        glBegin(GL_QUADS);
        glColor3f(1.0f,0.89f,0.10f);
        glVertex2f(273,180);
        glVertex2f(8,430);
        glVertex2f(9,430);
        glVertex2f(282,180);
        glEnd();
    }
    else
    {
        glBegin(GL_QUADS);
        glColor3f(0.404, 0.776, 0.678);
        glVertex2f(273,180);
        glVertex2f(8,430);
        glVertex2f(9,430);
        glVertex2f(282,180);
        glEnd();
    }

}

void line3()
{
    if(isDay)
    {
        glColor3f(1.0f,0.89f,0.10f);
        glBegin(GL_QUADS);

        glVertex2f(350,275);
        glVertex2f(73,430);
        glVertex2f(75,430);
        glVertex2f(362.50,275);
        glEnd();
    }
    else
    {
        glBegin(GL_QUADS);
        glColor3f(0.404, 0.776, 0.678);
        glVertex2f(350,275);
        glVertex2f(73,430);
        glVertex2f(75,430);
        glVertex2f(362.50,275);
        glEnd();
    }


}

void tiles3()
{
    if(isDay)

    {
        glBegin(GL_TRIANGLES);
        glColor3f(0.92f, 0.69f, 0.34f);
        glVertex2f(603,430);
        glVertex2f(800,430);
        glVertex2f(660,360);
    }
    else
    {
        glBegin(GL_TRIANGLES);
        glColor3f(0.59f, 0.89f, 0.8f);
        glVertex2f(603,430);
        glVertex2f(800,430);
        glVertex2f(660,360);
    }

}

void longline()
{
    if(isDay)
    {
        glBegin(GL_QUADS);
        glColor3f(1.0f,0.89f,0.10f);
        glVertex2f(930,0);
        glVertex2f(596,430);
        glVertex2f(602,430);
        glVertex2f(942,0);
        glEnd();
    }
    else
    {
        glBegin(GL_QUADS);
        glColor3f(0.404, 0.776, 0.678);
        glVertex2f(930,0);
        glVertex2f(596,430);
        glVertex2f(602,430);
        glVertex2f(942,0);
        glEnd();
    }


}

void building1()
{
    if(isDay)
    {
        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(0,430);
        glVertex2f(0,500);
        glVertex2f(12,500);
        glVertex2f(12,430);


        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(12,430);
        glVertex2f(12,470);
        glVertex2f(24,470);
        glVertex2f(24,430);


        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(24,430);
        glVertex2f(24,460);
        glVertex2f(34,460);
        glVertex2f(34,430);


        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(34,430);
        glVertex2f(34,486);
        glVertex2f(44,486);
        glVertex2f(44,430);


        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(44,430);
        glVertex2f(44,520);
        glVertex2f(56,520);
        glVertex2f(56,430);

    }
    else
    {

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(0,430);
        glVertex2f(0,500);
        glVertex2f(12,500);
        glVertex2f(12,430);


        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(12,430);
        glVertex2f(12,470);
        glVertex2f(24,470);
        glVertex2f(24,430);


        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(24,430);
        glVertex2f(24,460);
        glVertex2f(34,460);
        glVertex2f(34,430);


        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(34,430);
        glVertex2f(34,486);
        glVertex2f(44,486);
        glVertex2f(44,430);


        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(44,430);
        glVertex2f(44,520);
        glVertex2f(56,520);
        glVertex2f(56,430);

    }
    glEnd();
}


void building2()
{
    if(isDay)
    {
        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(65,430);
        glVertex2f(65,445);
        glVertex2f(72,445);
        glVertex2f(72,430);

        glEnd();


        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(72,430);
        glVertex2f(72,480);
        glVertex2f(79,480);
        glVertex2f(79,430);


        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(79,430);
        glVertex2f(79,500);
        glVertex2f(85,500);
        glVertex2f(85,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(85,430);
        glVertex2f(85,490);
        glVertex2f(91,490);
        glVertex2f(91,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(91,430);
        glVertex2f(91,530);
        glVertex2f(102,530);
        glVertex2f(102,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(102,430);
        glVertex2f(102,515);
        glVertex2f(120,515);
        glVertex2f(120,430);


        glEnd();
    }

    else
    {
        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(65,430);
        glVertex2f(65,445);
        glVertex2f(72,445);
        glVertex2f(72,430);

        glEnd();


        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(72,430);
        glVertex2f(72,480);
        glVertex2f(79,480);
        glVertex2f(79,430);


        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(79,430);
        glVertex2f(79,500);
        glVertex2f(85,500);
        glVertex2f(85,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(85,430);
        glVertex2f(85,490);
        glVertex2f(91,490);
        glVertex2f(91,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(91,430);
        glVertex2f(91,530);
        glVertex2f(102,530);
        glVertex2f(102,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(102,430);
        glVertex2f(102,515);
        glVertex2f(120,515);
        glVertex2f(120,430);


        glEnd();
    }


}

void building3()
{
    if(isDay)
    {
        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(330,430);
        glVertex2f(333,534);
        glVertex2f(365,534);
        glVertex2f(365,430);

        glBegin(GL_QUADS);

        glColor3f(0.70,0.86,0.69);
        glVertex2f(365,430);
        glVertex2f(365,445);
        glVertex2f(375,445);
        glVertex2f(375,430);


        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(375,430);
        glVertex2f(375,460);
        glVertex2f(385,460);
        glVertex2f(385,430);


        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(385,430);
        glVertex2f(385,540);
        glVertex2f(405,540);
        glVertex2f(405,430);


        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(405,430);
        glVertex2f(405,520);
        glVertex2f(410,520);
        glVertex2f(410,430);


        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(405,430);
        glVertex2f(405,508);
        glVertex2f(421,508);
        glVertex2f(421,430);


        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(421,430);
        glVertex2f(421,480);
        glVertex2f(434,480);
        glVertex2f(434,430);


        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(434,430);
        glVertex2f(434,443);
        glVertex2f(444,443);
        glVertex2f(444,430);


        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(444,430);
        glVertex2f(444,465);
        glVertex2f(460,465);
        glVertex2f(460,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(460,430);
        glVertex2f(460,534);
        glVertex2f(480,534);
        glVertex2f(480,430);


        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(480,440);
        glVertex2f(495,440);
        glColor3f(0.84, 0.95, 0.75);
        glVertex2f(495,430);
        glVertex2f(480,430);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(495,500);
        glVertex2f(510,500);
        glColor3f(0.84, 0.95, 0.75);
        glVertex2f(510,430);
        glVertex2f(495,430);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(510,480);
        glVertex2f(520,480);
        glColor3f(0.84, 0.95, 0.75);
        glVertex2f(520,430);
        glVertex2f(510,430);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(520,550);
        glVertex2f(540,550);
        glColor3f(0.84, 0.95, 0.75);
        glVertex2f(540,430);
        glVertex2f(520,430);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(540,485);
        glVertex2f(552,485);
        glColor3f(0.84, 0.95, 0.75);
        glVertex2f(552,430);
        glVertex2f(540,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(552,495);
        glVertex2f(564,495);
        glColor3f(0.84, 0.95, 0.75);
        glVertex2f(564,430);
        glVertex2f(552,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(564,541);
        glVertex2f(589,546);
        glColor3f(0.84, 0.95, 0.75);
        glVertex2f(589,430);
        glVertex2f(564,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(589,450);
        glVertex2f(605,450);
        glColor3f(0.84, 0.95, 0.75);
        glVertex2f(605,430);
        glVertex2f(589,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(605,510);
        glVertex2f(620,510);
        glColor3f(0.84, 0.95, 0.75);
        glVertex2f(620,430);
        glVertex2f(605,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(620,470);
        glVertex2f(630,470);
        glVertex2f(630,430);
        glVertex2f(620,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(630,540);
        glVertex2f(640,540);
        glVertex2f(640,430);
        glVertex2f(630,430);


        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(640,580);
        glVertex2f(655,580);
        glVertex2f(655,430);
        glVertex2f(640,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(655,540);
        glVertex2f(665,540);
        glVertex2f(665,430);
        glVertex2f(655,430);


        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(655,540);
        glVertex2f(665,540);
        glVertex2f(665,430);
        glVertex2f(655,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(665,520);
        glVertex2f(685,520);
        glVertex2f(685,430);
        glVertex2f(665,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(685,500);
        glVertex2f(700,500);
        glVertex2f(700,430);
        glVertex2f(685,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(700,520);
        glVertex2f(715,520);
        glVertex2f(715,430);
        glVertex2f(700,430);


        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(715,490);
        glVertex2f(725,490);
        glVertex2f(725,430);
        glVertex2f(715,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(725,540);
        glVertex2f(735,540);
        glVertex2f(735,430);
        glVertex2f(725,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(735,595);
        glVertex2f(750,590);
        glVertex2f(750,430);
        glVertex2f(735,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(750,570);
        glVertex2f(760,570);
        glVertex2f(760,430);
        glVertex2f(750,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(760,510);
        glVertex2f(766,510);
        glVertex2f(766,430);
        glVertex2f(760,430);


        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(776,500);
        glVertex2f(795,500);
        glVertex2f(795,430);
        glVertex2f(776,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(795,480);
        glVertex2f(808,480);
        glVertex2f(808,430);
        glVertex2f(795,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(808,445);
        glVertex2f(820,445);
        glVertex2f(820,430);
        glVertex2f(808,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(820,510);
        glVertex2f(836,510);
        glVertex2f(836,430);
        glVertex2f(820,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(836,560);
        glVertex2f(848,560);
        glVertex2f(848,430);
        glVertex2f(836,430);


        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(848,560);
        glVertex2f(858,560);
        glVertex2f(858,430);
        glVertex2f(848,430);


        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(858,440);
        glVertex2f(868,440);
        glVertex2f(868,430);
        glVertex2f(858,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(868,460);
        glVertex2f(878,460);
        glVertex2f(878,430);
        glVertex2f(868,430);

        glBegin(GL_QUADS);
        glColor3f(0.70,0.86,0.69);
        glVertex2f(878,492);
        glVertex2f(890,492);
        glVertex2f(890,430);
        glVertex2f(878,430);

        glEnd();
    }
    else
    {

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(330,430);
        glVertex2f(333,534);
        glVertex2f(365,534);
        glVertex2f(365,430);

        glBegin(GL_QUADS);

        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(365,430);
        glVertex2f(365,445);
        glVertex2f(375,445);
        glVertex2f(375,430);


        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(375,430);
        glVertex2f(375,460);
        glVertex2f(385,460);
        glVertex2f(385,430);


        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(385,430);
        glVertex2f(385,540);
        glVertex2f(405,540);
        glVertex2f(405,430);


        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(405,430);
        glVertex2f(405,520);
        glVertex2f(410,520);
        glVertex2f(410,430);


        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(405,430);
        glVertex2f(405,508);
        glVertex2f(421,508);
        glVertex2f(421,430);


        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(421,430);
        glVertex2f(421,480);
        glVertex2f(434,480);
        glVertex2f(434,430);


        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(434,430);
        glVertex2f(434,443);
        glVertex2f(444,443);
        glVertex2f(444,430);


        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(444,430);
        glVertex2f(444,465);
        glVertex2f(460,465);
        glVertex2f(460,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(460,430);
        glVertex2f(460,534);
        glVertex2f(480,534);
        glVertex2f(480,430);


        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(480,440);
        glVertex2f(495,440);
        glColor3f(0.84, 0.95, 0.75);
        glVertex2f(495,430);
        glVertex2f(480,430);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(495,500);
        glVertex2f(510,500);
        glColor3f(0.84, 0.95, 0.75);
        glVertex2f(510,430);
        glVertex2f(495,430);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(510,480);
        glVertex2f(520,480);
        glColor3f(0.84, 0.95, 0.75);
        glVertex2f(520,430);
        glVertex2f(510,430);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(520,550);
        glVertex2f(540,550);
        glColor3f(0.84, 0.95, 0.75);
        glVertex2f(540,430);
        glVertex2f(520,430);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(540,485);
        glVertex2f(552,485);
        glColor3f(0.84, 0.95, 0.75);
        glVertex2f(552,430);
        glVertex2f(540,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(552,495);
        glVertex2f(564,495);
        glColor3f(0.84, 0.95, 0.75);
        glVertex2f(564,430);
        glVertex2f(552,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(564,541);
        glVertex2f(589,546);
        glColor3f(0.84, 0.95, 0.75);
        glVertex2f(589,430);
        glVertex2f(564,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(589,450);
        glVertex2f(605,450);
        glColor3f(0.84, 0.95, 0.75);
        glVertex2f(605,430);
        glVertex2f(589,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(605,510);
        glVertex2f(620,510);
        glColor3f(0.84, 0.95, 0.75);
        glVertex2f(620,430);
        glVertex2f(605,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(620,470);
        glVertex2f(630,470);
        glVertex2f(630,430);
        glVertex2f(620,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(630,540);
        glVertex2f(640,540);
        glVertex2f(640,430);
        glVertex2f(630,430);


        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(640,580);
        glVertex2f(655,580);
        glVertex2f(655,430);
        glVertex2f(640,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(655,540);
        glVertex2f(665,540);
        glVertex2f(665,430);
        glVertex2f(655,430);


        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(655,540);
        glVertex2f(665,540);
        glVertex2f(665,430);
        glVertex2f(655,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(665,520);
        glVertex2f(685,520);
        glVertex2f(685,430);
        glVertex2f(665,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(685,500);
        glVertex2f(700,500);
        glVertex2f(700,430);
        glVertex2f(685,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(700,520);
        glVertex2f(715,520);
        glVertex2f(715,430);
        glVertex2f(700,430);


        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(715,490);
        glVertex2f(725,490);
        glVertex2f(725,430);
        glVertex2f(715,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(725,540);
        glVertex2f(735,540);
        glVertex2f(735,430);
        glVertex2f(725,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(735,595);
        glVertex2f(750,590);
        glVertex2f(750,430);
        glVertex2f(735,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(750,570);
        glVertex2f(760,570);
        glVertex2f(760,430);
        glVertex2f(750,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(760,510);
        glVertex2f(766,510);
        glVertex2f(766,430);
        glVertex2f(760,430);


        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(776,500);
        glVertex2f(795,500);
        glVertex2f(795,430);
        glVertex2f(776,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(795,480);
        glVertex2f(808,480);
        glVertex2f(808,430);
        glVertex2f(795,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(808,445);
        glVertex2f(820,445);
        glVertex2f(820,430);
        glVertex2f(808,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(820,510);
        glVertex2f(836,510);
        glVertex2f(836,430);
        glVertex2f(820,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(836,560);
        glVertex2f(848,560);
        glVertex2f(848,430);
        glVertex2f(836,430);


        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(848,560);
        glVertex2f(858,560);
        glVertex2f(858,430);
        glVertex2f(848,430);


        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(858,440);
        glVertex2f(868,440);
        glVertex2f(868,430);
        glVertex2f(858,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(868,460);
        glVertex2f(878,460);
        glVertex2f(878,430);
        glVertex2f(868,430);

        glBegin(GL_QUADS);
        glColor3f(0.37f, 0.78f, 0.69f);
        glVertex2f(878,492);
        glVertex2f(890,492);
        glVertex2f(890,430);
        glVertex2f(878,430);

        glEnd();
    }

}

void fench()
{
    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(910,470);
    glVertex2f(912,470);
    glVertex2f(912,430);
    glVertex2f(910,430);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(960,470);
    glVertex2f(962,470);
    glVertex2f(962,430);
    glVertex2f(960,430);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(1010,470);
    glVertex2f(1012,470);
    glVertex2f(1012,430);
    glVertex2f(1010,430);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(910,470);
    glVertex2f(1012,470);
    glVertex2f(1012,468);
    glVertex2f(910,468);
    glEnd();







}

void fench2()
{

    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(1055,470);
    glVertex2f(1057,470);
    glVertex2f(1057,430);
    glVertex2f(1055,430);

    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(1105,470);
    glVertex2f(1107,470);
    glVertex2f(1107,430);
    glVertex2f(1105,430);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(1155,470);
    glVertex2f(1157,470);
    glVertex2f(1157,430);
    glVertex2f(1155,430);

    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(1055,470);
    glVertex2f(1157,470);
    glVertex2f(1157,468);
    glVertex2f(1055,468);

    glEnd();
}
void signalline()
{
    glBegin(GL_QUADS);
    glColor3f(0.569, 0.353, 0.522);
    glVertex2f(692,490);
    glVertex2f(693,540);
    glVertex2f(696,540);
    glVertex2f(695,490);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.937, 0.686, 0.533);
    glVertex2f(693,540);
    glVertex2f(694,590);
    glVertex2f(697,590);
    glVertex2f(696,540);
    glEnd();



    glBegin(GL_QUADS);
    glColor3f(0.937, 0.686, 0.533);
    glVertex2f(690,430);
    glVertex2f(692,490);
    glVertex2f(695,490);
    glVertex2f(694,430);
    glEnd();


    //

    glBegin(GL_QUADS);
    glColor3f(0.937, 0.686, 0.533);
    glVertex2f(723,430);
    glVertex2f(720,490);
    glVertex2f(723,490);
    glVertex2f(726,430);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.569, 0.353, 0.522);
    glVertex2f(720,490);
    glVertex2f(718,540);
    glVertex2f(721,540);
    glVertex2f(723,490);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.937, 0.686, 0.533);
    glVertex2f(718,540);
    glVertex2f(716,590);
    glVertex2f(719,590);
    glVertex2f(721,540);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.636, 0.391, 0.545);
    glVertex2f(685,590);
    glColor3f(0.636, 0.391, 0.545);
    glVertex2f(685,610);
    glColor3f(0.509, 0.318, 0.499);
    glVertex2f(730,610);
    glColor3f(0.509, 0.318, 0.499);
    glVertex2f(730,590);

    glEnd();



}


void tower()
{
    if(isDay)
    {
        glBegin(GL_QUADS);
        glColor3f(0.81,0.50,0.61);
        glVertex2f(120,430);
        glVertex2f(98,583);
        glVertex2f(144,610);
        glVertex2f(143,430);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.88, 0.61, 0.48);
        glVertex2f(143, 430);
        glColor3f(0.88, 0.61, 0.48);
        glVertex2f(144, 700);
        glColor3f(0.81, 0.50, 0.61);
        glVertex2f(170, 700);
        glColor3f(0.88, 0.61, 0.48);
        glVertex2f(187, 430);
        glEnd();

        glBegin(GL_QUADS);

// Sunlit Effect (Warmer Tint)
        glColor3f(0.32, 0.85, 0.70); // Slightly more red and less blue for sunlight
        glVertex2f(187,430);
        glVertex2f(175,612);

// Original Blue-Green (Shaded Side)
        glColor3f(0.24, 0.79, 0.79);
        glVertex2f(348,600);
        glVertex2f(330,430);
        glEnd();





        glBegin(GL_QUADS);
        glColor3f(0.92, 0.59, 0.50);
        glVertex2f(177,572);
        glVertex2f(175,612);
        glColor3f(0.96, 0.77, 0.56);
        glVertex2f(348,600);
        glVertex2f(344,560);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.92, 0.59, 0.50);
        glVertex2f(181,520);
        glVertex2f(179,550);
        glColor3f(0.96, 0.77, 0.56);
        glVertex2f(342,540);
        glVertex2f(339,516);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.747, 0.261, 0.312);
        glVertex2f(181,508);
        glVertex2f(180,522);
        glVertex2f(390,515);
        glVertex2f(386,503);
        glEnd();
        // FIXED LINE DRAWING
        glLineWidth(2.0f);
        glColor3f(0.212, 0.506, 0.565);
        glBegin(GL_LINES);  // FIXED
        glVertex2f(228,430);
        glVertex2f(232,506);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.808, 0.329, 0.302);
        glVertex2f(208,430);
        glVertex2f(230,508);
        glVertex2f(245,508);
        glVertex2f(212,430);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.808, 0.329, 0.302);
        glVertex2f(350,430);
        glVertex2f(372,503);
        glVertex2f(385,503);
        glVertex2f(354,430);
        glEnd();

        glLineWidth(2.0f);
        glColor3f(0.212, 0.506, 0.565);
        glBegin(GL_LINES);  // FIXED
        glVertex2f(208,430);
        glVertex2f(212,506);
        glEnd();

        glLineWidth(2.0f);
        glColor3f(0.212, 0.506, 0.565);
        glBegin(GL_LINES);  // FIXED
        glVertex2f(248,430);
        glVertex2f(252,506);
        glEnd();

        glLineWidth(2.0f);
        glColor3f(0.212, 0.506, 0.565);
        glBegin(GL_LINES);  // FIXED
        glVertex2f(268,430);
        glVertex2f(272,506);
        glEnd();

        glLineWidth(2.0f);
        glColor3f(0.212, 0.506, 0.565);
        glBegin(GL_LINES);  // FIXED
        glVertex2f(288,430);
        glVertex2f(292,506);
        glEnd();

        glLineWidth(2.0f);
        glColor3f(0.212, 0.506, 0.565);
        glBegin(GL_LINES);  // FIXED
        glVertex2f(308,430);
        glVertex2f(312,506);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(0.92, 0.59, 0.50);
        glVertex2f(133,700);
        glVertex2f(133,712);
        glVertex2f(182,712);
        glVertex2f(182,700);
        glEnd();


        glBegin(GL_QUADS);

// Top-left: Slightly darker blue-green shadow
        glColor3f(0.32, 0.85, 0.70);
        glVertex2f(135,712);
        glVertex2f(110,775);

// Center: Bright Sunlit Glow (Adding Warm Light)
        glColor3f(0.95, 0.95, 0.75);
        glVertex2f(205,775);
        glVertex2f(180,712);
        glEnd();

        glLineWidth(1.0f);
        glColor3f(0.212, 0.506, 0.565);
        glBegin(GL_LINES);
        glVertex2f(144,712);
        glVertex2f(130,772);
        glEnd();


        glLineWidth(1.0f);
        glColor3f(0.212, 0.506, 0.565);
        glBegin(GL_LINES);
        glVertex2f(152,712);
        glVertex2f(142,772);
        glEnd();


        glLineWidth(1.0f);
        glColor3f(0.212, 0.506, 0.565);
        glBegin(GL_LINES);
        glVertex2f(160,712);
        glVertex2f(160,772);
        glEnd();

        glLineWidth(1.0f);
        glColor3f(0.212, 0.506, 0.565);
        glBegin(GL_LINES);
        glVertex2f(167,712);
        glVertex2f(178,772);
        glEnd();


        glLineWidth(1.0f);
        glColor3f(0.212, 0.506, 0.565);
        glBegin(GL_LINES);
        glVertex2f(173,712);
        glVertex2f(190,772);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.88, 0.61, 0.48);
        glVertex2f(108,772);
        glVertex2f(103,780);
        glVertex2f(211,780);
        glVertex2f(206,772);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.34f, 0.32f, 0.58f);
        glVertex2f(110,780);
        glVertex2f(113,790);
        glVertex2f(200,790);
        glVertex2f(203,780);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.34f, 0.32f, 0.58f);
        glVertex2f(140,790);
        glVertex2f(138,794);
        glVertex2f(160,805);
        glVertex2f(160,790);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.50f, 0.45f, 0.75f);
        glVertex2f(160,790);
        glVertex2f(160,805);
        glVertex2f(182,794);
        glVertex2f(180,790);
        glEnd();


    }
    else
    {
        glBegin(GL_QUADS);
        glColor3f(0.298, 0.502, 0.588);
        glVertex2f(120,430);
        glVertex2f(98,583);
        glVertex2f(144,610);
        glVertex2f(143,430);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.173, 0.173, 0.227);
        glVertex2f(143, 430);
        glVertex2f(144, 700);
        glColor3f(0.383, 0.585, 0.618);
        glVertex2f(170, 700);
        glVertex2f(187, 430);
        glEnd();

        glBegin(GL_QUADS);

// Sunlit Effect (Warmer Tint)
        glColor3f(0.784, 0.675, 0.349);

// Slightly more red and less blue for sunlight
        glVertex2f(187,430);
        glVertex2f(175,612);

// Original Blue-Green (Shaded Side)
        glColor3f(1.000, 0.859, 0.388);
        glVertex2f(348,600);
        glVertex2f(330,430);
        glEnd();





        glBegin(GL_QUADS);
        glColor3f(0.173, 0.173, 0.227);
        glVertex2f(177,572);
        glVertex2f(175,612);
        glColor3f(0.383, 0.585, 0.618);
        glVertex2f(348,600);
        glVertex2f(344,560);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.173, 0.173, 0.227);
        glVertex2f(181,520);
        glVertex2f(179,550);
        glColor3f(0.383, 0.585, 0.618);
        glVertex2f(342,540);
        glVertex2f(339,516);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.747, 0.261, 0.312);
        glVertex2f(181,508);
        glVertex2f(180,522);
        glVertex2f(390,515);
        glVertex2f(386,503);
        glEnd();
        // FIXED LINE DRAWING
        glLineWidth(2.0f);
        glColor3f(0.212, 0.506, 0.565);
        glBegin(GL_LINES);  // FIXED
        glVertex2f(228,430);
        glVertex2f(232,506);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.808, 0.329, 0.302);
        glVertex2f(208,430);
        glVertex2f(230,508);
        glVertex2f(245,508);
        glVertex2f(212,430);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.808, 0.329, 0.302);
        glVertex2f(350,430);
        glVertex2f(372,503);
        glVertex2f(385,503);
        glVertex2f(354,430);
        glEnd();

        glLineWidth(2.0f);
        glColor3f(0.212, 0.506, 0.565);
        glBegin(GL_LINES);  // FIXED
        glVertex2f(208,430);
        glVertex2f(212,506);
        glEnd();

        glLineWidth(2.0f);
        glColor3f(0.212, 0.506, 0.565);
        glBegin(GL_LINES);  // FIXED
        glVertex2f(248,430);
        glVertex2f(252,506);
        glEnd();

        glLineWidth(2.0f);
        glColor3f(0.212, 0.506, 0.565);
        glBegin(GL_LINES);  // FIXED
        glVertex2f(268,430);
        glVertex2f(272,506);
        glEnd();

        glLineWidth(2.0f);
        glColor3f(0.212, 0.506, 0.565);
        glBegin(GL_LINES);  // FIXED
        glVertex2f(288,430);
        glVertex2f(292,506);
        glEnd();

        glLineWidth(2.0f);
        glColor3f(0.212, 0.506, 0.565);
        glBegin(GL_LINES);  // FIXED
        glVertex2f(308,430);
        glVertex2f(312,506);
        glEnd();


        glBegin(GL_QUADS);
        glColor3f(0.92, 0.59, 0.50);
        glVertex2f(133,700);
        glVertex2f(133,712);
        glVertex2f(182,712);
        glVertex2f(182,700);
        glEnd();


        glBegin(GL_QUADS);

// Top-left: Slightly darker blue-green shadow
        glColor3f(0.784, 0.675, 0.349);
        glVertex2f(135,712);
        glVertex2f(110,775);

// Center: Bright Sunlit Glow (Adding Warm Light)
        glColor3f(1.000, 0.859, 0.388);
        glVertex2f(205,775);
        glVertex2f(180,712);
        glEnd();

        glLineWidth(1.0f);
        glColor3f(0.212, 0.506, 0.565);
        glBegin(GL_LINES);
        glVertex2f(144,712);
        glVertex2f(130,772);
        glEnd();


        glLineWidth(1.0f);
        glColor3f(0.212, 0.506, 0.565);
        glBegin(GL_LINES);
        glVertex2f(152,712);
        glVertex2f(142,772);
        glEnd();


        glLineWidth(1.0f);
        glColor3f(0.212, 0.506, 0.565);
        glBegin(GL_LINES);
        glVertex2f(160,712);
        glVertex2f(160,772);
        glEnd();

        glLineWidth(1.0f);
        glColor3f(0.212, 0.506, 0.565);
        glBegin(GL_LINES);
        glVertex2f(167,712);
        glVertex2f(178,772);
        glEnd();


        glLineWidth(1.0f);
        glColor3f(0.212, 0.506, 0.565);
        glBegin(GL_LINES);
        glVertex2f(173,712);
        glVertex2f(190,772);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.88, 0.61, 0.48);
        glVertex2f(108,772);
        glVertex2f(103,780);
        glVertex2f(211,780);
        glVertex2f(206,772);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.34f, 0.32f, 0.58f);
        glVertex2f(110,780);
        glVertex2f(113,790);
        glVertex2f(200,790);
        glVertex2f(203,780);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.34f, 0.32f, 0.58f);
        glVertex2f(140,790);
        glVertex2f(138,794);
        glVertex2f(160,805);
        glVertex2f(160,790);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.50f, 0.45f, 0.75f);
        glVertex2f(160,790);
        glVertex2f(160,805);
        glVertex2f(182,794);
        glVertex2f(180,790);
        glEnd();


    }





}


void semcircle()
{
    if(isDay)
    {
        glBegin(GL_QUADS);
        glColor3f(0.569, 0.353, 0.522);
        glVertex2f(940,430);
        glVertex2f(940,498);
        glVertex2f(1070,488);
        glVertex2f(1070,430);
        glEnd();


        glBegin(GL_POLYGON);

        glColor3f(0.937, 0.686, 0.533);


        // Define semi-circle at (800, 480)
        float radius = 70.0;  // Adjust size for better visibility
        float pi = 3.14159265359;

        for (int i = 0; i <= 180; i++)
        {
            float angle = i * pi / 180.0;
            float x = cos(angle) * radius + 940; // Centered at (800, 480)
            float y = sin(angle) * radius + 430;
            glVertex2f(x, y);
        }

        glEnd();
    }
    else
    {
        glBegin(GL_QUADS);
        glColor3f(0.220, 0.373, 0.439);
        glVertex2f(940,430);
        glVertex2f(940,498);
        glVertex2f(1070,488);
        glVertex2f(1070,430);
        glEnd();


        glBegin(GL_POLYGON);

        glColor3f(0.298, 0.502, 0.588);


        // Define semi-circle at (800, 480)
        float radius = 70.0;  // Adjust size for better visibility
        float pi = 3.14159265359;

        for (int i = 0; i <= 180; i++)
        {
            float angle = i * pi / 180.0;
            float x = cos(angle) * radius + 940; // Centered at (800, 480)
            float y = sin(angle) * radius + 430;
            glVertex2f(x, y);
        }

        glEnd();
    }





}

void semcircle1()
{
    if(isDay)
    {
        glBegin(GL_QUADS);
        glColor3f(0.569, 0.353, 0.522);
        glVertex2f(1100,430);
        glVertex2f(1100,498);
        glVertex2f(1200,485);
        glVertex2f(1200,430);
        glEnd();



        glBegin(GL_POLYGON);

        glColor3f(0.937, 0.686, 0.533);


        // Define semi-circle at (800, 480)
        float radius = 70.0;  // Adjust size for better visibility
        float pi = 3.14159265359;

        for (int i = 0; i <= 180; i++)
        {
            float angle = i * pi / 180.0;
            float x = cos(angle) * radius + 1100; // Centered at (800, 480)
            float y = sin(angle) * radius + 430;
            glVertex2f(x, y);
        }

        glEnd();

    }
    else
    {
        glBegin(GL_QUADS);
        glColor3f(0.220, 0.373, 0.439);
        glVertex2f(1100,430);
        glVertex2f(1100,498);
        glVertex2f(1200,485);
        glVertex2f(1200,430);
        glEnd();



        glBegin(GL_POLYGON);

        glColor3f(0.298, 0.502, 0.588);


        // Define semi-circle at (800, 480)
        float radius = 70.0;  // Adjust size for better visibility
        float pi = 3.14159265359;

        for (int i = 0; i <= 180; i++)
        {
            float angle = i * pi / 180.0;
            float x = cos(angle) * radius + 1100; // Centered at (800, 480)
            float y = sin(angle) * radius + 430;
            glVertex2f(x, y);
        }

        glEnd();
    }



}
void text()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor3f(0.713, 0.451, 0.322);
    glLoadIdentity(); // Reset any transformations
    glRasterPos2f(110,210); // Ensure it's inside the viewport

    renderBitmapString(110,210, GLUT_BITMAP_HELVETICA_18, "A");

    glRasterPos2f(160,210); // Another text
    renderBitmapString(160,210, GLUT_BITMAP_HELVETICA_18, "B");

    glRasterPos2f(865,290); // Another text
    renderBitmapString(875,295, GLUT_BITMAP_HELVETICA_18, "A");

    glRasterPos2f(925,290); // Another text
    renderBitmapString(925,295, GLUT_BITMAP_HELVETICA_18, "C");

    glDisable(GL_BLEND);

}


void tree()
{
    //glPushMatrix(); // Save the transformation state

    //glTranslatef(treePositionX, 0, 0); // Move tree left or right

    // Trunk

    if(isDay)
    {
        glColor3f(0.396f, 0.270f, 0.125f);
        glLineWidth(5);
        glBegin(GL_LINES);
        glVertex2f(120, 430);
        glVertex2f(120, 530);
        glEnd();

        // Leaves
        glBegin(GL_TRIANGLES);
        glColor3f(0.73f, 0.77f, 0.21f);
        glVertex2f(100, 490);
        glVertex2f(120, 550);
        glVertex2f(140, 490);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3f(0.73f, 0.77f, 0.21f);
        glVertex2f(100, 510);
        glVertex2f(120, 550);
        glVertex2f(140, 510);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3f(0.73f, 0.77f, 0.21f);
        glVertex2f(105, 530);
        glVertex2f(120, 580);
        glVertex2f(135, 530);
        glEnd();
    }
    else
    {

        glColor3f(0.220, 0.373, 0.439);
        glLineWidth(5);
        glBegin(GL_LINES);
        glVertex2f(120, 430);
        glVertex2f(120, 530);
        glEnd();

        // Leaves
        glBegin(GL_TRIANGLES);
        glColor3f(0.220, 0.373, 0.439);
        glVertex2f(100, 490);
        glVertex2f(120, 550);
        glVertex2f(140, 490);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3f(0.220, 0.373, 0.439);
        glVertex2f(100, 510);
        glVertex2f(120, 550);
        glVertex2f(140, 510);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3f(0.220, 0.373, 0.439);
        glVertex2f(105, 530);
        glVertex2f(120, 580);
        glVertex2f(135, 530);
        glEnd();
    }



}

void plane()
{
    if (!newPlaneIncoming ) return;

    if(isRaining) return;
    glPushMatrix();
    glTranslatef(planeX, planeY, 0.0f); // Move the plane
    glScalef(planeScale, planeScale, 0.0f); // Scale the plane

    //plan left wings
    glBegin(GL_POLYGON);
    glColor3f(0.945, 0.765, 0.682);
    glVertex2f(537.5719744607954,758.5557657961883);
    glVertex2f(514.9646794671613,757.6395564240689);
    glVertex2f(491.7312830317819,756.0507924938971);
    glVertex2f(457.3799983094299,754.1625097881391);
    glVertex2f(383.0405809061926,747.7735626579216);
    glVertex2f(370.0508874406583,746.2564764813659);
    glVertex2f(360,745);
    glVertex2f(354.769017490881,744.7612444654292);
    glVertex2f(351.0042823539069,744.5088114118831);
    glVertex2f(346.336773803004,743.7672048046468);
    glVertex2f(289.8536881986875,737.6814747553881);
    glVertex2f(277.9851006955707,736.0325600563591);
    glVertex2f(272.3051755736215,735.4222378291961);
    glVertex2f(268.3372665032408,734.8829226708942);
    glVertex2f(265.0113039417206,735.5769017514396);
    glVertex2f(262.6856929373332,736.2260076067239);
    glVertex2f(261.2547467660567,736.7843876483346);
    glVertex2f(259.2534597338089,737.613611019473);
    glVertex2f(257.5474487376421,738.291102810801);
    glVertex2f(255.7646084987166,739.0403920440299);
    glVertex2f(254.7856236958655,739.4399043877352);
    glVertex2f(253.7320863215713,739.847661025118);
    glVertex2f(252.3192311986121,740.4031213601082);
    glVertex2f(251.3295920602233,740.8855373826821);
    glVertex2f(250.3000743932638,741.5299797454925);
    glVertex2f(249.2950690517081,741.8982325242414);
    glVertex2f(248.2900637101524,742.3892362292398);
    glVertex2f(247.4321323210195,742.8802399342383);
    glVertex2f(246.3781023286562,743.5860577601735);
    glVertex2f(245.6182202411384,744.0463737336096);
    glVertex2f(244.7357765266017,744.537377438608);
    glVertex2f(243.778627374898,745.115876644723);
    glVertex2f(242.9289724046953,745.5522701225174);
    glVertex2f(242,746);
    glVertex2f(241.077160290151,746.6705284093655);
    glVertex2f(240.1839332701943,747.3523932184193);
    glVertex2f(239.23914235135,748.0241908383267);
    glVertex2f(238.3298922602565,748.6407797879094);
    glVertex2f(237.4964130100875,749.2099388182935);
    glVertex2f(236.3977358166829,750.0162474446709);
    glVertex2f(235.2990586232783,750.869985990247);
    glVertex2f(234,752);
    glVertex2f(232.8599937648849,753.5498970783376);
    glVertex2f(232.5351707941803,754.8511957471278);
    glVertex2f(235.0038253715353,756.3151567495167);
    glVertex2f(237.0826923840448,757.5351242515075);
    glVertex2f(238.9666656141316,758.5924294198995);
    glVertex2f(240.9156034383593,759.324409921094);
    glVertex2f(242.4747536977414,760.0563904222885);
    glVertex2f(244.3587269278281,760.5443774230848);
    glVertex2f(246.8273815051832,761.439020257878);
    glVertex2f(248.8412839235517,762.1710007590725);
    glVertex2f(250.9201509360613,763.309637094264);
    glVertex2f(252.9340533544298,763.8789552618596);
    glVertex2f(255,765);
    glVertex2f(257.0917873794489,765.7495720982455);
    glVertex2f(259.6903711450858,766.7255460998381);
    glVertex2f(261.7692381575952,767.7828512682302);
    glVertex2f(264.5875499242408,768.9482202961098);
    glVertex2f(269.7694573413148,770.9226429558687);
    glVertex2f(275.1766650808704,772.8970656156275);
    glVertex2f(280,775);
    glVertex2f(284.9263599283583,776.9355728801945);
    glVertex2f(289.6474591176634,778.1858685865041);
    glVertex2f(295,780);
    glVertex2f(300.0883515555494,781.7094292133764);
    glVertex2f(305.4449833280302,783.6417043958547);
    glVertex2f(309.6213403031846,785.2329898402487);
    glVertex2f(315.2503431827406,786.8242752846427);
    glVertex2f(320.0622327410707,787.5062547608115);
    glVertex2f(325.055703037451,788.6428872210929);
    glVertex2f(330,790);
    glVertex2f(334.8610628921614,792.6211008320778);
    glVertex2f(339.9453235575669,794.439712768528);
    glVertex2f(344.8480034849221,795.3490187367531);
    glVertex2f(349.4783123052021,796.7129776890907);
    glVertex2f(354.6533633396326,798.0769366414285);
    glVertex2f(360,800);
    glVertex2f(363.9373458855447,800.4967999376665);
    glVertex2f(369.5228212550386,801.8649227738977);
    glVertex2f(379.3581148404517,804.7531820948301);
    glVertex2f(389.8005253138533,807.3374141188223);
    glVertex2f(400,810);
    glVertex2f(409.9568059950703,811.5937962759859);
    glVertex2f(419.9135229580812,814.6340692453884);
    glVertex2f(429.7488165434943,817.0662876209105);
    glVertex2f(439.4626867513097,818.2823968086716);
    glVertex2f(450.026520602309,821.3226697780742);
    glVertex2f(460.7117778309059,822.8428062627754);
    glVertex2f(469.818531150733,825.4270382867677);
    glVertex2f(490.0602390139351,828.6405951560399);
    glVertex2f(500,830);
    glVertex2f(509.5914822256858,832.5981057814472);
    glVertex2f(519.7522445901803,835.0008800897302);
    glVertex2f(524.1552416147946,835.8489180808889);
    glVertex2f(519.0599453791617,805.2305241960266);
    glEnd();

    //plan ar pakha

    glBegin(GL_POLYGON);
    glColor3f(0.902, 0.604, 0.573);
    glVertex2f(384.2041767214269,793.2676341751477);
    glVertex2f(388.7816642581166,795.783549915155);
    glVertex2f(393.0242136823657,796.7619615918246);
    glVertex2f(397.0434710316542,797.6006001718271);
    glVertex2f(400.3928521560614,797.6006001718271);
    glVertex2f(402.9607110181069,797.7403732684942);
    glVertex2f(405.9751540300733,798.0199194618283);
    glVertex2f(407.8731366672373,797.46082707516);
    glVertex2f(410.2177034543223,796.7619615918246);
    glVertex2f(412.6739162788875,795.3642306251538);
    glVertex2f(415.1301291034528,794.3858189484843);
    glVertex2f(418.5911562653402,792.9880879818135);
    glVertex2f(421.3823072023461,791.5903570151427);
    glVertex2f(424.2851041768323,790.0528529518049);
    glVertex2f(427.1879011513185,787.5369372117974);
    glVertex2f(429.8674060508442,786.1392062451266);
    glVertex2f(434.3332475500537,782.5051057317826);
    glVertex2f(438.687443011783,778.5914590251044);
    glVertex2f(441.7018860237494,775.0971316084275);
    glVertex2f(445.0512671481566,770.7641656117481);
    glVertex2f(448.2890022350834,767.8289305817394);
    glVertex2f(450.2986309097277,764.3346031650625);
    glVertex2f(452.6431976968127,761.2595950383868);
    glVertex2f(454.4282504939737,757.6642291986702);
    glVertex2f(456,755);
    glVertex2f(456.8695217154375,752.6431611742399);
    glVertex2f(457.1310864891658,750.8421259046073);
    glVertex2f(457.3054630049847,749.0410906349748);
    glVertex2f(457.3054630049847,747.8949772815722);
    glVertex2f(457.1746806181205,746.2030956646447);
    glVertex2f(457.0874923602111,744.8386750058321);
    glVertex2f(456.5643628127546,743.419677520667);
    glVertex2f(455.8880602925237,741.5718168830252);
    glVertex2f(454.6944196337032,738.7404067839234);
    glVertex2f(452.9981934343266,736.2235978069439);
    glVertex2f(450.925028079533,734.0213899520868);
    glVertex2f(448.9146859173089,732.1337832193522);
    glVertex2f(446.2132886368203,730.1675262060869);
    glVertex2f(443.0093058157756,728.5945205954747);
    glVertex2f(440.307908535287,727.3361161069851);
    glVertex2f(438.2347431804934,726.7069138627402);
    glVertex2f(435.6589922851437,726.7069138627402);
    glVertex2f(433.0832413897941,726.3923127406177);
    glVertex2f(430.2561977241664,726.3136624600871);
    glVertex2f(426.2983365922877,726.549613301679);
    glVertex2f(423.7854088895077,726.7069138627402);
    glVertex2f(420.1416637204765,727.3361161069851);
    glVertex2f(415.8152089751178,727.5540996260745);
    glVertex2f(411.440241172853,729.3209242389383);
    glVertex2f(406.2185054088595,731.6177962356614);
    glVertex2f(402.4080495810806,733.207938387239);
    glVertex2f(398.3153377660586,736.2115402291076);
    glVertex2f(393.7992419701724,739.568506993549);
    glVertex2f(390.1299141360148,741.8653789902721);
    glVertex2f(386.8839702827216,744.6922983708544);
    glVertex2f(384.6287598468704,746.5045289644124);
    glVertex2f(381.3057131469149,751.1720973847226);
    glVertex2f(379.3605150786483,754.5205703819016);
    glVertex2f(377.7395166884261,757.5646367429736);
    glVertex2f(376.5237678957594,761.014578618855);
    glVertex2f(375,765);
    glVertex2f(374.20974734789,767.866414687787);
    glVertex2f(374.2766167704743,772.973083362749);
    glVertex2f(374.5440944608116,777.7448885180413);
    glVertex2f(375.6191360509681,782.1174724683109);
    glVertex2f(376.9625190055856,784.7959302058581);
    glVertex2f(378.0322498768551,786.8826356525518);
    glVertex2f(379.1517356723697,788.6267476676989);
    glEnd();

    //left pakha

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(381.7554261690275,783.7230495532689);
    glVertex2f(383.710021360351,786.5075868623662);
    glVertex2f(385.9342158884088,788.5327049053462);
    glVertex2f(388.0236107480995,790.0515434375812);
    glVertex2f(390.5174046128916,791.5703819698161);
    glVertex2f(393.0785983118673,792.8360807466786);
    glVertex2f(395.3701926741086,793.0892205020511);
    glVertex2f(397.9987862072679,793.2579803389661);
    glVertex2f(401.1665784138957,793.4267401758812);
    glVertex2f(403.9299716154221,793.5111200943386);
    glVertex2f(407.0977638220498,792.8360807466786);
    glVertex2f(409.591557686842,792.4985610728486);
    glVertex2f(411.4787530439819,791.4860020513587);
    glVertex2f(414.0399467429576,790.6422028667837);
    glVertex2f(416.6011404419332,788.870245791762);
    glVertex2f(418.4209359648896,787.8576655576862);
    glVertex2f(420.8473299954982,786.1700671885362);
    glVertex2f(422.3975261817203,783.8074294717263);
    glVertex2f(424.2173217046767,781.1916519995439);
    glVertex2f(425.4305187199809,779.166533956564);
    glVertex2f(426.7111155694688,776.0444769736365);
    glVertex2f(427.3177140771209,774.103738849114);
    glVertex2f(428.0591122531401,769.9691228446966);
    glVertex2f(427.924312584773,766.0876465956517);
    glVertex2f(427.5873134138552,762.0374105096918);
    glVertex2f(426.9807149062031,759.5060129559669);
    glVertex2f(425.9023175592659,755.793296543837);
    glVertex2f(424.7565203781452,753.6837985823995);
    glVertex2f(423.6781230312081,751.405540784047);
    glVertex2f(421.9257273424353,748.4522436380346);
    glVertex2f(420.3081313220296,746.5958854319697);
    glVertex2f(418.8253349699911,744.6551473074472);
    glVertex2f(417.0729392812182,742.9675489382972);
    glVertex2f(415.3205435924454,741.7862300798922);
    glVertex2f(413.4333482353055,741.0268108137748);
    glVertex2f(410,740);
    glVertex2f(407.5695626613348,739.5079722815398);
    glVertex2f(404.6039699572577,739.2548325261673);
    glVertex2f(401.8405767557314,739.6767321184548);
    glVertex2f(398.3357853781857,741.1111907322323);
    glVertex2f(396.1789906843115,742.1237497537222);
    glVertex2f(392.1350006332973,744.3176276336172);
    glVertex2f(389.1694079292202,747.3553046980871);
    glVertex2f(387.0800130695295,749.9710821702696);
    glVertex2f(383.8448210287181,754.0213182562295);
    glVertex2f(382.1598251741289,758.0715543421804);
    glVertex2f(380.407429485356,762.1217904281493);
    glVertex2f(380,765);
    glVertex2f(379.332455244043,767.0335611111503);
    glVertex2f(378.8081654007837,770.0200652049627);
    glVertex2f(379,774);
    glVertex2f(379.2287002142048,777.5726379499621);
    glVertex2f(380.2528576841327,780.210957795719);

    glEnd();


    //left 2nd pakha

    glBegin(GL_POLYGON);
    glColor3f(0.902, 0.604, 0.573);
    glVertex2f(284.0639146174032,760.1973504573464);
    glVertex2f(285.462861432718,765.1596062594884);
    glVertex2f(288.0275972607952,769.1002211611896);
    glVertex2f(290.7046986795463,771.213723949015);
    glVertex2f(292.9917551570335,773.0609730525822);
    glVertex2f(295.7952437423404,774.2616849699009);
    glVertex2f(298.3774042814388,775.0005846113278);
    glVertex2f(301.0333408359401,775.0929470665061);
    glVertex2f(304.1319334828582,775.1853095216844);
    glVertex2f(306.8616460527622,775.0005846113278);
    glVertex2f(310,775);
    glVertex2f(312.6161752541817,773.8922351491874);
    glVertex2f(315.4934398548913,772.9686105974039);
    glVertex2f(318.370704455601,771.7678986800852);
    glVertex2f(320,770);
    glVertex2f(323.4612495183951,768.7199376591993);
    glVertex2f(326.4860661499104,766.1337889142053);
    glVertex2f(329.1420027044117,764.1941773554597);
    glVertex2f(331.5028351973017,762.1622033415358);
    glVertex2f(333.9374437055945,759.3913296861851);
    glVertex2f(337.1835883833182,756.5280935756559);
    glVertex2f(339.249316814597,753.4801325547702);
    glVertex2f(341.7641288479216,750.5708880283962);
    glVertex2f(342.8690330852106,748.4553085824599);
    glVertex2f(344.038931689399,746.7465713376652);
    glVertex2f(345,745);
    glVertex2f(346.9534070850211,741.9898799824831);
    glVertex2f(347.4214505036467,739.9979850807508);
    glVertex2f(347.4718608002364,738.2785487602142);
    glVertex2f(347.2990444534642,736.5786238305611);
    glVertex2f(346.9657027185463,734.2265431689768);
    glVertex2f(346,732);
    glVertex2f(345.0311668317274,729.866520916512);
    glVertex2f(344.1522145036487,728.5460560814922);
    glVertex2f(342.6404164993534,726.9174827849678);
    glVertex2f(341.1989346813044,725.3769404774447);
    glVertex2f(339.1382307001767,723.837930885);
    glVertex2f(336.0319890325116,721.8363430004118);
    glVertex2f(333.1541474874689,720.8641432101534);
    glVertex2f(330.5047060650487,720.1778845346769);
    glVertex2f(328,720);
    glVertex2f(325.2058232202081,720.349449203546);
    glVertex2f(321.6427813072982,720.8069549871971);
    glVertex2f(319.2674200320248,721.3788372167608);
    glVertex2f(316.3895784869822,721.8935312233682);
    glVertex2f(313.7401370645619,722.8085427906702);
    glVertex2f(311.4561358383376,723.4376132431904);
    glVertex2f(308.8980544649663,724.8673188170998);
    glVertex2f(306.522693189693,725.8967068303147);
    glVertex2f(304.55845213514,727.0976595123985);
    glVertex2f(301.774243209489,728.2347729867198);
    glVertex2f(299.3033203238842,730.2305304725305);
    glVertex2f(296.3541542991301,732.1265000840507);
    glVertex2f(293.8035242236671,734.222045444152);
    glVertex2f(291.7311372873534,736.6169544271248);
    glVertex2f(288.8616784524576,740.1095300272937);
    glVertex2f(287.3472418451514,742.9035905074287);
    glVertex2f(286,745);
    glVertex2f(285.0657528633188,747.7114932175966);
    glVertex2f(284.493638245596,750.9454869677579);
    glVertex2f(284.011087384684,756.066987325435);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(288.9057831797016,763.6276106826192);
    glVertex2f(290.8768231306933,766.341976550004);
    glVertex2f(293.7019803937814,768.9740889062558);
    glVertex2f(296.9870469787676,770.8659196623119);
    glVertex2f(300.1407109003544,771.8529617959064);
    glVertex2f(303.2286734902414,772.1819758404378);
    glVertex2f(307.1050520605251,771.9352153070392);
    glVertex2f(310.3244173138115,771.5239477513749);
    glVertex2f(313.9379905572964,770.2901450843818);
    glVertex2f(316.3032384984864,768.7273283728572);
    glVertex2f(319.1283957615745,766.7532441056683);
    glVertex2f(321.4279423710648,763.792117704885);
    glVertex2f(323.3989823220566,760.0907097039058);
    glVertex2f(324.6473076243513,755.8957806361293);
    glVertex2f(325.1072169462494,751.6185980572201);
    glVertex2f(324.8444116194505,746.1076128113177);
    glVertex2f(323.8588916439546,743.0642328994015);
    glVertex2f(322.2163583514616,739.3628248984223);
    glVertex2f(319.3912010883734,736.0726844531074);
    glVertex2f(317.354459805682,733.7695861413871);
    glVertex2f(314.2007958840952,731.7955018741982);
    glVertex2f(310.1930146504121,730.8907132517365);
    glVertex2f(305.3968174363322,731.0552202740023);
    glVertex2f(301.651841529448,732.1245159187297);
    glVertex2f(298.1696709493626,734.3453607193171);
    glVertex2f(294.4246950424783,737.5532476534992);
    glVertex2f(291.7309404427897,740.6788810765482);
    glVertex2f(289.9570044868971,744.2980355663946);
    glVertex2f(288.3144711944041,748.6574716564367);
    glVertex2f(287.131847223809,752.6056401908145);
    glVertex2f(287.3946525506079,757.6231043699196);
    glVertex2f(287.854561872506,761.3245123708988);
    glEnd();


    //plan ar muk

    glBegin(GL_POLYGON);
    glColor3f(0.945, 0.765, 0.682);
    glVertex2f(525.6238023694199,835.8781365146606);
    glVertex2f(527.6814642256498,843.6062863719235);
    glVertex2f(530,850);
    glVertex2f(532.0025541237328,856.2289311387864);
    glVertex2f(533.6486836087167,860.7370185555232);
    glVertex2f(533.6486836087167,860.7370185555232);
    glVertex2f(535.8092285577583,864.3434884889126);
    glVertex2f(537.9697735067997,868.3363659151652);
    glVertex2f(540.6447339198986,873.1020583271439);
    glVertex2f(543.3196943329976,876.7085282605334);
    glVertex2f(545.4802392820391,879.7997882034385);
    glVertex2f(548.3609658807611,883.7926656296911);
    glVertex2f(551.1388093866715,887.0127280702173);
    glVertex2f(554.0195359853935,890.2327905107436);
    glVertex2f(557.414678048173,893.968062941754);
    glVertex2f(559.8785385391336,896.1868153124943);
    glVertex2f(562.5509043879426,898.2372412955849);
    glVertex2f(565,900);
    glVertex2f(567.505545004113,902.0234065402267);
    glVertex2f(569.5002704469867,903.3928705648844);
    glVertex2f(571.1732659797195,904.6817778822093);
    glVertex2f(573.4897213327342,906.1317986141997);
    glVertex2f(575.5487927576362,907.5818193461902);
    glVertex2f(578.0582860567355,909.1929534928463);
    glVertex2f(580,910);
    glVertex2f(582.1120829245112,911.0457577615008);
    glVertex2f(584.1711543494132,912.1735516641601);
    glVertex2f(585.7798039001178,913.0596754448209);
    glVertex2f(587.7101833609635,913.5430156888177);
    glVertex2f(590.1553306780345,914.3485827621457);
    glVertex2f(593.7587056716129,915.0735931281409);
    glVertex2f(594.7595023282811,919.3740509793622);
    glVertex2f(595.0656879192494,923.3989438128993);
    glVertex2f(595.8311518966702,927.6154982099382);
    glVertex2f(596.2904302831228,932.1195449522298);
    glVertex2f(596.7497086695752,935.9527762222651);
    glVertex2f(597.0765284143358,938.923610278791);
    glVertex2f(597.3436584416854,941.9334647062547);
    glVertex2f(598.2340918661839,946.0580800327789);
    glVertex2f(598.8573952633329,949.6253149097729);
    glVertex2f(599.480698660482,953.1925497867668);
    glVertex2f(600.2820887425307,957.3171651132911);
    glVertex2f(601.1725221670292,960.884399990285);
    glVertex2f(602.597215646227,965.0090153168093);
    glVertex2f(603.9328657829749,962.8909696085941);
    glVertex2f(605,960);
    glVertex2f(605.1794725772728,957.3171651132911);
    glVertex2f(605.8027759744218,954.9761672252638);
    glVertex2f(606.1589493442212,951.8548367078942);
    glVertex2f(606.96033942627,949.4023627299607);
    glVertex2f(607.1384261111697,945.9466039428729);
    glVertex2f(607.9398161932185,942.9367495154092);
    glVertex2f(608.7412062752671,939.5924668182274);
    glVertex2f(608.830249617717,935.8022797614213);
    glVertex2f(610,930);
    glVertex2f(610.1658997544648,926.5497642992183);
    glVertex2f(610.4330297818144,923.4284337818485);
    glVertex2f(611.0563331789634,920.0841510846667);
    glVertex2f(611.0563331789634,917.5202010168273);
    glVertex2f(611.323463206313,915.1792031288);
    glVertex2f(612.8593903538883,914.2284471644014);
    glVertex2f(614.8958801460639,913.1854518931334);
    glVertex2f(617.1175053738918,912.2583449853396);
    glVertex2f(619.4316983195458,911.4471264410201);
    glVertex2f(621.3756203938952,910.5200195332263);
    glVertex2f(623.5972456217231,909.4770242619585);
    glVertex2f(625.7263031317248,908.6658057176389);
    glVertex2f(627.8553606417265,907.3910337194226);
    glVertex2f(629.7067149982497,906.6957035385773);
    glVertex2f(631.558069354773,905.1891548134124);
    glVertex2f(633.7796945826009,903.6826060882477);
    glVertex2f(636.3715906817333,901.9442806361344);
    glVertex2f(638.5006481917351,900.3218435474953);
    glVertex2f(640.4445702660845,898.3517413684336);
    glVertex2f(642.9438986473908,896.7293042797946);
    glVertex2f(644.795253003914,894.5274253737845);
    glVertex2f(646.8521985745915,892.8990084207286);
    glVertex2f(650,890);
    glVertex2f(653.0688815332071,886.8024379193627);
    glVertex2f(655.3483319513662,883.8190098016729);
    glVertex2f(658.0422279000996,880.8355816839832);
    glVertex2f(660.2180669356151,878.500724896226);
    glVertex2f(662.290294588487,875.3875825125497);
    glVertex2f(665.2950246851511,871.3664402669679);
    glVertex2f(667.1600295727359,868.1235836173051);
    glVertex2f(668.681254156105,865.5111334011957);
    glVertex2f(670.5475474011852,861.772781845998);
    glVertex2f(672.0405819972494,858.1901949389335);
    glVertex2f(673.6580361429857,855.3864312725351);
    glVertex2f(675.0266511893778,852.4269029580036);
    glVertex2f(676.519685785442,848.844316050939);
    glVertex2f(677.8883008318342,845.4174937920078);
    glVertex2f(679.0080767788824,841.3676129405435);
    glVertex2f(680,840);
    glVertex2f(681.2476286729786,836.2273795521467);
    glVertex2f(682.5292305346619,828.6257449408168);
    glVertex2f(683.4252846068116,820.3992294997329);
    glVertex2f(684.0226539882448,809.5551864183042);
    glVertex2f(684.0226539882448,799.459008376974);
    glVertex2f(682.8279152253784,792.354290496038);
    glVertex2f(681.3344917717956,786.745302695299);
    glVertex2f(680,780);
    glVertex2f(676.2568520296138,775.1533945737717);
    glVertex2f(672.3739510502984,768.0486766928357);
    glVertex2f(668.1923653802664,761.3178913319489);
    glVertex2f(663.1147256380847,754.9610384911113);
    glVertex2f(658.6344552773361,749.3520506903723);
    glVertex2f(654.1541849165876,744.8648604497811);
    glVertex2f(649.673914555839,740.3776702091899);
    glVertex2f(643.1028513600744,736.264412488648);
    glVertex2f(638.3238963086093,732.151154768106);
    glVertex2f(633.5449412571442,729.1596946077119);
    glVertex2f(628.1686168242459,726.9160994874163);
    glVertex2f(618.909391412032,725.04643688717);
    glVertex2f(611.4422741441178,722.8028417668744);
    glVertex2f(603.676472185487,722.0549767267759);
    glVertex2f(594.4172467732732,722.4289092468251);
    glVertex2f(585.7553907424926,723.5507068069729);
    glVertex2f(579.4830122374447,725.4203694072193);
    glVertex2f(571.1198408973806,727.2900320074656);
    glVertex2f(564.2500930108995,732.8990198082046);
    glVertex2f(556.7829757429852,738.8819401289928);
    glVertex2f(549.0171737843543,745.9866580099289);
    glVertex2f(542.1474258978732,752.3435108507664);
    glVertex2f(533.186885176376,765.8050815725401);
    glVertex2f(527.8105607434777,774.7794620537225);
    glVertex2f(522.7329210012961,785.2495726151019);
    glVertex2f(519.4473894034137,796.8414807366291);
    glVertex2f(520,820);
    glVertex2f(522.7704439085235,829.5026695208152);
    glEnd();




    //right wing

    glBegin(GL_POLYGON);
    glColor3f(0.945, 0.765, 0.682);
    glVertex2f(681.2297992992479,834.9644379617606);
    glVertex2f(684.9747592770569,834.2318707441863);
    glVertex2f(689.831504248278,833.5725602483694);
    glVertex2f(694.9223092181121,832.473709422008);
    glVertex2f(699.8960841886396,831.7411422044337);
    glVertex2f(704.6357991605541,830.935318265102);
    glVertex2f(710,830);
    glVertex2f(715.2270140977953,828.9573867776514);
    glVertex2f(720.1422740686696,827.6387657860176);
    glVertex2f(724.8234740409308,826.9061985684434);
    glVertex2f(729.8904823246153,825.8245493593716);
    glVertex2f(735,825);
    glVertex2f(739.8365568017433,823.8687699582861);
    glVertex2f(744.5752624426786,822.4997243775261);
    glVertex2f(749.8347049672334,821.717412617092);
    glVertex2f(755,820);
    glVertex2f(759.6245583792756,819.1097067489779);
    glVertex2f(764.9360745921922,818.4577802819495);
    glVertex2f(767.4548615562102,817.9116210041043);
    glVertex2f(769.1221736122174,817.6639682328594);
    glVertex2f(771.2698976165656,817.0979047557281);
    glVertex2f(773.5024002000328,816.5672202459176);
    glVertex2f(775.3675289406509,816.1426726380691);
    glVertex2f(776.950062417539,815.6827460629);
    glVertex2f(778.7304125790381,815.3997143243345);
    glVertex2f(780.1999079504343,815.0459246511274);
    glVertex2f(781.5281056899654,814.9044087818446);
    glVertex2f(782.7150057976314,814.7628929125618);
    glVertex2f(783.4780130097025,814.4798611739961);
    glVertex2f(784.3540583272656,814.267587370072);
    glVertex2f(785.3148822239477,814.019934598827);
    glVertex2f(786.2757061206298,813.8430397622235);
    glVertex2f(787.4343467019229,813.5953869909786);
    glVertex2f(788.6212468095889,813.3477342197338);
    glVertex2f(789.864665970001,812.8524286772439);
    glVertex2f(791.5037184996352,812.640154873319);
    glVertex2f(792.9157102495094,811.9996588516843);
    glVertex2f(793.9963605107778,811.6173177768625);
    glVertex2f(795.3354271388712,811.5584960730438);
    glVertex2f(796.53353938506,811.176154998222);
    glVertex2f(797.8256212191852,810.940868182947);
    glVertex2f(798.8357942895013,810.6761705157627);
    glVertex2f(799.6110433899764,810.5291162562158);
    glVertex2f(800.5977240633084,810.382061996669);
    glVertex2f(801.7018667215609,810.058542625666);
    glVertex2f(802.6180702039406,809.8526666623004);
    glVertex2f(803.5342736863203,809.5879689951161);
    glVertex2f(804.426984771716,809.3820930317505);
    glVertex2f(805.5781122239366,809.0879845126568);
    glVertex2f(806.3533613244117,808.9115194012006);
    glVertex2f(807.6924279525051,808.6762325859257);
    glVertex2f(808.7495858167894,808.3233023630132);
    glVertex2f(810.1674626828197,807.8602053480424);
    glVertex2f(811.8897549626383,807.75239582307);
    glVertex2f(813.8273337774342,807.1594434357215);
    glVertex2f(816.1093710481939,806.2969672359418);
    glVertex2f(818.0900071699853,806.1891577109694);
    glVertex2f(820.5012163617313,805.3805862736759);
    glVertex2f(822.8263109394865,804.7876338863275);
    glVertex2f(825.7972651221735,803.979062449034);
    glVertex2f(828.0793023929332,803.3861100616856);
    glVertex2f(830.2321677427063,802.5775386243921);
    glVertex2f(832.3850330924796,802.308014811961);
    glVertex2f(834.4087265212664,801.7150624246125);
    glVertex2f(836.6477064850307,801.0682052747777);
    glVertex2f(839.1019729837722,800.421348124943);
    glVertex2f(840.9103798775817,799.8283957375945);
    glVertex2f(843.4507609903142,799.1815385877597);
    glVertex2f(845.3452824981146,798.5885862004113);
    glVertex2f(847.7995489968561,798.1573481005215);
    glVertex2f(849.3926693556883,797.6183004756592);
    glVertex2f(851.1671425023524,797.2609318133635);
    glVertex2f(852.7760928764454,796.9252160978067);
    glVertex2f(853.8822462586344,796.5895003822498);
    glVertex2f(854.8878402424425,796.4636069889159);
    glVertex2f(856,796);
    glVertex2f(857.3347856030423,795.7082466289129);
    glVertex2f(858.9772557765956,795.2466375200221);
    glVertex2f(860.0498893593243,794.9948507333545);
    glVertex2f(861.0890031425927,794.6171705533529);
    glVertex2f(862.3962753215433,794.0296680511284);
    glVertex2f(863.5694683026528,793.6519878711268);
    glVertex2f(864.8097008826828,793.4841300133484);
    glVertex2f(866.1169730616334,792.9385919755684);
    glVertex2f(867.1896066443621,792.77073411779);
    glVertex2f(867.9270422324881,792.5189473311224);
    glVertex2f(869.267834210899,792.1832316155654);
    glVertex2f(870,792);
    glVertex2f(871.1784627801345,791.6376935777855);
    glVertex2f(872.6533339563864,791.260013397784);
    glVertex2f(874.0946853331781,790.8403687533379);
    glVertex2f(875.3684377126684,790.3787596444471);
    glVertex2f(876.541630693778,790.168937322224);
    glVertex2f(877.4466652792053,789.7073282133333);
    glVertex2f(878.4522592630134,789.3716124977764);
    glVertex2f(879.4913730462819,789.0358967822195);
    glVertex2f(878.4522592630134,789.3716124977764);
    glVertex2f(880.4299274311604,788.8680389244411);
    glVertex2f(881.5360808133585,788.5742876733287);
    glVertex2f(882.5081549977064,788.1966074933273);
    glVertex2f(883.580788580435,787.9448207066596);
    glVertex2f(884.9277315161486,787.3615599987146);
    glVertex2f(886.5937102634088,786.7358530401655);
    glVertex2f(887.9264932612169,786.2144305747079);
    glVertex2f(889.2425751963881,785.9015770954333);
    glVertex2f(891.0918528810114,785.3801546299757);
    glVertex2f(894.0906146260799,784.441594199152);
    glVertex2f(896.4229848722441,783.7116027405112);
    glVertex2f(899.5050455546756,782.5644733165044);
    glVertex2f(902.1706115502919,781.9387663579553);
    glVertex2f(904.260179985012,780.9206560586105);
    glVertex2f(904.260179985012,780.9206560586105);
    glVertex2f(905.8422952083718,780.7225862040558);
    glVertex2f(907.7408334764034,780.0491486985701);
    glVertex2f(909.3229486097632,779.5341670767282);
    glVertex2f(910.8417793141886,779.098413396708);
    glVertex2f(912.044186883042,778.8211156003315);
    glVertex2f(912.9934560179578,778.3457479494004);
    glVertex2f(914.512286632383,777.8307663275584);
    glVertex2f(915.8412634200052,777.3950126475382);
    glVertex2f(916.8221748584883,777.1177148511618);
    glVertex2f(918.2460785595121,776.4442773456761);
    glVertex2f(919.6699822605358,776.0481376365668);
    glVertex2f(921.6634474419691,775.3747001310812);
    glVertex2f(923.4670587965992,774.7804905674174);
    glVertex2f(924.8593201931558,774.0278251201098);
    glVertex2f(926.7895007656547,773.433615556446);
    glVertex2f(928.6563967292192,772.9582479055149);
    glVertex2f(929.8816125716423,772.2840241265318);
    glVertex2f(929.8816125716423,772.2840241265318);
    glVertex2f(930.7387375530524,772.0157588669977);
    glVertex2f(931.463997152707,771.5411357155142);
    glVertex2f(932.7002351066637,771.1284199316156);
    glVertex2f(934.0188889242175,770.7569757261067);
    glVertex2f(935.0408456328219,770.344250942208);
    glVertex2f(936.1946677231815,769.8902725799195);
    glVertex2f(937.7911482562145,769.1375983033723);
    glVertex2f(939.4271087993994,768.5117871735991);
    glVertex2f(941.1993993878498,767.8290841229376);
    glVertex2f(942.6990298857694,767.3170568349415);
    glVertex2f(944.2895470805325,766.8050295469452);
    glVertex2f(945.7437342300303,766.2361103380606);
    glVertex2f(948.0,765.0);
    glVertex2f(949.3792021037747,764.9275961576259);
    glVertex2f(951.2423793800687,764.1880011860759);
    glVertex2f(952.78745323541,763.4484062145258);
    glVertex2f(954.650630520704,762.5381354803104);
    glVertex2f(954.650630520704,762.5381354803104);
    glVertex2f(955.8321575796709,762.0261081923142);
    glVertex2f(957.3772314260123,761.514080904318);
    glVertex2f(959.3767387565716,760.5469182492141);
    glVertex2f(961.5125761323065,759.8073232776641);
    glVertex2f(962.8758765850506,759.0108363852256);
    glVertex2f(964.5572804766574,758.4419171763409);
    glVertex2f(965.9205809203115,757.7592141256794);
    glVertex2f(967.419948461533,757.2007184832904);
    glVertex2f(968.3037017831484,756.6548955323674);
    glVertex2f(969.211021860007,756.2713442695566);
    glVertex2f(970.2126089578379,755.8582890634527);
    glVertex2f(970.7075108179426,755.6517614604007);
    glVertex2f(970.9431783703734,755.504241743035);
    glVertex2f(971.2377628109119,755.2977141408832);
    glVertex2f(971.567697384315,755.0616825945381);
    glVertex2f(971.7090079157736,754.8551549914861);
    glVertex2f(971.7090079157736,754.8551549914861);
    glVertex2f(971.9329820905828,754.7371392183135);
    glVertex2f(971.980115601069,754.4863557003218);
    glVertex2f(971.9211987120613,754.2650761256233);
    glVertex2f(971.7915815591243,753.9847886643386);
    glVertex2f(971.6030475171797,753.536485429881);
    glVertex2f(971.414513475235,753.217686138717);
    glVertex2f(971.2141960556688,752.9669026207253);
    glVertex2f(970.9715486542294,752.680624596427);
    glVertex2f(970.7193537351847,752.3540067862708);
    glVertex2f(970.5,752.0);
    glVertex2f(970.1813849420078,751.6401376303111);
    glVertex2f(969.9404927123975,751.4390840526797);
    glVertex2f(969.6433922958782,751.1978197595221);
    glVertex2f(969.3857901863768,750.879174579228);
    glVertex2f(969.0847659957977,750.6077031917167);
    glVertex2f(968.7057488757679,750.2836522594771);
    glVertex2f(968.35446471574,749.9711745748175);
    glVertex2f(968.35446471574,749.9711745748175);
    glVertex2f(968.1048680757203,749.7975758611177);
    glVertex2f(967.8737600757021,749.5892574046779);
    glVertex2f(967.4721841689627,749.489350300143);
    glVertex2f(967.2533370927239,749.2382007172286);
    glVertex2f(966.8787942638049,749.047347036101);
    glVertex2f(966.5649725855742,748.8017951744008);
    glVertex2f(966.1923093426752,748.3843570095104);
    glVertex2f(965.6038936959926,748.0896947754701);
    glVertex2f(965.1527750335358,747.7950325414298);
    glVertex2f(964.7212702259686,747.4758151212195);
    glVertex2f(964.2309238537331,747.2548184456801);
    glVertex2f(963.9367160303917,747.0092665830801);
    glVertex2f(963.387528003488,746.7391595361188);
    glVertex2f(963.014864850589,746.4936076744185);
    glVertex2f(962.5245184783535,746.2971661850584);
    glVertex2f(962.0,746.0);
    glVertex2f(961.7007365729977,745.6832865308077);
    glVertex2f(961.7007365729977,745.6832865308077);
    glVertex2f(961.1907763458728,745.4377346691075);
    glVertex2f(960.7396576834161,745.1676276212372);
    glVertex2f(960.023256462419,744.8840032119942);
    glVertex2f(959.4371987817975,744.7113670763799);
    glVertex2f(958.6787711938168,744.1502096356336);
    glVertex2f(958.0237655496518,743.6323612287908);
    glVertex2f(957.1947115461649,743.184952599757);
    glVertex2f(956.4036792480705,742.8454151430989);
    glVertex2f(955.7482524867924,742.5624672625505);
    glVertex2f(954.7538118834738,741.968276713309);
    glVertex2f(954.1887888134064,741.6570340447958);
    glVertex2f(953.2169491328006,741.1194330717537);
    glVertex2f(952.5389214488096,740.8364851912054);
    glVertex2f(951.3862743858721,740.6101268867667);
    glVertex2f(950.6856457789885,740.0725259137247);
    glVertex2f(949.6460033300646,739.4783353645731);
    glVertex2f(948.9679756459836,739.2519770601344);
    glVertex2f(948.9679756459836,739.2519770601344);
    glVertex2f(948.0413378110732,739.0599138437505);
    glVertex2f(947.385911049795,738.7143760870024);
    glVertex2f(946.7078033657141,738.4597229945989);
    glVertex2f(946.0,738.0);
    glVertex2f(944.786804927485,737.8655324454473);
    glVertex2f(943.9279698609826,737.4411106246247);
    glVertex2f(943.2725430997044,736.9600092276925);
    glVertex2f(942.4137080332019,736.6771513471441);
    glVertex2f(941.9390886543454,736.4224982546505);
    glVertex2f(941.4192674298833,736.3659086785408);
    glVertex2f(940.3796249809594,736.0829607979924);
    glVertex2f(939.6789637407578,736.0263721218828);
    glVertex2f(939.1591751496138,735.6868337652247);
    glVertex2f(938.0,735.0);
    glVertex2f(937.1627273272986,735.2017678095474);
    glVertex2f(936.0,735.0);
    glVertex2f(934.511011378817,735.2536391295531);
    glVertex2f(934.511011378817,735.2536391295531);
    glVertex2f(933.2680195279662,735.2536391295531);
    glVertex2f(931.6521301218602,735.3573817695647);
    glVertex2f(930.2019729625343,735.6686096895992);
    glVertex2f(928.6275166181233,735.9798376096336);
    glVertex2f(927.2602255821874,736.0317089296394);
    glVertex2f(925.8100684228616,736.2910655296681);
    glVertex2f(923.6418547383327,736.6929515277748);
    glVertex2f(920.829661630174,737.0837771673037);
    glVertex2f(918.1513824795468,737.5867301324122);
    glVertex2f(915.5177413147633,737.977915771941);
    glVertex2f(857.4654468762693,745.2803324440076);
    glVertex2f(848.6737431024749,745.4424229796941);
    glVertex2f(840.2000894725775,746.6664722173896);
    glVertex2f(829.988250482701,747.7545159842301);
    glVertex2f(821.0800505128088,748.0265269259402);
    glVertex2f(747.7712355748549,755.3169287880623);
    glVertex2f(739.771827326465,755.3482921228409);
    glVertex2f(739.771827326465,755.3482921228409);
    glVertex2f(729.8590529272257,756.302915671454);
    glVertex2f(722.2338418508878,756.8756898006219);
    glVertex2f(716.6302983048093,757.368838995859);
    glVertex2f(710.1860083502738,757.6393886395124);
    glVertex2f(705.7633859259979,757.0666145103445);
    glVertex2f(702.2557888308825,757.4484639297898);
    glVertex2f(696.1556199698122,758.5940121881255);
    glVertex2f(690.3604595517953,758.5940121881255);
    glVertex2f(680.0,760.0);
    glVertex2f(685.3278202414123,758.7849368978481);
    glVertex2f(675.7200542852265,760.1214098659065);
    glVertex2f(670.0,760.0);
    glEnd();

    //right wing pakha
    glBegin(GL_POLYGON);
    glColor3f(0.902, 0.604, 0.573);
    glVertex2f(805.654868479075,797.3345020158049);
    glVertex2f(810.9936985585413,796.5918525679725);
    glVertex2f(815.4427236247632,795.2922160342657);
    glVertex2f(819.7434478554443,793.0642676907685);
    glVertex2f(825.8237821126143,786.9374097461512);
    glVertex2f(830,780);
    glVertex2f(830,770);
    glVertex2f(828.0482946457252,761.6873285198492);
    glVertex2f(825.5271804415328,755.931795299148);
    glVertex2f(822.9585726595259,751.276761181287);
    glVertex2f(817.6188753004924,745.366894818006);
    glVertex2f(815.3476547855748,742.9636989474589);
    glVertex2f(811.4827912531166,739.6372019219526);
    glVertex2f(807.0140427937118,736.7643181271973);
    glVertex2f(802.3037403635284,733.7402299221916);
    glVertex2f(797.9557688895129,732.0769814094385);
    glVertex2f(792.6415815323829,728.7504843839323);
    glVertex2f(787.5689481460315,727.8432579224306);
    glVertex2f(783.1001996866266,727.0872358711791);
    glVertex2f(778.1483432856646,726.6336226404283);
    glVertex2f(773.4380408554812,725.5751917686763);
    glVertex2f(767.7615225421832,726.482418230178);
    glVertex2f(761.9642272434959,728.1456667429311);
    glVertex2f(756.4084859155872,731.7745725889379);
    glVertex2f(751.5774065000145,735.7058872554453);
    glVertex2f(750,740);
    glVertex2f(747.591765982167,745.0805606909628);
    glVertex2f(747.229435025999,751.8847591522256);
    glVertex2f(751.3358525292358,762.1666590492448);
    glVertex2f(756.8915938571445,768.3660398695065);
    glVertex2f(762.3265581996639,774.1118074590172);
    glVertex2f(767.1576376152366,779.2527574075268);
    glVertex2f(772.7133789431452,784.5449117662868);
    glVertex2f(780,790);
    glVertex2f(789.7429338830392,794.5244028428054);
    glVertex2f(795.4194521963373,796.1876513555585);
    glVertex2f(800.8544165388565,797.8508998683117);
    glEnd();


// right inner pakha

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(776.2914683331462,774.3941504418366);
    glVertex2f(779.5275855982572,781.3207279689003);
    glVertex2f(784.5383478152032,787.2017843598035);
    glVertex2f(790,790);
    glVertex2f(794.9774357671743,792.6907703246465);
    glVertex2f(799.4662435865217,793.736291460807);
    glVertex2f(804.4770058034677,793.736291460807);
    glVertex2f(808.7570318637759,793.3442210347469);
    glVertex2f(814.1853575988007,791.1224886204056);
    glVertex2f(817.1083022253526,788.6393759220243);
    glVertex2f(821.7015009242198,784.1959110933419);
    glVertex2f(823.789318514614,780.0138265486996);
    glVertex2f(825.3551817074097,774.7862208678969);
    glVertex2f(825.4595725869293,769.0358546190138);
    glVertex2f(823.6849276350943,762.8934179440705);
    glVertex2f(821.7015009242198,756.7509812691271);
    glVertex2f(819.7180742133453,752.8302770085251);
    glVertex2f(816.7951295867935,748.7788826059029);
    glVertex2f(813.5590123216825,745.9036994814613);
    glVertex2f(808.5482501047364,742.1136853628793);
    glVertex2f(804.5813966829875,740.4147135166185);
    glVertex2f(800,740);
    glVertex2f(794.351090490056,740.4147135166185);
    glVertex2f(789.4447191526297,741.3295445107589);
    glVertex2f(784.5383478152032,744.9888684873209);
    glVertex2f(781.406621429612,748.909572747923);
    glVertex2f(778.170504164501,755.3133897069064);
    glVertex2f(776.395859212666,762.2399672339701);
    glVertex2f(775.9782956945871,767.9903334828532);
    glEnd();


//right 2nd pakah

    glBegin(GL_POLYGON);
    glColor3f(0.902, 0.604, 0.573);
    glVertex2f(884.2020623481606,770.329767257418);
    glVertex2f(888.1837023804418,772.2556884513212);
    glVertex2f(892.165342412723,773.955030681236);
    glVertex2f(896.8709169963281,775.2012149831735);
    glVertex2f(901.5764915799331,775.2012149831735);
    glVertex2f(906.7345252581156,774.294899127219);
    glVertex2f(910.6256734714814,772.4822674153099);
    glVertex2f(915,770);
    glVertex2f(917.7745271658044,766.4779248696112);
    glVertex2f(919.6748553630296,762.9659509277875);
    glVertex2f(920.6702653710998,757.1881873460774);
    glVertex2f(920,750);
    glVertex2f(918.0460026225509,744.9529232906914);
    glVertex2f(916.6886253388186,742.4605546868165);
    glVertex2f(914.3024459087192,738.932080502371);
    glVertex2f(911.3492257427544,735.6970070065164);
    glVertex2f(909.3330496270711,734.068169100608);
    glVertex2f(907.2651672216873,732.588828888492);
    glVertex2f(905,730);
    glVertex2f(900.8645788240707,727.1645814440665);
    glVertex2f(895.8425786967099,725.0688494769022);
    glVertex2f(892.691519793268,723.8360659668054);
    glVertex2f(888.9496373454305,722.6032824567087);
    glVertex2f(885.3062254883256,721.6170556486314);
    glVertex2f(881.6628136312208,720.8773855425734);
    glVertex2f(877.7239900019183,720.5075504895443);
    glVertex2f(873.5882251911506,720.7541071915637);
    glVertex2f(869.8463427433131,721.6170556486314);
    glVertex2f(865.3166955696153,723.2196742117571);
    glVertex2f(861.2794013495801,726.9180247420471);
    glVertex2f(860,730);
    glVertex2f(857.3405777202776,733.0819422925306);
    glVertex2f(856.4543424036846,737.5199629288787);
    glVertex2f(857.0451659480799,742.0812619162365);
    glVertex2f(859.7122722261846,747.1800909797372);
    glVertex2f(861.5282006170079,749.879772975036);
    glVertex2f(864.8763185875882,753.9292959679842);
    glVertex2f(868.2244365581686,757.0552435414882);
    glVertex2f(870.7780858577637,759.8970140628554);
    glVertex2f(874.2964471149837,763.1650501624276);
    glVertex2f(877.0770874634319,765.7226436316581);
    glVertex2f(880.0279710985196,767.8539715226835);
    glVertex2f(882.4681248736883,769.2038125203329);
    glEnd();


//right plan 2nd innner pakha black
    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(881.1414705434228,761.5773421161734);
    glVertex2f(883.4543221829948,765.4119627477448);
    glVertex2f(886.7048163791501,768.1509774845816);
    glVertex2f(890,770);
    glVertex2f(893.6433712978662,771.359537604876);
    glVertex2f(897.2689225166548,772.0638556800626);
    glVertex2f(900.4569072090379,772.0638556800626);
    glVertex2f(902.8322683523821,771.985598116153);
    glVertex2f(905.4576675108153,771.359537604876);
    glVertex2f(908.1455761730207,770.2639317101414);
    glVertex2f(910.833484835226,768.7770379958586);
    glVertex2f(913.2088459785703,766.3510535146603);
    glVertex2f(914.834093076648,763.5337812139139);
    glVertex2f(916.0842831520922,760.7165089131677);
    glVertex2f(916.9594162049033,757.2731761011444);
    glVertex2f(916.9594162049033,753.7515857252114);
    glVertex2f(916.1467926558645,749.4474197101823);
    glVertex2f(915,745);
    glVertex2f(912.6462604446203,741.3086330635817);
    glVertex2f(910.1458802937316,737.943557815468);
    glVertex2f(908.1455761730207,735.9871187177275);
    glVertex2f(906.0202530447652,734.1089371838966);
    glVertex2f(903.3948538863322,732.5437859057042);
    glVertex2f(901.2968511014702,731.795572739365);
    glVertex2f(899.4672160266515,731.069292469748);
    glVertex2f(897.503705214651,730.9016893306056);
    glVertex2f(895.6740701398322,730.845821617558);
    glVertex2f(893.442807853468,730.9016893306056);
    glVertex2f(891.256170812831,731.4603664610802);
    glVertex2f(889.4265357380123,732.2983821567922);
    glVertex2f(887.0613977144661,733.9185458351686);
    glVertex2f(885.4102636225566,735.4828418004976);
    glVertex2f(883.3128770733741,737.829285748491);
    glVertex2f(882,740);
    glVertex2f(880.4122361011006,743.6395279054273);
    glVertex2f(879.5643564322821,746.8798552621801);
    glVertex2f(878.9396029921002,750.7347274624551);
    glVertex2f(879.1181039750093,754.1426579583504);
    glVertex2f(879.6089816780094,758.6679427151948);
    glEnd();

    //plan window
    if(isDay)
    {
        glBegin(GL_POLYGON);
        glColor3f(0,0,0);
        glVertex2f(533.3251665213019,858.4212944441513);
        glVertex2f(535.3665210517819,858.6230550476859);
        glVertex2f(537.5690351504578,859.4973509963355);
        glVertex2f(539.2880705445463,859.7663651342817);
        glVertex2f(541.5980243553527,860.7079146175429);
        glVertex2f(543.9079781661501,861.2459428036351);
        glVertex2f(545.8956128405739,862.0529853077733);
        glVertex2f(548.0444070831845,862.8600277219115);
        glVertex2f(550.0857616136647,863.1962953944601);
        glVertex2f(552.3419955684058,864.1378448776303);
        glVertex2f(552.7180345608626,866.9624033271141);
        glVertex2f(553.20151326545,869.2491135005056);
        glVertex2f(553.6849919700373,871.1322124668282);
        glVertex2f(553.9535912503637,873.4188326402198);
        glVertex2f(555.0,875.0);
        glVertex2f(555.1354280837995,877.3867911763092);
        glVertex2f(555.7263465005175,879.8079184188139);
        glVertex2f(555.0,880.0);
        glVertex2f(553.6849919700373,879.2698901427218);
        glVertex2f(553.6849919700373,879.2698901427218);
        glVertex2f(552.5031551366015,878.6646083321182);
        glVertex2f(551.3750381592309,877.7230588489568);
        glVertex2f(550.2469211818604,877.1850305728648);
        glVertex2f(549.4411233408814,876.3779881587266);
        glVertex2f(548.3667262195761,875.5036922100768);
        glVertex2f(547.5072085225319,874.6966497959386);
        glVertex2f(546.3790915451613,874.0241144508234);
        glVertex2f(545.1972547117255,873.0153114331506);
        glVertex2f(543.7468185979633,872.275522553524);
        glVertex2f(542.3501023402664,871.4684801393857);
        glVertex2f(541.4368647871569,870.6614377252475);
        glVertex2f(540.0,870.0);
        glVertex2f(539.1806308324158,869.5181276385517);
        glVertex2f(538.2673932793062,868.643831689902);
        glVertex2f(537.7839145747189,867.7022822067407);
        glVertex2f(537.0318365898052,866.4917185855334);
        glVertex2f(536.387198317022,864.9448872917685);
        glVertex2f(536.387198317022,864.9448872917685);
        glVertex2f(535.6888401881736,863.5325630670267);
        glVertex2f(534.7294598993426,861.9211142753794);
        glVertex2f(534.1309643622808,860.5061540140083);
        glVertex2f(534.0,860.0);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0,0,0);
        glVertex2f(556.9044737527029,864.9852440851301);
        glVertex2f(556.9294020672231,866.6392957028376);
        glVertex2f(557.1786852124255,868.3557643627225);
        glVertex2f(557.2783984705065,870.2594841491405);
        glVertex2f(557.3781117285876,872.5377061886243);
        glVertex2f(557.3531834140673,874.472634496131);
        glVertex2f(557.5775382447495,876.4387713247265);
        glVertex2f(557.727108131871,878.1864485057005);
        glVertex2f(557.727108131871,879.6844575179638);
        glVertex2f(557.7520364463911,880.9327983615165);
        glVertex2f(558.0,882.0);
        glVertex2f(559.0033087498492,882.7524462720143);
        glVertex2f(559.7396932069998,883.1738873127737);
        glVertex2f(560.4339985523133,883.7270286775891);
        glVertex2f(561.0862247857895,884.201149847431);
        glVertex2f(561.8436487988587,884.5962508222992);
        glVertex2f(562.5379541441721,885.1493921871147);
        glVertex2f(563.2532990454041,885.7025335519303);
        glVertex2f(564.0,886.0);
        glVertex2f(564.5291487499596,886.4310257981319);
        glVertex2f(565.203594269813,886.7648421550512);
        glVertex2f(565.7525615534146,887.2557485622854);
        glVertex2f(566.5368005299882,887.6288374317834);
        glVertex2f(567.3680938451564,888.1197438300176);
        glVertex2f(567.948430687821,888.4731964522263);
        glVertex2f(568.6385609872058,888.8266490654349);
        glVertex2f(569.4227999637794,889.2193741912223);
        glVertex2f(570.1599846017588,889.7691893673247);
        glVertex2f(570.8501149011436,890.0440969553758);
        glVertex2f(571.5402452005285,890.4760945937419);
        glVertex2f(572.1048972636615,890.7902746043718);
        glVertex2f(572.6852341063261,890.9670010009761);
        glVertex2f(573.2655709489906,891.3597261267635);
        glVertex2f(573.9557012483755,891.595361202236);
        glVertex2f(574.6677295164611,892.043501146597);
        glVertex2f(575.2737172827428,892.3174597739185);
        glVertex2f(575.6945421204385,892.507123438087);
        glVertex2f(576.1995319256735,892.8021558068716);
        glVertex2f(576.8728516659866,893.139356558825);
        glVertex2f(577.4788394322683,893.4975892454567);
        glVertex2f(578.1858251595971,893.9190640567203);
        glVertex2f(578.6234829908007,894.0665802406626);
        glVertex2f(579.2631367440981,894.4037600896735);
        glVertex2f(579.8186255208564,894.6777187169948);
        glVertex2f(580.5761102377087,894.9727510848794);
        glVertex2f(581.2830950650374,895.2045622310744);
        glVertex2f(582.0237476793818,895.5206683395222);
        glVertex2f(582.596069458648,895.7735532262803);
        glVertex2f(583.3030551859767,896.1107330752913);
        glVertex2f(583.8417109782273,896.3425442214863);
        glVertex2f(584.4981977250326,896.5954291082445);
        glVertex2f(585.0200205237752,896.76401903275);
        glVertex2f(585.6428412835648,897.1644201034504);
        glVertex2f(586.4999818200121,897.5779727166961);
        glVertex2f(587.1680743172685,897.8169457100421);
        glVertex2f(588.0,898.0);
        glVertex2f(588.7714963106839,898.3426862954034);
        glVertex2f(589.5159422361982,898.5816502887495);
        glVertex2f(590.2985648758414,898.8923241800993);
        glVertex2f(590.9475690160333,899.1790917721146);
        glVertex2f(591.5774847991607,899.4180647654606);
        glVertex2f(592.398284152933,899.5853458608028);
        glVertex2f(593.3145252920275,899.9915999494912);
        glVertex2f(594.1735013599285,900.1588810448334);
        glVertex2f(594.841593857185,900.421751337514);
        glVertex2f(595.7960117104084,900.66072433086);
        glVertex2f(596.6549877783095,900.899697324206);
        glVertex2f(597.2658152043725,901.1625676168867);
        glVertex2f(598.182056343467,901.3059514128044);
        glVertex2f(599.4609762667864,901.3776433108982);
        glVertex2f(600.5108359053322,901.4732325082366);
        glVertex2f(601.236193473782,901.2581568142251);
        glVertex2f(601.2528291663782,900.6804413002927);
        glVertex2f(601.2730062008666,900.2762771524399);
        glVertex2f(601.232938922067,899.253745410991);
        glVertex2f(601.0403802685927,898.5841062974142);
        glVertex2f(600.9120078320431,897.9680383129236);
        glVertex2f(600.8050308032352,897.32518476389);
        glVertex2f(600.7622399913521,896.3341188757963);
        glVertex2f(600.7622399913521,895.5305519395043);
        glVertex2f(600.7622399913521,894.9144839550137);
        glVertex2f(600.7622399913521,893.7894902442048);
        glVertex2f(600.6766583675857,892.718067662482);
        glVertex2f(600.6766583675857,892.2350275007068);
        glVertex2f(600.6552620616441,891.7537873380315);
        glVertex2f(600.6766583675857,891.2716471771563);
        glVertex2f(600.6203198599487,890.6484092371062);
        glVertex2f(600.5896387072091,890.321779677007);
        glVertex2f(600.0220373832857,890.168136975057);
        glVertex2f(599.469776635597,890.1873423128008);
        glVertex2f(599.0,890.0);
        glVertex2f(598.441958021843,889.9568782598758);
        glVertex2f(597.859016121505,889.7456195446946);
        glVertex2f(597.4448205607384,889.5919768427447);
        glVertex2f(597.076646728946,889.4959501540259);
        glVertex2f(596.6471105918548,889.2846914388447);
        glVertex2f(596.294277336387,889.2078700878697);
        glVertex2f(596.0,889.0);
        glVertex2f(595.6653137070749,888.8621740084823);
        glVertex2f(595.2971398752824,888.727736644276);
        glVertex2f(594.8820443145158,888.497272591351);
        glVertex2f(594.5607922116975,888.3244245516573);
        glVertex2f(594.0238720403335,888.1515765119635);
        glVertex2f(593.6614101782562,888.0440615227313);
        glVertex2f(593.2526239244384,887.9002413223577);
        glVertex2f(592.927968376781,887.7421788088208);
        glVertex2f(592.5912885495807,887.501321872478);
        glVertex2f(591.9114076618273,887.3068061820668);
        glVertex2f(591.555991391804,887.1236787911581);
        glVertex2f(591.1169477641283,886.9404613992496);
        glVertex2f(590.6360904576262,886.6263744416918);
        glVertex2f(590.0925126328849,886.469330962013);
        glVertex2f(589.7161895234485,886.1814179184851);
        glVertex2f(589.0680775016415,885.9196787871871);
        glVertex2f(588.5454065163132,885.657939655889);
        glVertex2f(587.9182013339192,885.265330958042);
        glVertex2f(587.2700893121122,884.8988961751246);
        glVertex2f(586.5592567720657,884.6109831306968);
        glVertex2f(586.1829336626204,884.2968961731301);
        glVertex2f(586.0,884.0);
        glVertex2f(585.4093806043435,883.9042874761919);
        glVertex2f(584.9494301372546,883.642548344804);
        glVertex2f(584.5108865095789,883.3284613873362);
        glVertex2f(584.1131565607294,882.962026603519);
        glVertex2f(583.4859513783355,882.6479306459613);
        glVertex2f(583.0260009112466,882.4385483409228);
        glVertex2f(582.3778888894395,881.9150700783267);
        glVertex2f(581.959752101177,881.6533309470286);
        glVertex2f(581.5207084735011,881.339243989471);
        glVertex2f(580.9353169699335,880.8681135531344);
        glVertex2f(580.7471554152153,880.5540265955768);
        glVertex2f(580.0,880.0);
        glVertex2f(579.5554655626668,879.9258526804615);
        glVertex2f(579.0118877439254,879.4285483309951);
        glVertex2f(578.4892167585972,878.77420050275);
        glVertex2f(578.0058844200715,878.4925453635502);
        glVertex2f(577.7098396695209,878.2024890607424);
        glVertex2f(577.3236943427157,878.0252324312488);
        glVertex2f(576.9632920376976,877.7029476503513);
        glVertex2f(576.4484316019574,877.2195204790052);
        glVertex2f(576.0,877.0);
        glVertex2f(575.7404985028145,876.6716363514795);
        glVertex2f(575.5345543285184,876.4209227658064);
        glVertex2f(575.1870235343038,875.9626098335051);
        glVertex2f(574.8652357620562,875.6403250526076);
        glVertex2f(574.3836290547755,875.1522880146463);
        glVertex2f(573.9918587943333,874.8089595759129);
        glVertex2f(573.580500020869,874.4901545970891);
        glVertex2f(573.0,874.0);
        glVertex2f(572.561897343719,873.7299273398037);
        glVertex2f(571.9938304660778,873.1413643020651);
        glVertex2f(571.7979453358566,872.6754185637841);
        glVertex2f(571.4649406144807,872.3566135849602);
        glVertex2f(571.0,872.0);
        glVertex2f(570.5442805024414,871.5718628678553);
        glVertex2f(570.289629833154,871.0323467498457);
        glVertex2f(569.9958021378224,870.8361590705696);
        glVertex2f(569.7019744424906,870.394736792198);
        glVertex2f(569.2906156690262,870.1740256530123);
        glVertex2f(569.0,870.0);
        glVertex2f(568.5070751481418,869.1930872566312);
        glVertex2f(568.1740704267659,868.7761884381692);
        glVertex2f(567.8214771923679,868.5064303791645);
        glVertex2f(567.4101184189035,867.9423908012453);
        glVertex2f(567.0379366714833,867.5745380026024);
        glVertex2f(566.5286953320084,867.1085931643214);
        glVertex2f(566.0976880464219,866.7897881854975);
        glVertex2f(565.6319168244379,866.7877753056958);
        glVertex2f(564.9716830480344,866.7619451799715);
        glVertex2f(564.517772326757,866.7619451799715);
        glVertex2f(564.1257585220175,866.5036430227284);
        glVertex2f(563.67184780074,866.3486617283826);
        glVertex2f(570.289629833154,871.0323467498457);
        glVertex2f(569.9958021378224,870.8361590705696);
        glVertex2f(569.7019744424906,870.394736792198);
        glVertex2f(569.2906156690262,870.1740256530123);
        glVertex2f(569.0,870.0);
        glVertex2f(568.5070751481418,869.1930872566312);
        glVertex2f(568.1740704267659,868.7761884381692);
        glVertex2f(567.8214771923679,868.5064303791645);
        glVertex2f(567.4101184189035,867.9423908012453);
        glVertex2f(567.0379366714833,867.5745380026024);
        glVertex2f(566.5286953320084,867.1085931643214);
        glVertex2f(566.0976880464219,866.7897881854975);
        glVertex2f(565.6319168244379,866.7877753056958);
        glVertex2f(564.9716830480344,866.7619451799715);
        glVertex2f(564.517772326757,866.7619451799715);
        glVertex2f(564.1257585220175,866.5036430227284);
        glVertex2f(563.67184780074,866.3486617283826);
        glEnd();
    }
    else
    {
        glBegin(GL_POLYGON);
        glColor3f(1,1,1);
        glVertex2f(533.3251665213019,858.4212944441513);
        glVertex2f(535.3665210517819,858.6230550476859);
        glVertex2f(537.5690351504578,859.4973509963355);
        glVertex2f(539.2880705445463,859.7663651342817);
        glVertex2f(541.5980243553527,860.7079146175429);
        glVertex2f(543.9079781661501,861.2459428036351);
        glVertex2f(545.8956128405739,862.0529853077733);
        glVertex2f(548.0444070831845,862.8600277219115);
        glVertex2f(550.0857616136647,863.1962953944601);
        glVertex2f(552.3419955684058,864.1378448776303);
        glVertex2f(552.7180345608626,866.9624033271141);
        glVertex2f(553.20151326545,869.2491135005056);
        glVertex2f(553.6849919700373,871.1322124668282);
        glVertex2f(553.9535912503637,873.4188326402198);
        glVertex2f(555.0,875.0);
        glVertex2f(555.1354280837995,877.3867911763092);
        glVertex2f(555.7263465005175,879.8079184188139);
        glVertex2f(555.0,880.0);
        glVertex2f(553.6849919700373,879.2698901427218);
        glVertex2f(553.6849919700373,879.2698901427218);
        glVertex2f(552.5031551366015,878.6646083321182);
        glVertex2f(551.3750381592309,877.7230588489568);
        glVertex2f(550.2469211818604,877.1850305728648);
        glVertex2f(549.4411233408814,876.3779881587266);
        glVertex2f(548.3667262195761,875.5036922100768);
        glVertex2f(547.5072085225319,874.6966497959386);
        glVertex2f(546.3790915451613,874.0241144508234);
        glVertex2f(545.1972547117255,873.0153114331506);
        glVertex2f(543.7468185979633,872.275522553524);
        glVertex2f(542.3501023402664,871.4684801393857);
        glVertex2f(541.4368647871569,870.6614377252475);
        glVertex2f(540.0,870.0);
        glVertex2f(539.1806308324158,869.5181276385517);
        glVertex2f(538.2673932793062,868.643831689902);
        glVertex2f(537.7839145747189,867.7022822067407);
        glVertex2f(537.0318365898052,866.4917185855334);
        glVertex2f(536.387198317022,864.9448872917685);
        glVertex2f(536.387198317022,864.9448872917685);
        glVertex2f(535.6888401881736,863.5325630670267);
        glVertex2f(534.7294598993426,861.9211142753794);
        glVertex2f(534.1309643622808,860.5061540140083);
        glVertex2f(534.0,860.0);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(1,1,1);
        glVertex2f(556.9044737527029,864.9852440851301);
        glVertex2f(556.9294020672231,866.6392957028376);
        glVertex2f(557.1786852124255,868.3557643627225);
        glVertex2f(557.2783984705065,870.2594841491405);
        glVertex2f(557.3781117285876,872.5377061886243);
        glVertex2f(557.3531834140673,874.472634496131);
        glVertex2f(557.5775382447495,876.4387713247265);
        glVertex2f(557.727108131871,878.1864485057005);
        glVertex2f(557.727108131871,879.6844575179638);
        glVertex2f(557.7520364463911,880.9327983615165);
        glVertex2f(558.0,882.0);
        glVertex2f(559.0033087498492,882.7524462720143);
        glVertex2f(559.7396932069998,883.1738873127737);
        glVertex2f(560.4339985523133,883.7270286775891);
        glVertex2f(561.0862247857895,884.201149847431);
        glVertex2f(561.8436487988587,884.5962508222992);
        glVertex2f(562.5379541441721,885.1493921871147);
        glVertex2f(563.2532990454041,885.7025335519303);
        glVertex2f(564.0,886.0);
        glVertex2f(564.5291487499596,886.4310257981319);
        glVertex2f(565.203594269813,886.7648421550512);
        glVertex2f(565.7525615534146,887.2557485622854);
        glVertex2f(566.5368005299882,887.6288374317834);
        glVertex2f(567.3680938451564,888.1197438300176);
        glVertex2f(567.948430687821,888.4731964522263);
        glVertex2f(568.6385609872058,888.8266490654349);
        glVertex2f(569.4227999637794,889.2193741912223);
        glVertex2f(570.1599846017588,889.7691893673247);
        glVertex2f(570.8501149011436,890.0440969553758);
        glVertex2f(571.5402452005285,890.4760945937419);
        glVertex2f(572.1048972636615,890.7902746043718);
        glVertex2f(572.6852341063261,890.9670010009761);
        glVertex2f(573.2655709489906,891.3597261267635);
        glVertex2f(573.9557012483755,891.595361202236);
        glVertex2f(574.6677295164611,892.043501146597);
        glVertex2f(575.2737172827428,892.3174597739185);
        glVertex2f(575.6945421204385,892.507123438087);
        glVertex2f(576.1995319256735,892.8021558068716);
        glVertex2f(576.8728516659866,893.139356558825);
        glVertex2f(577.4788394322683,893.4975892454567);
        glVertex2f(578.1858251595971,893.9190640567203);
        glVertex2f(578.6234829908007,894.0665802406626);
        glVertex2f(579.2631367440981,894.4037600896735);
        glVertex2f(579.8186255208564,894.6777187169948);
        glVertex2f(580.5761102377087,894.9727510848794);
        glVertex2f(581.2830950650374,895.2045622310744);
        glVertex2f(582.0237476793818,895.5206683395222);
        glVertex2f(582.596069458648,895.7735532262803);
        glVertex2f(583.3030551859767,896.1107330752913);
        glVertex2f(583.8417109782273,896.3425442214863);
        glVertex2f(584.4981977250326,896.5954291082445);
        glVertex2f(585.0200205237752,896.76401903275);
        glVertex2f(585.6428412835648,897.1644201034504);
        glVertex2f(586.4999818200121,897.5779727166961);
        glVertex2f(587.1680743172685,897.8169457100421);
        glVertex2f(588.0,898.0);
        glVertex2f(588.7714963106839,898.3426862954034);
        glVertex2f(589.5159422361982,898.5816502887495);
        glVertex2f(590.2985648758414,898.8923241800993);
        glVertex2f(590.9475690160333,899.1790917721146);
        glVertex2f(591.5774847991607,899.4180647654606);
        glVertex2f(592.398284152933,899.5853458608028);
        glVertex2f(593.3145252920275,899.9915999494912);
        glVertex2f(594.1735013599285,900.1588810448334);
        glVertex2f(594.841593857185,900.421751337514);
        glVertex2f(595.7960117104084,900.66072433086);
        glVertex2f(596.6549877783095,900.899697324206);
        glVertex2f(597.2658152043725,901.1625676168867);
        glVertex2f(598.182056343467,901.3059514128044);
        glVertex2f(599.4609762667864,901.3776433108982);
        glVertex2f(600.5108359053322,901.4732325082366);
        glVertex2f(601.236193473782,901.2581568142251);
        glVertex2f(601.2528291663782,900.6804413002927);
        glVertex2f(601.2730062008666,900.2762771524399);
        glVertex2f(601.232938922067,899.253745410991);
        glVertex2f(601.0403802685927,898.5841062974142);
        glVertex2f(600.9120078320431,897.9680383129236);
        glVertex2f(600.8050308032352,897.32518476389);
        glVertex2f(600.7622399913521,896.3341188757963);
        glVertex2f(600.7622399913521,895.5305519395043);
        glVertex2f(600.7622399913521,894.9144839550137);
        glVertex2f(600.7622399913521,893.7894902442048);
        glVertex2f(600.6766583675857,892.718067662482);
        glVertex2f(600.6766583675857,892.2350275007068);
        glVertex2f(600.6552620616441,891.7537873380315);
        glVertex2f(600.6766583675857,891.2716471771563);
        glVertex2f(600.6203198599487,890.6484092371062);
        glVertex2f(600.5896387072091,890.321779677007);
        glVertex2f(600.0220373832857,890.168136975057);
        glVertex2f(599.469776635597,890.1873423128008);
        glVertex2f(599.0,890.0);
        glVertex2f(598.441958021843,889.9568782598758);
        glVertex2f(597.859016121505,889.7456195446946);
        glVertex2f(597.4448205607384,889.5919768427447);
        glVertex2f(597.076646728946,889.4959501540259);
        glVertex2f(596.6471105918548,889.2846914388447);
        glVertex2f(596.294277336387,889.2078700878697);
        glVertex2f(596.0,889.0);
        glVertex2f(595.6653137070749,888.8621740084823);
        glVertex2f(595.2971398752824,888.727736644276);
        glVertex2f(594.8820443145158,888.497272591351);
        glVertex2f(594.5607922116975,888.3244245516573);
        glVertex2f(594.0238720403335,888.1515765119635);
        glVertex2f(593.6614101782562,888.0440615227313);
        glVertex2f(593.2526239244384,887.9002413223577);
        glVertex2f(592.927968376781,887.7421788088208);
        glVertex2f(592.5912885495807,887.501321872478);
        glVertex2f(591.9114076618273,887.3068061820668);
        glVertex2f(591.555991391804,887.1236787911581);
        glVertex2f(591.1169477641283,886.9404613992496);
        glVertex2f(590.6360904576262,886.6263744416918);
        glVertex2f(590.0925126328849,886.469330962013);
        glVertex2f(589.7161895234485,886.1814179184851);
        glVertex2f(589.0680775016415,885.9196787871871);
        glVertex2f(588.5454065163132,885.657939655889);
        glVertex2f(587.9182013339192,885.265330958042);
        glVertex2f(587.2700893121122,884.8988961751246);
        glVertex2f(586.5592567720657,884.6109831306968);
        glVertex2f(586.1829336626204,884.2968961731301);
        glVertex2f(586.0,884.0);
        glVertex2f(585.4093806043435,883.9042874761919);
        glVertex2f(584.9494301372546,883.642548344804);
        glVertex2f(584.5108865095789,883.3284613873362);
        glVertex2f(584.1131565607294,882.962026603519);
        glVertex2f(583.4859513783355,882.6479306459613);
        glVertex2f(583.0260009112466,882.4385483409228);
        glVertex2f(582.3778888894395,881.9150700783267);
        glVertex2f(581.959752101177,881.6533309470286);
        glVertex2f(581.5207084735011,881.339243989471);
        glVertex2f(580.9353169699335,880.8681135531344);
        glVertex2f(580.7471554152153,880.5540265955768);
        glVertex2f(580.0,880.0);
        glVertex2f(579.5554655626668,879.9258526804615);
        glVertex2f(579.0118877439254,879.4285483309951);
        glVertex2f(578.4892167585972,878.77420050275);
        glVertex2f(578.0058844200715,878.4925453635502);
        glVertex2f(577.7098396695209,878.2024890607424);
        glVertex2f(577.3236943427157,878.0252324312488);
        glVertex2f(576.9632920376976,877.7029476503513);
        glVertex2f(576.4484316019574,877.2195204790052);
        glVertex2f(576.0,877.0);
        glVertex2f(575.7404985028145,876.6716363514795);
        glVertex2f(575.5345543285184,876.4209227658064);
        glVertex2f(575.1870235343038,875.9626098335051);
        glVertex2f(574.8652357620562,875.6403250526076);
        glVertex2f(574.3836290547755,875.1522880146463);
        glVertex2f(573.9918587943333,874.8089595759129);
        glVertex2f(573.580500020869,874.4901545970891);
        glVertex2f(573.0,874.0);
        glVertex2f(572.561897343719,873.7299273398037);
        glVertex2f(571.9938304660778,873.1413643020651);
        glVertex2f(571.7979453358566,872.6754185637841);
        glVertex2f(571.4649406144807,872.3566135849602);
        glVertex2f(571.0,872.0);
        glVertex2f(570.5442805024414,871.5718628678553);
        glVertex2f(570.289629833154,871.0323467498457);
        glVertex2f(569.9958021378224,870.8361590705696);
        glVertex2f(569.7019744424906,870.394736792198);
        glVertex2f(569.2906156690262,870.1740256530123);
        glVertex2f(569.0,870.0);
        glVertex2f(568.5070751481418,869.1930872566312);
        glVertex2f(568.1740704267659,868.7761884381692);
        glVertex2f(567.8214771923679,868.5064303791645);
        glVertex2f(567.4101184189035,867.9423908012453);
        glVertex2f(567.0379366714833,867.5745380026024);
        glVertex2f(566.5286953320084,867.1085931643214);
        glVertex2f(566.0976880464219,866.7897881854975);
        glVertex2f(565.6319168244379,866.7877753056958);
        glVertex2f(564.9716830480344,866.7619451799715);
        glVertex2f(564.517772326757,866.7619451799715);
        glVertex2f(564.1257585220175,866.5036430227284);
        glVertex2f(563.67184780074,866.3486617283826);
        glVertex2f(570.289629833154,871.0323467498457);
        glVertex2f(569.9958021378224,870.8361590705696);
        glVertex2f(569.7019744424906,870.394736792198);
        glVertex2f(569.2906156690262,870.1740256530123);
        glVertex2f(569.0,870.0);
        glVertex2f(568.5070751481418,869.1930872566312);
        glVertex2f(568.1740704267659,868.7761884381692);
        glVertex2f(567.8214771923679,868.5064303791645);
        glVertex2f(567.4101184189035,867.9423908012453);
        glVertex2f(567.0379366714833,867.5745380026024);
        glVertex2f(566.5286953320084,867.1085931643214);
        glVertex2f(566.0976880464219,866.7897881854975);
        glVertex2f(565.6319168244379,866.7877753056958);
        glVertex2f(564.9716830480344,866.7619451799715);
        glVertex2f(564.517772326757,866.7619451799715);
        glVertex2f(564.1257585220175,866.5036430227284);
        glVertex2f(563.67184780074,866.3486617283826);
        glEnd();
    }



    // plan wheel

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);

    glVertex2f(590.0463967528009,779.6241951002256);
    glVertex2f(591.0996971433307,779.5655880315019);
    glVertex2f(592.293437585931,779.6241951002256);
    glVertex2f(593.0424511969743,779.6241951002256);
    glVertex2f(593.7446514573274,779.3604632909689);
    glVertex2f(594.751138497167,779.3311597566071);
    glVertex2f(595.9682856151124,779.3018562222453);
    glVertex2f(596.9513659796069,779.3018562222453);
    glVertex2f(597.7471920413406,779.3018562222453);
    glVertex2f(598.6132399201093,779.2432491535216);
    glVertex2f(599.7367603456744,779.2725526878824);
    glVertex2f(600.4155539306824,779.2725526878834);
    glVertex2f(601.1645675417258,779.3604632009689);
    glVertex2f(602.1242412308751,779.2725526878834);
    glVertex2f(603.224354972095,779.2725526878834);
    glVertex2f(604.1372153105541,779.2139456191597);
    glVertex2f(605.213922376429,779.2432491535216);
    glVertex2f(605.9863426628174,779.3018562222453);
    glVertex2f(606.8757963259313,779.3018562222453);
    glVertex2f(607.8588766904257,779.3018562222453);
    glVertex2f(608.5844836261241,779.3018562222453);
    glVertex2f(609.3334972371674,779.3018562222453);
    glVertex2f(609.8952574454499,779.3311597566071);
    glVertex2f(610.4008812957794,779.3740474755188);
    glVertex2f(610.9933212333788,779.4976630952285);
    glVertex2f(611.4047378567116,779.5182656985135);
    glVertex2f(612.0300911241775,779.5800735083683);
    glVertex2f(612.6554443916434,779.6006761116532);
    glVertex2f(613.2478843292428,779.662483921508);
    glVertex2f(613.6757576175089,779.7242917313629);
    glVertex2f(614.1694575655083,779.7448943346478);
    glVertex2f(614.8441808277742,779.8273047477876);
    glVertex2f(615.4201641004402,779.8273047477876);
    glVertex2f(616.0,780.0);
    glVertex2f(616.6544139704387,779.7860995412177);
    glVertex2f(616.6544139704387,779.7860995412177);
    glVertex2f(617.0232631961209,779.7532047819271);
    glVertex2f(617.2809807602407,779.7532047819271);
    glVertex2f(617.5100800394583,779.7293943533456);
    glVertex2f(617.816899064303,779.3980358913661);
    glVertex2f(617.7046158707574,778.7264580221611);
    glVertex2f(617.5328041669889,778.250981905292);
    glVertex2f(617.5,778.0);
    glVertex2f(617.3881206269733,777.5717303097646);
    glVertex2f(617.2705652507107,777.3000296715536);
    glVertex2f(617.0354544981852,776.7905909749081);
    glVertex2f(616.9178991219226,776.3717191576662);
    glVertex2f(616.755130130405,775.8622804610206);
    glVertex2f(616.5398873076354,775.4819897454637);
    glVertex2f(616.342441095728,774.8354955290196);
    glVertex2f(616.1298067136738,774.2650594556865);
    glVertex2f(616.0234895226467,773.7896960612424);
    glVertex2f(615.7804788002992,773.2953181310204);
    glVertex2f(615.5982207585384,772.8009402007984);
    glVertex2f(615.3855863764843,772.2114895016877);
    glVertex2f(615.0362584631097,771.526966303688);
    glVertex2f(614.8084359109089,771.0516029092438);
    glVertex2f(614.5654251885612,770.3480650854664);
    glVertex2f(614.1353303011203,769.7658500195655);
    glVertex2f(613.9587526806489,769.1227575149255);
    glVertex2f(613.7019123745087,768.5198582918256);
    glVertex2f(613.3648094726007,767.9571523502656);
    glVertex2f(612.9956015326228,766.9925135933056);
    glVertex2f(612.6263935925462,766.5101942148257);
    glVertex2f(612.3374482481383,765.7063285840256);
    glVertex2f(611.807715116724,765.0431394386158);
    glVertex2f(611.2779819853097,764.2191771670458);
    glVertex2f(610.908774045233,763.4354081770158);
    glVertex2f(610.42719847122,762.4707694200558);
    glVertex2f(610.0,762.0);
    glVertex2f(609.6406250336653,761.1845844107759);
    glVertex2f(609.3516796892575,760.601781828446);
    glVertex2f(609.0,760.0);
    glVertex2f(608.5811587708366,760.059172527656);
    glVertex2f(608.1958983116261,759.9184960422659);
    glVertex2f(607.6340601419442,759.757722916106);
    glVertex2f(606.9277493000585,759.657239712256);
    glVertex2f(606.0930183051025,759.4763699453259);
    glVertex2f(605.6923741836974,759.273280125039);
    glVertex2f(605.6498708476809,758.6879566034363);
    glVertex2f(605.5648641756477,757.969605008742);
    glVertex2f(605.6498708476809,757.4374927163758);
    glVertex2f(605.6498708476809,756.8255635801547);
    glVertex2f(605.5648641756477,755.8145502246591);
    glVertex2f(605.6286191796726,754.9365649422549);
    glVertex2f(605.7986325237389,754.4310582645071);
    glVertex2f(605.2035858195067,754.2714245767972);
    glVertex2f(605.2454022041628,753.5125551050621);
    glVertex2f(605.2285742203785,753.0280035832692);
    glVertex2f(605.2285742293785,752.3959798591915);
    glVertex2f(605.1780903050259,751.7639561351137);
    glVertex2f(605.1780903050259,750.963392751282);
    glVertex2f(605.1780903050259,750.1206944525117);
    glVertex2f(605.2285742203785,749.4044008085569);
    glVertex2f(605.2117462545943,748.9619842917026);
    glVertex2f(605.1612623302417,748.2667581952171);
    glVertex2f(605.1612623302417,747.6347344711394);
    glVertex2f(605.1612623302417,746.8131036208383);
    glVertex2f(605.2454022041628,746.0336077034758);
    glVertex2f(605.2285742293785,745.6122585540907);
    glVertex2f(605.2285742293785,744.8748975426666);
    glVertex2f(605.2117462545943,744.327143648466);
    glVertex2f(605.1444343554574,743.8215246692038);
    glVertex2f(604.976332420343,743.3363068850684);
    glVertex2f(605.0320044533722,742.7090291628256);
    glVertex2f(604.976332420343,741.9772051535423);
    glVertex2f(604.8928243707994,741.2802299066058);
    glVertex2f(605.0041684368576,740.6520521843629);
    glVertex2f(605.0320044533722,740.02567446212);
    glVertex2f(604.7536442882267,739.6074893130581);
    glVertex2f(604.7536442882267,738.8756653046748);
    glVertex2f(604.6979722551977,738.283236344778);
    glVertex2f(604.6423002221686,737.3423197614145);
    glVertex2f(604.6175536306978,736.5489791916915);
    glVertex2f(604.6448590628344,736.0362115791966);
    glVertex2f(604.5083319021518,735.3183369217036);
    glVertex2f(604.6448590628344,734.7030157867096);
    glVertex2f(605.3602695559205,734.6923073037706);
    glVertex2f(605.9726638687445,734.7148565747199);
    glVertex2f(606.4229538046444,734.7148565747199);
    glVertex2f(606.9002519756687,734.7768646121876);
    glVertex2f(607.3325512536289,734.844515701885);
    glVertex2f(607.6702850645353,734.8952540191581);
    glVertex2f(608.0,735.0);
    glVertex2f(608.3322433333911,734.9459923364311);
    glVertex2f(608.7105052021271,734.9121667915824);
    glVertex2f(608.8726174313623,735.4533755091613);
    glVertex2f(608.8591080789259,736.4681418546216);
    glVertex2f(609.0077109557249,737.2968677034144);
    glVertex2f(608.9806922508523,738.3285468212991);
    glVertex2f(609.0212203081611,739.3602259301838);
    glVertex2f(609.2643886520137,740.5948583261606);
    glVertex2f(609.3724634715038,741.558886354348);
    glVertex2f(609.4940476434301,742.6920421067789);
    glVertex2f(609.6021224629202,743.9097617213314);
    glVertex2f(609.6561598726652,745.1105685634595);
    glVertex2f(609.588613110484,746.0238582743739);
    glVertex2f(609.6156318153564,746.8864096680152);
    glVertex2f(609.7752515891277,747.6753482232153);
    glVertex2f(610.229217568225,748.0250921769958);
    glVertex2f(610.7181040072528,748.2582548128495);
    glVertex2f(611.2069904462807,748.4768447830623);
    glVertex2f(611.6609564253779,748.7245800845568);
    glVertex2f(612.2778845508178,748.9140247261879);
    glVertex2f(612.8016914497762,748.9140247261879);
    glVertex2f(613.3022180421142,749.0451787088556);
    glVertex2f(613.8143847877624,749.059751373563);
    glVertex2f(614.4429530665125,749.190905356264);
    glVertex2f(615.1297221118135,749.3803499978051);
    glVertex2f(615.909612383596,749.4386406568585);
    glVertex2f(616.5847412755868,749.4969313158219);
    glVertex2f(617.2715103208878,749.5406493100445);
    glVertex2f(617.8535179863972,749.4823586510811);
    glVertex2f(618.5519271850084,749.4386406568585);
    glVertex2f(619.1558635171723,749.4519666064753);
    glVertex2f(619.7051015284603,749.4317428446394);
    glVertex2f(620.2866476580593,749.371071559132);
    glVertex2f(620.7712694327253,749.371071559132);
    glVertex2f(621.3366615031689,749.3306240354603);
    glVertex2f(621.9343616919235,749.2497289881172);
    glVertex2f(622.5643699989802,749.1890577026098);
    glVertex2f(623.1620701877438,749.1283864171023);
    glVertex2f(623.775924435654,749.0474913697592);
    glVertex2f(624.3090083877865,748.9261487987443);
    glVertex2f(624.8905545173856,748.8452537514012);
    glVertex2f(625.5044087652058,748.6834636567147);
    glVertex2f(625.9728764808061,748.6430161330431);
    glVertex2f(626.4090360780054,748.5418973238641);
    glVertex2f(626.8128875568038,748.440778514685);
    glVertex2f(627.3298174498707,748.2992121818345);
    glVertex2f(628.0,748.0);
    glVertex2f(628.4767556499133,747.8947360451183);
    glVertex2f(628.8806071288017,747.6722755649246);
    glVertex2f(629.4783073175563,747.5509329939097);
    glVertex2f(629.866004737289,747.3689191373875);
    glVertex2f(630.2052309795552,747.1869052808653);
    glVertex2f(630.6413995767545,746.903772615164);
    glVertex2f(630.9483267007096,746.6813112349702);
    glVertex2f(631.3521781795978,746.3375072837615);
    glVertex2f(631.6267971852418,745.9937033325529);
    glVertex2f(631.8706959254309,745.725636352775);
    glVertex2f(632.1306457803256,745.4627816209978);
    glVertex2f(632.2006322797204,745.1373424292735);
    glVertex2f(632.270618779115,744.8119032375494);
    glVertex2f(632.2106303510624,744.5240147217934);
    glVertex2f(632.1406438516677,744.2110924220585);
    glVertex2f(631.9906727815362,743.7354505264616);
    glVertex2f(631.7762794220185,742.8187183965217);
    glVertex2f(631.6277606228866,742.1121644949362);
    glVertex2f(631.4495380639282,741.2568624035433);
    glVertex2f(631.211907985317,740.4387473596023);
    glVertex2f(630.9742779067059,739.4718841258538);
    glVertex2f(630.7366478280948,738.8025172717203);
    glVertex2f(630.52872150931,737.9844022277791);
    glVertex2f(630.4099064700043,737.2778483261937);
    glVertex2f(630.0,736.0);
    glVertex2f(629.6970162341709,734.972251384178);
    glVertex2f(629.4890899153861,734.3400715774964);
    glVertex2f(629.3999786359069,733.6707047233627);
    glVertex2f(629.251459836775,732.8525896794217);
    glVertex2f(629.1326447974694,732.1460357778362);
    glVertex2f(628.8950147188582,731.4766689237026);
    glVertex2f(628.5682733607679,730.3082445475086);
    glVertex2f(628.4494583214623,729.6916906460131);
    glVertex2f(628.3009395223303,728.9107626495239);
    glVertex2f(628.0,728.0);
    glVertex2f(627.7538168363511,727.3249416144838);
    glVertex2f(627.579161711046,726.6033764674353);
    glVertex2f(627.2307211710355,725.9312092070024);
    glVertex2f(627.0739561285653,724.9172045696362);
    glVertex2f(626.7081710294683,723.9359097592817);
    glVertex2f(626.394640944528,722.8564854678017);
    glVertex2f(626.0288558454309,721.74435134049);
    glVertex2f(625.6630707463329,720.8938958471828);
    glVertex2f(625.2972856472369,720.0434403448755);
    glVertex2f(625.1666481118451,719.3892438046302);
    glVertex2f(624.8269905198265,718.6369177833674);
    glVertex2f(624.644097970278,717.7864622810602);
    glVertex2f(624.4089504065728,717.0014264327766);
    glVertex2f(624.1999303499459,716.2818102385166);
    glVertex2f(623.8602727579272,715.5949038712686);
    glVertex2f(623.6833085430984,715.0072527344356);
    glVertex2f(623.4984990247813,714.4814147775128);
    glVertex2f(623.3976938329719,713.8083421926516);
    glVertex2f(623.0784773922422,713.2404371991751);
    glVertex2f(622.7928626821158,712.4411635046524);
    glVertex2f(622.5072479719893,711.8942920204527);
    glVertex2f(622.255234992466,711.347420554253);
    glVertex2f(621.952819417038,710.5691803780072);
    glVertex2f(621.7008064375145,709.8330072383153);
    glVertex2f(621.4655943232927,709.1389011351772);
    glVertex2f(621.171590148465,708.7792218158842);
    glVertex2f(620.9556704797255,708.3009696315837);
    glVertex2f(620.7397508109859,707.6563688614394);
    glVertex2f(620.5238311422463,707.3028781165216);
    glVertex2f(620.2746930629313,706.7830387857601);
    glVertex2f(620.0,706.0);
    glVertex2f(619.7930261095892,705.6185986848544);
    glVertex2f(619.4442327985482,705.2027272202453);
    glVertex2f(619.211703924521,704.558126450101);
    glVertex2f(619.0,704.0);
    glVertex2f(618.6802093553157,703.8927321067263);
    glVertex2f(618.3812436601378,703.8511449602654);
    glVertex2f(617.9494043226586,703.7471770941131);
    glVertex2f(617.5208689351583,703.7049319792383);
    glVertex2f(617.0629695450498,703.6314373276086);
    glVertex2f(616.7342212649719,703.6755341185865);
    glVertex2f(616.511142074919,703.6902330489123);
    glVertex2f(616.2645808648605,703.6902330489123);
    glVertex2f(615.9827966247938,703.7490287702161);
    glVertex2f(615.6070843047047,703.7490287702161);
    glVertex2f(615.1844079446045,703.7637277005421);
    glVertex2f(614.7265085544959,703.7637277005421);
    glVertex2f(614.3977602744179,703.7931255611938);
    glVertex2f(614.0220479543289,703.8519212824976);
    glVertex2f(613.6463356342308,703.8813191431494);
    glVertex2f(613.2823643241536,703.9107170038013);
    glVertex2f(613.0,704.0);
    glVertex2f(612.6131267530996,703.9989105857569);
    glVertex2f(612.1904503938047,704.0430073767347);
    glVertex2f(611.6386229237639,704.1752077496681);
    glVertex2f(611.0434217440526,704.305961217143);
    glVertex2f(610.5458450064727,704.4133632120157);
    glVertex2f(610.0139526318185,704.5207652068884);
    glVertex2f(609.4477446200897,704.6711279997102);
    glVertex2f(608.7785896971375,704.9718535853536);
    glVertex2f(608.3153285966322,705.1007359792009);
    glVertex2f(607.7834362219778,705.4873831607425);
    glVertex2f(607.1829125731746,705.788108746386);
    glVertex2f(606.8397562024298,706.4110403166476);
    glVertex2f(606.8054405653554,707.4420094674252);
    glVertex2f(606.771124928281,708.5590802141012);
    glVertex2f(606.8569140209671,709.633100162828);
    glVertex2f(607.0284922063395,710.9434045002746);
    glVertex2f(607.2172282102491,712.2107480397723);
    glVertex2f(607.3493630433074,713.4333020514016);
    glVertex2f(607.3819093212516,714.5741811758708);
    glVertex2f(607.4144555991958,715.3687219946975);
    glVertex2f(607.4307287381679,716.5503468021834);
    glVertex2f(607.5120944330283,717.6912259266526);
    glVertex2f(607.6097332668609,718.8932235756469);
    glVertex2f(607.7887377955539,719.9118656510658);
    glVertex2f(607.8375572124702,721.052744775535);
    glVertex2f(607.9452543308674,721.7735747950583);
    glVertex2f(607.9587880996261,722.0733134120873);
    glVertex2f(607.8893441860437,722.4521082666255);
    glVertex2f(607.8083470518671,722.6136019392129);
    glVertex2f(607.581187788578,722.703320646206);
    glVertex2f(607.2355675229245,722.6737808569969);
    glVertex2f(606.7045929081921,722.5437223663907);
    glVertex2f(606.0120173237588,722.5292714229901);
    glVertex2f(605.457956856212,722.5292714229901);
    glVertex2f(604.730752492557,722.5148204795893);
    glVertex2f(603.0215777314044,722.4605772680085);
    glVertex2f(602.1899014024385,722.4853677701526);
    glVertex2f(601.4176305255417,722.4853677701526);
    glVertex2f(600.6849632833573,722.4357867658645);
    glVertex2f(600.1039615717488,722.4701284155589);
    glVertex2f(599.58429706442,722.545195791668);
    glVertex2f(599.1745615874876,722.570218250371);
    glVertex2f(598.7448390141195,722.64528562648);
    glVertex2f(598.4350390193658,722.495150874262);
    glVertex2f(598.5,722.0);
    glVertex2f(598.5438778469958,721.4896863168086);
    glVertex2f(598.5877607913018,720.9403022842415);
    glVertex2f(598.6667500913047,720.4788196968851);
    glVertex2f(598.7018564468216,720.1382015966935);
    glVertex2f(598.7281862134591,719.8744972610614);
    glVertex2f(598.7896223356136,719.5778298834751);
    glVertex2f(598.8422818688888,719.2152364219809);
    glVertex2f(598.9124945799225,718.7537538346245);
    glVertex2f(598.9124045799225,718.3581973311761);
    glVertex2f(599.0,718.0);
    glVertex2f(599.0353668242313,717.5011582403715);
    glVertex2f(599.0529200019809,717.1715278208312);
    glVertex2f(599.1055795352651,716.6551068302182);
    glVertex2f(599.1452114768348,716.0108333308963);
    glVertex2f(599.1722089045429,715.4869502675231);
    glVertex2f(599.1587101906888,715.0137655651214);
    glVertex2f(599.1722089045429,714.3884857798049);
    glVertex2f(599.1722089045429,713.7632050044884);
    glVertex2f(599.199206332251,713.1210267555148);
    glVertex2f(599.3206047569378,712.5295458775128);
    glVertex2f(599.4421831816245,712.0732606287684);
    glVertex2f(599.4961780370409,711.5662770190523);
    glVertex2f(599.5501728924571,711.0930923166507);
    glVertex2f(599.523175464749,710.6706059752206);
    glVertex2f(599.5366741786031,710.0115272825898);
    glVertex2f(599.523175464749,709.4876442192165);
    glVertex2f(599.4816503277467,708.9748002712726);
    glVertex2f(599.4942111191455,708.4873150316222);
    glVertex2f(599.5570155099966,708.0941817738396);
    glVertex2f(599.5946981011216,707.7167738463684);
    glVertex2f(599.5821372374132,707.3708165795197);
    glVertex2f(599.5946981011216,706.9934086520484);
    glVertex2f(599.6072589648298,706.6474513851997);
    glVertex2f(599.6575024196632,706.301494118351);
    glVertex2f(599.6449415559548,705.8611848696345);
    glVertex2f(599.4007006583022,705.6259433660333);
    glVertex2f(599.0912660047169,705.5533076045166);
    glVertex2f(598.8591900145279,705.4443539622416);
    glVertex2f(598.6174441914145,705.2627645584498);
    glVertex2f(598.4047078670746,705.141704955922);
    glVertex2f(598.2306508744329,705.0811751546581);
    glVertex2f(598.0,705.0);
    glVertex2f(597.7230461873752,704.9012051085293);
    glVertex2f(597.3022175989829,704.7880876399038);
    glVertex2f(596.9259903299893,704.698977554627);
    glVertex2f(596.4989215381588,704.6225974815327);
    glVertex2f(596.1837040965696,704.4952973597088);
    glVertex2f(595.8481500458456,704.4316472987969);
    glVertex2f(595.3319757493183,704.1652184252767);
    glVertex2f(594.9161527911558,704.0374116490752);
    glVertex2f(594.5515537050485,703.822177065448);
    glVertex2f(594.0994508382753,703.8730886511019);
    glVertex2f(593.793187605945,703.8730886511019);
    glVertex2f(593.443172483282,703.854830540216);
    glVertex2f(593.0712814154523,703.83657242933);
    glVertex2f(592.8014780917329,703.83657242933);
    glVertex2f(592.509798822847,703.8639595956589);
    glVertex2f(592.1754508219315,703.8550984835961);
    glVertex2f(591.8450346656421,703.8368488608984);
    glVertex2f(591.5777863039375,703.8125160306347);
    glVertex2f(591.4028601035491,703.8003496155029);
    glVertex2f(591.2279339031606,703.8064328230688);
    glVertex2f(591.111316436235,703.8064328230688);
    glVertex2f(590.9801217859437,703.8125160306347);
    glVertex2f(590.8732224412618,703.7881832003711);
    glVertex2f(590.5524923953883,703.845268581058);
    glVertex2f(590.1572164616177,703.8743778785928);
    glVertex2f(589.7386890023312,703.8889325273602);
    glVertex2f(589.3550388313186,703.8889325273602);
    glVertex2f(589.0,704.0);
    glVertex2f(588.6458673030832,703.9471511224298);
    glVertex2f(588.3319177086183,703.9617057711972);
    glVertex2f(588.0,704.0);
    glVertex2f(587.6809289941726,704.0781429613364);
    glVertex2f(587.2972788231599,704.2819080440801);
    glVertex2f(586.882444710998,705.1173223309581);
    glVertex2f(586.5639772514988,706.0033204969584);
    glVertex2f(585.9801202424171,707.2437179293586);
    glVertex2f(585.5554969630848,708.3512156368588);
    glVertex2f(585.1308736837526,709.215063848709);
    glVertex2f(584.6531724945039,710.2782616479092);
    glVertex2f(584.1577786686163,711.4522092178594);
    glVertex2f(583.7685406625617,712.5597069253596);
    glVertex2f(583.2554542000353,713.8222543119098);
    glVertex2f(582.7423677375089,714.79685229451);
    glVertex2f(582.3000518215377,716.0372497269102);
    glVertex2f(581.8400432689278,717.1004475261104);
    glVertex2f(581.4672724224139,718.2291619276185);
    glVertex2f(580.9543286814127,719.349543617355);
    glVertex2f(580.6160040862842,720.3606197763856);
    glVertex2f(580.3322479742409,721.3443695527396);
    glVertex2f(579.9830096824954,722.4100984771233);
    glVertex2f(579.5392206092647,723.7767001130726);
    glVertex2f(579.3054751310804,724.623796013573);
    glVertex2f(579.0225200785416,725.671145814644);
    glVertex2f(578.6621825334771,726.5604182958272);
    glVertex2f(578.425151205287,727.5191386801026);
    glVertex2f(578.1151871607307,728.5919924434585);
    glVertex2f(577.8052231161743,729.9159396407913);
    glVertex2f(577.5864249670757,730.8746600250668);
    glVertex2f(577.2764609225194,731.764900381894);
    glVertex2f(576.9482636988715,732.9975408759624);
    glVertex2f(576.651000821435,734.2298339902758);
    glVertex2f(576.3240139628251,735.6513832810845);
    glVertex2f(576.0314467735426,736.793750817643);
    glVertex2f(575.6356250767278,738.775938616952);
    glVertex2f(575.3086337176682,740.1176082952999);
    glVertex2f(575.0160665283856,741.1454576829989);
    glVertex2f(574.7923386777578,742.2232217461852);
    glVertex2f(574.4309321498206,743.1927701262821);
    glVertex2f(574.189994464529,744.1407729868212);
    glVertex2f(574.1383649605381,744.9810482495718);
    glVertex2f(574.4974160365482,745.6777195875081);
    glVertex2f(575.0243428843322,746.152686216004);
    glVertex2f(575.530192658205,746.4165565651683);
    glVertex2f(576.0078218773139,746.7774514383424);
    glVertex2f(576.7187615749493,747.0684284076659);
    glVertex2f(577.2382944390137,747.2738239154238);
    glVertex2f(577.6621238660425,747.4621031308685);
    glVertex2f(578.1132971356958,747.7017312232526);
    glVertex2f(578.5918142398735,747.8215452694446);
    glVertex2f(579.0,748.0);
    glVertex2f(579.5078326964424,748.0782896541419);
    glVertex2f(580.0000217178823,748.3692666234655);
    glVertex2f(580.4648669047978,748.4548480850312);
    glVertex2f(574.7923386777578,742.2232217461852);
    glVertex2f(574.4309321498206,743.1927701262821);
    glVertex2f(574.189994464529,744.1407729868212);
    glVertex2f(574.1383649605381,744.9810482495718);
    glVertex2f(574.4974160365482,745.6777195875081);
    glVertex2f(575.0243428843322,746.152686216004);
    glVertex2f(575.530192658205,746.4165565651683);
    glVertex2f(576.0078218773139,746.7774514383424);
    glVertex2f(576.7187615749493,747.0684284076659);
    glVertex2f(577.2382944390137,747.2738239154238);
    glVertex2f(577.6621238660425,747.4621031308685);
    glVertex2f(578.1132971356958,747.7017312232526);
    glVertex2f(578.5918142398735,747.8215452694446);
    glVertex2f(579.0,748.0);
    glVertex2f(579.5078326964424,748.0782896541419);
    glVertex2f(580.0000217178823,748.3692666234655);
    glVertex2f(580.4648669047978,748.4548480850312);
    glVertex2f(580.9570559262378,748.5575458389102);
    glVertex2f(581.5749904666427,748.8210530081195);
    glVertex2f(581.922587836755,748.8573169916805);
    glVertex2f(582.3860509969049,748.9842409341438);
    glVertex2f(582.8639973808095,748.9661089423633);
    glVertex2f(583.29849409345,748.9842409341438);
    glVertex2f(583.7474740298452,748.9842409341438);
    glVertex2f(584.2688700850138,748.9497695050829);
    glVertex2f(585.0,749.0);
    glVertex2f(585.6013266704447,749.0749008934062);
    glVertex2f(586.3110046344241,749.1474288601681);
    glVertex2f(587.0206825984036,749.4738047122167);
    glVertex2f(587.6144947723457,749.5282006875582);
    glVertex2f(588.3096895125705,749.636992638241);
    glVertex2f(589.1786829378515,749.582596628996);
    glVertex2f(589.9462937968497,749.5644646711191);
    glVertex2f(590.6559717608292,749.5100686957777);
    glVertex2f(591.119434920979,749.2018248355096);
    glVertex2f(591.6842806474117,749.1836928437291);
    glVertex2f(592.6112069677114,749.0386369094853);
    glVertex2f(593.5236500642565,748.9479769505829);
    glVertex2f(594.0,749.0);
    glVertex2f(594.4505763845561,748.8573169916805);
    glVertex2f(594.9430059922154,748.8391849999);
    glVertex2f(595.3340503335919,748.5128091478514);
    glVertex2f(595.7830329699871,748.2589612629247);
    glVertex2f(596.4347780389478,748.0950593533394);
    glVertex2f(596.6809928427774,747.5336815917055);
    glVertex2f(596.7823754090603,746.8084019204865);
    glVertex2f(596.8904374934501,746.2379336476513);
    glVertex2f(597.04294517578,745.5816150643734);
    glVertex2f(597.052476059526,745.1639577841057);
    glVertex2f(597.0715403662168,744.7343674386874);
    glVertex2f(597.1096672867973,744.4002416144732);
    glVertex2f(597.1477942073817,743.9348520736035);
    glVertex2f(597.2240480485466,743.3023996206266);
    glVertex2f(597.3098336198572,742.8131439494558);
    glVertex2f(597.338428810294,742.2403568222314);
    glVertex2f(597.3765557308765,741.4647705787485);
    glVertex2f(597.4242143816045,740.6413260920635);
    glVertex2f(597.4051509213133,740.0446728345381);
    glVertex2f(597.4337461117501,739.4360865118623);
    glVertex2f(597.4623413021869,738.8394332543369);
    glVertex2f(597.4528095720414,738.2308469316611);
    glVertex2f(597.4718730323326,737.7172513018193);
    glVertex2f(597.4658370601203,737.3284040765237);
    glVertex2f(597.5,737.0);
    glVertex2f(597.4658370601203,736.6483769579523);
    glVertex2f(597.4583962007132,736.359598318559);
    glVertex2f(597.4658370601203,735.9310880794593);
    glVertex2f(597.5104822165632,734.7387117619643);
    glVertex2f(597.5,734.5);
    glVertex2f(597.8803171264833,734.5207295919463);
    glVertex2f(601.8094127493542,734.5881125405892);
    glVertex2f(601.7951615224515,739.681321284932);
    glVertex2f(601.6725420915686,741.6855777170113);
    glVertex2f(601.3940489819951,743.3591172082422);
    glVertex2f(601.3197841527755,745.0791439075628);
    glVertex2f(601.3383503600804,746.6132217745244);
    glVertex2f(601.4126151893,748.2170304536207);
    glVertex2f(601.2640855308607,749.9370571529413);
    glVertex2f(601.3287814047691,751.6980204129766);
    glVertex2f(601.2149091610665,752.8995988410045);
    glVertex2f(601.1823742342943,754.5492234625343);
    glVertex2f(601.0,756.0);
    glVertex2f(601.0,757.0);
    glVertex2f(601.0,758.0);
    glVertex2f(600.8587297279964,758.7507740585514);
    glVertex2f(600.7537343608185,759.2911669495912);
    glVertex2f(600.3920836488346,759.4518242955761);
    glVertex2f(600.0187667855052,759.5686660017469);
    glVertex2f(599.447125338532,759.7147181344603);
    glVertex2f(599.0,760.0);
    glVertex2f(598.0,760.0);
    glVertex2f(597.3747087112712,760.3184941884089);
    glVertex2f(596.939216827884,760.9895165123196);
    glVertex2f(596.419976505384,761.7863555219636);
    glVertex2f(595.9174858077066,762.7928890078297);
    glVertex2f(595.381495860384,763.7155447032069);
    glVertex2f(594.8455058500614,764.5752920557175);
    glVertex2f(594.3765145910291,765.5818255415835);
    glVertex2f(593.9912717711098,766.3157562083609);
    glVertex2f(593.5390301999001,767.1125952180048);
    glVertex2f(593.1705370678034,768.0142814657598);
    glVertex2f(592.6217171558826,769.3095318088638);
    glVertex2f(592.1031654151165,770.5460857511655);
    glVertex2f(591.6586924944597,771.8444673905824);
    glVertex2f(590.4734313727087,774.1939198809556);
    glVertex2f(589.979572571979,775.5541292174876);
    glVertex2f(589.5543649615023,776.6770799385639);
    glVertex2f(589.2668041481527,777.3670918161232);
    glVertex2f(589.0151884364718,778.1771057593448);
    glVertex2f(588.7515910242438,778.7621158294494);
    glVertex2f(588.428401529677,779.431278805877);
    glEnd();


    // plan front

    glBegin(GL_POLYGON);
    glColor3f(0.121f, 0.302f, 0.459f);
    glVertex2f(565.190702309754, 864.8063313337336);
    glVertex2f(564.210282363605, 863.5788457862573);
    glVertex2f(563.3634551729751, 862.3513602387809);
    glVertex2f(562.0, 860.0);
    glVertex2f(561.0905380028356, 858.3899296082891);
    glVertex2f(560.0209299227699, 856.492906489462);
    glVertex2f(559.0850228527124, 854.0937301921218);
    glVertex2f(558.1045487793189, 851.5829642995566);
    glVertex2f(557.3460977220657, 849.853325753672);
    glVertex2f(556.856672685909, 847.844712859515);
    glVertex2f(556.0, 845.0);
    glVertex2f(555.7870646058433, 842.6000018839433);
    glVertex2f(555.608796592499, 840.2566203842067);
    glVertex2f(555.608796592499, 838.303802467767);
    glVertex2f(555.6979305991711, 835.7372417775892);
    glVertex2f(556.1914336792327, 833.3264095972971);
    glVertex2f(556.500487117291, 830.5406722357576);
    glVertex2f(557.3040281962199, 827.6000791874659);
    glVertex2f(558.5402443262057, 824.8142968259264);
    glVertex2f(560.0237036821886, 821.5642174041303);
    glVertex2f(561.3217306186738, 819.5522634763518);
    glVertex2f(562.8051899746567, 817.8498409220775);
    glVertex2f(564.1650277176411, 815.9152698376752);
    glVertex2f(565.0, 815.0);
    glVertex2f(566.0980211689047, 813.8483537205442);
    glVertex2f(567.2608612322068, 812.586664616933);
    glVertex2f(569.4314960170376, 810.8397104717072);
    glVertex2f(571.9897441563023, 808.8986503111672);
    glVertex2f(574.5479922955672, 807.054631586542);
    glVertex2f(577.958989145869, 805.2106360061413);
    glVertex2f(581.6800780171538, 803.5607348696823);
    glVertex2f(584.8580575235131, 802.0078867412502);
    glVertex2f(588.8896864096274, 800.6491446288722);
    glVertex2f(592.3782065995339, 800.0668265807102);
    glVertex2f(595.6341587767799, 799.3874555245212);
    glVertex2f(599.2777243084602, 799.3874555245212);
    glVertex2f(602.6887218274799, 799.2904025164942);
    glVertex2f(606.7199007135941, 799.3874555245212);
    glVertex2f(610.0, 800.0);
    glVertex2f(614.9373038275961, 800.8432506449262);
    glVertex2f(619.9762774352389, 802.1049397492773);
    glVertex2f(625.0152510428817, 804.0459990988172);
    glVertex2f(629.7441339669772, 806.0841130783842);
    glVertex2f(633.6202675113178, 808.7045442951132);
    glVertex2f(637.263833042998, 811.2279225038152);
    glVertex2f(640.0546491949233, 814.0424597365982);
    glVertex2f(642.84546535468485, 817.7304740416242);
    glVertex2f(645.171454734528, 820.6402642824343);
    glVertex2f(647.1895293725226, 825.3339583210851);
    glVertex2f(649.2220049290618, 830.9682493033644);
    glVertex2f(650.09306590115, 836.3299133026302);
    glVertex2f(650.09306590115, 840.6919450308465);
    glVertex2f(650.0, 845.0);
    glVertex2f(648.7864744430177, 849.1433815042654);
    glVertex2f(647.4072945705447, 853.2327862494682);
    glVertex2f(645.2296421403241, 857.50394231668);
    glVertex2f(643.0519897101036, 860.7754661128421);
    glVertex2f(640.874837279883, 864.2287412301133);
    glVertex2f(638.6966848496625, 867.1367623831575);
    glVertex2f(637.2481879762048, 869.0918860776922);
    glVertex2f(635.4944527595056, 870.9737904502476);
    glVertex2f(633.6780837757814, 872.9341075049929);
    glVertex2f(631.9243483790822, 874.2671231022197);
    glVertex2f(631.1929817427896, 875.303626241383);
    glVertex2f(630.048684714319, 876.3410121400203);
    glVertex2f(628.7860121311792, 877.4771966956708);
    glVertex2f(627.1682128840313, 878.6627805798279);
    glVertex2f(626.0, 880.0);
    glVertex2f(624.6823262359746, 880.6387537200895);
    glVertex2f(623.3801951346115, 881.6267402920204);
    glVertex2f(622.1964395879179, 882.6147268603512);
    glVertex2f(620.933767004778, 883.4545154449625);
    glVertex2f(619.631635903415, 884.0967067155475);
    glVertex2f(617.658709992259, 885.1834919426914);
    glVertex2f(616.0, 886.0);
    glVertex2f(613.9496092792856, 887.1594650829531);
    glVertex2f(612.778502863599, 887.8043886472406);
    glVertex2f(611.8962737702342, 888.3566334699519);
    glVertex2f(610.4626514935163, 889.0124241969215);
    glVertex2f(609.5804224001515, 889.2540313068578);
    glVertex2f(608.836041602625, 889.5991843210523);
    glVertex2f(608.0, 890.0);
    glVertex2f(607.394227821724, 890.2342954653226);
    glVertex2f(606.7020954007969, 890.4610273633293);
    glVertex2f(605.9201335387334, 890.5933195288715);
    glVertex2f(605.2649763029503, 890.7256116944136);
    glVertex2f(604.849593713874, 890.6492375267455);
    glVertex2f(604.4979374469945, 890.5913099925332);
    glVertex2f(604.0722482818244, 890.5681389788482);
    glVertex2f(603.6743214535132, 890.5217969514783);
    glVertex2f(603.2301240637706, 890.5217969514783);
    glVertex2f(602.8136890188886, 890.463869417266);
    glVertex2f(602.4712868562935, 890.463869417266);
    glVertex2f(601.9993271296919, 890.3943563762111);
    glVertex2f(601.4440803925136, 890.3943563762111);
    glVertex2f(601.0831700133476, 890.3943563762111);
    glVertex2f(600.7686471263934, 890.3661847489344);
    glVertex2f(600.3612263217381, 890.2961761575688);
    glVertex2f(599.8299815470403, 890.1911632705203);
    glVertex2f(599.3147140587998, 890.0861503834718);
    glVertex2f(598.84674049197632, 889.9441031845278);
    glVertex2f(598.5779860086269, 889.8401956441994);
    glVertex2f(598.2186001622995, 889.7329096787659);
    glVertex2f(597.6713787058421, 889.5592265846674);
    glVertex2f(597.2012306939562, 889.3372981866528);
    glVertex2f(596.5461064150988, 889.0671244847218);
    glVertex2f(595.8524454139557, 888.7680036004413);
    glVertex2f(595.2666872352127, 888.4978298985104);
    glVertex2f(594.7811245344125, 888.2951996220622);
    glVertex2f(594.4083693297578, 888.1881827660974);
    glVertex2f(593.8071964621005, 887.9662543680828);
    glVertex2f(593.3909998614146, 887.7539750308514);
    glVertex2f(592.8823151272429, 887.54169569362);
    glVertex2f(592.3119716374142, 887.3004691740389);
    glVertex2f(591.9034823811854, 887.0592426544578);
    glVertex2f(591.5, 887);
    glVertex2f(591.2754520800261, 886.8237836956795);
    glVertex2f(591.0562472005957, 886.7041573198718);
    glVertex2f(590.6403083659842, 886.5000887964352);
    glVertex2f(590.269335891874, 886.2678728904556);
    glVertex2f(589.7747059263875, 885.9371411457575);
    glVertex2f(589.291375510281, 885.6697410114172);
    glVertex2f(588.6224429386124, 885.3601198034444);
    glVertex2f(588, 885);
    glVertex2f(587.1593518064064, 884.1451650466794);
    glVertex2f(585.7584239431822, 883.2528480023734);
    glVertex2f(584.5295398526345, 882.6682264905868);
    glVertex2f(583.5710126200073, 881.8998876592885);
    glVertex2f(582.5387476259473, 881.1605183812422);
    glVertex2f(581.4081742626435, 880.422049103196);
    glVertex2f(580.0564017630411, 879.098958313363);
    glVertex2f(578.6308962180059, 877.837406630034);
    glVertex2f(576.7138370367516, 876.3604680739414);
    glVertex2f(574.968216281739, 874.9142990711008);
    glVertex2f(573.6170419285715, 873.7142864942756);
    glVertex2f(572.314439192591, 872.4219652576945);
    glVertex2f(570.9380818111777, 870.9142571483501);
    glVertex2f(569.70919772063, 869.4988576987613);
    glVertex2f(568.7506681300029, 868.6373102077074);
    glVertex2f(568, 868);
    glVertex2f(566.9319196759924, 866.7603674593397);
    glVertex2f(565.8750793581214, 865.7142026487742);
    glEnd();



    //window
    if(isDay)
    {
        glBegin(GL_POLYGON);
        glColor3f(0,0,0);
        glVertex2f(653.085797177614,863.8431528852958);
        glVertex2f(652.3733204148647,866.7210247625234);
        glVertex2f(651.5580951663206,871.2797292317584);
        glVertex2f(650.5798248680677,876.9270795443931);
        glVertex2f(650.0363413690384,880.9414610919285);
        glVertex2f(657.0472785065174,875.6343126053563);
        glVertex2f(661.2864497989465,872.5044558055829);
        glVertex2f(665,870);
        glVertex2f(666.2606353198561,868.7419460060261);
        glVertex2f(667.9902041238955,866.6385115229441);
        glVertex2f(669.299977462515,864.2824721474332);
        glVertex2f(671.2772561302633,860.5473014381986);
        glVertex2f(671.8321567878198,859.3981841420479);
        glVertex2f(671.47502213035,858.1839924995439);
        glVertex2f(670.6745353904848,858.5284828983324);
        glVertex2f(669.4237748594454,858.9042906061015);
        glVertex2f(666.9222537973668,859.9690791114476);
        glVertex2f(663.6452612060438,860.845963762909);
        glVertex2f(661.61902914576,861.4096753245628);
        glVertex2f(659.1675385049228,862.1926080490821);
        glVertex2f(656.9912151809144,862.8815888466589);
        glVertex2f(654.4146484869733,863.2260792454473);
        glEnd();

    }
    else
    {
        glBegin(GL_POLYGON);
        glColor3f(1,1,1);
        glVertex2f(653.085797177614,863.8431528852958);
        glVertex2f(652.3733204148647,866.7210247625234);
        glVertex2f(651.5580951663206,871.2797292317584);
        glVertex2f(650.5798248680677,876.9270795443931);
        glVertex2f(650.0363413690384,880.9414610919285);
        glVertex2f(657.0472785065174,875.6343126053563);
        glVertex2f(661.2864497989465,872.5044558055829);
        glVertex2f(665,870);
        glVertex2f(666.2606353198561,868.7419460060261);
        glVertex2f(667.9902041238955,866.6385115229441);
        glVertex2f(669.299977462515,864.2824721474332);
        glVertex2f(671.2772561302633,860.5473014381986);
        glVertex2f(671.8321567878198,859.3981841420479);
        glVertex2f(671.47502213035,858.1839924995439);
        glVertex2f(670.6745353904848,858.5284828983324);
        glVertex2f(669.4237748594454,858.9042906061015);
        glVertex2f(666.9222537973668,859.9690791114476);
        glVertex2f(663.6452612060438,860.845963762909);
        glVertex2f(661.61902914576,861.4096753245628);
        glVertex2f(659.1675385049228,862.1926080490821);
        glVertex2f(656.9912151809144,862.8815888466589);
        glVertex2f(654.4146484869733,863.2260792454473);
        glEnd();
    }






    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(604.6986047338384,901.2477031840838);
    glVertex2f(608.871694914543,900.3055947465587);
    glVertex2f(615.7128263583212,898.0787929851355);
    glVertex2f(622.8276030598505,895.3381138941533);
    glVertex2f(628.7793874159375,892.3404961383914);
    glVertex2f(635.210050973089,888.7433548314771);
    glVertex2f(640.0672542981715,886.6021992916473);
    glVertex2f(644.7192236799407,883.5189353142921);
    glVertex2f(646.9083857419497,882.4055344335806);
    glVertex2f(647.2504423141386,879.1509780130391);
    glVertex2f(647.7149551391711,875.0673661674767);
    glVertex2f(648.04606590105,869.574873976705);
    glVertex2f(648.267696999058,866.8306031557613);
    glVertex2f(648.4620045652186,864.9892850707082);
    glVertex2f(646.9458073321346,865.0956553608485);
    glVertex2f(645.6900601373691,865.4154062231296);
    glVertex2f(644.4130290918449,865.7618029906009);
    glVertex2f(642.880591837216,866.1614915684524);
    glVertex2f(641.8802508515554,866.5611801463039);
    glVertex2f(640.8160583136187,866.5878260514941);
    glVertex2f(639.5390272680945,866.3480129047831);
    glVertex2f(638,868);
    glVertex2f(636.2460358387826,870.1631489136956);
    glVertex2f(634.6253947797202,872.1601251478139);
    glVertex2f(632.8499236048322,873.6990709432281);
    glVertex2f(630.6228876531118,875.9861797738565);
    glVertex2f(629.3875786486419,877.1624071724655);
    glVertex2f(627.8738901502071,878.3604165599374);
    glVertex2f(626.5551726867593,879.2255067490058);
    glVertex2f(625.2107697212007,880.170809086193);
    glVertex2f(623.7374514027804,881.0930552688146);
    glVertex2f(622.5403802690639,882.2228068425261);
    glVertex2f(621.2880596984066,883.0067160977545);
    glVertex2f(620,884);
    glVertex2f(618.7788751970318,884.5664325973004);
    glVertex2f(616.6109311485891,885.7727062014744);
    glVertex2f(614.9849731122572,886.6774114046049);
    glVertex2f(611.1308503594703,888.675302061518);
    glVertex2f(608.40477160518,889.6840855332032);
    glVertex2f(605.4212121504639,890.3632145401123);
    glVertex2f(605.3070089177476,892.5793197205522);
    glVertex2f(605.1367520234952,894.8014778360846);
    glVertex2f(605.0219194039569,897.3339920459939);
    glVertex2f(604.8119466380924,899.3672333645479);
    glEnd();



    glPopMatrix();
}


void resetPlane(int value)
{
    newPlaneIncoming = true;
    planeX = 475.0f;
    planeY = 550.0f;
    planeScale = 0.1f;
    planeLanded = false;
    glutTimerFunc(30, updatePlane, 0);
}






void updatePlane(int value)
{
    if (planeLanded)
    {
        newPlaneIncoming = false;
        glutTimerFunc(5000, resetPlane, 0); // Wait 5 seconds before new plane appears
        return;
    }

    if (!isStopped)
    {
        planeX -= 6.0f;  // Move left
        planeY -= 13.0f; // Move downward
        planeScale += 0.010f; // Increase size

        if (planeX <= targetX && planeY <= targetY)
        {
            planeLanded = true;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(80, updatePlane, 0);
}


void display_m()
{
    glClear(GL_COLOR_BUFFER_BIT);

    sky();


    for (int i = 0; i < 10; i++)
    {
        if (i % 3 == 0)
        {
            drawCloud1(cloud_positions[i][0], cloud_positions[i][1]);
        }
        else if (i % 3 == 1)
        {
            drawCloud2(cloud_positions[i][0], cloud_positions[i][1]);
        }
        else
        {
            drawCloud3(cloud_positions[i][0], cloud_positions[i][1]);
        }
    }

    tiles();
    field1();

    tiles2();
    field2();
    tiles3();

    field3();
    big_filed();
    field4();
    field5();

    road1();
    road2();
    road3();


    roadstarucureline1();
    crossline1();
    crossline2();
    crossline3();
    crossline4();
    crossline5();
    crossrunwayline1();
    crossrunwayline2();
    line2();
    line3();
    longline();
    building1();
    building2();

    building3();
    signalline();

    tower();
    tree();
    semcircle();
    fench();
    semcircle1();
    fench2();
    text();
    plane();
    drawRain();
    drawMoon();
    glutSwapBuffers();



}

#include <iostream>
#include <GL/glut.h>

// Function to display keyboard and mouse controls in a visually appealing way
void dc() {
    std::cout << "========================================\n";
    std::cout << "          CONTROL INSTRUCTIONS          \n";
    std::cout << "========================================\n\n";

    std::cout << " Keyboard Controls:\n";
    std::cout << "----------------------------------------\n";
    std::cout << " [D / d]  - Switch to Day mode\n";
    std::cout << " [N / n]  - Switch to Night mode\n";
    std::cout << " [R / r]  - Toggle Rain On/Off\n";
    std::cout << " [M / m]  - Toggle Moon Visibility\n";
    std::cout << " [F / f]  - Toggle Fullscreen\n";
    std::cout << " [Esc]    - Exit the Program\n";
    std::cout << "----------------------------------------\n\n";

    std::cout << " Mouse Controls:\n";
    std::cout << "----------------------------------------\n";
    std::cout << " [Left Click] - Toggle Stop/Resume\n";
    std::cout << "========================================\n\n";
}

void timer_m(int value)
{
    updateCloudPositions();
    glutTimerFunc(12, timer_m, 0);

}

///////////shoikot////////////////////
/////////////////




// Cloud positions
float cloud1X2 = 100;
float cloud2X2 = 500;

float planex2 = 1200, planey = 600;

float landingx2 = 5.0f;
float landingy2 = 2.0f;

float takeoffx2 = 5.0f, takeoffy2 = 2.0f;




bool isLanding2 = false;
bool isNightMode2 = false;
bool isTakeOff2 = false;

bool isRaining2 = false;

const int numRaindrops2 = 1000;
float rainX[numRaindrops2];
float rainY[numRaindrops2];

void initRain2() {
    for (int i = 0; i < numRaindrops2; i++) {
        rainX[i] = rand() % 1200; // Random
        rainY[i] = rand() % 1000;
    }
}

void drawRain2() {
    if (!isRaining2) return;

    glColor3f(0.6, 0.6, 1.0); // Light blue raindrops
    glBegin(GL_LINES);
    for (int i = 0; i < numRaindrops2; i++) {
        glVertex2f(rainX[i], rainY[i]);
        glVertex2f(rainX[i], rainY[i] - 10); // Raindrop length
    }
    glEnd();
}

void updateRain2(int value) {
    if (isRaining2) {
        for (int i = 0; i < numRaindrops2; i++) {
            rainY[i] -= 5; // Move raindrops down

            if (rainY[i] < 0) { // Reset raindrop when it reaches bottom
                rainY[i] = 1000;
                rainX[i] = rand() % 1200; // New random X position
            }
        }
        glutPostRedisplay();
    }
    glutTimerFunc(30, updateRain2, 0); // Repeat every 30ms
}


void plane2(){



if (isLanding2) {
        if (planex2 > -800) planex2 -= landingx2;
        if (planey > 200) planey -= landingy2;
        if (planex2 <= -800 && planey<= 200) {
            isLanding2 = false;
        }
    }

if (isTakeOff2) {   //shoikot
    if (planex2 < 200) {
        planex2 += takeoffx2;  // Move forward on the ground
    } else {
        planex2 += takeoffx2;  // Continue moving forward
        planey += takeoffy2;  // Start taking off
    }

    if (planex2 >= 1200 || planey>= 900) {  // Stop when fully out of screen
        isTakeOff2 = false;
    }
}

glPushMatrix();

glTranslatef(planex2 -280, planey -620, 0.0f);
    // plan body
    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex2f(601.7013684734217,822.7771865940432);
    glVertex2f(616.5624037600165,822.8872683369069);
    glVertex2f(625.3689431891098,827.0703745657262);
    glVertex2f(632.9645834467028,833.1248704232279);
    glVertex2f(641.3307959043415,840.5003471950936);
    glVertex2f(650.2474170762983,848.6463961670048);
    glVertex2f(661.8060000769833,859.5444887105078);
    glVertex2f(670.9427847346676,868.6812733681921);
    glVertex2f(673.8049100491229,871.8736430112384);
    glVertex2f(676.0065449063962,874.1853605113755);
    glVertex2f(677.8779345350786,875.7265049114668);
    glVertex2f(680.8501415923976,876.9374040829671);
    glVertex2f(683.6021851639891,877.7079762830127);
    glVertex2f(687.1248009356265,877.2676493115581);
    glVertex2f(691.0877436787184,876.7172405972398);
    glVertex2f(695.9313403647197,875.7265049114668);
    glVertex2f(699.0136291649025,875.7265049114668);
    glVertex2f(701.2152640221757,874.1853605113755);
    glVertex2f(700,870);
    glVertex2f(698.3531387077204,863.2872679678725);
    glVertex2f(677.9880162779422,810.8883583647672);
    glVertex2f(678.4335824768156,809.0619753795652);
    glVertex2f(682.2606173090358,807.6123409734212);
    glVertex2f(687.0734035374338,806.3946480722602);
    glVertex2f(692.5820142807811,804.249189151167);
    glVertex2f(696.7569613704758,800.9440227051587);
    glVertex2f(698.4965226578486,797.7548270116419);
    glVertex2f(697.9746542716368,794.3916751893878);
    glVertex2f(671.0114543173582,789.752845089727);
    glVertex2f(649.5826595925173,786.4208318745342);
    glVertex2f(627.0691748781237,784.039597914358);
    glVertex2f(603.5815489982034,783.173694656112);
    glVertex2f(583.2328224294246,782.9572188415506);
    glVertex2f(566.4177682991556,783.4595735040637);
    glVertex2f(553.1805927650474,784.1132611847603);
    glVertex2f(536.5405324795405,785.7569049882529);
    glVertex2f(519.9350176210129,787.6468406859151);
    glVertex2f(506.4259416134842,789.2222282255444);
    glVertex2f(490.827605780575,791.2679116134669);
    glVertex2f(471.6799013933147,793.4260276476035);
    glVertex2f(319.7491964930285,818.3090803410508);
    glVertex2f(312.4413919713593,819.6495133743365);
    glVertex2f(306.3156307666736,820.8084411698176);
    glVertex2f(300.1898695619879,822.4640523062192);
    glVertex2f(295,825);
    glVertex2f(290.4217638572188,828.0103496131644);
    glVertex2f(287.0277610275957,832.3149385678084);
    glVertex2f(286.1999554593049,837.7784553179337);
    glVertex2f(288.6005916071771,842.5797276134982);
    glVertex2f(294.1468889141223,845.1459248749206);
    glVertex2f(298.3686973119462,846.8843165681423);
    glVertex2f(301.5143584711091,847.2154387954225);
    glVertex2f(304.8255807439122,847.712122136343);
    glVertex2f(307.0606557780543,849.4505138295647);
    glVertex2f(309.2957308121964,851.7683694205269);
    glVertex2f(312.110269744079,854.0862250114891);
    glVertex2f(316.0009559146226,856.072958375171);
    glVertex2f(323.6084683806805,858.2562240694856);
    glVertex2f(332.3583891523874,858.6494789356298);
    glVertex2f(339.7319178925899,858.4528515025577);
    glVertex2f(349.8582306958014,857.9612820198775);
    glVertex2f(359.4929749163326,856.7815183214451);
    glVertex2f(370.5041111683683,855.8966948726207);
    glVertex2f(382.0068160030842,854.3236754080442);
    glVertex2f(407.7139011876407,850.8951477649068);
    glVertex2f(426.2403088599048,848.9269556324431);
    glVertex2f(447.302250245076,845.2237571471381);
    glVertex2f(472.9931897368784,843.1407079991542);
    glVertex2f(500,840);
    glVertex2f(518.1259212765311,836.428660744539);
    glVertex2f(542.6596112416756,832.9569121645657);
    glVertex2f(559.3240044255474,830.6424131112501);
    glVertex2f(572.0537492187829,828.559363963266);
    glVertex2f(583.3947945800289,826.7077647206136);
    glVertex2f(591.7269911719648,825.0876153832927);
    glEnd();


//plan pakha

    glBegin(GL_POLYGON);
    glColor3f(0.671, 0.671, 0.671);
    glVertex2f(396.9036705680077,809.4761894569062);
    glVertex2f(403.6439874186744,809.8994102235503);
    glVertex2f(410,810);
    glVertex2f(416.3890938123589,808.7482393234756);
    glVertex2f(423.8717046628445,806.7748034947759);
    glVertex2f(428.7230677417309,805.0480471446638);
    glVertex2f(432.7521658919924,802.4167993730644);
    glVertex2f(435,800);
    glVertex2f(435.0545076921418,797.400983308453);
    glVertex2f(434.6433752278294,794.2763765796788);
    glVertex2f(434.1500162706545,791.6451288080793);
    glVertex2f(433.0810718634423,788.2738426007176);
    glVertex2f(432.176580441955,786.629312743468);
    glVertex2f(431.0254095418803,785.4781418433931);
    glVertex2f(428.8052042345933,784.7381034076308);
    glVertex2f(424.3650636200194,784.1625179575934);
    glVertex2f(418.6914356125083,784.2447444504559);
    glVertex2f(413.1822605907221,784.5736504219059);
    glVertex2f(406.3574616831363,785.3959153505307);
    glVertex2f(400.9305131542126,786.5470862506054);
    glVertex2f(396.6547355253636,788.0271631221301);
    glVertex2f(393.6123552894518,789.7539194722422);
    glVertex2f(392.7078638679645,793.6185646367788);
    glVertex2f(392.954543346552,798.6343807013902);
    glVertex2f(394.0234877537642,804.7191411732139);
    glEnd();

//pakha picone side

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(435.9567675257559,799.52762557011);
    glVertex2f(439.0196231814829,798.5331919156531);
    glVertex2f(442.4802522989928,797.0216527608787);
    glVertex2f(446.0602134550374,795.6204456446391);
    glVertex2f(449.1230691107645,794.3565705669344);
    glVertex2f(450.8732723426085,793.6803556819036);
    glVertex2f(451.9870380356002,792.5268126427337);
    glVertex2f(452.4271709945014,790.77567234407);
    glVertex2f(451.6347863890862,789.6175717669247);
    glVertex2f(450.6290674668284,788.6728055066219);
    glVertex2f(448.7090586152455,788.4594711897793);
    glVertex2f(447.002384080505,788.2766132039143);
    glVertex2f(445.5090438626071,788.0328025560942);
    glVertex2f(443.1318900463616,787.8804209012067);
    glVertex2f(440.9071178850035,787.7280392463191);
    glVertex2f(438.1642480970278,787.6975620153416);
    glVertex2f(436.4575735622874,787.7585155772066);
    glVertex2f(435.2689966541646,787.7585155772966);
    glVertex2f(434.0499434150643,786.8442256479714);
    glVertex2f(432.5261268661889,786.3261280213537);
    glVertex2f(433.6657998943709,790.252677886258);
    glVertex2f(434.4647565627031,793.4485045595866);
    glVertex2f(434.8255757032402,796.2061937051201);
    glVertex2f(435.2637132310352,799.1185196251696);
    glEnd();

//plan window

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(308.6783405097053,848.2569399231455);
    glVertex2f(309.2960904711659,847.3179599817253);
    glVertex2f(310.7539803802131,846.7990500140983);
    glVertex2f(312,846);
    glVertex2f(313.5462102060155,846.378980040305);
    glVertex2f(314.386350153602,848.2322209246871);
    glVertex2f(314.8805501227705,849.6406998368175);
    glVertex2f(314.5840301412604,850.9750397535727);
    glVertex2f(313.2744002229728,851.4692397227412);
    glVertex2f(311.7670903170087,851.691629708867);
    glVertex2f(310.8281103755884,851.0985897458647);
    glVertex2f(310.0373904249188,850.3325797936535);
    glVertex2f(309.3455104680828,849.5912798399006);
    glEnd();

//plan window2
    glBegin(GL_POLYGON);
    glColor3f(0,0,0);

    glVertex2f(315.6712700734402,846.3542700418466);
    glVertex2f(316.3137300333593,845.4400000988848);
    glVertex2f(318.1175599208245,845.2917401081341);
    glVertex2f(319.9460998067481,845.2670301096757);
    glVertex2f(322.886589623301,848.2075199262287);
    glVertex2f(323.1288332291762,848.9642452259202);
    glVertex2f(322.6765300989596,849.5431932325974);
    glVertex2f(322.0794899670737,849.8145751107273);
    glVertex2f(321.3377128335185,849.9593121123967);
    glVertex2f(320.5778435747546,850.0859569888573);
    glVertex2f(319.9446191924514,850.1764176149006);
    glVertex2f(319.1304735580616,850.2487861157352);
    glVertex2f(318.3886964245064,850.3754309921959);
    glVertex2f(317.7554720422032,850.4477994930306);
    glVertex2f(317.2488925363606,850.4477994930306);
    glVertex2f(316.8870500321873,850.1402333644833);
    glVertex2f(316.5975760288487,849.5793774830147);
    glVertex2f(316.3081020255101,848.9099688502941);
    glVertex2f(316.0909965230061,848.4395735948689);
    glVertex2f(316,848);
    glVertex2f(315.8015225196675,847.4806909588098);
    glVertex2f(315.6567855179982,847.1912169554711);
    glEnd();

//plan design 1

    glBegin(GL_POLYGON);
    glColor3f(1,1,0);
    glVertex2f(407.1423639682738,825.3805972762892);
    glVertex2f(402.1055975488507,827.9829265929911);
    glVertex2f(397.0688311294275,829.4100104118277);
    glVertex2f(392.7875796729178,830.3334175887219);
    glVertex2f(387.8347593604851,831.7605014075584);
    glVertex2f(384.2250767598085,832.5999624774623);
    glVertex2f(380.6153941593119,833.3554774403758);
    glVertex2f(373.6478672791099,834.7825612592123);
    glVertex2f(370,835);
    glVertex2f(365.3372026870616,835.789914543097);
    glVertex2f(360.3004362676385,836.1256989710585);
    glVertex2f(354.9042136279606,836.2550362998896);
    glVertex2f(349.6176464024862,836.3245963949616);
    glVertex2f(342.383396514995,835.9767959196015);
    glVertex2f(335.2187067225758,835.8376757294575);
    glVertex2f(330,835);
    glVertex2f(325.7445082308466,835.0310744947442);
    glVertex2f(319.5300129313596,834.3248716198025);
    glVertex2f(314.4453522317793,834.1130107573199);
    glVertex2f(307.3833234823622,833.1949470198957);
    glVertex2f(303.9229293951478,832.6299847199424);
    glVertex2f(299.6150918580034,831.8531615575065);
    glVertex2f(294.8835325958939,830.9350978200823);
    glVertex2f(292.6179146963481,830.228782596669);
    glVertex2f(290.8073289847237,829.9077709529598);
    glVertex2f(289.4095075299198,829.3004080703579);
    glVertex2f(291.7132579522276,826.9966576480501);
    glVertex2f(293.2623315120553,826.1625411158353);
    glVertex2f(296.7576769803844,824.4545882165381);
    glVertex2f(298.5450695494163,823.4615923448538);
    glVertex2f(302.7553720453581,821.991958454761);
    glVertex2f(305.1385621374006,821.3564410968829);
    glVertex2f(307.5217522294432,820.6414840692702);
    glVertex2f(308.8722266149339,822.1508377942304);
    glVertex2f(310.8979381931702,823.2629931705169);
    glVertex2f(312.6853307622021,823.8587906935276);
    glVertex2f(315.5848787075205,824.6134675560077);
    glVertex2f(318.2461076436347,825.0901055744162);
    glVertex2f(320.390978726473,825.5667435928247);
    glVertex2f(323.2494035104907,826.0984452767516);
    glVertex2f(327.8401696949939,826.6034295570469);
    glVertex2f(333.1195508071726,827.6593057794826);
    glVertex2f(337.4807786824507,828.3479207071581);
    glVertex2f(342.3469908380241,828.3479207071581);
    glVertex2f(346.8918493606823,828.5774590163833);
    glVertex2f(350.8858159412001,828.7151820019184);
    glVertex2f(354.9256901835629,828.6692743400733);
    glVertex2f(359.2410103969959,828.5774590163833);
    glVertex2f(363.1890693156687,828.4397360308482);
    glVertex2f(366.8097893523812,828.3796207611747);
    glVertex2f(370.4428452190587,828.1814540775378);
    glVertex2f(375.5951789936195,827.9172318326886);
    glVertex2f(378.6997903705985,827.7190651490516);
    glVertex2f(383.7860685839469,827.2566762205654);
    glVertex2f(388.8062912360831,826.7942872920792);
    glVertex2f(393.0338471536715,826.1997872411683);
    glVertex2f(396.5347918979243,826.0676761187436);
    glVertex2f(400,825);
    glVertex2f(402.7440146518823,825.4731760678328);
    glVertex2f(405,825);
    glEnd();


//plan design 2

    glBegin(GL_POLYGON);
    glColor3f(1,0,0);
    glVertex2f(677.5502946448202,808.9840128712718);
    glVertex2f(680.3668794105798,808.2257015881827);
    glVertex2f(684.2667660093239,806.9799044802506);
    glVertex2f(688.9791289828064,805.4632819140724);
    glVertex2f(693.6914919562888,803.1341829731558);
    glVertex2f(697.4830483717345,799.6134520159563);
    glVertex2f(698.4580200214206,796.5802068835999);
    glVertex2f(696.39974653875,793.7094570261911);
    glVertex2f(694.2873079644303,793.0594759264004);
    glVertex2f(691.2540628320738,792.4636599182589);
    glVertex2f(688.7624686162095,792.0303391850651);
    glVertex2f(685.6296410005061,791.7896197030336);
    glVertex2f(682.4524799786475,791.4366018117161);
    glVertex2f(679.8048457937653,791.0835839203984);
    glVertex2f(676.4511758262478,790.554057083422);
    glVertex2f(667.4492195976482,789.2302399909809);
    glVertex2f(661.359660972419,788.3476952626868);
    glVertex2f(655.7113747113368,788.171186317028);
    glVertex2f(645.4738558631254,788.2594407898574);
    glVertex2f(638.7665159280905,789.5832578822985);
    glVertex2f(632.3239394115436,791.0835839203984);
    glVertex2f(625.6165994765087,792.7604189041572);
    glVertex2f(619.3980736937012,793.9869604308165);
    glVertex2f(612.80396446208,795.6825885189476);
    glVertex2f(605.6446458677483,796.6246041234649);
    glVertex2f(598.67373039432,797.5666197279822);
    glVertex2f(590,800);
    glVertex2f(568.6824424536608,803.1523659965385);
    glVertex2f(553.2150142656674,805.6471124784729);
    glVertex2f(542.7370790415428,807.8092260961494);
    glVertex2f(530,810);
    glVertex2f(517.7896142221986,812.2997697636313);
    glVertex2f(500.3263888486576,814.7945162455657);
    glVertex2f(487.1873907104697,816.1250477025973);
    glVertex2f(472.7178611152501,817.9545284560159);
    glVertex2f(460,820);
    glVertex2f(449.7661934814535,821.280857098595);
    glVertex2f(440.8390864542306,822.186405181423);
    glVertex2f(432.9252236096611,823.5466003578333);
    glVertex2f(425.7532854067699,824.2885249995117);
    glVertex2f(418.0867307760932,825.1541037481364);
    glVertex2f(410.4201761454165,825.5250660689757);
    glVertex2f(404.5434183983594,827.5006502071003);
    glVertex2f(399.5823024435303,828.7409291958076);
    glVertex2f(395,830);
    glVertex2f(389.8789432965852,831.002614410509);
    glVertex2f(385.9392335677503,832.0969782240742);
    glVertex2f(382.4372693643416,832.6076813370713);
    glVertex2f(377.0384078840864,833.9209179133496);
    glVertex2f(371.6395464038312,834.7964089642018);
    glVertex2f(367.4080063247122,835.0152817269148);
    glVertex2f(362.8846358953093,835.890772777767);
    glVertex2f(381.2699479632053,836.5473910659061);
    glVertex2f(388.7116218954489, 835.963730365338);
    glVertex2f(394.4023137259882, 836.1096455404801);
    glVertex2f(402.573563533942, 835.5989424274829);
    glVertex2f(410, 835);
    glVertex2f(418.6925928313256, 834.4932842639238);
    glVertex2f(427.9100360256717, 834.4932842639238);
    glVertex2f(435.8866695592404, 834.4932842639238);
    glVertex2f(445.8131468454594, 833.7842501720511);
    glVertex2f(456.9804337924556, 833.0752160801783);
    glVertex2f(468.1477207394518, 832.1889234653373);
    glVertex2f(478.2514565486389, 831.1253723275281);
    glVertex2f(492.4321383860944, 829.7073041437826);
    glVertex2f(505.9037861316772, 828.289235960037);
    glVertex2f(518.1346242164826, 826.8711677762915);
    glVertex2f(529.8336867323834, 826.3393922073869);
    glVertex2f(538.1648373118886, 825.2758410695777);
    glVertex2f(544.7234026617117, 824.7440655006732);
    glVertex2f(553.0545532412169, 824.3895484547368);
    glVertex2f(560.8539282518175, 825.984751614505);
    glVertex2f(568.1215276935134, 828.289235960037);
    glVertex2f(575.2789187537646, 827.6697126687336);
    glVertex2f(579.685883879813, 827.0086972236011);
    glVertex2f(588.0585069299298, 825.3561586107699);
    glVertex2f(596.1009052754382, 823.813789238794);
    glVertex2f(605.9059677115703, 821.5002351808303);
    glVertex2f(613.507645330594, 820.618881253987);
    glVertex2f(620, 820);
    glVertex2f(628.7110005686413, 818.7460041594445);
    glVertex2f(637.8550475596479, 817.4239732691799);
    glVertex2f(646.7787560689295, 815.7714346563487);
    glVertex2f(653.3276300491149, 814.8267502010219);
    glVertex2f(658.2499414332626, 813.688396550488);
    glVertex2f(663.8315296426773, 812.912246334215);
    glVertex2f(669.5750412430981, 811.8256360314327);
    glVertex2f(675,810);
    glEnd();

//plan ar wheel

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(467.323604476862, 793.8868000927973);
    glVertex2f(467.1486076052906, 791.728505343418);
    glVertex2f(467.9069273820996, 790.3868626613713);
    glVertex2f(468.6069148683848, 789.3368814319434);
    glVertex2f(469.656890978127, 788.2285679119918);
    glVertex2f(470.823541908288, 786.945257520469);
    glVertex2f(471.6985262661445, 786.0702731626125);
    glVertex2f(471.9901877187634, 784.5536336089945);
    glVertex2f(471.2318679419544, 783.6786492511379);
    glVertex2f(473.7401564344764, 783.6786492511379);
    glVertex2f(475.6651220217607, 783.5619846700904);
    glVertex2f(477.0650969943311, 783.0369940553766);
    glVertex2f(477.8817490616639, 785.7202794149699);
    glVertex2f(478.2900750953302, 788.52022936464107);
    glVertex2f(478.9900625816154, 791.1451824381803);
    glVertex2f(477.8817490616639, 793.0701480254646);
    glVertex2f(474.5568085018091, 793.5368063496547);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(471.2318679419544, 783.6786492511379);
    glVertex2f(473.7401564344764, 783.6786492511379);
    glVertex2f(475.6651220217607, 783.5619846700904);
    glVertex2f(477.0650969943311, 783.0369940553766);
    glVertex2f(477.8817490616639, 785.7202794149699);
    glVertex2f(478.2900750953302, 788.52022936464107);
    glVertex2f(478.9900625816154, 791.1451824381803);
    glVertex2f(477.8817490616639, 793.0701480254646);
    glVertex2f(474.5568085018091, 793.5368063496547);
    glVertex2f(470.7795624232518, 782.9435456180261);
    glVertex2f(468.9685742727974, 781.8569527277534);
    glVertex2f(467.2662454113702, 779.7562064732263);
    glVertex2f(466.6505094402157, 777.2570428255991);
    glVertex2f(466.7591687292473, 774.757879177972);
    glVertex2f(467.8095418565065, 772.7295724494629);
    glVertex2f(469.5480940840927, 771.099683114054);
    glVertex2f(471.2328588683881, 770.3752878538721);
    glVertex2f(474, 770);
    glVertex2f(476.6833837937332, 771.1721226400721);
    glVertex2f(478.4943719441876, 772.9468910275175);
    glVertex2f(479.363462564057, 774.6854396519537);
    glVertex2f(479.5809648344603, 777.0397242475445);
    glVertex2f(479.1825474413603, 778.850712397999);
    glVertex2f(478.394928921513, 780.9514586525262);
    glVertex2f(477.2266802388695, 782.0380515427988);
    glVertex2f(476.5022849786877, 783.341963011126);
    glVertex2f(474.6912968282333, 783.6679408782079);
    glVertex2f(472.916528440788, 783.5230618261716);
    glVertex2f(471.685056498479, 783.0522040970534);
    glVertex2f(470.2665402309385, 782.593066506865);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex2f(470.6497536105954, 777.6078820251779);
    glVertex2f(471.6109943548288, 778.7250883066673);
    glVertex2f(473, 779);
    glVertex2f(474.1820970005985, 778.8400948356441);
    glVertex2f(475, 778);
    glVertex2f(475.4635983234833, 776.7535478099213);
    glVertex2f(475.1678672489715, 775.4063284704783);
    glVertex2f(474.3956805544127, 774.5519942552218);
    glVertex2f(473.7549298929702, 774.1905451641517);
    glVertex2f(472.7691596445973, 774.0426796268957);
    glVertex2f(471.4876583217124, 774.5519942552218);
    glVertex2f(470.8140486519909, 775.324180947806);
    glVertex2f(470.4854585691999, 776.6878297933631);
    glEnd();

//biman ar shamne wheel

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);

    glVertex2f(338.0860123426534, 814.9553895636764);
    glVertex2f(340.5028104776905, 814.8873107429711);
    glVertex2f(342.4770962781433, 814.5469166394447);
    glVertex2f(343.8727121026013, 813.491694918513);
    glVertex2f(344, 812);
    glVertex2f(343.3961603576644, 810.802581006548);
    glVertex2f(342.5792145092012, 810.0196750625443);
    glVertex2f(342.2047800995322, 808.9984927519652);
    glVertex2f(342.409017457438, 807.704995158565);
    glVertex2f(343.532317999075, 807.3305616446861);
    glVertex2f(344, 806);
    glVertex2f(343.4982785887223, 805.4924334856438);
    glVertex2f(342.3409386367327, 805.5264728959963);
    glVertex2f(341.5920716089748, 805.6285911270543);
    glVertex2f(341.1155198640379, 805.1520393821174);
    glVertex2f(340.8772439915695, 804.1308570715383);
    glVertex2f(341.5580321986221, 803.2117929920172);
    glVertex2f(342.3749780470854, 801.8161771657592);
    glVertex2f(342.7153721506117, 800.7269160362748);
    glVertex2f(342.783450971317, 799.1270637497009);
    glVertex2f(342.3749780470854, 798.0378026184167);
    glVertex2f(341.5580321986221, 797.254896180306);
    glVertex2f(340.638968119101, 796.3017926904323);
    glVertex2f(339.6518252188746, 795.9954379972586);
    glVertex2f(337.745618239127, 796.0635168179638);
    glVertex2f(336.3159630043164, 796.9825808974849);
    glVertex2f(335.0905442316215, 798.5824331840588);
    glVertex2f(334.9884260005636, 801.2375071915643);
    glVertex2f(336.2819235939637, 803.3139112230751);
    glVertex2f(337.6775394184218, 803.688344736954);
    glVertex2f(338.3923670358271, 805.0499211510595);
    glVertex2f(338, 806);
    glVertex2f(336.9627180180164, 806.5816946169281);
    glVertex2f(336.0776871318479, 806.6497734376334);
    glVertex2f(335.6692142076163, 807.8411527997756);
    glVertex2f(337.1329088527796, 808.3177045449124);
    glVertex2f(338.0489684000722, 808.6151148966998);
    glVertex2f(338.3100914456186, 809.7640562971037);
    glVertex2f(338.2056422274001, 810.6344664489249);
    glVertex2f(337.5963551211252, 811.870448864511);
    glVertex2f(337.3178238725425, 813.1586558892063);
    glVertex2f(337.4919059029067, 814.3250054926467);
    glEnd();

//plan wheel white

    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex2f(336.8122129534775, 800.5255726779957);
    glVertex2f(337.4929874201864, 801.6223759854711);
    glVertex2f(338.5141491202496, 801.9627632188254);
    glVertex2f(339.667683633284, 801.6791071910301);
    glVertex2f(340.6510245296412, 800.5444830798488);
    glVertex2f(340.5942933240822, 799.3720381649613);
    glVertex2f(339.9324292592264, 798.313055661192);
    glVertex2f(338.778894746192, 797.9348476241315);
    glVertex2f(337.6064498313045, 798.275234857486);
    glVertex2f(336.7933025516245, 799.3153069594023);
    glEnd();

//plan ar picone design

    glBegin(GL_QUADS);
    glColor3f(1,1,0);
    glVertex2f(640.3649788405372,840.7855787308916);
    glVertex2f(686.9455544805999,834.38813147375);
    glVertex2f(686.2316219576372,831.3539182511589);
    glVertex2f(637.7734519615494,838.2255187846741);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(1,0,0);
    glVertex2f(635.6598021060104,835.8485659284743);
    glVertex2f(684.8617517680204,828.3083290607669);
    glVertex2f(682.7291595226083,823.5861605173542);
    glVertex2f(630.5568135187741,831.5833814376499);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.710, 0.188, 0.176);
    glVertex2f(630.8594615936017, 826.9349535027229);
    glVertex2f(641.6609028365986, 826.2425534230437);
    glVertex2f(659.820141577471, 823.9399205999241);
    glVertex2f(681.6420157165726, 820.1990278903638);
    glVertex2f(676.7933652847228, 809.9534956313147);
    glVertex2f(672.7821916359841, 811.1896445946402);
    glVertex2f(660.943810409088, 813.3987205173624);
    glVertex2f(655.902585867491, 814.2483651030249);
    glVertex2f(650, 815);
    glVertex2f(642.3082724968925, 816.6840129152571);
    glVertex2f(633.5852547507585, 818.1000872246943);
    glVertex2f(626.1083823969294, 819.2329466722442);
    glVertex2f(623.2762337780543, 819.3462326169994);
    glVertex2f(621.1052229921038, 819.456087486666);
    glVertex2f(620.9433013020465, 820.8433741479075);
    glEnd();


//plan ar lag

    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex2f(638.0241243163877, 805.5777660223786);
    glVertex2f(650.8906284061493, 805.5777660223786);
    glVertex2f(662.7619332845481, 805.2934233905606);
    glVertex2f(675, 805);
    glVertex2f(684.3719733027114, 804.2271385212433);
    glVertex2f(691.0540251504328, 803.3741106257895);
    glVertex2f(699.5132184470164, 802.5210827303357);
    glVertex2f(703.0675013447407, 802.1656544405632);
    glVertex2f(704.8446427936027, 801.3126265451094);
    glVertex2f(705, 800);
    glVertex2f(705.0578997674662, 798.6824572007934);
    glVertex2f(703.6361866083765, 798.2559432530664);
    glVertex2f(700.8638459481516, 797.9716006212485);
    glVertex2f(695.1769933117929, 797.4740010155671);
    glVertex2f(688.8503697538438, 796.905317519312);
    glVertex2f(683.0213458015761, 796.1233735144318);
    glVertex2f(678.5429493504436, 796.2655448303408);
    glVertex2f(674.9175807947675, 796.905317519312);
    glVertex2f(666.5294731561359, 797.8294290353395);
    glEnd();




// plan wind design

    glBegin(GL_POLYGON);
    glColor3f(0.671, 0.671, 0.671);
    glVertex2f(441.4216157849391, 809.3729542745134);
    glVertex2f(441.4809973398804, 802.8409832309706);
    glVertex2f(442.609246883765, 799.8719054839056);
    glVertex2f(448.3692577130708, 797.6747879510776);
    glVertex2f(453.357038231897, 796.7246830720169);
    glVertex2f(459.117319574454, 795.7151966380147);
    glVertex2f(462.8583571187471, 794.9432364237779);
    glVertex2f(470.874867035822, 795.2995257534257);
    glVertex2f(474.1408525575934, 796.8434461818995);
    glVertex2f(477.4068380793646, 798.3279850554319);
    glVertex2f(474.2596156674759, 799.9906685937882);
    glVertex2f(469.9814437117026, 800.9407734728491);
    glVertex2f(465.1148562065163, 802.0096414617924);
    glVertex2f(460.1861871463887, 803.2566541155596);
    glVertex2f(455, 805);
    glVertex2f(450.4476121360161, 806.8789289669788);
    glVertex2f(444.9251275264756, 808.7197571701591);
    glEnd();



    glBegin(GL_POLYGON);
    glColor3f(1,0,0);
    glVertex2f(506.1250070054209, 799.8630725585685);
    glVertex2f(510.3203529302554, 803.8520899952966);
    glVertex2f(514.3781465296854, 808.6664213844512);
    glVertex2f(517.5418500139868, 811.7613487060505);
    glVertex2f(521.1182104745014, 815.1313806784586);
    glVertex2f(521.5996436134169, 809.2854068648771);
    glVertex2f(521.0494343117992, 804.47107455496165);
    glVertex2f(520.292896522075, 800.9634911618039);
    glVertex2f(519.8802395458619, 797.5246830266935);
    glVertex2f(519.0549255934353, 795.3238458202228);
    glVertex2f(518.2983878037111, 794.360979542392);
    glVertex2f(514.7220273431965, 794.2922033796987);
    glVertex2f(511.2832192080862, 794.6360841932008);
    glVertex2f(508.1195157237848, 794.9799650067118);
    glVertex2f(505, 795);
    glVertex2f(500.7604663146489, 796.4242644234582);
    glVertex2f(503.8274323375493, 798.2627341295972);
    glEnd();



//plan window

    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(589.8033906326415,810.6707898109263);
    glVertex2f(592.5921566325294,810.22259527523);
    glVertex2f(592.5921566325294,806.2386438468186);
    glVertex2f(589.3551960969452,806.5374402039494);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(584.0618460145364,811.6837635074519);
    glVertex2f(586.4398635338207,811.392577688764);
    glVertex2f(586.3913325640393,807.1218523480085);
    glVertex2f(583.7585944265667,807.4338241309542);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(578.3093671158161,812.3278154723203);
    glVertex2f(580.6478339415123,812.0280120331284);
    glVertex2f(580.1381680948863,807.620901477008);
    glVertex2f(577.6198192056751,808.1905280114731);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(572.0462336798289,813.5247139542698);
    glVertex2f(574.8203045596122,813.225967859524);
    glVertex2f(574.6069144919364,808.6594204112653);
    glVertex2f(571.6621315580127,808.7447764383355);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(566,814);
    glVertex2f(568.5046634593994,813.7112862802352);
    glVertex2f(568.2838595102392,810.0312204609);
    glVertex2f(565.6342121203179,810.2520244100601);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(560.3349173404754,814.9257080006158);
    glVertex2f(562.8373620976232,814.7785053678424);
    glVertex2f(562.395754199303,810.8040342829604);
    glVertex2f(559.9669107585419,810.9880375739272);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(554.2944453146142,815.9242985774034);
    glVertex2f(556.9281298652776,815.7693759567762);
    glVertex2f(556.6182846240231,811.7413878204674);
    glVertex2f(554,812);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(548.4073857307784,816.7376423356966);
    glVertex2f(550.57630241956,816.4665277495989);
    glVertex2f(550.3439184886191,812.2061556823492);
    glVertex2f(547.9813485240534,812.7096541993877);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(541.8231743541199,817.705908714617);
    glVertex2f(544.6892428357243,817.5509860939896);
    glVertex2f(544.5730508702537,813.1744220612695);
    glVertex2f(541.5907904231791,813.484267302524);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(535.437931660551,818.1921337221296);
    glVertex2f(538.4253162382882,817.9120664179668);
    glVertex2f(535.5935246073082,814.1778356957952);
    glVertex2f(538.4564348276397,813.8977683916323);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(530.1166528814567,819.1256914026725);
    glVertex2f(532.9484445124367,818.8767426878611);
    glVertex2f(532.9484445124367,814.1778356957952);
    glVertex2f(529.6809926305367,814.3645472319038);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(511.6332298370522, 821.627082548115);
    glVertex2f(514.5893818702485, 821.285988175054);
    glVertex2f(514.5325320080716, 817.2497047604974);
    glVertex2f(511.1215882774606, 817.761346320089);
    glVertex2f(505.4935311219523, 822.6503656672984);
    glEnd();

    glPopMatrix();

}



void update2(int value)
 {
    // Move clouds to the right
    cloud1X2 += 2.0f;
    cloud2X2 += 1.0f;


    if (cloud1X2 > 1300){

        cloud1X2 = -200;
    }
    if (cloud2X2 > 1300){

        cloud2X2 = -200;
    }

     if (isLanding2) {
        plane2();
    }


    glutPostRedisplay();
    glutTimerFunc(30, update2, 0);
}






void drawLampPost(int x, int y) {
    // lamp post bar

       if (isNightMode2) {
        glColor3f(0.2f, 0.2f, 0.2f); // Darker pole for night mode
    } else {
        glColor3f(0.5f, 0.25f, 0.1f); // Original color for day mode
    }
    glBegin(GL_QUADS);
    glVertex2i(x - 5, y);
    glVertex2i(x + 5, y);
    glVertex2i(x + 5, y + 100);
    glVertex2i(x - 5, y + 100);
    glEnd();

    //lamp post light
     if (isNightMode2) {


         glColor3f(1.0f, 1.0f, 0.0f);  // night color
}
    else{
        glColor3f(1.0f, 1.0f, 1.0f); // white light day
}

    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(x + cos(angle) * 15, y + 100 + sin(angle) * 15);
    }
    glEnd();
}




void drawTree(int x, int y) {

    glColor3f(0.4f, 0.2f, 0.0f); //tree
    glBegin(GL_QUADS);
    glVertex2i(x - 10, y);
    glVertex2i(x + 10, y);
    glVertex2i(x + 10, y + 60);
    glVertex2i(x - 10, y + 60);
    glEnd();

    if (isNightMode2){
        glColor3f(0.0f, 0.25f, 0.10f);
    }
        else{
    glColor3f(0.0f, 0.5f, 0.0f); // First circle
        }

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(x + cos(angle) * 30, y + 60 + sin(angle) * 30);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN); // Middle circle
    for (int i = 0; i <= 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(x + cos(angle) * 25, y + 90 + sin(angle) * 25);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN); // Last circle
    for (int i = 0; i <= 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(x + cos(angle) * 20, y + 115 + sin(angle) * 20);
    }
    glEnd();
}



void drawCloud_s(int x, int y) {


        if (isNightMode2) {
        glColor3f(0.3f, 0.3f, 0.3f); // Night sky cloud

    }
        else {
        glColor3f(1.0f, 1.f, 1.0f); // Day sky cloud

    }

    glBegin(GL_TRIANGLE_FAN); // First circle
    for (int i = 0; i <= 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(x + cos(angle) * 50, y + sin(angle) * 50);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN); // Second circle
    for (int i = 0; i <= 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(x - 30 + cos(angle) * 40, y + 10 + sin(angle) * 40);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN); // Third circle
    for (int i = 0; i <= 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(x + 30 + cos(angle) * 40, y + 10 + sin(angle) * 40);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN); // Fourth circle
    for (int i = 0; i <= 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(x + cos(angle) * 45, y - 20 + sin(angle) * 35);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN); // Fifth circle
    for (int i = 0; i <= 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(-70 + x + cos(angle) * 45, y - 20 + sin(angle) * 35);
    }
    glEnd();


}



void drawSun(int x, int y, int radius) {

     if (isNightMode2) {
        glColor3f(0.05f, 0.05f, 0.2f); //sun color will be night key color

    }
    else if (isRaining2) {
        glColor3f(0.3f, 0.4f, 0.5f); //sun color will be night key color

    }
        else {
        glColor3f(1.0f, 1.0f, 0.0f); // Yellow color for the sun

    }


    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}


void drawMoon(int x, int y, int radius) {
    glColor3f(0.8f, 0.8f, 0.8f); // Light gray

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}


void drawsky(){

    glBegin(GL_QUADS); // sky
    if(isRaining2){

            glColor3f(0.3f, 0.4f, 0.5f); // rainly sky
    }
    else {
            glColor3f(0.6f, 0.85f, 1.0f);

    }

    glVertex2i(0, 500);
    glVertex2i(1200, 500);
    glVertex2i(1200, 1000);
    glVertex2i(0, 1000);
    glEnd();

}

void nightsky(){

    glBegin(GL_QUADS); // sky
    glColor3f(0.05f, 0.05f, 0.2f);
    glVertex2i(0, 500);
    glVertex2i(1200, 500);
    glVertex2i(1200, 1000);
    glVertex2i(0, 1000);
    glEnd();
    }

void nightmode(){



        drawCloud_s(cloud1X2, 850);
        drawCloud_s(cloud2X2, 900);
        nightsky();
        drawMoon(200, 920, 50);
        drawSun(1000, 850, 50);

}



void drawScene() {

    glClear(GL_COLOR_BUFFER_BIT);


    drawsky();

     if (isNightMode2) {
        nightmode();
    }


    glBegin(GL_POLYGON); // Runway below
    glColor3f(0.6f, 0.6f, 0.6f);
    glVertex2i(200,350);
    glVertex2i(400,350);
    glVertex2i(110,0);
    glVertex2i(0,0);
    glVertex2i(0,150);
    glEnd();



    glBegin(GL_POLYGON); // yellow line quad
    glColor3f(0.9f, 0.7f, 0.0f);
    glVertex2i(0,15);
    glVertex2i(0,0);
    glVertex2i(20,0);
    glVertex2i(280,350);
    glVertex2i(260,350);
    glEnd();


    glBegin(GL_QUADS); // dark grass


    if(isNightMode2){

        glColor3f(0.0f, 0.40f, 0.15f); // Dark green for night mode
    }
    else{

        glColor3f(0.0f, 0.4f, 0.0f); // Bright green for day mode
    }

    glVertex2i(110, 0);
    glVertex2i(1200, 0);
    glVertex2i(1200, 550);
    glVertex2i(500, 550);
    glEnd();


    glBegin(GL_QUADS); // light grass

     if(isNightMode2){

        glColor3f(0.0f, 0.25f, 0.10f); // Darker green for night mode
    }
    else{

       glColor3f(0.0f, 0.50f, 0.20f); // Bright green for day mode
    }


    glVertex2i(110, 0);
    glVertex2i(250, 0);
    glVertex2i(550, 550);
    glVertex2i(500, 550);
    glEnd();





    glBegin(GL_QUADS); // runway
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2i(0, 270);
    glVertex2i(1200, 270);
    glVertex2i(1200, 466);
    glVertex2i(0, 466);
    glEnd();

    glBegin(GL_TRIANGLES);

    if(isNightMode2){

        glColor3f(0.0f, 0.25f, 0.10f); // Darker green for night mode
    }
    else{

        glColor3f(0.0f, 0.50f, 0.20f);

    }// Left grass

    glVertex2i(0,270);
    glVertex2i(120,270);
    glVertex2i(0,140);
    glEnd();


    // Yellow ash color side runway (Below)

    bool f= true;

     for(int i = 0; i<=1200; i= i+50){


       if (f) {


                glColor3f(0.9f, 0.7f, 0.0f);
                f = !f;
            }
            else {

                glColor3f(0.75f, 0.75f, 0.75f);
                f = !f;

            }

            glBegin(GL_QUADS);

            glVertex2i(i,255);
            glVertex2i(i-60, 255);
            glVertex2i(i-40, 270);
            glVertex2i(i+20, 270);
            glEnd();

        }


    glBegin(GL_QUADS); // light color side runway (up)
    glColor3f(0.75f, 0.75f, 0.75f);
    glVertex2i(0, 466);
    glVertex2i(1200, 466);
    glVertex2i(1200, 458);
    glVertex2i(0, 458);
    glEnd();


    // white color runway

     bool x= true;

     for(int i = 10; i<=1200; i= i+40){


       if (x) {

                glColor3f(1.0f, 1.0f, 1.0f);
                x = !x;
            }
            else {

                glColor3f(0.5f, 0.5f, 0.5f);
                x = !x;

            }

            glBegin(GL_QUADS);
            glVertex2i(i, 378);       // 441 - 15
            glVertex2i(i + 50, 378);   // 441 - 15
            glVertex2i(i + 50, 385);   // 431 - 15
            glVertex2i(i, 385);        // 431 - 15
            glEnd();

        }


    glBegin(GL_QUADS); // atc building
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2i(210,500);
    glVertex2i(290,500);
    glVertex2i(290,700);
    glVertex2i(210,700);
    glEnd();


    drawSun(1000, 850, 50);

    drawCloud(cloud1X2, 850);
    drawCloud(cloud2X2, 900);



    glBegin(GL_QUADS); // atc building glass
    glColor3f(0.4f, 0.6f, 0.8f);
    glVertex2i(210,700);
    glVertex2i(290,700);
    glVertex2i(320,750);
    glVertex2i(180,750);
    glEnd();


    glBegin(GL_QUADS); // atc building
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2i(180,750);
    glVertex2i(320,750);
    glVertex2i(320,770);
    glVertex2i(180,770);
    glEnd();


    glBegin(GL_QUADS);  // Building
    glColor3f(0.4f, 0.6f, 0.8f);
    glVertex2i(0,490);
    glVertex2i(500,490);
    glVertex2i(500,640);
    glVertex2i(0,640);
    glEnd();


    glBegin(GL_QUADS);  // Building front
    glColor3f(0.85f, 0.68f, 0.40f);
    glVertex2i(0,466);
    glVertex2i(515,466);
    glVertex2i(500,500);
    glVertex2i(0,500);
    glEnd();



    glBegin(GL_QUADS); //building door
    glColor3f(0.6f, 0.8f, 0.9f);
    glVertex2i(220,500);
    glVertex2i(280,500);
    glVertex2i(280,520);
    glVertex2i(220,520);
    glEnd();


    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(0.5f, 0.5f, 0.5);

    glVertex2f(249,500);
    glVertex2f(249,520);

    glVertex2f(279,500);
    glVertex2f(279,520);

    glVertex2f(219,500);
    glVertex2f(219,520);

    glVertex2f(0,500);
    glVertex2f(500,500);

    glVertex2f(219,520);
    glVertex2f(279,520);

    glVertex2f(500,500);
    glVertex2f(500,640);

    glVertex2f(0,535);
    glVertex2f(500,535);

    glVertex2f(0,570);
    glVertex2f(500,570);

    glVertex2f(0,605);
    glVertex2f(500,605);

    glVertex2f(0,640);
    glVertex2f(500,640);

    glVertex2i(210,700);
    glVertex2i(290,700);


    glVertex2i(290,700);
    glVertex2i(320,750);


    glVertex2i(320,750);
    glVertex2i(180,750);


    glVertex2i(180,750);
    glVertex2i(210,700);

    glVertex2i(180,750);
    glVertex2i(320,750);

    glVertex2i(180,750);
    glVertex2i(180,770);

    glVertex2i(320,750);
    glVertex2i(320,770);

    glVertex2i(320,770);
    glVertex2i(180,770);

    glEnd();




    glBegin(GL_QUADS); //building right side
    glColor3f(0.4f, 0.6f, 0.8f);

    glVertex2i(800,500);
    glVertex2i(1200,500);
    glVertex2i(1200,700);
    glVertex2i(800,700);
    glEnd();


    glBegin(GL_QUADS); //right building door
    glColor3f(0.6f, 0.8f, 0.9f);
    glVertex2i(820,500);
    glVertex2i(880,500);
    glVertex2i(880,530);
    glVertex2i(820,530);
    glEnd();



    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(0.5f, 0.5f, 0.5);


    glVertex2i(800,500);
    glVertex2f(1200, 500);

    glVertex2f(800, 540);
    glVertex2f(1200, 540);

    glVertex2f(800, 580);
    glVertex2f(1200, 580);

    glVertex2f(800, 620);
    glVertex2f(1200, 620);

    glVertex2f(800, 660);
    glVertex2f(1200, 660);

    glVertex2f(800, 700);
    glVertex2f(1200,700);




    glVertex2i(800,500);
    glVertex2f(800,700);

    glVertex2i(900,500);
    glVertex2f(900,700);

    glVertex2i(1000,500);
    glVertex2f(1000,700);

    glVertex2i(1100,500);
    glVertex2f(1100,700);

    glVertex2i(1200,500);
    glVertex2f(1200,700);



    //door

    glVertex2i(820,500);
    glVertex2i(820,530);

    glVertex2i(850,500);
    glVertex2i(850,530);

    glVertex2i(880,500);
    glVertex2i(880,530);

    glVertex2i(880,530);
    glVertex2i(820,530);

    glEnd();


    glBegin(GL_QUADS);  //Right Building front
    glColor3f(0.85f, 0.68f, 0.40f);
    glVertex2f(800, 500);
    glVertex2i(1200,500);
    glVertex2i(1200,466);
    glVertex2i(785,466);
    glEnd();



    drawTree(520, 475);
    drawTree(310, 472);
    drawTree(760, 500);

    drawLampPost(200, 475);
    drawLampPost(600, 500);
    drawLampPost(910, 480);
    drawLampPost(910, 200);

    plane2();
    drawRain2();




    glFlush();


}

void keyboard_s(unsigned char key, int x, int y) {
    switch (key) {
        case 'n':
                   // Night mode
            isNightMode2 = true;
            glutPostRedisplay();
            break;

        case 'd':                // Day mode
            isNightMode2 = false;
            glutPostRedisplay();
            break;


        case 'l':
        case 'L': // Press 'L' to start landing
             if (!isLanding2 && !isTakeOff2) {
                isLanding2 = true;
                planex2 = 1200;  // Reset position for re-landing
                planey = 600;}
            break;



        case 't':
        case 'T': // Press 'T' to take off
            if (!isTakeOff2 && !isLanding2) {
                isTakeOff2 = true;
                isLanding2 = false;
                planex2 = -800;
                planey = 200;

            }
            break;

        case 'r':
        case 'R': // Toggle rain
        isRaining2 = !isRaining2;
            break;


        case '27':                // Exit mode
            exit(0);
            break;
        default:
              glutKeyboardFunc(keyboard);
    }
}

void mouseClick_s(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            isRaining2 = !isRaining2; }



            }


        }










void keyboard(unsigned char key, int x, int y) {
    switch (key) {
         case 'd': // Switch to day
            isDay = true;
            isNight = false;
            break;
        case 'n': // Switch to night
            isDay = false;
            isNight = true;
            break;
        case's':
            if(isDay){
             paused = !paused;         // Toggle state
            if (paused) {
                savebusMove = busMove;

            } else {
                busMove = savebusMove;}}
            if(!isDay){
             carpaused = !carpaused;         // Toggle state
            if (carpaused) {
                savecarMove = carMove;

            } else {
                carMove = savecarMove;}}
                break;
                 case 'a':
                if(isDay)
             carMove+=2.5;
            glutPostRedisplay();

            break;
             case 'b':
                if(!isDay)
             busMove+=2.5;
            glutPostRedisplay();

            break;
            case 'p':
                if(isDay)
              planeMovex+=2.4f;
            planeMovey+=2.9f;
            glutPostRedisplay();


            break;
            case 'q':
                if(!isDay)
              landingMovex+=2.4f;
                landingMovey-=2.9f;
            glutPostRedisplay();

            break;
        case '1':
                glutDisplayFunc(display_r);
                glutKeyboardFunc(keyboard_r);
                glutMouseFunc(mouse_r);
                //glutTimerFunc(20, update_r, 0);
           break;

           case'2':
             glutDisplayFunc(display1);
    glutKeyboardFunc(handleKeypress1);
    glutMouseFunc(mouseClick1);

    glutTimerFunc(0, timer1, 0);
   glutTimerFunc(50, timer, 0);
    glutTimerFunc(50,liftmovement1,0);
    glutTimerFunc(0, movePlane1, 0);
    glutTimerFunc(100, updateTextColorIntensity1, 0);

    glutPostRedisplay();

            break;
     case'3':
          glutDisplayFunc(display_m);
    glutKeyboardFunc(handleKeypress);
    glutMouseFunc(mouseClick);
    glutTimerFunc(0, timer_m, 0);
    glutTimerFunc(30, update_Rain, 0); // Start rain animation
    glutTimerFunc(80, updatePlane, 0);
    glutTimerFunc(0, updateMoon, 0);

    glutPostRedisplay();

     break;
case'4':

        glutDisplayFunc(drawScene);
        glutKeyboardFunc(keyboard_s);
        glutMouseFunc(mouseClick_s);
        glutTimerFunc(0, update2, 0);
        glutTimerFunc(30, updateRain2, 0);
        if (key == 'n') {
    // Night mode

break;
 glutPostRedisplay();
      }

    glutPostRedisplay();}}

/* Main function */
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1200,1000);
    glutInitWindowPosition(80, 50);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
       glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glutCreateWindow("Airport");
    init();
     initializeRain();
    glutDisplayFunc(display_r);
     glutKeyboardFunc(keyboard);
     glutMouseFunc(mouse_r);
    glutTimerFunc(20, update_r, 0); // Add a timer
    glutMainLoop();

    return 0;
}

