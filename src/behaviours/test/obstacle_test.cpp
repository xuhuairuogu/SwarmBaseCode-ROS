#include <gtest/gtest.h>
#include "test_util.h"

#include "ObstacleBehavior.hpp"
#include "SwarmieSensors.hpp"
#include "ROSTimer.hpp"

TEST(ObstacleBehavior, allFar)
{
   SwarmieSensors sensors;
   sensors.SetLeftSonar(3.2);
   sensors.SetRightSonar(3.2);
   sensors.SetCenterSonar(3.2);

   ObstacleBehavior<ROSTimer> obs(&sensors);
   obs.Update();
   Action a = obs.GetAction();
   EXPECT_LT(a.drive.left, 0.1);
   EXPECT_LT(a.drive.right, 0.1);
}

// TODO: Test the of ObstacleBehavior behavior when each US is at a
// mid/low value (0.8, 0.7, 0.5, 0.3) In each case the movement should
// be non-negligible
TEST(ObstacleBehavior, leftSonarTriggersMovement)
{
   SwarmieSensors sensors;
   Action a;
   sensors.SetLeftSonar(3.2);
   sensors.SetRightSonar(3.2);
   sensors.SetCenterSonar(3.2);

   ObstacleBehavior<ROSTimer> obs(&sensors);
   obs.Update();

   sensors.SetLeftSonar(0.3);
   obs.Update();
   a = obs.GetAction();
   EXPECT_TRUE(is_moving(a));

   sensors.SetLeftSonar(0.5);
   obs.Update();
   a = obs.GetAction();
   EXPECT_TRUE(is_moving(a));

   sensors.SetLeftSonar(0.7);
   obs.Update();
   a = obs.GetAction();
   EXPECT_TRUE(is_moving(a));

   sensors.SetLeftSonar(0.8);
   obs.Update();
   a = obs.GetAction();
   EXPECT_TRUE(is_moving(a));
}

TEST(ObstacleBehavior, rightSonarTriggersMovement)
{
   SwarmieSensors sensors;
   Action a;
   sensors.SetLeftSonar(3.2);
   sensors.SetRightSonar(3.2);
   sensors.SetCenterSonar(3.2);

   ObstacleBehavior<ROSTimer> obs(&sensors);
   obs.Update();

   sensors.SetRightSonar(0.3);
   obs.Update();
   a = obs.GetAction();
   EXPECT_TRUE(is_moving(a));

   sensors.SetRightSonar(0.5);
   obs.Update();
   a = obs.GetAction();
   EXPECT_TRUE(is_moving(a));

   sensors.SetRightSonar(0.7);
   obs.Update();
   a = obs.GetAction();
   EXPECT_TRUE(is_moving(a));
 
   sensors.SetRightSonar(0.8);
   obs.Update();
   a = obs.GetAction();
   EXPECT_TRUE(is_moving(a));
}

TEST(ObstacleBehavior, centerSonarTriggersMovement)
{
   SwarmieSensors sensors;
   Action a;
   sensors.SetLeftSonar(3.2);
   sensors.SetRightSonar(3.2);
   sensors.SetCenterSonar(3.2);

   ObstacleBehavior<ROSTimer> obs(&sensors);
   obs.Update();

   sensors.SetCenterSonar(0.3);
   obs.Update();
   a = obs.GetAction();
   EXPECT_TRUE(is_moving(a));

   sensors.SetCenterSonar(0.5);
   obs.Update();
   a = obs.GetAction();
   EXPECT_TRUE(is_moving(a));

   sensors.SetCenterSonar(0.7);
   obs.Update();
   a = obs.GetAction();
   EXPECT_TRUE(is_moving(a));
 
   sensors.SetCenterSonar(0.79);
   obs.Update();
   a = obs.GetAction();
   EXPECT_TRUE(is_moving(a));
}


// TODO: If any one sonar reads below 0.3 then left + right = 0 &&
// left /= 0 && right /= 0. ie. the action is to turn in place.
TEST(ObstacleBehavior, leftTriggersTurnaround)
{
   Action a;
   SwarmieSensors sensors;
   sensors.SetLeftSonar(3.2);
   sensors.SetRightSonar(3.2);
   sensors.SetCenterSonar(3.2);
   ObstacleBehavior<ROSTimer> obs(&sensors);
   obs.Update();

   sensors.SetLeftSonar(0.29);
   obs.Update();
   a = obs.GetAction();
   ASSERT_NE(a.drive.left, 0);
   ASSERT_NE(a.drive.right, 0);
   EXPECT_EQ(a.drive.left, -(a.drive.right));
}

TEST(ObstacleBehavior, rightTriggersTurnaround)
{
   Action a;
   SwarmieSensors sensors;
   sensors.SetLeftSonar(3.2);
   sensors.SetRightSonar(3.2);
   sensors.SetCenterSonar(3.2);
   ObstacleBehavior<ROSTimer> obs(&sensors);
   obs.Update();

   sensors.SetRightSonar(0.29);
   obs.Update();
   a = obs.GetAction();
   ASSERT_NE(a.drive.left, 0);
   ASSERT_NE(a.drive.right, 0);
   EXPECT_EQ(a.drive.left, -(a.drive.right));
}

TEST(ObstacleBehavior, centerSonarTriggersTurnaround)
{
   Action a;
   SwarmieSensors sensors;
   sensors.SetLeftSonar(3.2);
   sensors.SetRightSonar(3.2);
   sensors.SetCenterSonar(3.2);
   ObstacleBehavior<ROSTimer> obs(&sensors);
   obs.Update();

   sensors.SetCenterSonar(0.29);
   obs.Update();
   a = obs.GetAction();
   ASSERT_NE(a.drive.left, 0);
   ASSERT_NE(a.drive.right, 0);
   EXPECT_EQ(a.drive.left, -(a.drive.right));
}

TEST(ObstacleBehavior, leftAndRightTriggerTurnaround)
{
   Action a;
   SwarmieSensors sensors;
   sensors.SetLeftSonar(3.2);
   sensors.SetRightSonar(3.2);
   sensors.SetCenterSonar(3.2);
   ObstacleBehavior<ROSTimer> obs(&sensors);
   obs.Update();

   sensors.SetLeftSonar(0.2);
   sensors.SetRightSonar(0.28);
   obs.Update();
   a = obs.GetAction();
   ASSERT_NE(a.drive.left, 0);
   ASSERT_NE(a.drive.right, 0);
   EXPECT_EQ(a.drive.left, -(a.drive.right));
}

TEST(ObstacleBehavior, leftAndCenterTriggerTurnaround)
{
   Action a;
   SwarmieSensors sensors;
   sensors.SetLeftSonar(3.2);
   sensors.SetRightSonar(3.2);
   sensors.SetCenterSonar(3.2);
   ObstacleBehavior<ROSTimer> obs(&sensors);
   obs.Update();

   sensors.SetLeftSonar(0.2);
   sensors.SetCenterSonar(0.28);
   obs.Update();
   a = obs.GetAction();
   ASSERT_NE(a.drive.left, 0);
   ASSERT_NE(a.drive.right, 0);
   EXPECT_EQ(a.drive.left, -(a.drive.right));
}

TEST(ObstacleBehavior, centerAndRightTriggerTurnaround)
{
   Action a;
   SwarmieSensors sensors;
   sensors.SetLeftSonar(3.2);
   sensors.SetRightSonar(3.2);
   sensors.SetCenterSonar(3.2);
   ObstacleBehavior<ROSTimer> obs(&sensors);
   obs.Update();

   sensors.SetCenterSonar(0.2);
   sensors.SetRightSonar(0.28);
   obs.Update();
   a = obs.GetAction();
   ASSERT_NE(a.drive.left, 0);
   ASSERT_NE(a.drive.right, 0);
   EXPECT_EQ(a.drive.left, -(a.drive.right));
}

TEST(ObstacleBehavior, allTriggerTurnaround)
{
   Action a;
   SwarmieSensors sensors;
   sensors.SetLeftSonar(3.2);
   sensors.SetRightSonar(3.2);
   sensors.SetCenterSonar(3.2);
   ObstacleBehavior<ROSTimer> obs(&sensors);
   obs.Update();

   sensors.SetCenterSonar(0.2);
   sensors.SetRightSonar(0.28);
   sensors.SetLeftSonar(0.1);
   obs.Update();
   a = obs.GetAction();
   ASSERT_NE(a.drive.left, 0);
   ASSERT_NE(a.drive.right, 0);
   EXPECT_EQ(a.drive.left, -(a.drive.right));
}