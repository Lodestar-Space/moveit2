/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2018 Pilz GmbH & Co. KG
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Pilz GmbH & Co. KG nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

#include <pilz_industrial_motion_planner/planning_context_loader_ptp.hpp>
#include <moveit/planning_scene/planning_scene.hpp>
#include <pilz_industrial_motion_planner/planning_context_ptp.hpp>
#include <moveit/utils/logger.hpp>

#include <pluginlib/class_list_macros.hpp>

namespace
{
rclcpp::Logger getLogger()
{
  return moveit::getLogger("moveit.planners.pilz.planning_context_loader.ptp");
}
}  // namespace

pilz_industrial_motion_planner::PlanningContextLoaderPTP::PlanningContextLoaderPTP()
{
  alg_ = "PTP";
}

pilz_industrial_motion_planner::PlanningContextLoaderPTP::~PlanningContextLoaderPTP()
{
}

bool pilz_industrial_motion_planner::PlanningContextLoaderPTP::loadContext(
    planning_interface::PlanningContextPtr& planning_context, const std::string& name, const std::string& group) const
{
  if (limits_set_ && model_set_)
  {
    planning_context = std::make_shared<PlanningContextPTP>(name, group, model_, limits_);
    return true;
  }
  else
  {
    if (!limits_set_)
    {
      RCLCPP_ERROR_STREAM(getLogger(),
                          "Joint Limits are not defined. Cannot load planning context. Call setLimits loadContext");
    }
    if (!model_set_)
    {
      RCLCPP_ERROR_STREAM(getLogger(), "Robot model was not set");
    }
    return false;
  }
}

PLUGINLIB_EXPORT_CLASS(pilz_industrial_motion_planner::PlanningContextLoaderPTP,
                       pilz_industrial_motion_planner::PlanningContextLoader)
