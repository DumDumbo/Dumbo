# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from ros_stm32_serial/serial_topic_msgs.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class serial_topic_msgs(genpy.Message):
  _md5sum = "d5bec99ac5726ba6e665cc5e4980b15b"
  _type = "ros_stm32_serial/serial_topic_msgs"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """float64 flag
float64 status
float64 linearX
float64 linearY
float64 angularZ
int32 LaserFront
int32 LaserL
int32 LaserR
int32 LaserRear
uint8 Roller
uint8 Mode
uint8 KeepOrNot
uint8 PlaceOrNot
string RobotStatus
"""
  __slots__ = ['flag','status','linearX','linearY','angularZ','LaserFront','LaserL','LaserR','LaserRear','Roller','Mode','KeepOrNot','PlaceOrNot','RobotStatus']
  _slot_types = ['float64','float64','float64','float64','float64','int32','int32','int32','int32','uint8','uint8','uint8','uint8','string']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       flag,status,linearX,linearY,angularZ,LaserFront,LaserL,LaserR,LaserRear,Roller,Mode,KeepOrNot,PlaceOrNot,RobotStatus

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(serial_topic_msgs, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.flag is None:
        self.flag = 0.
      if self.status is None:
        self.status = 0.
      if self.linearX is None:
        self.linearX = 0.
      if self.linearY is None:
        self.linearY = 0.
      if self.angularZ is None:
        self.angularZ = 0.
      if self.LaserFront is None:
        self.LaserFront = 0
      if self.LaserL is None:
        self.LaserL = 0
      if self.LaserR is None:
        self.LaserR = 0
      if self.LaserRear is None:
        self.LaserRear = 0
      if self.Roller is None:
        self.Roller = 0
      if self.Mode is None:
        self.Mode = 0
      if self.KeepOrNot is None:
        self.KeepOrNot = 0
      if self.PlaceOrNot is None:
        self.PlaceOrNot = 0
      if self.RobotStatus is None:
        self.RobotStatus = ''
    else:
      self.flag = 0.
      self.status = 0.
      self.linearX = 0.
      self.linearY = 0.
      self.angularZ = 0.
      self.LaserFront = 0
      self.LaserL = 0
      self.LaserR = 0
      self.LaserRear = 0
      self.Roller = 0
      self.Mode = 0
      self.KeepOrNot = 0
      self.PlaceOrNot = 0
      self.RobotStatus = ''

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
      buff.write(_get_struct_5d4i4B().pack(_x.flag, _x.status, _x.linearX, _x.linearY, _x.angularZ, _x.LaserFront, _x.LaserL, _x.LaserR, _x.LaserRear, _x.Roller, _x.Mode, _x.KeepOrNot, _x.PlaceOrNot))
      _x = self.RobotStatus
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.Struct('<I%ss'%length).pack(length, _x))
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
      end = 0
      _x = self
      start = end
      end += 60
      (_x.flag, _x.status, _x.linearX, _x.linearY, _x.angularZ, _x.LaserFront, _x.LaserL, _x.LaserR, _x.LaserRear, _x.Roller, _x.Mode, _x.KeepOrNot, _x.PlaceOrNot,) = _get_struct_5d4i4B().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.RobotStatus = str[start:end].decode('utf-8', 'rosmsg')
      else:
        self.RobotStatus = str[start:end]
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
      buff.write(_get_struct_5d4i4B().pack(_x.flag, _x.status, _x.linearX, _x.linearY, _x.angularZ, _x.LaserFront, _x.LaserL, _x.LaserR, _x.LaserRear, _x.Roller, _x.Mode, _x.KeepOrNot, _x.PlaceOrNot))
      _x = self.RobotStatus
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.Struct('<I%ss'%length).pack(length, _x))
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
      end = 0
      _x = self
      start = end
      end += 60
      (_x.flag, _x.status, _x.linearX, _x.linearY, _x.angularZ, _x.LaserFront, _x.LaserL, _x.LaserR, _x.LaserRear, _x.Roller, _x.Mode, _x.KeepOrNot, _x.PlaceOrNot,) = _get_struct_5d4i4B().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.RobotStatus = str[start:end].decode('utf-8', 'rosmsg')
      else:
        self.RobotStatus = str[start:end]
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_5d4i4B = None
def _get_struct_5d4i4B():
    global _struct_5d4i4B
    if _struct_5d4i4B is None:
        _struct_5d4i4B = struct.Struct("<5d4i4B")
    return _struct_5d4i4B
