#include "DeathBox.h"


#include "../Components/Collider.h"
#include "../Scene/SceneManager.h"
#include "../Systems/PhysixSystem.h"
#include "Shapes/Primitives/BoxShape.h"


DeathBox::DeathBox()
{
	m_name = "DeathBox";

	BoxShape* box =  new BoxShape(2,2,2);
	Collider col(*box, RigidType::STATIC ,*GetTransform(), m_idEntity);

	col.TriggerCollision(true);
	col.BindOnBeginContact(this, &DeathBox::BeginOverlap);

	const size_t indexCollider = World::GetInstance().GetSystem<PhysixSystem>()->Register(col);
	
	AddComponent<Collider>(indexCollider);
}

void DeathBox::BeginOverlap(size_t idOtherEntity)
{
	const auto root = SceneManager::GetInstance().GetScene()->m_root;
	const auto actor = SceneManager::GetInstance().GetScene()->GetActor(root, idOtherEntity);

	if(actor->m_name == "Capsule")
	{
		actor->GetTransform()->SetLocalPosition({ 0,10,0 });
	}
}
