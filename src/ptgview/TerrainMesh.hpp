/**
 * @file TerrainMesh.hpp
 * @date 2. nov. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef TERRAINMESH_HPP
#define TERRAINMESH_HPP

#include <helsing/Drawable.hpp>

#include <helsing/Shader.hpp>
#include <helsing/HeightMap.hpp>
#include <helsing/math/Vec4.hpp>

/** @brief A collection of vertices and normals used for drawing a terrain
 *
 * The class is initialized using a HeightMap
 */
class TerrainMesh: public helsing::Drawable {
public:
	explicit TerrainMesh(const helsing::HeightMap&, helsing::Shader*);
	virtual ~TerrainMesh();
	virtual void setShader(helsing::Shader* shader){this->shader = shader;}
	virtual void draw(const helsing::Mat4& modelViewMatrix, const helsing::Mat4& projectionMatrix);
private:
	struct TerrainVertex{
		helsing::Vec4 position;
		helsing::Vec4 normal;
	};
	static TerrainVertex getVertex(int x, int z, const helsing::HeightMap&);
	unsigned int vaoId;
	unsigned int vboId;
	unsigned int iboId;
	unsigned int numberOfVertices;
	unsigned int width;
	helsing::Shader* shader;

    // Disable value copying
    TerrainMesh(const TerrainMesh& uncopyable);
    TerrainMesh& operator=(const TerrainMesh& uncopyable);
};

#endif // TERRAINMESH_HPP
