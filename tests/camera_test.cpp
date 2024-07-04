#include <gtest/gtest.h>
#include "camera.hpp"
#include "matrix4.hpp"
#include "vec3.hpp"

// Test default constructor and initialization with values
TEST(CameraTest, Initialization) {
  Camera camera1;
  EXPECT_FLOAT_EQ(camera1.getPosition().x, 0.0f);
  EXPECT_FLOAT_EQ(camera1.getPosition().y, 0.0f);
  EXPECT_FLOAT_EQ(camera1.getPosition().z, 0.0f);
  EXPECT_FLOAT_EQ(camera1.getDirection().x, 0.0f);
  EXPECT_FLOAT_EQ(camera1.getDirection().y, 0.0f);
  EXPECT_FLOAT_EQ(camera1.getDirection().z, 1.0f);
  EXPECT_FLOAT_EQ(camera1.getUp().x, 0.0f);
  EXPECT_FLOAT_EQ(camera1.getUp().y, 1.0f);
  EXPECT_FLOAT_EQ(camera1.getUp().z, 0.0f);

  Vec3 position(1.0f, 2.0f, 3.0f);
  Vec3 direction(4.0f, 5.0f, 6.0f);
  Vec3 up(0.0f, 1.0f, 0.0f);
  Vec3 normalizedDirection = direction.normalized();
  Camera camera2(position, direction, up);

  EXPECT_FLOAT_EQ(camera2.getPosition().x, 1.0f);
  EXPECT_FLOAT_EQ(camera2.getPosition().y, 2.0f);
  EXPECT_FLOAT_EQ(camera2.getPosition().z, 3.0f);
  EXPECT_FLOAT_EQ(camera2.getDirection().x, normalizedDirection.x);
  EXPECT_FLOAT_EQ(camera2.getDirection().y, normalizedDirection.y);
  EXPECT_FLOAT_EQ(camera2.getDirection().z, normalizedDirection.z);
  EXPECT_FLOAT_EQ(camera2.getUp().x, 0.0f);
  EXPECT_FLOAT_EQ(camera2.getUp().y, 1.0f);
  EXPECT_FLOAT_EQ(camera2.getUp().z, 0.0f);
}

// Test forward movement
TEST(CameraTest, MoveForward) {
  Camera camera(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));
  camera.moveForward(5.0f);
  EXPECT_FLOAT_EQ(camera.getPosition().x, 0.0f);
  EXPECT_FLOAT_EQ(camera.getPosition().y, 0.0f);
  EXPECT_FLOAT_EQ(camera.getPosition().z, 5.0f);
}

// Test backward movement
TEST(CameraTest, MoveBackward) {
  Camera camera(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));
  camera.moveBackward(5.0f);
  EXPECT_FLOAT_EQ(camera.getPosition().x, 0.0f);
  EXPECT_FLOAT_EQ(camera.getPosition().y, 0.0f);
  EXPECT_FLOAT_EQ(camera.getPosition().z, -5.0f);
}

// Test left movement
TEST(CameraTest, MoveLeft) {
  Camera camera(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));
  camera.moveLeft(5.0f);
  EXPECT_FLOAT_EQ(camera.getPosition().x, -5.0f);
  EXPECT_FLOAT_EQ(camera.getPosition().y, 0.0f);
  EXPECT_FLOAT_EQ(camera.getPosition().z, 0.0f);
}

// Test right movement
TEST(CameraTest, MoveRight) {
  Camera camera(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));
  camera.moveRight(5.0f);
  EXPECT_FLOAT_EQ(camera.getPosition().x, 5.0f);
  EXPECT_FLOAT_EQ(camera.getPosition().y, 0.0f);
  EXPECT_FLOAT_EQ(camera.getPosition().z, 0.0f);
}

// Test turning left
TEST(CameraTest, TurnLeft) {
  Camera camera(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f));
  camera.turnLeft(M_PI_2); // Turn 90 degrees to the left
  EXPECT_NEAR(camera.getDirection().x, 0.0f, 1e-5);
  EXPECT_NEAR(camera.getDirection().y, 0.0f, 1e-5);
  EXPECT_NEAR(camera.getDirection().z, -1.0f, 1e-5);
}

// Test turning right
TEST(CameraTest, TurnRight) {
  Camera camera(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f));
  camera.turnRight(M_PI_2); // Turn 90 degrees to the right
  EXPECT_NEAR(camera.getDirection().x, 0.0f, 1e-5);
  EXPECT_NEAR(camera.getDirection().y, 0.0f, 1e-5);
  EXPECT_NEAR(camera.getDirection().z, 1.0f, 1e-5);
}

// Test looking up
TEST(CameraTest, LookUp) {
  Camera camera(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));
  camera.lookUp(M_PI_2); // Look up 90 degrees
  EXPECT_NEAR(camera.getDirection().x, 0.0f, 1e-5);
  EXPECT_NEAR(camera.getDirection().y, 1.0f, 1e-5);
  EXPECT_NEAR(camera.getDirection().z, 0.0f, 1e-5);
}


// Test looking down
TEST(CameraTest, LookDown) {
  Camera camera(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));
  camera.lookDown(M_PI_2); // Look down 90 degrees
  EXPECT_NEAR(camera.getDirection().x, 0.0f, 1e-5);
  EXPECT_NEAR(camera.getDirection().y, -1.0f, 1e-5);
  EXPECT_NEAR(camera.getDirection().z, 0.0f, 1e-5);
}

// Test tilting left
TEST(CameraTest, TiltLeft) {
  Camera camera(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));
  camera.tiltLeft(M_PI_2); // Tilt left 90 degrees
  EXPECT_NEAR(camera.getUp().x, -1.0f, 1e-5);
  EXPECT_NEAR(camera.getUp().y, 0.0f, 1e-5);
  EXPECT_NEAR(camera.getUp().z, 0.0f, 1e-5);
}

// Test tilting right
TEST(CameraTest, TiltRight) {
  Camera camera(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));
  camera.tiltRight(M_PI_2); // Tilt right 90 degrees
  EXPECT_NEAR(camera.getUp().x, 1.0f, 1e-5);
  EXPECT_NEAR(camera.getUp().y, 0.0f, 1e-5);
  EXPECT_NEAR(camera.getUp().z, 0.0f, 1e-5);
}

// Test getting view matrix
TEST(CameraTest, GetViewMatrix) {
  Camera camera(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));
  Matrix4 viewMatrix = camera.getViewMatrix();

  EXPECT_FLOAT_EQ(viewMatrix(0, 0), 1.0f);
  EXPECT_FLOAT_EQ(viewMatrix(0, 1), 0.0f);
  EXPECT_FLOAT_EQ(viewMatrix(0, 2), 0.0f);
  EXPECT_FLOAT_EQ(viewMatrix(0, 3), 0.0f);
  EXPECT_FLOAT_EQ(viewMatrix(1, 0), 0.0f);
  EXPECT_FLOAT_EQ(viewMatrix(1, 1), 1.0f);
  EXPECT_FLOAT_EQ(viewMatrix(1, 2), 0.0f);
  EXPECT_FLOAT_EQ(viewMatrix(1, 3), 0.0f);
  EXPECT_FLOAT_EQ(viewMatrix(2, 0), 0.0f);
  EXPECT_FLOAT_EQ(viewMatrix(2, 1), 0.0f);
  EXPECT_FLOAT_EQ(viewMatrix(2, 2), 1.0f);
  EXPECT_FLOAT_EQ(viewMatrix(2, 3), 0.0f);
  EXPECT_FLOAT_EQ(viewMatrix(3, 0), 0.0f);
  EXPECT_FLOAT_EQ(viewMatrix(3, 1), 0.0f);
  EXPECT_FLOAT_EQ(viewMatrix(3, 2), 0.0f);
  EXPECT_FLOAT_EQ(viewMatrix(3, 3), 1.0f);
}
