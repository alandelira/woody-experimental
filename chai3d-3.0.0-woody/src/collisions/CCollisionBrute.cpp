//==============================================================================
/*
    Software License Agreement (BSD License)
    Copyright (c) 2003-2014, CHAI3D.
    (www.chai3d.org)

    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above
    copyright notice, this list of conditions and the following
    disclaimer in the documentation and/or other materials provided
    with the distribution.

    * Neither the name of CHAI3D nor the names of its contributors may
    be used to endorse or promote products derived from this software
    without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
    COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
    ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE. 

    \author    <http://www.chai3d.org>
    \author    Chris Sewell
    \author    Francois Conti
    \version   3.0.0 $Rev: 1304 $
*/
//==============================================================================

//------------------------------------------------------------------------------
#include "collisions/CCollisionBrute.h"
using namespace std;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
namespace chai3d {
//------------------------------------------------------------------------------

//==============================================================================
/*!
    Constructor of cCollisionBrute.

    \param  a_triangles  List of triangles.
*/
//==============================================================================
cCollisionBrute::cCollisionBrute(cTriangleArrayPtr a_triangles)
{
    // radius padding around triangles
    m_radiusAroundTriangles = 0.0;

    // list of triangles
    m_triangles = a_triangles;
}


//==============================================================================
/*!
    Check if the given line segment intersects any triangle of the mesh. This
    method is called "brute force" because all triangles are checked by
    invoking their collision-detection methods.  This method is simple but very
    inefficient.

    \param  a_object  Object for which collision detector is being used.
    \param  a_segmentPointA  Initial point of segment.
    \param  a_segmentPointB  End point of segment.
    \param  a_recorder  Returns pointer to nearest collided object.
    \param  a_settings  Structure which contains some rules about how the
            collision detection should be performed.

    \return Return __true__ if the line segment intersects one or more triangles.
*/
//==============================================================================
bool cCollisionBrute::computeCollision(cGenericObject* a_object,
                                       cVector3d& a_segmentPointA,
                                       cVector3d& a_segmentPointB,
                                       cCollisionRecorder& a_recorder,
                                       cCollisionSettings& a_settings)
{
    // temp variables
    bool hit = false;

    // check all triangles for collision
    int numtriangles = m_triangles->getNumTriangles();
    for (unsigned int i=0; i<numtriangles; i++)
    {
        // check for a collision between this triangle and the segment by
        // calling the triangle's collision detection method
        if (m_triangles->m_allocated[i])
        {
            if (m_triangles->computeCollision(i,
                a_object,
                a_segmentPointA, 
                a_segmentPointB, 
                a_recorder, 
                a_settings))
            {
                hit = true;
            }
        }
    }

    // return result
    return (hit);
}




//------------------------------------------------------------------------------
} // namespace chai3d
//------------------------------------------------------------------------------
