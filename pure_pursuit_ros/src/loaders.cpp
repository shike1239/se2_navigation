/*
 * AckermannSteeringControllerLoader.cpp
 *
 *  Created on: Mar 26, 2020
 *      Author: jelavice
 */

#include "pure_pursuit_ros/loaders.hpp"
#include <ros/ros.h>
#include <yaml-cpp/yaml.h>
#include <stdexcept>

namespace pure_pursuit {

AckermannSteeringCtrlParameters loadAckermannSteeringControllerParameters(const std::string& filename) {
  YAML::Node basenode = YAML::LoadFile(filename);

  if (basenode.IsNull()) {
    throw std::runtime_error("AckermannSteeringControllerLoader::loadParameters loading failed");
  }

  auto node = basenode["heading_control"];

  AckermannSteeringCtrlParameters parameters;
  parameters.anchorDistanceBck_ = node["anchor_dist_bck"].as<double>();
  parameters.anchorDistanceFwd_ = node["anchor_dist_fwd"].as<double>();
  parameters.lookaheadDistanceBck_ = node["lookahead_bck"].as<double>();
  parameters.lookaheadDistanceFwd_ = node["lookahead_fwd"].as<double>();
  parameters.deadZoneWidth_ = node["dead_zone_width"].as<double>();
  parameters.avgFilgerCurrentSampleWeight_ = node["avg_filter_current_sample_weight"].as<double>();

  //ackermann specific
  auto ackermannNode = node["heading_control_ackermann"];
  parameters.wheelBase_ = ackermannNode["wheel_base"].as<double>();
  parameters.maxSteeringAngleMagnitude_ = ackermannNode["max_steering_angle_magnitude"].as<double>();
  parameters.maxSteeringRateOfChange_ = ackermannNode["max_steering_rate_of_change"].as<double>();

  return parameters;
}

ConstantVelocityControllerParameters loadConstantVelocityControllerParameters(const std::string& filename) {
  YAML::Node basenode = YAML::LoadFile(filename);

  if (basenode.IsNull()) {
    throw std::runtime_error("ConstantVelocityControllerLoader::loadParameters loading failed");
  }

  auto node = basenode["constant_velocity_control"];
  ConstantVelocityControllerParameters parameters;
  parameters.constantDesiredVelocity_ = node["desired_velocity"].as<double>();

  return parameters;
}

SimplePathTrackerParameters loadSimplePathTrackerParameters(const std::string& filename) {
  YAML::Node basenode = YAML::LoadFile(filename);

  if (basenode.IsNull()) {
    throw std::runtime_error("SimplePathTrackerLoader::loadParameters loading failed");
  }

  auto node = basenode["path_tracking"];
  SimplePathTrackerParameters parameters;
  parameters.waitingTimeBetweenDirectionSwitches_ = node["waiting_time_between_direction_changes"].as<double>();

  return parameters;
}

ProgressValidatorParameters loadProgressValidatorParameters(const std::string& filename) {
  YAML::Node basenode = YAML::LoadFile(filename);

  if (basenode.IsNull()) {
    throw std::runtime_error("ProgressValidatorLoader::loadParameters loading failed");
  }

  auto node = basenode["progress_validation"];
  ProgressValidatorParameters parameters;
  parameters.goalDistanceTolerance_ = node["goal_distance_tolerance"].as<double>();

  return parameters;
}

PathPreprocessorParameters loadPathPreprocessorParameters(const std::string& filename) {
  YAML::Node basenode = YAML::LoadFile(filename);

  if (basenode.IsNull()) {
    throw std::runtime_error("PathPreprocessorLoader::loadParameters loading failed");
  }

  auto node = basenode["path_preprocessing"];
  PathPreprocessorParameters parameters;
  parameters.minimumSegmentLength_ = node["minimal_segment_length"].as<double>();

  return parameters;
}

} /* namespace pure_pursuit */
