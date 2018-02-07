//
//  LTexturedCircle.hpp
// Dungeon_Game
//
//  Created by Roberto Ockerse on 03/03/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef LTexturedCircle_hpp
#define LTexturedCircle_hpp

#include "LShaderProgram.hpp"
#include "glm/glm.hpp"
#include "LColorRGBA.h"


class LTexturedCircle : public LShaderProgram
{
public:
    LTexturedCircle();
    
    bool loadProgram(std::string glvsPath, std::string glfsPath);
    
    void setTextCoordPointer(GLsizei stride,  const GLvoid *data);
    
    void setVertexPointer(GLsizei stride, const GLvoid *data);
    
    void setColorPointer(GLsizei stride, const GLvoid *data);
    
    
    void setResolution(GLfloat width, GLfloat height);
    
    void enableVertexPointers();
    void disableVertexPointers();
    
    void enableTextCoorPonters();
    void disableTextCoorPointer();
    
    
    void enableDataPointers();
    void disableDataPointers();
    
    void updateModelView(glm::mat4 matrix);
    
    void updateProjectionMatrix(glm::mat4 matrix);
    
    //updates the center point that the program will use to handle the rendering
    void updateCenterPoint(GLfloat x, GLfloat y);
    
    
private:
    
    GLint mVertexPosLocation;
    GLint mTexCoordLocation;
    GLint mColorLocation;
    GLint mProjectionMatrixLocation;
    GLint mModelViewMatrixLocation;
    GLint mResolutionLocation;
    GLint mCenterLocation;
};

#endif /* LTexturedCircle_hpp */
