#pragma once

#include "Renderable.h"

class TerrainQuad : public Renderable
{
protected:
	QVector3D lightPos_;
	float sign_;
	unsigned int numIdxPerStrip_;
	unsigned int numStrips_;
	QOpenGLTexture heightTexture_;
public:
	TerrainQuad();
	virtual ~TerrainQuad();

	// Our init method is much easier now.  We only need a texture!
	virtual void init(const QString& textureFile);
	virtual void update(const qint64 msSinceLastFrame) override;
	virtual void draw(const QMatrix4x4& world, const QMatrix4x4& view, const QMatrix4x4& projection) override;


private:

};