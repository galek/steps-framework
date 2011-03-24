//
// Camera class for OpenGL
//
// Author: Alexey V. Boreskov <steps3d@narod.ru>, <steps3d@gmail.com>
//

#include    "Camera.h"
#include	"quat.h"
#include	"plane.h"

Camera :: Camera ( const vec3& p, float yaw, float pitch, float roll,
                   float aFov, float nearZ, float farZ, bool rHanded )
{
	zNear       = nearZ;
	zFar        = farZ;
    pos         = p;
    fov         = aFov;
	rightHanded = rHanded;
	infinite    = false;
	
	setViewSize    ( 640, 480, aFov );
    setEulerAngles ( yaw, pitch, roll );
}

Camera :: Camera ( const vec3& p, const quat& orientation,
                   float aFov, float nearZ, float farZ, bool rHanded )
{
	zNear       = nearZ;
	zFar        = farZ;
    pos         = p;
	rightHanded = rHanded;
	infinite    = false;

	setViewSize    ( 640, 480, aFov );
    setOrientation ( orientation );
}

Camera :: Camera ( const Camera& camera )
{
    zNear       = camera.zNear;
    zFar        = camera.zFar;
    fov         = camera.fov;
    pos         = camera.pos;
    rightHanded = camera.rightHanded;
	infinite    = camera.infinite;
	width       = camera.width;
	height      = camera.height;
	aspect      = camera.aspect;
	rotation    = camera.rotation;

    computeMatrix ();
}

void    Camera :: setEulerAngles ( float yaw, float pitch, float roll )
{
	rotation = vec3 ( yaw, pitch, roll );

    computeMatrix ();
}

void	Camera :: setOrientation ( const quat& orientation )
{
    mat3  r;

	orientation.getMatrix ( r );

	rotation = eulerFromMatrix ( r );

    computeMatrix ();
}

quat	Camera :: getOrientation () const
{
	return quat ( rot );		// use existing rotation matrix
}

void	Camera :: setRightHanded  ( bool flag )
{
	if ( flag == rightHanded )
		return;

	rightHanded = flag;

	computeMatrix ();
}

void    Camera :: setFov ( float newFovAngle )
{
    fov = newFovAngle;

    computeMatrix ();
}

void	Camera :: setViewSize ( int theWidth, int theHeight, float theFov )
{
	width  = theWidth;
	height = theHeight;
	fov    = theFov;
	aspect = (float)width / (float) height;

	computeMatrix ();
}

void    Camera :: computeMatrix ()
{
	rot  = mat3 :: rotateEuler ( rotation.x, rotation.y, rotation.z );
	proj = perspective ( fov, aspect, zNear, zFar ) * mat4 ( rot ) * mat4 :: translate ( -pos );
}

void    Camera :: mirror ( const plane& mirror )		// XXX
{
	vec3	viewDir = getViewDir ();
	vec3	sideDir = getSideDir ();
	vec3	upDir   = getUpDir   ();
	
    mirror.reflectPos ( pos );
    mirror.reflectDir ( viewDir );
    mirror.reflectDir ( upDir );
    mirror.reflectDir ( sideDir );
	
					// now build rotation matrix from vectors
	mat3 r ( sideDir.x, upDir.x, -viewDir.x,
	         sideDir.y, upDir.y, -viewDir.y,
		     sideDir.z, upDir.z, -viewDir.z );
			 
	rotation    = eulerFromMatrix ( r );
    rightHanded = !rightHanded;

    computeMatrix ();
}

void	Camera :: getPlanePolyForZ ( float z, vec3 * poly ) const
{
	float	halfAngle = 0.5f * M_PI * fov / 180.0f;
    float	f         = 1 / (float)tan ( halfAngle );
	vec3	base ( z * aspect / f, z / f, z );
	vec3	viewDir = getViewDir ();
	vec3	sideDir = getSideDir ();
	vec3	upDir   = getUpDir   ();
	
	poly [0] = pos + base.z * viewDir + base.x * sideDir + base.y * upDir;
	poly [1] = pos + base.z * viewDir + base.x * sideDir - base.y * upDir; 	//vec3 (  base.x, -base.y, base.z );
	poly [2] = pos + base.z * viewDir - base.x * sideDir - base.y * upDir;	//vec3 ( -base.x, -base.y, base.z );
	poly [3] = pos + base.z * viewDir - base.x * sideDir + base.y * upDir;	//vec3 ( -base.x,  base.y, base.z );
}
