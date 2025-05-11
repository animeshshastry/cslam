#include <memory>
#include <tuple>
#include "cslam/back_end/decentralized_pgo.h"

namespace cslam {
  class PoseGraphManagerComponent : public rclcpp::Node
  {
    public:
      std::shared_ptr<DecentralizedPGO> manager;
      PoseGraphManagerComponent(rclcpp::NodeOptions ops) : Node("pose_graph_manager", ops.start_parameter_event_publisher(false).start_parameter_services(false))
      {
        declare_parameter<std::string>("frontend.sensor_base_frame", "base_link");
        declare_parameter<std::string>("frontend.kf_frame", "kf");
        declare_parameter<std::string>("frontend.kf_opt_frame", "kf_opt");
        declare_parameter<std::string>("frontend.odom_frame", "odom");
        declare_parameter<std::string>("frontend.map_frame", "map");

       declare_parameter<std::vector<std::string>>("robot_names", {"a","b"});
       declare_parameter<int>("robot_id", 0);
       declare_parameter<int>("backend.pose_graph_optimization_start_period_ms", 1000);
       declare_parameter<int>("backend.pose_graph_optimization_loop_period_ms", 100);
       declare_parameter<int>("backend.max_waiting_time_sec", 100);
       declare_parameter<bool>("backend.enable_broadcast_tf_frames", true);
       declare_parameter<std::string>("backend.solver", "CHOLMOD");
       declare_parameter<bool>("backend.enable_gravity_factor", false);
       declare_parameter<double>("neighbor_management.heartbeat_period_sec", 1.0);
       declare_parameter<bool>("evaluation.enable_logs", false);
       declare_parameter<std::string>("evaluation.log_folder", "");
       declare_parameter<bool>("evaluation.enable_gps_recording", false);
       declare_parameter<bool>("evaluation.enable_simulated_rendezvous", false);
       declare_parameter<std::string>("evaluation.rendezvous_schedule_file", "");
       declare_parameter<bool>("evaluation.enable_pose_timestamps_recording", false);
       declare_parameter<bool>("visualization.enable", false);
       declare_parameter<std::string>("frontend.sensor_base_frame_id", ""); // If empty we assume that the camera link is the base link
       declare_parameter<int>("visualization.publishing_period_ms", 0);
      manager = std::make_shared<DecentralizedPGO>(this);
      }
  };
};

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(cslam::PoseGraphManagerComponent)