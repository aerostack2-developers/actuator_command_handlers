#ifndef BASIC_CONTROL_COMMANDS_HPP
#define BASIC_CONTROL_COMMANDS_HPP

#include <as2_core/synchronous_service_client.hpp>
#include <as2_msgs/msg/platform_info.hpp>
#include <as2_msgs/msg/thrust.hpp>
#include <as2_msgs/srv/set_control_mode.hpp>
#include <functional>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>
#include <memory>
#include <thread>

#include "as2_core/node.hpp"
#include "rclcpp/rclcpp.hpp"
#include "as2_core/names/topics.hpp"
#include "as2_core/names/services.hpp"
#include "as2_core/synchronous_service_client.hpp"
#include "as2_msgs/msg/control_mode.hpp"

#define AUX_NODE_SPIN_RATE 10

namespace as2
{
namespace controlCommandsHandlers
{
class BasicControlCommandsHandler
{
public:
  BasicControlCommandsHandler(as2::Node * as2_ptr);
  ~BasicControlCommandsHandler();

private:
  static int number_of_instances_;

  static rclcpp::Client<as2_msgs::srv::SetControlMode>::SharedPtr set_mode_client_;
  static rclcpp::Subscription<as2_msgs::msg::PlatformInfo>::SharedPtr platform_info_sub_;
  as2::SynchronousServiceClient<as2_msgs::srv::SetControlMode>::SharedPtr  set_mode_client_ptr_;
  static as2_msgs::msg::ControlMode current_mode_;

protected:
  as2::Node * node_ptr_;
  geometry_msgs::msg::PoseStamped command_pose_msg_;
  geometry_msgs::msg::TwistStamped command_twist_msg_;
  as2_msgs::msg::Thrust command_thrust_msg_;

  virtual as2_msgs::msg::ControlMode ownSetControlMode() = 0;

  bool sendCommand();

private:
  rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr command_twist_pub_;
  rclcpp::Publisher<as2_msgs::msg::Thrust>::SharedPtr command_thrust_pub_;
  rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr command_pose_pub_;
  as2_msgs::msg::ControlMode desired_control_mode_;

  bool setMode(const as2_msgs::msg::ControlMode & mode);
  void setControlMode() { desired_control_mode_ = ownSetControlMode(); };
  void publishCommands();
};

}  // namespace controlCommandsHandlers
}  // namespace as2

#endif  // BASIC_CONTROL_COMMANDS_HPP
