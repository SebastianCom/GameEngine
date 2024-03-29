#pragma once

// This header includes all files inside the framework project.
// It is meant for use by game projects ONLY.
// As new files are created, include them here so the game has easy access to them.
// It should not be included by any files inside the framework project.

#include "CoreHeaders.h"

#include "../Libraries/imgui/imgui.h"
#include "../Libraries/box2d/include/box2d/box2d.h"

#include "FWCore.h"
#include "GameCore.h"
#include "Components/ComponentManager.h"
#include "Components/MeshComponent.h"
#include "Components/TransformComponent.h"
#include "Components/PlayerMovementComponent.h"
#include "Components/PhysicsBodyComponent.h"
#include "Components/LightComponent.h"
#include "Events/Event.h"
#include "Events/EventManager.h"
#include "Math/Random.h"
#include "Math/Vector.h"
#include "Objects/Camera.h"
#include "Objects/GameObject.h"
#include "Objects/Material.h"
#include "Objects/Mesh.h"
#include "Objects/Scene.h"
#include "Objects/ShaderProgram.h"
#include "Objects/SpriteSheet.h"
#include "Objects/Texture.h"
#include "Objects/FrameBufferObject.h"
#include "Physics/PhysicsBody.h"
#include "Physics/Box2D/PhysicsWorldBox2D.h"
#include "Physics/Bullet3D/PhysicsWorldBullet3D.h"
#include "UI/ImGuiManager.h"
#include "Utility/Utility.h"
