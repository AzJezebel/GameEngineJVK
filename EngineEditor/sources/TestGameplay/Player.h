#pragma once
#include <foundation/PxVec3.h>

#include "../Components/StaticMesh.h"
#include "../Scene/Actor.h"
#include "Forces/ForceMode.h"
#include "Shapes/ComplexMesh/ConvexMeshDescriptor.h"
#include "Shapes/ComplexMesh/TriangleMeshDescriptor.h"
#include "Vector/Vector3.h"

class LightSystem;
class TriangleMesh;
class ConvexMesh;
struct Collider;
class BoxShape;

class Player : public Actor
{
public:
	Player();
	~Player();
	
	void Update(float deltaTime) override;
	void Begin() override;
	void End() override;

	void BeginOverlap(size_t indexOtherCollider);
	void AddForce();
	/*StaticMesh m_mesh;
	std::pair<std::vector<uint32_t>, std::vector<LibMath::Vector3>> m_dataObj;
	ConvexMesh* m_cPhysixShape = nullptr;
	TriangleMesh* m_tPhysixShape;
	Collider* m_collider;
	ConvexMeshDescriptor m_cDesc;
	TriangleMeshDescriptor m_tDesc;*/
	size_t indexPointLight = 0;
	LightSystem* m_lightSystem = nullptr;
	int test = 0;
};
