
//#include "lighting.h"
#include "src/main.h"
#include "src/parser.hh"
#define MS_PER_CYCLE 1000
float Time; // = 1.0;
int spin=0;
int clusterCollectionSize=0;
int k;
std::string strFileName;

void parseArgument(int argc,char  *argv[])

{

    optionparser::parser p("Anomaly detection and clustering algorithm visualization tool");

    p.add_option("-knn", "-k").help("Number of cluster for K-mean")
            .mode(optionparser::store_value)
            .default_value(3);
            //.m_default_value("4");


    p.add_option("-gmm","-g").help("Number of cluster of GMM.")
            .mode(optionparser::store_mult_values)
            .required(false)
            .default_value("3");

    p.add_option("-input", "-i") .help("Input data.")
            .mode(optionparser::store_value)
                    // .required(true)
            .default_value("multivariated.txt");

    p.eat_arguments(argc, argv);


    if (p.get_value("input"))
    {
        auto names = p.get_value<std::string>("input");

        strFileName = names;
        std::cout<<strFileName<<" File name"<<std::endl;

        /*for (int i = 0; i < names.size(); ++i)
        {
            std::cout << "element " << i << ": " << names[i] << std::endl;
        }*/

    }

    if (p.get_value("gmm"))
    {
        auto names = p.get_value<int>("gmm");

        std::cout << "Gmm value" <<names<<std::endl;

    }

    if (p.get_value("knn"))
    {
         auto names = p.get_value<int>("knn");
        k = names;
        std::cout << "K value" <<names<<std::endl;

    }
   // std::cout<<argv[0]<<argv[1];
    //k =5; atoi(argv[1]);

}
int
main( int argc, char  *argv[ ] )
{
    // turn on the glut package:
    // (do this before checking argc and argv since it might
    // pull some command line arguments out)

    parseArgument(argc,argv);
    glutInit( &argc, argv );

    // setup all the graphics stuff:

    InitGraphics( );


    // create the display structures that will not change:

    InitLists( );


    // init all the global variables used by Display( ):
    // this will also post a redisplay

    Reset( );


    // setup all the user interface stuff:

    InitMenus( );


    // draw the scene once and wait for some interaction:
    // (this will never return)

    glutSetWindow( MainWindow );
    glutMainLoop( );


    // this is here to make the compiler happy:

    return 0;
}


// this is where one would put code that is to be called
// everytime the glut main loop has nothing to do
//
// this is typically where animation parameters are set
//
// do not call Display( ) from here -- let glutMainLoop( ) do it

void
Animate( )
{
    // put animation stuff in here -- change some global variables
    // for Display( ) to find:
    int ms = glutGet(GLUT_ELAPSED_TIME);
    ms %= MS_PER_CYCLE;
    Time = (float)ms / (float)MS_PER_CYCLE;		// [0.,1.)
    // force a call to Display( ) next time it is convenient:
    spin = spin+1;// = Time ; //* 360;
    glutSetWindow( MainWindow );
    glutPostRedisplay( );
}


// draw the complete scene:

void
Display( )
{
    if( DebugOn != 0 )
    {
        fprintf( stderr, "Display\n" );
    }


    // set which window we want to do the graphics into:

    glutSetWindow( MainWindow );


    // erase the background:

    glDrawBuffer( GL_BACK );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable( GL_DEPTH_TEST );

    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_LIGHTING);

    // specify shading to be flat:

   // glShadeModel( GL_FLAT );


    // set the viewport to a square centered in the window:

    GLsizei vx = glutGet( GLUT_WINDOW_WIDTH );
    GLsizei vy = glutGet( GLUT_WINDOW_HEIGHT );
    GLsizei v = vx < vy ? vx : vy;			// minimum dimension
    GLint xl = ( vx - v ) / 2;
    GLint yb = ( vy - v ) / 2;
    glViewport( xl, yb,  v, v );


    // set the viewing volume:
    // remember that the Z clipping  values are actually
    // given as DISTANCES IN FRONT OF THE EYE
    // USE gluOrtho2D( ) IF YOU ARE DOING 2D !

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    if( WhichProjection != ORTHO )
        gluPerspective(90., 1., 0.1, 1000.);
    else
        glOrtho(-3., 3., -3., 3., 0.1, 1000.);


    // place the objects into the scene:

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );


    // set the eye position, look-at position, and up-vector:

    gluLookAt( 0., 0., 3.,     0., 0., 0.,     0., 1., 0. );


    // rotate the scene:

   glRotatef( (GLfloat)Yrot, 0., 1., 0. );
   glRotatef( (GLfloat)Xrot, 1., 0., 0. );

// Inset light source.

    // source light
    //glEnable(GL_LIGHTING);
/*
    GLfloat Light0position[] = { 1.0, 1.0, 0 };
    GLfloat Light1position[] = { 0.0, 1.0, 1.0 };
    GLfloat Light2position[] = { 2.3, 1.5, 0 };
*/
    glPushMatrix ();
    //glRotated ((GLdouble) spin, 1.0, 0.0, 0.0);

   // glTranslated (0.0, 0.0, 1.5);
    // uniformly scale the scene:

    if( Scale < MINSCALE )
        Scale = MINSCALE;
    glScalef( (GLfloat)Scale, (GLfloat)Scale, (GLfloat)Scale );


    // set the fog parameters:

    if( DepthCueOn != 0 )
    {
        glFogi( GL_FOG_MODE, FOGMODE );
        glFogfv( GL_FOG_COLOR, FOGCOLOR );
        glFogf( GL_FOG_DENSITY, FOGDENSITY );
        glFogf( GL_FOG_START, FOGSTART );
        glFogf( GL_FOG_END, FOGEND );
        glEnable( GL_FOG );
    }
    else
    {
        glDisable( GL_FOG );
    }


    // possibly draw the axes:

    if( AxesOn != 0 )
    {
        glColor3fv( &Colors[WhichColor][0] );
        glCallList( AxesList );
    }





    // since we are using glScalef( ), be sure normals get unitized:

    glEnable( GL_NORMALIZE );

   // if(clusterdness==KMEAN)
     //   drawKmean();

    // draw the current object:
   if(clusterdness!=currentswitch)
   {
       drawKmean();
   }
    if(spin>0)
    {
        drawKmean();
    }
    glCallList( BoxList );

    //gluLookAt(0,0,0.4,0.7,0.8,0,0.0,0.0,0.0);
   // MjbSphere(0.8,0.2,0.3,30,30);


    // draw some gratuitous text that just rotates on top of the scene:
//    glDisable(GL_LIGHTING);

    glDisable( GL_DEPTH_TEST );
    glColor3f( 0., 1., 1. );
    //DoRasterString( 0., 1., 0., "Text That Moves" );
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    // draw some gratuitous text that is fixed on the screen:
    //
    // the projection matrix is reset to define a scene whose
    // world coordinate system goes from 0-100 in each axis
    //
    // this is called "percent units", and is just a convenience
    //
    // the modelview matrix is reset to identity as we don't
    // want to transform these coordinates

    glDisable( GL_DEPTH_TEST );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluOrtho2D( 0., 100.,     0., 100. );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    glColor3f( 1., 1., 1. );
    //DoRasterString( 5., 5., 0., "Text That Doesn't" );


    // swap the double-buffered framebuffers:

    glutSwapBuffers( );


    // be sure the graphics buffer has been sent:
    // note: be sure to use glFlush( ) here, not glFinish( ) !

    glFlush( );
}




// initialize the display lists that will not change:
// (a display list is a way to store opengl commands in
//  memory so that they can be played back efficiently at a later time
//  with a call to glCallList( )
std::vector<std::vector<std::vector<int> > > clusterCollection;

void drawKmean()
{
      const char* filename = strFileName.c_str(); //"/home/tadeze/projects/comgraph/Finalproject/data/multivariate_large.csv";
//  const char* filenams = "/home/tadeze/projects/comgraph/Finalproject/data/multivariate.csv";
    std::vector<std::vector<double> > points = readcsv(filename,',',true);

    currentswitch=clusterdness;
    rAvg distType=MAX;
    //int k = 4;
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clean the screen and the depth buffer
    //glLoadIdentity();
    BoxList = glGenLists(1);
    glNewList(BoxList, GL_COMPILE);
    std::vector<double> mean = means(points);
    glPointSize(3.0);
    glBegin(GL_POINTS);
    glColor4f(0.0, 0.0, 1.0,1.0);
    glVertex3f(mean[0],mean[1],mean[2]);
    glEnd();

  if(clusterdness==NONCLUSTER)
  {

      glColor4f(1.0, 1.0, 0.0,1.0);
      std::vector<int> pointIndex;
      glBegin(GL_POINTS);
      for (int j = 0; j < points.size(); j++) {
         glVertex3f(points[j][0], points[j][1], points[j][2]);
          pointIndex.push_back(j);

      }
      glEnd();

      glColor4f(.8, .4, .4, 0.4);
      cloudpp cloud = radiusXYZ(pointIndex, points,distType);
      glTranslatef(cloud.x, cloud.y, cloud.z);
      MjbSphere(cloud.radiusX, cloud.radiusY, cloud.radiusZ, 30, 30);



  }
  else if(clusterdness==KMEAN) {

      if(spin==0) {
        Kmean km;
         clusterCollection = km.kmeans(points, k);
}
      clusterCollectionSize = clusterCollection.size();

       if(spin>=clusterCollection.size()-1) {
           spin = clusterCollectionSize - 1;
           glutIdleFunc(Animate);
       }

      std::cout<<clusterCollectionSize<<" Size of the collection \n";
      std::cout<<"Spin value "<<spin<<std::endl;
         std::vector<std::vector<int> > clusters = clusterCollection[spin];
         for (int i = 0; i < clusters.size(); i++) {

            glBegin(GL_POINTS);
             glColor3fv(Colors[i]);

             for (int j = 0; j < clusters[i].size(); j++) {
                 glVertex3f(points[clusters[i][j]][0], points[clusters[i][j]][1], points[clusters[i][j]][2]);
             }
             glEnd();

             glColor4fv(ColorsT[i]);
             //glColor4f(0.9,0.9,0.1, 0.4);
             cloudpp cloud = radiusXYZ(clusters[i], points, distType);
             //std::cout << cloud.radiusX << "\t" << cloud.radiusY << "\t" << cloud.radiusZ << std::endl;
             glTranslatef(cloud.x, cloud.y, cloud.z);
             MjbSphere(cloud.radiusX, cloud.radiusY, cloud.radiusZ, 30, 30);
             glTranslatef(-cloud.x, -cloud.y, -cloud.z);
         }


  }


    else{
      // Put code for the guassian code.
      RGM rgm(points);

      //std::cout << cloud.radiusX << "\t" << cloud.radiusY << "\t" << cloud.radiusZ << std::endl;

      glColor4f(1.0, 1.0, 0.0,1.0);
      glBegin(GL_POINTS);
      for (int j = 0; j < points.size(); j++) {
          glVertex3f(points[j][0], points[j][1], points[j][2]);
      }
      glEnd();
     if(clusterdness==GMM)
     {
         std::vector<cloudpp> cc = rgm.gmmRadiusXYZ(k);
         for (cloudpp cloud : cc)
         {
             glColor4f(.8, .1, 1.0, 0.4);
             glTranslatef(cloud.x, cloud.y, cloud.z);
             MjbSphere(cloud.radiusX, cloud.radiusY, cloud.radiusZ, 30, 30);
             glTranslatef(-cloud.x, -cloud.y, -cloud.z);

         }
     }
     else
     {
        //For single guassian model
         cloudpp cloud = rgm.singleRadiusXYZ();
         glColor4f(.8, .1, 1.0, 0.4);
         glTranslatef(cloud.x, cloud.y, cloud.z);
         MjbSphere(cloud.radiusX, cloud.radiusY, cloud.radiusZ, 30, 30);
         glTranslatef(-cloud.x, -cloud.y, -cloud.z);



     }

  }
glEndList();

}


void
InitLists( )
{


    glutSetWindow(MainWindow);
    // create the object:


   // if(clusterdness==KMEAN)
    drawKmean();


    AxesList = glGenLists( 1 );
    glNewList( AxesList, GL_COMPILE );
    glLineWidth( AXES_WIDTH );
    Axes( 1.5 );
    glLineWidth( 1. );
    glEndList( );


}




// the keyboard callback:

void
Keyboard( unsigned char c, int x, int y )
{
    if( DebugOn != 0 )
        fprintf( stderr, "Keyboard: '%c' (0x%0x)\n", c, c );

    switch( c )
    {
        case 'o':
        case 'O':
            WhichProjection = ORTHO;
            break;

        case 'p':
        case 'P':
            WhichProjection = PERSP;
            break;
        case 'f':
        case 'F':
            Frozen = !Frozen;
            if (Frozen)
                glutIdleFunc(NULL);
            else
                glutIdleFunc(Animate);
            break;
        case 'q':
        case 'Q':
        case ESCAPE:
            DoMainMenu( QUIT );	// will not return here
            break;				// happy compiler

        default:
            fprintf( stderr, "Don't know what to do with keyboard hit: '%c' (0x%0x)\n", c, c );
    }

    // force a call to Display( ):

    glutSetWindow( MainWindow );
    glutPostRedisplay( );
}


// called when the mouse button transitions down or up:

void
MouseButton( int button, int state, int x, int y )
{
    int b = 0;			// LEFT, MIDDLE, or RIGHT

    if( DebugOn != 0 )
        fprintf( stderr, "MouseButton: %d, %d, %d, %d\n", button, state, x, y );


    // get the proper button bit mask:

    switch( button )
    {
        case GLUT_LEFT_BUTTON:
            b = LEFT;		break;

        case GLUT_MIDDLE_BUTTON:
            b = MIDDLE;		break;

        case GLUT_RIGHT_BUTTON:
            b = RIGHT;		break;

        default:
            b = 0;
            fprintf( stderr, "Unknown mouse button: %d\n", button );
    }


    // button down sets the bit, up clears the bit:

    if( state == GLUT_DOWN )
    {
        Xmouse = x;
        Ymouse = y;
        ActiveButton |= b;		// set the proper bit
    }
    else
    {
        ActiveButton &= ~b;		// clear the proper bit
    }
}


// called when the mouse moves while a button is down:

void
MouseMotion( int x, int y )
{
    if( DebugOn != 0 )
        fprintf( stderr, "MouseMotion: %d, %d\n", x, y );


    int dx = x - Xmouse;		// change in mouse coords
    int dy = y - Ymouse;

    if( ( ActiveButton & LEFT ) != 0 )
    {
        Xrot += ( ANGFACT*dy );
        Yrot += ( ANGFACT*dx );
    }


    if( ( ActiveButton & MIDDLE ) != 0 )
    {
        Scale += SCLFACT * (float) ( dx - dy );

        // keep object from turning inside-out or disappearing:

        if( Scale < MINSCALE )
            Scale = MINSCALE;
    }

    Xmouse = x;			// new current position
    Ymouse = y;

    glutSetWindow( MainWindow );
    glutPostRedisplay( );
}


// reset the transformations and the colors:
// this only sets the global variables --
// the glut main loop is responsible for redrawing the scene

void
Reset( )
{
    ActiveButton = 0;
    AxesOn = 1;
    DebugOn = 0;
    DepthCueOn = 0;
    Scale  = 1.0;
    WhichColor = WHITE;
    WhichProjection = PERSP;
    Xrot = Yrot = 0.;
    Frozen = false;
    Distort = false;

}


// called when user resizes the window:

void
Resize( int width, int height )
{
    if( DebugOn != 0 )
        fprintf( stderr, "ReSize: %d, %d\n", width, height );

    // don't really need to do anything since window size is
    // checked each time in Display( ):

    glutSetWindow( MainWindow );
    glutPostRedisplay( );
}


// handle a change to the window's visibility:

void
Visibility ( int state )
{
    if( DebugOn != 0 )
        fprintf( stderr, "Visibility: %d\n", state );

    if( state == GLUT_VISIBLE )
    {
        glutSetWindow( MainWindow );
        glutPostRedisplay( );
    }
    else
    {
        // could optimize by keeping track of the fact
        // that the window is not visible and avoid
        // animating or redrawing it ...
    }
}



///////////////////////////////////////   HANDY UTILITIES:  //////////////////////////


// the stroke characters 'X' 'Y' 'Z' :

static float xx[ ] = {
        0.f, 1.f, 0.f, 1.f
};

static float xy[ ] = {
        -.5f, .5f, .5f, -.5f
};

static int xorder[ ] = {
        1, 2, -3, 4
};

static float yx[ ] = {
        0.f, 0.f, -.5f, .5f
};

static float yy[ ] = {
        0.f, .6f, 1.f, 1.f
};

static int yorder[ ] = {
        1, 2, 3, -2, 4
};

static float zx[ ] = {
        1.f, 0.f, 1.f, 0.f, .25f, .75f
};

static float zy[ ] = {
        .5f, .5f, -.5f, -.5f, 0.f, 0.f
};

static int zorder[ ] = {
        1, 2, 3, 4, -5, 6
};

// fraction of the length to use as height of the characters:
const float LENFRAC = 0.10f;

// fraction of length to use as start location of the characters:
const float BASEFRAC = 1.10f;

//	Draw a set of 3D axes:
//	(length is the axis length in world coordinates)

void
Axes( float length )
{
    glBegin( GL_LINE_STRIP );
    glVertex3f( length, 0., 0. );
    glVertex3f( 0., 0., 0. );
    glVertex3f( 0., length, 0. );
    glEnd( );
    glBegin( GL_LINE_STRIP );
    glVertex3f( 0., 0., 0. );
    glVertex3f( 0., 0., length );
    glEnd( );

    float fact = LENFRAC * length;
    float base = BASEFRAC * length;

    glBegin( GL_LINE_STRIP );
    for( int i = 0; i < 4; i++ )
    {
        int j = xorder[i];
        if( j < 0 )
        {

            glEnd( );
            glBegin( GL_LINE_STRIP );
            j = -j;
        }
        j--;
        glVertex3f( base + fact*xx[j], fact*xy[j], 0.0 );
    }
    glEnd( );

    glBegin( GL_LINE_STRIP );
    for( int i = 0; i < 5; i++ )
    {
        int j = yorder[i];
        if( j < 0 )
        {

            glEnd( );
            glBegin( GL_LINE_STRIP );
            j = -j;
        }
        j--;
        glVertex3f( fact*yx[j], base + fact*yy[j], 0.0 );
    }
    glEnd( );

    glBegin( GL_LINE_STRIP );
    for( int i = 0; i < 6; i++ )
    {
        int j = zorder[i];
        if( j < 0 )
        {

            glEnd( );
            glBegin( GL_LINE_STRIP );
            j = -j;
        }
        j--;
        glVertex3f( 0.0, fact*zy[j], base + fact*zx[j] );
    }
    glEnd( );

}

// function to convert HSV to RGB
// 0.  <=  s, v, r, g, b  <=  1.
// 0.  <= h  <=  360.
// when this returns, call:
//		glColor3fv( rgb );

void
HsvRgb( float hsv[3], float rgb[3] )
{
    // guarantee valid input:

    float h = hsv[0] / 60.f;
    while( h >= 6. )	h -= 6.;
    while( h <  0. ) 	h += 6.;

    float s = hsv[1];
    if( s < 0. )
        s = 0.;
    if( s > 1. )
        s = 1.;

    float v = hsv[2];
    if( v < 0. )
        v = 0.;
    if( v > 1. )
        v = 1.;

    // if sat==0, then is a gray:

    if( s == 0.0 )
    {
        rgb[0] = rgb[1] = rgb[2] = v;
        return;
    }

    // get an rgb from the hue itself:

    float i = floor( h );
    float f = h - i;
    float p = v * ( 1.f - s );
    float q = v * ( 1.f - s*f );
    float t = v * ( 1.f - ( s * (1.f-f) ) );

    float r, g, b;			// red, green, blue
    switch( (int) i )
    {
        case 0:
            r = v;	g = t;	b = p;
            break;

        case 1:
            r = q;	g = v;	b = p;
            break;

        case 2:
            r = p;	g = v;	b = t;
            break;

        case 3:
            r = p;	g = q;	b = v;
            break;

        case 4:
            r = t;	g = p;	b = v;
            break;

        case 5:
            r = v;	g = p;	b = q;
            break;
    }


    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
}