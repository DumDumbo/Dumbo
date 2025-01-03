# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from orbbec_camera/IMUInfo.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import std_msgs.msg

class IMUInfo(genpy.Message):
  _md5sum = "efdf590a2d0b51a471d0de8470a87a58"
  _type = "orbbec_camera/IMUInfo"
  _has_header = True  # flag to mark the presence of a Header object
  _full_text = """std_msgs/Header header
float64 noise_density
float64 random_walk
float64 reference_temperature
float64[3] bias
float64[3] gravity
float64[9] scale_misalignment
float64[9] temperature_slope


================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id
"""
  __slots__ = ['header','noise_density','random_walk','reference_temperature','bias','gravity','scale_misalignment','temperature_slope']
  _slot_types = ['std_msgs/Header','float64','float64','float64','float64[3]','float64[3]','float64[9]','float64[9]']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       header,noise_density,random_walk,reference_temperature,bias,gravity,scale_misalignment,temperature_slope

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(IMUInfo, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.noise_density is None:
        self.noise_density = 0.
      if self.random_walk is None:
        self.random_walk = 0.
      if self.reference_temperature is None:
        self.reference_temperature = 0.
      if self.bias is None:
        self.bias = [0.] * 3
      if self.gravity is None:
        self.gravity = [0.] * 3
      if self.scale_misalignment is None:
        self.scale_misalignment = [0.] * 9
      if self.temperature_slope is None:
        self.temperature_slope = [0.] * 9
    else:
      self.header = std_msgs.msg.Header()
      self.noise_density = 0.
      self.random_walk = 0.
      self.reference_temperature = 0.
      self.bias = [0.] * 3
      self.gravity = [0.] * 3
      self.scale_misalignment = [0.] * 9
      self.temperature_slope = [0.] * 9

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_3I().pack(_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs))
      _x = self.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.Struct('<I%ss'%length).pack(length, _x))
      _x = self
      buff.write(_get_struct_3d().pack(_x.noise_density, _x.random_walk, _x.reference_temperature))
      buff.write(_get_struct_3d().pack(*self.bias))
      buff.write(_get_struct_3d().pack(*self.gravity))
      buff.write(_get_struct_9d().pack(*self.scale_misalignment))
      buff.write(_get_struct_9d().pack(*self.temperature_slope))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      if self.header is None:
        self.header = std_msgs.msg.Header()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs,) = _get_struct_3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.header.frame_id = str[start:end].decode('utf-8', 'rosmsg')
      else:
        self.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 24
      (_x.noise_density, _x.random_walk, _x.reference_temperature,) = _get_struct_3d().unpack(str[start:end])
      start = end
      end += 24
      self.bias = _get_struct_3d().unpack(str[start:end])
      start = end
      end += 24
      self.gravity = _get_struct_3d().unpack(str[start:end])
      start = end
      end += 72
      self.scale_misalignment = _get_struct_9d().unpack(str[start:end])
      start = end
      end += 72
      self.temperature_slope = _get_struct_9d().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_3I().pack(_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs))
      _x = self.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.Struct('<I%ss'%length).pack(length, _x))
      _x = self
      buff.write(_get_struct_3d().pack(_x.noise_density, _x.random_walk, _x.reference_temperature))
      buff.write(self.bias.tostring())
      buff.write(self.gravity.tostring())
      buff.write(self.scale_misalignment.tostring())
      buff.write(self.temperature_slope.tostring())
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      if self.header is None:
        self.header = std_msgs.msg.Header()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs,) = _get_struct_3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.header.frame_id = str[start:end].decode('utf-8', 'rosmsg')
      else:
        self.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 24
      (_x.noise_density, _x.random_walk, _x.reference_temperature,) = _get_struct_3d().unpack(str[start:end])
      start = end
      end += 24
      self.bias = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=3)
      start = end
      end += 24
      self.gravity = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=3)
      start = end
      end += 72
      self.scale_misalignment = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=9)
      start = end
      end += 72
      self.temperature_slope = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=9)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_3I = None
def _get_struct_3I():
    global _struct_3I
    if _struct_3I is None:
        _struct_3I = struct.Struct("<3I")
    return _struct_3I
_struct_3d = None
def _get_struct_3d():
    global _struct_3d
    if _struct_3d is None:
        _struct_3d = struct.Struct("<3d")
    return _struct_3d
_struct_9d = None
def _get_struct_9d():
    global _struct_9d
    if _struct_9d is None:
        _struct_9d = struct.Struct("<9d")
    return _struct_9d
