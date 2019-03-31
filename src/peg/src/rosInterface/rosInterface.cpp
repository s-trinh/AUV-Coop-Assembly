#include "header/rosInterface.h"

/** @brief RosInterface Constructor

    @param robotName the name of the robot (found in .xml file of the scene)
    @param topicTwist the name of the topic where twist command must be published
    @param arcg, argv the standard argument of c++ main, they are needed for ros::init
*/
RosInterface::RosInterface(std::string robotName, std::string topicRoot, int argc, char **argv)
{

  ROS_INFO("[ROS_INTERFACE] Start");
  ros::init(argc, argv, "rosInterface");
  ros::NodeHandle nh;

  this->robotName = robotName;
  this->topicRoot = topicRoot;

  pubTwist = nh.advertise<geometry_msgs::TwistStamped>((topicRoot + "twist_command_A"),1);
  pubJoint = nh.advertise<sensor_msgs::JointState>((topicRoot + "joint_command_A"),1);

  subJointState = nh.subscribe(topicRoot+"joint_state_A", 1, &RosInterface::subJointStateCallback, this);
}


int RosInterface::init(){

  if(!ros::ok()){
    return -1;
  }

  //Wait to transform wTv to be ready (or fail if wait more than 3 sec)
  std::string topic = "/" + robotName;
  tfListener_wTv.waitForTransform("world", topic, ros::Time(0), ros::Duration(3.0));

  //Wait to joint state to be ready (ie : the callback is called at least once)
  ros::Rate rate(100);
  while (jState_priv.size()==0){
    ros::spinOnce();
    rate.sleep();
  }

  return 0;
}

int RosInterface::getwTv(Eigen::Matrix4d* wTv_eigen){

  if(!ros::ok()){
    return -1;
  }

  tf::StampedTransform wTv_tf;

  std::string topic = "/" + robotName;
  try {
    tfListener_wTv.lookupTransform("world", topic, ros::Time(0), wTv_tf);

  } catch (tf::TransformException &ex) {
    ROS_ERROR("%s",ex.what());
    ros::Duration(1.0).sleep();
  }

  *wTv_eigen = CONV::transfMatrix_tf2eigen(wTv_tf);

  return 0;
}

void RosInterface::subJointStateCallback(const sensor_msgs::JointState& js)
{
   jState_priv = js.position;
}

/**
 * @brief RosInterface::getJointState
 * @param jState
 * @return
 * @note Doing so, only when main call this function it gets the joint state position
 */
int RosInterface::getJointState(std::vector<double> *jState){

  if(!ros::ok()){
    return -1;
  }

  *jState = jState_priv;
  return 0;
}


int RosInterface::sendQDot(std::vector<double> qDot){

  if(!ros::ok()){
    return -1;
  }
  sensor_msgs::JointState js;
  js.name.push_back(std::string("Slew"));
  js.velocity.push_back(qDot.at(0));
  js.name.push_back(std::string("Shoulder"));
  js.velocity.push_back(qDot.at(1));
  js.name.push_back(std::string("Elbow"));
  js.velocity.push_back(qDot.at(2));
  js.name.push_back(std::string("JawRotate"));
  js.velocity.push_back(qDot.at(3));
  geometry_msgs::TwistStamped twist;
  twist.twist.linear.x=qDot.at(4);
  twist.twist.linear.y=qDot.at(5);
  twist.twist.linear.z=qDot.at(6);
  twist.twist.angular.x=qDot.at(7);
  twist.twist.angular.y=qDot.at(8);
  twist.twist.angular.z=qDot.at(9);

  pubJoint.publish(js);
  pubTwist.publish(twist);
  return 0;

}

void RosInterface::spinOnce(){
  ros::spinOnce();
}
