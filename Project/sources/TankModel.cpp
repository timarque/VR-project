#include "TankModel.hpp"
#include <memory>

// void TankModel::createPhysicsObject(PhysicsEngine physics, btCollisionShape *collision_shape, float mass, btVector3 origin)
// {
//     btTransform localTrans;
//     localTrans.setIdentity();
//     localTrans.setOrigin(btVector3(0, 0.15, 0));
    
//     btTransform carTransform;
//     carTransform.setIdentity();
//     carTransform.setOrigin(origin);
//     btVector3 localInertia(0, 0, 0);
//     collision_shape->calculateLocalInertia(mass, localInertia);
//     PhysicModel::mMotionState = std::make_unique<btDefaultMotionState>(carTransform);
//     btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, &(*PhysicModel::mMotionState), &(*collision_shape), localInertia);
//     PhysicModel::physicsObject = std::make_unique<btRigidBody>(rbInfo);

//     mVehicleRaycaster = std::make_unique<btDefaultVehicleRaycaster>(&(*physics.getWorld()));
//     btRaycastVehicle::btVehicleTuning tuning;
//     mVehicle = std::make_unique<btRaycastVehicle>(tuning, &(*PhysicModel::physicsObject), &(*mVehicleRaycaster));
//     PhysicModel::physicsObject->setActivationState(DISABLE_DEACTIVATION);

//     btVector3 wheelDirection(0, -1, 0);
//     btVector3 wheelAxleCS(-1, 0, 0);
//     mVehicle->addWheel(localTrans.getOrigin() + btVector3(0.5, 0.0, 0.0), wheelDirection, wheelAxleCS, 0.6, 1, tuning, true);
//     mVehicle->addWheel(localTrans.getOrigin() + btVector3(-0.5, 0.0, 0.0), wheelDirection, wheelAxleCS, 0.6, 1, tuning, true);
//     std::cout << "------- Vehicle creation: " << mVehicle->getNumWheels() << " wheels" << std::endl;
//     physics.getWorld()->addVehicle(mVehicle.get());
// }


// void TankModel::applyEngineForce(float force)
// {
//     for (int i = 0; i < mVehicle->getNumWheels(); i++) {
//         std::cout << "Roue " << i << " accel" << std::endl;
//         btWheelInfo &wheel = mVehicle->getWheelInfo(i);
//         mVehicle->applyEngineForce(force, i);
//     }
// }

// void TankModel::setBrake(float force)
// {
//     for (int i = 0; i < mVehicle->getNumWheels(); i++) {
//         btWheelInfo &wheel = mVehicle->getWheelInfo(i);
//         mVehicle->setBrake(force, i);
//     }
// }

// void TankModel::setSteering(float steering)
// {
//     float steering_clamp = 0.3f;
//     mSteering = steering;
//     if (mSteering > steering_clamp) {
//         mSteering = steering_clamp;
//     } else if (mSteering < -steering_clamp) {
//         mSteering = -steering_clamp;
//     }
//     for (int i = 0; i < mVehicle->getNumWheels(); i++) {
//         btWheelInfo &wheel = mVehicle->getWheelInfo(i);
//         if (wheel.m_bIsFrontWheel)
//         {
//             mVehicle->setSteeringValue(mSteering, i);
//         }
//     }
// }

// glm::vec3 TankModel::getPosition() {
//     if (mVehicle) {
//         // Obtenez la position du véhicule du RigidBody associé
//         const btTransform &transform = mVehicle->getChassisWorldTransform();
//         const btVector3 &position = transform.getOrigin();

//         // Convertissez la position en glm::vec3
//         return glm::vec3(position.getX(), position.getY(), position.getZ());
//     }

//     // Retournez une valeur par défaut si le véhicule n'est pas initialisé
//     return glm::vec3(0.0f);
// }

bool TankModel::update(GLFWwindow *window, float deltaTime)
{
    bool shot = false;
    // Key for resetting car position and position
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        std::cout << "Reset position" << std::endl;
        // mGameObject.mTransform->setTranslation(mInitialPosition);
        // mGameObject.mTransform->setRotation(INITIAL_ROTATION);
        // this->setSteering(0.5);
        PhysicModel::physicsObject->setLinearVelocity(btVector3(0, 0, 0));
        PhysicModel::physicsObject->setAngularVelocity(btVector3(0, 0, 0));
    }

    // Keys for driving car
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        std::cout << "Jump" << std::endl;
        applyImpulse(btVector3(0.0f, 0.2f, 0.0f));
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        moveForward(1.5);
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        moveBackward(1.5);
    }




    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        moveForward(3.0);
    }

    if (lastMouseX == 0, lastMouseY) {
        // Initialisation de la position du curseur
        double lastMouseX, lastMouseY;
        glfwGetCursorPos(window, &lastMouseX, &lastMouseY);
    }

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    
    // rotation horizontale
    double deltaX = mouseX - lastMouseX;
    float rotationSpeed = 0.01f;
    rotate((float)(-deltaX * rotationSpeed));
    lastMouseX = mouseX;
    
    // Rotation verticale
    double deltaY = mouseY - lastMouseY;
    
    heightView -= deltaY/(600);
    if (heightView > 2.5) heightView = 2.5;
    if (heightView < 0) heightView = 0.0;
    
    lastMouseY = mouseY;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (get_reload_time_left(glfwGetTime()) > this->reload_time) {
            set_reload_time_start(glfwGetTime());
            shot = true;
        }
    }
    return shot;
}

// glm::mat4 TankModel::getOpenGLMatrix() {
//     if (mVehicle)
//     {
//         // Obtenez la transformation du corps rigide associé au véhicule
//         const btTransform &transform = mVehicle->getChassisWorldTransform();

//         // Extrayez la matrice de transformation
//         btScalar matrix[16];
//         transform.getOpenGLMatrix(matrix);

//         // Convertissez la matrice en glm::mat4
//         return glm::make_mat4(matrix);
//     }

//     // Retournez une matrice identité si le véhicule n'est pas initialisé
//     return glm::mat4(1.0f);
// }
