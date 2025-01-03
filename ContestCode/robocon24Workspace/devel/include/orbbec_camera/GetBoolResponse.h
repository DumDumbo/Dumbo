// Generated by gencpp from file orbbec_camera/GetBoolResponse.msg
// DO NOT EDIT!


#ifndef ORBBEC_CAMERA_MESSAGE_GETBOOLRESPONSE_H
#define ORBBEC_CAMERA_MESSAGE_GETBOOLRESPONSE_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace orbbec_camera
{
template <class ContainerAllocator>
struct GetBoolResponse_
{
  typedef GetBoolResponse_<ContainerAllocator> Type;

  GetBoolResponse_()
    : data(false)
    , success(false)
    , message()  {
    }
  GetBoolResponse_(const ContainerAllocator& _alloc)
    : data(false)
    , success(false)
    , message(_alloc)  {
  (void)_alloc;
    }



   typedef uint8_t _data_type;
  _data_type data;

   typedef uint8_t _success_type;
  _success_type success;

   typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _message_type;
  _message_type message;





  typedef boost::shared_ptr< ::orbbec_camera::GetBoolResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::orbbec_camera::GetBoolResponse_<ContainerAllocator> const> ConstPtr;

}; // struct GetBoolResponse_

typedef ::orbbec_camera::GetBoolResponse_<std::allocator<void> > GetBoolResponse;

typedef boost::shared_ptr< ::orbbec_camera::GetBoolResponse > GetBoolResponsePtr;
typedef boost::shared_ptr< ::orbbec_camera::GetBoolResponse const> GetBoolResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::orbbec_camera::GetBoolResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::orbbec_camera::GetBoolResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::orbbec_camera::GetBoolResponse_<ContainerAllocator1> & lhs, const ::orbbec_camera::GetBoolResponse_<ContainerAllocator2> & rhs)
{
  return lhs.data == rhs.data &&
    lhs.success == rhs.success &&
    lhs.message == rhs.message;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::orbbec_camera::GetBoolResponse_<ContainerAllocator1> & lhs, const ::orbbec_camera::GetBoolResponse_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace orbbec_camera

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::orbbec_camera::GetBoolResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::orbbec_camera::GetBoolResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::orbbec_camera::GetBoolResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::orbbec_camera::GetBoolResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::orbbec_camera::GetBoolResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::orbbec_camera::GetBoolResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::orbbec_camera::GetBoolResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "43f76a855b16e988566e147b692f2fab";
  }

  static const char* value(const ::orbbec_camera::GetBoolResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x43f76a855b16e988ULL;
  static const uint64_t static_value2 = 0x566e147b692f2fabULL;
};

template<class ContainerAllocator>
struct DataType< ::orbbec_camera::GetBoolResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "orbbec_camera/GetBoolResponse";
  }

  static const char* value(const ::orbbec_camera::GetBoolResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::orbbec_camera::GetBoolResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool data\n"
"bool success\n"
"string message\n"
"\n"
;
  }

  static const char* value(const ::orbbec_camera::GetBoolResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::orbbec_camera::GetBoolResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.data);
      stream.next(m.success);
      stream.next(m.message);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct GetBoolResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::orbbec_camera::GetBoolResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::orbbec_camera::GetBoolResponse_<ContainerAllocator>& v)
  {
    s << indent << "data: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.data);
    s << indent << "success: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.success);
    s << indent << "message: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.message);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ORBBEC_CAMERA_MESSAGE_GETBOOLRESPONSE_H
