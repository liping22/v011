/*
 *  Copyright (c) 2013-2014, Filippo Basso <bassofil@dei.unipd.it>
 *
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *     1. Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *     2. Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *     3. Neither the name of the copyright holder(s) nor the
 *        names of its contributors may be used to endorse or promote products
 *        derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 *  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <gtest/gtest.h>
#include <calibration_common/objects/base_object.h>

using calibration::BaseObject;

TEST(BaseObject, BaseObject)
{
  BaseObject object;

  EXPECT_EQ(object.frameId(), "");
  EXPECT_FALSE(object.parent());
  EXPECT_EQ(object.pose().matrix(), Eigen::Affine3d::Identity().matrix());
}

TEST(BaseObject, setFrameId)
{
  BaseObject object;
  object.setFrameId("Object");

  EXPECT_EQ(object.frameId(), "Object");
}

TEST(BaseObject, setParent)
{
  BaseObject::Ptr parent(new BaseObject());
  parent->setFrameId("Parent");
  BaseObject object;
  object.setParent(parent);

  EXPECT_TRUE(object.parent());
  EXPECT_EQ(object.parent()->frameId(), "Parent");
}

TEST(BaseObject, transform)
{
  BaseObject object;
  Eigen::Translation3d translation(1, 2, 3);
  Eigen::Affine3d transform(translation);

  object.transform(transform);
  EXPECT_EQ(object.pose().matrix(), transform.matrix());

  object.transform(transform);
  transform = translation * transform;
  EXPECT_EQ(object.pose().matrix(), transform.matrix());
}
