#include "Core\Context.h"
#include "Core\Engine.h"
#include "Core\Logger.h"
#include "GameFramework\World.h"
#include "GameFramework\Entity.h"
#include "Component\CameraComponent.h"
#include "Component\MeshRenderComponent.h"
#include "Component\LightComponent.h"
#include "Resource\ResourceManager.h"
#include "Resource\Model.h"
#include "Resource\ModelLoader.h"
#include "Resource\Material.h"
#include "Resource\Texture2D.h"
#include "Rendering\Cube.h"
#include "Rendering\RendererDX11.h"
#include "Math\Vector3.h"
#include "MT\ThreadPool.h"
#include "RotateComponent.h"

using namespace Mile;

int main( )
{
   auto context = new Context( );
   auto engine = new Engine( context );

   if ( !engine->Init( ) )
   {
      return 1;
   }

   auto world = context->GetSubSystem<World>( );
   auto resMng = context->GetSubSystem<ResourceManager>( );
   auto renderer = context->GetSubSystem<RendererDX11>();

   Cube* cubeMesh = new Cube(renderer);
   cubeMesh->Init(Vector3(-1.0f, -1.0f, -1.0f), Vector3(1.0f, 1.0f, 1.0f));
   Entity* cube = world->CreateEntity(TEXT("Cube"));
   Transform* cubeTransform = cube->GetTransform();
   MeshRenderComponent* cubeRenderComponent = cube->AddComponent<MeshRenderComponent>();
   RotateComponent* cubeRotation = cube->AddComponent<RotateComponent>();
   cubeRenderComponent->SetMesh(cubeMesh);
   cubeRenderComponent->SetMaterial(resMng->Load<Material>(TEXT("Contents/Materials/Default.material")));
   cubeTransform->SetPosition(Vector3(3.5f, 0.0f, 1.5f));
   cubeTransform->SetScale(Vector3(0.7f, 0.7f, 0.7f));


   Entity* camera = world->CreateEntity(TEXT("Camera"));
   CameraComponent* camComponent = camera->AddComponent<CameraComponent>( );
   Transform* camTransform = camera->GetTransform( );
   camComponent->SetNearPlane(1.0f);
   camComponent->SetFarPlane(1000.0f);
   camComponent->SetFov(60.0f);
   camTransform->SetPosition(Vector3(0.0f, 0.0f, -5.0f));

   Entity* mainLight = world->CreateEntity(TEXT("Upper Light"));
   LightComponent* mainLightComponent = mainLight->AddComponent<LightComponent>();
   Transform* mainLightTransform = mainLight->GetTransform();
   mainLightComponent->SetLightType(ELightType::Point);
   mainLightComponent->SetRadiance(Vector3(200.0f, 200.0f, 200.0f));
   mainLightTransform->SetPosition(Vector3(0.0f, 0.0f, -5.0f));

   Model* damagedHelmetModel = resMng->Load<Model>(TEXT("Contents/Models/DamagedHelmet/DamagedHelmet.gltf"));
   Entity* damagedHelmet = Model::Instantiate(damagedHelmetModel, world, TEXT("DamagedHelmet"));
   Entity* damagedHelmetMesh = damagedHelmet->GetChildren()[0];
   RotateComponent* damagedHelmetRotation = damagedHelmet->AddComponent<RotateComponent>();
   MeshRenderComponent* helmetRenderComponent = damagedHelmetMesh->GetComponent<MeshRenderComponent>();
   Material* damagedHelmetMaterial = helmetRenderComponent->GetMaterial();
   damagedHelmetMaterial->Save();

   Model* lanternModel = resMng->Load<Model>(TEXT("Contents/Models/Lantern/Lantern.gltf"));
   Entity* lantern = Model::Instantiate(lanternModel, world, TEXT("Lantern"));
   Entity* lanternMesh = lantern->GetChildren()[0];
   RotateComponent* lanternRotateComponent = lantern->AddComponent<RotateComponent>();
   MeshRenderComponent* lanternRenderComponent = lanternMesh->GetComponent<MeshRenderComponent>();
   Material* lanternMaterial = lanternRenderComponent->GetMaterial();
   lanternMaterial->Save();

   Transform* lanternTransform = lantern->GetTransform();
   lanternTransform->SetScale(Vector3(0.1f, 0.1f, 0.1f));
   lanternTransform->SetPosition(Vector3(-2.5f, -0.9f, 0.0f));

   Model* metalRoughSpheresModel = resMng->Load<Model>(TEXT("Contents/Models/MetalRoughSpheres/MetalRoughSpheres.gltf"));
   Entity* spheresEntity = Model::Instantiate(metalRoughSpheresModel, world, TEXT("Spheres"));
   Entity* spheresMesh = spheresEntity->GetChildren()[0];
   MeshRenderComponent* spheresRenderComponent = spheresMesh->GetComponent<MeshRenderComponent>();
   Material* spheresMaterial = spheresRenderComponent->GetMaterial();
   spheresMaterial->Save();

   Transform* spheresTransform = spheresEntity->GetTransform();
   //spheresTransform->SetScale(Vector3(0.1f, 0.1f, 0.1f));
   spheresTransform->SetPosition(Vector3(0.0f, 0.0f, 4.0f));

   int execute = engine->Execute( );
   //world->Save();
   SafeDelete( context );
   return execute;
}