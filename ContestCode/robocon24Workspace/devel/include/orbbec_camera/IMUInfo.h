// Generated by gencpp from file orbbec_camera/IMUInfo.msg
// DO NOT EDIT!


#ifndef ORBBEC_CAMERA_MESSAGE_IMUINFO_H
#define ORBBEC_CAMERA_MESSAGE_IMUINFO_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace orbbec_camera
{
template <class ContainerAllocator>
struct IMUInfo_
{
  typedef IMUInfo_<ContainerAllocator> Type;

  IMUInfo_()
    : header()
    , noise_density(0.0)
    , random_walk(0.0)
    , reference_temperature(0.0)
    , bias()
    , gravity()
    , scale_misalignment()
    , temperature_slope()  {
      bias.assign(0.0);

      gravity.assign(0.0);

      scale_misalignment.assign(0.0);

      temperature_slope.assign(0.0);
  }
  IMUInfo_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , noise_density(0.0)
    , random_walk(0.0)
    , reference_temperature(0.0)
    , bias()
    , gravity()
    , scale_misalignment()
    , temperature_slope()  {
  (void)_alloc;
      bias.assign(0.0);

      gravity.assign(0.0);

      scale_misalignment.assign(0.0);

      temperature_slope.assign(0.0);
  }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef double _noise_density_type;
  _noise_density_type noise_density;

   typedef double _random_walk_type;
  _random_walk_type random_walk;

   typedef double _reference_temperature_type;
  _reference_temperature_type reference_temperature;

   typedef boost::array<double, 3>  _bias_type;
  _bias_type bias;

   typedef boost::array<double, 3>  _gravity_type;
  _gravity_type gravity;

   typedef boost::array<double, 9>  _scale_misalignment_type;
  _scale_misalignment_type scale_misalignment;

   typedef boost::array<double, 9>  _temperature_slope_type;
  _temperature_slope_type temperature_slope;





  typedef boost::shared_ptr< ::orbbec_camera::IMUInfo_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::orbbec_camera::IMUInfo_<ContainerAllocator> const> ConstPtr;

}; // struct IMUInfo_

typedef ::orbbec_camera::IMUInfo_<std::allocator<void> > IMUInfo;

typedef boost::shared_ptr< ::orbbec_camera::IMUInfo > IMUInfoPtr;
typedef boost::shared_ptr< ::orbbec_camera::IMUInfo const> IMUInfoConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::orbbec_camera::IMUInfo_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::orbbec_camera::IMUInfo_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::orbbec_camera::IMUInfo_<ContainerAllocator1> & lhs, const ::orbbec_camera::IMUInfo_<ContainerAllocator2> & rhs)
{
  return lhs.header == rhs.header &&
    lhs.noise_density == rhs.noise_density &&
    lhs.random_walk == rhs.random_walk &&
    lhs.reference_temperature == rhs.reference_temperature &&
    lhs.bias == rhs.bias &&
    lhs.gravity == rhs.gravity &&
    lhs.scale_misalignment == rhs.scale_misalignment &&
    lhs.temperature_slope == rhs.temperature_slope;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::orbbec_camera::IMUInfo_<ContainerAllocator1> & lhs, const ::orbbec_camera::IMUInfo_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace orbbec_camera

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::orbbec_camera::IMUInfo_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::orbbec_camera::IMUInfo_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::orbbec_camera::IMUInfo_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::orbbec_camera::IMUInfo_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::orbbec_camera::IMUInfo_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::orbbec_camera::IMUInfo_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::orbbec_camera::IMUInfo_<ContainerAllocator> >
{
  static const char* value()
  {
    return "efdf590a2d0b51a471d0de8470a87a58";
  }

  static const char* value(const ::orbbec_camera::IMUInfo_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xefdf590a2d0b51a4ULL;
  static const uint64_t static_value2 = 0x71d0de8470a87a58ULL;
};

template<class ContainerAllocator>
struct DataType< ::orbbec_camera::IMUInfo_<ContainerAllocator> >
{
  static const char* value()
  {
    return "orbbec_camera/IMUInfo";
  }

  static const char* value(const ::orbbec_camera::IMUInfo_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::orbbec_camera::IMUInfo_<ContainerAllocator> >
{
  static const char* value()
  {
    return "std_msgs/Header header\n"
"float64 noise_density\n"
"float64 random_walk\n"
"float64 reference_temperature\n"
"float64[3] bias\n"
"float64[3] gravity\n"
"float64[9] scale_misalignment\n"
"float64[9] temperature_slope\n"
"\n"
"\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
;
  }

  static const char* value(const ::orbbec_camera::IMUInfo_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::orbbec_camera::IMUInfo_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.noise_density);
      stream.next(m.random_walk);
      stream.next(m.reference_temperature);
      stream.next(m.bias);
      stream.next(m.gravity);
      stream.next(m.scale_misalignment);
      stream.next(m.temperature_slope);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct IMUInfo_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::orbbec_camera::IMUInfo_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::orbbec_camera::IMUInfo_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "noise_density: ";
    Printer<double>::stream(s, indent + "  ", v.noise_density);
    s << indent << "random_walk: ";
    Printer<double>::stream(s, indent + "  ", v.random_walk);
    s << indent << "reference_temperature: ";
    Printer<double>::stream(s, indent + "  ", v.reference_temperature);
    s << indent << "bias[]" << std::endl;
    for (size_t i = 0; i < v.bias.size(); ++i)
    {
      s << indent << "  bias[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.bias[i]);
    }
    s << indent << "gravity[]" << std::endl;
    for (size_t i = 0; i < v.gravity.size(); ++i)
    {
      s << indent << "  gravity[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.gravity[i]);
    }
    s << indent << "scale_misalignment[]" << std::endl;
    for (size_t i = 0; i < v.scale_misalignment.size(); ++i)
    {
      s << indent << "  scale_misalignment[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.scale_misalignment[i]);
    }
    s << indent << "temperature_slope[]" << std::endl;
    for (size_t i = 0; i < v.temperature_slope.size(); ++i)
    {
      s << indent << "  temperature_slope[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.temperature_slope[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // ORBBEC_CAMERA_MESSAGE_IMUINFO_H
