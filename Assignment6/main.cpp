#include<GL/glut.h>

void display();
void reshape(int w, int h);
void update(int);
void drawSun();
void drawMountain();

float bgR=0, bgG=0, bgB=0;
float sunR=0, sunG=0, sunB=0;
float sunX=-0.6f, sunY=-0.3f, sunZ=-1.4f;
float mGreen = 0;

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowPosition(500, 200);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Sun Rise and Sunset");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(1000 / 60, update, 0);
    glutMainLoop();
    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(bgR, bgG, bgB, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    drawSun();
    drawMountain();
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, w / h, 1.0, 100.0);
}

void update(int) {
    if (sunX < 0) {
        sunY += 0.0005;
        sunR += 0.0015;
        sunG += 0.0005;
        bgB += 0.001;
        mGreen += 0.001;
    }
    else {
        sunY -= 0.0005;
        sunR -= 0.0015;
        sunG -= 0.0005;
        bgB -= 0.001;
        mGreen -= 0.001;
    }

    sunX += 0.0005;
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, update, 0);
}

void drawSun() {
    glColor3f(sunR, sunG, sunB);
    glTranslatef(sunX, sunY, sunZ);
    glutSolidSphere(0.1, 30, 30);
}

void drawMountain() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBegin(GL_TRIANGLES);
    glColor3f(0, mGreen, 0);
    glVertex3f(-1.0, -1.0, -1.2f);
    glVertex3f(1.0, -1.0, -1.2f);
    glVertex3f(0.2, 0.02, -1.2f);
    glEnd();
}