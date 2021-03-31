#include <stdio.h>
#include <GLUT/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define WIN_LEFT -2
#define WIN_RIGHT 2
#define WIN_BOTTOM -2
#define WIN_TOP 2
#define WIN_NEAR -2
#define WIN_FAR 2

#define FLIP 15.0//the frequency of flipping wings

static GLfloat posX=0, posY=0, posZ=0;//for jumping
static GLboolean fly_state = GL_TRUE;//for flying
static GLfloat theta_wing = 0.0;//for flying
static GLint flip_direction = 1;//for flyingstatic
static GLboolean move_state = GL_TRUE;//for moving

static GLfloat movementX = 0.01;
static GLfloat movementY = 0.01;
static GLfloat movementZ = 0.01;


//material
typedef struct materialStruct{
    
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;
    GLfloat emission[4];
    
} materialStruct;

//male
materialStruct malebody={
    
    {0.0f, 0.5f, 0.5f, 1.0f},
    {0.5f, 0.5f, 0.5f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0.0f,
    {0.0f, 0.0f, 0.0f, 1.0f}
    
};
materialStruct malehead={
    
    {1.0f,0.8f, 0.1f, 1.0f},
    {0.5f, 0.5f, 0.5f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    100.0f,
    {0.3f, 0.2f, 0.2f, 0.0f}
    
};
materialStruct maleleg={
    
    {0.0f, 0.0f, 0.0f, 1.0f},
    {0.5f, 0.5f, 0.5f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0.0f,
    {0.0f, 0.0f, 0.0f, 1.0f}
    
};
materialStruct maleeye={
    
    {0.0f, 0.0f, 0.0f, 1.0f},
    {0.5f, 0.5f, 0.5f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    100.0f,
    {0.0f, 0.0f, 0.0f, 1.0f}
    
};
materialStruct malewing={
    
    {0.0f,0.6f, 0.0f, 1.0f},
    {0.5f, 0.5f, 0.5f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0.0f,
    {0.0f, 0.0f, 0.0f, 1.0f}
    
};
materialStruct malebeak={
    
    {1.0f,0.1f, 0.1f, 1.0f},
    {0.5f, 0.5f, 0.5f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0.0f,
    {0.3f, 0.2f, 0.2f, 0.0f}
    
};
materialStruct maletail={
    
    {0.0f,0.1f, 0.9f, 1.0f},
    {0.5f, 0.5f, 0.5f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0.0f,
    {0.0f, 0.0f, 0.0f, 1.0f}
    
};

//female
materialStruct femalebody={
    
    {0.5f, 0.5f, 0.5f, 1.0f},
    {0.5f, 0.5f, 0.5f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0.0f,
    {0.0f, 0.0f, 0.0f, 1.0f}
    
};
materialStruct femalehead={
    
    {0.9f,0.5f, 0.0f, 1.0f},
    {0.5f, 0.5f, 0.5f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0.0f,
    {0.3f, 0.2f, 0.2f, 0.0f}
    
};
materialStruct femaleleg={
    
    {0.0f, 0.0f, 0.0f, 1.0f},
    {0.5f, 0.5f, 0.5f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0.0f,
    {0.0f, 0.0f, 0.0f, 1.0f}
    
};
materialStruct femaleeye={
    
    {0.0f, 0.0f, 0.0f, 1.0f},
    {0.5f, 0.5f, 0.5f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    100.0f,
    {0.0f, 0.0f, 0.0f, 1.0f}

    
};
materialStruct femalewing={
    
    {1.0f,0.6f, 0.0f, 1.0f},
    {0.5f, 0.5f, 0.5f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0.0f,
    {0.0f, 0.0f, 0.0f, 1.0f}
    
};
materialStruct femalebeak={
    
    {0.0f,0.1f, 0.1f, 1.0f},
    {0.5f, 0.5f, 0.5f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0.0f,
    {0.3f, 0.2f, 0.2f, 0.0f}
    
};
materialStruct femaletail={
    
    {1.0f,0.9f, 0.9f, 1.0f},
    {0.5f, 0.5f, 0.5f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0.0f,
    {0.0f, 0.0f, 0.0f, 1.0f}
    
};

//baby
materialStruct babybody={
    
    {0.9f, 0.9f, 0.6f, 1.0f},
    {0.5f, 0.5f, 0.5f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0.0f,
    {0.0f, 0.0f, 0.0f, 1.0f}
    
};
materialStruct babyhead={
    
    {0.9f,0.7f, 0.6f, 1.0f},
    {0.5f, 0.5f, 0.5f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0.0f,
    {0.3f, 0.2f, 0.2f, 0.0f}
    
};
materialStruct babyleg={
    
    {0.0f, 0.0f, 0.0f, 1.0f},
    {0.5f, 0.5f, 0.5f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0.0f,
    {0.0f, 0.0f, 0.0f, 1.0f}
    
};
materialStruct babyeye={
    
    {0.0f, 0.0f, 0.0f, 1.0f},
    {0.5f, 0.5f, 0.5f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    100.0f,
    {0.0f, 0.0f, 0.0f, 1.0f}

};
materialStruct babywing={
    
    {1.0f,0.9f, 0.8f, 1.0f},
    {0.5f, 0.5f, 0.5f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0.0f,
    {0.0f, 0.0f, 0.0f, 1.0f}
    
};
materialStruct babybeak={
    
    {0.9f,0.4f, 0.1f, 1.0f},
    {0.5f, 0.5f, 0.5f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0.0f,
    {0.3f, 0.2f, 0.2f, 0.0f}
    
};
materialStruct babytail={
    
    {0.3f,0.9f, 0.9f, 1.0f},
    {0.5f, 0.5f, 0.5f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0.0f,
    {0.0f, 0.0f, 0.0f, 1.0f}
    
};

//material of each part
materialStruct *material_body;
materialStruct *material_head;
materialStruct *material_leg;
materialStruct *material_eye;
materialStruct *material_wing;
materialStruct *material_beak;
materialStruct *material_tail;

//struct of material
void chooseMaterial(materialStruct *material){
    glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &material->shininess);
    glMaterialfv(GL_FRONT, GL_SHININESS, material->emission);
    return;
}

//lighting
typedef struct lightingStruct {
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat light_position[4];
} lightingStruct;

lightingStruct whiteLighting={
   
    {0.4, 0.3, 0.2, 1.0},
    {1.0, 0.9, 0.8, 1.0},
    {0.0, 0.9, 0.8, 1.0},
    {1.0, 1.0, 1.0, 0.0}

};
lightingStruct noonLighting={
  
    {0.6, 0.5, 0.4, 1.0},
    {1.0, 0.9, 0.8, 1.0},
    {1.0, 0.7, 0.5, 1.0},
    {0.0, 1.0, 0.0, 0.0}

};
lightingStruct earlyEveningLighting={
 
    {0.3, 0.3, 0.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {-3.0, 0.1, 1.0, 0.0}

};
lightingStruct lateEveningLighting={
    
    {0.0, 0.0, 0.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {3.0, 0.0, -1.0, 0.0}
    
};

//struct of lighting
lightingStruct *currentLighting;

void head(){//modelling of the head of the hummingbird
    
    GLUquadricObj *head; // pointer to quadric object
    head = gluNewQuadric(); // initialisation
    chooseMaterial(material_head);
    glColor3f(1.0f, 0.5f, 0.3f);
    gluSphere(head, 0.2f, 50, 50);
    
}

void body(){//modelling of the body of the hummingbird
    
    GLUquadricObj *body;
    body = gluNewQuadric();
    chooseMaterial(material_body);
    glColor3f(0.0f, 0.5f, 0.5f);
    gluSphere(body, 0.3f, 50, 50);
    
}

void wingleft(){//modelling of the left wing of the hummingbird
    
    GLUquadricObj *wingleft;
    wingleft = gluNewQuadric();
    chooseMaterial(material_wing);
    glColor3f(0.2f, 0.5f, 0.2f);
    gluCylinder(wingleft, 0.13, 0.03, 0.5, 8, 32);
    
}

void wingright(){//modelling of the right wing of the hummingbird
    
    GLUquadricObj *wingright;
    wingright = gluNewQuadric();
    chooseMaterial(material_wing);
    glColor3f(0.2f, 0.5f, 0.2f);
    gluCylinder(wingright, 0.13, 0.03, 0.5, 8, 32);
    
}

void tail(){//modelling of the tail of the hummingbird
    
    GLUquadricObj *tail;
    tail = gluNewQuadric();
    chooseMaterial(material_tail);
    glColor3f(0.2f, 0.5f, 0.8f);
    gluCylinder(tail, 0.15, 0.05, 0.1, 8, 32);
    
}

void eyeleft(){//modelling of the left eye of the hummingbird
    
    chooseMaterial(material_eye);
    glColor3f(0.0f, 0.0f, 0.0f);
    glutSolidSphere(0.05f, 50, 50);
    
}

void eyeright(){//modelling of the right eye of the hummingbird
    
    chooseMaterial(material_eye);
    glColor3f(0.0f, 0.0f, 0.0f);
    glutSolidSphere(0.05f, 50, 50);
    
}

void beak(){//modelling of the beak of the hummingbird
    
    GLUquadricObj *beak;
    beak = gluNewQuadric();
    chooseMaterial(material_beak);
    glColor3f(0.7f, 0.2f, 0.1f);
    gluCylinder(beak, 0.03, 0.01, 0.3, 32, 32);
    
}

void legleft(){//modelling of the left leg of the hummingbird
    
    GLUquadricObj *legleft;
    legleft = gluNewQuadric();
    chooseMaterial(material_leg);
    glColor3f(0.0f, 0.0f, 0.0f);
    gluCylinder(legleft, 0.02, 0.02, 0.1, 32, 32);
    
}

void legright(){//modelling of the right leg of the hummingbird
    
    GLUquadricObj *legright;
    legright = gluNewQuadric();
    chooseMaterial(material_leg);
    glColor3f(0.0f, 0.0f, 0.0f);
    gluCylinder(legright, 0.02, 0.02, 0.1, 32, 32);
    
}

void animal(){
    
    //call all the parts of the whole body
    //do the rotating, translating and scaling
    glPushMatrix();
    glTranslatef(0.2f, 0.12f, 0.0f);
    head();
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(35, 0.0f, 0.0f, 1.0f);
    glScalef(1.2, 0.8, 0.8);
    body();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 0.04f, -0.02f);
    glRotatef(180, 0.0f, 1.0f, 0.0f);
    glRotatef(-30, 0.0f, 0.0f, 1.0f);
    glRotatef(60, -1.0f, 1.0f, 0.0f);
    glRotatef(theta_wing, 1.0, 0.0, 0.0);
    glScalef(2, 0.4, 2);
    wingleft();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 0.04f, 0.02f);
    glRotatef(30, 0.0f, 0.0f, 1.0f);
    glRotatef(60, -1.0f, -1.0f, 0.0f);
    glRotatef(theta_wing, 1.0, 0.0, 0.0);
    glScalef(2, 0.4, 2);
    wingright();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.35f, -0.3f, -0.0f);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    glRotatef(-50, 1.0f, 0.0f, 0.0f);
    glScalef(2, 0.4, 2);
    tail();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.3f, 0.16f, -0.13f);
    eyeleft();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.3f, 0.16f, 0.13f);
    eyeright();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.35f, 0.14f, 0.0f);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    glRotatef(20, 1.0f, 0.0f, 0.0f);
    beak();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.2f, -0.28f, -0.09f);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    glRotatef(-30, 1.0f, 0.0f, 0.0f);
    legleft();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.2f, -0.28f, 0.09f);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    glRotatef(-30, 1.0f, 0.0f, 0.0f);
    legright();
    glPopMatrix();
    
    glutSwapBuffers();
    
}

void myidle(){
    
    //flying
    if (fly_state == GL_TRUE){
        if (flip_direction == 1) {      // flip downwards
            theta_wing += FLIP;
            if (theta_wing >=110.0) {
                flip_direction = -1;    // then flip upwards
            }
        }
        if (flip_direction == -1) {     // flip upwards
            theta_wing -= FLIP;
            if (theta_wing <= 5.0) {
                flip_direction = 1;     // then flip downwards
            }
        }
    }
    
    //moving
    if (move_state == GL_TRUE){
        
        posX += movementX;
        if(posX < -0.1 || posX > 0.1){
            movementX *= -1;
        }
        
        posY += movementY;
        if(posY < -0.2 || posY > 0.2){
            movementY *= -1;
        }
        
        posZ += movementZ;
        if(posZ < -0.2 || posZ > 0.2){
            movementZ *= -1;
        }
        
    }
    
    glutPostRedisplay();
    
}

void mydisplay(){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(-0.2,0.4,0.8,  0.0,0.0,0.0,  0.0,1.0,0.0);
    
    glTranslatef(posX, posY, posZ);
    
    animal();
    
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glFlush();
    
}

void reshape(int w, int h){
    
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if (w<=h)
        glOrtho(WIN_LEFT,WIN_RIGHT,WIN_BOTTOM*(GLfloat)h/(GLfloat)w,WIN_TOP*(GLfloat)h/(GLfloat)w,WIN_NEAR,WIN_FAR);
    else
        glOrtho(WIN_LEFT*(GLfloat)w/(GLfloat)h,WIN_RIGHT*(GLfloat)w/(GLfloat)h,WIN_BOTTOM,WIN_TOP,WIN_NEAR,WIN_FAR);
    
}

void init()//initialization
{
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    currentLighting = &whiteLighting;//set current lighting as the defined white light
    glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting -> ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting -> diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting -> specular);
    glLightfv(GL_LIGHT0, GL_POSITION, currentLighting -> light_position);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    material_head = &malehead;
    material_body = &malebody;
    material_tail = &maletail;
    material_wing = &malewing;
    material_eye = &maleeye;
    material_leg = &maleleg;
    material_beak = &malebeak;
    
}

//set up the menu
void mymenu(int choose){//left button
    
    if (choose == 1){
        
        material_head = &malehead;
        material_body = &malebody;
        material_tail = &maletail;
        material_wing = &malewing;
        material_eye = &maleeye;
        material_leg = &maleleg;
        material_beak = &malebeak;
        return;
        
    }
    else if (choose == 2){
        
        material_head = &femalehead;
        material_body = &femalebody;
        material_tail = &femaletail;
        material_wing = &femalewing;
        material_eye = &femaleeye;
        material_leg = &femaleleg;
        material_beak = &femalebeak;
        return;
        
    }
    else if (choose == 3){
        
        material_head = &babyhead;
        material_body = &babybody;
        material_tail = &babytail;
        material_wing = &babywing;
        material_eye = &babyeye;
        material_leg = &babyleg;
        material_beak = &babybeak;
        return;
        
    }
}

void mymenu2(int light){//right button
    
    if (light == 1){
        
        currentLighting = &noonLighting;
        glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting -> ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting -> diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting -> specular);
        glLightfv(GL_LIGHT0, GL_POSITION, currentLighting -> light_position);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        return;
        
    }
    else if (light == 2){
        
        currentLighting = &earlyEveningLighting;
        glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting -> ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting -> diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting -> specular);
        glLightfv(GL_LIGHT0, GL_POSITION, currentLighting -> light_position);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        return;
        
    }
    else if (light == 3){
        
        currentLighting = &lateEveningLighting;
        glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting -> ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting -> diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting -> specular);
        glLightfv(GL_LIGHT0, GL_POSITION, currentLighting -> light_position);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        return;
        
    }
    
    else return;
    
}

//create the menu
void createMenu(){
    
    int choose;
    choose = glutCreateMenu(mymenu);
    glutAddMenuEntry("male hummingbird", 1);
    glutAddMenuEntry("female hummingbird", 2);
    glutAddMenuEntry("baby hummingbird", 3);
    glutAttachMenu(GLUT_LEFT_BUTTON);
    
}

void createMenu2(){
    
    int light;
    light = glutCreateMenu(mymenu2);
    glutAddMenuEntry("noon", 1);
    glutAddMenuEntry("early evening", 2);
    glutAddMenuEntry("late evening", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    return;
    
}

int main(int argc, char** argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("hummingbird");
    
    glutDisplayFunc(mydisplay);
    glutIdleFunc(myidle);
    glutReshapeFunc(reshape);
    
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    init();
    
    createMenu();
    createMenu2();

    glutMainLoop();
    
    return 0;
    
}
