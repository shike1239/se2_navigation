/*
 * OmplReedsSheppPlannerRos.hpp
 *
 *  Created on: Apr 2, 2020
 *      Author: jelavice
 */

#pragma once

#include "se2_planning/OmplReedsSheppPlanner.hpp"

#include <nav_msgs/Path.h>
#include <ros/ros.h>
#include <string>
#include "se2_navigation_msgs/PathRequestSrv.h"

namespace se2_planning {

struct OmplReedsSheppPlannerRosParameters : public OmplReedsSheppPlannerParameters {
  std::string pathFrame_ = "map";
  std::string pathNavMsgTopic_ = "ompl_rs_planner_ros/nav_msgs_path";
  std::string planningSerivceName_ = "ompl_rs_planner_ros/planning_service";
};

class OmplReedsSheppPlannerRos : public OmplReedsSheppPlanner {
  using BASE = OmplReedsSheppPlanner;

 public:
  explicit OmplReedsSheppPlannerRos(ros::NodeHandle* nh);
  ~OmplReedsSheppPlannerRos() override = default;

  bool initialize() final;
  bool plan() final;
  void setParameters(const OmplReedsSheppPlannerRosParameters& parameters);

 private:
  void initRos();
  void publishPathNavMsgs() const;
  using PlanningService = se2_navigation_msgs::PathRequestSrv;

  bool planningService(PlanningService::Request& req, PlanningService::Response& res);

  ros::NodeHandle* nh_;
  ros::Publisher pathNavMsgsPublisher_;
  OmplReedsSheppPlannerRosParameters parameters_;
  ros::ServiceServer planningService_;
};

nav_msgs::Path copyAllPoints(const ReedsSheppPath& path);
geometry_msgs::Pose convert(const ReedsSheppState& state, double z = 0.0);
ReedsSheppState convert(const geometry_msgs::Pose& state);

} /* namespace se2_planning */