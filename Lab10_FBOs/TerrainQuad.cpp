#include "TerrainQuad.h"

#include <QtGui>
#include <QOpenGLFunctions_3_3_core>

TerrainQuad::TerrainQuad() : lightPos_(0.5f, 0.5f, -2.0f), sign_(1.0f), numIdxPerStrip_(0), numStrips_(0), heightTexture_(QOpenGLTexture::Target2D)
{}

TerrainQuad::~TerrainQuad()
{}

void TerrainQuad::init(const QString& textureFile)
{
    // The unit quad goes from 0.0 to 1.0 in each dimension.
    QVector<QVector3D> pos;
    QVector<QVector3D> norm;
    QVector<QVector2D> texCoord;
    QVector<unsigned int> idx;
    // We need to figure out how many rows and columns we want!
    const unsigned int numRows = 300;
    const unsigned int numCols = 300;
    float rowStep = 1.0f / (float)numRows;
    float colStep = 1.0f / (float)numCols;

    QVector<unsigned int> stripIdx;
    QVector3D normal(0.0, 1.0, 0.0);
    QImage heightImage("../../terrain2.ppm");
    unsigned int curIdx = 0;
    // Populate our grid
    for (unsigned int r = 0; r < numRows; ++r) {
        for (unsigned int c = 0; c < numCols; ++c) {
            // compute our top coordinate
            float z = r * rowStep;
            float x = c * colStep;
            int pixX = z * (heightImage.width()-1);
            int pixY = x * (heightImage.height()-1);
            float val = heightImage.pixelColor(pixX, pixY).redF();
            float y = val / 4.0;
            // Be explicit about our texture coords
            float u = z;
            float v = x;
            pos << QVector3D(x, y, z);
            norm << normal;
            texCoord << QVector2D(u, v);
        }
    }
    // Assign our strips
    numStrips_ = numRows;
    int colsPerStrip = numCols;
    numIdxPerStrip_ = colsPerStrip * 2;
    for (unsigned int s = 0; s < numStrips_; ++s) {
        unsigned int startIDX = s * (numIdxPerStrip_/2);
        unsigned int topIdx = startIDX;
        for (int i = 0; i < colsPerStrip; ++i) {
            idx << topIdx;
            idx << topIdx + colsPerStrip;
            topIdx++;
        }
    }
    Renderable::init(pos, norm, texCoord, idx, textureFile);
    heightTexture_.setData(heightImage);
}

void TerrainQuad::update(const qint64 msSinceLastFrame)
{
    // For this lab, we want our polygon to rotate. 
    float sec = msSinceLastFrame / 1000.0f;
    float anglePart = sec * rotationSpeed_ * 360.f;
    rotationAngle_ += anglePart;
    while (rotationAngle_ >= 360.0) {
        rotationAngle_ -= 360.0;
    }
}

void TerrainQuad::draw(const QMatrix4x4& world, const QMatrix4x4& view, const QMatrix4x4& projection)
{
    // Create our model matrix.
    QMatrix4x4 rotMatrix;
    rotMatrix.setToIdentity();
    rotMatrix.translate(0.5, 0.0, 0.5);
    rotMatrix.rotate(rotationAngle_, QVector3D(0.0, 1.0, 0.0));
    rotMatrix.translate(-0.5, 0.0, -0.5);

    // incorporate a real world transform if want it.
    QMatrix4x4 modelMat;
    modelMat.setToIdentity();
    modelMat = modelMatrix_;
    modelMat = modelMat * rotMatrix;
    modelMat = world * modelMat;
    // Make sure our state is what we want
    shader_.bind();
    // Set our matrix uniforms!
    QMatrix4x4 id;
    id.setToIdentity();
    shader_.setUniformValue("modelMatrix", modelMat);
    shader_.setUniformValue("viewMatrix", view);
    shader_.setUniformValue("projectionMatrix", projection);

    vao_.bind();
    texture_.bind();

    // Setup our shader uniforms for multiple textures.
    for (int s = 0; s < numStrips_-1; ++s) {
        glDrawElements(GL_TRIANGLE_STRIP, numIdxPerStrip_, GL_UNSIGNED_INT, (const GLvoid*)((s * numIdxPerStrip_) * sizeof(unsigned int)));
    }

    heightTexture_.release();
    texture_.release();
    vao_.release();
    shader_.release();
}